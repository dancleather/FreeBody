#include "stdafx.h"
#include "m06_00_output_data.h"
#include "m06_01_output_kinematics.h"
#include "m06_02_output_trad_ida.h"
#include "m06_03_output_opt_values.h"
#include "m06_03_output_opt_values_2.h"
#include "m06_03_output_opt_values_3.h"
#include "m06_03_output_opt_values_4.h"
#include "m06_04_output_muscle_geometry.h"
#include "m06_05_output_bony_geometry.h"




using namespace std;

/*



*/

void m06_00_output_data(Segment **segment_data[], Structure *calibrate_pos[], Muscle **muscle_data[], Muscle *patellar_tendon[], Muscle **ligament_data[], 
						int frames, int segments, int muscles, int ligaments)
{

	m06_01_output_kinematics(segment_data,frames,segments);
	
//	m06_02_output_trad_ida(segment_data,frames,segments);

//	m06_03_output_opt_values(segment_data,muscle_data,patellar_tendon,ligament_data,frames,segments,muscles,ligaments);
//	m06_03_output_opt_values_2(segment_data,muscle_data,patellar_tendon,ligament_data,frames,segments,muscles,ligaments);
	m06_03_output_opt_values_3(segment_data,muscle_data,patellar_tendon,ligament_data,frames,segments,muscles,ligaments);
//	m06_03_output_opt_values_4(segment_data,muscle_data,patellar_tendon,ligament_data,frames,segments,muscles,ligaments);

	for (int i=0; i<muscles; i++) {

		m06_04_output_muscle_geometry(muscle_data,frames,i);
	}

	m06_05_output_bony_geometry(segment_data,patellar_tendon,calibrate_pos,frames,segments);


	cout << "6.";

	return;
}