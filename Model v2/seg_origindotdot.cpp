#pragma once
#include "stdafx.h"
#include "Segment.h"
#include "mathematics.h"
#include "kinematics.h"

/*

Segment class definition

*/
/*

Segment class constructor

*/
void Segment::seg_origindotdot(Segment **segment_data[]) {

	double t0=segment_data[(this->frame)-1][this->segnum]->time, t2=segment_data[(this->frame)+1][this->segnum]->time;
	Vec_DP v0(segment_data[(this->frame)-1][this->segnum]->origindot,3), v2(segment_data[(this->frame)+1][this->segnum]->origindot,3), v1(3);

	MATHEMATICS::math_deriv(v1,v0,v2,t0,t2);

	for (int i=0; i<3; i++) {
		this->origindotdot[i]=v1[i];
	}

}
