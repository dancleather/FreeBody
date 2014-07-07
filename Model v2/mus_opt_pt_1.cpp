#include "stdafx.h"


/*

Calculates the parameters of the optimization for the patellar tendon, based upon optimization method 1 (as described in the 
FreeBody user manual)

*/
void Muscle::mus_opt_pt_1(Segment **segment_data[]) {



	int points=this->pnts, segment_prox_point, segment_dist_point, frame=this->frame;
	int segment_most_prox=int (this->gblpnts[0][3]), segment_most_dist=int (this->gblpnts[points-1][3]);
	int num_segments=this->segments_spanned;
	Vec_DP v0(3), v1(3), v2(3), v3(3), v4(3), v5(3), v6(3), v7(3), r(3), Fnorm(3), Fnorm1(3), Fnorm2(3), opt_vec(3);

	for (int i=0; i<points-1; i++) {														// This routine iterates for each muscle point

		segment_prox_point=int (this->gblpnts[i][3]);										// Determine the location of each muscle point (what segment)
		segment_dist_point=int (this->gblpnts[i+1][3]);
		
		if ((segment_dist_point == segment_most_dist) && (segment_prox_point != segment_most_dist)) {

			for (int j=0; j<3; j++) {
				v0[j]=this->gblpnts[i][j];
				v1[j]=this->gblpnts[i+1][j];
				v2[j]=segment_data[frame][segment_dist_point]->rot_centre[j];
				r[j]=v1[j]-v2[j];
				Fnorm[j]=v0[j]-v1[j];
			}
			Fnorm=MATHEMATICS::math_vecnorm(Fnorm);
			opt_vec=MATHEMATICS::math_crossprd(r,Fnorm);

			for (int j=0; j<3; j++) {
				this->opt[0][j]=Fnorm[j];
				this->opt[3][j]=opt_vec[j];
			}
			this->opt[0][3]=segment_most_dist;
			this->opt[3][3]=segment_most_dist;

			for (int j=0; j<3; j++) {
				this->opt[1][j]=-Fnorm[j];
			}
			this->opt[1][3]=segment_most_prox;
			this->opt[2][3]=-1;

			
			if (segment_most_prox == 4) {
				for (int j=0; j<3; j++) {
					r[j]=segment_data[frame][2]->vec_rot_centre_to_rf[0][j];
				}
				opt_vec=MATHEMATICS::math_crossprd(r,Fnorm);
				for (int j=0; j<3; j++) {
					this->opt[4][j]=opt_vec[j];
				}
				this->opt[4][3]=2;
				this->opt[5][3]=-1;

			}

		
		}


	}

	return;
}
