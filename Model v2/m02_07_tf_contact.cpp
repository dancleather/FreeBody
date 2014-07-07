#include "stdafx.h"
#include "m02_07_tf_contact.h"



using namespace std;

/*



*/

void m02_07_tf_contact(Segment **segment_data[], Structure *calibrate_pos[], int frames)

{

	Vec_DP v0(3), v1(3), v2(3), v3(3);
	
	Mat_DP tf_contact=io_datainput("Files/Inputs/model_settings/tf_contact.txt");	

	for (int i=0; i<3; i++) {

		v0[i]=tf_contact[0][i];
		v1[i]=tf_contact[1][i];
	}

	v0=calibrate_pos[1]->struc_rot_hors_to_lcs(v0);
	v1=calibrate_pos[1]->struc_rot_hors_to_lcs(v1);

	for (int i=0; i<3; i++) {

		v0[i]=v0[i]*calibrate_pos[1]->scaling_factors[i];
		v1[i]=v1[i]*calibrate_pos[1]->scaling_factors[i];
	}

	for (int i=0; i<frames; i++) {

		v2=segment_data[i][1]->seg_pos_point_on_seg(v0);
		v3=segment_data[i][1]->seg_pos_point_on_seg(v1);

		for (int j=0; j<3; j++) {
			
			segment_data[i][1]->vec_rot_centre_to_rf[2][j]=v2[j]-segment_data[i][1]->rot_centre[j];
			segment_data[i][1]->vec_rot_centre_to_rf[3][j]=v3[j]-segment_data[i][1]->rot_centre[j];
			segment_data[i][2]->vec_rot_centre_to_rf[2][j]=v2[j]-segment_data[i][2]->rot_centre[j];
			segment_data[i][2]->vec_rot_centre_to_rf[3][j]=v3[j]-segment_data[i][2]->rot_centre[j];
		}
	}
	return;
}