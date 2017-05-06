#include "chair.h"
#include <maya/MMatrix.h>
#include <math.h>
#include "glm\glm.hpp"


//joint fully intersect with each other
chair::chair() : Furniture(1, MPoint(0,0,0), 5)
{
	num_parts = 12;
	angleOffset = 2.0 * M_PI / num_parts;
	explosion_radius = 5;
	explosion_duration = 1;
	alignment_duration = 20;
	part_interlock_duration = 30;

	transformations = {
		MPoint(2,2,0.2), MPoint(0,0,0), MPoint(0,0,0), //p1
		MPoint(0.2,0.2,3), MPoint(0,0,0), MPoint(0.33,-0.9,1.4), //p2
		MPoint(0.2,0.2,3), MPoint(0,0,0), MPoint(-0.33,-0.9,1.4), //p3
		MPoint(2,0.2,0.2), MPoint(0,0,0), MPoint(0,-0.9,2.8), //p4
		MPoint(0.2,0.2,8), MPoint(0,0,0), MPoint(0.9,-0.9,0), //p5
		MPoint(2,0.2,0.2), MPoint(0,0,0), MPoint(0,-0.9,-2), //p6
		MPoint(0.2,0.2,8), MPoint(0,0,0), MPoint(-0.9,-0.9,0), //p7
		MPoint(0.2,2,0.2), MPoint(0,0,0), MPoint(-0.9,0,-2), //p8
		MPoint(0.2,0.2,4), MPoint(0,0,0), MPoint(-0.9,0.9,-1.9), //p9
		MPoint(2,0.2,0.2), MPoint(0,0,0), MPoint(0,0.9,-2), //p10
		MPoint(0.2,0.2,4), MPoint(0,0,0), MPoint(0.9,0.9,-1.9), //p11
		MPoint(0.2,2,0.2), MPoint(0,0,0), MPoint(0.9,0,-2), //p12
	};

	mobility = {
		Y_PLUS,
		Z_MINUS,
		Y_MINUS,
		Z_PLUS,
		X_MINUS,
		X_PLUS,
		Z_PLUS,
		Y_PLUS,
		X_PLUS,
		Y_PLUS,
		Z_MINUS,
		X_MINUS	
	};
}


chair::~chair()
{
}