#include "stdafx.h"
#include "m02_05_patella_segment.h"

#include "io_datainput.h"


using namespace std;

/*

Calculate the position of the patella segment (using the St Mary's knee model)

*/

void m02_05_patella_segment(Segment **segment_data[], Structure *calibrate_pos[], Muscle *patellar_tendon[], int frames)

{

	double knee_flexion_angle, pat_ten_length0, pat_ten_length, pat_ten_sag_ang, pat_ten_cor_ang, scale_pat_ang, scale_pat_ang_dash, sf;
	double pat_ten_strain, pat_flex, pat_tilt, pat_rot;
	double sign_x, sign_z;
	Vec_DP tib_tub(3), pat_origin(3), quad_ten_ins(3), euler(3), q_femlcs_to_patlcs(4), q_lcs_to_fem(4), q_lcs_to_pat(4), q_fem_to_lcs(4);
	Vec_DP v0(3), v1(3), v2(3), pat_o_calib(3), wrap_point(3);
	
	Mat_DP patella_parameters=io_datainput("Files/Inputs/model_settings/patella_parameters.txt");			// Input patella parameters

	for (int i=0; i<3; i++) {
		tib_tub[i]=patella_parameters[1][i]*calibrate_pos[1]->scaling_factors[i];		// Position of patellar tendon insertion in tibial frame
		quad_ten_ins[i]=patella_parameters[2][i]*calibrate_pos[4]->scaling_factors[i];	// Position of quad tendon insertion in patella frame
		wrap_point[i]=patella_parameters[2][i+3]*calibrate_pos[4]->scaling_factors[i];	// Quadriceps wrapping point in patellar frame
	}	

	// Scale patellar tendon angle in anatomical position

	scale_pat_ang_dash=(patella_parameters[3][0]/180)*pi;
	scale_pat_ang=(patella_parameters[3][0]/180)*pi;
	scale_pat_ang=tan(scale_pat_ang);
	scale_pat_ang=scale_pat_ang*calibrate_pos[1]->scaling_factors[0]/calibrate_pos[1]->scaling_factors[1];
	scale_pat_ang=atan(scale_pat_ang);
	patella_parameters[3][0]=(scale_pat_ang*180)/pi;

	sf=calibrate_pos[1]->scaling_factors[0]*(sin(scale_pat_ang_dash)/sin(scale_pat_ang));
	pat_ten_length0=patella_parameters[0][0]*sf;


	for (int i=-1; i<frames; i++) {

		if (i == -1) {
			knee_flexion_angle=0;
		}
		else {
			knee_flexion_angle=(segment_data[i][2]->joint_angle[2]);
		}

		pat_ten_sag_ang=pat_ten_cor_ang=pat_ten_strain=0;
		pat_flex=pat_tilt=pat_rot=0;

		// Calculate patella position from regression relationships specified in patella_parameters.txt

		for (int j=0; j<6; j++) {

			pat_ten_sag_ang+=patella_parameters[3][j]*pow(knee_flexion_angle,j);
			pat_ten_cor_ang+=patella_parameters[4][j]*pow(knee_flexion_angle,j);
//			pat_ten_strain+=patella_parameters[5][j]*pow(knee_flexion_angle,j);			// Patella strain is switched off
			pat_flex+=patella_parameters[6][j]*pow(knee_flexion_angle,j);
			pat_tilt+=patella_parameters[7][j]*pow(knee_flexion_angle,j);
			pat_rot+=patella_parameters[8][j]*pow(knee_flexion_angle,j);

		}
		
		// Calculate position of patella origin, based upon patellar tendon length and orientation
		
		pat_ten_strain=pat_ten_strain/100;
		pat_ten_length=pat_ten_length0*(1+pat_ten_strain);									// Calculate patellar tendon length

		pat_ten_sag_ang=(pat_ten_sag_ang/180)*pi;
		pat_ten_cor_ang=(pat_ten_cor_ang/180)*pi;

		if (pat_ten_sag_ang < 0) {sign_x=-1;} else {sign_x=1;}
		if (pat_ten_cor_ang < 0) {sign_z=1;} else {sign_z=-1;}

		pat_origin[0]=sign_x*sqrt((pow(pat_ten_length,2)*pow(tan(pat_ten_sag_ang),2))/(1+pow(tan(pat_ten_sag_ang),2)+pow(tan(pat_ten_cor_ang),2)));
		pat_origin[1]=sqrt((pow(pat_ten_length,2))/(1+pow(tan(pat_ten_sag_ang),2)+pow(tan(pat_ten_cor_ang),2)));
		pat_origin[2]=sign_z*sqrt((pow(pat_ten_length,2)*pow(tan(pat_ten_cor_ang),2))/(1+pow(tan(pat_ten_sag_ang),2)+pow(tan(pat_ten_cor_ang),2)));
		
		for (int j=0; j<3; j++) {
			pat_origin[j]+=tib_tub[j];
		}

		if (i == -1) {
			pat_o_calib=calibrate_pos[1]->struc_pos_point_in_calib(pat_origin);
			for (int j=0; j<3; j++) {
				calibrate_pos[4]->origin[j]=pat_o_calib[j];
			}
		}
		else {				// Specify patella origin, and geometry of the patellar tendon (for all frames)
		
			pat_origin=segment_data[i][1]->seg_pos_point_on_seg(pat_origin);
			v0=segment_data[i][1]->seg_pos_point_on_seg(tib_tub);


			for (int j=0; j<3; j++) {
				segment_data[i][4]->origin[j]=pat_origin[j];
				segment_data[i][4]->other_points[1][j]=v0[j];
			}
			for (int j=0; j<3; j++) {
				patellar_tendon[i]->gblpnts[0][j]=pat_origin[j];
				patellar_tendon[i]->gblpnts[1][j]=v0[j];
			}
			patellar_tendon[i]->gblpnts[0][3]=4;
			patellar_tendon[i]->gblpnts[1][3]=1;
			patellar_tendon[i]->pnts=2;
			patellar_tendon[i]->segments_spanned=2;
			patellar_tendon[i]->frame=i;
		
		}

		// Find the orientation of the patella

		euler[0]=(pat_rot/180)*pi;
		euler[1]=(pat_tilt/180)*pi;
		euler[2]=(pat_flex/180)*pi;

		// Orientation of patella LCS wrt femur LCS

		KINEMATICS::kin_qcalc(euler,q_femlcs_to_patlcs,"cardan"); 

		if (i == -1) {

			for (int j=0; j<4; j++) {
				q_lcs_to_fem[j]=calibrate_pos[2]->rot_lcs_to_gcs[j];
			}

			q_lcs_to_pat=MATHEMATICS::math_qmply(q_lcs_to_fem,MATHEMATICS::math_qcon(q_femlcs_to_patlcs));

			for (int j=0; j<4; j++) {
				calibrate_pos[4]->rot_lcs_to_gcs[j]=q_lcs_to_pat[j];
			}

			v1=calibrate_pos[4]->struc_pos_point_in_calib(quad_ten_ins);

			for (int j=0; j<3; j++) {
				calibrate_pos[4]->landmarks[0][j]=v1[j];
			}


			// Calculate position of quadriceps tendon wrapping point

			calibrate_pos[4]->depth[0]=patella_parameters[0][1];
			calibrate_pos[4]->depth[1]=patella_parameters[0][2];
	
			for (int i=0; i<6; i++) {
		
				calibrate_pos[4]->landmarks_local[0][i]=0;
			}
			calibrate_pos[4]->landmarks_local[0][3]=-calibrate_pos[4]->depth[0];

			v2=calibrate_pos[4]->struc_pos_point_in_calib(wrap_point);

			v2=calibrate_pos[2]->struc_pos_point_in_lcs(v2);

			v2[0]-=calibrate_pos[4]->depth[1];
		
			for (int j=0; j<3; j++) {
				calibrate_pos[2]->landmarks_local[0][j]=v2[j];
			}

			
		}
		else {		// Find the orientation of the patella (rotation from LCS to GCS) for all frames.
	
			for (int j=0; j<4; j++) {
				q_lcs_to_fem[j]=segment_data[i][2]->rot_lcs_to_gcs[j];
			}

			q_lcs_to_pat=MATHEMATICS::math_qmply(q_lcs_to_fem,MATHEMATICS::math_qcon(q_femlcs_to_patlcs));

			for (int j=0; j<4; j++) {
				segment_data[i][4]->rot_lcs_to_gcs[j]=q_lcs_to_pat[j];
			}

			v1=segment_data[i][4]->seg_pos_point_on_seg(quad_ten_ins);

			for (int j=0; j<3; j++) {
				segment_data[i][4]->other_points[0][j]=v1[j];
			}
		}	

	}


	return;
}