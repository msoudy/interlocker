#include "joint.h"
#include <iostream>


State getStateMax(float a, float b) {

	if (a < b)
		return Inside;
	else if (a > b)
		return Outside;
	else
		return Common;
}

State getStateMin(float a, float b) {

	if (a > b)
		return Inside;
	else if (a < b)
		return Outside;
	else
		return Common;
}

Joint::Joint(CubeMesh AA, CubeMesh BB) : A(AA), B(BB)
{

	//std::cout << "min : " << A.min.x << " " << A.min.y << " " << A.min.z << std::endl;
	//std::cout << "max : " << A.max.x << " " << A.max.y << " " << A.max.z << std::endl;

	//std::cout << "min : " << B.min.x << " " << B.min.y << " " << B.min.z << std::endl;
	//std::cout << "max : " << B.max.x << " " << B.max.y << " " << B.max.z << std::endl;

	icoVector.push_back(getStateMax(A.max.x, B.max.x));
	icoVector.push_back(getStateMin(A.min.x, B.min.x));
	icoVector.push_back(getStateMax(A.max.y, B.max.y));
	icoVector.push_back(getStateMin(A.min.y, B.min.y));
	icoVector.push_back(getStateMax(A.max.z, B.max.z));
	icoVector.push_back(getStateMin(A.min.z, B.min.z));
}

Joint::~Joint()
{
}
