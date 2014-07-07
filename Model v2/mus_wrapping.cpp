#include "stdafx.h"

#include "m05_04_wrap_cylinder.h"

using namespace std;

/*



*/

void Muscle::mus_wrapping(Segment **segment_data[], Structure *calibrate_pos[], int i) {

	int segment;
	double radius=this->wrap[2][0], direction=this->wrap[2][1], wrap_check1, wrap_check2, final_segment, result;
	Vec_DP vc(3), pc(3), o(3), ins(3), eo(3), ei(3);

	segment=int (this->wrap[2][2]);										// Determine the location of each muscle point (what segment)

	for (int j=0; j<3; j++) {

		vc[j]=this->wrap[1][j];
		pc[j]=this->wrap[0][j];
		o[j]=this->gblpnts[i-1][j];
		ins[j]=this->gblpnts[i][j];
	}
	pc=segment_data[this->frame][segment]->seg_pos_point_on_seg(pc); 				// Transform the muscle point to the GCS
	vc=segment_data[this->frame][segment]->seg_rot_to_gcs(vc);

	wrap_check1=KINEMATICS::kin_dist_point_line(o,vc,pc);
	wrap_check2=KINEMATICS::kin_dist_point_line(ins,vc,pc);

	if ((wrap_check1 < radius) || (wrap_check2 < radius)) {
	
			cout << "wrapping failed for " << this->name << endl;

			for (int j=0; j<3; j++) {

				ei[j]=this->gblpnts[i-1][j];
				eo[j]=this->gblpnts[i-1][j];
			}
			final_segment=this->gblpnts[i-1][3];
	}
	
	else {
		m05_04_wrap_cylinder(vc,pc,o,ins,radius,eo,ei,direction,result);
		if (result == 1) {final_segment=segment;}
		else {final_segment=this->gblpnts[i-1][3];}
	}

	for (int j=0; j<3; j++) {

		this->gblpnts[i][j]=ei[j];
		this->gblpnts[i+1][j]=eo[j];
		this->gblpnts[i+2][j]=ins[j];
	}
	this->gblpnts[i+2][3]=this->gblpnts[i][3];
	this->gblpnts[i][3]=this->gblpnts[i+1][3]=final_segment;

	return;
}

