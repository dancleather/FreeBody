#include "stdafx.h"
#include "m03_04_calc_linear_quantities.h"




using namespace std;

/*

Calculates the acceleration of the centre of mass of each segment

*/

void m03_04_calc_linear_quantities(Segment **segment_data[], Structure *calibrate_pos[], int frames, int segments)

{

	Vec_DP com(3), accn(3);

	for (int j=0; j<segments; j++) {
		for (int i=0; i<3; i++) {
			com[i]=calibrate_pos[j]->com[i];
		}
		for (int i=2; i<frames-2; i++) {
			accn=segment_data[i][j]->seg_accn_point_on_seg(com);
			for (int k=0; k<3; k++) {
				segment_data[i][j]->acceleration[k]=accn[k];
			}
		}
	}


	return;
}