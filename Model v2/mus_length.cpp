#include "stdafx.h"


/*

Calculates force upper bound of each muscle element

*/
void Muscle::mus_length() {

	int pnts=int (this->pnts);
	double length=0;
	Vec_DP v0(3), v1(3), v2(3);

	for (int i=0; i<pnts-1; i++) {

		for (int j=0; j<3; j++) {
			v0[j]=this->gblpnts[i][j];
			v1[j]=this->gblpnts[i+1][j];
			v2[j]=v1[j]-v0[j];
		}

		length+=MATHEMATICS::math_vecmag(v2);
	}

	this->length=length;

	return;
}
