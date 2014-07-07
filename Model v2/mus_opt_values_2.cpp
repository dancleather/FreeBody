#include "stdafx.h"


/*

Calculates the parameters of the optimization, based upon optimization method 2 (as described in the FreeBody user manual)

*/
void Muscle::mus_opt_values_2(Segment **segment_data[]) {



	int points=this->pnts, segment_prox_point, segment_dist_point, frame=this->frame;
	int segment_most_prox=int (this->gblpnts[0][3]), segment_most_dist=int (this->gblpnts[points-1][3]);
	int num_segments=this->segments_spanned;
	Vec_DP v0(3), v1(3), v2(3), v3(3), v4(3), v5(3), v6(3), v7(3), r(3), Fnorm(3), Fnorm1(3), Fnorm2(3), opt_vec(3);

	for (int i=0; i<points-1; i++) {														// This routine iterates for each muscle point

		segment_prox_point=int (this->gblpnts[i][3]);										// Determine the location of each muscle point (what segment)
		segment_dist_point=int (this->gblpnts[i+1][3]);

		// Determine optimization values at distal segment for all muscles
		
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
				this->opt_2[0][j]=Fnorm[j];
				this->opt_2[3][j]=opt_vec[j];
			}
			this->opt_2[0][3]=segment_most_dist;
			this->opt_2[3][3]=segment_most_dist;		
			
			// Calculate optimization values for proximal segment of monoarticular muscles

			if (num_segments == 2) {

				for (int j=0; j<3; j++) {
					v2[j]=segment_data[frame][segment_prox_point]->rot_centre[j];
					r[j]=v0[j]-v2[j];
					Fnorm[j]=v1[j]-v0[j];
				}
				
				Fnorm=MATHEMATICS::math_vecnorm(Fnorm);
				opt_vec=MATHEMATICS::math_crossprd(r,Fnorm);

				for (int j=0; j<3; j++) {
					this->opt_2[1][j]=Fnorm[j];
					this->opt_2[4][j]=opt_vec[j];
				}
				this->opt_2[1][3]=segment_most_prox;
				this->opt_2[2][3]=-1;
				this->opt_2[4][3]=segment_most_prox;
				this->opt_2[5][3]=-1;

			}

			// Calculate optimization values for proximal segments of biarticular muscles that do not attach to the
			// intermediate segment

			else if ((num_segments == 3) && (segment_prox_point == segment_most_prox)) {

				for (int j=0; j<3; j++) {
					v2[j]=segment_data[frame][segment_most_prox]->rot_centre[j];
					r[j]=v0[j]-v2[j];
					Fnorm[j]=v1[j]-v0[j];
				}
		
				Fnorm=MATHEMATICS::math_vecnorm(Fnorm);
				opt_vec=MATHEMATICS::math_crossprd(r,Fnorm);

				for (int j=0; j<3; j++) {
					this->opt_2[1][j]=Fnorm[j];
					this->opt_2[4][j]=opt_vec[j];
				}
				this->opt_2[1][3]=segment_most_prox;
				this->opt_2[2][3]=-1;
				this->opt_2[4][3]=segment_most_prox;
				this->opt_2[5][3]=-1;
			}

			// Calculate optimization values for distal end of intermediate segment of biarticular muscles that attach to the
			// intermediate segment
			
			else if ((num_segments == 3) && (segment_prox_point != segment_most_prox)) {

				for (int j=0; j<3; j++) {
					v2[j]=segment_data[frame][segment_data[frame][segment_most_prox]->dist]->rot_centre[j];
					r[j]=v0[j]-v2[j];
					Fnorm[j]=v1[j]-v0[j];
				}
		
				Fnorm=MATHEMATICS::math_vecnorm(Fnorm);
				opt_vec=MATHEMATICS::math_crossprd(r,Fnorm);
		
				for (int j=0; j<3; j++) {
					this->opt_2[2][j]+=Fnorm[j];
					this->opt_2[5][j]+=opt_vec[j];
				}
			}
		}

		// Calculate optimization values for proximal and proximal end of intermediate segments of biarticular muscles that attach to the
		// intermediate segment

		else if ((num_segments == 3) && (segment_prox_point == segment_most_prox) && (segment_dist_point != segment_most_prox) &&
			(segment_dist_point != segment_most_dist)) {

			for (int j=0; j<3; j++) {
				v0[j]=this->gblpnts[i][j];
				v1[j]=this->gblpnts[i+1][j];
				v2[j]=segment_data[frame][(segment_data[frame][segment_most_prox]->dist)]->rot_centre[j];
				r[j]=v1[j]-v2[j];
				Fnorm[j]=v0[j]-v1[j];
			}

			Fnorm=MATHEMATICS::math_vecnorm(Fnorm);
			opt_vec=MATHEMATICS::math_crossprd(r,Fnorm);

			for (int j=0; j<3; j++) {
				this->opt_2[2][j]=Fnorm[j];
				this->opt_2[5][j]=opt_vec[j];
			}
			this->opt_2[2][3]=(segment_data[frame][segment_most_prox]->dist);
			this->opt_2[5][3]=(segment_data[frame][segment_most_prox]->dist);

			for (int j=0; j<3; j++) {
				v2[j]=segment_data[frame][segment_most_prox]->rot_centre[j];
				r[j]=v0[j]-v2[j];
				Fnorm[j]=v1[j]-v0[j];
			}

			Fnorm=MATHEMATICS::math_vecnorm(Fnorm);
			opt_vec=MATHEMATICS::math_crossprd(r,Fnorm);

			for (int j=0; j<3; j++) {
				this->opt_2[1][j]=Fnorm[j];
				this->opt_2[4][j]=opt_vec[j];
			}
			this->opt_2[2][3]=segment_most_prox;
			this->opt_2[5][3]=segment_most_prox;





			}

	}

	return;
}
