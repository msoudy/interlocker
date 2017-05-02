#include "furniture.h"


// git pull request testing

Furniture::Furniture(int furniture_id, MPoint o, float radius) : id(furniture_id), origin(o), explosion_radius(radius)
{
}


Furniture::~Furniture()
{
}

MPoint Furniture::translateBasedOnMobility(MPoint p, Mobility m) {

	float offset = 2.0;
	MPoint p2 = p;
	switch (m) {
	case X_PLUS:
		p2 = MPoint(p.x - offset, p.y, p.z);
		break;
	case X_MINUS:
		p2 = MPoint(p.x + offset, p.y, p.z);
		break;
	case Y_PLUS:
		p2 = MPoint(p.x, p.y - offset, p.z);
		break;
	case Y_MINUS:
		p2 = MPoint(p.x, p.y + offset, p.z);
		break;
	case Z_PLUS:
		p2 = MPoint(p.x, p.y, p.z - offset);
		break;
	case Z_MINUS:
		p2 = MPoint(p.x, p.y, p.z + offset);
		break;
	default:
		p2 = p;
		break;
	}

	return p2;
}

std::vector<MPoint> Furniture::updateTransformations(int time)
{
	for (int i = 0; i < num_parts; i++) {

		//initial explosion
		if (time <= explosion_duration) {
			float x = (origin.x + explosion_radius * cos(angleOffset*i)) * (float(time - 1) / explosion_duration);
			float y = (origin.y + explosion_radius * sin(angleOffset*i)) * (float(time - 1) / explosion_duration);
			float z = origin.z * (float(time - 1) / explosion_duration);
			MPoint untranslated = transformations[i * 3 + 2];
			transformations[i * 3 + 2] = MPoint(untranslated.x + x, untranslated.y + y, untranslated.z + z);
		}
		//alignment in space
		else if (time <= explosion_duration + alignment_duration) {
			float x = (origin.x + explosion_radius * cos(angleOffset*i));
			float y = (origin.y + explosion_radius * sin(angleOffset*i));
			float z = origin.z;
			MPoint untranslated = transformations[i * 3 + 2];
			MPoint currentPos = MPoint(untranslated.x + x, untranslated.y + y, untranslated.z + z);
			MPoint translation = translateBasedOnMobility(untranslated, mobility[i]);
			MPoint dir = ((translation - currentPos) / alignment_duration) * (alignment_duration - (explosion_duration + alignment_duration - double(time)));
			transformations[i * 3 + 2] = MPoint(currentPos.x + dir.x, currentPos.y + dir.y, currentPos.z + dir.z);
		}
		//interlocking parts in turn depending on order in lists 
		else {

			for (int k = 0; k < num_parts; k++) {

				int time_check = explosion_duration + alignment_duration + (k + 1) * part_interlock_duration;

				if (time <= time_check) {
					float x = (origin.x + explosion_radius * cos(angleOffset*i));
					float y = (origin.y + explosion_radius * sin(angleOffset*i));
					float z = origin.z;
					MPoint untranslated = transformations[i * 3 + 2];
					MPoint currentPos = translateBasedOnMobility(untranslated, mobility[i]);
					MPoint dir = ((untranslated - currentPos) / part_interlock_duration) * (part_interlock_duration - (time_check - double(time)));
					if (i != k)
						dir = MPoint(0, 0, 0);
					if (i < k)
						currentPos = untranslated;
					transformations[i * 3 + 2] = MPoint(currentPos.x + dir.x, currentPos.y + dir.y, currentPos.z + dir.z);
					break;
				}
			}
		}
	}
	return transformations;
}