#include "bedstand.h"
#include <maya/MMatrix.h>
#include <math.h>
#include "glm\glm.hpp"

bedstand::bedstand() : Furniture(1, MPoint(0,0,0), 5)
{
	num_parts = 6;
	angleOffset = 2.0 * M_PI / num_parts;
	explosion_radius = 5;
	explosion_duration = 1;
	alignment_duration = 20;
	part_interlock_duration = 30;

	transformations = {
		MPoint(0.2,2,2), MPoint(0,0,0), MPoint(1.5,0,0), //p1
		MPoint(3,0.2,2), MPoint(0,0,0), MPoint(0,1,0), //p2
		MPoint(3,2,0.2), MPoint(0,0,0), MPoint(0,0,-1), //p3
		MPoint(3,0.2,2), MPoint(0,0,0), MPoint(0,-1,0), //p4
		MPoint(0.2,1,2), MPoint(0,0,0), MPoint(-1.5,-0.5,0), //p5
		MPoint(1.5,0.2,2), MPoint(0,0,0), MPoint(-0.75,0,0), //p6
	};

	mobility = {
		Y_PLUS,
		Y_MINUS,
		X_PLUS,
		Z_MINUS,
		X_PLUS,
		Z_MINUS
	};

}


bedstand::~bedstand()
{
}