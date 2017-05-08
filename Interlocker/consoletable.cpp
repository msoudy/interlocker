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
		//MPoint(0.2,0.7,0.8), MPoint(0,0,0), MPoint(-1,-1.15,-0.15),
		MPoint(0.2,3.0,1.0), MPoint(0,90,0), MPoint(-1.5,0,0),
		MPoint(0.2,3.5,1.1), MPoint(0,0,90), MPoint(0.2,-0.8,-0.2),
		MPoint(0.2,3.2,1.0), MPoint(0,0,90), MPoint(0.2,0.5,-0.2),
		MPoint(0.2,3.0,1.0), MPoint(0,0,0), MPoint(1.5,0,0),
		MPoint(0.2,4.0,1.5), MPoint(0,0,90), MPoint(0,1.5,0)
	};

// 	jointTransformations = {
	//	MPoint(0.2,0.2,0.2), MPoint(0,0,0), MPoint(-1.1,0.5,0)
		//MPoint(0.2,0.2,0.2), MPoint(0,0,0), MPoint(-1.1,-0.8,0)
//	};

	mobility = {
		//Y_PLUS,
		X_PLUS,
		Y_MINUS,
		X_MINUS,
		Z_MINUS,
		Y_MINUS
	};

}


std::vector<MPoint> ConsoleTable::updateJoints(int time, int part, int expIdx, std::vector<MPoint> srt) {

	int i = part;
	//initial explosion
	if (time <= explosion_duration) {
		float x = (origin.x + explosion_radius * cos(angleOffset*expIdx)) * (float(time - 1) / explosion_duration);
		float y = (origin.y + explosion_radius * sin(angleOffset*expIdx)) * (float(time - 1) / explosion_duration);
		float z = origin.z * (float(time - 1) / explosion_duration);
		MPoint untranslated = srt[i * 3 + 2];
		srt[i * 3 + 2] = MPoint(untranslated.x + x, untranslated.y + y, untranslated.z + z);
	}
	//alignment in space
	else if (time <= explosion_duration + alignment_duration) {
		float x = (origin.x + explosion_radius * cos(angleOffset*expIdx));
		float y = (origin.y + explosion_radius * sin(angleOffset*expIdx));
		float z = origin.z;
		MPoint untranslated = srt[i * 3 + 2];
		MPoint currentPos = MPoint(untranslated.x + x, untranslated.y + y, untranslated.z + z);
		MPoint translation = translateBasedOnMobility(untranslated, mobility[expIdx]);
		MPoint dir = ((translation - currentPos) / alignment_duration) * (alignment_duration - (explosion_duration + alignment_duration - double(time)));
		srt[i * 3 + 2] = MPoint(currentPos.x + dir.x, currentPos.y + dir.y, currentPos.z + dir.z);
	}
	//interlocking parts in turn depending on order in lists 
	else {

		for (int k = 0; k < num_parts; k++) {

			int time_check = explosion_duration + alignment_duration + (k + 1) * part_interlock_duration;

			if (time <= time_check) {
				float x = (origin.x + explosion_radius * cos(angleOffset*expIdx));
				float y = (origin.y + explosion_radius * sin(angleOffset*expIdx));
				float z = origin.z;
				MPoint untranslated = srt[i * 3 + 2];
				MPoint currentPos = translateBasedOnMobility(untranslated, mobility[expIdx]);
				MPoint dir = ((untranslated - currentPos) / part_interlock_duration) * (part_interlock_duration - (time_check - double(time)));
				if (expIdx != k)
					dir = MPoint(0, 0, 0);
				if (expIdx < k)
					currentPos = untranslated;
				srt[i * 3 + 2] = MPoint(currentPos.x + dir.x, currentPos.y + dir.y, currentPos.z + dir.z);
				break;
			}
		}
	}
	return srt;

}


ConsoleTable::~ConsoleTable()
{
}