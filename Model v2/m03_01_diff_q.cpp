#include "stdafx.h"
#include "m03_01_diff_q.h"

#include "Segment.h"


using namespace std;

/*

Differentiate the quaternions representing the orientation of the segments by time (twice)

*/

void m03_01_diff_q(Segment **segment_data[], int frames, int segments)

{

	for (int i=1; i<frames-1; i++) {
		for (int j=0; j<segments; j++) {

			segment_data[i][j]->seg_qdot(segment_data);

		}
	}

	for (int i=2; i<frames-2; i++) {
		for (int j=0; j<segments; j++) {

			segment_data[i][j]->seg_qdotdot(segment_data);

		}
	}

	return;
}