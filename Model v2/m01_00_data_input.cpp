// Input Data.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "m01_00_data_input.h"
#include "m01_01_dans_data_input.h"
#include "m01_02_dans_calibration_data.h"

using namespace std;

/*

Select the data input scheme to use

This routine is included to increase the extensibility of the model.  Should other data input routines
be required, they can be called here, and the existing data input routines switched off.

*/

void m01_00_data_input(Vec_DP &coord_map, Mat_DP &model_structure, Segment **segment_data[], Structure *calibrate_pos[],
					   int frames, double freq, int segments)
{

	// Input motion capture data

	int add0, add1, add2;
	Vec_DP sign(3);


	Vec_DP marker_segment_info;

	m01_01_dans_data_input(coord_map,sign,add0,add1,add2,model_structure,marker_segment_info,segment_data,calibrate_pos,frames,freq,segments);


	// Input calibration data

	// The existing model is calibrated based upon the consideration of one static frame.  Should an alternative
	// method be desired (for instance based upon the consideration of multiple static frames and average data) it 
	// can be called here.

	m01_02_dans_calibration_data(sign,add0,add1,add2,calibrate_pos,marker_segment_info,segments);



	cout << "1.";

	return;
}

/*	Auditing

m01_00_data_input.cpp					DC - checked 18/12/13
m01_01_dans_data_input.cpp				DC - checked 20/12/13
m01_01_mapcoord.cpp						DC - checked 18/12/13
m01_02_dans_calibration_data.cpp		DC - checked 20/12/13
m01_03_save_raw_positions				DC - checked 20/12/13

*/