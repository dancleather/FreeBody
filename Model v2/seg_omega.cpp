#pragma once
#include "stdafx.h"
#include "Segment.h"
#include "mathematics.h"
#include "kinematics.h"

/*

Segment class function

*/
/*

Calculate the angular velocity of the segment

*/
void Segment::seg_omega() {

	Vec_DP q1(this->rot_lcs_to_gcs,4), q1dot(this->qdot,4), w(3);

	w=MATHEMATICS::math_qmply(q1dot,MATHEMATICS::math_qcon(q1));
	for (int k=0; k<3; k++) {
		this->w[k]=2*w[k+1];
	}


}
