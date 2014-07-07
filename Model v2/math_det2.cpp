#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"

/*

Calculates the determinant of a 2x2 matrix

*/

double MATHEMATICS::math_det2(Mat_DP m) {
	
	int x=m.nrows(), y=m.ncols();
	double a=0;

	if (x!=2||y!=2) {
		cout << "Input matrix is not 2x2";
	}
	else {
		a=m[0][0]*m[1][1]-m[0][1]*m[1][0];
	}

	return a;
}