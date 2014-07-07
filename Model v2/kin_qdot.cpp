#include "stdafx.h"
#include "nr.h"
#include "kinematics.h"
using namespace std;

/*

Calculate rate of change of unit quaternions

Arguments:
Input:
q0 - vector containing unit quaternion at time t0
q2 - vector containing unit quaternion at time t2
t - time interval between t0 and t2
Output:
q1 - vector containing rate of change of unit quaternion at time t1

*/

void KINEMATICS::kin_qdot(Vec_DP q0, Vec_DP q2, double t, Vec_DP &q1) {
	
	for (int i=0; i<q0.size(); i++) {
		q1[i]=(q2[i]-q0[i])/t;
	}

	return;
}