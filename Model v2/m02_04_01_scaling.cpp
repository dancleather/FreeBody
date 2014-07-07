#include "stdafx.h"
#include "m02_04_01_scaling.h"

#include "io_datainput.h"
#include "mathematics.h"
#include "kinematics.h"


using namespace std;

/*

Calculate the scaling factors for the subject based upon the Klein Horsman muscle model

*/

void m02_04_01_scaling(Structure *calibrate_pos[], int frames, int segments)

{

	// Calculate rotation from LCS of Klein Horsman subject to Klein Horsman laboratory

	int instructions[2];

	Vec_DP va(3), vb(3), vc(3), q(4);
	Vec_DP lengths(3);
	Mat_DP axes(3,3);

	Mat_DP horsman_landmarks=io_datainput("Files/Inputs/model_settings/horsman_landmarks.txt");
	Mat_DP horsman_instructions=io_datainput("Files/Inputs/model_settings/horsman_instructions.txt");

	for (int i=0; i<segments; i++) {

		MATHEMATICS::math_zeromatrix(axes);
		
		for (int j=0; j<2; j++) {
			instructions[j]=(int) horsman_instructions[i][j];
		}
		
		for (int j=0; j<3; j++) {
			for (int k=0; k<3; k++) {
				axes[j][k]=horsman_landmarks[3*i+j][k]-horsman_landmarks[3*i+j][k+3];
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
			calibrate_pos[i]->rot_lcs_to_horsman[j]=q[j];
		}

	}
	for (int j=0; j<4; j++) {	
		calibrate_pos[4]->rot_lcs_to_horsman[j]=calibrate_pos[2]->rot_lcs_to_horsman[j];
	}


	// Calculate scaling factors for muscle geometry data

	double horsman, subject, scale;
	Vec_DP v0(3), v1(3);

		// x and z directions for all segments scaled based on pelvis z dimensions

		for (int k=0; k<3; k++) {

			v0[k]=calibrate_pos[3]->landmarks[2][k]-calibrate_pos[3]->landmarks[2][k+3];
			v1[k]=horsman_landmarks[11][k]-horsman_landmarks[11][k+3];
		}

		subject=MATHEMATICS::math_vecmag(v0);
		horsman=MATHEMATICS::math_vecmag(v1);

		scale=subject/horsman;

		for (int i=0; i<segments; i++) {
			
			calibrate_pos[i]->scaling_factors[0]=scale;
			calibrate_pos[i]->scaling_factors[2]=scale;
		}

		// y direction for all segments (except pelvis and patella) based on length comparison to Klein Horsman model

		for (int i=0; i<3; i++) {
			for (int k=0; k<3; k++) {

				v1[k]=horsman_landmarks[3*i+1][k]-horsman_landmarks[3*i+1][k+3];
			}
			horsman=MATHEMATICS::math_vecmag(v1);
			calibrate_pos[i]->scaling_factors[1]=calibrate_pos[i]->length/horsman;
		}

		// pelvis y direction scaled based on femur length

		calibrate_pos[3]->scaling_factors[1]=calibrate_pos[2]->scaling_factors[1];
		
		// patella scaled on femur dimensions, but with x and y directions reversed (scaling of patella model)

		calibrate_pos[4]->scaling_factors[0]=calibrate_pos[2]->scaling_factors[1];
		calibrate_pos[4]->scaling_factors[1]=calibrate_pos[2]->scaling_factors[0];
		

	return;
}