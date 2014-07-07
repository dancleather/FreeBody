#include "stdafx.h"
#include "m05_01_02_initialize_generic_quad.h"




using namespace std;

/*



*/

void m05_01_02_initialize_generic_quad(Muscle *muscle_model[], int frames, Muscle *patella_ratio_av[])
{

	// Imaginary muscle running parallel to the femur longitudinal axis

	for (int i=0; i<frames; i++) {
			patella_ratio_av[i]->frame=i;
			patella_ratio_av[i]->pnts=2;
			for (int k=0; k<3; k++) {
				for (int l=0; l<3; l++) {
					patella_ratio_av[i]->wrap[k][l]=muscle_model[162]->wrap[k][l];
				}
			}
	}

	
	return;
}