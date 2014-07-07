#pragma once
#include "stdafx.h"
#include "Structure.h"


/*

Segment class definition

*/

class Segment {
public:

	// *********************************************************

	// Segment structure

	// *********************************************************

	// General information

	int frame;					// Frame number
	double time;
	int segnum;					// Segment number
	int dist;					// Distal segment
	int prox;					// Proximal segment

	// Anthropometry

	double length;
	double mass;
	double inertia[3];
	
	// Data input

	int markers;				// Number of markers on the segment
	int ex_forces;
	double marker_pos[10][3];	// Position of each marker on the segment for the given frame in the GCS (raw data transposed to GCS)
	double landmarks[3][6];
	
	double external_forces[2][6];
	double rot_cal_to_gcs[4];
	double trans_cal_to_gcs[3];
	double trans_lcs_to_gcs[3];

	// Kinematics

	double rot_lcs_to_gcs[4];	// Orientation of segment (q)
	double qdot[4];				// Rate of change of quaternion
	double qdotdot[4];
	double w[3];				// Angular velocity in GCS
	double a[3];				// Angular acceleration in GCS

	double origin[3];			// Location of origin in GCS
	double rot_centre[3];
	double origindot[3];
	double origindotdot[3];
	double acceleration[3];		// Linear acceleration of centre of mass in GCS
	double com[3];				// Location of COM in GCS
	double distal[3];			// Location of distal end of segment in GCS
	double dist_contact[3];


	double joint_angle[3];		// Joint angles of this segment with the next most distal segment (basis?)

	// Kinetics

	double q[4];				// Segment quaternion for rotation from GCS to LCS ?????????????????????????
	double fp[3];				// Force on proximal end of segment in GCS
	double fd[3];				// Force on distal end of segment in GCS
	double mp_segmental_approach[3];				// Moment at proximal end of segment in GCS
	double md_segmental_approach[3];				// Moment at distal end of segment in GCS
	double mp_opt_approach[3];
	double md_opt_approach[3];

	double rhs_opt_approach_1[6];
	double rhs_opt_approach_2[6];

	double internal_reaction_forces_prox[2][4];
	double internal_reaction_forces_dist[4][4];

	double vec_rot_centre_to_rf[4][3];

	// Patella specific details

	double other_points[2][3];
	double theta;
	double beta;
	double patella_ratio;
	double contact_position;
	
	// *****************************************************************

	// Segment functions

	// *****************************************************************

	// General

	Segment();
	void zerosegment();

	// Create segments

	void seg_calculate_transf_cal_to_gcs(Structure *calibrate_pos[]);
	void seg_calculate_transf_lcs_to_gcs(Structure *calibrate_pos[]);

	// Kinematics

	void seg_qdot(Segment **segment_data[]);
	void seg_qdotdot(Segment **segment_data[]);
	void seg_origindot(Segment **segment_data[]);
	void seg_origindotdot(Segment **segment_data[]);
	void seg_omega();
	void seg_alpha();
	Vec_DP seg_pos_point_on_seg(Vec_DP v);
	Vec_DP seg_pos_point_in_lcs(Vec_DP v);
	Vec_DP seg_rot_to_gcs(Vec_DP v);
	Vec_DP seg_vel_point_on_seg(Vec_DP v);
	Vec_DP seg_accn_point_on_seg(Vec_DP v);

	// Inverse dynamics

	void seg_solve_wrench_eqns(Vec_DP g);
};