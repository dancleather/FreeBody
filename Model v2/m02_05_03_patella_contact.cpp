#include "stdafx.h"

#include "m02_05_03_patella_contact.h"




using namespace std;

/*

Calculate position of contact between patella and femur

*/

void m02_05_03_patella_contact(Segment **segment_data[], Structure *calibrate_pos[], int frames)
{
	
	Vec_DP pat_vec(3), pat_origin(3), pat_contact(3), pat_depth(3), q(4);

	for (int i=0; i<frames; i++) {

		for (int j=0; j<3; j++) {
	
			pat_depth[j]=calibrate_pos[4]->landmarks_local[0][j+3]-calibrate_pos[4]->landmarks_local[0][j];
		}

		for (int j=0; j<4; j++) {
	
			q[j]=segment_data[i][4]->rot_lcs_to_gcs[j];
		}

		pat_depth=KINEMATICS::kin_qrotate(pat_depth,q);

		for (int j=0; j<3; j++) {
	
			pat_vec[j]=segment_data[i][4]->other_points[0][j]-segment_data[i][4]->origin[j];	// other points[0][] is the insertion of the quadriceps tendon
			pat_origin[j]=segment_data[i][4]->origin[j];
			pat_contact[j]=pat_origin[j]+segment_data[i][4]->contact_position*pat_vec[j]+pat_depth[j];
		}

		segment_data[i][2]->internal_reaction_forces_dist[2][3]=4;
		segment_data[i][4]->internal_reaction_forces_prox[0][3]=2;

		for (int j=0; j<3; j++) {
	
		segment_data[i][2]->internal_reaction_forces_dist[2][j]=segment_data[i][4]->internal_reaction_forces_prox[0][j]=
			pat_contact[j];
		
		segment_data[i][2]->vec_rot_centre_to_rf[1][j]=pat_contact[j]-segment_data[i][2]->rot_centre[j];
		}

	}

	
	return;
}