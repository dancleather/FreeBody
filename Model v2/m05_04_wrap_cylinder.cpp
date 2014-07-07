#include "stdafx.h"
#include "m05_04_wrap_cylinder.h"
using namespace std;

/*


Wrap muscle around a cylinder

vc is vector down centre of cylinder
pc is point on vc
o is origin of muscle
ins is insertion of muscle
r is radius of cylinder
eo is effective origin
ei is effective insertion

Algorithm is based upon Charlton and Johnson (2001).  Application of spherical and cylindrical wrapping 
algorithms in a musculoskeletal model of the upper limb.  Journal of Biomechanics, 34, 1209-1216.

*/

void m05_04_wrap_cylinder(Vec_DP vc, Vec_DP pc, Vec_DP o, Vec_DP ins, double r, Vec_DP &eo, Vec_DP &ei, double direction, double &result) {

	double l1, l2, f, l1h, l2h, alpha1, alpha2, beta1, beta2, theta, h, h1, h2, short_dist, test3, axis_direction;
	double mua, mub;
	Vec_DP po(3), pins(3), vop(3), vip(3), voc(3), vic(3), idash(3), cdash(3), oidash(3), oi(3), test2(3), test4(3), test5(3), test;
	Vec_DP pa(3), pb(3), pc_vc(3);


	for (int j=0; j<3; j++) {
		oi[j]=(o[j]-ins[j]);
		pc_vc[j]=pc[j]+vc[j];
	}
	vc=MATHEMATICS::math_vecnorm(vc);

	short_dist=KINEMATICS::kin_dist_2_lines(o,oi,pc,vc);				// Calculate the shortest distance between the muscle element and the wrapping cylinder
	KINEMATICS::kin_line_line_intersect(o,ins,pc,pc_vc,pa,pb,mua,mub);	// Calculate the points of intersection between muscle and the axis of the wrapping cylinder

	// In the code below, the variables are named following the convention in Charlton and Johnson

	for (int j=0; j<3; j++) {
		po[j]=pc[j]-o[j];
		pins[j]=pc[j]-ins[j];
	}

	vop=MATHEMATICS::math_vecnorm(po);
	vip=MATHEMATICS::math_vecnorm(pins);

	vop=MATHEMATICS::math_crossprd(vc,vop);
	vip=MATHEMATICS::math_crossprd(vc,vip);
	vop=MATHEMATICS::math_vecnorm(vop);
	vic=MATHEMATICS::math_vecnorm(vip);

	voc=MATHEMATICS::math_crossprd(vop,vc);
	vic=MATHEMATICS::math_crossprd(vip,vc);
	voc=MATHEMATICS::math_vecnorm(voc);
	vic=MATHEMATICS::math_vecnorm(vic);

	for (int j=0; j<3; j++) {
		vop[j]=direction*vop[j];
		vip[j]=direction*vip[j];
	}

	// Calculate vector orthogonal to voc and vic (test 2)

	test2=MATHEMATICS::math_crossprd(voc,vic);
	
	//  Compare test 2 to vc - if they are in the same direction then the clockwise angle of excursion around the cylinder
	//  is larger than the anti-clockwise excursion
	
	test3=KINEMATICS::kin_compare_vec(test2,vc);		// 1 = from o to i small angle is anticlockwise; -1 = clockwise

	// Calculate direction of vector from projection of o onto vc to projection of ins onto vc
	// If this is in the same direction as vc then use the formula from C&J, else change the sign of vc in Equations 12 and 13
	
	test4=KINEMATICS::kin_perp_point_on_line(o,vc,pc);
	test5=KINEMATICS::kin_perp_point_on_line(ins,vc,pc);

	for (int j=0; j<3; j++) {
		test5[j]-=test4[j];
	}
	
	axis_direction=KINEMATICS::kin_compare_vec(test5,vc);

	// Calculate wrapping points if the below conditions are satisfied

	if ( ((short_dist <= r) && (0 <= mua) && (mua <= 1)) || ( ((short_dist > r) && (0 <= mua) && (mua <= 1)) && (direction == test3) ) ) {

		l1h=MATHEMATICS::math_dotprd(po,voc);
		l2h=MATHEMATICS::math_dotprd(pins,vic);

		for (int j=0; j<3; j++) {
			voc[j]=l1h*voc[j];
			vic[j]=l2h*vic[j];
		}

		l1=sqrt(l1h*l1h-r*r);
		l2=sqrt(l2h*l2h-r*r);

		for (int j=0; j<3; j++) {
			cdash[j]=o[j]+voc[j];
			idash[j]=cdash[j]-vic[j];
			oidash[j]=o[j]-idash[j];
		}

		oidash=MATHEMATICS::math_vecnorm(oidash);

		f=MATHEMATICS::math_dotprd(vic,oidash);

		f=sqrt(l2h*l2h-f*f);

		alpha1=atan(r/l1);
		alpha2=atan(r/l2);
		beta1=asin(f/(l1/cos(alpha1)));
		beta2=asin(f/(l2/cos(alpha2)));

		if ((short_dist <= r) && (direction != test3)) {

			theta=alpha1+alpha2-beta1-beta2;
		}
		else {
			theta=alpha1+alpha2+beta1+beta2;
		}
		h=MATHEMATICS::math_dotprd(oi,vc);

		h1=h*l1/(r*theta+l1+l2);
		h2=h*l2/(r*theta+l1+l2);

		voc=MATHEMATICS::math_vecnorm(voc);
		vic=MATHEMATICS::math_vecnorm(vic);


		for (int j=0; j<3; j++) {
			ei[j]=o[j]+l1*cos(alpha1)*voc[j]+l1*sin(alpha1)*vop[j]+axis_direction*h1*vc[j];
			eo[j]=ins[j]+l2*cos(alpha2)*vic[j]-l2*sin(alpha2)*vip[j]-axis_direction*h2*vc[j];
		}
		result=1;
	}
	else {

		for (int j=0; j<3; j++) {
			ei[j]=o[j];
			eo[j]=o[j];
		}
		result=0;
	}

	return;
}

