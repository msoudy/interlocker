#include "bookshelf.h"
#include <maya/MMatrix.h>
#include <math.h>
#include "glm\glm.hpp"

bookshelf::bookshelf() : Furniture(1, MPoint(0,0,0), 5)
{
	num_parts = 13;
	angleOffset = 2.0 * M_PI / num_parts;
	explosion_radius = 5;
	explosion_duration = 1;
	alignment_duration = 20;
	part_interlock_duration = 30;

	transformations = {
		MPoint(3,0.2,1), MPoint(0,0,0), MPoint(0,-3,0), //p1
		MPoint(0.2,8,1), MPoint(0,0,0), MPoint(1.5,0,0), //p2
		MPoint(0.2,8,1), MPoint(0,0,0), MPoint(-1.5,0,0), //p3
		MPoint(2,0.2,1), MPoint(0,0,0), MPoint(-0.5,-1,0), //p4
		MPoint(0.2,2,1), MPoint(0,0,0), MPoint(-0.5,-2,0), //p5
		MPoint(2,0.2,1), MPoint(0,0,0), MPoint(0.5,-2,0), //p6
		MPoint(0.2,2,1), MPoint(0,0,0), MPoint(0.5,-1,0), //p7
		MPoint(3,0.2,1), MPoint(0,0,0), MPoint(0,0,0), //p8
		MPoint(0.2,2,1), MPoint(0,0,0), MPoint(-0.5,1,0), //p9
		MPoint(2,0.2,1), MPoint(0,0,0), MPoint(-0.5,2,0), //p10
		MPoint(2,0.2,1), MPoint(0,0,0), MPoint(0.5,1,0), //p11
		MPoint(0.2,2,1), MPoint(0,0,0), MPoint(0.5,2,0), //p12
		MPoint(3,0.2,1), MPoint(0,0,0), MPoint(0,3,0), //p13
	};

	mobility = {
		Y_PLUS,
		Z_PLUS,
		Y_MINUS,
		Z_MINUS,
		X_PLUS,
		Y_MINUS,
		X_MINUS,
		Z_MINUS,
		X_PLUS,
		Z_MINUS,
		Y_MINUS,
		X_MINUS,
		Z_MINUS
	};

}


bookshelf::~bookshelf()
{
}