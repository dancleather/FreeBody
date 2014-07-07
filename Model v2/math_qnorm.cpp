#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"
using namespace std;

/* 

Calculate the norm of a quaternion

*/

double MATHEMATICS::math_qnorm(Vec_DP a) {

	int x=a.size();
	double b=0;

	if(x!=4) {
		cout << "Quaternion dimensions are invalid for calculating its norm";
	return 0;
	}
	else {
		for (int i=0; i<4; i++) {
			b+=a[i]*a[i];
		}
		b=sqrt(b);
	return b;
	}
}