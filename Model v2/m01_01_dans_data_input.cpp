#include "stdafx.h"
#include "m01_01_dans_data_input.h"

#include "m01_03_save_raw_positions.h"
#include "io_datainput.h"
#include "m01_01_mapcoord.h"


using namespace std;

/*

Data input scheme for data collected and formatted as described in the FreeBody user manual

*/

void m01_01_dans_data_input(Vec_DP &coord_map, Vec_DP &sign, int &add0, int &add1, int &add2, Mat_DP &model_structure, 
							Vec_DP &marker_segment_info, Segment **segment_data[], Structure *calibrate_pos[],
							int frames, double freq, int segments)
{
	
	int dummy=0, force_count;
	Vec_DP addition(3);

	// Input coordinate system mapping (from lab to model coordinate system)

	coord_map=io_datainput("Files/Inputs/raw_data/coord_map.txt",dummy);

	for (int i=0; i<3; i++) {													// This small routine just turns the coordinate mappings into
		if (coord_map[i]<0) {													// the indices that will be used to map them to the model coordinate
			sign[i]=-1;}														// system in m01_01_mapcoord.cpp
		else {sign[i]=1;}
		addition[i]=sign[i]*coord_map[i];
		addition[i]=addition[i]-1;
	}

	add0=(int) addition[0], add1=(int) addition[1], add2=(int) addition[2]; 

	// Input tree-like model structure

	model_structure=io_datainput("Files/Inputs/model_settings/model_tree_structure.txt");  

	for (int i=0; i<frames; i++) {
		for (int j=0; j<segments; j++) {
			segment_data[i][j]->dist=int (model_structure[1][j]);
		
//			segment_data[i][segment_data[i][j]->dist]->prox=j;
		}
	}
	for (int j=0; j<segments; j++) {
		calibrate_pos[j]->dist=int (model_structure[1][j]);
//		calibrate_pos[calibrate_pos[j]->dist]->prox=j;
	}

	// Input number of markers per segment
																										
	marker_segment_info=io_datainput("Files/Inputs/model_settings/markers.txt",dummy);

	// Input motion capture data

	Mat_DP raw_data=io_datainput("Files/Inputs/raw_data/position_data.txt");

	// Input external force info

	Vec_DP external_forces_info=io_datainput("Files/Inputs/model_settings/external_forces.txt",dummy);	

	// Input external forces

	Mat_DP force_data=io_datainput("Files/Inputs/raw_data/force_data.txt");		

	m01_01_mapcoord(raw_data,sign,add0,add1,add2);							// This piece of code simply maps the inputted data from
	m01_01_mapcoord(force_data,sign,add0,add1,add2);						// the laboratory coordinate frame, to the GCS of the model
	for (int i=0; i<frames; i++) {											// based upon the settings give in coord_map.txt
		for (int j=3; j<6; j++) {
			force_data[i][j]=force_data[i][j]*1000;
		}
	}

	m01_03_save_raw_positions(raw_data,segment_data,frames,segments,marker_segment_info);

	for (int i=0; i<frames; i++) {						// Save raw data to Segment objects
		force_count=0;
		for (int j=0; j<segments; j++) {

			segment_data[i][j]->time=i/freq;
			segment_data[i][j]->ex_forces=(int) external_forces_info[j];
			

			for (int k=force_count; k<force_count+segment_data[i][j]->ex_forces; k++) {
				for (int l=0; l<6; l++) {
					segment_data[i][j]->external_forces[k-force_count][l]=force_data[i][6*k+l];
				}
			}
			force_count+=segment_data[i][j]->ex_forces;
		
		}
	}

	return;
}