#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"

/*



*/

void MATHEMATICS::math_deriv(Vec_DP &v1, Vec_DP v0, Vec_DP v2, double t0, double t2) {
	
	int n=v1.size();

	for (int i=0; i<n; i++) {

		v1[i]=(v2[i]-v0[i])/(t2-t0);

	}


}