// Input Data.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mathematics.h"
#include "kinematics.h"
#include "datainput.h"
#include "readdata.h"
#include "mapcoord.h"
#include "lengthcalc.h"
#include "calq1.h"
#include "writedata.h"
#include "dataoutput.h"
#include "outop.h"

using namespace std;

/*

IMPORTANT: CHANGE THIS ROUTINE BACK TO CURRENT DATA COLLECTION CONFIGURATION
(mapcoord and

Note this routine is configured to use the VICON virtual marker set
Pelvis is 0, foot is 3, then reordered in mapcoord

Need to add force input

*/

int create_segments()
{

	// Input model parameters

	const int segments=4, dataframes=450, califrames=dataframes, maxframes=dataframes,
		maxmark=5, totalmark=18;
	int nummark, frames;
	double markarr[4]={4,5,5,4};	// Number of markers per segment in order of input file
	double freq=100;
	double height=1.86, horsman=1.74;

	string calidata="/Users/Dan/My Documents/Model v1/Visual Studio 2005/Projects/Horsman/Inputs and Outputs/Inputs/position.txt";
	string dataset="/Users/Dan/My Documents/Model v1/Visual Studio 2005/Projects/Horsman/Inputs and Outputs/Inputs/position.txt";
	string forces="/Users/Dan/My Documents/Model v1/Visual Studio 2005/Projects/Horsman/Inputs and Outputs/Inputs/forcedata.txt";
	string output;

	Vec_DP markers(markarr,4);
	Vec_DP q0(4), v0(3), q1(4), v1(3);
	Vec_DP c0(3), c1(3);

	Mat_DP input(maxframes,3*totalmark), forceinput(dataframes,6);
	Mat_DP cal(segments,3*maxmark), data(segments,3*maxmark);
	Mat_DP q0mat(maxframes-1,4*segments), v0mat(maxframes-1,3*segments);
	Mat_DP r0(maxframes-1,4), r1(maxframes-1,4), d0(maxframes-1,3), d1(maxframes-1,3);
	Mat_DP q1mat(segments,4);
	Mat_DP origins(segments+1,3);
	Mat_DP scaling(4,2);

	Segment *segment0[1000], *segment1[1000], *segment2[1000], *segment3[1000];
	Segment *segchain[segments];

	for(int i=0; i<maxframes; i++) {
		segment0[i]=new Segment;
		segment1[i]=new Segment;
		segment2[i]=new Segment;
		segment3[i]=new Segment;
	}
	for(int i=0; i<segments; i++) {
			segchain[i]=new Segment;
	}

	datainput(forceinput,dataframes,6,forces);
	cout << "i";
	mapcoord(forceinput);

	for (int l=0; l<2; l++) { // Use l=0 for a calibration routine, that includes functional COR

		if (l==0) {
			frames=califrames;
			datainput(input,frames,3*totalmark,calidata);
		}

		// Input calibration information

		readdata(cal,markers,segments,0,input);			// Input calibration data (the model uses the first frame of data to
														// calibrate - consider taking an average)

		mapcoord(cal,segments,markers);					// Map coordinate system to Delp coordinate system

		// Calculate transformation from initial marker position to GCS for each frame (q0, v0)

		for (int i=1; i<frames; i++) {					// This loop iterates for each frame and outputs model inputs

			// Input data for frame of interest

			readdata(data,markers,segments,i,input);	// Input position data for each segment

			mapcoord(data,segments,markers);			// Map coordinate system to Delp coordinate system

			for (int j=0; j<segments; j++) {			// This loop iterates for each segment
	
				// Calculate transformation from initial marker position

				nummark=int (markers[segments-1-j]);
				Mat_DP p0(3,nummark), p1(3,nummark);

				for (int k=0; k<nummark; k++) {			// Input calibration and position data for segment
					for (int l=0; l<3; l++) {
						p0[l][k]=cal[j][3*k+l];			// p0 is a matrix containing the calibration position of the markers
						p1[l][k]=data[j][3*k+l];		// p1 is a matrix containing the position of the markers
					}
				}
 
				KINEMATICS::markcalc(p0,p1,q0,v0);		// Calculate unit quaternion and translation vector representing the
													// the transformation from p0 to p1
			
				for (int k=0; k<4; k++) {
					q0mat[i-1][4*j+k]=q0[k];
				}
				for (int k=0; k<3; k++) {
					v0mat[i-1][3*j+k]=v0[k];
				}
			}
		}

		if (l==0) {

		// Calculate centre of rotations

			for (int i=0; i<segments-1; i++) {

				for (int j=0; j<frames-1; j++) {
			
					for (int k=0; k<4; k++) {
						r0[j][k]=q0mat[j][4*i+k];
						r1[j][k]=q0mat[j][4*(i+1)+k];
					}

					for (int k=0; k<3; k++) {
						d0[j][k]=v0mat[j][3*i+k];
						d1[j][k]=v0mat[j][3*(i+1)+k];
					}
				}

				KINEMATICS::score(r0,r1,d0,d1,frames-1,c0,c1);

				for (int j=0; j<3; j++) {
					origins[i+1][j]=(c0[j]+c1[j])/2;
				}
			}


			// Anatomically defined COR - needs checking and scaling

			double hipcentre[3]={-0.0376,-0.0878,0.0897};
			double kneecentre[3]={-0.01587,-0.00550,0.00248};
			double anklecentre[3]={0.01478,-0.00960,0.00343};

			// Scaling

			scaling[3][1]=(cal[3][2]-cal[3][5])/(0.0415+0.2209);
			scaling[2][1]=(cal[2][2]-cal[2][5])/(0.0321+0.0547);
			scaling[1][1]=scaling[2][1];
			scaling[0][1]=(sqrt((cal[1][2]-cal[1][5])*(cal[1][2]-cal[1][5])+(cal[1][0]-cal[1][3])*(cal[1][0]-cal[1][3]))
				/(sqrt((0.0104-0.0455)*(0.0104-0.0455)+(0.112-0.045)*(0.112-0.045))));

			hipcentre[0]=hipcentre[0]*(cal[3][0]-cal[3][6])/(0.0376+0.113);
			hipcentre[1]=hipcentre[1]*((cal[3][1]-cal[2][1])/(0.0878+0.3996));
			hipcentre[2]=hipcentre[2]*scaling[3][1];

			for (int i=0; i<3; i++) {
				origins[3][i]=((cal[3][i]+cal[3][i+3])/2)+hipcentre[i];
				origins[2][i]=((cal[2][i]+cal[2][i+3])/2)+kneecentre[i];
				origins[1][i]=((cal[1][i]+cal[1][i+3])/2)+anklecentre[i];
			}

			MATHEMATICS::zeromatrix(input);
			MATHEMATICS::zeromatrix(q0mat);
			MATHEMATICS::zeromatrix(v0mat);

			frames=dataframes;
			datainput(input,frames,3*totalmark,dataset);

			readdata(data,markers,segments,0,input);	// Input position data for each segment

			mapcoord(data,segments,markers);			// Map coordinate system to Delp coordinate system

			for (int j=1; j<segments; j++) {			// This loop iterates for each segment
	
				// Calculate transformation from initial marker position

				nummark=int (markers[segments-1-j]);
				Mat_DP p0(3,nummark), p1(3,nummark);

				for (int k=0; k<nummark; k++) {			// Input calibration and position data for segment
					for (int l=0; l<3; l++) {
						p0[l][k]=cal[j][3*k+l];			// p0 is a matrix containing the calibration position of the markers
						p1[l][k]=data[j][3*k+l];		// p1 is a matrix containing the position of the markers
					}
				}
 
				KINEMATICS::markcalc(p0,p1,q0,v0);		// Calculate unit quaternion and translation vector representing the
													// the transformation from p0 to p1

				for (int k=0; k<3; k++) {
					c0[k]=origins[j][k];
				}

				KINEMATICS::qrotate(c0,q0,c1);

				for (int k=0; k<3; k++) {
					origins[j][k]=c1[k]+v0[k];
				}

			}
		}
	}

	// Complete origins matrix

	for (int i=0; i<3; i++) {			
		origins[0][i]=cal[0][i+6];					// Marker on second metatarsal
		origins[4][i]=(cal[3][i]+cal[3][i+3])/2;	// Mid point of ASISs
	}

	// Calculate segment lengths

	lengthcalc(origins,segchain);

	// Scaling

	scaling[2][0]=segchain[2]->length/0.4098;
	scaling[3][0]=scaling[2][0];
	scaling[1][0]=segchain[1]->length/0.4099;
	scaling[0][0]=segchain[0]->length/0.1333;

	// Calculate transformation from LCS to initial marker position (q1)

	calq1(q1mat,segments,cal,origins);

	// Calculate transformation from LCS to GCS

	for (int i=1; i<frames; i++) {
		for (int j=0; j<segments; j++) {
	
			for (int k=0; k<4; k++) {
				q0[k]=q0mat[i-1][4*j+k];
				q1[k]=q1mat[j][k];
			}

			for (int k=0; k<3; k++) {
				v0[k]=origins[j+1][k];
			}

			KINEMATICS::qrotate(v0,q0,v1);

			for (int k=0; k<3; k++) {
				v1[k]+=v0mat[i-1][3*j+k];
			}

			q0=MATHEMATICS::qmply(q0,q1);

			// Save location and orientation of each segment in segment class

			segchain[j]->segnum=j;				// Store segment number
			for (int k=0; k<3; k++) {			// Store location of origin for the segment
				segchain[j]->origin[k]=v1[k];
			}
			for (int k=0; k<4; k++) {			// Store unit quaternion for rotation of the segment
				segchain[j]->q[k]=q0[k];
			}
			segchain[j]->time=(i-1)*(1/freq);

		}

		for (int k=0; k<3; k++) {				// Store force on distal aspect of foot
			segchain[0]->fd[k]=forceinput[i][k+3];
		}
		
		writedata(segment0,segment1,segment2,segment3,segchain,i);	
			
	}

	dataoutput("/Users/Dan/My Documents/Model v1/Visual Studio 2005/Projects/Horsman/Inputs and Outputs/Outputs0/segment0.txt",frames,segment0);
	dataoutput("/Users/Dan/My Documents/Model v1/Visual Studio 2005/Projects/Horsman/Inputs and Outputs/Outputs0/segment1.txt",frames,segment1);
	dataoutput("/Users/Dan/My Documents/Model v1/Visual Studio 2005/Projects/Horsman/Inputs and Outputs/Outputs0/segment2.txt",frames,segment2);
	dataoutput("/Users/Dan/My Documents/Model v1/Visual Studio 2005/Projects/Horsman/Inputs and Outputs/Outputs0/segment3.txt",frames,segment3);

	dataoutput("/Users/Dan/My Documents/Model v1/Visual Studio 2005/Projects/Horsman/Inputs and Outputs/Outputs0/scaling.txt",scaling);

	for (int i=1; i<frames; i++) {
		for (int j=0; j<3; j++) {
	
			forceinput[i][j+3]=forceinput[i][j];
			}
			forceinput[i][0]=input[i][48]/1000;	//Should be +ve
			forceinput[i][1]=input[i][50]/1000;
			forceinput[i][2]=-input[i][49]/1000;		// Should be -ve

	}

	dataoutput("/Users/Dan/My Documents/Model v1/Visual Studio 2005/Projects/Horsman/Inputs and Outputs/Outputs0/distmom.txt",frames,forceinput);


	return 0;
}