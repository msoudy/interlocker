#pragma once

#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include "glm\glm.hpp"
#include <maya/MString.h>

class Box
{	 
private:
	static int newUID;
	const int uid;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
public:
	Box();
	~Box();

	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);
	MString toMelCmd();
};

