#include "stdafx.h"
#include "io_outop.h"
#include "m01_01_mapcoord.h"

/*

Map lab coordinate system to Klein Horsman system

*/


void m01_01_mapcoord(Mat_DP &data, Vec_DP sign, int add0, int add1, int add2) {

	double z[3];

	for (int i=0; i<data.nrows(); i++) {
		for (int j=0; j<data.ncols(); j=j+3) {
			z[0]=data[i][j]/1000;
			z[1]=data[i][j+1]/1000;
			z[2]=data[i][j+2]/1000;
			data[i][j]=sign[0]*z[add0];		
			data[i][j+1]=sign[1]*z[add1];
			data[i][j+2]=sign[2]*z[add2];
		}
	}


	return;
}