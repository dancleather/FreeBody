// Model v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "m01_00_data_input.h"
#include "m02_00_create_segments.h"
#include "m03_00_calculate_kinematics.h"
#include "m04_00_inverse_dynamics.h"
#include "m05_00_muscle_model.h"
#include "m06_00_output_data.h"



int _tmain(int argc, _TCHAR* argv[])

{

	// Define all variables for tmain


	const int max_segments=5, max_frames=4000, max_muscles=163, max_ligaments=14;				

	Mat_DP settings(1,4);
	settings=io_datainput("Files/Inputs/raw_data/basics.txt");		// Input number of segments, frames, muscles and data collection frequency

	int segments=int (settings[0][0]), muscles=int(settings[0][1]), ligaments=int(settings[0][2]), frames=int (settings[0][5]);
	const double freq=settings[0][3], marker_width=settings[0][4];													
																		
	Vec_DP g(3);															// A vector describing the acceleration due to gravity
	g[0]=g[2]=0;
	g[1]=-9.814;

	Vec_DP coord_map;
	
	Mat_DP model_structure;													// A matrix that contains an array representing the tree-
																			// like structure of the model
	Mat_DP make_segment_info;
	

	Segment **segment_data[max_frames];
	Structure *calibrate_pos[max_segments];
	Muscle **muscle_data[max_frames];
	Muscle *muscle_model[max_muscles];
	Muscle **ligament_data[max_frames];
	Muscle *ligament_model[max_ligaments];
	Muscle *patellar_tendon[max_frames];
	Muscle *patella_ratio_av[max_frames];

	for (int i=0; i<frames; i++) {
		segment_data[i]=new Segment *[max_segments];
		muscle_data[i]=new Muscle *[max_muscles];
		ligament_data[i]=new Muscle *[max_ligaments];
		patellar_tendon[i]=new Muscle;
		patella_ratio_av[i]=new Muscle;
		for (int j=0; j<segments; j++) {
			segment_data[i][j]=new Segment;
		}
		for (int j=0; j<muscles; j++) {
			muscle_data[i][j]=new Muscle;
		}
		for (int j=0; j<ligaments; j++) {
			ligament_data[i][j]=new Muscle;
		}

	}
	for (int i=0; i<segments; i++) {
		calibrate_pos[i]=new Structure;
	}
	for (int i=0; i<muscles; i++) {
		muscle_model[i]=new Muscle;
	}
	for (int i=0; i<ligaments; i++) {
		ligament_model[i]=new Muscle;
	}


	// ****************************************************************************************

	m01_00_data_input(coord_map,model_structure,segment_data,calibrate_pos,frames,freq,segments);							// Input raw data from text files

	m02_00_create_segments(model_structure,segment_data,calibrate_pos,frames,segments,patellar_tendon,patella_ratio_av,marker_width);

	m03_00_calculate_kinematics(segment_data,calibrate_pos,frames,segments);

	m04_00_inverse_dynamics(segment_data,frames,segments,g);

	m05_00_muscle_model(segment_data,calibrate_pos,muscle_data,muscle_model,patellar_tendon,ligament_data,ligament_model,
		frames,freq,segments,muscles,ligaments,patella_ratio_av);

	m06_00_output_data(segment_data,calibrate_pos,muscle_data,patellar_tendon,ligament_data,frames,segments,muscles,ligaments);

	// ****************************************************************************************



	string stop;

//	cin >> stop;

// Test

	


	
	return 0;
}

