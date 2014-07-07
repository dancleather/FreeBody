#include "stdafx.h"
#include "mathematics.h"

/*

Calculates the determinant of a 3x3 matrix

*/

double MATHEMATICS::math_det3(Mat_DP m) {
	
	int x=m.nrows(), y=m.ncols();
	double a=0;
	Mat_DP b0(2,2), b1(2,2), b2(2,2);

	if (x!=3||y!=3) {
		cout << "Input matrix is not 3x3";
	}
	else {
		b0[0][0]=m[1][1], b0[0][1]=m[1][2], b0[1][0]=m[2][1], b0[1][1]=m[2][2];
		b1[0][0]=m[1][0], b1[0][1]=m[1][2], b1[1][0]=m[2][0], b1[1][1]=m[2][2];
		b2[0][0]=m[1][0], b2[0][1]=m[1][1], b2[1][0]=m[2][0], b2[1][1]=m[2][1];
		a=m[0][0]*MATHEMATICS::math_det2(b0)-m[0][1]*MATHEMATICS::math_det2(b1)+m[0][2]*MATHEMATICS::math_det2(b2);
	}

	return a;
}