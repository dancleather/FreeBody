#include "stdafx.h"


/*

Calculates the parameters of the optimization, based upon optimization method 6 (as described in the FreeBody user manual)

*/
void Muscle::mus_opt_values_3(Segment **segment_data[], Muscle *patellar_tendon[]) {



	int points=this->pnts, segment_prox_point, segment_dist_point, segment_prox_point_rec, segment_dist_point_rec, frame=this->frame;
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
			if (segment_most_dist == 4) {			// Patella exception
				for (int j=0; j<3; j++) {
					v0[j]=patellar_tendon[frame]->gblpnts[0][j];
					v1[j]=patellar_tendon[frame]->gblpnts[1][j];
					v2[j]=segment_data[frame][1]->rot_centre[j];
					r[j]=v1[j]-v2[j];
					Fnorm[j]=v0[j]-v1[j];
				}
			}
		
			Fnorm=MATHEMATICS::math_vecnorm(Fnorm);
			opt_vec=MATHEMATICS::math_crossprd(r,Fnorm);

			for (int j=0; j<3; j++) {
				this->opt_3[0][j]=Fnorm[j];
				this->opt_3[3][j]=opt_vec[j];
			}
			this->opt_3[0][3]=segment_most_dist;
			this->opt_3[3][3]=segment_most_dist;		

			if (segment_most_dist == 4) {			// Patella exception
				this->opt_3[0][3]=1;
				this->opt_3[3][3]=1;		
			}
			
			// Calculate optimization values for proximal segment of monoarticular muscles

			if (num_segments == 2) {

				for (int j=0; j<3; j++) {
					this->opt_3[1][j]=-Fnorm[j];
					this->opt_3[4][j]=-opt_vec[j];
				}
				this->opt_3[1][3]=segment_most_prox;
				this->opt_3[2][3]=-1;
				this->opt_3[4][3]=segment_most_prox;
				this->opt_3[5][3]=-1;

			}
			else if ((num_segments == 3) && (segment_most_dist == 4)) {

				for (int j=0; j<3; j++) {
					this->opt_3[2][j]=-Fnorm[j];
					this->opt_3[5][j]=-opt_vec[j];
				}
				this->opt_3[2][3]=2;
				this->opt_3[5][3]=2;

				for (int k=0; k<points; k++) {														// This routine iterates for each muscle point

					segment_prox_point_rec=int (this->gblpnts[k][3]);										// Determine the location of each muscle point (what segment)
					segment_dist_point_rec=int (this->gblpnts[k+1][3]);
						
					if ((segment_dist_point_rec != 3) && (segment_prox_point_rec == 3)) {

					for (int j=0; j<3; j++) {
						v0[j]=this->gblpnts[k][j];
						v1[j]=this->gblpnts[k+1][j];
						v2[j]=segment_data[frame][2]->rot_centre[j];
						r[j]=v1[j]-v2[j];
						Fnorm[j]=v0[j]-v1[j];
					}

					Fnorm=MATHEMATICS::math_vecnorm(Fnorm);
					opt_vec=MATHEMATICS::math_crossprd(r,Fnorm);

					for (int j=0; j<3; j++) {
						this->opt_3[1][j]=-Fnorm[j];
						this->opt_3[2][j]+=Fnorm[j];
						this->opt_3[4][j]=-opt_vec[j];
						this->opt_3[5][j]+=opt_vec[j];
					}
					this->opt_3[1][3]=3;
					this->opt_3[4][3]=3;
					}
				}

			}



			// Calculate optimization values for proximal and intermediate segments of biarticular muscles that do not attach to the
			// intermediate segment

			else if ((num_segments == 3) && (segment_prox_point == segment_most_prox) && (segment_most_dist != 4)) {

				for (int j=0; j<3; j++) {
					v2[j]=segment_data[frame][(segment_data[frame][segment_most_prox]->dist)]->rot_centre[j];
					r[j]=v0[j]-v2[j];
				}
				opt_vec=MATHEMATICS::math_crossprd(r,Fnorm);

				for (int j=0; j<3; j++) {
					this->opt_3[1][j]=-Fnorm[j];
					this->opt_3[4][j]=-opt_vec[j];
				}
				this->opt_3[1][3]=segment_most_prox;
				this->opt_3[4][3]=segment_most_prox;

				if (segment_most_dist != 4) { // Don't do this routine for rec_fem
				
					for (int j=0; j<3; j++) {
						v3[j]=segment_data[frame][(segment_data[frame][segment_most_prox]->dist)]->dist_contact[j];
						r[j]=v3[j]-v2[j];
					}
					opt_vec=MATHEMATICS::math_crossprd(r,Fnorm);

					for (int j=0; j<3; j++) {
						this->opt_3[5][j]=opt_vec[j];
					}
					this->opt_3[2][3]=-1;
					this->opt_3[5][3]=(segment_data[frame][segment_most_prox]->dist);					
				}

			}

			// Calculate optimization values for distal end of intermediate segment of biarticular muscles that attach to the
			// intermediate segment
			
			else if ((num_segments == 3) && (segment_prox_point != segment_most_prox) && (segment_most_dist != 4)) {

				for (int j=0; j<3; j++) {
					this->opt_3[2][j]-=Fnorm[j];
					this->opt_3[5][j]-=opt_vec[j];
				}
			}
		}

		// Calculate optimization values for proximal and proximal end of intermediate segments of biarticular muscles that attach to the
		// intermediate segment

		else if ((num_segments == 3) && (segment_prox_point == segment_most_prox) && (segment_dist_point != segment_most_prox) &&
			(segment_dist_point != segment_most_dist) && (segment_most_dist != 4)) {

			for (int j=0; j<3; j++) {
				v0[j]=this->gblpnts[i][j];
				v1[j]=this->gblpnts[i+1][j];
				v2[j]=segment_data[frame][(segment_data[frame][segment_most_prox]->dist)]->rot_centre[j];
				r[j]=v0[j]-v2[j];
				Fnorm[j]=v0[j]-v1[j];
			}

			Fnorm=MATHEMATICS::math_vecnorm(Fnorm);
			opt_vec=MATHEMATICS::math_crossprd(r,Fnorm);

			for (int j=0; j<3; j++) {
				this->opt_3[1][j]=-Fnorm[j];
				this->opt_3[2][j]=Fnorm[j];
				this->opt_3[4][j]=-opt_vec[j];
				this->opt_3[5][j]=opt_vec[j];
			}
			this->opt_3[1][3]=segment_most_prox;
			this->opt_3[2][3]=(segment_data[frame][segment_most_prox]->dist);
			this->opt_3[4][3]=segment_most_prox;
			this->opt_3[5][3]=(segment_data[frame][segment_most_prox]->dist);

			}




	}

	return;
}
