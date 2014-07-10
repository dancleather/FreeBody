function v1 = qrotate(v0,q)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

	t2=q(1)*q(2);
	t3=q(1)*q(3);
	t4=q(1)*q(4);
	t5=-q(2)*q(2);
	t6=q(2)*q(3);
	t7=q(2)*q(4);
	t8=-q(3)*q(3);
	t9=q(3)*q(4);
	t10=-q(4)*q(4);

	v1(1)=2*(v0(1)*(t8+t10)+v0(2)*(t6-t4)+v0(3)*(t3+t7))+v0(1);
	v1(2)=2*(v0(1)*(t4+t6)+v0(2)*(t5+t10)+v0(3)*(t9-t2))+v0(2);
	v1(3)=2*(v0(1)*(t7-t3)+v0(2)*(t2+t9)+v0(3)*(t5+t8))+v0(3);


end

