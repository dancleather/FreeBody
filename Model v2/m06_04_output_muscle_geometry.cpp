#include "stdafx.h"
#include "m06_04_output_muscle_geometry.h"
#include "io_dataoutput.h"





using namespace std;

/*



*/

void m06_04_output_muscle_geometry(Muscle **muscle_data[], int frames, int muscle)
{

	int pnts=muscle_data[0][muscle]->pnts;
	Mat_DP out(frames,(pnts)*3);

	for (int i=0; i<frames; i++) {

		for (int j=0; j<pnts; j++) {

			for (int k=0; k<3; k++) {

				out[i][3*j+k]=muscle_data[i][muscle]->gblpnts[j][k];
			}

		}
	}
		
	string filename0="Files/Outputs/muscle_geometry/muscle_path" + to_string(muscle) + ".txt";

	io_dataoutput(filename0,out);

	return;
}