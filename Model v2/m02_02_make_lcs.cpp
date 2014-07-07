#include "stdafx.h"
#include "m02_02_make_lcs.h"


#include "io_datainput.h"

using namespace std;

/*

Create the coordinate system for each segment by specifying the transformation from the LCS to the calibration position

*/

void m02_02_make_lcs(Structure *calibrate_pos[], int segments)
{
	int instructions[2];

	Vec_DP va(3), vb(3), vc(3), q(4);
	Mat_DP axes(3,3);
	
	Mat_DP make_segments=io_datainput("Files/Inputs/model_settings/make_segments.txt");


	for (int i=0; i<segments; i++) {

		MATHEMATICS::math_zeromatrix(axes);
		
		for (int j=0; j<2; j++) {
			instructions[j]=(int) make_segments[i][j];
		}


		for (int j=0; j<3; j++) {
			for (int k=0; k<3; k++) {
				axes[j][k]=calibrate_pos[i]->landmarks[j][k]-calibrate_pos[i]->landmarks[j][k+3];
			}
		}
		for (int j=0; j<3; j++) {
			va[j]=axes[(instructions[0]+1)%3][j];
			vb[j]=axes[(instructions[0]+2)%3][j];
		}

		va=MATHEMATICS::math_vecnorm(va);
		vb=MATHEMATICS::math_vecnorm(vb);
		vc=MATHEMATICS::math_crossprd(va,vb);
		vc=MATHEMATICS::math_vecnorm(vc);
		for (int j=0; j<3; j++) {
			axes[instructions[0]][j]=vc[j];
			axes[(instructions[0]+1)%3][j]=va[j];
			axes[(instructions[0]+2)%3][j]=vb[j];
		}
		for (int j=0; j<3; j++) {
			va[j]=axes[(instructions[1]+1)%3][j];
			vb[j]=axes[(instructions[1]+2)%3][j];
		}
		vc=MATHEMATICS::math_crossprd(va,vb);
		vc=MATHEMATICS::math_vecnorm(vc);
		for (int j=0; j<3; j++) {
			axes[instructions[1]][j]=vc[j];
		}
		axes=MATHEMATICS::math_transpose(axes);

		KINEMATICS::kin_qcalc(axes,q);

		for (int j=0; j<4; j++) {	
			calibrate_pos[i]->rot_lcs_to_gcs[j]=q[j];
		}

	}


	return;
}