#include "stdafx.h"
#include "m02_03_01_calc_seg_pos_vectors.h"



using namespace std;

/*

Calculate the position of the COM and the distal end of each segment in the GCS

*/

void m02_03_01_calc_seg_pos_vectors(Segment **segment_data[], Structure *calibrate_pos[], int frames, int segments)

{

	Vec_DP com(3), distal(3), com_seg(3), distal_seg(3);

	for (int j=0; j<segments; j++) {
		for (int i=0; i<3; i++) {
			com[i]=calibrate_pos[j]->com[i];
			distal[i]=calibrate_pos[j]->distal[i];
		}
		for (int i=0; i<frames; i++) {

			com_seg=segment_data[i][j]->seg_pos_point_on_seg(com);
			distal_seg=segment_data[i][j]->seg_pos_point_on_seg(distal);
			
			for (int k=0; k<3; k++) {
				
				segment_data[i][j]->com[k]=com_seg[k];
				segment_data[i][j]->distal[k]=distal_seg[k];	
			}
		}
	}


	return;
}