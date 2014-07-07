#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"
using namespace std;

/* 

Calculate dot product of two vectors

*/

double MATHEMATICS::math_dotprd(Vec_DP a, Vec_DP b) {

	int i;
	int x=a.size(), y=b.size();
	double c=0;

	if(x!=y) {
		cout << "Vector dimensions are invalid for dot product";
	return 0;
	}
	else {
		for(i=0; i<x; i++) {
			c+=a[i]*b[i];
		}
	return c;
	}
}