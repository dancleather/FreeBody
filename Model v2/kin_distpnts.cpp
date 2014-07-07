#include "stdafx.h"
#include "nr.h"
#include "kinematics.h"
using namespace std;

/*

Calculates distance between two points

Arguments:
Input:
a, b - vectors containing 2 points

Output:
Distance between 2 points

*/

double KINEMATICS::kin_distpnts(Vec_DP a, Vec_DP b) {
	
	double c=0;
	double d[3];
	int x=a.size(), y=b.size();

	if(x!=y) {
		cout << "Vector dimensions are invalid for calculating the distance between two points";
	return c;
	}
	else {
		for(int i=0; i<x; i++) {
			d[i]=b[i]-a[i];
			c+=d[i]*d[i];		
		}
		c=sqrt(c);
	return c;
	}
}

