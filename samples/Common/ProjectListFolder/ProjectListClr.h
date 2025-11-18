//
// (C) Copyright 2009-2012 by Autodesk, Inc.
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted,
// provided that the above copyright notice appears in all copies and
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC.
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//- ProjectListClr.h : Access to the managed Project class
//-----------------------------------------------------------------------------


// Utility function returns true of the active drawing is contained in the current project
bool PnPEditingActiveProject();


// PnPProject - Project blind wrapper.
//
// The purpose of PnPProject is to allow non-CLI code to exchange and manage the lifetime of a
// Project (Autodesk::ProcessPower::ProjectManager) CLR object.
//
// PnPProject contains a GCHandle to a managed PnPProject object.  It is implemented using the
// facilities of System::Runtime::InteropServices::GCHandle in a manner similar to a gcroot object.
//
// PnPProject is not intended to be an unmanaged wrapper to the managed Project object.
//
class PnPProject
{
public:
	PnPProject(); //Uses the Current Project
    virtual ~PnPProject();

	//Methods
	bool IsLoaded();
	void List();
	//Add additional methods here...

protected:
	void* m_pProjectGCHandle;
};



//end
