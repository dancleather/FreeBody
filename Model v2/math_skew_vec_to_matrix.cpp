#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"
using namespace std;

/* 

Calculate the conjugate of a quaternion

*/

Mat_DP MATHEMATICS::math_skew_vec_to_matrix(Vec_DP d) {

	Mat_DP m1(3,3);

	MATHEMATICS::math_zeromatrix(m1);

	m1[0][1]=-d[2];
	m1[1][0]=d[2];
	m1[0][2]=d[1];
	m1[2][0]=-d[1];
	m1[1][2]=-d[0];
	m1[2][1]=d[0];

	return m1;

}