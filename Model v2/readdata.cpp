#include "stdafx.h"
#include "io_inop.h"
#include "readdata.h"

/*

Input all data

*/

void readdata(Mat_DP &data, Vec_DP markers, int segments, int index, Mat_DP dataset) {
	
	int count=0;

	for (int i=0; i<segments; i++) {
		for (int j=0; j<3*markers[i]; j++) {
			data[i][j]=dataset[index][count];
			count++;
		}
	}
	
	return;
}
void readdata(Segment *segchain[], Segment *segment0[], Segment *segment1[],
			  Segment *segment2[], Segment *segment3[], int index) {

				  segchain[0]=segment0[index];
				  segchain[1]=segment1[index];
				  segchain[2]=segment2[index];
				  segchain[3]=segment3[index];

	return;
}