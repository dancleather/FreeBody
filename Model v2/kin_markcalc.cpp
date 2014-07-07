#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"
#include "kinematics.h"
using namespace std;

/*

These routines calculate the rotation and translation that represent the transformation of a set of markers from
one position to another based on various descriptions of rotation and numerical methods

1. Quaternion basis

Calculates the unit quaternion representing the rotation and the vector representing the translation

Arguments:
Input:
p0, p1 - 3xn matrices which contain n marker positions before and after transformation respectively
Output:
q - unit quaternion
t - translation vector

Dependencies:
Numerical Recipes: tqli, tred2
Mathematics: max, qnormalise
Kinematics: kin_crossdisp, kin_qrotate

References:
Horn, B. K. P. (1987).  Closed form solution of absolute orientation using unit quaternions.
Journal of Optical Society of America, 4(4), 629-642.

2. Rotation matrix basis

Calculates the rotation matrix and the vector representing the translation

Arguments:
Input:
p0, p1 - 3xn matrices which contain n marker positions before and after transformation respectively
Output:
m - 3x3 rotation matrix
t - translation vector

Dependencies:
Numerical Recipes: pythag, svdcmp
Mathematics: det2, det3, mxmply, transpose, math_zeromatrix
Kinematics: kin_crossdisp

References:
Based on Sommer, J. Fortran routine downloaded from http://isbweb.org/software/movanal/sommer.txt
on 20th July 2006
Challis, J. H. (1995).  A procedure for determining rigid body transformation parameters.
Journal of Biomechanics, 28(6), 733-737.

*/

void KINEMATICS::kin_markcalc(Mat_DP p0, Mat_DP p1, Vec_DP &q, Vec_DP &t) {

	int x;
	Vec_DP xbar0(3), xbar1(3), a(4), b(4);
	Mat_DP cross(3,3), n(4,4);

	for (int i=0; i<4; i++) {
		q[i]=0;		
	}

	KINEMATICS::kin_crossdisp(p1,p0,xbar1,xbar0,cross);

	n[0][0]=cross[0][0]+cross[1][1]+cross[2][2];
	n[0][1]=cross[1][2]-cross[2][1];
	n[0][2]=cross[2][0]-cross[0][2];
	n[0][3]=cross[0][1]-cross[1][0];
	n[1][0]=cross[1][2]-cross[2][1];
	n[1][1]=cross[0][0]-cross[1][1]-cross[2][2];
	n[1][2]=cross[0][1]+cross[1][0];
	n[1][3]=cross[2][0]+cross[0][2];
	n[2][0]=cross[2][0]-cross[0][2];
	n[2][1]=cross[0][1]+cross[1][0];
	n[2][2]=-cross[0][0]+cross[1][1]-cross[2][2];
	n[2][3]=cross[1][2]+cross[2][1];
	n[3][0]=cross[0][1]-cross[1][0];
	n[3][1]=cross[2][0]+cross[0][2];
	n[3][2]=cross[1][2]+cross[2][1];
	n[3][3]=-cross[0][0]-cross[1][1]+cross[2][2];

	NR::tred2(n,a,b);
	NR::tqli(a,b,n);				// Calculate eigenvalues and eigenvectors of n

	x=MATHEMATICS::math_max(a);		

	for (int i=0; i<4; i++) {
		q[i]=n[i][x];				// Select eigenvector corresponding to most positive eigenvalue
	}

	q=MATHEMATICS::math_qnormalise(q);	// Calculate unit quaternion

	if (q[0]<0) {
		for (int i=0; i<4; i++) {
			q[i]=-1*q[i];
		}
	}

	KINEMATICS::kin_qrotate(xbar0,q,t);

	for (int i=0; i<3; i++) {
		t[i]=xbar1[i]-t[i];			// Calculate translation vector
	}

	return;
}
void KINEMATICS::kin_markcalc(Mat_DP p0, Mat_DP p1, Mat_DP &m, Vec_DP &t) {

	double du, dvt;
	Vec_DP xbar0(3), xbar1(3), w(3);
	Mat_DP cross(3,3), u(3,3), v(3,3), vt(3,3), z(3,3);

	KINEMATICS::kin_crossdisp(p0,p1,xbar0,xbar1,cross);	// Calculate cross-dispersion matrix

	u=cross;
	NR::svdcmp(u,w,v);		// Singular value decompostion of cross-dispersion matrix

	vt=MATHEMATICS::math_transpose(v);

	du=MATHEMATICS::math_det3(u);
	dvt=MATHEMATICS::math_det3(vt);

	MATHEMATICS::math_zeromatrix(z);

	z[0][0]=1, z[1][1]=1, z[2][2]=du*dvt;

	m=MATHEMATICS::math_mxmply(z,vt);
	m=MATHEMATICS::math_mxmply(u,m);		// Calculate rotation matrix

	xbar0=MATHEMATICS::math_mxmply(m,xbar0);

	for (int i=0; i<3; i++) {
		t[i]=xbar1[i]-xbar0[i];		// Calculate translation vector
	}

	return;
}