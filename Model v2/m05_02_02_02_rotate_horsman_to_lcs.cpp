#include "stdafx.h"
#include "io_outop.h"
#include "mathematics.h"
#include "kinematics.h"
#include "m05_02_02_02_rotate_horsman_to_lcs.h"


/*

To be tidied.

*/

void m05_02_02_02_rotate_horsman_to_lcs(Muscle *muscle_model[], Mat_DP &horsman_adj_factor, int muscles) {

	int pnts, segment;
	Vec_DP q(4), v0(3), v1(3);

	for (int l=0; l<muscles; l++) {

		pnts=muscle_model[l]->pnts;


		for (int i=0; i<pnts; i++) {			// This routine iterates for each muscle point

			for (int j=0; j<3; j++) {
				v0[j]=muscle_model[l]->gblpnts[i][j];
			}
			segment=int (muscle_model[l]->gblpnts[i][3]);	// Determine the location of each muscle point
															// Transform the muscle point to the LCS

			for (int j=0; j<4; j++) {
				q[j]=horsman_adj_factor[segment][j];
			}
				

			KINEMATICS::kin_qrotate(v0,q,v1);	// Rotate the muscle point

			for (int j=0; j<3; j++) {
				muscle_model[l]->mslpnts[i][j]=v1[j];
				muscle_model[l]->mslpnts[i][j+3]=muscle_model[l]->gblpnts[i][j+3];
			}	
		}

	}
	return;
}