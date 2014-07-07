#include "stdafx.h"
#include "m03_02_calc_angular_quantities.h"

#include "Segment.h"


using namespace std;

/*

Calculate segment angular velocities and accelerations

*/

void m03_02_calc_angular_quantities(Segment **segment_data[], int frames, int segments)

{

	for (int i=2; i<frames-2; i++) {
		for (int j=0; j<segments; j++) {

			segment_data[i][j]->seg_omega();

		}
	}

	for (int i=2; i<frames-2; i++) {
		for (int j=0; j<segments; j++) {

			segment_data[i][j]->seg_alpha();

		}
	}

	return;
}