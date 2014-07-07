#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"
using namespace std;

/* 

Create a unit quaternion based on a given quaternion by dividing the given quaternion by its norm

*/

Vec_DP MATHEMATICS::math_qnormalise(Vec_DP a) {

	int x=a.size();
	double norm;
	Vec_DP b(4);
	for (int i=0; i<4; i++) {b[i]=0;}

	if(x!=4) {
		cout << "Quaternion dimensions are invalid for making it a unit quaternion";
	return b;
	}
	else {
		norm=MATHEMATICS::math_qnorm(a);
		for (int i=0; i<4; i++) {
			b[i]=a[i]/norm;
		}
	return b;
	}
}