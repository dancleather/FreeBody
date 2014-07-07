#include "stdafx.h"


/*

Calculates force upper bound of each muscle element

*/
void Muscle::mus_length_change(Muscle **muscle_data[], int muscle) {

	int frame=int (this->frame);

	this->length_change=(muscle_data[frame+1][muscle]->length-muscle_data[frame-1][muscle]->length)/(muscle_data[frame+1][muscle]->time-
		muscle_data[frame-1][muscle]->time);

	return;
}
