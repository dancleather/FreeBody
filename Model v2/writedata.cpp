#include "stdafx.h"
#include "io_inop.h"
#include "writedata.h"

/*



*/

void writedata(Segment *segment0[], Segment *segment1[], Segment *segment2[],
			   Segment *segment3[], Segment *segchain[], int index) {

				  *segment0[index-1]=*segchain[0];
				  *segment1[index-1]=*segchain[1];
				  *segment2[index-1]=*segchain[2];
				  *segment3[index-1]=*segchain[3];

	return;
}