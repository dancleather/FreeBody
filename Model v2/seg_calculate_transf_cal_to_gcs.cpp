#pragma once
#include "stdafx.h"
#include "Segment.h"
#include "mathematics.h"
#include "kinematics.h"

/*

Segment class definition

*/
/*

This function calculates the transformation of the markers within the object from the calibration position

*/
void Segment::seg_calculate_transf_cal_to_gcs(Structure *calibrate_pos[]) {

	Vec_DP q0(4), v0(4);
	Mat_DP p0(3,this->markers), p1(3,this->markers);

	for (int k=0; k<this->markers; k++) {			
		for (int l=0; l<3; l++) {
			p0[l][k]=calibrate_pos[this->segnum]->marker_pos[k][l];			// p0 is a matrix containing the calibration position of the markers
			p1[l][k]=this->marker_pos[k][l];								// p1 is a matrix containing the position of the markers
		}
	}
 
	KINEMATICS::kin_markcalc(p0,p1,q0,v0);		// Calculate unit quaternion and translation vector representing the transformation
												// from calibration position to current position
	for (int i=0; i<4; i++) {
		this->rot_cal_to_gcs[i]=q0[i];			// Save transformation as part of Segment object
	}
	for (int i=0; i<3; i++) {
		this->trans_cal_to_gcs[i]=v0[i];
	}

}