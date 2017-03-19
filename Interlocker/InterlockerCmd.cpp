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

const char* longName = "-name";
const char* name = "-n";
const char* longId = "-userid";
const char* id = "-i";


class interlocker : public MPxCommand
{
public:
	virtual MStatus doIt(const MArgList& args)
	{
		MSyntax syntax;
		syntax.addFlag(id, longId, MSyntax::kUnsigned);
		syntax.addFlag(name, longName, MSyntax::kString);

		MStatus stat;
		MArgDatabase parser(syntax, args, &stat);

		int idVal = 0;
		MString nameVal = "";

		if (parser.isFlagSet(name))
			parser.getFlagArgument(name, 0, nameVal);

		if (parser.isFlagSet(id))
			parser.getFlagArgument(id, 0, idVal);

		MString box = "confirmDialog -title \"Interlocker\" -message \"Name: ";
		box += nameVal;
		box += "\\nID: ";
		if (parser.isFlagSet(id))
			box += idVal;
		box += "\" -button \"OK\" -defaultButton \"OK\";";

		MStatus status = MGlobal::executeCommand(box);
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
	/*MStatus   status;
	MFnPlugin plugin( obj, "", "2015", "Any");

	// Add plug-in feature registration here
	//

	return status;*/
	MStatus stat;
	MFnPlugin plugin(obj, "CIS660", "1.0", "Any");
	stat = plugin.registerCommand("interlocker", interlocker::creator);
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
	stat = plugin.deregisterCommand("interlocker");
	if (!stat) stat.perror("deregisterCommand failed");
	return stat;
}