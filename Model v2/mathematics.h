#ifndef _MATHEMATICS_H_
#define _MATHEMATICS_H_
#include "nr.h"
using namespace std;

namespace MATHEMATICS {

Vec_DP math_crossprd(Vec_DP a, Vec_DP b);
double math_det2(Mat_DP m);
double math_det3(Mat_DP m);
double math_dotprd(Vec_DP a, Vec_DP b);
Mat_DP identity(int n);
int math_max(Vec_DP a);
Mat_DP mxadd(Mat_DP a, Mat_DP b);
Mat_DP math_mxmply(Mat_DP a, Mat_DP b);
Vec_DP math_mxmply(Mat_DP a, Vec_DP b);
Vec_DP qadd(Vec_DP a, Vec_DP b);
Vec_DP math_qcon(Vec_DP a);
Vec_DP math_qmply(Vec_DP a, Vec_DP b);
double math_qnorm(Vec_DP a);
Vec_DP math_qnormalise(Vec_DP a);
double math_trace(Mat_DP m);
Mat_DP math_transpose(Mat_DP m);
double math_vecmag(Vec_DP a);
Vec_DP math_vecnorm(Vec_DP a);
void math_deriv(Vec_DP &v1, Vec_DP v0, Vec_DP v2, double t0, double t2);
void math_zeromatrix(Mat_DP &m);
Mat_DP math_skew_vec_to_matrix(Vec_DP d);



}
#endif /* _MATHEMATICS_H_ */
