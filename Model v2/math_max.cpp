#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"
using namespace std;

/*

Find position of maximum value from a list of numbers in vector form

*/

int MATHEMATICS::math_max(Vec_DP a) {
	
	int x=0, n=a.size();	
	double y=a[0];

	for (int i=1; i<n; i++) {
		if (a[i]>y) {
			y=a[i];
			x=i;
		}
	}

	return x;
}