#include "stdafx.h"
#include "Muscle.h"
#include "m05_03_patella_ratios.h"




using namespace std;

/*



*/

void m05_03_patella_ratios(Muscle **muscle_data[], Segment **segment_data[], Structure *calibrate_pos[], int frames, int muscles, Muscle *patella_ratio_av[])
{
	
	double theta, beta, points, mag_pat_ten, mag_quad_ten, pq_ratio, pq_adj;
	Vec_DP pat_vec(3), pat_ten(3), femur_axis(3), quad_ten(3), q(4), quad_ten_adj(3);

	for (int i=0; i<frames; i++) {

		for (int j=0; j<3; j++) {
	
			pat_vec[j]=segment_data[i][4]->other_points[0][j]-segment_data[i][4]->origin[j];	// other points[0][] is the insertion of the quadriceps tendon
			pat_ten[j]=segment_data[i][4]->origin[j]-segment_data[i][4]->other_points[1][j];	// other_points[1][] is the tibial tuberosity

		}

		for (int j=0; j<4; j++) {
	
			q[j]=segment_data[i][2]->rot_lcs_to_gcs[j];
		}

		q=MATHEMATICS::math_qcon(q);
		pat_vec=KINEMATICS::kin_qrotate(pat_vec,q);
		pat_ten=KINEMATICS::kin_qrotate(pat_ten,q);


		pat_vec[2]=0;

		theta=segment_data[i][4]->theta;

		// Ratio check based on femur longitudinal axis

		patella_ratio_av[i]->mus_wrapping(segment_data,calibrate_pos,1);
		patella_ratio_av[i]->pnts+=2;
		double check;
		if (patella_ratio_av[i]->gblpnts[2][0] == patella_ratio_av[i]->gblpnts[0][0]) { check =0;}
		else { check=1;}
		for (int l=0; l<3; l++) {

			quad_ten[l]=(patella_ratio_av[i]->gblpnts[2][l]-segment_data[i][4]->other_points[0][l]);
		}

		quad_ten=KINEMATICS::kin_qrotate(quad_ten,q);
		quad_ten[2]=0;

		beta=MATHEMATICS::math_dotprd(pat_vec,quad_ten);
		beta=acos(beta/((MATHEMATICS::math_vecmag(pat_vec))*(MATHEMATICS::math_vecmag(quad_ten))));

		patella_ratio_av[i]->pq_ratio=cos(beta)/cos(theta);

		// Output ratio check figures (switched off)
//		cout << (segment_data[i][2]->joint_angle[2]) << " " << check << " " << patella_ratio_av[i]->pq_ratio << " " << beta << " " << theta << endl;



		pat_ten=MATHEMATICS::math_vecnorm(pat_ten);
		pat_ten[2]=0;

		mag_pat_ten=MATHEMATICS::math_vecmag(pat_ten);




		for (int j=0; j<muscles; j++) {

			points=muscle_data[i][j]->pnts;

			muscle_data[i][j]->pq_ratio=0;

			for (int k=1; k<points; k++) {

				if ((muscle_data[i][j]->gblpnts[k][3] == 4) && (muscle_data[i][j]->gblpnts[k-1][3] !=4 )) {
					
					for (int l=0; l<3; l++) {

						quad_ten[l]=(muscle_data[i][j]->gblpnts[k-1][l]-muscle_data[i][j]->gblpnts[k][l]);

					}

					quad_ten=KINEMATICS::kin_qrotate(quad_ten,q);
					for (int l=0; l<3; l++) {
						quad_ten_adj[l]=quad_ten[l];
					}
					quad_ten[2]=0;

					beta=MATHEMATICS::math_dotprd(pat_vec,quad_ten);
					beta=acos(beta/((MATHEMATICS::math_vecmag(pat_vec))*(MATHEMATICS::math_vecmag(quad_ten))));

					pq_ratio=cos(beta)/cos(theta);


					//

					quad_ten_adj=MATHEMATICS::math_vecnorm(quad_ten_adj);
					quad_ten_adj[2]=0;
					
					mag_quad_ten=MATHEMATICS::math_vecmag(quad_ten_adj);

					pq_adj=pq_ratio*mag_quad_ten/mag_pat_ten;

					muscle_data[i][j]->pq_ratio=pq_adj;



				}
			}
		}
	}

	
	return;
}