#pragma once
#include "stdafx.h"
#include "Segment.h"
#include "mathematics.h"
#include "kinematics.h"

/*

Segment class function

*/
/*

Calculates the linear acceleration of a given point on a segment

*/
Vec_DP Segment::seg_accn_point_on_seg(Vec_DP v) {

	Vec_DP vcalc(4), v1(3);
	Vec_DP q1(this->rot_lcs_to_gcs,4), q1dot(this->qdot,4), q1dotdot(this->qdotdot,4), qa(4), qb(4), qc(4);
	Vec_DP v1dotdot(this->origindotdot,3);

	for (int i=0; i<3; i++) {
		vcalc[i+1]=v[i];
	}
	vcalc[0]=0;

	qa=MATHEMATICS::math_qmply(q1dotdot,MATHEMATICS::math_qmply(vcalc,MATHEMATICS::math_qcon(q1)));
	qb=MATHEMATICS::math_qmply(q1dot,MATHEMATICS::math_qmply(vcalc,MATHEMATICS::math_qcon(q1dot)));
	qc=MATHEMATICS::math_qmply(q1,MATHEMATICS::math_qmply(vcalc,MATHEMATICS::math_qcon(q1dotdot)));

	for (int k=0; k<3; k++) {
		v1[k]=v1dotdot[k]+qa[k+1]+2*qb[k+1]+qc[k+1];
	}

	return v1;

}
