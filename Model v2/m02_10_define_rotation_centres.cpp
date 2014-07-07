#include "stdafx.h"
#include "m02_10_define_rotation_centres.h"



using namespace std;

/*



*/

void m02_10_define_rotation_centres(Segment **segment_data[], Structure *calibrate_pos[], Mat_DP model_structure, int frames, int segments)

{
	
	int instructions;

	Vec_DP v0(3), v1(3);

	Mat_DP centres=io_datainput("Files/Inputs/model_settings/rotation_centres.txt");  
		
	for (int i=0; i<segments; i++) {

		instructions=int (model_structure[2][i]);

		if (instructions > 0) {

			for (int k=0; k<3; k++) {
					
				v0[k]=centres[i][k];
			}

			v0=calibrate_pos[i]->struc_rot_hors_to_lcs(v0);	

			for (int k=0; k<3; k++) {

				v0[k]=v0[k]*calibrate_pos[i]->scaling_factors[k];
				calibrate_pos[i]->rot_centre[k]=v0[k];
			}
		}
	}
	for (int i=0; i<segments; i++) {

		instructions=int (model_structure[2][i]);

		if (instructions > 0) {

			for (int k=0; k<3; k++) {
					
				v0[k]=calibrate_pos[i]->rot_centre[k];
			}
			
			for (int l=0; l<frames; l++) {

				v1=segment_data[l][i]->seg_pos_point_on_seg(v0);

				for (int k=0; k<3; k++) {
						
					segment_data[l][i]->rot_centre[k]=v1[k];
				}	
			}
		}
	}
	for (int i=0; i<segments; i++) {

		instructions=int (model_structure[3][i]);

		if (instructions > 0) {

			for (int l=0; l<frames; l++) {
				for (int k=0; k<3; k++) {
						
					segment_data[l][i]->dist_contact[k]=segment_data[l][segment_data[l][i]->dist]->rot_centre[k];
				}	
			}
		}
	}
	for (int l=0; l<frames; l++) {
		for (int k=0; k<3; k++) {
						
			segment_data[l][0]->dist_contact[k]=segment_data[l][0]->distal[k];
		}	
	}
	for (int i=0; i<segments; i++) {

		instructions=int (model_structure[4][i]);

		if (instructions > 0) {

			for (int l=0; l<frames; l++) {
				for (int k=0; k<3; k++) {
						
					segment_data[l][i]->vec_rot_centre_to_rf[0][k]=segment_data[l][i]->dist_contact[k]-segment_data[l][i]->rot_centre[k];
				}	
			}
		}
	}


	return;
}