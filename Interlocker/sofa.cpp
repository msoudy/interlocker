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
		// MPoint(3,0.2,1), MPoint(0,0,0), MPoint(0,-3,0), //p1
	};

	mobility = {
		// Y_PLUS,
		// Z_PLUS,
		// Y_MINUS,
		// Z_MINUS,
		// X_PLUS,
		// Y_MINUS,
		// X_MINUS,
		// Z_MINUS,
		// X_PLUS,
		// Z_MINUS,
		// Y_MINUS,
		// X_MINUS,
		// Z_MINUS
	};

}


sofa::~sofa()
{
}