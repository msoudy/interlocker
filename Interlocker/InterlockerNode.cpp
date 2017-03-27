#include "InterlockerNode.h"
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMeshData.h>
#include <maya/MFnMesh.h>
#include <iostream>

#define McheckErr(stat,msg)             \
        if ( MS::kSuccess != stat ) {   \
                cerr << msg;            \
                return MS::kFailure;    \
        }

MTypeId InterlockerNode::id;
MObject InterlockerNode::time;
MObject InterlockerNode::scale;
MObject InterlockerNode::outputMesh;

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

	InterlockerNode::outputMesh = typedAttr.create("outputMesh", "out",
		MFnData::kMesh,
		&returnStatus);
	McheckErr(returnStatus, "ERROR creating geometry output attribute\n");
	typedAttr.setStorable(false);

	returnStatus = addAttribute(InterlockerNode::time);
	McheckErr(returnStatus, "ERROR adding time attribute\n");

	returnStatus = addAttribute(InterlockerNode::scale);
	McheckErr(returnStatus, "ERROR adding scale attribute\n");

	returnStatus = addAttribute(InterlockerNode::outputMesh);
	McheckErr(returnStatus, "ERROR adding outputMesh attribute\n");

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

		MDataHandle outputHandle = data.outputValue(outputMesh, &returnStatus);
		McheckErr(returnStatus, "ERROR getting polygon data handle\n");

		MFnMeshData dataCreator;
		MObject newOutputData = dataCreator.create(&returnStatus);
		McheckErr(returnStatus, "ERROR creating outputData");


		std::cout << scaleData.asFloat() << std::endl;

		outputHandle.set(newOutputData);
		data.setClean(plug);
	}

	return returnStatus;
}