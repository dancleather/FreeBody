#include "stdafx.h"
#include "m02_03_horsman_landmarks.h"



using namespace std;

/*

Specify the proximal/distal ends of each segment

*/

void m02_03_horsman_landmarks(Structure *calibrate_pos[], int segments, double marker_width) {

	Vec_DP v0(3), v1(3), v2(3), midasis(3);


	calibrate_pos[0]->landmarks[1][4]-=marker_width/2;		// Adjust landmark for width of marker

	// Centres of rotation of joints used to define ends of intermediate segments

	for (int i=0; i<segments-3; i++) {
		for (int j=0; j<3; j++) {
			calibrate_pos[i]->landmarks[1][j]=(calibrate_pos[i]->landmarks[2][j]+calibrate_pos[i]->landmarks[2][j+3])/2;
			calibrate_pos[i+1]->landmarks[1][j+3]=calibrate_pos[i]->landmarks[1][j];
		}
	}


	// Position of hip joint centre

		// Create LCS defined by pelvis markers

		// Calculate hip centre in Horsman pelvis frame

		double horsmanhip[3][3]={0.1509,0.002,0.0868,0,0,0,0,0,0.2624};		// axes of Klein Horsman pelvis (x, y, z)
		double hipcentre[3]={-0.0376,-0.0878,0.0897};						// vector from midpoint of ASISs to hip centre (global)

		Vec_DP x(3), y(3), z(3);
		Vec_DP hipc(hipcentre,3);

		Mat_DP rot(3,3);		// rot is the rotation from the global frame to the local pelvis frame

		for (int k=0; k<3; k++) {
			x[k]=horsmanhip[0][k];
			z[k]=horsmanhip[2][k];
		}

		double scalhors=MATHEMATICS::math_vecmag(z);

		x=MATHEMATICS::math_vecnorm(x);
		z=MATHEMATICS::math_vecnorm(z);

		y=MATHEMATICS::math_crossprd(z,x);
		x=MATHEMATICS::math_crossprd(y,z);

		x=MATHEMATICS::math_vecnorm(x);
		y=MATHEMATICS::math_vecnorm(y);
		z=MATHEMATICS::math_vecnorm(z);

		for (int k=0; k<3; k++) {
			rot[0][k]=x[k];	
			rot[1][k]=y[k];
			rot[2][k]=z[k];
		}

		hipc=MATHEMATICS::math_mxmply(rot,hipc);

		// Calculate position of hip centre in calibration frame
	
		for (int k=0; k<3; k++) {
			x[k]=calibrate_pos[segments-2]->landmarks[0][k]-calibrate_pos[segments-2]->landmarks[0][k+3];
			z[k]=calibrate_pos[segments-2]->landmarks[2][k]-calibrate_pos[segments-2]->landmarks[2][k+3];
			midasis[k]=(calibrate_pos[segments-2]->landmarks[2][k]+calibrate_pos[segments-2]->landmarks[2][k+3])/2;
		}
		midasis[0]-=marker_width/2;		// Adjust landmark for width of marker

		double scalsub=MATHEMATICS::math_vecmag(z);

		x=MATHEMATICS::math_vecnorm(x);
		z=MATHEMATICS::math_vecnorm(z);

		y=MATHEMATICS::math_crossprd(z,x);
		x=MATHEMATICS::math_crossprd(y,z);

		x=MATHEMATICS::math_vecnorm(x);
		y=MATHEMATICS::math_vecnorm(y);
		z=MATHEMATICS::math_vecnorm(z);
			
		for (int k=0; k<3; k++) {
			rot[k][0]=x[k];
			rot[k][1]=y[k];
			rot[k][2]=z[k];
		}

		double scalhip=scalsub/scalhors;
		double scalhipy=((calibrate_pos[segments-2]->landmarks[0][1]-calibrate_pos[segments-3]->landmarks[2][1])/(0.0878+0.3996));

		hipc[0]=scalhip*hipc[0];
		hipc[1]=scalhipy*hipc[1];
		hipc[2]=scalhip*hipc[2];

		hipc=MATHEMATICS::math_mxmply(rot,hipc);

		for (int j=0; j<3; j++) {
			calibrate_pos[segments-3]->landmarks[1][j]=hipc[j]+midasis[j];
		}


		// Define origins of segments

		for (int i=0; i<segments-2; i++) {
			for (int j=0; j<3; j++) {
				calibrate_pos[i]->origin[j]=calibrate_pos[i]->landmarks[1][j];
			}
		}
		for (int i=0; i<3; i++) {
			calibrate_pos[3]->origin[i]=midasis[i];
		}

		// Calculate segment lengths, positions of COM, and distal points

		for (int i=0; i<segments-2; i++) {
			for (int j=0; j<3; j++) {
				v0[j]=calibrate_pos[i]->landmarks[1][j]-calibrate_pos[i]->landmarks[1][j+3];
			}
			calibrate_pos[i]->length=MATHEMATICS::math_vecmag(v0);

			calibrate_pos[i]->com[1]=-calibrate_pos[i]->length*calibrate_pos[i]->com[1];
			calibrate_pos[i]->distal[1]=-calibrate_pos[i]->length;

			calibrate_pos[i]->com[0]=calibrate_pos[i]->com[2]=0;
			calibrate_pos[i]->distal[0]=calibrate_pos[i]->distal[2]=0;
		}


	return;
}