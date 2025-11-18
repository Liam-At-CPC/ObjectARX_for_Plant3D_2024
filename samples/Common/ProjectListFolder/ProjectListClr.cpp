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
//- ProjectListClr.cpp : Access to the managed Project class
//- compile with: /clr
//-----------------------------------------------------------------------------
#include "stdafx.h"
#include "ProjectListClr.h"


//System
using namespace System::Collections::Generic;
#using <System.Xml.dll>
using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

//AutoCAD
//acdbmgd.dll
using namespace Autodesk::AutoCAD::DatabaseServices;

//ProcessPower
#using <PnPProjectManagerMgd.dll>
using namespace Autodesk::ProcessPower::ProjectManager;
using namespace Autodesk::ProcessPower::PlantInstance;


//Utility to check if active drawing is in the current project
bool PnPEditingActiveProject()
{
	//Current Project
	if (!PlantApplication::CurrentProject) return false;

	Project^ pProject = PlantApplication::CurrentProject->ProjectParts[L"PnId"];
	if (!pProject) return false;

	//Active Drawing
	AcDbDatabase *pDbDwg = acdbHostApplicationServices()->workingDatabase();
	if (pDbDwg == NULL) 
		return false;
    ACHAR* sDwgGuid = NULL;
	pDbDwg->getFingerprintGuid(sDwgGuid);

	bool bFound=false;
	List<PnPProjectDrawing^>^ pDwgList = pProject->GetPnPDrawingFiles();
	for each (PnPProjectDrawing^ pDwg in pDwgList) 
	{
		const wchar_t *sProjectDwgGuid = StringToWchar(pDwg->DrawingGuid);
		if (_wcsicmp(sDwgGuid, sProjectDwgGuid) == 0)
		{
			bFound=true;
			break;
		}
	}

	acutDelString(sDwgGuid);
	return bFound; //ActiveDocument is not in the CurrentProject
}



// PnPProject Handle implementation
// similar macros that use GCHandle are used in <gcroot.h> and "mgdinterop.h"
// please refer to gcroot in visual studio help for a discussion on how to 
// declare handles in native types.
//
#define __GCHANDLE_TO_VOIDPTR(x) ((GCHandle::operator System::IntPtr(x)).ToPointer())
#define __VOIDPTR_TO_GCHANDLE(x) (GCHandle::operator GCHandle(System::IntPtr(x)))

static Project^ GETPROJECT(void* pProjectGCHandle)
{
	Project^ pProject = nullptr;
	if (pProjectGCHandle != NULL)
	{
		pProject = static_cast<Project^>(__VOIDPTR_TO_GCHANDLE(pProjectGCHandle).Target);
	}
	return pProject;
}

PnPProject::PnPProject()
{
	Project^ pProject = nullptr;
    try 
	{
		pProject = PlantApplication::CurrentProject->ProjectParts[L"PnId"];
    } 
	catch (...) 
	{
        pProject = nullptr;
    }
	m_pProjectGCHandle = __GCHANDLE_TO_VOIDPTR(GCHandle::Alloc(pProject));
}

PnPProject::~PnPProject ()
{
	GCHandle g = __VOIDPTR_TO_GCHANDLE(m_pProjectGCHandle);
	g.Free();
	m_pProjectGCHandle = NULL;
}


// PnPProject sample methods
//
bool PnPProject::IsLoaded()
{
	Project^ pProject = GETPROJECT(m_pProjectGCHandle);
    if (pProject == nullptr)
    {
        return false;
    }
    return pProject->Isloaded();
}

void PnPProject::List()
{
	acutPrintf(L"\nListing Project.");

	Project^ pProject = GETPROJECT(m_pProjectGCHandle);


	//List Sample Project Values
	const wchar_t *sVal=StringToWchar(pProject->Name);
	acutPrintf(L"\nProject: %s:", sVal);

	double fVal=pProject->AnnotationOffsetDistance;
	acutPrintf(L"\n   AnnotationOffsetDistance: %g.", fVal);

	System::Collections::Generic::List<PnPProjectDrawing^>^ pDwgList = pProject->GetPnPDrawingFiles();

	for each (PnPProjectDrawing^ pDwg in pDwgList) 
	{
		const wchar_t *sProjectDwgName = StringToWchar(pDwg->ResolvedFilePath);
		const wchar_t *sDrawingGuid = StringToWchar(pDwg->DrawingGuid);
		acutPrintf(L"\n   %s %s.", sProjectDwgName, sDrawingGuid);
	}

	sVal=StringToWchar(pProject->ProjectDirectory);
	acutPrintf(L"\n   ProjectDirectory: %s.", sVal);

	sVal=StringToWchar(pProject->SymbolsDirectory);
	acutPrintf(L"\n   SymbolsDirectory: %s.", sVal);
}



//end