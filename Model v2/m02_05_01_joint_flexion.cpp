#include "stdafx.h"

#include "m02_05_01_joint_flexion.h"

using namespace std;

/*

Find the joint flexion angles during the motion (based upon the ICLLM)

*/

void m02_05_01_joint_flexion(Segment **segment_data[], Structure *calibrate_pos[], int frames, int segments)

{

	Vec_DP qneutral(4), qjoint(4);
	Vec_DP qdist(4), qprox(4);
	Vec_DP euler(3);

	string sequence="xyz";

	for (int j=1; j<segments; j++) {					

		Vec_DP qdist_calib(calibrate_pos[(calibrate_pos[j]->dist)]->rot_lcs_to_gcs,4);
		Vec_DP qprox_calib(calibrate_pos[j]->rot_lcs_to_gcs,4);

		qneutral=MATHEMATICS::math_qmply(MATHEMATICS::math_qcon(qdist_calib),qprox_calib);
		
		for (int i=0; i<frames; i++) {
		
			for (int k=0; k<4; k++) {

				qdist[k]=segment_data[i][(segment_data[i][j]->dist)]->rot_lcs_to_gcs[k];
				qprox[k]=segment_data[i][j]->rot_lcs_to_gcs[k];
			}

			qjoint=MATHEMATICS::math_qmply(MATHEMATICS::math_qcon(qdist),MATHEMATICS::math_qmply(qprox,MATHEMATICS::math_qcon(qneutral)));
		
			KINEMATICS::kin_cardan(qjoint,euler,sequence);

			for (int k=0; k<3; k++) {

				segment_data[i][j]->joint_angle[k]=euler[k]*180/pi;
			}

		}

	}

	return;
}