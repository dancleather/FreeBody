#include "stdafx.h"
#include "m03_00_calculate_kinematics.h"

#include "m03_00_set_anth.h"
#include "m03_01_diff_q.h"
#include "m03_02_calc_angular_quantities.h"
#include "m03_04_calc_linear_quantities.h"
#include "m03_05_diff_origin.h"



using namespace std;

/*



*/

void m03_00_calculate_kinematics(Segment **segment_data[], Structure *calibrate_pos[], int frames, int segments)

{
		
	m03_00_set_anth(segment_data,calibrate_pos,frames,segments);
	
	m03_01_diff_q(segment_data,frames,segments);

	m03_02_calc_angular_quantities(segment_data,frames,segments);

	m03_05_diff_origin(segment_data,frames,segments);

	m03_04_calc_linear_quantities(segment_data,calibrate_pos,frames,segments);

	

	cout << "3.";

	return;
}
/*
Auditing

m03_00_set_anth.cpp										DC - checked 02/01/14
m03_01_diff_q.cpp (and dependencies)					DC - checked 02/01/14
m03_02_calc_angular_quantities (and dependencies)		DC - checked 02/01/14
m03_05_diff_origin.cpp (and dependencies)				DC - checked 02/01/14
m03_03_calc_seg_pos_vectors.cpp (and dependencies)		DC - checked 02/01/14
m03_04_calc_linear_quantities.cpp (and dependencies)	DC - checked 02/01/14
m03_06_joint_angles.cpp (and dependencies)				DC - new routines - to be checked


*/