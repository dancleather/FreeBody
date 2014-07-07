#include "stdafx.h"
#include "m06_02_output_trad_ida.h"
#include "io_dataoutput.h"





using namespace std;

/*



*/

void m06_02_output_trad_ida(Segment **segment_data[], int frames, int segments)
{

	Mat_DP trad_ida(frames,18);
	for (int i=2; i<frames-2; i++) {
		for (int j=0; j<3; j++) {
			for (int k=0; k<3; k++) {
				trad_ida[i][3*j+k]=segment_data[i][j]->fp[k];
				trad_ida[i][3*j+k+9]=segment_data[i][j]->mp_segmental_approach[k];
			}
		}
	}
	
	io_dataoutput("Files/Outputs/segmental_forces_moments.txt",trad_ida);





	return;
}