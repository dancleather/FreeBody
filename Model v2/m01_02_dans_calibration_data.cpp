// Input Data.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "m01_02_dans_calibration_data.h"


#include "io_datainput.h"
#include "m01_01_mapcoord.h"
#include "m01_03_save_raw_positions.h"
#include "io_outop.h"

using namespace std;

/*

Select the data input scheme to use

*/

void m01_02_dans_calibration_data(Vec_DP &sign, int &add0, int &add1, int &add2, Structure *calibrate_pos[], 
								  Vec_DP marker_segment_info, int segments)
{

	Mat_DP raw_data=io_datainput("Files/Inputs/raw_data/calib_data.txt");
	Mat_DP anthropometry=io_datainput("Files/Inputs/raw_data/anthropometry.txt");

	m01_01_mapcoord(raw_data,sign,add0,add1,add2);

	m01_03_save_raw_positions(raw_data,calibrate_pos,segments,marker_segment_info);
	
	for (int i=0; i<segments; i++) {

		calibrate_pos[i]->mass=anthropometry[i][0];
		calibrate_pos[i]->com[1]=anthropometry[i][1];
		calibrate_pos[i]->com[0]=calibrate_pos[i]->com[2]=0;

		for (int j=0; j<3; j++) {
			calibrate_pos[i]->inertia[j]=anthropometry[i][3+j];
		}
	}

	return;
}