#include "stdafx.h"
#include "m06_01_output_kinematics.h"
#include "io_dataoutput.h"





using namespace std;

/*



*/

void m06_01_output_kinematics(Segment **segment_data[], int frames, int segments)
{


	Mat_DP joint_angles(frames,3*(segments-1));
	
	for (int i=0; i<frames; i++) {
		for (int j=0; j<segments-1; j++) {
			for (int k=0; k<3; k++) {
				joint_angles[i][3*j+k]=segment_data[i][j+1]->joint_angle[k];
//			kinematics[i][6*j+k]=segment_data[i][j]->a[k];
//			kinematics[i][6*j+k+3]=segment_data[i][j]->acceleration[k];
			}
		}
	}

	io_dataoutput("Files/Outputs/optimization/joint_angles.txt",joint_angles);



	return;
}