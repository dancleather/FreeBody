// Input Data.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "m01_03_save_raw_positions.h"

#include "io_outop.h"

using namespace std;

/*

Save raw data to the relevant Segment objects for each frame for use in further processing.

*/

void m01_03_save_raw_positions(Mat_DP &raw_data, Segment **segment_data[], int frames, int segments, Vec_DP &marker_segment_info)
{

	int marker_count, mark_seg_int;

	for (int i=0; i<frames; i++) {						// Save raw data to Segment objects
		marker_count=0;

		for (int j=0; j<segments; j++) {

			segment_data[i][j]->frame=i;
			segment_data[i][j]->segnum=j;
			mark_seg_int=(int) marker_segment_info[j];
			segment_data[i][j]->markers=mark_seg_int;
				
			for (int k=marker_count; k<marker_count+mark_seg_int; k++) {
				for (int l=0; l<3; l++) {
					segment_data[i][j]->marker_pos[k-marker_count][l]=raw_data[i][3*k+l];
				}
			}
			marker_count+=mark_seg_int;
		
		
		}
	}

	
	return;
}
void m01_03_save_raw_positions(Mat_DP &raw_data, Structure *calibrate_pos[], int segments, Vec_DP &marker_segment_info)
{

	int marker_count, mark_seg_int;

	marker_count=0;

	for (int j=0; j<segments; j++) {

	calibrate_pos[j]->frame=0;
	calibrate_pos[j]->segnum=j;
	mark_seg_int=(int) marker_segment_info[j];
	calibrate_pos[j]->markers=mark_seg_int;
				
	for (int k=marker_count; k<marker_count+mark_seg_int; k++) {
		for (int l=0; l<3; l++) {
			calibrate_pos[j]->marker_pos[k-marker_count][l]=raw_data[0][3*k+l];
		}
	}
	marker_count+=mark_seg_int;
		
		
	}
	

	
	return;
}