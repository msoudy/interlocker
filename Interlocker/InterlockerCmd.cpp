//
// Copyright (C) 
// 
// File: InterlockerCmd.cpp
//
// MEL Command: Interlocker
//
// Author: Maya Plug-in Wizard 2.0
//

// Includes everything needed to register a simple MEL command with Maya.
// 
#include <maya/MSimple.h>
#include <maya/MFnPlugin.h>
#include <maya/MArgList.h>
#include <maya/MObject.h>
#include <maya/MGlobal.h>
#include <maya/MPxCommand.h>
#include <maya/MSyntax.h>
#include <maya/MArgDatabase.h>
#include "PartsGraph.h"
#include <iostream>

// Use helper macro to register a command with Maya.  It creates and
// registers a command that does not support undo or redo.  The 
// created class derives off of MPxCommand.
//
//DeclareSimpleCommand( Interlocker, "", "2015");

const char* longFurniture = "-furniture";
const char* furniture = "-f";
const char* longId = "-userid";
const char* id = "-i";


class interlocker : public MPxCommand
{
public:
	virtual MStatus doIt(const MArgList& args)
	{
		MSyntax syntax;
		syntax.addFlag(id, longId, MSyntax::kUnsigned);
		syntax.addFlag(furniture, longFurniture, MSyntax::kString);

		MStatus stat;
		MArgDatabase parser(syntax, args, &stat);

		int idVal = 0;
		MString nameVal = "";

		if (parser.isFlagSet(furniture))
			parser.getFlagArgument(furniture, 0, nameVal);

		if (parser.isFlagSet(id))
			parser.getFlagArgument(id, 0, idVal);

		MString box = "confirmDialog -title \"Interlocker\" -message \"Furniture: ";
		box += nameVal;
		box += "\\nID: ";
		if (parser.isFlagSet(id))
			box += idVal;
		box += "\" -button \"OK\" -defaultButton \"OK\";";

		MString commands;

		if (nameVal == "Console Table") {
			string part1 = "polyCube -width 0.2 -height 4.0 -depth 1.5 -n part1; rotate 0 0 90deg part1; move 0 1.5 0 part1;";
			string part2 = "polyCube -width 0.2 -height 3.0 -depth 1.0 -n part2; move 1.5 0 0 part2;";
			string part3 = "polyCube -width 0.2 -height 3.2 -depth 1.0 -n part3; rotate 0 0 90deg part3; move 0.2 0.5 -0.2 part3;";
			string part4 = "polyCube -width 0.2 -height 3.5 -depth 1.1 -n part4; rotate 0 0 90deg part4; move 0.2 -0.8 -0.2 part4;";
			string part5 = "polyCube -width 0.2 -height 3.0 -depth 1.0 -n part5; rotate 0 90deg 0 part5; move -1.5 0 0 part5;";
			string part6 = "polyCube -width 0.2 -height 0.7 -depth 0.8 -n part6; rotate 0 0 0 part6; move -1 -1.15 -0.15 part6;";

			commands += part1.c_str();
			commands += part2.c_str();
			commands += part3.c_str();
			commands += part4.c_str();
			commands += part5.c_str();
			commands += part6.c_str();
		}

		MStatus status = MGlobal::executeCommand(commands);
		const MStatus failed = MS::kFailure;
		const MStatus success = MS::kSuccess;
		if (status == failed)
		{
			MGlobal::displayError("error");
			return MS::kFailure;
		}
		if (status == success)
			return MStatus::kSuccess;
	}
	static void *creator() { return new interlocker; }
};

MStatus initializePlugin(MObject obj)
//
//	Description:
//		this method is called when the plug-in is loaded into Maya.  It 
//		registers all of the services that this plug-in provides with 
//		Maya.
//
//	Arguments:
//		obj - a handle to the plug-in object (use MFnPlugin to access it)
//
{
	MStatus stat;
	MFnPlugin plugin(obj, "CIS660", "1.0", "Any");
	stat = plugin.registerCommand("Interlocker", interlocker::creator);
	if (!stat) stat.perror("registerCommand failed");


	char buffer[2048];
	MString s = plugin.loadPath();
	sprintf_s(buffer, 2048, "source \"%s/../InterlockerCmd.mel\";", s.asChar());
	MGlobal::executeCommand(buffer, true);

	return stat;
}

MStatus uninitializePlugin(MObject obj)
//
//	Description:
//		this method is called when the plug-in is unloaded from Maya. It 
//		deregisters all of the services that it was providing.
//
//	Arguments:
//		obj - a handle to the plug-in object (use MFnPlugin to access it)
//
{
	/*MStatus   status;
	MFnPlugin plugin( obj );

	// Add plug-in feature deregistration here
	//

	return status;*/
	MStatus stat;
	MFnPlugin plugin(obj);
	stat = plugin.deregisterCommand("Interlocker");
	if (!stat) stat.perror("deregisterCommand failed");
	return stat;
}