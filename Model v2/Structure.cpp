#pragma once
#include "stdafx.h"
#include "Structure.h"
#include "mathematics.h"
#include "kinematics.h"

/*

Structure class definition

*/
/*

Structure class constructor

*/
Structure::Structure() {
	
	this->frame=0;
	this->segnum=0;
	this->markers=0;
	this->ex_forces=0;
	for (int i=0; i<10; i++) {
		for (int j=0; j<3; j++) {
			this->marker_pos[i][j]=0;
		}
	}
	for (int i=0; i<3; i++) {
		for (int j=0; j<6; j++) {
			this->landmarks[i][j]=0;
		}
	}

	this->length=0;

	for (int i=0; i<3; i++) {
		this->origin[i]=0;
	}
	for (int i=0; i<3; i++) {
		this->acceleration[i]=0;
	}
}
void Structure::zerosegment() {
	
	this->segnum=0;
	this->length=0;
	for (int i=0; i<3; i++) {
		this->acceleration[i]=0;
	}

	return;
}