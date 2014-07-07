#include "stdafx.h"
#include "kinematics.h"
#include "mathematics.h"
#include "solvewrench.h"
#include "outop.h"

/*

Solve Euler equation to calculate proximal moments moving up the kinetic chain

*/

void solvewrench(Anthropometry *a[], int segments, Segment *s[], Mat_DP cpos, Mat_DP dpos, Mat_DP accn, Mat_DP omeg, Mat_DP alph,
				 int index, double g, Vec_DP dist, Mat_DP &checkout, Mat_DP &rhs, Mat_DP &rhs2, Mat_DP &dmat) {
	
	Vec_DP p0(3);
	Vec_DP c(3), d(3), gravity(3);
	Vec_DP v0(6), v1(6), v2(6), v4(3);
	Vec_DP w(6), w0(6), w1(6), w2(6), v3(3), om(3), checkvec(3);
	
	Mat_DP m0(6,6), m1(6,6), r(3,3), rinv(3,3), I(3,3), check(3,3);

	for (int i=0; i<3; i++) {
		gravity[i]=0;
	}
	gravity[1]=-g;				// Calculate force due to gravity
	for (int i=0; i<6; i++) {
		v0[i]=v1[i]=v2[i]=0;
	}
	for (int i=0; i<3; i++) {
		v2[i]=-s[0]->fd[i];//-ve
		v2[i+3]=-s[0]->md[i];//-ve
	}
//cout << v2;
	for (int i=0; i<segments-1; i++) {			// This loop iterates for each segment

	for (int j=0; j<3; j++) {
		v4[j]=0;
	}

	MATHEMATICS::zeromatrix(m0);
	MATHEMATICS::zeromatrix(m1);
	MATHEMATICS::zeromatrix(I);
	MATHEMATICS::zeromatrix(check);

		Vec_DP p1(s[i]->origin,3);
		
		for (int j=0; j<3; j++) {
			c[j]=cpos[index][3*i+j]-p1[j];
		}
		/*
		if (i==0) {
			for (int j=0; j<3; j++) {
			//	p0[j]=dist[j];
			}			
		}
		else {
		*/	for (int j=0; j<3; j++) {
				p0[j]=dpos[index][3*i+j];
			}
		

		for (int j=0; j<3; j++) {
			d[j]=p0[j]-p1[j];
		}

		Vec_DP q(s[i]->q,4);

		KINEMATICS::rmatcalc(q,r);
		rinv=MATHEMATICS::transpose(r);
		for (int j=0; j<3; j++) {
			I[j][j]=a[i]->inertia[j];
			om[j]=omeg[index][3*i+j];
		}

		I=MATHEMATICS::mxmply(r,MATHEMATICS::mxmply(I,rinv));
		v3=MATHEMATICS::crossprd(om,MATHEMATICS::mxmply(I,om));

		for(int j=0; j<3; j++) {
			m0[j][j]=a[i]->m;	
			for (int k=0; k<3; k++) {
				m0[j+3][k+3]=I[j][k];
			}
			v0[j]=accn[index][3*i+j]-gravity[j];
			v0[j+3]=alph[index][3*i+j];
			v1[j+3]=v3[j];
			checkvec[j]=accn[index][3*i+j]-gravity[j];
		}

		for(int j=0; j<3; j++) {
			m1[j][j]=1;//+ve
			m1[j+3][j+3]=1;//+ve
		}
		m0[3][1]=-c[2]*a[i]->m;
		m0[4][0]=c[2]*a[i]->m;
		m0[3][2]=c[1]*a[i]->m;
		m0[5][0]=-c[1]*a[i]->m;
		m0[4][2]=-c[0]*a[i]->m;
		m0[5][1]=c[0]*a[i]->m;
		m1[3][1]=-d[2];
		m1[4][0]=d[2];
		m1[3][2]=d[1];
		m1[5][0]=-d[1];
		m1[4][2]=-d[0];
		m1[5][1]=d[0];

		w0=MATHEMATICS::mxmply(m0,v0);
		w1=MATHEMATICS::mxmply(m1,v2);

		for (int j=0; j<6; j++) {
			w[j]=w0[j]+v1[j]+w1[j];
		}

		if (i>0) {
			for (int j=0; j<3; j++) {
				v2[j+3]=0;
			}
		}
		w1=MATHEMATICS::mxmply(m1,v2);
		for (int j=0; j<3; j++) {
			rhs[index-2][3*i+j]=w0[j+3]+v1[j+3]+w1[j+3];
		}
		if (i==0) {
			for (int j=0; j<3; j++) {
				v4[j]=v2[j];
			}
		}
//		cout << v4;
		for (int j=0; j<3; j++) {
			rhs2[index-2][3*i+j]=w0[j]+v4[j];
			rhs2[index-2][3*i+9+j]=w0[j+3]+v1[j+3]+w1[j+3];
		}	
		for (int j=0; j<3; j++) {
			dmat[index-2][3*i+j]=d[j];
		}
		check[0][1]=-c[2]*a[i]->m;
		check[1][0]=c[2]*a[i]->m;
		check[0][2]=c[1]*a[i]->m;
		check[2][0]=-c[1]*a[i]->m;
		check[1][2]=-c[0]*a[i]->m;
		check[2][1]=c[0]*a[i]->m;

		checkvec=MATHEMATICS::mxmply(check,checkvec);

		for(int j=0; j<3; j++) {
			checkout[index][3*i+j]=checkvec[j];
		}

		for(int j=0; j<3; j++) {
			v2[j]=w[j];//+ve
			v2[j+3]=w[j+3];//+ve
		}

		for(int j=0; j<3; j++) {
			s[i]->fp[j]=w[j];//+ve
			s[i]->mp[j]=w[j+3];//+ve
			s[i+1]->fd[j]=-w[j];//-ve
			s[i+1]->md[j]=-w[j+3];//-ve
		}

	}

	return;
}