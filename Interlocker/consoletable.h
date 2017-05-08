#pragma once

#include <maya/MPoint.h>
#include <maya/MPointArray.h>
#include <maya/MVector.h>
#include <maya/MVectorArray.h>
#include <maya/MIntArray.h>
#include <maya/MDoubleArray.h>
#include <furniture.h>

class ConsoleTable : public Furniture
{
public:
	ConsoleTable();
	~ConsoleTable();

	std::vector<MPoint> updateJoints(int time, int part, int k, std::vector<MPoint> srt);
};

