#include "shoerack.h"
#include <maya/MMatrix.h>
#include <math.h>
#include "glm\glm.hpp"

shoerack::shoerack() : Furniture(1, MPoint(0,0,0), 5)
{
	num_parts = 9;
	angleOffset = 2.0 * M_PI / num_parts;
	explosion_radius = 5;
	explosion_duration = 1;
	alignment_duration = 20;
	part_interlock_duration = 30;

	transformations = {
		MPoint(3,0.2,1.5), MPoint(0,0,0), MPoint(0,-1.5,0), //p1
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(-1.5,0,-0.75), //p2
		MPoint(0.2,0.2,1.5), MPoint(0,0,0), MPoint(-1.5,1.8,0), //p3
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(-1.5,0,0.75), //p4
		MPoint(3,0.2,1.5), MPoint(0,0,0), MPoint(0,0,0), //p5
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(1.5,0,0.75), //p6
		MPoint(0.2,0.2,1.5), MPoint(0,0,0), MPoint(1.5,1.8,0), //p7
		MPoint(0.2,3,0.2), MPoint(0,0,0), MPoint(1.5,0,-0.75), //p8
		MPoint(3,0.2,1.5), MPoint(0,0,0), MPoint(0,1.5,0), //p9
	};

	mobility = {
		Y_PLUS,
		X_PLUS,
		Y_PLUS,
		Z_MINUS,
		X_MINUS,
		Y_MINUS,
		X_MINUS,
		Z_PLUS,
		Y_MINUS
	};

}


shoerack::~shoerack()
{
}