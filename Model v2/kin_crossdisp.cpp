#include "stdafx.h"
#include "nr.h"
#include "mathematics.h"
#include "kinematics.h"
using namespace std;

/*

Calculate cross-dispersion matrix of n markers given their positions at p0 and p1

Arguments:
Input:
p0, p1 - 3xn matrices which contain n marker positions before and after transformation respectively
Output:
xbar0, xbar1 - mean marker position before and after transformation respectively
cross - cross-dispersion matrix

Dependencies:
Mathematics: math_zeromatrix

References:
Challis, J. H. (1995).  A procedure for determining rigid body transformation parameters.
Journal of Biomechanics, 28(6), 733-737.

*/

void KINEMATICS::kin_crossdisp(Mat_DP p0, Mat_DP p1, Vec_DP &xbar0, Vec_DP &xbar1, Mat_DP &cross) {

	int n=p0.ncols(), m=p1.ncols();

	if (n!=m) {
		cout << "Number of initial points not equal to number of final points";
	}

	else {

		for (int i=0; i<3; i++) {
			xbar0[i]=xbar1[i]=0;
		}
		for (int i=0; i<3; i++) {
			for (int j=0; j<n; j++) {
				xbar0[i]+=p0[i][j];
				xbar1[i]+=p1[i][j];
			}
		}
		for (int i=0; i<3; i++) {	// Calculate mean marker position
			xbar0[i]=xbar0[i]/n;
			xbar1[i]=xbar1[i]/n;
		}

		for (int i=0; i<3; i++) {
			for (int j=0; j<n; j++) {
				p0[i][j]=p0[i][j]-xbar0[i];
				p1[i][j]=p1[i][j]-xbar1[i];
			}
		}
		MATHEMATICS::math_zeromatrix(cross);
		for (int i=0; i<3; i++) {		// Calculate cross-dispersion matrix
			for (int j=0; j<3; j++) {
				for (int k=0; k<n; k++) {
					cross[i][j]+=p1[i][k]*p0[j][k];
				}
			}
		}
	}

	return;
}