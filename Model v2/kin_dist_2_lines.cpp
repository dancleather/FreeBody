#include "stdafx.h"
using namespace std;

/*

Calculates distance between 2 lines

Arguments:
Input:
a - a point on the first line
b - vector along the first line
c - a point on the second line
d - vector along the second line

Output:
Shortest (perpendicular) distance between the 2 lines

*/

double KINEMATICS::kin_dist_2_lines(Vec_DP a, Vec_DP b, Vec_DP c, Vec_DP d) {
	
	double g;
	Vec_DP e(3), f(3);
	
	b=MATHEMATICS::math_vecnorm(b);
	d=MATHEMATICS::math_vecnorm(d);
		
	for (int i=0; i<3; i++) {
		
		e[i]=c[i]-a[i];
	}

	f=MATHEMATICS::math_crossprd(d,b);
	
	g=MATHEMATICS::math_dotprd(e,f)/MATHEMATICS::math_vecmag(f);

	if (g < 0) {
		g=-1*g;
	}

	
	return g;

}

