#pragma once
#include "stdafx.h"
#include "Segment.h"
#include "mathematics.h"
#include "kinematics.h"

/*

Segment class definition

*/
/*

Segment class constructor

*/
Segment::Segment() {
	
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
	for (int i=0; i<4; i++) {
		this->rot_cal_to_gcs[i]=0;
	}
	for (int i=0; i<3; i++) {
		this->trans_cal_to_gcs[i]=0;
	}

	for (int i=0; i<3; i++) {
		this->origin[i]=0;
	}
	for (int i=0; i<4; i++) {
		this->q[i]=0;
	}
	for (int i=0; i<4; i++) {
		this->qdot[i]=0;
	}
	for (int i=0; i<4; i++) {
		this->qdotdot[i]=0;
	}
	for (int i=0; i<3; i++) {
		this->w[i]=0;
	}
	for (int i=0; i<3; i++) {
		this->a[i]=0;
	}
	for (int i=0; i<3; i++) {
		this->acceleration[i]=0;
	}
	for (int i=0; i<3; i++) {
		this->fp[i]=0;
	}
	for (int i=0; i<3; i++) {
		this->fd[i]=0;
	}
	for (int i=0; i<2; i++) {
		for (int j=0; j<6; j++) {
		this->external_forces[i][j]=0;
		}
	}
	for (int i=0; i<3; i++) {
		this->mp_segmental_approach[i]=0;
	}	
	for (int i=0; i<3; i++) {
		this->md_segmental_approach[i]=0;
	}
	this->time=0;

}
void Segment::zerosegment() {
	
	this->segnum=0;
	this->length=0;
	for (int i=0; i<4; i++) {
		this->q[i]=0;
	}
	for (int i=0; i<4; i++) {
		this->qdot[i]=0;
	}
		for (int i=0; i<4; i++) {
		this->qdotdot[i]=0;
	}
	for (int i=0; i<3; i++) {
		this->w[i]=0;
	}
	for (int i=0; i<3; i++) {
		this->a[i]=0;
	}
	for (int i=0; i<3; i++) {
		this->acceleration[i]=0;
	}
	for (int i=0; i<3; i++) {
		this->fp[i]=0;
	}
	for (int i=0; i<3; i++) {
		this->fd[i]=0;
	}
	for (int i=0; i<3; i++) {
//		this->mp[i]=0;
	}	
	for (int i=0; i<3; i++) {
//		this->md[i]=0;
	}
	this->time=0;

	return;
}