#include "stdafx.h"

using namespace std;

/* 

Calculate the conjugate of a quaternion

*/

Vec_DP MATHEMATICS::math_qcon(Vec_DP a) {

	int x=a.size();
	Vec_DP b(4);
	for (int i=0; i<4; i++) {b[i]=0;}

	if(x!=4) {
		cout << "Quaternion dimensions are invalid for calculating its conjugate";
	return b;
	}
	else {
		b[0]=a[0];
		for (int i=1; i<4; i++) {
			b[i]=-a[i];
		}
	return b;
	}
}