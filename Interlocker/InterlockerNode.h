#pragma once
#include "maya\MPxNode.h"
class InterlockerNode :
	public MPxNode
{
public:
	InterlockerNode();
	~InterlockerNode();

	virtual MStatus compute(const MPlug& plug, MDataBlock& data);
	static  void* creator();
	static MStatus initialize();
	static MTypeId  id;

	static MObject time;
	static MObject scale;
	static MObject outputMesh;
	static MString path;
};

