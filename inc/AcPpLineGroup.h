//
// (C) Copyright 2007-2011 by Autodesk, Inc.
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
//
// DESCRIPTION: Main Exported Database Library Definitions

//-----------------------------------------------------------------------------
//----- AcPpLineGroup.h : Declaration of the AcPpLineGroup
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "dbmain.h"
#include "dbapserv.h"
#include "AcPpDataLinks.h"
#include "PnPDllDef.h"

#define BLANKLINENUMBERSTR      _T("")
#define UNASSIGNEDSTR           _T("Unassigned")

class AcPpLineGroupImpl;

/// <summary>
/// Represents a group of line segments. 
/// </summary>
class PNIDOBJECTS_API AcPpLineGroup : public AcDbObject {

public:
	ACRX_DECLARE_MEMBERS(AcPpLineGroup) ;

protected:
    static Adesk::UInt32 kCurrentVersionNumber;

public:
	/// <summary>
    /// Default constructor.
    /// </summary>
    AcPpLineGroup () ;

    /// <summary>
    /// Destructor.
    /// </summary>
	virtual ~AcPpLineGroup () ;

	/// <summary>
	/// This functions purpose is to allow the object to write out its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to write out the object's data </param>
	/// <returns>Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const ;

	/// <summary>
	/// This functions purpose is to allow the object to read in its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to read in the object's data </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) ;

    /// <summary>
	/// This functions purpose is to allow the object to write out its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to write out the object's data </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler *pFiler) const ;
    
	/// <summary>
	/// This functions purpose is to allow the object to read in its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to read in the object's data </param>
	/// <returns> Acad::ErrorStatus</returns>
	virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler *pFiler) ;	


    /// <summary>
    /// Deprecated.  Used to process pre-2014 drawings
    /// Gets the object id of every line segment in group.
    /// </summary>
    /// <param name="slines">Output AcDbObjectIdArray of line segment object ids</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus getAllSlines(AcDbObjectIdArray& slines);


    /// <summary>
    /// For internal use.
    /// </summary>
    AcPpLineGroupImpl*   implementation();

    //
    //-- static utility functions
public:

    //-- LineGroup dictionary utilities
    //-- Deprecated.  Used to process pre-2014 drawings

    /// <summary>
    /// Open and get the line group dictionary.
    /// </summary>
    /// <param name="pPnPLineGroupDict">Output pointer to line group dictionary</param>
    /// <param name="mode">Input dictionary open mode</param>
    /// <param name="pDb">Input pointer to drawing database</param>
    /// <param name="bCreate">Input create flag</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    static Acad::ErrorStatus    openPnPLineGroupDictionary(AcDbDictionary*& pPnPLineGroupDict,
                                   AcDb::OpenMode mode,
                                   const AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase(),
                                   bool bCreate = true);

    /// <summary>
    /// Get the line group dictionary name.
    /// </summary>
    /// <returns>Dictionary name.</returns>
    static const ACHAR*         lineGroupDictName();

private:
    AcPpLineGroupImpl* mpLineGroupImpl;
} ;
