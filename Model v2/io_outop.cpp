#include "stdafx.h"

/*

Define all output operators

*/

ostream &operator <<(ostream &out, Vec_DP &v) {
	for (int i=0; i<v.size(); i++) {
		out << v[i] << " ";
	}	
	out << endl;
	return out;
}
ostream &operator <<(ostream &out, Mat_DP &m) {
	for (int i=0; i<m.nrows(); i++) {
		for (int j=0; j<m.ncols(); j++) {
		out << m[i][j] << " ";
		}	
	out << endl;
	}
	return out;
}
ostream &operator <<(ostream &out, Segment &s) {
	out << setprecision(10);
	out << "<frame>" << s.frame << "</frame>" << endl;
	out << "<time> " << s.time << "</time>" << endl;
	out	<< "<segment_number>" << s.segnum << "</segment_number>" << endl;
	out << "<length>" << s.length << "</length>" << endl;
	out << "<mass>" << s.mass << "</mass>" << endl;
	out << "<inertia>";
		for (int i=0; i<3; i++) {
				out << s.inertia[i] << " ";
		}
	out << endl;
	out << "</marker_positions>";
	out << "<number_markers>" << s.markers << "</number_markers>" << endl;
	out << "<marker_positions>";
		for (int i=0; i<s.markers; i++) {
			for (int j=0; j<3; j++){
				out << s.marker_pos[i][j] << " ";
			}
			out << endl;
		}
		out << "</marker_positions>";
	out << endl << "landmarks:" << endl;
	for (int i=0; i<3; i++) {
		out << i << ": ";
		for (int j=0; j<6; j++){
		out << s.landmarks[i][j] << " ";
		}
		out << endl;
		}
	out << endl << "origin: ";
	for (int i=0; i<3; i++) {
		out << s.origin[i] << " ";
	}
	out << endl << "rot_lcs_to_gcs: ";
	for (int i=0; i<4; i++) {
		out << s.rot_lcs_to_gcs[i] << " ";
	}
	out << endl << "rot_cal_to_gcs: ";
	for (int i=0; i<4; i++) {
		out << s.rot_cal_to_gcs[i] << " ";
	}
	out << endl << "qdot: ";
	for (int i=0; i<4; i++) {
		out << s.qdot[i] << " ";
	}
	out << endl << "qdotdot: ";
	for (int i=0; i<4; i++) {
		out << s.qdotdot[i] << " ";
	}
	out << endl << "w: ";
	for (int i=0; i<3; i++) {
		out << s.w[i] << " ";
	}
	out << endl << "a: ";
	for (int i=0; i<3; i++) {
		out << s.a[i] << " ";
	}
	out << endl << "accn: ";
	for (int i=0; i<3; i++) {
		out << s.acceleration[i] << " ";
	}
	out << endl << "fp: ";
	for (int i=0; i<3; i++) {
		out << s.fp[i] << " ";
	}
	out << endl << "fd: ";
	for (int i=0; i<3; i++) {
		out << s.fd[i] << " ";
	}
	out << endl << "ext forces:" << endl;
	for (int i=0; i<2; i++) {
		out << i << ": ";
		for (int j=0; j<6; j++){
		out << s.external_forces[i][j] << " ";
		}
		out << endl;
	}
	out << endl << "mp:";
	for (int i=0; i<3; i++) {
		out << s.mp_segmental_approach[i] << " ";
	}	
	out << endl << "md:";
	for (int i=0; i<3; i++) {
		out << s.md_segmental_approach[i] << " ";
	}
	out << s.time << endl;

	return out;
}
ostream &operator <<(ostream &out, Muscle &m) {
	out << setprecision(6);
	out << m.name << endl;
	out << "Local muscle points: " << endl;
	for (int i=0; i<m.pnts; i++) {
		for (int j=0; j<6; j++) {
			out << m.mslpnts[i][j] << " ";
		}
		out << endl;
	}
	for (int i=0; i<m.pnts; i++) {
		for (int j=0; j<6; j++) {
			out << m.gblpnts[i][j] << " ";
		}
		out << endl;
	}

	return out;
}