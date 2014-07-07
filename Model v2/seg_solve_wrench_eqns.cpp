#include "stdafx.h"
#include "kinematics.h"
#include "mathematics.h"
#include "Segment.h"
#include "io_outop.h"

/*

Solve Euler equation to calculate proximal moments moving up the kinetic chain

IMPORTANT: This needs to be checked when including external forces

*/

void Segment::seg_solve_wrench_eqns(Vec_DP g) {
	
	// Create all variables

	double mass=this->mass;
	
	Vec_DP origin(this->rot_centre,3), com(this->com,3), distal(this->dist_contact,3);
	Vec_DP q(this->rot_lcs_to_gcs,4);

	Vec_DP c(3), d(3), ex0(3), ex1(3);
	Vec_DP w(3);
	Vec_DP v0(6), v1(6), v2(6), v3(3), v4(3), vex0(6), vex1(6);
	Vec_DP W(6), W0(6), W1(6), W2(6), W3(6);
	
	Mat_DP m0(6,6), m1(6,6), mex0(6,6), mex1(6,6), r(3,3), rinv(3,3), I(3,3), cmat(3,3), dmat(3,3), ex0mat(3,3), ex1mat(3,3);

	for (int i=0; i<6; i++) {
		v0[i]=v1[i]=v2[i]=0;
	}

	MATHEMATICS::math_zeromatrix(m0);
	MATHEMATICS::math_zeromatrix(m1);
	MATHEMATICS::math_zeromatrix(mex0);
	MATHEMATICS::math_zeromatrix(mex1);
	MATHEMATICS::math_zeromatrix(I);


	// Specify all forces acting on the segment

	for (int i=0; i<3; i++) {
		v2[i]=-this->fd[i];
		v2[i+3]=-this->md_segmental_approach[i];
		vex0[i]=-this->external_forces[0][i+3];
		vex0[i+3]=0;
		vex1[i]=-this->external_forces[1][i+3];
		vex1[i+3]=0;
	}

	// Calculate vectors from centre of rotation to point of action of each force
		
	for (int j=0; j<3; j++) {
		c[j]=com[j]-origin[j];
		d[j]=distal[j]-origin[j];
		ex0[j]=this->external_forces[0][j]-origin[j];
		ex1[j]=this->external_forces[1][j]-origin[j];

	}


	// Set up inertial terms etc

	KINEMATICS::kin_rmatcalc(q,r);
	rinv=MATHEMATICS::math_transpose(r);
	for (int j=0; j<3; j++) {
		I[j][j]=this->inertia[j];
		w[j]=this->w[j];
	}

	I=MATHEMATICS::math_mxmply(r,MATHEMATICS::math_mxmply(I,rinv));
	v3=MATHEMATICS::math_crossprd(w,MATHEMATICS::math_mxmply(I,w));

	for(int j=0; j<3; j++) {
		m0[j][j]=mass;	
		for (int k=0; k<3; k++) {
			m0[j+3][k+3]=I[j][k];
		}
		v0[j]=this->acceleration[j]-g[j];
		v0[j+3]=this->a[j];
		v1[j+3]=v3[j];
	}

	for (int j=0; j<3; j++) {
		m1[j][j]=mex0[j][j]=mex1[j][j]=1;
		m1[j+3][j+3]=mex0[j+3][j+3]=mex1[j+3][j+3]=1;
		c[j]=c[j]*mass;
	}

	cmat=MATHEMATICS::math_skew_vec_to_matrix(c);
	dmat=MATHEMATICS::math_skew_vec_to_matrix(d);
	ex0mat=MATHEMATICS::math_skew_vec_to_matrix(ex0);
	ex1mat=MATHEMATICS::math_skew_vec_to_matrix(ex1);

	for (int i=3; i<6; i++) {
		for (int j=0; j<3; j++) {
			m0[i][j]=cmat[i-3][j];
			m1[i][j]=dmat[i-3][j];
			mex0[i][j]=ex0mat[i-3][j];
			mex1[i][j]=ex1mat[i-3][j];
		}
	}

	W0=MATHEMATICS::math_mxmply(m0,v0);
	W1=MATHEMATICS::math_mxmply(m1,v2);
	W2=MATHEMATICS::math_mxmply(mex0,vex0);
	W3=MATHEMATICS::math_mxmply(mex1,vex1);

	// *******************************************************************

	// Solve Euler eqn

	for (int j=0; j<6; j++) {
		W[j]=W0[j]+v1[j]+W1[j]+W2[j]+W3[j];
	}

	// *******************************************************************

	// Save result

	for(int j=0; j<3; j++) {
		this->fp[j]=W[j];
		this->mp_segmental_approach[j]=W[j+3];
	}

	for (int j=0; j<3; j++) {
			v2[j+3]=0;
	}

	W1=MATHEMATICS::math_mxmply(m1,v2);

	// Calculate variables needed for optimization approach to inverse dynamics

	for (int j=0; j<3; j++) {

		this->rhs_opt_approach_1[j]=W0[j]+vex0[j]+vex1[j];
		this->rhs_opt_approach_1[j+3]=W0[j+3]+v1[j+3]+W1[j+3]+W2[j+3]+W3[j+3];
	}
	for (int j=0; j<3; j++) {

		this->rhs_opt_approach_2[j]=W0[j]+vex0[j]+vex1[j];
		this->rhs_opt_approach_2[j+3]=W0[j+3]+v1[j+3]+W2[j+3]+W3[j+3];
	}

	return;
}