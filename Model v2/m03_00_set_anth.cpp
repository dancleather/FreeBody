#include "stdafx.h"
#include "m03_00_set_anth.h"

#include "Segment.h"
#include "Structure.h"


using namespace std;

/*



*/

void m03_00_set_anth(Segment **segment_data[], Structure *calibrate_pos[], int frames, int segments)

{

	for (int i=0; i<frames; i++) {
		for (int j=0; j<segments; j++) {
			segment_data[i][j]->mass=calibrate_pos[j]->mass;
			for (int k=0; k<3; k++) {
				segment_data[i][j]->inertia[k]=calibrate_pos[j]->inertia[k];
			}
		}
	}

	return;
}