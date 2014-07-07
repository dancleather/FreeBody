#pragma once
#include "stdafx.h"
#include "Segment.h"
#include "kinematics.h"

/*

Segment class definition

*/
/*

Segment class constructor

*/
void Segment::seg_calculate_qdot(Segment **segment_data[]) {

	Vec_DP q0(segment_data[this->frame-1][this->segnum]->q,4);
	Vec_DP q1(4);
	Vec_DP q2(segment_data[this->frame+1][this->segnum]->q,4);

	double t0=segment_data[this->frame-1][this->segnum]->time;
	double t2=segment_data[this->frame+1][this->segnum]->time;
	double t1=t2-t0;

	KINEMATICS::kin_qdot(q0,q2,t1,q1);

	for (int i=0; i<4; i++) {
		this->qdot[i]=q1[i];
	}

}