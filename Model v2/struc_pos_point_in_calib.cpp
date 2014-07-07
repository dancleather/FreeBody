#pragma once
#include "stdafx.h"


/*

Segment class function

*/
/*

Calculate the position of a point on a segment in the GCS, given its position in the LCS of the segment.

*/
Vec_DP Structure::struc_pos_point_in_calib(Vec_DP v) {

	Vec_DP v1(3);
	Vec_DP q1(this->rot_lcs_to_gcs,4);
	
	v1=KINEMATICS::kin_qrotate(v,q1);

	for (int i=0; i<3; i++) {
		v1[i]=v1[i]+this->origin[i];
	}
	
	return v1;

}
