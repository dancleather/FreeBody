#include "stdafx.h"
#include "nr.h"
#include "kinematics.h"
using namespace std;

/* 

These routines generate a rotation matrix for various parameterisations of rotation

1. Axis-angle basis

Calculates rotation matrix given a rotation axis and angle

Arguments:
Input:
theta - rotation angle
v - axis of rotation
Output:
m - 3x3 rotation matrix

References:
Heard, W. B. (2006).  Rigid Body Mechanics.  Wiley-VCH: Weinheim.

2. Quaternion basis

Calculates rotation matrix given a unit quaternion describing the rotation

Arguments:
Input:
q - unit quaternion
Output:
m - 3x3 rotation matrix

References:
Heard, W. B. (2006).  Rigid Body Mechanics.  Wiley-VCH: Weinheim.

3. Cardan angles basis

Calculates rotation matrix given the Cardan rotation series x-y'-z''

Arguments:
Input:
v - vector containing Cardan angles about the axes x, y' and z''
Output:
m - 3x3 rotation matrix

References:
Winter, D. A. (2005).  Biomechanics and Motor Control of Human Movement (3rd Edition).
John Wiley & Sons: Hoboken, NJ.

*/

void KINEMATICS::kin_rmatcalc(double theta, Vec_DP v, Mat_DP &m) {

	m[0][0]=(1-cos(theta))*v[0]*v[0]+cos(theta);
	m[0][1]=(1-cos(theta))*v[0]*v[1]-sin(theta)*v[2];
	m[0][2]=(1-cos(theta))*v[0]*v[2]+sin(theta)*v[1];
	m[1][0]=(1-cos(theta))*v[1]*v[0]+sin(theta)*v[2];
	m[1][1]=(1-cos(theta))*v[1]*v[1]+cos(theta);
	m[1][2]=(1-cos(theta))*v[1]*v[2]-sin(theta)*v[0];
	m[2][0]=(1-cos(theta))*v[2]*v[0]-sin(theta)*v[1];
	m[2][1]=(1-cos(theta))*v[2]*v[1]+sin(theta)*v[0];
	m[2][2]=(1-cos(theta))*v[2]*v[2]+cos(theta);

	return;
}
void KINEMATICS::kin_rmatcalc(Vec_DP q, Mat_DP &m) {

 	int s=q.size();

	if (s==4) {

		m[0][0]=q[0]*q[0]+q[1]*q[1]-q[2]*q[2]-q[3]*q[3];
		m[0][1]=2*(q[1]*q[2]-q[0]*q[3]);
		m[0][2]=2*(q[1]*q[3]+q[0]*q[2]);
		m[1][0]=2*(q[2]*q[1]+q[0]*q[3]);
		m[1][1]=q[0]*q[0]-q[1]*q[1]+q[2]*q[2]-q[3]*q[3];
		m[1][2]=2*(q[2]*q[3]-q[0]*q[1]);
		m[2][0]=2*(q[3]*q[1]-q[0]*q[2]);
		m[2][1]=2*(q[3]*q[2]+q[0]*q[1]);
		m[2][2]=q[0]*q[0]-q[1]*q[1]-q[2]*q[2]+q[3]*q[3];
	}
	else if (s==3) {

		m[0][0]=cos(q[1])*cos(q[2]);
		m[0][1]=sin(q[2])*cos(q[0])+sin(q[0])*sin(q[1])*cos(q[2]);
		m[0][2]=sin(q[0])*sin(q[2])-cos(q[0])*sin(q[1])*cos(q[2]);
		m[1][0]=-cos(q[1])*sin(q[2]);
		m[1][1]=cos(q[0])*cos(q[2])-sin(q[0])*sin(q[1])*sin(q[2]);
		m[1][2]=sin(q[0])*cos(q[2])+cos(q[0])*sin(q[1])*sin(q[2]);
		m[2][0]=sin(q[1]);
		m[2][1]=-sin(q[0])*cos(q[1]);
		m[2][2]=cos(q[0])*cos(q[1]);
	}

	return;
}