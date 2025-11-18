//
// (C) Copyright 2008-2011 by Autodesk, Inc.
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

#pragma once

#include "AcString.h"
#include "AcPpDataLinks.h"

#include "PnPDllDef.h"

// Forward declares
class AcPpDataLinksManager;
class AcDbDatabase;

/// <summary>
/// PnPCommonServices defines an interface to allow PnP Object Enablers to conditionally
/// access services only available from ARX modules.  This is not intended to be a public API,
/// nor is it intended to be a general utility class.  This base class "PnPCommonServices"
/// provides functionality that is common to both the 2D and 3D products, each of which
/// derives and extends this class, providing 2D-Arx-side services to PnIDObjects.dbx
/// and 3D-Arx-side services to PnP3dObjects.dbx
///
/// All code within our ObjectEnablers must code defensively to deal with the possibility
/// that a service is unavailable.
///
/// </summary>
class PNPCOMMONDBX_API PnPCommonServices
{
public:
    /// <summary>
    /// Returns an instance of PnPServices 
    /// Null if there are no services
    /// </summary>
	/// <returns>Pointer to AcPnIDServices class </returns>
    static PnPCommonServices * getCommonServices ();

    /// <summary>
    /// Register PnPServices 
    /// </summary>
	/// <param name = "srv"> Pointer to AcPnIDServices to set</param>
    static void  setCommonServices (PnPCommonServices * srv);

    /// <summary>
    /// Copies the name of the current AutoCAD command to the buffer provided 
    /// by the caller.
    /// Will return false if AutoCAD is not the host
    /// </summary>
	/// <param name = "buffer"> Name of the current AutoCAD command is copied in this buffer </param>
	/// <param name = "len"> Length of character array. Determines the length of characters being copied </param>
	/// <returns> Returns false if AutoCAD is not the host </returns>
    virtual bool   getCurrentAcadCommand(ACHAR* buffer, int len) = 0;

    /// <summary>
    /// Reports whether AutoCAD currently has a bedit session in progress
    ///
    /// <returns> Returns true is AutoCAD is the host and a BEDIT session is in progress.
    ///           Otherwise returns false
    /// </returns>
    /// </summary>
    virtual bool   beditInProgress() = 0;

    /// <summary>
    /// Copies the name of the current AutoCAD command owning the lock on the provided
    /// AcDbDatabase.  The returned string may be empty if there is no current lock.
    /// Will return false if AutoCAD is not the host
    /// </summary>
	/// <param name = "buffer"> Name of the current AutoCAD command is copied in this buffer </param>
	/// <param name = "len"> Length of character array. Determines the length of characters being copied </param>
	/// <returns> Returns false if AutoCAD is not the host </returns>
    virtual bool   getCommandOwningCurrentLock(ACHAR* buffer, int len) = 0;

    /// <summary>
    /// Returns an AcDbObjectIdArray of the current AutoCAD selection set, if one exists.
    /// Will return an empty array for non-AutoCAD hosts.
    /// </summary>
    virtual AcDbObjectIdArray getAcadCurrentSelection() = 0;

    /// <summary>
    /// Gets the AcPpDataLinksManager
    /// May return NULL if the project part is unknown
    /// </summary>
    virtual AcPpDataLinksManager* getLinksManager() = 0;

    /// <summary>
    /// Gets the AcPpDataLinksManager for a specific AcDbDatabase
    /// May return NULL if the project part for pDb cannot be determined
    /// <param name = "pDb"> AcDbDatabase for which to seek the Data Links Manager</param>
    /// </summary>
    virtual AcPpDataLinksManager* getLinksManager(AcDbDatabase* pDb) = 0;

    /// <summary>
    /// Copies the value of the requested property to the buffer 
    /// provided by the caller.
    /// Will return false if the none is found
    /// </summary>
	/// <param name = "pCategory"> Name of the Category whose value of property is requested </param>
	/// <param name = "pProperty"> Name of the Property whose value is requested </param>
	/// <param name = "buffer"> Name of the value of the requested property is copied here </param>
	/// <param name = "len"> Length of character array. Determines the length of characters being copied </param>
    /// <param name = "pFGuid"> Fingerprint GUID of a project-resident AcDbDatabase, used to identify project part</param>
	/// <returns> Will return false if none is found </returns>
    virtual bool   getPropertyFromProject(const ACHAR* pCategory, const ACHAR* pProperty, 
        ACHAR* buffer, int len, const ACHAR* pFGuid) = 0;

    /// <summary>
    /// Copies the value of newValue into the category and property of the project 
    /// Will return false if the none is found
    /// </summary>
	/// <param name = "pCategory"> Name of the Category whose value is to be set to the new value</param>
	/// <param name = "pProperty"> Name of the Property whose value is to be set to the new value</param>
	/// <param name = "newValue"> Name of the value to be set </param>
    /// <param name = "pFGuid"> Fingerprint GUID of a project-resident AcDbDatabase, used to identify project part</param>
	/// <returns> Will return false if none is found </returns>
	virtual bool   setPropertyInProject(const ACHAR* pCategory, const ACHAR* pProperty, 
        const ACHAR* newValue, const ACHAR* pFGuid) = 0;

    /// <summary>
    /// Copies the value of the requested property to the buffer 
    /// provided by the caller.
    /// Will return false if the none is found
    /// </summary>
	/// <param name = "pFGuid"> Fingerprint GUID of an AcDbDatabase </param>
	/// <param name = "pCategory"> Name of the Category whose property's value is requested</param>
	/// <param name = "pProperty"> Name of the Property whose value is requested</param>
	/// <param name = "buffer"> Name of the value of the requested property is copied here </param>
	/// <param name = "len"> Length of character array. Determines the length of characters being copied </param>
	/// <returns> Will return false if none is found </returns>
    virtual bool   getPropertyFromDrawing(const ACHAR* pFGuid, 
        const ACHAR* pCategory, const ACHAR* pProperty, ACHAR* buffer, int len) = 0;

    /// <summary>
    /// Copies the value of newValue into the category and property of the drawing 
    /// Will return false if the none is found
    /// </summary>
	/// <param name = "pFGuid"> Fingerprint GUID of an AcDbDatabase </param>
	/// <param name = "pCategory"> Name of the Category whose property's value is requested</param>
	/// <param name = "pProperty"> Name of the Property whose value is requested</param>
	/// <param name = "newValue"> Name of the value of the requested property which is to be set </param>
	/// <returns> Will return false if none is found </returns>
    virtual bool   setPropertyInDrawing(const ACHAR* pFGuid, 
        const ACHAR* pCategory, const ACHAR* pProperty, const ACHAR* newValue) = 0;

	/// <summary>
	/// Copies the full file path of the dwg being requested to the buffer provided by the caller.
	/// Will return true only if the dwg exists and belongs to the project.
	/// </summary>
	/// <param name="pFGuid"> Fingerprint GUID of an AcDbDatabase </param>
	/// <param name="buffer"> File path of dwg requested is copied here </param>
	/// <param name="len"> Length of character array. Determines the length of characters being copied </param>
	/// <returns> Will return true only if the requested dwg exists and belongs the project </returns>
	virtual bool getPnPDrawingFile(const ACHAR* pFGuid, ACHAR* buffer, int len) = 0;

    /// <summary>
    /// Returns the next available value from the project for pAutogenKey
    /// Will return -1 if none is found
    /// </summary>
    /// <param name = "pDb"> Pointer a a project-resident drawing, used to find the correct project part.</param>
	/// <param name = "pAutogenKey"> Name of the AutogenKey whose value is requested</param>
	/// <returns> Will return -1 if none is found </returns>
    virtual int    getNextProjectAutogenValue(const AcDbDatabase* pDb, 
        const ACHAR* pAutogenKey) = 0;

    /// <summary>
    /// Returns the next available value from the project for pAutogenKey
    /// This variant is useful when collecting a value without having a project-resident drawing open
    /// Will return -1 if none is found
    /// </summary>
    /// <param name = "pLm"> Data Links Manager, used to identify correct project part.</param>
	/// <param name = "pAutogenKey"> Name of the AutogenKey whose value is requested</param>
	/// <returns> Will return -1 if none is found </returns>
    virtual int    getNextProjectAutogenValue(AcPpDataLinksManager* pLm, 
        const ACHAR* pAutogenKey) = 0;

    /// <summary>
    /// Returns the next available value from the drawing for pAutogenKey
    /// Will return -1 if none is found
    /// </summary>
	/// <param name = "pDb"> Pointer a a project-resident drawing, used to lookup the value. </param>
	/// <param name = "pAutogenKey"> Name of the AutogenKey whose value is requested </param>
	/// <returns> Will return -1 if none is found </returns>
    virtual int    getNextDrawingAutogenValue(const AcDbDatabase* pDb,
        const ACHAR* pAutogenKey) = 0;       

    /// <summary>
    /// Returns the next available value from the drawing for pAutogenKey.  This variant is useful
    /// when collecting a value from a drawing that is not currently open.
    /// Will return -1 if none is found
    /// </summary>
    /// <param name = "rowId"> RowId of a row in the project.  Used to collect drawing data.</param>
    /// <param name = "pLm"> Data Links Manager, used to identify correct project part.</param>
	/// <param name = "pAutogenKey"> Name of the AutogenKey whose value is requested </param>
	/// <returns> Will return -1 if none is found </returns>
    virtual int    getNextDrawingAutogenValue(AcPpRowId rowId,
		AcPpDataLinksManager* pLm, const ACHAR* pAutogenKey) = 0;

        /// <summary>
    /// Copies the name of the symbol and style cache drawing to the buffer 
    /// provided by the caller.
    /// Will return false if the none is found
    /// </summary>
	/// <param name = "buffer"> Name of the symbol and style cache drawing is copied here </param>
	/// <param name = "len"> Length of character array. Determines the length of characters being copied </param>
	/// <returns> Will return false if none is found </returns>
    virtual bool   getSymbolAndStyleCacheFile (ACHAR* buffer, int len) = 0;

    /// <summary>
    /// Assigns the symbol and style cache drawing database to the specified pointer; the caller
    /// should <b>never</b> delete the database after use, the <c>AcPnIDServices</c> class manages the 
    /// <c>AcDbDatabase</c> internally.
    /// Will return false if the none is found
    /// </summary>
    /// <param name = "pDb"> Output pointer to symbol and style cache drawing AcDbDatabase </param>
    /// <returns> Will return false if none is found </returns>
    virtual bool    getSymbolAndStyleCacheFile(AcDbDatabase*& pDb) = 0;

    /// <summary>
    /// Copies the symbol library directory name to the buffer 
    /// provided by the caller.
    /// Will return false if the none is found
    /// </summary>
	/// <param name = "buffer"> Name of the symbol library directory is copied here </param>
	/// <param name = "len"> Length of character array. Determines the length of characters being copied </param>
	/// <returns> Will return false if none is found </returns>
    virtual bool   getSymbolLibraryPath (ACHAR* buffer, int len) = 0;

    /// <summary>
    /// For the given tag name return tag format value and class
    /// </summary>
    /// <param name ="tagname"> Tag name</param>
    /// <param name ="tagVal"> tag value</param>
    /// <param name ="tagclass"> tag class</param>
    /// <returns> true if a tag format exists, false - otherwise</returns>
    virtual bool getTagFormat    (const ACHAR * tagname, ACHAR * tagVal, int len1, ACHAR * tagclass, int len2) = 0;

    /// <summary>
    /// Used to determine if publishing is in progress
    /// </summary>
    /// <returns> true if publishing is in progress </returns>
    virtual bool isPublishing() = 0;

    /// <summary>
    /// Used to specify if publishing is invoked via API
    /// </summary>
    /// <param name ="bIsPublishing"> Publishing in progress</param>
    virtual void setIsPublishing(bool bIsPublishing) = 0;

    /// <summary>
    /// Format double (see acdbRToS)
    /// </summary>
    virtual void        formatDouble            (double val,
                                                 int unit,
                                                 int prec,
                                                 AcString& str) = 0;
};
