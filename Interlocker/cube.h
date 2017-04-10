#pragma once

#include <maya/MPoint.h>
#include <maya/MPoint.h>
#include <maya/MPointArray.h>
#include <maya/MVector.h>
#include <maya/MVectorArray.h>
#include <maya/MIntArray.h>
#include <maya/MDoubleArray.h>


class CubeMesh
{
public:
	CubeMesh(MPoint scale, MPoint rotation, MPoint translation, const int& time);
	~CubeMesh();

	void getMesh(
		MPointArray& points,
		MIntArray& faceCounts,
		MIntArray& faceConnects);

	void appendToMesh(
		MPointArray& points,
		MIntArray& faceCounts,
		MIntArray& faceConnects);

	MMatrix rotateBy(float angle, float x, float y, float z);
	MMatrix translateBy(float x, float y, float z);
	MMatrix scaleBy(float x, float y, float z);

protected:
	void transform(MPointArray& points, MVectorArray& normals);
	MPoint scale;
	MPoint rotation;
	MPoint translation;
	int time;

	void initCubeMesh();
	static MPointArray gPoints;
	static MVectorArray gNormals;
	static MIntArray gFaceCounts;
	static MIntArray gFaceConnects;
};

