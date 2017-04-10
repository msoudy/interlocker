#include "InterlockerNode.h"
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMeshData.h>
#include <maya/MFnMesh.h>
#include <cube.h>
#include <cylinder.h>
#include <consoletable.h>
#include <iostream>
#include <maya/MGlobal.h>
#include <maya/MTime.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MFnTransform.h>
#include <cmath>
#include "glm\glm.hpp"
#include <maya\MMatrix.h>
#include <maya/MBoundingBox.h>
#include <maya/MDagPath.h>
#include <maya/MSelectionList.h>
#include <math.h>

#define McheckErr(stat,msg)             \
        if ( MS::kSuccess != stat ) {   \
                cerr << msg;            \
                return MS::kFailure;    \
        }

MTypeId InterlockerNode::id;
MObject InterlockerNode::time;
MObject InterlockerNode::scale;
MObject InterlockerNode::outputMesh;
MObject InterlockerNode::furniture;

InterlockerNode::InterlockerNode()
{
}


InterlockerNode::~InterlockerNode()
{
}


void* InterlockerNode::creator()
{
	return new InterlockerNode;
}

MStatus InterlockerNode::initialize()
{

	MFnUnitAttribute unitAttr;
	MFnTypedAttribute typedAttr;
	MFnNumericAttribute numAttr;
	MStatus returnStatus;

	InterlockerNode::scale = numAttr.create("scale", "s",
		MFnNumericData::kFloat,
		0.0, &returnStatus);
	McheckErr(returnStatus, "ERROR creating scale attribute\n");
	numAttr.setMin(1);
	numAttr.setMax(10);

	InterlockerNode::time = unitAttr.create("time", "t",
		MFnUnitAttribute::kTime,
		0.0, &returnStatus);
	McheckErr(returnStatus, "ERROR creating time attribute\n");
	unitAttr.setMin(0);
	unitAttr.setMax(10);

	InterlockerNode::furniture = typedAttr.create("furniture", "f",
		MFnData::kString,
		&returnStatus);
	McheckErr(returnStatus, "ERROR creating furniture attribute\n");
	typedAttr.setStorable(false);

	InterlockerNode::outputMesh = typedAttr.create("outputMesh", "out",
		MFnData::kMesh,
		&returnStatus);
	McheckErr(returnStatus, "ERROR creating geometry output attribute\n");
	typedAttr.setStorable(false);

	returnStatus = addAttribute(InterlockerNode::time);
	McheckErr(returnStatus, "ERROR adding time attribute\n");

	returnStatus = addAttribute(InterlockerNode::scale);
	McheckErr(returnStatus, "ERROR adding scale attribute\n");

	returnStatus = addAttribute(InterlockerNode::furniture);
	McheckErr(returnStatus, "ERROR adding furniture attribute\n");

	returnStatus = addAttribute(InterlockerNode::outputMesh);
	McheckErr(returnStatus, "ERROR adding outputMesh attribute\n");

	returnStatus = attributeAffects(InterlockerNode::furniture, InterlockerNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects\n");
	returnStatus = attributeAffects(InterlockerNode::time, InterlockerNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects\n");
	returnStatus = attributeAffects(InterlockerNode::scale, InterlockerNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects\n");

	return returnStatus;
}

MStatus InterlockerNode::compute(const MPlug& plug, MDataBlock& data)

{
	MStatus returnStatus;

	if (plug == outputMesh) {
		MDataHandle timeData = data.inputValue(time, &returnStatus);
		McheckErr(returnStatus, "Error getting time data handle\n");

		MDataHandle scaleData = data.inputValue(scale, &returnStatus);
		McheckErr(returnStatus, "Error getting step data handle\n");

		MDataHandle furnitureData = data.inputValue(furniture, &returnStatus);
		McheckErr(returnStatus, "Error getting furniture data handle\n");

		MDataHandle outputHandle = data.outputValue(outputMesh, &returnStatus);
		McheckErr(returnStatus, "ERROR getting polygon data handle\n");

		MFnMeshData dataCreator;
		MObject newOutputData = dataCreator.create(&returnStatus);
		McheckErr(returnStatus, "ERROR creating outputData");

		//std::cout << int(timeData.asTime().value()) << std::endl;

		MString furnitureName = furnitureData.asString();

		MPointArray points;
		MIntArray faceCounts;
		MIntArray faceConnects;

		int currentTime = int(timeData.asTime().value());
		if (currentTime == 0) currentTime++;

		ConsoleTable table = ConsoleTable();
		std::vector<MPoint> transformations = table.updateTransformations(currentTime);

		if (furnitureName == "Console Table") {
			std::cout << "Creating Console Table..." << std::endl;

			for (unsigned int i = 0; i < transformations.size(); i += 3) {
				CubeMesh c = CubeMesh(transformations[i], transformations[i + 1], transformations[i + 2], timeData.asTime().value());
				c.appendToMesh(points, faceCounts, faceConnects);
			}

		}

		MFnMesh mesh;
		mesh.create(points.length(), faceCounts.length(), points, faceCounts, faceConnects, newOutputData, &returnStatus);


		outputHandle.set(newOutputData);
		data.setClean(plug);
	}

	return returnStatus;
}