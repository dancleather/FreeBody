#include "stdafx.h"
#include "kinematics.h"
#include "outop.h"
#include "io_datainput.h"
#include "lengthcalc.h"


/*

Calculate lengths of all segments

*/

void lengthcalc(Mat_DP origins, Segment *segchain[]) {

	Vec_DP k0(3), k1(3), k2(3), k3(3);

	for (int i=0; i<3; i++) {
		k0[i]=origins[0][i];
		k1[i]=origins[1][i];
		k2[i]=origins[2][i];
		k3[i]=origins[3][i];
	}

	segchain[0]->length=KINEMATICS::distpnts(k0,k1);
	segchain[1]->length=KINEMATICS::distpnts(k1,k2);
	segchain[2]->length=KINEMATICS::distpnts(k2,k3);

	return;
}