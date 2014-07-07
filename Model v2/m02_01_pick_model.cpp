#include "stdafx.h"
#include "m02_01_pick_model.h"
#include "m02_04_input_landmarks.h"
#include "m02_03_horsman_landmarks.h"


using namespace std;

/*

This routine is simply included to increase the extensibility of the model.  FreeBody is provided with a model based upon the Klein
Horsman data set (as described in the user manual).  If a different model is required it can be selected here.

*/

void m02_01_pick_model(Structure *calibrate_pos[], int segments, double marker_width)
{

	m02_04_input_landmarks(calibrate_pos,segments);				// Specify raw data landmarks for Klein Horsman model
	m02_03_horsman_landmarks(calibrate_pos,segments,marker_width);


	return;
}