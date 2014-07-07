#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"
#include "kinematics.h"
using namespace std;

/* 

This routine calculates the new position of a vector after it has been rotated by a unit quaternion

Arguments:
Input:
v0 - vector to be rotated
q - unit quaternion
Output:
v1 - new vector

Dependencies:
Mathematics: math_qcon, math_qmply

References:
Heard, W. B. (2006).  Rigid Body Mechanics.  Wiley-VCH: Weinheim.

*/

void KINEMATICS::kin_qrotate(Vec_DP v0, Vec_DP q, Vec_DP &v1) {

	double t2, t3, t4, t5, t6, t7, t8, t9, t10;

	t2=q[0]*q[1];
	t3=q[0]*q[2];
	t4=q[0]*q[3];
	t5=-q[1]*q[1];
	t6=q[1]*q[2];
	t7=q[1]*q[3];
	t8=-q[2]*q[2];
	t9=q[2]*q[3];
	t10=-q[3]*q[3];

	v1[0]=2*(v0[0]*(t8+t10)+v0[1]*(t6-t4)+v0[2]*(t3+t7))+v0[0];
	v1[1]=2*(v0[0]*(t4+t6)+v0[1]*(t5+t10)+v0[2]*(t9-t2))+v0[1];
	v1[2]=2*(v0[0]*(t7-t3)+v0[1]*(t2+t9)+v0[2]*(t5+t8))+v0[2];

	return;
}
Vec_DP KINEMATICS::kin_qrotate(Vec_DP v0, Vec_DP q) {

	Vec_DP v1(3);

	double t2, t3, t4, t5, t6, t7, t8, t9, t10;
	
	t2=q[0]*q[1];
	t3=q[0]*q[2];
	t4=q[0]*q[3];
	t5=-q[1]*q[1];
	t6=q[1]*q[2];
	t7=q[1]*q[3];
	t8=-q[2]*q[2];
	t9=q[2]*q[3];
	t10=-q[3]*q[3];

	v1[0]=2*(v0[0]*(t8+t10)+v0[1]*(t6-t4)+v0[2]*(t3+t7))+v0[0];
	v1[1]=2*(v0[0]*(t4+t6)+v0[1]*(t5+t10)+v0[2]*(t9-t2))+v0[1];
	v1[2]=2*(v0[0]*(t7-t3)+v0[1]*(t2+t9)+v0[2]*(t5+t8))+v0[2];

	return v1;
}