#include "stdafx.h"
using namespace std;

/*

Determine whether vectors are in the same direction

Routine outputs -1 if false, 1 if true (vectors in the same direction)

*/

double KINEMATICS::kin_compare_vec(Vec_DP a, Vec_DP b) {
	
	double f=0, g, h;
	Vec_DP c(3);

	a=MATHEMATICS::math_vecnorm(a);
	b=MATHEMATICS::math_vecnorm(b);

	c=MATHEMATICS::math_crossprd(a,b);
	g=MATHEMATICS::math_vecmag(c);

	for (int i=0; i<3; i++) {

		f+=pow((a[i]-b[i]),2);
	}
	f=sqrt(f);
	
	if ((g < 0.01) && (f < 0.01)) {

		h=1;
	}
	else {

		h=-1;
	}


	return h;

}

