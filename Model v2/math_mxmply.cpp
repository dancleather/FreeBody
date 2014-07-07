#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"
using namespace std;

/*

Matrix multiplication

*/

Mat_DP MATHEMATICS::math_mxmply(Mat_DP a, Mat_DP b) {
	
	int x=a.nrows(), y=b.ncols();
	double initial=0;
	Mat_DP c(initial, x, y);	

	if(x!=y) {
		cout << "Matrix dimensions are invalid for multiplication";
	return c;
	}
	else {
		int i, j, k;
		for(i=0; i<x; i++) {
			for(j=0; j<y; j++) {
				for(k=0; k<x; k++) {
				c[i][j]+=a[i][k]*b[k][j];
				}
			}
		}
	return c;
	}
}

Vec_DP MATHEMATICS::math_mxmply(Mat_DP a, Vec_DP b) {
	
	int x=a.nrows(), y=b.size();
	double initial=0;
	Vec_DP c(initial, y);	

	if(x!=y) {
		cout << "Matrix dimensions are invalid for multiplication";
	return c;
	}
	else {
		int i, j;
		for(i=0; i<x; i++) {
			for(j=0; j<y; j++) {
				c[i]+=a[i][j]*b[j];
				}
		}
	return c;
	}
}