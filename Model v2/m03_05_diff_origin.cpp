#include "stdafx.h"
#include "m03_05_diff_origin.h"

#include "Segment.h"


using namespace std;

/*

Differentiate the vector representing the position of the origin of the segment with respect to time (twice)

*/

void m03_05_diff_origin(Segment **segment_data[], int frames, int segments)

{

	for (int i=1; i<frames-1; i++) {
		for (int j=0; j<segments; j++) {

			segment_data[i][j]->seg_origindot(segment_data);

		}
	}

	for (int i=2; i<frames-2; i++) {
		for (int j=0; j<segments; j++) {

			segment_data[i][j]->seg_origindotdot(segment_data);

		}
	}

	return;
}