#include "stdafx.h"
#include "m05_00_muscle_model.h"
#include "m05_01_pick_muscle_model.h"
#include "m05_01_01_initialize_all_muscles.h"
#include "m05_01_02_initialize_generic_quad.h"
#include "m05_03_patella_ratios.h"




using namespace std;

/*



*/

void m05_00_muscle_model(Segment **segment_data[], Structure *calibrate_pos[], Muscle **muscle_data[], Muscle *muscle_model[], 
						 Muscle *patellar_tendon[], Muscle **ligament_data[], Muscle *ligament_model[], int frames, double freq, int segments,
						 int muscles, int ligaments, Muscle *patella_ratio_av[])
{

	// Input muscle model parameters

	string filename_muscle="Files/Inputs/model_settings/horsman_muscle_model.txt";
	string filename_wrap="Files/Inputs/model_settings/wrapping_cylinders.txt";
	string filename_ligament="Files/Inputs/model_settings/ligament_model.txt";

	m05_01_pick_muscle_model(muscle_model,calibrate_pos,muscles,filename_muscle,filename_wrap);
	m05_01_pick_muscle_model(ligament_model,calibrate_pos,ligaments,filename_ligament,filename_wrap);

	m05_01_01_initialize_all_muscles(muscle_data,muscle_model,frames,freq,muscles);
	m05_01_01_initialize_all_muscles(ligament_data,ligament_model,frames,freq,ligaments);

	m05_01_02_initialize_generic_quad(muscle_model,frames,patella_ratio_av);

	// Calculate musculoskeletal geometry for each frame

	for (int i=0; i<frames; i++) {
		for (int j=0; j<muscles; j++) {
			muscle_data[i][j]->mus_lcs_to_gcs(segment_data,calibrate_pos);
			muscle_data[i][j]->mus_length();
		}
	}
	for (int i=1; i<frames-1; i++) {
		for (int j=0; j<muscles; j++) {
			muscle_data[i][j]->mus_length_change(muscle_data,j);
			muscle_data[i][j]->mus_upper_bound();
		}
	}
	for (int i=0; i<frames; i++) {
		for (int j=0; j<ligaments; j++) {

			ligament_data[i][j]->mus_lcs_to_gcs(segment_data,calibrate_pos);
			ligament_data[i][j]->mus_upper_bound();
		}
	}


	//

	m05_03_patella_ratios(muscle_data,segment_data,calibrate_pos,frames,muscles,patella_ratio_av);

	// Calculate muscle geometry values for the optimization for each frame

	for (int i=0; i<frames; i++) {
		for (int j=0; j<muscles; j++) {
//			muscle_data[i][j]->mus_opt_values_1(segment_data);
			muscle_data[i][j]->mus_opt_values_2(segment_data);
//			muscle_data[i][j]->mus_opt_values_3(segment_data,patellar_tendon);
		}
//		patellar_tendon[i]->mus_opt_pt_1(segment_data);
		patellar_tendon[i]->mus_opt_pt_2(segment_data);
	}
	for (int i=0; i<frames; i++) {
		for (int j=0; j<ligaments; j++) {
//			ligament_data[i][j]->mus_opt_values_1(segment_data);
			ligament_data[i][j]->mus_opt_values_2(segment_data);
		}
	}


	cout << "5.";

	return;
}

/*

Auditing

m05_01_pick_muscle_model.cpp					DC - checked 03/01/14
m05_01_01_initialize_all_muscles.cpp			DC - checked 03/01/14
m05_02_01_initialize_generic_quad.cpp			DC - checked 26/02/14
m05_02_horsman_muscle_model.cpp					DC - checked 26/02/14
m05_03_patella_ratios.cpp						DC - checked 04/03/14
m05_04_wrap_cylinder.cpp						DC - checked 28/02/14
Muscle::mus_lcs_to_gcs.cpp						DC - checked 03/01/14 / Non wrapping muscle outputs DC checked 26/02/14  
Muscle::mus_opt_values_1.cpp
Muscle::mus_opt_pt_1.cpp
Muscle::mus_upper_bound.cpp						DC - checked 27/02/14
Muscle::mus_wrapping.cpp						DC - checked 27/02/14
Structure::struc_rot_hors_to_lcs				DC - checked 26/02/14 - but add some description of just rotation to manual
KINEMATICS::kin_qrotate.cpp						to do


*/