#include "babybed.h"
#include <maya/MMatrix.h>
#include <math.h>
#include "glm\glm.hpp"

babybed::babybed() : Furniture(1, MPoint(0,0,0), 5)
{
	num_parts = 22;
	angleOffset = 2.0 * M_PI / num_parts;
	explosion_radius = 5;
	explosion_duration = 1;
	alignment_duration = 20;
	part_interlock_duration = 30;

	transformations = {
		MPoint(8,0.2,4), MPoint(0,0,0), MPoint(0,0,0), //p1
		MPoint(0.4,4,0.4), MPoint(0,0,0), MPoint(3.0,1.6,1.5), //p2
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(-3.0,1.5,2), //p3-1
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(-2.0,1.5,2), //p3-2
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(-1.0,1.5,2), //p3-3
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(0,1.5,2), //p3-4
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(1.0,1.5,2), //p3-5
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(2.0,1.5,2), //p3-6
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(3.0,1.5,2), //p3-7
		MPoint(8,0.2,0.2), MPoint(0,0,0), MPoint(0,1.7,2), //p4
		MPoint(0.4,4,0.4), MPoint(0,0,0), MPoint(-3.0,1.6,1.5), //p5
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(-3.0,1.5,0), //p6		
		MPoint(0.4,4,0.4), MPoint(0,0,0), MPoint(-3.0,1.6,-1.5), //p7
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(-3.0,1.5,-2), //p8-1
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(-2.0,1.5,-2), //p8-2
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(-1.0,1.5,-2), //p8-3
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(0,1.5,-2), //p8-4
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(1.0,1.5,-2), //p8-5
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(2.0,1.5,-2), //p8-6
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(3.0,1.5,-2), //p8-7
		MPoint(8,0.2,0.2), MPoint(0,0,0), MPoint(0,1.7,-2), //p9
		MPoint(0.4,4,0.4), MPoint(0,0,0), MPoint(3.0,1.6,-1.5), //p10
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(3.0,1.5,0), //p11
	};

	mobility = {
		Y_PLUS,
		Z_MINUS,
		Y_MINUS,
		Y_MINUS,
		Y_MINUS,
		Y_MINUS,
		Y_MINUS,
		Y_MINUS,
		Y_MINUS,
		Y_MINUS,
		X_PLUS,
		Y_MINUS,
		Z_PLUS,
		Y_MINUS,
		Y_MINUS,
		Y_MINUS,
		Y_MINUS,
		Y_MINUS,
		Y_MINUS,
		Y_MINUS,
		Y_MINUS,
		X_MINUS,
		Y_MINUS
	};
}


babybed::~babybed()
{
}