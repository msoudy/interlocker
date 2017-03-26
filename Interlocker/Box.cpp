#include "Box.h"
#include <string>

int Box::newUID = 0;

Box::Box() : uid(newUID++), position(glm::vec3(0)), scale(glm::vec3(0)), rotation(glm::vec3(0))
{
}


Box::~Box()
{
}

void Box::setPosition(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
}

void Box::setRotation(float x, float y, float z)
{
	rotation = glm::vec3(x, y, z);
}

void Box::setScale(float x, float y, float z)
{
	scale = glm::vec3(x, y, z);
}

MString Box::toMelCmd()
{
	//MString cmd = "polyCube -width 0.2 -height 0.7 -depth 0.8 -n part6; rotate 0 0 0 part6; move -1 -1.15 -0.15 part6;";
	std::string posx = std::to_string(position.x);
	std::string posy = std::to_string(position.y);
	std::string posz = std::to_string(position.z);
	std::string rotx = std::to_string(rotation.x);
	std::string roty = std::to_string(rotation.y);
	std::string rotz = std::to_string(rotation.z);
	std::string scax = std::to_string(scale.x);
	std::string scay = std::to_string(scale.y);
	std::string scaz = std::to_string(scale.z);
	std::string name = "part" + std::to_string(uid);
	std::string cmd = "polyCube -width " + scax + " -height " + scay + " -depth " + scaz + " -n " + name + ";"
		+ " rotate " + rotx + " " + roty + " " + rotz + " " + name + ";"
		+ " move " + posx + " " + posy + " " + posz + " " + name + ";";
	return cmd.c_str();
}