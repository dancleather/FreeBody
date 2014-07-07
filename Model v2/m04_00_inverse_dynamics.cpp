#include "stdafx.h"
#include "m04_00_inverse_dynamics.h"



using namespace std;

/*



*/

void m04_00_inverse_dynamics(Segment **segment_data[], int frames, int segments, Vec_DP g)
{

	for (int i=2; i<frames-2; i++) {
		for (int j=0; j<segments-2; j++) {										// Make this flexible

			segment_data[i][j]->seg_solve_wrench_eqns(g);

			for (int k=0; k<3; k++) {
				segment_data[i][j+1]->fd[k]=-segment_data[i][j]->fp[k];
				segment_data[i][j+1]->md_segmental_approach[k]=-segment_data[i][j]->mp_segmental_approach[k];
			}
		}
	}


	cout << "4.";

	return;
}

/* Auditing

m04_00_inverse_dynamics.cpp							DC - checked 02/01/14
Segment::seg_solve_wrench_eqns.cpp					DC - checked 11/02/14

*/