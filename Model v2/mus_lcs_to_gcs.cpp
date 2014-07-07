#include "stdafx.h"


/*

Calculates global position of muscle points

The position of wrapping points that vary with joint angle is calculated in this routine

*/
void Muscle::mus_lcs_to_gcs(Segment **segment_data[], Structure *calibrate_pos[]) {

	int points=this->pnts, segment, frame=this->frame, new_i=0;
	Vec_DP v0(3), v1(3), v2(3);

	for (int i=0; i<points; i++) {												// This routine iterates for each muscle point

		for (int j=0; j<3; j++) {
			v0[j]=this->mslpnts[i][j];
		}
		segment=int (this->mslpnts[i][3]);										// Determine the location of each muscle point (what segment)
					
		v1=segment_data[frame][segment]->seg_pos_point_on_seg(v0); 				// Transform the muscle point to the GCS
	
		for (int j=0; j<3; j++) {												
			this->gblpnts[new_i][j]=v1[j];	
		}	
		this->gblpnts[new_i][3]=segment;
	
		if ((i > 0) && (this->mslpnts[i-1][4] == 1)) {
		
			this->mus_wrapping(segment_data,calibrate_pos,new_i);

			this->pnts+=2;

			new_i+=2;

		}

		new_i+=1;
	}

	return;
}
