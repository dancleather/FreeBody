#include "stdafx.h"

using namespace std;

/* 

Multiply two quaternions

*/

Vec_DP MATHEMATICS::math_qmply(Vec_DP a, Vec_DP b) {

	int x=a.size(), y=b.size();
	Vec_DP c(4);
	for (int i=0; i<4; i++) {c[i]=0;}

	if(x!=4||y!=4) {
		cout << "Quaternion dimensions are invalid for multiplication";
	return c;
	}
	else {
		c[0]=a[0]*b[0]-a[1]*b[1]-a[2]*b[2]-a[3]*b[3];
		c[1]=a[0]*b[1]+a[1]*b[0]+a[2]*b[3]-a[3]*b[2];
		c[2]=a[0]*b[2]+a[2]*b[0]+a[3]*b[1]-a[1]*b[3];
		c[3]=a[0]*b[3]+a[3]*b[0]+a[1]*b[2]-a[2]*b[1];
	return c;
	}
}