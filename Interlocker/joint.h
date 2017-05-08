#pragma once

#include "cube.h"
#include "glm\glm.hpp"
#include <vector>
#include "maya\MObject.h"

enum State
{
	Inside,
	Common,
	Outside
};

class Joint
{
public:

	CubeMesh A;
	CubeMesh B;

	std::vector<State> icoVector;

	Joint(CubeMesh A, CubeMesh B);

	MObject createBoolMesh(MObject meshA, MObject meshB, MObject& outData);
	~Joint();
};

