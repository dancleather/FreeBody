#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"
#include "kinematics.h"
using namespace std;

/* 

These routines generate a unit quaternion representing the input rotation for various descriptions of rotation


1. Axis-angle basis

Calculates unit quaternion given a rotation axis and angle

Arguments:
Input:
theta - rotation angle
v - axis of rotation
Output:
q - unit quaternion

References:
Heard, W. B. (2006).  Rigid Body Mechanics.  Wiley-VCH: Weinheim.

2. Rotation matrix basis

Calculates unit quaternion given a rotation matrix

Arguments:
Input:
m - 3x3 rotation matrix
Output:
q - unit quaternion

Dependencies:
Mathematics: math_trace

References:
Heard, W. B. (2006).  Rigid Body Mechanics.  Wiley-VCH: Weinheim.

3. Cardan angles basis

Calculates rotation matrix given the Cardan rotation series x-y'-z''

Arguments:
Input:
v - vector containing Cardan angles about the axes x, y' and z''
Output:
q - unit quaternion

References:
Diebel, J. (2006).  Representing attitude: Euler angles, unit quaternions, and rotation vectors.
Downloaded from http://ai.stanford.edu/~diebel/attitude/attitude.pdf on 10th August 2006.

*/

void KINEMATICS::kin_qcalc(double theta, Vec_DP v, Vec_DP &q) {

	q[0]=cos(theta/2);

	for (int i=1; i<4; i++) {
		q[i]=sin(theta/2)*v[i-1];
	}

	q=MATHEMATICS::math_vecnorm(q);

	return;
}
void KINEMATICS::kin_qcalc(Mat_DP rotmat, Vec_DP &q) {

	q[0]=(sqrt(MATHEMATICS::math_trace(rotmat)+1))/2;
	q[1]=(rotmat[2][1]-rotmat[1][2])/(4*q[0]);
	q[2]=(rotmat[0][2]-rotmat[2][0])/(4*q[0]);
	q[3]=(rotmat[1][0]-rotmat[0][1])/(4*q[0]);

	return;
}
void KINEMATICS::kin_qcalc(Vec_DP v, Vec_DP &q, string basis) {

	if (basis=="cardan") {

	q[0]=cos(v[0]/2)*cos(v[1]/2)*cos(v[2]/2)+sin(v[0]/2)*sin(v[1]/2)*sin(v[2]/2);
	q[1]=-cos(v[0]/2)*sin(v[1]/2)*sin(v[2]/2)+cos(v[1]/2)*cos(v[2]/2)*sin(v[0]/2);
	q[2]=cos(v[0]/2)*cos(v[2]/2)*sin(v[1]/2)+sin(v[0]/2)*cos(v[1]/2)*sin(v[2]/2);
	q[3]=cos(v[0]/2)*cos(v[1]/2)*sin(v[2]/2)-sin(v[0]/2)*cos(v[2]/2)*sin(v[1]/2);

	}

	else {
	
	q[0]=cos(v[0]/2)*cos(v[1]/2)*cos(v[2]/2)-sin(v[0]/2)*sin(v[1]/2)*sin(v[2]/2);
	q[1]=-cos(v[0]/2)*sin(v[1]/2)*sin(v[2]/2)-cos(v[1]/2)*cos(v[2]/2)*sin(v[0]/2);
	q[2]=-cos(v[0]/2)*cos(v[2]/2)*sin(v[1]/2)+sin(v[0]/2)*cos(v[1]/2)*sin(v[2]/2);
	q[3]=-cos(v[0]/2)*cos(v[1]/2)*sin(v[2]/2)-sin(v[0]/2)*cos(v[2]/2)*sin(v[1]/2);

	}

	return;
}