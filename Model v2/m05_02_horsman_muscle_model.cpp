#include "stdafx.h"
#include "m05_02_horsman_muscle_model.h"



using namespace std;

/*

Specify the muscle model parameters based on the Klein Horsman muscle model

*/

void m05_02_horsman_muscle_model(Muscle *muscle_model[], Structure *calibrate_pos[], int muscles, 
								 string filename_model, string filename_wrap)
{

	int pnts, segment, wrap_num;
	Vec_DP v0(3), v1(3);

	// Input muscle model parameters in Klein Horsman laboratory frame
	
	io_datainput(filename_model,muscles,muscle_model);
	Mat_DP cylinders=io_datainput(filename_wrap);

	// Rotate parameters to LCS

	for (int i=0; i<muscles; i++) {

		pnts=muscle_model[i]->pnts;

		for (int j=0; j<pnts; j++) {								// This routine iterates for each muscle point

			for (int k=0; k<3; k++) {
				v0[k]=muscle_model[i]->gblpnts[j][k];
			}
			segment=int (muscle_model[i]->gblpnts[j][3]);			// Determine the location of each muscle point
															

			v1=calibrate_pos[segment]->struc_rot_hors_to_lcs(v0);	// Transform the muscle point to the LCS

			for (int k=0; k<3; k++) {
				muscle_model[i]->mslpnts[j][k]=v1[k]*calibrate_pos[segment]->scaling_factors[k];	// Scale the muscle points
				muscle_model[i]->mslpnts[j][k+3]=muscle_model[i]->gblpnts[j][k+3];
			}	
		
			if (muscle_model[i]->mslpnts[j][4] == 1) {				// Determine wrapping cylinders
					
				wrap_num=int (muscle_model[i]->mslpnts[j][5]);
	
				for (int k=0; k<3; k++) {

					v0[k]=cylinders[wrap_num][k];
					v1[k]=cylinders[wrap_num][k+3];
				}

				v0=calibrate_pos[segment]->struc_rot_hors_to_lcs(v0);	// Transform the muscle point to the LCS
				v1=calibrate_pos[segment]->struc_rot_hors_to_lcs(v1);	// Transform the muscle point to the LCS

				for (int k=0; k<3; k++) {

					muscle_model[i]->wrap[0][k]=v0[k]*calibrate_pos[segment]->scaling_factors[k];	// Scale wrapping points
					muscle_model[i]->wrap[1][k]=v1[k];
					
				}
				muscle_model[i]->wrap[2][0]=cylinders[wrap_num][6]*calibrate_pos[segment]->scaling_factors[0]; // Scale radius of wrapping cylinder
				muscle_model[i]->wrap[2][1]=cylinders[wrap_num][7];
				muscle_model[i]->wrap[2][2]=cylinders[wrap_num][8];

				if (wrap_num == 2) {				// Determine wrapping cylinders
	
					for (int k=0; k<3; k++) {

						muscle_model[i]->wrap[0][k]=calibrate_pos[2]->landmarks_local[0][k];
					}

				}
			}
		
		
		}

	}

	return;
}