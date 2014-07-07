#include "stdafx.h"
#include "string.h"

/*

Define all input operators

*/

// Input a vector

istream &operator >>(istream &in, Vec_DP &m) {
	int x=m.size();
	for (int i=0; i<x; i++) {
		in >> m[i];
	}
	return in;
}

// Input a matrix

istream &operator >>(istream &in, Mat_DP &m) {
	int x=m.nrows(), y=m.ncols();
	for (int i=0; i<x; i++) {
		for (int j=0; j<y; j++) {
			in >> m[i][j];
		}
	}
	return in;
}

// Input a muscle (object)

istream &operator >>(istream &in, Muscle &m) {
	in >> m.name;
	in >> m.pnts;
	in >> m.segments_spanned;
	for (int i=0; i<m.pnts; i++) {
		for (int j=0; j<6; j++) {
			in >> m.mslpnts[i][j];
		}
	}	
	in >> m.pcsa;
	in >> m.pcsa_multiple;
	in >> m.max_tension;
	in >> m.pennation_angle;
	return in;

}

// use strstr
/*
istream &operator >>(istream &in, Segment &s) {

	char input_elements[20];
	char input[256];
//	char end_input


//	in.get(input,256,'>');

	string str;

	cout << str.max_size();
	


	/*	in >> m.name;
	in >> m.pnts;
	for (int i=0; i<m.pnts; i++) {
		for (int j=0; j<6; j++) { // change to 7 for mono case
			in >> m.mslpnts[i][j];
		}
	}	
	in >> m.force_max;
	in >> m.optimal_fibre_length;
	in >> m.tendon_slack_length;
	in >> m.pennation_angle;
	for (int i=0; i<9; i++) {
		in >> m.joint_action[i];
	}	
	return in;
}
*/