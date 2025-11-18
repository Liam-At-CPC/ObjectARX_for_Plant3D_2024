//
// (C) Copyright 2007 by Autodesk, Inc.
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
// AcPpTagFormat.h
//
//  DESCRIPTION: AcPpTagFormat API class declaration
//
//  AcRxObject
//    AcDbObject
//      AcPpTagFormat
//

//-----------------------------------------------------------------------------
//----- AcPpTagFormat.h : Declaration of the AcPpTagFormat
//-----------------------------------------------------------------------------
#ifndef __ACPPTAGFORMAT_H__
#define __ACPPTAGFORMAT_H__

#pragma once

#include "dbmain.h"
#include "dbobjptr.h"
#include "AcString.h"
//#include "dbapserv.h"
//#include "atlstr.h"
#include "PnPDllDef.h"

class AcPpImpTagFormat;

/// <summary>
/// Represents a tag format.
/// </summary>
class PNIDOBJECTS_API AcPpTagFormat : public AcDbObject
{
public:
    ACRX_DECLARE_MEMBERS(AcPpTagFormat);

    /// <summary>
    /// Default constructor.
    /// </summary>
	AcPpTagFormat();

	/// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcPpTagFormat();

	/// <summary>
	/// Overloaded assignment operator
	/// </summary>
    AcPpTagFormat& operator =( const AcPpTagFormat &);

	/// <summary>
	/// This function gets the name of the tag style .
	/// </summary>
	/// <param name = "name"> Name of the tag style </param>
	/// <returns>Acad::ErrorStatus </returns>
    Acad::ErrorStatus           getName(AcString& name) const;

	/// <summary>
	/// This function sets the name of the tag style .
	/// </summary>
	/// <param name = "pName"> Tag style name to set </param>
	/// <returns>Acad::ErrorStatus </returns>
    Acad::ErrorStatus           setName(const ACHAR * pName);

	/// <summary>
	/// This function gets the class name.
	/// </summary>
	/// <returns> Character pointer representing class name </returns>
    const ACHAR*                tagClassName(void) const;

	/// <summary>
	/// This function sets the class name .
	/// </summary>
	/// <param name = "pClassName"> String representing class name </param>
	/// <returns>Acad::ErrorStatus </returns>
    Acad::ErrorStatus           setTagClassName(const ACHAR * pClassName);

	/// <summary>
	/// This function returns the tag description.
	/// </summary>
	/// <returns> String representing tag description </returns>
    const ACHAR*                description(void) const;

	/// <summary>
	/// This function sets the tag description.
	/// </summary>
	/// <param name = "pClassName"> String representing tag description </param>
	/// <returns>Acad::ErrorStatus </returns>
    Acad::ErrorStatus           setDescription(const ACHAR * pszDescription);

	/// <summary>
	/// This function returns the tag format string.
	/// </summary>
	/// <returns> String representing tag format string </returns>
    const ACHAR*                formatString(void) const;

	/// <summary>
	/// This function sets the tag format string.
	/// </summary>
	/// <param name = "pFormatString"> String representing tag format string </param>
	/// <returns>Acad::ErrorStatus </returns>
    Acad::ErrorStatus           setFormatString(const ACHAR * pFormatString);

	/// <summary>
	/// This function returns the bit flag.
	/// </summary>
	/// <returns> bit flag </returns>
    Adesk::UInt32               bitFlags() const;

	/// <summary>
	/// This function sets the bit flags
	/// </summary>
	/// <param name = "flags"> bit flags to set </param>
	/// <returns>Acad::ErrorStatus </returns>
    Acad::ErrorStatus           setBitFlags(Adesk::UInt32 flags);

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
	/// This function is called by AutoCAD when the AUDIT command is executed. 
	/// The AcDbAuditInfo object pointed to by pAuditInfo contains member functions that are used to determine what to do and also to report the results of the audit operation on the object.
	/// </summary>
	/// <param name="pAuditInfo"> Passed in a pointer to an AcDbAuditInfo object <param>
	virtual Acad::ErrorStatus   audit(AcDbAuditInfo* pAuditInfo);

    /// <summary>
    /// Posts Tag Format Style to Database.
    /// </summary>
    /// <param name="styleName">Style Name</param>
    /// <param name="Id">Input Id of Tag Format Style</param>
	/// <param name="pDb">Input pointer to drawing database</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus           postTagFormatStyleToDb(const ACHAR* styleName, 
                                                        AcDbObjectId& Id,
                                                        AcDbDatabase* pDb = NULL);

private:
    AcPpImpTagFormat* mpImpTagFormat;

};

#endif // __ACPPTAGFORMAT_H__
