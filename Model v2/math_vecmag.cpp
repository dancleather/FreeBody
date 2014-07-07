#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"

/*

Calculates the magnitude of a vector

*/

double MATHEMATICS::math_vecmag(Vec_DP a) {
	
	double c=0;
	int x=a.size();
	
	for(int i=0; i<x; i++) {
		c+=a[i]*a[i];		
	}
	
	c=sqrt(c);

	return c;
}

