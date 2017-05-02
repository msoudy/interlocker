#include "chair.h"
#include <maya/MMatrix.h>
#include <math.h>
#include "glm\glm.hpp"

chair::chair() : Furniture(1, MPoint(0,0,0), 5)
{
	num_parts = 12;
	angleOffset = 2.0 * M_PI / num_parts;
	explosion_radius = 5;
	explosion_duration = 1;
	alignment_duration = 20;
	part_interlock_duration = 30;

	transformations = {
		MPoint(0.2,2,2), MPoint(0,0,90), MPoint(0,0,0), //p1
		MPoint(0.2,0.2,3), MPoint(0,0,0), MPoint(0.33,-1,1.5), //p2
		MPoint(0.2,0.2,3), MPoint(0,0,0), MPoint(-0.33,-1,1.5), //p3
		MPoint(0.2,0.2,2), MPoint(0,0,90), MPoint(0,-1,3), //p4
		MPoint(0.2,0.2,3), MPoint(0,0,90), MPoint(1,-1,1.5), //p5
		MPoint(0.2,0.2,2), MPoint(0,0,90), MPoint(0,-1,-1.5), //p6
		MPoint(0.2,0.2,3), MPoint(0,0,0), MPoint(-1,-1,1.5), //p7
		MPoint(0.2,2,0.2), MPoint(0,0,0), MPoint(-1,0,-1.5), //p8		
		MPoint(0.2,0.2,3), MPoint(0,0,0), MPoint(-1,1,-1.5), //p9
		MPoint(0.2,0.2,2), MPoint(0,0,90), MPoint(0,1,-1.5), //p10
		MPoint(0.2,0.2,3), MPoint(0,0,0), MPoint(1,1,-1.5), //p11
		MPoint(0.2,2,0.2), MPoint(0,0,0), MPoint(1,0,-1.5), //p12
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