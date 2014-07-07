#include "stdafx.h"


/*

Calculates force upper bound of each muscle element

*/
void Muscle::mus_upper_bound() {

	this->max_force=this->pcsa * this->pcsa_multiple * this->max_tension;

	return;
}
