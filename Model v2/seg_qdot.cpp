#pragma once
#include "stdafx.h"
#include "Segment.h"
#include "mathematics.h"
#include "kinematics.h"
#include "io_outop.h"
/*

Segment class function

*/
/*

Differentiate the quaternion representing the orientation of the segment (q) with respect to time

*/
void Segment::seg_qdot(Segment **segment_data[]) {

	double t0=segment_data[(this->frame)-1][this->segnum]->time, t2=segment_data[(this->frame)+1][this->segnum]->time;
	Vec_DP q0(segment_data[(this->frame)-1][this->segnum]->rot_lcs_to_gcs,4), q2(segment_data[(this->frame)+1][this->segnum]->rot_lcs_to_gcs,4), q1(4);

	MATHEMATICS::math_deriv(q1,q0,q2,t0,t2);

	for (int i=0; i<4; i++) {
		this->qdot[i]=q1[i];
	}

}
