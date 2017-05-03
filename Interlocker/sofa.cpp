#include "sofa.h"
#include <maya/MMatrix.h>
#include <math.h>
#include "glm\glm.hpp"

sofa::sofa() : Furniture(1, MPoint(0,0,0), 5)
{
	num_parts = 13;
	angleOffset = 2.0 * M_PI / num_parts;
	explosion_radius = 5;
	explosion_duration = 1;
	alignment_duration = 20;
	part_interlock_duration = 30;

	transformations = {
		MPoint(7,0.6,3), MPoint(0,0,0), MPoint(0,0,0), //p1
		MPoint(0.5,2,0.2), MPoint(0,0,0), MPoint(-2,1.3,-1.6), //p2
		MPoint(0.5,2,0.2), MPoint(0,0,0), MPoint(2,1.3,-1.6), //p3
		MPoint(0.5,2,0.2), MPoint(0,0,0), MPoint(-1,1.3,-1.6), //p4
		MPoint(0.5,2,0.2), MPoint(0,0,0), MPoint(1,1.3,-1.6), //p5
		MPoint(0.5,2,0.2), MPoint(0,0,0), MPoint(0,1.3,-1.6), //p6
		MPoint(0.75,3,0.2), MPoint(0,0,0), MPoint(3.875,0,1.6), //p7
		MPoint(0.75,3,0.2), MPoint(0,0,0), MPoint(-3.875,0,1.6), //p8
		MPoint(0.75,0.2,3), MPoint(0,0,0), MPoint(-3.875,1.5,0), //p9
		MPoint(0.75,2,0.2), MPoint(0,0,0), MPoint(-3.875,1.3,-1.6), //p10
		MPoint(7,2,0.2), MPoint(0,0,0), MPoint(0,4.3,-1.6), //p11
		MPoint(0.75,2,0.2), MPoint(0,0,0), MPoint(3.875,1.3,-1.6), //p12
		MPoint(0.75,0.2,3), MPoint(0,0,0), MPoint(3.875,1.5,0), //p13
	};

	mobility = {
		Y_PLUS,
		Z_PLUS,
		Z_PLUS,
		Z_PLUS,
		Z_PLUS,
		Z_PLUS,
		X_MINUS,
		Y_MINUS,
		X_PLUS,
		Y_PLUS,
		X_PLUS,
		Z_PLUS,
		Y_MINUS
	};
}


sofa::~sofa()
{
}