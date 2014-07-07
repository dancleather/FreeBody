#include "stdafx.h"
using namespace std;

/*

Calculates distance between a point and a line

Arguments:
Input:
a - the point
b - vector along the line
c - a point on the line

Output:
Shortest (perpendicular) distance between the point and the line

*/

double KINEMATICS::kin_dist_point_line(Vec_DP a, Vec_DP b, Vec_DP c) {
	
	double e;
	Vec_DP d(3);
		
	for (int i=0; i<3; i++) {
		
		d[i]=c[i]-a[i];
	}

	d=MATHEMATICS::math_crossprd(d,b);

	e=MATHEMATICS::math_vecmag(d)/MATHEMATICS::math_vecmag(b);
	
	return e;

}

