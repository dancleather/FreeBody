#ifndef _KINEMATICS_H_
#define _KINEMATICS_H_
#include "nr.h"
using namespace std;

namespace KINEMATICS {

void kin_cardan(Vec_DP &q, Vec_DP &euler, string sequence);
double kin_compare_vec(Vec_DP a, Vec_DP b);
void kin_crossdisp(Mat_DP p0, Mat_DP p1, Vec_DP &xbar0, Vec_DP &xbar1, Mat_DP &cross);
double kin_distpnts(Vec_DP a, Vec_DP b);
double kin_dist_point_line(Vec_DP a, Vec_DP b, Vec_DP c);
double kin_dist_2_lines(Vec_DP a, Vec_DP b, Vec_DP c, Vec_DP d);
void kin_line_line_intersect(Vec_DP p1, Vec_DP p2, Vec_DP p3, Vec_DP p4, Vec_DP &pa, Vec_DP &pb, double &mua, double &mub);
void kin_markcalc(Mat_DP p0, Mat_DP p1, Vec_DP &q, Vec_DP &t);
void kin_markcalc(Mat_DP p0, Mat_DP p1, Mat_DP &m, Vec_DP &t);
Vec_DP kin_perp_point_on_line(Vec_DP a, Vec_DP b, Vec_DP c);
void kin_qcalc(double theta, Vec_DP v, Vec_DP &q);
void kin_qcalc(Mat_DP rotmat, Vec_DP &q);
void kin_qcalc(Vec_DP v, Vec_DP &q, string basis);
void kin_qdot(Vec_DP q0, Vec_DP q2, double t, Vec_DP &q1);
void kin_qrotate(Vec_DP v0, Vec_DP q, Vec_DP &v1);
Vec_DP kin_qrotate(Vec_DP v0, Vec_DP q);
void kin_rmatcalc(double theta, Vec_DP v, Mat_DP &m);
void kin_rmatcalc(Vec_DP q, Mat_DP &m);


}
#endif /* _KINEMATICS_H_ */
