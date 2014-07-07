#pragma once
#include "stdafx.h"
#include "Segment.h"
#include "mathematics.h"
#include "kinematics.h"

/*

Segment class function

*/
/*

Calculate the angular acceleration of the segment

*/
void Segment::seg_alpha() {

	Vec_DP q1(this->rot_lcs_to_gcs,4), q1dot(this->qdot,4), q1dotdot(this->qdotdot,4), qa(4), qb(4), a(3);

	qa=MATHEMATICS::math_qmply(q1dotdot,MATHEMATICS::math_qcon(q1));
	qb=MATHEMATICS::math_qmply(q1dot,MATHEMATICS::math_qcon(q1dot));
	
	for (int k=0; k<3; k++) {
		this->a[k]=2*qa[k+1]+2*qb[k+1];
	}



}
