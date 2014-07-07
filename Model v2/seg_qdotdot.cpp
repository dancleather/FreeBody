#pragma once
#include "stdafx.h"
#include "Segment.h"
#include "mathematics.h"
#include "kinematics.h"

/*

Segment class function

*/
/*

Differentiate qdot with respect to time

*/
void Segment::seg_qdotdot(Segment **segment_data[]) {

	double t0=segment_data[(this->frame)-1][this->segnum]->time, t2=segment_data[(this->frame)+1][this->segnum]->time;
	Vec_DP q0(segment_data[(this->frame)-1][this->segnum]->qdot,4), q2(segment_data[(this->frame)+1][this->segnum]->qdot,4), q1(4);

	MATHEMATICS::math_deriv(q1,q0,q2,t0,t2);

	for (int i=0; i<4; i++) {
		this->qdotdot[i]=q1[i];
	}

}
