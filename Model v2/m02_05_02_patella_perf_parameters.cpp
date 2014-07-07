#include "stdafx.h"

#include "m02_05_02_patella_perf_parameters.h"




using namespace std;

/*

Calculate pivot point of the patella (for the patellofemoral joint reaction force) and also the average P/Q ratio (as a check)

*/

void m02_05_02_patella_perf_parameters(Segment **segment_data[], int frames, Muscle *patella_ratio_av[])
{
	
	double theta, beta, check_ratio, d;
	Vec_DP pat_vec(3), pat_ten(3), femur_axis(3), quad_ten(3), q(4);


	for (int i=0; i<frames; i++) {

		for (int j=0; j<3; j++) {
	
			pat_vec[j]=segment_data[i][4]->other_points[0][j]-segment_data[i][4]->origin[j];	// other points[0][] is the insertion of the quadriceps tendon
			pat_ten[j]=segment_data[i][4]->origin[j]-segment_data[i][4]->other_points[1][j];	// other_points[1][] is the tibial tuberosity
		}

		// Analyse patellar geometry in the sagittal plane (of the femur)

		for (int j=0; j<4; j++) {
	
			q[j]=segment_data[i][2]->rot_lcs_to_gcs[j];
		}

		q=MATHEMATICS::math_qcon(q);
		pat_vec=KINEMATICS::kin_qrotate(pat_vec,q);
		pat_ten=KINEMATICS::kin_qrotate(pat_ten,q);

		pat_vec[2]=pat_ten[2]=0;

		// Find the angle of the patella tendon to the longitudinal axis of the patella

		theta=MATHEMATICS::math_dotprd(pat_vec,pat_ten);		
		theta=acos(theta/((MATHEMATICS::math_vecmag(pat_vec))*(MATHEMATICS::math_vecmag(pat_ten))));

		// Define an arbitrary muscle element that runs along the longitudinal axis of the femur

		for (int j=0; j<3; j++) {
	
			femur_axis[j]=-(segment_data[i][2]->distal[j]-segment_data[i][2]->origin[j]);
		}

		// Save the arbitray quad for later use

		for (int j=0; j<3; j++) {
			patella_ratio_av[i]->gblpnts[0][j]=segment_data[i][4]->other_points[0][j]+femur_axis[j];
			patella_ratio_av[i]->gblpnts[1][j]=segment_data[i][4]->other_points[0][j];
		}
		patella_ratio_av[i]->gblpnts[0][3]=2;
		patella_ratio_av[i]->gblpnts[1][3]=4;

		// Find the angle of the quad element to the patella in the femoral sagittal plane

		femur_axis=KINEMATICS::kin_qrotate(femur_axis,q);
		femur_axis[2]=0;
		
		beta=MATHEMATICS::math_dotprd(pat_vec,femur_axis);
		beta=acos(beta/((MATHEMATICS::math_vecmag(pat_vec))*(MATHEMATICS::math_vecmag(femur_axis))));
		
		// Find the contact position (on the patella posterior surface)

		check_ratio=cos(beta)/cos(theta);
		d=tan(beta)/(tan(theta)+tan(beta));

		segment_data[i][4]->theta=theta;
		segment_data[i][4]->beta=beta;
		segment_data[i][4]->patella_ratio=check_ratio;
		segment_data[i][4]->contact_position=d;




		


	}

	
	return;
}