#include "InterlockerNode.h"
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMeshData.h>
#include <maya/MFnMesh.h>
#include <cube.h>
#include <consoletable.h>
#include <bedstand.h>
#include <sofa.h>
#include <shoerack.h>
#include <bookshelf.h>
#include <chair.h>
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
#include <joint.h>

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

		std::vector<MPointArray> allPoints;
		std::vector<MIntArray> allFaceCounts;
		std::vector<MIntArray> allFaceConnects;


		std::vector<MPointArray> allPointsJoints;
		std::vector<MIntArray> allFaceCountsJoints;
		std::vector<MIntArray> allFaceConnectsJoints;
		//for (int i = 0; i < 6; i++) {
		//	allPoints.push_back(MPointArray());
		//	allFaceCounts.push_back(MIntArray());
		//	allFaceConnects.push_back(MIntArray());
		//}

		MPointArray points;
		MIntArray faceCounts;
		MIntArray faceConnects;

		int currentTime = int(timeData.asTime().value());
		if (currentTime == 0) currentTime++;

		ConsoleTable table = ConsoleTable();
		std::vector<MPoint> transformations = table.updateTransformations(currentTime);

		std::vector<MPoint> jointTransformations = {
			MPoint(0.2,0.2,0.2), MPoint(0,0,0), MPoint(-1.1,0.5,0),  //(0,2)
			MPoint(0.2,0.2,0.2), MPoint(0,0,0), MPoint(-1.1,-0.8,0), //(0,1)
			MPoint(0.6,0.2,0.2), MPoint(0,0,0), MPoint(-1.5,1.4,0.0), // (0, 4) union

			MPoint(0.2,0.2,0.2), MPoint(0,0,0), MPoint(-1.45,-0.8,0), //(1,0)
			MPoint(0.2,0.2,0.4), MPoint(0,0,0), MPoint(1.5,-0.8,0.15),// (1,3)


			MPoint(0.2,0.2,0.2), MPoint(0,0,0), MPoint(-1.3,0.5,0),  //(2,0)
			MPoint(0.2,0.2,0.4), MPoint(0,0,0), MPoint(1.5,0.5,0.1),// (2,3)

			MPoint(0.2,0.2,0.4), MPoint(0,0,0), MPoint(1.5,-0.8,-0.3),// (3,1)
			MPoint(0.2,0.2,0.4), MPoint(0,0,0), MPoint(1.5,0.5,-0.3),// (3,2)
			MPoint(0.2,0.2,0.6), MPoint(0,0,0), MPoint(1.5,1.4,0.0),// (3,4) union

			MPoint(0.6,0.2,0.2), MPoint(0,0,0), MPoint(-1.5,1.4,0.0), // (4,0) diff
			MPoint(0.2,0.2,0.6), MPoint(0,0,0), MPoint(1.5,1.4,0.0)// (4,3) diff
		};


		std::vector<MPoint> updatedJointTransformations = table.updateJoints(currentTime, 0,0,
		{ jointTransformations[0],jointTransformations[1],jointTransformations[2] });
		std::vector<MPoint> updatedJointTransformations2 = table.updateJoints(currentTime, 0,0,
		{ jointTransformations[3],jointTransformations[4],jointTransformations[5] });
		std::vector<MPoint> updatedJointTransformations3 = table.updateJoints(currentTime, 0,0,
		{ jointTransformations[6],jointTransformations[7],jointTransformations[8] });

		std::vector<MPoint> updatedJointTransformations4 = table.updateJoints(currentTime, 0,1,
		{ jointTransformations[9],jointTransformations[10],jointTransformations[11] });
		std::vector<MPoint> updatedJointTransformations5 = table.updateJoints(currentTime, 0,1,
		{ jointTransformations[12],jointTransformations[13],jointTransformations[14] });

		std::vector<MPoint> updatedJointTransformations6 = table.updateJoints(currentTime, 0, 2,
		{ jointTransformations[15],jointTransformations[16],jointTransformations[17] });
		std::vector<MPoint> updatedJointTransformations7 = table.updateJoints(currentTime, 0, 2,
		{ jointTransformations[18],jointTransformations[19],jointTransformations[20] });

		std::vector<MPoint> updatedJointTransformations8 = table.updateJoints(currentTime, 0, 3,
		{ jointTransformations[21],jointTransformations[22],jointTransformations[23] });
		std::vector<MPoint> updatedJointTransformations9 = table.updateJoints(currentTime, 0, 3,
		{ jointTransformations[24],jointTransformations[25],jointTransformations[26] });
		std::vector<MPoint> updatedJointTransformations10 = table.updateJoints(currentTime, 0, 3,
		{ jointTransformations[27],jointTransformations[28],jointTransformations[29] });

		std::vector<MPoint> updatedJointTransformations11 = table.updateJoints(currentTime, 0, 4,
		{ jointTransformations[30],jointTransformations[31],jointTransformations[32] });
		std::vector<MPoint> updatedJointTransformations12 = table.updateJoints(currentTime, 0, 4,
		{ jointTransformations[33],jointTransformations[34],jointTransformations[35] });
	/*	std::vector<MPoint> updatedJointTransformationsAll;// = { updatedJointTransformations,
			//updatedJointTransformations2,updatedJointTransformations3,updatedJointTransformations4 };
		updatedJointTransformationsAll.insert(updatedJointTransformationsAll.end(), 
			updatedJointTransformations.begin(), updatedJointTransformations.end());
		updatedJointTransformationsAll.insert(updatedJointTransformationsAll.end(),
			updatedJointTransformations2.begin(), updatedJointTransformations2.end());
		updatedJointTransformationsAll.insert(updatedJointTransformationsAll.end(),
			updatedJointTransformations3.begin(), updatedJointTransformations3.end());
		updatedJointTransformationsAll.insert(updatedJointTransformationsAll.end(),
			updatedJointTransformations4.begin(), updatedJointTransformations4.end());*/

		std::vector<CubeMesh> parts;
		std::vector<MFnMesh*> meshParts;
		std::vector<MObject> meshObjects;

		std::vector<MFnMesh*> meshJoints;
		std::vector<MObject> meshJointsObjects;

		//meshParts.push_back(new MFnMesh());

		if (furnitureName == "") {
			//std::cout << "Creating Console Table..." << std::endl;

			for (unsigned int i = 0; i < transformations.size(); i += 3) {
				CubeMesh c = CubeMesh(transformations[i], transformations[i + 1], transformations[i + 2], timeData.asTime().value());
				parts.push_back(c);

				//c.appendToMesh(points, faceCounts, faceConnects);
				allPoints.push_back(MPointArray());
				allFaceCounts.push_back(MIntArray());
				allFaceConnects.push_back(MIntArray());
				int idx = i / 3;
				c.appendToMesh(allPoints[idx], allFaceCounts[idx], allFaceConnects[idx]);
				MFnMeshData* dataCreator1 = new MFnMeshData();
				MObject newOutputData1 = dataCreator1->create(&returnStatus);
				MFnMesh* part1 = new MFnMesh();
				part1->create(allPoints[idx].length(), allFaceCounts[idx].length(), allPoints[idx], allFaceCounts[idx], allFaceConnects[idx], newOutputData1, &returnStatus);
				meshParts.push_back(part1);
				meshObjects.push_back(newOutputData1);
			}

			/*for (int k = 0; k < 4; k++) {

				CubeMesh j1 = CubeMesh(updatedJointTransformationsAll[k*3],
					updatedJointTransformations[k*3+1],
					updatedJointTransformations[k*3+2],
					timeData.asTime().value());
				allPointsJoints.push_back(MPointArray());
				allFaceCountsJoints.push_back(MIntArray());
				allFaceConnectsJoints.push_back(MIntArray());
				j1.appendToMesh(allPointsJoints[k], allFaceCountsJoints[k], allFaceConnectsJoints[k]);
				MFnMeshData* dataCreator1 = new MFnMeshData();
				MObject newOutputData1 = dataCreator1->create(&returnStatus);
				MFnMesh* joint1 = new MFnMesh();
				joint1->create(allPointsJoints[k].length(), allFaceCountsJoints[k].length(),
					allPointsJoints[k], allFaceCountsJoints[k], allFaceConnectsJoints[k], newOutputData1, &returnStatus);
				meshJoints.push_back(joint1);
				meshJointsObjects.push_back(newOutputData1);


			}*/


			CubeMesh j1 = CubeMesh(updatedJointTransformations[0], 
				updatedJointTransformations[1],
				updatedJointTransformations[2],
				timeData.asTime().value());
			allPointsJoints.push_back(MPointArray());
			allFaceCountsJoints.push_back(MIntArray());
			allFaceConnectsJoints.push_back(MIntArray());
			j1.appendToMesh(allPointsJoints[0], allFaceCountsJoints[0], allFaceConnectsJoints[0]);
			MFnMeshData* dataCreator1 = new MFnMeshData();
			MObject newOutputData1 = dataCreator1->create(&returnStatus);
			MFnMesh* joint1 = new MFnMesh();
			joint1->create(allPointsJoints[0].length(), allFaceCountsJoints[0].length(),
			allPointsJoints[0], allFaceCountsJoints[0], allFaceConnectsJoints[0], newOutputData1, &returnStatus);
			meshJoints.push_back(joint1);
			meshJointsObjects.push_back(newOutputData1);



			CubeMesh j2 = CubeMesh(updatedJointTransformations2[0],
				updatedJointTransformations2[1],
				updatedJointTransformations2[2],
				timeData.asTime().value());
			allPointsJoints.push_back(MPointArray());
			allFaceCountsJoints.push_back(MIntArray());
			allFaceConnectsJoints.push_back(MIntArray());
			j2.appendToMesh(allPointsJoints[1], allFaceCountsJoints[1], allFaceConnectsJoints[1]);
			MFnMeshData* dataCreator2 = new MFnMeshData();
			MObject newOutputData2 = dataCreator2->create(&returnStatus);
			MFnMesh* joint2 = new MFnMesh();
			joint2->create(allPointsJoints[1].length(), allFaceCountsJoints[1].length(),
				allPointsJoints[1], allFaceCountsJoints[1], allFaceConnectsJoints[1], newOutputData2, &returnStatus);
			meshJoints.push_back(joint2);
			meshJointsObjects.push_back(newOutputData2);


			CubeMesh j3 = CubeMesh(updatedJointTransformations3[0],
				updatedJointTransformations3[1],
				updatedJointTransformations3[2],
				timeData.asTime().value());
			allPointsJoints.push_back(MPointArray());
			allFaceCountsJoints.push_back(MIntArray());
			allFaceConnectsJoints.push_back(MIntArray());
			j3.appendToMesh(allPointsJoints[2], allFaceCountsJoints[2], allFaceConnectsJoints[2]);
			MFnMeshData* dataCreator3 = new MFnMeshData();
			MObject newOutputData3 = dataCreator3->create(&returnStatus);
			MFnMesh* joint3 = new MFnMesh();
			joint3->create(allPointsJoints[2].length(), allFaceCountsJoints[2].length(),
				allPointsJoints[2], allFaceCountsJoints[2], allFaceConnectsJoints[2], newOutputData3, &returnStatus);
			meshJoints.push_back(joint3);
			meshJointsObjects.push_back(newOutputData3);


			CubeMesh j4 = CubeMesh(updatedJointTransformations4[0],
				updatedJointTransformations4[1],
				updatedJointTransformations4[2],
				timeData.asTime().value());
			allPointsJoints.push_back(MPointArray());
			allFaceCountsJoints.push_back(MIntArray());
			allFaceConnectsJoints.push_back(MIntArray());
			j4.appendToMesh(allPointsJoints[3], allFaceCountsJoints[3], allFaceConnectsJoints[3]);
			MFnMeshData* dataCreator4 = new MFnMeshData();
			MObject newOutputData4 = dataCreator4->create(&returnStatus);
			MFnMesh* joint4 = new MFnMesh();
			joint4->create(allPointsJoints[3].length(), allFaceCountsJoints[3].length(),
				allPointsJoints[3], allFaceCountsJoints[3], allFaceConnectsJoints[3], newOutputData4, &returnStatus);
			meshJoints.push_back(joint4);
			meshJointsObjects.push_back(newOutputData4);


			CubeMesh j5 = CubeMesh(updatedJointTransformations5[0],
				updatedJointTransformations5[1],
				updatedJointTransformations5[2],
				timeData.asTime().value());
			allPointsJoints.push_back(MPointArray());
			allFaceCountsJoints.push_back(MIntArray());
			allFaceConnectsJoints.push_back(MIntArray());
			j5.appendToMesh(allPointsJoints[4], allFaceCountsJoints[4], allFaceConnectsJoints[4]);
			MFnMeshData* dataCreator5 = new MFnMeshData();
			MObject newOutputData5 = dataCreator5->create(&returnStatus);
			MFnMesh* joint5 = new MFnMesh();
			joint5->create(allPointsJoints[4].length(), allFaceCountsJoints[4].length(),
				allPointsJoints[4], allFaceCountsJoints[4], allFaceConnectsJoints[4], newOutputData5, &returnStatus);
			meshJoints.push_back(joint5);
			meshJointsObjects.push_back(newOutputData5);


			CubeMesh j6 = CubeMesh(updatedJointTransformations6[0],
				updatedJointTransformations6[1],
				updatedJointTransformations6[2],
				timeData.asTime().value());
			allPointsJoints.push_back(MPointArray());
			allFaceCountsJoints.push_back(MIntArray());
			allFaceConnectsJoints.push_back(MIntArray());
			j6.appendToMesh(allPointsJoints[5], allFaceCountsJoints[5], allFaceConnectsJoints[5]);
			MFnMeshData* dataCreator6 = new MFnMeshData();
			MObject newOutputData6 = dataCreator6->create(&returnStatus);
			MFnMesh* joint6 = new MFnMesh();
			joint6->create(allPointsJoints[5].length(), allFaceCountsJoints[5].length(),
				allPointsJoints[5], allFaceCountsJoints[5], allFaceConnectsJoints[5], newOutputData6, &returnStatus);
			meshJoints.push_back(joint6);
			meshJointsObjects.push_back(newOutputData6);

			CubeMesh j7 = CubeMesh(updatedJointTransformations7[0],
				updatedJointTransformations7[1],
				updatedJointTransformations7[2],
				timeData.asTime().value());
			allPointsJoints.push_back(MPointArray());
			allFaceCountsJoints.push_back(MIntArray());
			allFaceConnectsJoints.push_back(MIntArray());
			j7.appendToMesh(allPointsJoints[6], allFaceCountsJoints[6], allFaceConnectsJoints[6]);
			MFnMeshData* dataCreator7 = new MFnMeshData();
			MObject newOutputData7 = dataCreator7->create(&returnStatus);
			MFnMesh* joint7 = new MFnMesh();
			joint7->create(allPointsJoints[6].length(), allFaceCountsJoints[6].length(),
				allPointsJoints[6], allFaceCountsJoints[6], allFaceConnectsJoints[6], newOutputData7, &returnStatus);
			meshJoints.push_back(joint7);
			meshJointsObjects.push_back(newOutputData7);

			CubeMesh j8 = CubeMesh(updatedJointTransformations8[0],
				updatedJointTransformations8[1],
				updatedJointTransformations8[2],
				timeData.asTime().value());
			allPointsJoints.push_back(MPointArray());
			allFaceCountsJoints.push_back(MIntArray());
			allFaceConnectsJoints.push_back(MIntArray());
			j8.appendToMesh(allPointsJoints[7], allFaceCountsJoints[7], allFaceConnectsJoints[7]);
			MFnMeshData* dataCreator8 = new MFnMeshData();
			MObject newOutputData8 = dataCreator8->create(&returnStatus);
			MFnMesh* joint8 = new MFnMesh();
			joint8->create(allPointsJoints[7].length(), allFaceCountsJoints[7].length(),
				allPointsJoints[7], allFaceCountsJoints[7], allFaceConnectsJoints[7], newOutputData8, &returnStatus);
			meshJoints.push_back(joint8);
			meshJointsObjects.push_back(newOutputData8);

			CubeMesh j9 = CubeMesh(updatedJointTransformations9[0],
				updatedJointTransformations9[1],
				updatedJointTransformations9[2],
				timeData.asTime().value());
			allPointsJoints.push_back(MPointArray());
			allFaceCountsJoints.push_back(MIntArray());
			allFaceConnectsJoints.push_back(MIntArray());
			j9.appendToMesh(allPointsJoints[8], allFaceCountsJoints[8], allFaceConnectsJoints[8]);
			MFnMeshData* dataCreator9 = new MFnMeshData();
			MObject newOutputData9 = dataCreator9->create(&returnStatus);
			MFnMesh* joint9 = new MFnMesh();
			joint9->create(allPointsJoints[8].length(), allFaceCountsJoints[8].length(),
				allPointsJoints[8], allFaceCountsJoints[8], allFaceConnectsJoints[8], newOutputData9, &returnStatus);
			meshJoints.push_back(joint9);
			meshJointsObjects.push_back(newOutputData9);

			CubeMesh j10 = CubeMesh(updatedJointTransformations10[0],
				updatedJointTransformations10[1],
				updatedJointTransformations10[2],
				timeData.asTime().value());
			allPointsJoints.push_back(MPointArray());
			allFaceCountsJoints.push_back(MIntArray());
			allFaceConnectsJoints.push_back(MIntArray());
			j10.appendToMesh(allPointsJoints[9], allFaceCountsJoints[9], allFaceConnectsJoints[9]);
			MFnMeshData* dataCreator10 = new MFnMeshData();
			MObject newOutputData10 = dataCreator10->create(&returnStatus);
			MFnMesh* joint10 = new MFnMesh();
			joint10->create(allPointsJoints[9].length(), allFaceCountsJoints[9].length(),
				allPointsJoints[9], allFaceCountsJoints[9], allFaceConnectsJoints[9], newOutputData10, &returnStatus);
			meshJoints.push_back(joint10);
			meshJointsObjects.push_back(newOutputData10);

			CubeMesh j11 = CubeMesh(updatedJointTransformations11[0],
				updatedJointTransformations11[1],
				updatedJointTransformations11[2],
				timeData.asTime().value());
			allPointsJoints.push_back(MPointArray());
			allFaceCountsJoints.push_back(MIntArray());
			allFaceConnectsJoints.push_back(MIntArray());
			j11.appendToMesh(allPointsJoints[10], allFaceCountsJoints[10], allFaceConnectsJoints[10]);
			MFnMeshData* dataCreator11 = new MFnMeshData();
			MObject newOutputData11 = dataCreator11->create(&returnStatus);
			MFnMesh* joint11 = new MFnMesh();
			joint11->create(allPointsJoints[10].length(), allFaceCountsJoints[10].length(),
				allPointsJoints[10], allFaceCountsJoints[10], allFaceConnectsJoints[10], newOutputData11, &returnStatus);
			meshJoints.push_back(joint11);
			meshJointsObjects.push_back(newOutputData11);

			CubeMesh j12 = CubeMesh(updatedJointTransformations12[0],
				updatedJointTransformations12[1],
				updatedJointTransformations12[2],
				timeData.asTime().value());
			allPointsJoints.push_back(MPointArray());
			allFaceCountsJoints.push_back(MIntArray());
			allFaceConnectsJoints.push_back(MIntArray());
			j12.appendToMesh(allPointsJoints[11], allFaceCountsJoints[11], allFaceConnectsJoints[11]);
			MFnMeshData* dataCreator12 = new MFnMeshData();
			MObject newOutputData12 = dataCreator12->create(&returnStatus);
			MFnMesh* joint12 = new MFnMesh();
			joint12->create(allPointsJoints[11].length(), allFaceCountsJoints[11].length(),
				allPointsJoints[11], allFaceCountsJoints[11], allFaceConnectsJoints[11], newOutputData12, &returnStatus);
			meshJoints.push_back(joint12);
			meshJointsObjects.push_back(newOutputData12);
		}

		//Empty mesh
		MFnMesh mesh;
		mesh.create(points.length(), faceCounts.length(), points, faceCounts, faceConnects, newOutputData, &returnStatus);
		meshJoints[0]->booleanOp(MFnMesh::BoolOperation::kUnion, *(meshJoints[0]), *(meshJoints[1]));
		mesh.booleanOp(MFnMesh::BoolOperation::kDifference, *(meshParts[0]), *(meshJoints[0]));
		mesh.booleanOp(MFnMesh::BoolOperation::kUnion, mesh, *(meshJoints[2]));


		meshJoints[3]->booleanOp(MFnMesh::BoolOperation::kUnion, *(meshJoints[3]), *(meshJoints[4]));
		meshParts[1]->booleanOp(MFnMesh::BoolOperation::kDifference, *(meshParts[1]), *(meshJoints[3]));
		//meshParts[1]->booleanOp(MFnMesh::BoolOperation::kDifference, *(meshParts[1]), *(meshJoints[4]));
		mesh.booleanOp(MFnMesh::BoolOperation::kUnion, mesh, *(meshParts[1]));

		meshJoints[5]->booleanOp(MFnMesh::BoolOperation::kUnion, *(meshJoints[5]), *(meshJoints[6]));
		meshParts[2]->booleanOp(MFnMesh::BoolOperation::kDifference, *(meshParts[2]), *(meshJoints[5]));
		mesh.booleanOp(MFnMesh::BoolOperation::kUnion, mesh, *(meshParts[2]));


		meshJoints[7]->booleanOp(MFnMesh::BoolOperation::kUnion, *(meshJoints[7]), *(meshJoints[8]));
		meshParts[3]->booleanOp(MFnMesh::BoolOperation::kDifference, *(meshParts[3]), *(meshJoints[7]));
		meshParts[3]->booleanOp(MFnMesh::BoolOperation::kUnion, *(meshParts[3]), *(meshJoints[9]));
		mesh.booleanOp(MFnMesh::BoolOperation::kUnion, mesh, *(meshParts[3]));


		meshJoints[10]->booleanOp(MFnMesh::BoolOperation::kUnion, *(meshJoints[10]), *(meshJoints[11]));
		meshParts[4]->booleanOp(MFnMesh::BoolOperation::kDifference, *(meshParts[4]), *(meshJoints[10]));
		mesh.booleanOp(MFnMesh::BoolOperation::kUnion, mesh, *(meshParts[4]));
		//mesh.booleanOp(MFnMesh::BoolOperation::kDifference, mesh, *(meshJoints[0]));
		//mesh.booleanOp(MFnMesh::BoolOperation::kDifference, mesh, *(meshJoints[1]));


		//part0 joint (0,1)
		//meshParts[0]->booleanOp(MFnMesh::BoolOperation::kDifference, *(meshParts[0]), *(meshParts[1]));

		//part1 joint (1,0)
		//meshParts[1]->booleanOp(MFnMesh::BoolOperation::kDifference, *(meshParts[1]), *(meshParts[0]));

		//part0 joint (0,2)
		//meshParts[0]->booleanOp(MFnMesh::BoolOperation::kDifference, *(meshParts[0]), *(meshParts[2]));

		//part2 joint (2,0)
		//meshParts[2]->booleanOp(MFnMesh::BoolOperation::kDifference, *(meshParts[2]), *(meshParts[0]));



		//mesh.booleanOp(MFnMesh::BoolOperation::kUnion, *(meshParts[0]), *(meshParts[1]));
		//mesh.booleanOp(MFnMesh::BoolOperation::kUnion, mesh, *(meshParts[0]));


		mesh.setObject(newOutputData);


		outputHandle.set(newOutputData);
		data.setClean(plug);
	}

	return returnStatus;
}