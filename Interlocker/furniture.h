#pragma once
#include "maya/MPoint.h";
#include "vector";

enum Mobility {
	NONE = 0,
	X_PLUS = 1 << 0,
	X_MINUS = 1 << 1,
	Y_PLUS = 1 << 2,
	Y_MINUS = 1 << 3,
	Z_PLUS = 1 << 4,
	Z_MINUS = 1 << 5,
	ALL = X_PLUS | X_MINUS | Y_PLUS | Y_MINUS | Z_PLUS | Z_MINUS
};

class Furniture
{
public:
	Furniture(int id, MPoint origin, float explosion_radius);
	~Furniture();

	int id;
	MPoint origin;
	float explosion_radius;

	int num_parts;
	float angleOffset;
	int explosion_duration;
	int alignment_duration;
	int part_interlock_duration;
	std::vector<MPoint> transformations;
	std::vector<Mobility> mobility;
	std::vector<MPoint> jointTransformations;


	MPoint translateBasedOnMobility(MPoint p, Mobility m);
	std::vector<MPoint> updateTransformations(int time);
;};

