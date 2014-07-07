#include "stdafx.h"
#include "io_outop.h"
#include "io_dataoutput.h"

/*

Output all data

*/
void io_dataoutput (string filename, Segment **segment_data[], int frames, int segments) {

	ofstream outfile(filename.c_str());
	outfile << "<?xml version=&quot;1.0&quot; encoding=&quot;ISO-8859-1&quot;?>" << endl;
	outfile << "<musculoskeletal_model_data>" << endl;
	for (int i=0; i<frames; i++) {
		outfile << "<frame>" << endl;
		for (int j=0; j<segments; j++) {
			outfile << "<segment>" << endl;

			outfile << "</segment>" << endl;
		}
		outfile << "</frame>" << endl;
	}
	outfile << "</musculoskeletal_model_data>" << endl;

	return;

}
void io_dataoutput(string filename, Mat_DP m) {
	
	ofstream outfile(filename.c_str());
//	outfile << m.nrows() << endl;
	for (int i=0; i<m.nrows(); i++) {
		for (int j=0; j<m.ncols(); j++) {
		outfile << m[i][j] << " ";
		}	
	outfile << endl;
	}
	outfile.close();

	return;
}
/*void dataoutput(string filename, int frames, Segment *s[]) {
	
	ofstream outfile(filename.c_str());
	outfile << frames-1 << endl;
	outfile << "Segment information" << endl;
	outfile << "Data file structure:" << endl;
	outfile << "n, data index, segnum, length, origin(3), q (4), qdot (4), qinst(4), qjnt(4), "
	<< "omega (3), alpha (3), a (3), fp (3), fd (3), mp (3), md (3), t" << endl;
	outfile << endl;
	for (int i=0; i<frames-1; i++) {
		outfile << "n " << i << " ";
		outfile << *s[i];
	}
	outfile.close();

	return;
}
void dataoutput(string filename, int frames, Mat_DP m) {
	
	ofstream outfile(filename.c_str());
	outfile << frames-1 << endl;
	outfile << "Distal moment information" << endl;
	outfile << "Data file structure:" << endl;
	outfile << "n, data index, distal point (3), cop (3)" << endl;
	outfile << endl;
	for (int i=1; i<frames; i++) {
		outfile << "n " << i-1 << " ";
		for (int j=0; j<6; j++) {
			outfile << m[i][j] << " ";
		}
		outfile << endl;
	}
	outfile.close();

	return;
}*/