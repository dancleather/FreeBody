#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"
using namespace std;

/*

Calculate the trace of a matrix

*/

double MATHEMATICS::math_trace(Mat_DP m) {

	int x=m.nrows(), y=m.ncols();
	double t=0;

	if(x!=y) {
		cout << "Matrix dimensions are invalid for calculating a trace";
	return 0;
	}
	else {
		for(int i=0; i<x; i++) {
			t+=m[i][i];
		}
	}
	return t;
}