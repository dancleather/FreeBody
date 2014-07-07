#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"
using namespace std;

/*

Calculates the transpose of a matrix

*/

Mat_DP MATHEMATICS::math_transpose(Mat_DP m) {

	int x=m.nrows(), y=m.ncols();

	Mat_DP transm(y,x);

	for(int i=0; i<y; i++) {
			for(int j=0; j<x; j++) {
				transm[i][j]=m[j][i];
			}
		}

	return transm;
}