#include "stdafx.h"
#include "m05_01_01_initialize_all_muscles.h"




using namespace std;

/*



*/

void m05_01_01_initialize_all_muscles(Muscle **muscle_data[], Muscle *muscle_model[], int frames, double freq, int muscles)
{

	for (int i=0; i<frames; i++) {
		for (int j=0; j<muscles; j++) {
			muscle_data[i][j]->frame=i;
			muscle_data[i][j]->time=(i/freq);
			muscle_data[i][j]->name=muscle_model[j]->name;
			muscle_data[i][j]->pnts=muscle_model[j]->pnts;
			muscle_data[i][j]->segments_spanned=muscle_model[j]->segments_spanned;
			for (int k=0; k<muscle_model[j]->pnts; k++) {
				for (int l=0; l<6; l++) {
					muscle_data[i][j]->mslpnts[k][l]=muscle_model[j]->mslpnts[k][l];
				}
			}
			for (int k=0; k<3; k++) {
				for (int l=0; l<3; l++) {
					muscle_data[i][j]->wrap[k][l]=muscle_model[j]->wrap[k][l];
				}
			}
			for (int k=0; k<8; k++) {
				for (int l=0; l<3; l++) {
					muscle_data[i][j]->opt[k][l]=0;
					muscle_data[i][j]->opt_2[k][l]=0;
					muscle_data[i][j]->opt_3[k][l]=0;
				}
				muscle_data[i][j]->opt[k][3]=-1;
				muscle_data[i][j]->opt_2[k][3]=-1;
				muscle_data[i][j]->opt_3[k][3]=-1;
			}
			muscle_data[i][j]->pcsa=muscle_model[j]->pcsa;		
			muscle_data[i][j]->pcsa_multiple=muscle_model[j]->pcsa_multiple;		
			muscle_data[i][j]->max_tension=muscle_model[j]->max_tension;		
		}
	}

	
	return;
}