#include "stdafx.h"


/*

Segment class function

*/
/*

Calculate the orientation of a point on a segment in the GCS, given its orientation in the LCS of the segment.

*/
Vec_DP Segment::seg_rot_to_gcs(Vec_DP v) {

	Vec_DP v1(3);
	Vec_DP q1(this->rot_lcs_to_gcs,4);

	v1=KINEMATICS::kin_qrotate(v,q1);
	
	return v1;

}
