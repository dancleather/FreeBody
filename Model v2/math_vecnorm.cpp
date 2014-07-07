#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"

/*

Calculates the normalized vector

*/

Vec_DP MATHEMATICS::math_vecnorm(Vec_DP a) {
	
	double mag;
	
	int x=a.size();

	Vec_DP b(x); 
	
	mag=MATHEMATICS::math_vecmag(a);

	for(int i=0; i<x; i++) {
		b[i]=a[i]/mag;
	}

	return b;
}