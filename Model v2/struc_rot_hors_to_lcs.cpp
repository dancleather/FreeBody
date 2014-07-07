#pragma once
#include "stdafx.h"
#include "Structure.h"
#include "mathematics.h"
#include "kinematics.h"

/*

Structure class function

*/
/*

Calculate the position of muscle point in the LCS, given its location in the Klein Horsman GCS.

*/
Vec_DP Structure::struc_rot_hors_to_lcs(Vec_DP v) {

	Vec_DP v1(3);
	Vec_DP q1(this->rot_lcs_to_horsman,4);

	q1=MATHEMATICS::math_qcon(q1);

	v1=KINEMATICS::kin_qrotate(v,q1);
	
	return v1;

}
