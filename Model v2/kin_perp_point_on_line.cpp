#include "stdafx.h"
using namespace std;

/*





*/

Vec_DP KINEMATICS::kin_perp_point_on_line(Vec_DP a, Vec_DP b, Vec_DP c) {
	
	double t;
	Vec_DP d(3);

	for (int i=0; i<3; i++) {
		d[i]=c[i]-a[i];
	}

	t=-MATHEMATICS::math_dotprd(d,b)/pow(MATHEMATICS::math_vecmag(b),2);

	for (int i=0; i<3; i++) {
		d[i]=c[i]+t*b[i];
	}


	return d;

}

