#include "stdafx.h"
#include "m02_04_input_landmarks.h"

#include "io_datainput.h"
#include "m01_01_mapcoord.h"


using namespace std;

/*

Specify calibration landmarks (in raw data) for Klein Horsman model

*/

void m02_04_input_landmarks(Structure *calibrate_pos[], int segments)
{

	int int0, int1;

	Mat_DP raw_data=io_datainput("Files/Inputs/model_settings/landmarks.txt");	// Input landmarks data

	for (int j=0; j<segments; j++) {

		for (int k=0; k<3; k++) {
			for (int l=0; l<2; l++) {
				int0=(int) raw_data[j][4*k+2*l];
				int1=(int) raw_data[j][4*k+2*l+1];
				if (int0 < 0)
				{
					for (int i=0; i<3; i++) {
						calibrate_pos[j]->landmarks[k][3*l+i]=0;
					}
				}
				else
				{
					for (int i=0; i<3; i++) {
						calibrate_pos[j]->landmarks[k][3*l+i]=calibrate_pos[int0]->marker_pos[int1][i];
					}
				}
			}
		}
		
	}

	return;
}