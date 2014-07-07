#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"
using namespace std;

/* 

Calculate cross product of two vectors

*/

Vec_DP MATHEMATICS::math_crossprd(Vec_DP a, Vec_DP b) {

	int x=a.size(), y=b.size();
	double initial=0;
	Vec_DP c(initial, 3);

	if(x!=3||y!=3) {
		cout << "Vector dimensions are invalid for cross product";
	return c;
	}
	else {
		c[0]=a[1]*b[2]-a[2]*b[1];
		c[1]=a[2]*b[0]-a[0]*b[2];
		c[2]=a[0]*b[1]-a[1]*b[0];
		
		return c;
	}
}