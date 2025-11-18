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
// DESCRIPTION: 

#pragma once

#include "AcString.h"
#include "AcPpDataLinks.h"
#include "PnPCommonServices.h"
#include "AcPp3dSpecManager.h"
#include "AcPp3dSpecPort.h"
#include "PnPDllDef.h"

#ifdef PNPMAIN_EXPORTS
#define PNPMAIN_API __declspec(dllexport)
#else
#define PNPMAIN_API 
#endif

// Forward declares
class AcPpProject;
class AcPp2dProject;
class AcPpDataLinksManager;
class AcDbDatabase;
class AcPpProjectReactor;
class AcPpGranularDwfManager;

/// <summary>
/// AcPnPService interface extends the PnPCommonServices interface and adds
/// PnID (2D) specific services.
///
/// Services client is intended to be ObjectEnabler code (*.dbx) that would
/// otherwise not have access to ARX-side functionality.  Such client code
/// is expected to use these services defensively; that is, it should
/// account for the possibility of not receiving a services pointer or for
/// a particular service to be unimplemented.
/// 
/// The Services class is NOT intended to be a general utility class!
/// </summary>
class AcPnIDServices : public PnPCommonServices
{
    // Overrides from PnPCommonServices base class

public:

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
    /// Copies the name of the current AutoCAD command owning the lock on the provided
    /// AcDbDatabase.  The returned string may be empty if there is no current lock.
    /// Will return false if AutoCAD is not the host
    /// </summary>
	/// <param name = "buffer"> Name of the current AutoCAD command is copied in this buffer </param>
	/// <param name = "len"> Length of character array. Determines the length of characters being copied </param>
	/// <returns> Returns false if AutoCAD is not the host </returns>
    virtual bool   getCommandOwningCurrentLock(ACHAR* buffer, int len) = 0;

    /// <summary>
    /// Reports whether AutoCAD currently has a bedit session in progress
    ///
    /// <returns> Returns true is AutoCAD is the host and a BEDIT session is in progress.
    ///           Otherwise returns false
    /// </returns>
    /// </summary>
    virtual bool   beditInProgress() = 0;

    /// <summary>
    /// Returns an AcDbObjectIdArray of the current AutoCAD selection set, if one exists.
    /// Will return an empty array for non-AutoCAD hosts.
    /// </summary>
    virtual AcDbObjectIdArray getAcadCurrentSelection() = 0;

	/// <summary>
	/// Retrieves the value of a system variable. This function internally invokes the AutoCAD acedGetVar() 
	/// method
	/// </summary>
	/// <param name = "varName"> Input system variable name to get - Case Sensitive </param>
	/// <param name = "result">  Output preallocated buffer to be filled in with system variable value </param>
	/// <returns> Returns RTNORM if successful; otherwise it returns RTERROR </returns>
	virtual int   getVar(const ACHAR *varName, struct resbuf *result) = 0;

	/// <summary>
	/// Retrieves the value of an environment variable. This function internally invokes the AutoCAD acedGetEnv() 
	/// method
	/// </summary>
	/// <param name = "envName"> Input environment variable name to get - Case Sensitive </param>
	/// <param name = "envValue"> Output preallocated buffer to be filled in with environment variable value </param>
	/// <returns> Returns RTNORM if successful; otherwise it returns RTERROR </returns>
	virtual int   getEnv(const ACHAR *envName, ACHAR *envValue) = 0;

	/// <summary>
	/// Set the value of an environment variable. This function internally invokes the AutoCAD acedSetEnv() 
	/// method
	/// </summary>
	/// <param name = "envName"> Input environment variable name - Case Sensitive </param>
	/// <param name = "envValue"> Input environment variable value </param>
	/// <returns> Returns RTNORM if successful; otherwise it returns RTERROR </returns>
	virtual int   setEnv(const ACHAR *envName, const ACHAR *envValue) = 0;

	/// <summary>
    /// Gets the AcPpDataLinksManager
    /// Same as get2dLinksManager for P&ID
    /// </summary>
    virtual AcPpDataLinksManager* getLinksManager() = 0;

    /// <summary>
    /// Gets the AcPpDataLinksManager for a specific AcDbDatabase
    /// May return NULL if the project part for pDb cannot be determined
    /// <param name = "pDb"> AcDbDatabase for which to seek the Data Links Manager</param>
    /// </summary>
    virtual AcPpDataLinksManager* getLinksManager(AcDbDatabase* pDb) = 0;


    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    //
    // Services specific to PnID (2D) functionality


    // Services protocol
    //
    virtual AcPp2dProject *          get2dProject            () = 0;
    virtual AcPpDataLinksManager *   get2dLinksManager       () = 0;
    virtual bool                     is2dDwg                 (AcDbDatabase *dwg,
                                                             bool &bProjectLoaded,
                                                             bool &bDwgInProject) = 0;
    /// <summary>
    /// Copies the name of the data links manager to the buffer provided by the 
    /// caller.
    /// Will return false if the data links manager is not initialized
    /// </summary>
	/// <param name = "buffer"> Name of the data links manager </param>
	/// <param name = "len"> Length of character array. Determines the length of characters being copied</param>
	/// <returns> Returns false if the data links manager is not initialized </returns>
    virtual bool   getDataLinksManagerName (ACHAR* buffer, int len) = 0;

    /// <summary>
    /// Get Spec Manager for the current project
    /// </summary>
    virtual AcPp3dSpecManager *     getSpecManager() = 0;

    /// <summary>
    /// Copies the name of the default Style for pClassname 
    /// to the buffer provided by the caller.
    /// Will return false if none is found.
    /// </summary>
	/// <param name = "pClassName"> Name of the pClassname whose default style is requested </param>
	/// <param name = "buffer"> Name of the default style is copied here </param>
	/// <param name = "len"> Length of character array. Determines the length of characters being copied </param>
	/// <returns> Will return false if none is found </returns>
    virtual bool   getDefaultStyleNameForClass(const ACHAR* pClassName, 
        ACHAR* buffer, int len) = 0;

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
    /// <param name = "pDb"> Pointer to a project-resident AcDbDatabase, used to identify correct project part. </param>
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
	/// <param name = "pDb"> Database for which to get the property</param>
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
    /// Copies the default property names and values into the string arrays
    /// </summary>
	/// <param name = "pClassName"> Class name whos property names and values are requested </param>
	/// <param name = "propNames"> Property names </param>
	/// <param name = "propValues"> Property values </param>
	/// <returns> Will return false if none is found </returns>
    virtual bool   getDefaultPropertiesForClass(const ACHAR* pClassName, 
        AcPpStringArray& propNames, AcPpStringArray& propValues) = 0;

    /// <summary>
    /// Gets the blockname associated with a given End Code property
    /// </summary>
    /// <param name = "pEndCodeName"> Name of the End Code property for which the block is requested. </param>
    /// <param name = "pBlockNameBuffer">  User provided buffer to contain the name of the Block Definition </param>
    /// <param name = "len"> Length of character array. Determines the length of characters being copied. </param>
    /// <returns> Will return false if none is found </returns>
    virtual bool    getEndCodeBlockDefName(const ACHAR* pEndCodeName, ACHAR* pBlockNameBuffer, int len) = 0;

    /// <summary>
    /// Returns an instance of PnPServices 
    /// Null if there are no services
    /// </summary>
	/// <returns>Pointer to AcPnIDServices class </returns>
    PNIDOBJECTS_API static AcPnIDServices * getPnIDServices ();

    /// <summary>
    /// Register PnPServices 
    /// </summary>
	/// <param name = "srv"> Pointer to AcPnIDServices to set</param>
    PNIDOBJECTS_API static void  setPnIDServices (AcPnIDServices * srv);

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
	/// Returns an instance to the granular DWF manager.
	/// </summary>
	/// <returns> 
	/// Instance to the granular DWF manager 
	/// </returns>
	virtual AcPpGranularDwfManager* getGranularDwfManager() const = 0;
    
    /// <summary>
    /// For a given class property returns the content of symbol pick list,
    /// associated with it.
    /// </summary>
    /// <param name ="sClassName"> Name of P&ID class</param>
    /// <param name ="sPropertyName"> Property name</param>
    /// <param name ="values"> output list of pick list values</param>
    /// <param name ="styleNames"> output list of corresponding styles</param>
    /// <returns> true if a property has symbol picklist, false - otherwise</returns>
    virtual bool        getSymbolPickList   (const ACHAR *sClassName,
                                             const ACHAR *sPropertyName,
                                             AcPpStringArray &values,
                                             AcPpStringArray &styleNames) const = 0;

    // Property Acquisition
    //

    /// <summary>
    /// Reacquire the value of the specified property/column belonging to the specified table row.
    /// </summary>
    /// <param name="rowid">Table row id.</param>
    /// <param name="sPropertyNames">Property name, or the column name in the table row.</param>
    /// <returns>Returns <c>true</c> if successful.</returns>
    virtual bool refreshAcquisitionValues(const AcPpRowId& rowid,
                                          const AcPpStringArray& sPropertyNames) const = 0;

	// Do we need to disable PnID object editing ?
	//

	/// <summary>
	/// This function would be used to check if we need to disable PnID object editing
	/// </summary>
	/// <param name="pDb">Database</param>
	/// <param name="bisBedit">Do we also need to check if bedit is in progress?</param>
	/// <returns>Returns <c>true</c> if successful.</returns>
	virtual bool disablePnIDObjectEdit(AcDbDatabase *pDb) = 0;

	/// <summary>
	/// Get the current PnID project's unit
	/// </summary>
	/// <returns>Returns project's unit</returns>
	virtual AcDb::UnitsValue getProjectUnit() = 0;

protected:
    virtual bool    has2dProjectPart() = 0;

};
