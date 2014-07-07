#include "stdafx.h"
#include "m02_00_create_segments.h"

#include "m02_01_pick_model.h"
#include "m02_02_make_lcs.h"
#include "m02_03_01_calc_seg_pos_vectors.h"
#include "m02_04_01_scaling.h"
#include "m02_05_01_joint_flexion.h"
#include "m02_05_patella_segment.h"
#include "m02_05_02_patella_perf_parameters.h"
#include "m02_05_03_patella_contact.h"
#include "m02_07_tf_contact.h"
#include "m02_10_define_rotation_centres.h"

#include "io_datainput.h"

using namespace std;

/*



*/

void m02_00_create_segments(Mat_DP &model_structure, Segment **segment_data[], Structure *calibrate_pos[], int frames, int segments,
							Muscle *patellar_tendon[], Muscle *patella_ratio_av[], double marker_width)
{

	// Calculate transformations from calibration position to instantaneous position of segments for each frame (both in GCS)

	for (int i=0; i<frames; i++) {
		for (int j=0; j<segments; j++) {
			segment_data[i][j]->seg_calculate_transf_cal_to_gcs(calibrate_pos);
		}
	}

	// Define geometrical limits of each segment

	m02_01_pick_model(calibrate_pos,segments,marker_width);

	// Calculate transformations from LCS to calibration position (in GCS) of each segment by constructing LCS

	m02_02_make_lcs(calibrate_pos,segments);

	// Calculate transformations for LCS to GCS for each segment for each frame

	for (int i=0; i<frames; i++) {
		for (int j=0; j<segments; j++) {
			segment_data[i][j]->seg_calculate_transf_lcs_to_gcs(calibrate_pos);
		}
	}

	m02_03_01_calc_seg_pos_vectors(segment_data,calibrate_pos,frames,segments);

	m02_04_01_scaling(calibrate_pos,frames,segments);

	m02_10_define_rotation_centres(segment_data,calibrate_pos,model_structure,frames,segments);

	// Knee modelling (kinematics)
	
	m02_05_01_joint_flexion(segment_data,calibrate_pos,frames,segments);

	// Calculate position and orientation of patellar segment using St Mary's University Knee Model

	m02_05_patella_segment(segment_data,calibrate_pos,patellar_tendon,frames);

	m02_05_02_patella_perf_parameters(segment_data,frames,patella_ratio_av);

	// Patella contact point

	m02_05_03_patella_contact(segment_data,calibrate_pos,frames);

	// Find tibiofemoral contact points

	m02_07_tf_contact(segment_data,calibrate_pos,frames);

	cout << "2.";

	return;
}

/* Auditing

Segment::seg_calculate_transf_cal_to_gcs.cpp		DC - checked 23/12/13
KINEMATICS::kin_markcalc.cpp plus dependencies		DC - historic library functions
KINEMATICS::kin_cardan.cpp							DC - checked 26/02/14
KINEMATICS::kin_qcalc.cpp							to do
m02_01_pick_model.cpp								DC - checked 20/12/13
m02_02_make_lcs.cpp									DC - checked 05/01/14
m02_03_horsman_landmarks.cpp						DC - checked 24/12/13
m02_03_01_calc_seg_pos_vectors.cpp					DC - checked 26/02/13
m02_04_input_landmarks.cpp							DC - checked 23/12/13
m02_04_01_scaling.cpp								DC - checked 26/02/14
m02_05_patella_segment.cpp							DC - checked 20/02/14
m02_05_01_joint_flexion.cpp							DC - checked 26/02/14
m02_05_02_patella_perf_parameters.cpp				DC - checked 20/02/14
m02_05_03_patella_contact.cpp						DC - checked 21/02/14
m02_08_define_reaction_forces.cpp					to do
Segment::seg_calculate_transf_lcs_to_gcs.cpp		DC - checked 05/01/14
Segment::struc_pos_point_in_calib.cpp				to do
Segment::seg_pos_point_on_seg.cpp					to do


*/