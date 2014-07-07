#pragma once
#include "stdafx.h"


/*

Muscle class definition

*/

class Muscle {
public:


	string name;
	int frame;
	int pnts;
	int segments_spanned;
	double time;
	double pq_ratio;


	double mslpnts[15][6];
	double gblpnts[15][6];
	
	double wrap[3][3];
	
	double opt[8][4];
	double opt_2[8][4];
	double opt_3[8][4];

	double pcsa;
	double pcsa_multiple;
	double max_tension;

	double length;
	double length_change;

	double max_force;

	double pennation_angle;

	Muscle() {;}

	void mus_lcs_to_gcs(Segment **segment_data[], Structure *calibrate_pos[]);
	void mus_upper_bound();
	void mus_opt_values_1(Segment **segment_data[]);
	void mus_opt_pt_1(Segment **segment_data[]);
	void mus_opt_values_2(Segment **segment_data[]);
	void mus_opt_pt_2(Segment **segment_data[]);
	void mus_opt_values_3(Segment **segment_data[], Muscle *patellar_tendon[]);
	void mus_wrapping(Segment **segment_data[], Structure *calibrate_pos[], int i);
	void mus_length();
	void mus_length_change(Muscle **muscle_data[], int muscle);


};
