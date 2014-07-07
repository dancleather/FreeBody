#include "stdafx.h"
using namespace std;

/*

Calculate the line segment PaPb that is the shortest route between
two lines P1P2 and P3P4. Calculate also the values of mua and mub where
      Pa = P1 + mua (P2 - P1)
      Pb = P3 + mub (P4 - P3)


Adapted from the code of Paul Bourke, downloaded on 21/02/14

http://paulbourke.net/geometry/pointlineplane/lineline.c


*/
void KINEMATICS::kin_line_line_intersect(Vec_DP p1, Vec_DP p2, Vec_DP p3, Vec_DP p4, Vec_DP &pa, Vec_DP &pb, double &mua, double &mub)
 {
	
	Vec_DP p13(3), p43(3), p21(3);
	double d1343,d4321,d1321,d4343,d2121;
	double numer,denom;

	p13[0] = p1[0] - p3[0];
	p13[1] = p1[1] - p3[1];
	p13[2] = p1[2] - p3[2];
	p43[0] = p4[0] - p3[0];
	p43[1] = p4[1] - p3[1];
	p43[2] = p4[2] - p3[2];
	p21[0] = p2[0] - p1[0];
	p21[1] = p2[1] - p1[1];
	p21[2] = p2[2] - p1[2];

	d1343 = p13[0] * p43[0] + p13[1] * p43[1] + p13[2] * p43[2];
	d4321 = p43[0] * p21[0] + p43[1] * p21[1] + p43[2] * p21[2];
	d1321 = p13[0] * p21[0] + p13[1] * p21[1] + p13[2] * p21[2];
	d4343 = p43[0] * p43[0] + p43[1] * p43[1] + p43[2] * p43[2];
	d2121 = p21[0] * p21[0] + p21[1] * p21[1] + p21[2] * p21[2];

	denom = d2121 * d4343 - d4321 * d4321;

	numer = d1343 * d4321 - d1321 * d4343;

	mua = numer / denom;
	mub = (d1343 + d4321 * (mua)) / d4343;

	pa[0] = p1[0] + mua * p21[0];
	pa[1] = p1[1] + mua * p21[1];
	pa[2] = p1[2] + mua * p21[2];
	pb[0] = p3[0] + mub * p43[0];
	pb[1] = p3[1] + mub * p43[1];
	pb[2] = p3[2] + mub * p43[2];

   return;
}

