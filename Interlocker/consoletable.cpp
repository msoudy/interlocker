#include "consoletable.h"
#include <maya/MMatrix.h>
#include <math.h>
#include "glm\glm.hpp"

ConsoleTable::ConsoleTable() : Furniture(1, MPoint(0,0,0), 5)
{
	num_parts = 6;
	angleOffset = 2.0 * M_PI / num_parts;
	explosion_radius = 5;
	explosion_duration = 1;
	alignment_duration = 20;
	part_interlock_duration = 30;

	transformations = {
		MPoint(0.2,0.7,0.8), MPoint(0,0,0), MPoint(-1,-1.15,-0.15),
		MPoint(0.2,3.0,1.0), MPoint(0,90,0), MPoint(-1.5,0,0),
		MPoint(0.2,3.5,1.1), MPoint(0,0,90), MPoint(0.2,-0.8,-0.2),
		MPoint(0.2,3.2,1.0), MPoint(0,0,90), MPoint(0.2,0.5,-0.2),
		MPoint(0.2,3.0,1.0), MPoint(0,0,0), MPoint(1.5,0,0),
		MPoint(0.2,4.0,1.5), MPoint(0,0,90), MPoint(0,1.5,0)
	};

	mobility = {
		Y_PLUS,
		X_PLUS,
		Y_MINUS,
		X_MINUS,
		Z_MINUS,
		Y_MINUS
	};

}


ConsoleTable::~ConsoleTable()
{
}