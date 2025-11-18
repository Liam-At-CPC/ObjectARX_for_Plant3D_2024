//
// (C) Copyright 2007-2010 by Autodesk, Inc.
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

#include "acdb.h"
#include "PnPCommonServices.h"
#include "AcPp3dSpecPort.h"
#include "gept3dar.h"
#include "gevc3dar.h"

class AcPpProject;
class AcPpDataLinksManager;
class AcDbDatabase;
class AcPpDb3dPart;
class AcPp3dSpecPart;
class AcPp3dPartSizeProperties;
class AcPp3dConnectionManager;
class AcPp3dUISettings;
class AcPpProjectReactor;
class AcDbBlockTableRecordIterator;
class AcPp3dSpecManager;
class AcCmEntityColor;

class AcPp3dAppServices : public PnPCommonServices
{
public:
    // Services protocol
    //
    virtual AcPpProject *            get3dProject            () = 0;
    virtual AcPpDataLinksManager *   get3dLinksManager       () = 0;
    virtual bool                     is3dDwg                 (AcDbDatabase *dwg,
                                                             bool &bProjectLoaded,
                                                             bool &bDwgInProject) = 0;
	virtual AcPp3dConnectionManager* get3dConnectionManager	 () = 0;

    // Same as get3dLinksManager()
    virtual AcPpDataLinksManager* getLinksManager() = 0;

    /// <summary>
    /// Gets the AcPpDataLinksManager for a specific AcDbDatabase
    /// May return NULL if the project part for pDb cannot be determined
    /// <param name = "pDb"> AcDbDatabase for which to seek the Data Links Manager</param>
    /// </summary>
    virtual AcPpDataLinksManager* getLinksManager(AcDbDatabase* pDb) = 0;

    /// <summary>
    /// Get Spec Manager for the current project
    /// </summary>
    virtual AcPp3dSpecManager *     get3dSpecManager        () = 0;

    // Project units
    //
    virtual AcPp3dNominalDiameter::EUnit    getLinearProjectUnit    () = 0;
    virtual AcPp3dNominalDiameter::EUnit    getNDProjectUnit        () = 0;

    /// <summary>
    /// Add a project reactor.
    /// </summary>
	/// <param name = "pReactor"> Pointer to AcPpProjectReactor class to add </param>
    virtual void addProjectReactor    (AcPpProjectReactor *pReactor) = 0;

    /// <summary>
    /// Remove a project reactor.
    /// </summary>
	/// <param name = "pReactor"> Pointer to AcPpProjectReactor class to remove </param>
	virtual void removeProjectReactor (AcPpProjectReactor *pReactor) = 0;

    /// <summary>
	/// get spec part for the part
    /// </summary>
    /// <param name = "id"> the part's AcDbObjectId </param>
    /// <returns> ptr to part properties if they exist, 0 - otherwise; the caller is responsible for deleting the ptr </returns>
    //
    virtual AcPp3dPartSizeProperties *   get3dPartByObjectId(const AcDbObjectId& id, int subindex) = 0;
    
    /// <summary>
	/// Updates insulation display on a part according to the current settings and properties
    /// </summary>
    /// <param name = "id"> the part's AcDbObjectId </param>
    //
    virtual void                    updateInsulationDisplay     (const AcDbObjectId &id) = 0;
    
    // UI settings (only in ACAD)
    //
    virtual AcPp3dUISettings *  getUISettings       () = 0;


    /// <summary>
    /// Returns an AcDbObjectIdArray of the current AutoCAD selection set, if one exists.
    /// Will return an empty array for non-AutoCAD hosts.
    /// </summary>
    virtual AcDbObjectIdArray getAcadCurrentSelection() = 0;


    // Project Get/Set services for 3d
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
	virtual bool   getPnPDrawingFile(const ACHAR* pFGuid, ACHAR* buffer, int len) = 0;

    /// <summary>
    /// Returns the next available value from the project for pAutogenKey
    /// Will return -1 if none is found
    /// </summary>
	/// <param name = "pAutogenKey"> Name of the AutogenKey whose value is requested</param>
	/// <returns> Will return -1 if none is found </returns>
    virtual int    getNextProjectAutogenValue(const AcDbDatabase* pDb, const ACHAR* pAutogenKey) = 0;

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
	/// <param name = "pDb"> Database </param>
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
    /// Creates Model Space iterator.
    /// Since dbx modules can't do that...
    /// </summary>
    /// <param name = "pDwg"> Database</param>
	/// <returns> Iterator </returns>
    virtual AcDbBlockTableRecordIterator * modelSpaceIterator   (AcDbDatabase *pDwg) = 0;

    // Background color of the current ACAD window
    //
    virtual bool        currentAcadBackground   (AcCmEntityColor &color) = 0;

    // Sysvars
    //
    virtual bool        LAYLOCKFADECTL          (int &val) = 0;

    /// <summary>
    /// Gets sizes of elbow straight sides
    /// </summary>
    /// <param name = "id"> Part id</param>
    /// <param name = "l1"> Length of the first straight side</param>
    /// <param name = "l2"> Length of the second straight side</param>
	/// <returns> true if success, and false othewise </returns>
    virtual bool        getElbowL1L2            (const AcDbObjectId &id, 
                                                 double &l1,
                                                 double &l2) = 0;
    // Format angle (acdbAngToS)
    //
    virtual void        formatAngle             (double val,    // angle in radians
                                                 int unit,
                                                 int prec,
                                                 AcString& str) = 0;

    // Layout
    //
    virtual bool isSwitchingLayout              () = 0;
};

// Get/set services
//
PNP3DOBJECTS_API
AcPp3dAppServices *     AcPp3dGetAppServices    ();

PNP3DOBJECTS_API
void                    AcPp3dSetAppServices    (AcPp3dAppServices *pSrv);


// Shotcut functions
//
inline AcPpProject *  AcPp3dGet3dProject ()
{
    AcPp3dAppServices *pServices =  AcPp3dGetAppServices();
    if (!pServices)
    {
        assert(false);
        return false;
    }
    return pServices->get3dProject();
}

inline AcPpDataLinksManager *  AcPp3dGet3dLinksManager ()
{
    AcPp3dAppServices *pServices =  AcPp3dGetAppServices();
    if (!pServices)
    {
        assert(false);
        return false;
    }
    return pServices->get3dLinksManager();
}

inline AcPp3dConnectionManager * AcPp3dGet3dConnectionManager ()
{
    AcPp3dAppServices *pServices =  AcPp3dGetAppServices();
    if (!pServices)
    {
        assert(false);
        return false;
    }
    return pServices->get3dConnectionManager();
}

inline AcPp3dSpecManager *  AcPp3dGet3dSpecManager ()
{
    AcPp3dAppServices *pServices =  AcPp3dGetAppServices();
    if (!pServices)
    {
        assert(false);
        return false;
    }
    return pServices->get3dSpecManager();
}

