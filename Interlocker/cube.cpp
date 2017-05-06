#include "cube.h"
#include <maya/MMatrix.h>
#include <math.h>

MPointArray CubeMesh::gPoints;
MVectorArray CubeMesh::gNormals;
MIntArray CubeMesh::gFaceCounts;
MIntArray CubeMesh::gFaceConnects;

CubeMesh::CubeMesh(MPoint s, MPoint r, MPoint tr, const int& t) : scale(s), rotation(r), translation(tr), time(t), min(1000), max(-1000)
{
	//if (gPoints.length() == 0)
	//{
	initCubeMesh();
	setMinMax();
	//}
}


CubeMesh::~CubeMesh()
{
}

void CubeMesh::getMesh(MPointArray & points, MIntArray & faceCounts, MIntArray & faceConnects)
{
	MVectorArray cnormals;
	transform(points, cnormals);
	faceCounts = gFaceCounts;
	faceConnects = gFaceConnects;
}

void CubeMesh::appendToMesh(MPointArray & points, MIntArray & faceCounts, MIntArray & faceConnects)
{
	MPointArray cpoints;
	MVectorArray cnormals;
	transform(cpoints, cnormals);

	int startIndex = points.length(); // offset for indexes
	for (unsigned int i = 0; i < cpoints.length(); i++)
	{
		points.append(cpoints[i]);
	}
	for (unsigned int i = 0; i < gFaceCounts.length(); i++)
	{
		faceCounts.append(gFaceCounts[i]);
	}

	for (unsigned int i = 0; i < gFaceConnects.length(); i++)
	{
		faceConnects.append(gFaceConnects[i] + startIndex);
	}
}

MMatrix CubeMesh::rotateBy(float angle, float x, float y, float z)
{
	float angleRadians = (angle * M_PI) / 180;
	float s = sin(angleRadians);
	float c = cos(angleRadians);
	float c1 = 1 - c;
	glm::vec4 n = glm::normalize(glm::vec4(x, y, z, 0));

	MVector vec0 = MVector(c + n[0] * n[0] * c1, n[2] * s + n[0] * n[1] * c1, -n[1] * s + n[0] * n[2] * c1);
	MVector vec1 = MVector(-n[2] * s + n[0] * n[1] * c1, c + n[1] * n[1] * c1, n[0] * s + n[1] * n[2] * c1);
	MVector vec2 = MVector(n[1] * s + n[0] * n[2] * c1, -n[0] * s + n[1] * n[2] * c1, c + n[2] * n[2] * c1);

	MMatrix rot;
	rot[0][0] = vec0[0];   rot[0][1] = vec0[1]; rot[0][2] = vec0[2]; rot[0][3] = 0;
	rot[1][0] = vec1[0];   rot[1][1] = vec1[1]; rot[1][2] = vec1[2]; rot[1][3] = 0;
	rot[2][0] = vec2[0];   rot[2][1] = vec2[1]; rot[2][2] = vec2[2]; rot[2][3] = 0;
	rot[3][0] = 0;            rot[3][1] = 0;       rot[3][2] = 0;     rot[3][3] = 1;

	return rot.transpose();
}

MMatrix CubeMesh::translateBy(float x, float y, float z)
{
	MMatrix translate;
	translate[0][0] = 1;   translate[0][1] = 0; translate[0][2] = 0; translate[0][3] = x;
	translate[1][0] = 0;   translate[1][1] = 1; translate[1][2] = 0; translate[1][3] = y;
	translate[2][0] = 0;   translate[2][1] = 0; translate[2][2] = 1; translate[2][3] = z;
	translate[3][0] = 0;   translate[3][1] = 0; translate[3][2] = 0; translate[3][3] = 1;
	return translate.transpose();
}

MMatrix CubeMesh::scaleBy(float x, float y, float z)
{
	MMatrix scale;
	scale[0][0] = x;   scale[0][1] = 0; scale[0][2] = 0; scale[0][3] = 0;
	scale[1][0] = 0;   scale[1][1] = y; scale[1][2] = 0; scale[1][3] = 0;
	scale[2][0] = 0;   scale[2][1] = 0; scale[2][2] = z; scale[2][3] = 0;
	scale[3][0] = 0;   scale[3][1] = 0; scale[3][2] = 0; scale[3][3] = 1;
	return scale.transpose();
}

void CubeMesh::transform(MPointArray & points, MVectorArray & normals)
{

	MMatrix rotX = rotateBy(rotation.x, 1, 0, 0);
	MMatrix rotY = rotateBy(rotation.y, 0, 1, 0);
	MMatrix rotZ = rotateBy(rotation.z, 0, 0, 1);
	MMatrix sca = scaleBy(scale.x, scale.y, scale.z);
	MMatrix tra = translateBy(translation.x, translation.y, translation.z);

	for (unsigned int i = 0; i < gPoints.length(); i++)
	{
		MPoint p = gPoints[i];
		p = p * sca * rotX * rotY * rotZ * tra;
		points.append(p);

		MVector n = gNormals[i] * sca * rotX * rotY * rotZ * tra;
		normals.append(n);
		normals.append(gNormals[i]);
	}
}

void CubeMesh::setMinMax()
{
	MPointArray points;
	MVectorArray cnormals;
	transform(points, cnormals);

	for (unsigned int i = 0; i < points.length(); i++)
	{
		glm::vec3 p = glm::vec3(points[i].x, points[i].y, points[i].z);
		min = glm::min(min, p);
		max = glm::max(max, p);
	}
}


void CubeMesh::initCubeMesh()
{
	// Add points and normals
	gPoints.clear();
	gNormals.clear();
	gFaceCounts.clear();
	gFaceConnects.clear();
	const double normal_value = 0.5775;
	double cube_size = 0.5;

	gPoints.append(MPoint(-cube_size, -cube_size, -cube_size));
	gPoints.append(MPoint(cube_size, -cube_size, -cube_size));
	gPoints.append(MPoint(cube_size, -cube_size, cube_size));
	gPoints.append(MPoint(-cube_size, -cube_size, cube_size));
	gPoints.append(MPoint(-cube_size, cube_size, -cube_size));
	gPoints.append(MPoint(-cube_size, cube_size, cube_size));
	gPoints.append(MPoint(cube_size, cube_size, cube_size));
	gPoints.append(MPoint(cube_size, cube_size, -cube_size));

	gNormals.append(MVector(-normal_value, -normal_value, -normal_value));
	gNormals.append(MVector(normal_value, -normal_value, -normal_value));
	gNormals.append(MVector(normal_value, -normal_value, normal_value));
	gNormals.append(MVector(-normal_value, -normal_value, normal_value));
	gNormals.append(MVector(-normal_value, normal_value, -normal_value));
	gNormals.append(MVector(-normal_value, normal_value, normal_value));
	gNormals.append(MVector(normal_value, normal_value, normal_value));
	gNormals.append(MVector(normal_value, normal_value, -normal_value));

	gFaceCounts.append(4);
	gFaceCounts.append(4);
	gFaceCounts.append(4);
	gFaceCounts.append(4);
	gFaceCounts.append(4);
	gFaceCounts.append(4);

	int face_connects[24] = { 0, 1, 2, 3,
		4, 5, 6, 7,
		3, 2, 6, 5,
		0, 3, 5, 4,
		0, 4, 7, 1,
		1, 7, 6, 2 };

	for (int i = 0; i<24; i++)
	{
		gFaceConnects.append(face_connects[i]);
	}
}