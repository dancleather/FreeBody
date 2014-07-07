#include "stdafx.h"
#include "m06_05_output_bony_geometry.h"
#include "io_dataoutput.h"





using namespace std;

/*



*/

void m06_05_output_bony_geometry(Segment **segment_data[], Muscle *patellar_tendon[], Structure *calibrate_pos[], int frames, int segments)
{

	Mat_DP out(frames,3*segments), patella(frames,12), scaling_factors(segments,3), rot_centres(frames,3*(segments-2)), tf_joint(frames,6);

	for (int i=0; i<frames; i++) {

		for (int j=0; j<segments; j++) {

			for (int k=0; k<3; k++) {

				out[i][3*j+k]=segment_data[i][j]->origin[k];
			}

		}
	}
		
	string filename0="Files/Outputs/muscle_geometry/origins.txt";

	io_dataoutput(filename0,out);


	for (int i=0; i<frames; i++) {

		for (int k=0; k<3; k++) {

			patella[i][k]=segment_data[i][4]->other_points[0][k];
			patella[i][k+3]=segment_data[i][4]->origin[k];
			patella[i][k+6]=patellar_tendon[i]->gblpnts[0][k];
			patella[i][k+9]=patellar_tendon[i]->gblpnts[1][k];
		}

	}
		
	string filename_pat="Files/Outputs/muscle_geometry/patella.txt";

	io_dataoutput(filename_pat,patella);


	for (int i=0; i<segments; i++) {
		for (int k=0; k<3; k++) {

			scaling_factors[i][k]=calibrate_pos[i]->scaling_factors[k];
		}
	}
		
	string filename_sf="Files/Outputs/muscle_geometry/scaling_factors.txt";

	io_dataoutput(filename_sf,scaling_factors);

	for (int i=0; i<frames; i++) {

		for (int j=0; j<segments-2; j++) {

			for (int k=0; k<3; k++) {

				rot_centres[i][3*j+k]=segment_data[i][j]->rot_centre[k];
			}

		}
	}
		
	string filename_rc="Files/Outputs/muscle_geometry/rot_centres_gcs.txt";

	io_dataoutput(filename_rc,rot_centres);

	for (int i=0; i<frames; i++) {
		for (int k=0; k<3; k++) {
			
			tf_joint[i][k]=segment_data[i][2]->rot_centre[k]+segment_data[i][2]->vec_rot_centre_to_rf[2][k];
			tf_joint[i][k+3]=segment_data[i][2]->rot_centre[k]+segment_data[i][2]->vec_rot_centre_to_rf[3][k];
		}
	}
		
	string filename_tf="Files/Outputs/muscle_geometry/tf_contact_gcs.txt";

	io_dataoutput(filename_tf,tf_joint);

	return;
}