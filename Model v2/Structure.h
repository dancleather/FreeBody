#pragma once
#include "stdafx.h"

/*

Structure class definition

*/
/*
finish paring down
*/
class Structure {
public:

	int frame;					// Frame number
	int segnum;					// Segment number
	int dist;					// Segment number of distal segment
	int prox;					// Segment number of proximal segment
	int markers;				// Number of markers on the segment
	int ex_forces;
	double marker_pos[10][3];	// Position of each marker on the segment for the given frame in the GCS (raw data transposed to GCS)
	double landmarks[3][6];
	double landmarks_local[3][6];

	// Model anthropometry

	double mass;
	double com[3];
	double inertia[3];

	double rot_lcs_to_gcs[4];		// Orientation of segment (q)
	double rot_lcs_to_horsman[4];	// Rotation from LCS to Klein Horsman laboratory

	double scaling_factors[3];

	double length;					// Segment length
	double width;
	double depth[2];
	double origin[3];				// Location of origin in GCS
	double rot_centre[3];
	
	double origindot[3];
	double origindotdot[3];
	double acceleration[3];			// Linear acceleration of centre of mass
	double distal[3];

	double internal_reaction_forces_prox[2][4];
	double internal_reaction_forces_dist[4][4];

	

	Structure();
	Vec_DP struc_pos_point_in_calib(Vec_DP v);
	Vec_DP struc_pos_point_in_lcs(Vec_DP v);
	Vec_DP struc_rot_hors_to_lcs(Vec_DP v);
	void zerosegment();
	
};