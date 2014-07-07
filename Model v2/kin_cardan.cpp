#include "stdafx.h"



using namespace std;

/* 


Calculates the Euler angles for the specified rotation series given a unit quaternion

Note, the following convention is used: zyx means first rotation about body fixed z axis, then y, then x

The routine returns a vector giving the Euler angles, where the first term is the angle of the first rotation etc

Not all rotation sequences defined


References:
Diebel, J. (2006).  Representing attitude: Euler angles, unit quaternions, and rotation vectors. Stanford University.

*/

void KINEMATICS::kin_cardan(Vec_DP &q, Vec_DP &euler, string sequence) {

	if (sequence == "xyz")	{

		euler[2]=atan2((-2*q[1]*q[2]+2*q[0]*q[3]),(-q[3]*q[3]-q[2]*q[2]+q[1]*q[1]+q[0]*q[0]));
		euler[1]=asin(2*q[1]*q[3]+2*q[0]*q[2]);
		euler[0]=atan2((-2*q[3]*q[2]+2*q[0]*q[1]),(-q[1]*q[1]+q[0]*q[0]+q[3]*q[3]-q[2]*q[2]));
	}
	else if (sequence == "zyx") {
	
		euler[2]=atan2((2*q[2]*q[3]+2*q[0]*q[1]),(q[3]*q[3]-q[2]*q[2]-q[1]*q[1]+q[0]*q[0]));
		euler[1]=-asin(2*q[1]*q[3]-2*q[0]*q[2]);
		euler[0]=atan2((2*q[1]*q[2]+2*q[0]*q[3]),(q[1]*q[1]+q[0]*q[0]-q[3]*q[3]-q[2]*q[2]));
	}
	else if (sequence == "zxy") {

		euler[2]=atan2((-2*q[1]*q[3]+2*q[0]*q[2]),(q[3]*q[3]-q[2]*q[2]-q[1]*q[1]+q[0]*q[0]));
		euler[1]=asin(2*q[2]*q[3]+2*q[0]*q[1]);
		euler[0]=atan2((-2*q[1]*q[2]+2*q[0]*q[3]),(-q[1]*q[1]+q[0]*q[0]-q[3]*q[3]+q[2]*q[2]));
	}
	else if (sequence == "yzx") {

		euler[2]=atan2((-2*q[2]*q[3]+2*q[0]*q[1]),(-q[3]*q[3]+q[2]*q[2]-q[1]*q[1]+q[0]*q[0]));
		euler[1]=asin(2*q[1]*q[2]+2*q[0]*q[3]);
		euler[0]=atan2((-2*q[1]*q[3]+2*q[0]*q[2]),(q[1]*q[1]+q[0]*q[0]-q[3]*q[3]-q[2]*q[2]));
	}
	else if (sequence == "yxz") {

		euler[2]=atan2((2*q[1]*q[2]+2*q[0]*q[3]),(-q[3]*q[3]+q[2]*q[2]-q[1]*q[1]+q[0]*q[0]));
		euler[1]=-asin(2*q[3]*q[2]-2*q[0]*q[1]);
		euler[0]=atan2((2*q[1]*q[3]+2*q[0]*q[2]),(-q[1]*q[1]+q[0]*q[0]+q[3]*q[3]-q[2]*q[2]));
	}
	else if (sequence == "xzy") {

		euler[2]=atan2((2*q[1]*q[3]+2*q[0]*q[2]),(-q[3]*q[3]-q[2]*q[2]+q[1]*q[1]+q[0]*q[0]));
		euler[1]=-asin(2*q[1]*q[2]-2*q[0]*q[3]);
		euler[0]=atan2((2*q[2]*q[3]+2*q[0]*q[1]),(-q[1]*q[1]+q[0]*q[0]-q[3]*q[3]+q[2]*q[2]));
	}
	
	return;
}
