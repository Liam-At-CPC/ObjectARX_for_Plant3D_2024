//
// (C) Copyright 2007-2012, 2014 by Autodesk, Inc.
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

#include <acarray.h>
#include <dbhandle.h>
#include <dbidar.h>
#include <map>
#include <vector>
#include <PnPSharedUtilDLL.h>
#include "AcString.h"
#include "PnPDllDef.h"

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(p) p
#endif

// forward declarations
class AcPpDataLinksManagerImp;
class AcPpRelationshipImp;
class AcDbDatabase;

/// <summary>
/// Data Links manager completion statuses enumeration.
/// </summary>
/// 
PNPDATALINKS_API
typedef enum _EPpDataLinksStatus
{
    ePpDLOk
    ,ePpDLFailed
    ,ePpDLNullPointer
    ,ePpDLNotImplemented
    ,ePpDLFailedToCreateCache
    ,ePpDLFailedToLoadCache
    ,ePpDLNotFound
    ,ePpDLAcceptChangedFailed
    ,ePpDLRejectChangedFailed
    ,ePpDLCannotGetLinkManager
    ,ePpDLFailedToLoadLinks
    ,ePpDLInvalidPpObjectId
    ,ePpDLInvalidDbObjectId
    ,ePpDLFailedToCreateLink
    ,ePpDLObjectAlreadyLinked
    ,ePpDLTableDoesNotExist
    ,ePpDLObjectDoesNotHaveLink
    ,ePpDLFailedToRemoveLink
    ,ePpDLFailedToCreateRelationship
    ,ePpDLFailedToGetRelatedRows
    ,ePpDLFailedToDestroyRelationship
    ,ePpDLCannotRelateToItself
    ,ePpDLFailedToSetProperties
    ,ePpDLFailedToGetProperties
    ,ePpDLFailedToAddDrawing
    ,ePpDLFailedToIdentifyDrawing
    ,ePpDLDrawingAlreadyAdded
    ,ePpDLCannotMergeRowsOfDifferentClass
    ,ePpDLRowMergeFailed
    ,ePpDLFailedToInsertTag
    ,ePpDLFailedToDeleteTag
    ,ePpDLFailedToCreateTagRegistry
    ,ePpDLFailedToEnlistColumnInCreateTagRegistry
    ,ePpDLTagRegistryDoesNotExist
    ,ePpDLOperationExecutedOnlyInExclusiveMode
    ,ePpDLDatabaseAlreadyOpenedInExclusiveMode
    ,ePpDLDatabaseDoesNotExist
    ,ePpDLDatabasePermissionDenied
    ,ePpDLMultipleAcDbDatabasesForDrawing
    ,ePpDLDrawingAlreadyEnlistedForWrite
    ,ePpDLCannotLinkToReadOnlyDrawingObject
    ,ePpDLMergeDrawinBlobCanceled
    ,ePpDLFailedToUpdateTag
    ,ePpDLFailedToSaveDrawingBlob
    ,ePpProjectItemDoesNotExist
    ,ePpFailedToChangeProjectItem
    ,ePpNotSupportedByEnlistedManager
    ,ePpSyncCanceled
} EPpDLStatus;



/// <summary>
/// Identifier that is used by AcPpLinkManager to identify AcDb Object.
/// The identifier is capable of identifying the object between autocad 
/// sessions in the multi-drawing environment
/// </summary>
class AcPpObjectId
{
public:


	/// <summary> Default constructor creates null object id </summary>
    PNPDATALINKS_API AcPpObjectId    ();

	/// <summary> Constructor for AcPpObjectId. AcDbHandle and dbid are supplied. Not Null</summary>
	/// <param name="dbid"> id representing the AcPpObjectId </param>
	/// <param name="handle"> Handle to AcPpObjectId </param>	
    PNPDATALINKS_API AcPpObjectId    (long dbid, const AcDbHandle & handle);

	/// <summary> Constructor for AcPpObjectId. AcDbHandle and dbid are supplied. Not Null</summary>
	/// <param name="dbid"> id representing the AcPpObjectId </param>
	/// <param name="handle"> Handle to AcPpObjectId </param>	
	/// <param name="subindex"> sub entity index </param>	
    PNPDATALINKS_API AcPpObjectId    (long dbid, const AcDbHandle & handle, long subindex);

	/// <summary> Construction of AcPpObjectId from AcDbObjectId is a method on AcPpDataLinksManager
	/// Data Links Manager also provides methods of converting  
	/// AcPpbjectId to AcDbObjectId</summary>
	/// <param name="other"> Reference to AcPpObjectId class </param>
    PNPDATALINKS_API AcPpObjectId    (const AcPpObjectId & other);

	/// <summary> Destructor</summary>
    PNPDATALINKS_API virtual     ~AcPpObjectId   ();

	/// <summary> Returns true if object id is null </summary>
	/// <returns> True if object id is null. False otherwise </returns>
    PNPDATALINKS_API bool        IsNull  () const;

    // equal to operator 
    PNPDATALINKS_API bool        operator== (const AcPpObjectId &) const;

    // less than operator
    PNPDATALINKS_API bool        operator<  (const AcPpObjectId &) const;

    // assignment operator
    PNPDATALINKS_API void        operator=  (const AcPpObjectId &);

	/// <summary> returns drawing identification as long  </summary>
	/// <returns> Drawing id </returns>
    PNPDATALINKS_API long        GetDwgId () const;

	/// <summary> Function to ask for AcDbHandle </summary>
	/// <returns> AcDbHandle </returns>
    PNPDATALINKS_API const AcDbHandle & GetAcDbHandle () const;

	/// <summary> Function to ask for sub index </summary>
	/// <returns> long </returns>
    PNPDATALINKS_API long        GetSubIndex () const;

    // null pp object id
    PNPDATALINKS_API static const AcPpObjectId & Null ();

protected:    
    static AcPpObjectId s_Null; 


private:
    long        m_dbid;
    AcDbHandle  m_handle;
    long        m_subindex;
};



/// <summary>
/// Array of AcPpObjectIds
/// </summary>
PNPDATALINKS_API
typedef AcArray<AcPpObjectId, AcArrayObjectCopyReallocator<AcPpObjectId> > AcPpObjectIdArray;


/// <summary>
/// Object that uniquly identifies data object in the PnP Database.
/// It is simply long
/// </summary>
PNPDATALINKS_API
typedef long AcPpRowId; 

/// <summary>
/// The array of AcPpDataObject ids 
/// </summary>
PNPDATALINKS_API
typedef AcArray<AcPpRowId> AcPpRowIdArray;

/// <summary>
/// value indicating null row id 
/// </summary>
const AcPpRowId PnPNullRowId = -1;



/// <summary>
/// Common relationship. 
/// Uses names 
/// Exposes relationship property values
/// </summary>
class PNPDATALINKS_API AcPpCommonRelationship
{
    friend class AcPpDataLinksManagerImp;

public:
	/// <summary>
	/// Default constructor. Initialises the member variables to default values
	/// </summary>
    AcPpCommonRelationship ();

	/// <summary>
	/// Constructor taking the arguments. Initialises the member variables by the supplied values
	/// </summary>
	/// <param name ="relname"> Relationship type name</param>
	/// <param name ="r1"> First role type name</param>
	/// <param name ="obj1"> Id of first object that uniquly identifies data object in the PnP Database</param>
	/// <param name ="r2"> Second role type name</param>
	/// <param name ="obj2"> Id of the second object that uniquly identifies data object in the PnP Database</param>
    AcPpCommonRelationship (const ACHAR      * relname, 
                            const ACHAR      * rolname1,
                            const AcPpRowId  & obj1,
                            const ACHAR      * rolname2,
                            const AcPpRowId  & obj2);


	/// <summary>
	/// Constructor taking the arguments. Initialises the member variables by the supplied values
	/// </summary>
	/// <param name ="relId"> Relationship id</param>
	/// <param name ="relname"> Relationship type name</param>
	/// <param name ="r1"> First role type name</param>
	/// <param name ="obj1"> Id of first object that uniquly identifies data object in the PnP Database</param>
	/// <param name ="r2"> Second role type name</param>
	/// <param name ="obj2"> Id of the second object that uniquly identifies data object in the PnP Database</param>
    AcPpCommonRelationship (const AcPpRowId  & relId,
                            const ACHAR      * relname, 
                            const ACHAR      * rolname1,
                            const AcPpRowId  & obj1,
                            const ACHAR      * rolname2,
                            const AcPpRowId  & obj2);

	/// <summary>
	/// Constructor taking the arguments. Initialises the member variables by the supplied values. Rest are initialised to null. 
	/// </summary>
	/// <param name ="rt"> Relationship type name</param>
	/// <param name ="r1"> First role type name</param>
	/// <param name ="r2"> Second role type name</param>
    AcPpCommonRelationship (const ACHAR      *  relname, 
                            const ACHAR      *  rolename1,
                            const ACHAR      *  rolename2);

	/// <summary>
	/// Copy Constructor
	/// </summary>
    AcPpCommonRelationship (const AcPpCommonRelationship & other);

	/// <summary>
	/// Destructor
	/// </summary>
    virtual ~AcPpCommonRelationship ();

	/// <summary>
	/// Assignment operator. 
	/// </summary>
    void operator = (const AcPpCommonRelationship & other);

	/// <summary>
	/// Get relationship type name. 
	/// </summary>
    const ACHAR *   RelationshipType (AcString & rtype) const;

	/// <summary>
	/// returns relationships id. 
	/// </summary>
    AcPpRowId         RelationshipId () const;

	/// <summary>
	/// Get row id in role. 
	/// </summary>
	/// <param name ="v">Rolename. </param>
    AcPpRowId         Role (const ACHAR * v) const;


	/// <summary>
	/// Get named property value. 
    /// returns NULL if property doesn't exist
	/// </summary>
	/// <param name ="pname">Property name. </param>
    const ACHAR *   PropertyValue (const ACHAR * pname, AcString & val) const;

	/// <summary>
	/// Set property value. 
	/// </summary>
	/// <param name ="pname">Property name. </param>
	/// <param name ="val">Property value. </param>
    void            SetPropertyValue (const ACHAR * pname, const ACHAR * val);

	/// <summary>
	/// Get role names. 
	/// </summary>
    void RoleNames (AcPpStringArray & rolenames) const;
    
    /// <summary>
	/// Get property names. 
	/// </summary>
    void PropertyNames (AcPpStringArray & propnames) const;

    /// <summary>
	/// Role 1 name
	/// </summary>
    const ACHAR * RoleName1 (AcString & name) const;

    /// <summary>
	/// Role 2 name
	/// </summary>
    const ACHAR * RoleName2 (AcString & name) const;

    /// <summary>
	/// Related id1
	/// </summary>
    AcPpRowId     RelatedId1 () const;

    /// <summary>
	/// Related id2
	/// </summary>
    AcPpRowId     RelatedId2 () const;


    /// <summary>
	/// Relationship is linked to the actual relationship in the projet database
    /// If relationship is retrieved and than deleted, getting relationship 
    /// data may result in a failure.
    /// The following method internal relationship storage to a 
    /// detached container
	/// </summary>
    void         Detach ();


    AcPpRelationshipImp * Imp ();

protected:
    AcPpCommonRelationship (AcPpRelationshipImp * imp);

private:
    AcPpRelationshipImp * m_imp;
};

/// <summary>
/// The array of AcPpCommonRelationship objects 
/// </summary>
PNPDATALINKS_API
typedef AcArray<AcPpCommonRelationship> AcPpCommonRelationshipArray;



class AcPpAuditResults
{
public:
    PNPDATALINKS_API AcPpAuditResults ()
    {
        m_rowsprocessed = 0;
        m_tagprocessed = 0;
    }

    PNPDATALINKS_API virtual ~AcPpAuditResults ()
    {
    }

    PNPDATALINKS_API long RowProcessed ()
    {
        return m_rowsprocessed;
    }
    PNPDATALINKS_API long TagProcessed ()
    {
        return m_tagprocessed;
    }

    PNPDATALINKS_API const AcPpRowIdArray  & DeletedRows ()
    {
        return m_deletedRows;
    }
    PNPDATALINKS_API const AcPpStringArray &  FixedTags ()
    {
        return m_fixedTags;
    }


    PNPDATALINKS_API void IncrementRowsProcessed ()
    {
        m_rowsprocessed ++;
    }

    PNPDATALINKS_API void IncrementTagsProcessed ()
    {
        m_tagprocessed ++;
    }

    PNPDATALINKS_API void AddDeletedRow (const AcPpRowId &rowid)
    {
        m_deletedRows.append (rowid); 
    }

    PNPDATALINKS_API void AddFixedTag (const ACHAR * tag)
    {
        m_fixedTags.Append (tag);
    }


private:
    int             m_rowsprocessed;
    int             m_tagprocessed;
    AcPpRowIdArray  m_deletedRows;
    AcPpStringArray m_fixedTags;
};


/// <summary>
/// Data Links manager completion statuses enumeration.
/// </summary>
PNPDATALINKS_API
typedef enum _EPpDataLinksAction
{
	/// <summary> ePpDLLinked </summary>
    ePpDLLinked,
    ePpDLLinkedNew,
    ePpDLUnlinking,
    ePpDLUnlinked,
    ePpDLRowAdded,
    ePpDLRowDeleting,
    ePpDLRowModified,
    ePpDLRelationshipAdded,
    ePpDLRelationshipDeleting,
    ePpDLRelationshipDeleted
} EPpDataLinksAction;

/// <summary>
/// Tag registry actions.
/// </summary>
PNPDATALINKS_API
typedef enum _EPpTagRegistryAction
{

    /// <summary>
    /// undefined action
    /// of TagRegistryOperationOccurred method
    /// </summary>

    ePpUndefined = 0,
    /// <summary>
    /// Candidate tag value is needed. Caller may initialize the candidatevalue argument
    /// of TagRegistryOperationOccurred method
    /// </summary>
    ePpCandidateTagNeeded = 1,

     /// <summary>
    /// Failed to add duplicated tag.  
    /// </summary>
    ePpDuplicatedTag = 2

} EPpTagRegistryAction;


/// <summary>
/// Audition events.
/// </summary>
PNPDATALINKS_API
typedef enum _EPpAuditionEvent
{

    /// <summary>
    /// unknown
    /// </summary>
    ePpAuditUndefined = 0,

    /// <summary>
    /// Row is about to be processed
    /// </summary>
    ePpAuditRowProcessing = 1,

    /// <summary>
    /// Problem row is about to be deleted
    /// </summary>
    ePpAuditRowToBeDeleted = 2,

    /// <summary>
    /// Problem tag is about to be deleted
    /// </summary>
    ePpAuditTagToBeDeleted = 3,

    /// <summary>
    /// Tag is about to be added
    /// </summary>
    ePpAuditTagToBeAdded = 4

} EPpAuditEvent;



/// <summary>
/// Drawing events.
/// </summary>
PNPDATALINKS_API
typedef enum _EPpDrawingEvent
{
    /// <summary>
    /// Accepting drawing changes
    /// </summary>
    ePpDwgAcceptingChanges = 1,

    /// <summary>
    /// Rejecting drawing changes
    /// </summary>
    ePpDwgRejectingChanges = 2,

    /// <summary>
    /// Drawing added to DLM
    /// </summary>
    ePpDwgAdded = 3,

    /// <summary>
    /// Drawing removing (before drawing removed
    /// </summary>
    ePpDwgRemoving = 4,

    /// <summary>
    /// Drawing cache is refreshing 
    /// </summary>
    ePpDwgCacheRefresh = 5,

    /// <summary>
    /// Begin drawing save 
    /// </summary>
    ePpDwgBeginSave = 6,

    /// <summary>
    /// Complete drawing save 
    /// </summary>
    ePpDwgCompleteSave = 7,

    /// <summary>
    /// Writing drawing blob 
    /// </summary>
    ePpDwgWritingDrawingBlob = 8,

    /// <summary>
    /// Getting connected parts from external drawings
    /// </summary>
    ePpDwgGetExtenalConnections = 9,

	/// <summary>
	/// Get internal dwg data, that has no link info in the dwg
	/// </summary>
	ePpDwgGetInternalData = 10

} EPpDrawingEvent;




/// <summary>
/// Data links operation listener. Defines callbacks for datalink operations. 
/// </summary>
class AcPpDataLinkOperationListener
{
public:
                AcPpDataLinkOperationListener () {};
    virtual     ~AcPpDataLinkOperationListener () {};

    /// <summary>
    /// Fired for the following actions:
    /// ePpDLLinked,
    /// ePpDLLinkedNew,
    /// ePpDLUnlinking,
    /// ePpDLUnlinked,
    /// ePpDLRowAdded,
    /// ePpDLRowDeleting,
    /// ePpDLRowModified
    /// </summary>
	/// <param name="a"> Any of the above mentioned actions. </param>
	/// <param name="oid"> Object id residing in the drawing </param>
	/// <param name="rowId"> Object that uniquly identifies data object in the PnP Database </param>
    virtual void DataLinkOperationOccurred (EPpDataLinksAction a,
                                            const AcPpObjectId & oid,
    const AcPpRowId  & rowId)
  {
    UNREFERENCED_PARAMETER(a);
    UNREFERENCED_PARAMETER(oid);
    UNREFERENCED_PARAMETER(rowId);
  };

    /// <summary>
    /// Fired for the following actions:
    /// ePpDLRelationshipAdded,
    /// ePpDLRelationshipDeleting
    /// ePpDLRelationshipDeleted
    /// </summary>
	/// <param name="a"> Any of the above mentioned actions. </param>
	/// <param name="rel"> Relationship properties which need to be updated </param>
    virtual void RelationshipOperationOccurred (EPpDataLinksAction a,
												const AcPpCommonRelationship & rel)
	{
		UNREFERENCED_PARAMETER(a);
		UNREFERENCED_PARAMETER(rel);
	};

    /// <summary>
    /// Fired when certain tag registry events happen
    /// </summary>
    virtual void TagRegistryOperationOccurred (EPpTagRegistryAction a,
                                               const ACHAR * registyrname,
                                               const ACHAR * tablename,
                                               const ACHAR * columnname,
                                               const AcPpRowId & rowid,
                                               const ACHAR * tagvalue,
											   ACHAR * &     candidatevalue,
                                               bool & bCancel)
	{
        UNREFERENCED_PARAMETER(a);
        UNREFERENCED_PARAMETER(registyrname);
        UNREFERENCED_PARAMETER(tablename);
        UNREFERENCED_PARAMETER(columnname);
        UNREFERENCED_PARAMETER(rowid);
        UNREFERENCED_PARAMETER(tagvalue);
        UNREFERENCED_PARAMETER(candidatevalue);
        UNREFERENCED_PARAMETER(bCancel);
	};

    /// <summary>
    /// Fired when certain audition event occurred.
    /// Return value has special meaning for certain events:
    /// ePpAuditRowToBeDeleted - by returning false 
    /// listener may veto removing the row.
    /// ePpAuditRowProcessing - by returning false, listener may 
    /// skip processing the row
    /// In other cases, return value is igonered
    /// </summary>
    virtual bool AuditionEventOccurred (EPpAuditEvent a,
                                        const AcPpRowId  & rowId,
                                        const ACHAR * tag) 
    {
		UNREFERENCED_PARAMETER(a);
		UNREFERENCED_PARAMETER(rowId);
		UNREFERENCED_PARAMETER(tag);
        return true;
    };


    /// <summary>
	/// Fired before drawing changes are being saved or discarded.
    /// Handler may add or remove rowids from the rowIds array.
    /// </summary>
	virtual void DrawingEventOccurred (EPpDrawingEvent 	 a,
                                       long              dwgId,
                                       AcPpRowIdArray  & rowIds)
    {
		UNREFERENCED_PARAMETER(a);
		UNREFERENCED_PARAMETER(dwgId);
		UNREFERENCED_PARAMETER(rowIds);
    };

    /// <summary>
    /// Fired before merging drawing blob into project database.
    /// argument is a GC handle wraping DrawingBlobMergeEventArgs object: 
	/// GCHandle gch = GCHandle::operator GCHandle(System::IntPtr(mergeData));
	/// DrawingBlobMergeEventArgs^ args = (DrawingBlobMergeEventArgs ^ ) gch.Target;
	/// handle should not be freed
    /// </summary>
    virtual void BlobMerging (void * mergeData)
    {
		UNREFERENCED_PARAMETER(mergeData);
    };



    /// <summary>
    /// Fired before data links manager is about to be closed and destroyed
    /// </summary>
    virtual void Closing              ()
    {
        return;
    };

    /// <summary>
    /// Fired when error occurred. 
    /// </summary>
    virtual void ErrorOccurred (int errorCode, const AcString & msg, void * exceptionData)
    {
        UNREFERENCED_PARAMETER(errorCode);
        UNREFERENCED_PARAMETER(msg);
        UNREFERENCED_PARAMETER(exceptionData);
    }

    /// <summary>
    /// Fired when entity need to be updated
    /// </summary>
    /// <param name="oid"> Object id residing in the drawing </param>
    /// <param name="rowId"> Object that uniquly identifies data object in the PnP Database </param>
    virtual void EntityNeedToBeUpdated(const AcPpObjectId& oid,
                                       const AcPpRowId& rowId)
    {
		UNREFERENCED_PARAMETER(oid);
		UNREFERENCED_PARAMETER(rowId);
    }
};



/// <summary>
/// Data links manager. IT manages links between AcDbObjects residing in 
/// AutoCAD drawings and PnP Data Objects in the PnPDatabase.
/// Each AcDbObject may be associated to one and only one PnP Data Object
/// A PnP Data object may be associated with multiple AcDbObjects 
/// It provides the following services:
///  - PnP Database creations
///  - Linking/unlinking of AcDbObject and PnP Data Instance
///  - Retrieving PnP Data OBject ids by AcDbObject id
///  - Retrieving AcDbObject Ids by the PnPDataOBject ID
/// 
/// </summary>
class PNPDATALINKS_API AcPpDataLinksManager
{
    friend class AcPpDLGeneralManager;
    friend class AcPpDataLinksManagerImp;
    friend class AcPpDataLinksManagerFactory;
protected:
	/// <summary>
	/// Default constructor
	/// </summary>
	AcPpDataLinksManager ();

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual     ~AcPpDataLinksManager ();

public:

    /// <summary>
    /// Creates PnP Data Link Manager and opens it. The creation parameters are specified
    /// If the data link manager with 
    /// such name already exists, sets manager to NULL and returns 
    /// relevant error status.
    /// </summary>
	/// <param name= "name"> Name of data link manager </param>
	/// <param name= "manager"> AcPpDataLinksManager pointer reference </param>
	/// <returns> </returns>
    static 
    EPpDLStatus          Create (const ACHAR * name, 
                                 const AcPpStringArray & parnames,
                                 const AcPpStringArray & parvalues, 
                                 AcPpDataLinksManager * & manager);

                                 
    /// <summary>
    /// Creates anonymous Data Link Manager and loads the info from given database.
    /// There is no persistent storage (mdb), and read-only access.
    /// 
    /// </summary>
	/// <param name= "db"> Database to load the info from</param>
	/// <param name= "manager"> Data Link Manager </param>
	/// <returns> </returns>
    static 
    EPpDLStatus          Load   (AcDbDatabase *db,
                                 AcPpDataLinksManager * & manager);


    /// <summary>
    /// Gets AcPpDataLinksManager.   
    /// </summary>
	/// <param name= "name"> Name string </param>
	/// <param name= "manager"> Pointer reference to Data Links Manager  </param>
	/// <returns> </returns>
    static 
    EPpDLStatus          GetManager (const ACHAR * name, 
                                     AcPpDataLinksManager * & manager);

    /// <summary>
    /// Gets AcPpDataLinksManager.   
    /// </summary>
	/// <param name= "name"> Name string </param>
    /// <param name= "username"> user id </param>
    /// <param name= "password"> password </param>
	/// <param name= "manager"> Pointer reference to Data Links Manager  </param>
	/// <returns> </returns>
    static 
    EPpDLStatus          GetManager (const ACHAR * name, 
                                     const ACHAR * username,
                                     const ACHAR * password,
                                     AcPpDataLinksManager * & manager);

    /// <summary>
    /// Gets local AcPpDataLinksManager for the specified database. 
    /// </summary>
	/// <param name= "name"> Name string </param>
	/// <param name= "manager"> Pointer reference to Data Links Manager  </param>
	/// <returns> </returns>
    static 
    EPpDLStatus          GetManager (AcDbDatabase *, 
                                     AcPpDataLinksManager * & manager);

    /// <summary>
    /// Upgrades data links manager to the current version. 
    /// </summary>
    EPpDLStatus          Upgrade ();

    
    /// <summary>
    /// Checks whether drawing has embedded blob. 
    /// </summary>
	/// <param name= "manager"> Pointer reference to Data Links Manager  </param>
	/// <returns>true if embedded blob exists </returns>
    static 
    bool                 DrawingHasBlob (AcDbDatabase * pDb);

    /// <summary>
    /// Closes the Data Links manager. Data link manager becomes un-usable 
    /// after that
    /// </summary>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          Close ();

    /// <summary>
    /// Gets the name of link mananger.   
    /// </summary>
	/// <returns> Name of link manager </returns>
    const ACHAR *       GetName () const;


    /// <summary>
    /// Get the current in-memory caching status.   
    /// </summary>
    bool                GetEnableCaching () const;


    /// <summary>
    /// Enable/Disable caching object in memory.   
    /// </summary>
    void                EnableCaching (bool val);

    /// <summary>
    /// Gets the AcDbDatabase pointer used to create the data links manager outside of a
	/// project environment. This special purpose function should not be used in a normal
	/// project setting. If this function returns a valid AcDbDatabase pointer, then it is
	/// recommended that the data links manager not be used to modify data as it could result
	/// in the project database becoming out of sync with this drawing. 
    /// </summary>
	/// <returns> Database pointer </returns>
    AcDbDatabase *      GetDatabase () const;

    /// <summary>
    /// Returns names of link manages
    /// </summary>
	/// <param name= "lmnames"> Names of link manager </param>
	/// <returns> </returns>
    static
    void                 GetLinkManagerNames (AcPpStringArray & lmnames);

    /// <summary>
    /// Sets the automanage flag. If the AcPpDataLinksManager is in the 
    /// automanage mode, it starts manage drawing links automatically when it is 
    /// opened.
    /// When not in the Automanaged mode, the drawing has to be added to the 
    /// Links Manager manually by calling AddDrawing method. 
    /// Method  RemoveDrawing may be used to remove AcDbDatabase from the 
    /// managed list  
    /// </summary>
	/// <param name= "bVal"> Automanage flag</param>
    void                 SetAutomanage (bool bVal);


    /// <summary>
    /// Get the automanage flag
    /// </summary>
	/// <returns> Returns the automanage flag</returns>
    bool                 GetAutomanage () const;

    /// <summary>
    /// Adds drawing to the list of drawings handled by the Links Manager
    /// </summary>
	/// <param name= "db"> AcDbDatabse pointer representing the drawing</param>
    /// <param name= "bReadWrtie"> drawing cache access mode </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          AddDrawing (AcDbDatabase * db);
    EPpDLStatus          AddDrawing (AcDbDatabase * db, bool bReadWrite);


    /// <summary>
    /// Adds drawing with filename to the list of drawings handled by the Links Manager
    /// </summary>
	/// <param name= "db"> AcDbDatabase pointer representing the drawing</param>
	/// <param name= "fileName"> FileName to be associated with the database. If NULL, db.getFilename() will be used</param>
    /// <param name= "bReadWrtie"> drawing cache access mode </param>
    /// <param name= "bMergeAsNew"> if true, new identities will be assigned to all rows 
    ///  merged from blob. The default value for parameter is true.
    /// </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          AddDrawing (AcDbDatabase * db, const ACHAR *fileName);
    EPpDLStatus          AddDrawing (AcDbDatabase * db, const ACHAR *fileName, bool bReadWrtie);
    EPpDLStatus          AddDrawing (AcDbDatabase * db, const ACHAR *fileName, bool bReadWrtie, bool bMergeAsNew);

    /// <summary>
    /// Adds drawing to the list of drawings handled by the Links Manager
    /// </summary>
	/// <param name= "fguid"> String name representing the drawing</param>
	/// <param name= "fileName"> FileName to be associated with the database. If NULL, db.getFilename() will be used</param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          AddDrawing (const ACHAR * fguid, const ACHAR * filename);

	/// <summary>
    /// Enlists drawing database with Links Manager. Drawing must be added before
    /// </summary>
    /// <param name= "db"> AcDbDatabse pointer representing the drawing</param>
    /// <param name= "bReadWrtie"> drawing cache access mode </param>
	/// <returns> EPpDLStatus </returns>
	EPpDLStatus			 EnlistDrawing (AcDbDatabase * dwg);
	EPpDLStatus			 EnlistDrawing (AcDbDatabase * dwg, bool bReadWrtie);
	EPpDLStatus			 EnlistDrawing (AcDbDatabase * dwg, const ACHAR * dwgname, bool bReadWrtie);

	/// <summary>
    /// Stop handling dwg by Links Manager
    /// </summary>
    EPpDLStatus          UnenlistDrawing (AcDbDatabase * dwg);

    /// <summary>
    /// Updates drawing in the project database by merging data stored 
    /// in the drawing file 
    /// </summary>
	/// <param name= "db"> AcDbDatabase pointer representing the drawing</param>
	/// <param name= "fileName"> FileName to be associated with the database. If NULL, db.getFilename() will be used</param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          UpdateDrawing (AcDbDatabase * dwg, const ACHAR * dwgname);

    /// <summary>
    /// Removes drawing from the list of drawings handled by the Links Manager, and
    /// updates it with the latest data cache information.
    /// </summary>
    /// <remarks>
    /// This is the overloaded method that should be used if the save state of the drawing 
    /// cannot be enforced before a call to this method. This method ensures that a drawing's 
    /// data cache information will be in-sync with its entities.
    /// </remarks>
	/// <param name= "db"> AcDbDatabse pointer representing the drawing</param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          RemoveDrawing (AcDbDatabase * db);


    /// <summary>
    /// Removes drawing from the list of drawings handled by the Links Manager
    /// the drawing is identified by its fingerprint guid (AcDbDatabase::getFingerprintGuid). 
    /// </summary>
	/// <param name= "fguid"> String name representing the drawing </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          RemoveDrawing (const ACHAR * fguid);


    /// <summary>
    /// Removes drawing from the list of drawings handled by the Links Manager
    /// the drawing is identified by drawing id. 
    /// </summary>
	/// <param name= "dwgId"> Drawing id </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          RemoveDrawing (int dwgId);


    /// <summary>
    /// Returns the collection of database currently managed by the 
    /// link manager
    /// </summary>
	/// <param name= "dbs"> Container containing AcDbDatabse representing the drawing</param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          GetEnlistedDrawings (AcArray<AcDbDatabase *> & dbs);


    /// <summary>
    /// Returns true if AcDbDatabase is enlisted as read-write  
    /// </summary>
    bool                 IsDrawingEnlistedAsReadWrite (AcDbDatabase * db);

    /// <summary>
    /// Returns drawing id by AcDbDatabase 
    /// Methods returns -1 if drawing is not handled by the 
    /// Data Links manager
    /// </summary>
	/// <param name= "db"> Drawing id by AcDbDatabase </param>
	/// <returns> Drawing ID </returns>
    long                GetDrawingId (AcDbDatabase * db);

    /// <summary>
    /// Returns drawing id by the drawing fingerprint guid 
    /// Methods returns -1 if drawing is not handled by the 
    /// Data Links manager
    /// </summary>
	/// <param name= "fguid"> String name representing the drawing </param>
	/// <returns> Drawing ID </returns>
    long                GetDrawingId (const ACHAR * fguid);

    /// <summary>
    /// Returns drawing guid by drawing long id.
    /// </summary>
    /// <param name= "id"> Drawing ID whose guid is requested</param>
	/// <param name= "fguid">output string that representing drawing guid. Caller
    /// is responsible for releasing return buffer.</param>
	/// <returns>Completion status</returns>
    EPpDLStatus          GetDrawingGuid (long dwgid, ACHAR * & fguid);

	/// <summary>
	///Gets the AcDbDatabase object corresponding to drawing
	///</summary>
	/// <param name= "dwgId"> Drawing ID whose AcDbDatabse is requested</param>
	/// <param name= "db"> AcDbDatabase of the drawing</param>
	/// <returns> EPpDLStatus </returns>
	EPpDLStatus			 GetDrawing(long dwgId, AcDbDatabase * & db);
	
	/// <summary>
	/// Gets the AcDbDatabase object corresponding to AcPpObjectId
	///</summary>
	/// <param name= "id"> Identifier that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "db"> AcDbDatabase of the drawing </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus		     GetDrawing(const AcPpObjectId& id, AcDbDatabase* & db);

    /// <summary>
    /// Returns the collection of databases related to the specified drawing id
    /// </summary>
	/// <param name= "dwgId"> Drawing ID whose AcDbDatabses are requested</param>
	/// <param name= "dbs"> Container containing AcDbDatabse representing the drawing</param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          GetDrawings (long dwgid, AcArray<AcDbDatabase *> & dbs);

    /// <summary>
    /// Data Links Manager doesn't save to datacache in case if 
    /// drawing database is not associated with document.
    /// The following method allows to override this behavior for 
    /// the specfied none-document database.
    /// Could be only one such database. 
    /// </summary>
    static void         SetDatabaseToForceSaveComplete (AcDbDatabase * db);

    /// <summary>
    /// Get database for which Save behavior is overriden
    /// </summary>
    static AcDbDatabase *  GetDatabaseToForceSaveComplete ();


    /// <summary>
	/// Audit drawing database 
	///</summary>
	/// <param name= "db">AcDbDatabase to audit.</param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus		     AuditDrawing(AcDbDatabase * db, AcPpAuditResults & res);

    /// <summary>
    /// Sets the drawing properties in the cache
    /// the drawing properties are:
    /// PnID  (drawing number)
    /// Dwg Name
    /// Title
    /// Path
    /// Rev
    /// Property names are properties to be set
    /// propvalues are properties values corresponding to the property names
    /// </summary>
	/// <param name= "dwgId"> drawing number </param>
	/// <param name= "propnames"> Property names </param>
	/// <param name= "propvals"> Properties values corresponding to the property names</param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus         SetDrawingProperties (long dwgId,
                                              const AcPpStringArray & propnames,
                                              const AcPpStringArray & propvals);

    /// <summary>
    /// Gets drawing properties from the cache
    /// </summary>
	/// <param name= "dwgId"> Drawing number </param>
	/// <param name= "propnames"> Property names </param>
	/// <param name= "propvals"> Properties values corresponding to the property names</param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus         GetDrawingProperties (long dwgId,
                                              AcPpStringArray & propnames,
                                              AcPpStringArray & propvals);

    /// <summary>
    /// Gets drawing save timestamp guid saved in the drawing database
    /// </summary>
	/// <param name= "dwg"> Drawing Database </param>
	/// <param name= "guidstr"> guid string. Must be released by caller </param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus         GetDwgSaveTimestampGuidFromDrawing (AcDbDatabase * dwg, ACHAR * & guidstr);

    /// <summary>
    /// Gets drawing save timestamp guid saved in the cache database
    /// </summary>
	/// <param name= "dwgid"> Drawing id </param>
	/// <param name= "guidstr"> guid string. Must be released by caller </param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus         GetDwgSaveTimestampGuidFromCache (long dwgid, ACHAR * & guidstr);


    /// <summary>
    /// Creates AcPpObjectId from AcDbObjectId. Data links manager 
    /// uses object handler and embeds internal drawing id into the 
    /// resulting object. If it is not possible to create
    /// acpp object id AcPpObjectId::Null is returned 
    /// </summary>
	/// <param name= "id"> AcDbObjectId as input</param>
	/// <param name= "subindex"> subentity id </param>
	/// <returns> Identifier that is used by AcPpLinkManager to identify AcDb Object</returns>
    AcPpObjectId         MakeAcPpObjectId (const AcDbObjectId & id);
    AcPpObjectId         MakeAcPpObjectId (const AcDbObjectId & id, int subindex);


    /// <summary>
    /// Creates AcDbObjectId from AcPpObjectId. Data links manager 
    /// uses object handler and internal drawing id to create 
    /// a valid AcDbObjectId. If it is not possible to create
    /// acdb object id AcDbObjectId::kNull is returned 
    /// </summary>
	/// <param name= "id"> Identifier that is used by AcPpLinkManager to identify AcDb Object</param>
	/// <param name= "db"> AcDbDatase that owns objectid</param>
	/// <returns> AcDbObjectId created out of AcDbObjectId</returns>
    AcDbObjectId         MakeAcDbObjectId (const AcPpObjectId & id);
    AcDbObjectId         MakeAcDbObjectId (const AcPpObjectId & id, AcDbDatabase * db);

    /// <summary>
    /// Creates AcDbObjectIds from AcPpObjectId for every enlisted AcDbDatabase 
    /// </summary>
	/// <param name= "id"> Identifier that is used by AcPpLinkManager to identify AcDb Object</param>
	/// <param name= "db"> AcDbDatase that owns objectid</param>
	/// <returns> AcDbObjectId created out of AcDbObjectId</returns>
    EPpDLStatus          MakeAcDbObjectIds (const AcPpObjectId & id, AcDbObjectIdArray & objids);

    /// <summary>
    /// Saves all changes to the PnPDatabase .   
    /// </summary>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          AcceptChanges();

    /// <summary>
    /// Accepts changes of the specified drawing
    /// </summary>
	/// <param name= "dwgId"> Specified drawing number</param>
	/// <returns>EPpDLStatus </returns>
    EPpDLStatus          AcceptChanges(long dwgId);


    /// <summary>
    /// Reject changes. Changes will be not saves to the PnP database
    /// </summary>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          RejectChanges ();

    /// <summary>
    /// Reject changes of the specified drawing
    /// </summary>
	/// <param name= "dwgId"> Specified drawing number </param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          RejectChanges (long dwgId);

        /// <summary>

    /// <summary>
    /// Saves all metadata changes to the PnPDatabase. This include 
    /// changes to the tag registry definition.
    /// </summary>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          AcceptMetadataChanges();

    /// <summary>
    /// Reject all metadata changes.   
    /// </summary>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          RejectMetadataChanges();



    /// <summary>
    /// Returns true if data links manager is undoing changes using AutoCAD 
    /// undo mechanism
    /// </summary>
	/// <returns>boolean</returns>
    bool                 IsUndoing (); 


    /// <summary>
	/// Creates empty link for RProject and LDrawing 
	/// 
	/// </summary>
	/// <param name= "oid"> Object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "dwgId"> Specified drawing number </param>
	/// <returns> EPpDLStatus</returns>
	virtual EPpDLStatus  Link     (const AcPpRowId & oid, 
								   const long        dwgId = 0); 


    /// <summary>
    /// Creates link between AcDb Object identified by AcPpObjectId and 
    /// the existent database object identified by AcPpRowId
    /// </summary>
	/// <param name= "oid"> Identifier that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "doid"> Object that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus</returns>
    virtual EPpDLStatus  Link     (const AcPpObjectId & oid, 
								   const AcPpRowId    & doid); 


    /// <summary>
    /// Creates link between AcDb Object identified by AcPpObjectId and 
    /// the existent database object identified by AcPpRowId
    /// </summary>
	/// <param name= "oid"> Object identified by AcDbObjectId </param>
	/// <param name= "doid"> Object that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus</returns>
    virtual EPpDLStatus  Link     (const AcDbObjectId & oid, 
                                   const AcPpRowId    & doid); 


    /// <summary>
    /// Creates an instances of the database object of specified class 
    /// and associates it with AcDb Object. Assigns the identifier of the
    /// created instance to dbod
    /// </summary>
	/// <param name= "oid"> Identifier that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "classname"> String representign the class name </param>
	/// <param name= "dboid"> Object that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus</returns>
    virtual EPpDLStatus  Link     (const AcPpObjectId & oid, 
                                   const ACHAR        * classname,
                                   AcPpRowId          & dboid); 
    /// <summary>
    /// Creates an instances of the database object of specified class 
    /// and associates it with AcDb Object. Assigns the identifier of the
    /// created instance to dbod
    /// </summary>
	/// <param name= "oid"> AcDbObjectId </param>
	/// <param name= "classname"> String representign the class name </param>
	/// <param name= "dboid"> Object that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus</returns>
    virtual EPpDLStatus  Link     (const AcDbObjectId & oid, 
                                   const ACHAR        * classname,
                                   AcPpRowId          & dboid); 

    /// <summary>
    /// Creates an instances of the database object of specified class, 
    /// assignes properties to the instance, and associates it with AcDb Object. 
    /// Assigns the identifier of the
    /// created instance to dbod
    /// Property values are specified using two arrays:
    /// propnames contains property names
    /// propvals contains values that correspond to the properties in the first array
    /// The conversion from string to the actual type is done. IF conversion is 
    /// not possible or property doesn't exist, the value is ignored
    /// </summary>
	/// <param name= "oid"> Identifier that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "classname"> AString representing class name</param>
	/// <param name= "propnames"> Property names </param>
	/// <param name= "propvals"> Properties values corresponding to the property names</param>
	/// <param name= "dboid"> Object that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          LinkSetProperties (
                                   const AcPpObjectId & oid, 
                                   const ACHAR * classname,
                                   const AcPpStringArray & propnames,
                                   const AcPpStringArray & propvals,
                                   AcPpRowId & dboid); 
    /// <summary>
    /// Similar to the one above. Uses AcDbOBjectId to identfy the object in the 
    /// acdbdatabase.
    /// </summary>
	/// <param name= "oid"> Identifier that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "classname"> AString representing class name</param>
	/// <param name= "propnames"> Property names </param>
	/// <param name= "propvals"> Properties values corresponding to the property names</param>
	/// <param name= "dboid"> Object that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          LinkSetProperties (
                                   const AcDbObjectId & oid, 
                                   const ACHAR * classname,
                                   const AcPpStringArray & propnames,
                                   const AcPpStringArray & propvals,
                                   AcPpRowId & dboid); 


    /// <summary>
    /// Assigns properties:
    /// propnames contains property names
    /// propvals contains values that correspond to the properties in the first array
    /// The conversion from string to the actual type is done. IF conversion is 
    /// not possible, the value is ignored
    /// </summary>
	/// <param name= "oid"> Identifier that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "propnames"> Property names </param>
	/// <param name= "propvals"> Properties values corresponding to the property names</param>
	/// <returns> EPpDLStatus</returns>
    virtual EPpDLStatus  SetProperties (
                                   const AcPpObjectId & oid, 
                                   const AcPpStringArray & propnames,
                                   const AcPpStringArray & propvals); 
    /// <summary>
    /// Similar to the one above. Uses AcDbOBjectId to identfy the object in the 
    /// acdbdatabase.
    /// </summary>
	/// <param name= "oid"> AcDbObjectId </param>
	/// <param name= "propnames"> Property names </param>
	/// <param name= "propvals"> Properties values corresponding to the property names</param>
	/// <returns> EPpDLStatus </returns>
    virtual EPpDLStatus  SetProperties (
                                   const AcDbObjectId & oid, 
                                   const AcPpStringArray & propnames,
                                   const AcPpStringArray & propvals); 

    /// <summary>
    /// Similar to the one above. Uses AcPpRowId to identfy the object in the 
    /// acdbdatabase.
    /// </summary>
	/// <param name= "rowid"> Object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "propnames"> Property names </param>
	/// <param name= "propvals"> Properties values corresponding to the property names</param>
	/// <returns> EPpDLStatus</returns>
    virtual EPpDLStatus  SetProperties (
                                   const AcPpRowId & rowid, 
                                   const AcPpStringArray & propnames,
                                   const AcPpStringArray & propvals); 


    /// <summary>
    /// Gets properties of the object that is linked to the cache row:
    /// Property values are returned as strings, If property doesn't 
    /// exists or it is a null value, sero length string is returned
    /// </summary>
	/// <param name= "oid"> Identifier that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "propnames"> Property names </param>
	/// <param name= "propvals"> Properties values corresponding to the property names</param>
	/// <param name= "bCurrentVersion"> Boolean parameter representing current version. Defaulted to true</param>
	/// <returns> EPpDLStatus</returns>
    virtual EPpDLStatus  GetProperties (
                                   const AcPpObjectId & oid, 
                                   const AcPpStringArray & propnames,
                                   AcPpStringArray & propvals,
                                   bool bCurrentVersion = true); 

    /// <summary>
    /// Gets properties of the object that is linked to the cache row:
    /// Property values are returned as strings, If property doesn't 
    /// exists or it is a null value, sero length string is returned
    /// </summary>
	/// <param name= "oid"> AcDbObjectId </param>
	/// <param name= "propnames"> Property names </param>
	/// <param name= "propvals"> Properties values corresponding to the property names</param>
	/// <param name= "bCurrentVersion"> Boolean parameter representing current version. Defaulted to true</param>
	/// <returns> EPpDLStatus</returns>
    virtual EPpDLStatus  GetProperties (
                                   const AcDbObjectId & oid, 
                                   const AcPpStringArray & propnames,
                                   AcPpStringArray & propvals,
                                   bool bCurrentVersion = true); 

    /// <summary>
    /// Gets properties of the object that is specified by the cache rowid:
    /// Property values are returned as strings, If property doesn't 
    /// exists or it is a null value, sero length string is returned
    /// </summary>
	/// <param name= "oid"> Object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "propnames"> Property names </param>
	/// <param name= "propvals"> Properties values corresponding to the property names</param>
	/// <param name= "bCurrentVersion"> Boolean parameter representing current version. Defaulted to true</param>
	/// <returns> EPpDLStatus</returns>
    virtual EPpDLStatus  GetProperties (
                                   const AcPpRowId & oid, 
                                   const AcPpStringArray & propnames,
                                   AcPpStringArray & propvals,
                                   bool bCurrentVersion = true); 

    /// <summary>
    /// Gets all properties of the object that is linked to the cache row:
    /// Property values are returned as strings. The name of the class is 
    /// copied to the caller provided buffer
    /// </summary>
	/// <param name= "oid"> Identifier that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "propnames"> Property names </param>
	/// <param name= "propvals"> Properties values corresponding to the property names</param>
	/// <param name= "bCurrentVersion"> Boolean parameter representing current version. Defaulted to true</param>
	/// <returns> EPpDLStatus</returns>
    virtual EPpDLStatus  GetAllProperties (
                                   const AcPpObjectId & oid, 
                                   AcPpStringArray & propnames,
                                   AcPpStringArray & propvals,
                                   bool bCurrentVersion = true); 

    /// <summary>
    /// Gets all properties of the object that is linked to the cache row:
    /// Property values are returned as strings. The name of the class is 
    /// copied to the caller provided buffer
    /// </summary>
	/// <param name= "oid"> AcDbObjectId </param>
	/// <param name= "propnames"> Property names </param>
	/// <param name= "propvals"> Properties values corresponding to the property names</param>
	/// <param name= "bCurrentVersion"> Boolean parameter representing current version. Defaulted to true</param>
	/// <returns> EPpDLStatus</returns>
    virtual EPpDLStatus  GetAllProperties (
                                   const AcDbObjectId & oid, 
                                   AcPpStringArray & propnames,
                                   AcPpStringArray & propvals,
                                   bool bCurrentVersion = true); 


    /// <summary>
    /// Gets all properties of the object identified by the rowid
    /// Property values are returned as strings. The name of the class is 
    /// copied to the caller provided buffer
    /// </summary>
	/// <param name= "oid"> Object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "propnames"> Property names </param>
	/// <param name= "propvals"> Properties values corresponding to the property names</param>
	/// <param name= "bCurrentVersion"> Boolean parameter representing current version. Defaulted to true</param>
	/// <returns> EPpDLStatus</returns>
    virtual EPpDLStatus  GetAllProperties (
                                   const AcPpRowId & rowId, 
                                   AcPpStringArray & propnames,
                                   AcPpStringArray & propvals,
                                   bool bCurrentVersion = true); 

    /// <summary>
    /// Checks whether the object identified by the rowid has this property
    /// copied to the caller provided buffer
    /// </summary>
	/// <param name= "oid"> AcDbObjectId </param>
	/// <param name= "iPropertyName"> Property Name</param>
	/// <returns> bool</returns>
	bool				  HasProperty (
                                    const AcDbObjectId  & oid, 
									const ACHAR *		iPropertyName); 

    /// <summary>
    /// Checks whether the object identified by the rowid has this property
    /// copied to the caller provided buffer
    /// </summary>
	/// <param name= "oid"> Objectthat uniquly identifies data object in the PnP Database </param>
	/// <param name= "iPropertyName"> Property Name</param>
	/// <returns> bool</returns>
	bool				  HasProperty (
                                    const AcPpObjectId  & oid, 
									const ACHAR *		iPropertyName); 
    /// <summary>
    /// Checks whether the object identified by the rowid has this property
    /// copied to the caller provided buffer
    /// </summary>
	/// <param name= "rowid"> Row id that uniquly identifies data object in the PnP Database </param>
	/// <param name= "iPropertyName"> Property Name</param>
	/// <returns> bool</returns>
	bool				  HasProperty (
									const AcPpRowId		& rowId, 
									const ACHAR *		iPropertyName);     
	
	/// <summary>
    /// Gets object class name
    /// </summary>
	/// <param name= "oid"> Identifier that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "classname"> String representing the class name</param>
	/// <param name= "len"> Length of the string buffer </param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          GetObjectClassname (
                                   const AcPpObjectId & oid, 
                                   ACHAR * classname,
                                   int       len);

    /// <summary>
    /// Gets object class name
    /// </summary>
	/// <param name= "oid"> AcDbObjectId </param>
	/// <param name= "classname"> String representing the class name</param>
	/// <param name= "len"> Length of the string buffer </param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          GetObjectClassname (
                                   const AcDbObjectId & oid, 
                                   ACHAR * classname,
                                   int       len);

    /// <summary>
    /// Gets object class name
    /// </summary>
	/// <param name= "rowId"> Object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "classname"> String representing the class name</param>
	/// <param name= "len"> Length of the string buffer </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          GetObjectClassname (
                                   const AcPpRowId & rowId, 
                                   ACHAR * classname,
                                   int       len);

    /// <summary>
	/// remove the association from map based on database object id.
	/// if bDelete is set to true, also delete the database object
	/// </summary>
	/// <param name= "dboid"> Identifier that is used by AcPpLinkManager to identify database Object</param>
	/// <param name= "bDelete"> Boolean to decide if it should delete the database or not </param>
	/// <returns> EPpDLStatus</returns>
	virtual EPpDLStatus  Unlink     (const AcPpRowId & dboid, 
									 bool bDelete); 

	/// <summary>
    /// disassociates the AcDb Object and the database object.
    /// if bDelete is set to true, also delete the database object
    /// </summary>
	/// <param name= "oid"> Identifier that is used by AcPpLinkManager to identify AcDb Object</param>
	/// <param name= "bDelete"> Boolean to decide if it should delete the database or not </param>
	/// <returns> EPpDLStatus</returns>
	virtual EPpDLStatus  Unlink     (const AcPpObjectId & oid, 
                                     bool bDelete); 

    /// <summary>
    /// disassociates the AcDb Object and the database object.
    /// if bDelete is set to true, also delete the database object
    /// </summary>
	/// <param name= "oid"> AcDbObjectId </param>
	/// <param name= "bDelete"> Boolean to decide if it should delete the database or not </param>
	/// <returns> EPpDLStatus </returns>
    virtual EPpDLStatus  Unlink     (const AcDbObjectId & oid, 
                                     bool bDelete); 

    /// <summary>
    /// Returns an array AcPpObjectIds associated with the 
    /// database id and are currently in memory
    /// </summary>
	/// <param name= "dboid"> Object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "oids"> List of identifiers those are used by AcPpLinkManager to identify AcDb Object </param>
	/// <returns> EPpDLStatus </returns>
    virtual EPpDLStatus  FindAcPpObjectIds (
                                            const AcPpRowId & dboid,
                                            AcPpObjectIdArray & oids); 

    /// <summary>
    /// Returns an array AcPpObjectIds associated with the 
    /// database id 
    /// </summary>
	/// <param name= "dboid"> Object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "oids"> List of identifiers those are used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "bInMemroy"> if true, only in-memroy map will be looked </param>
	/// <returns> EPpDLStatus </returns>

    virtual EPpDLStatus  FindAcPpObjectIds (
                                            const AcPpRowId & dboid,
                                            AcPpObjectIdArray & oids,
                                            bool bInMemoryOnly); 


    /// <summary>
    /// Returns AcPpRowId associated with the 
    /// AcPpObjectID
    /// </summary>
	/// <param name= "oid"> Identifier that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "dboid"> Requested object that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          FindAcPpRowId (
                                            const AcPpObjectId & oid,
                                            AcPpRowId & dboid);

    /// <summary>
    /// Returns AcPpRowId associated with the 
    /// AcDbObjectID
    /// </summary>
	/// <param name= "oid"> AcDbObjectId whose AcPpRowId is requested </param>
	/// <param name= "dboid"> Object that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          FindAcPpRowId (
                                            const AcDbObjectId & oid,
                                            AcPpRowId & dboid);


    /// <summary>
    /// Returns AcPpObjectArray of object subids for the given pp object id.
    /// Object subid has the same drawing id and handle as the pp object id, but 
    /// different subindex.
    /// </summary>
	/// <param name= "oid"> AcPpObjectId whose subids are requested </param>
	/// <param name= "soids"> Array of object subids </param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          SelectObjectSubIds (
                                            const AcPpObjectId & oid,
                                            AcPpObjectIdArray  & soids);
                                            
    /// <summary>
    /// Returns an array database ids in the given drawing  
    /// </summary>
	/// <param name= "dwgid"> Drawing id</param>
	/// <param name= "dboids"> Array of objects that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          SelectAcPpRowIds (
                                            long             dwgid,
                                            AcPpRowIdArray & dboids); 


    /// <summary>
    /// Returns an array database ids in the given drawing  
    /// </summary>
	/// <param name= "dwg"> Drawing AcDbDatabase </param>
	/// <param name= "dboids"> Array of object that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          SelectAcPpRowIds (
                                            const AcDbDatabase   * dwg,
                                            AcPpRowIdArray & dboids); 


    /// <summary>
    /// Returns an array database ids in the given drawing that are of the 
    /// specified class
    /// </summary>
	/// <param name= "dwgid"> Drawing id</param>
	/// <param name= "classname"> string representing the class name </param>
	/// <param name= "dboids"> Array of objects that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          SelectAcPpRowIds (
                                            long             dwgid,
                                            const ACHAR  * classname,
                                            AcPpRowIdArray & dboids); 

    /// <summary>
    /// Returns an array database ids in the given drawing that are of the 
    /// specified class
    /// </summary>
	/// <param name= "dwg"> Drawing AcDbDatabase </param>
	/// <param name= "classname"> string representing the class name </param>
	/// <param name= "dboids"> Array of objects that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          SelectAcPpRowIds (
                                            const AcDbDatabase   * dwg,
                                            const ACHAR  * classname,
                                            AcPpRowIdArray & dboids); 



    /// <summary>
    /// Returns an array database ids associated with the 
    /// provided AcPpObjectIds
    /// </summary>
	/// <param name= "oids"> Array of identifiers those are used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "dboids"> Array of objects that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          SelectAcPpRowIds (
                                            const AcPpObjectIdArray & oids,
                                            AcPpRowIdArray & dboids);


    /// <summary>
    /// Returns an array AcPpObjectIds associated with the 
    /// provided database ids
    /// </summary>
	/// <param name= "dboids">Array of objects that uniquly identifies data object in the PnP Database  </param>
	/// <param name= "oids"> Array of identifiers those are used by AcPpLinkManager to identify AcDb Object </param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          SelectAcPpObjectIds (
                                            const AcPpRowIdArray & dboids,
                                            AcPpObjectIdArray    & oids); 

    /// <summary>
    /// Returns true if object has links
    /// </summary>
	/// <param name= "oid"> Identifier that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <returns> True if object has links. False otherwise</returns>
    bool                 HasLinks (const AcPpObjectId & oid);

    /// <summary>
    /// Returns true if object has links
    /// </summary>
	/// <param name= "oid"> AcDbObjectId </param>
	/// <returns> True if object has links. False otherwise </returns>
    bool                 HasLinks (const AcDbObjectId & oid);

    /// <summary>
    /// Returns true if object is used by AcPpLinkManager to identify AcDbObject
    /// </summary>
	/// <param name= "rowid"> Object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "bInMemoryOnly"> if true only in-memory links will be looked.
    /// By default only in-memory look up is done</param>
	/// <returns> True if object has links. False otherwise </returns>
    bool                 HasLinks (const AcPpRowId & rowid);
    bool                 HasLinks (const AcPpRowId & rowid, bool bInMemoryOnly);


    /// <summary>
    /// Returns true if object is linked to the object in the drawing 
    /// specified by drawing id 
    /// drawing id from AcDbDatabase is returned by 
    ///   long  GetDrawingId (AcDbDatabase * db);
    /// </summary>
	/// <param name= "rowid"> Object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "dwgid"> Drawing id </param>
	/// <returns> True if object has links. False otherwise </returns>
    bool                 HasLinksInDwg (const AcPpRowId & rowid,
                                         long             dwgid);

    /// <summary>
    /// Refreshes in-memory link map. 
    /// Data links manager keeps linkage iformation between AutoCAD objects and 
    /// row in memory. This methods refreshes the map for drawing that are 
    /// not currenly loaded in AutoCAD session.
    /// This method is not called by the Data Links Manager automatically, because 
    /// it may cause performace degradation. 
    /// Caller may consider refrteshing the map before the followig methods call:
    ///  HasAcPpRowIds ()
    ///  SelectAcPpRowIds
    ///  HasLink
    /// Performance of RefreshLinkMap depends on the number of drawings 
    /// registered in the Data Links Manager
    /// </summary>
	/// <param name= "dwgid">
    /// Drawing id for which to refresh link map.
    /// -1 means refresh map for all enlisted drawings
    /// </param>
	/// <returns>nothing.</returns>
    void                 RefreshLinkMap (int dwgid);

    /// <summary>
    /// Establish specified relationship between two AcPpObject. 
    /// To create a relationship, the object roles must be specified.
    /// The relationship type has to exist in the schema 
    /// Link'ed with any cache row. If they are not, ePpDLObjectDoesNotHaveLink
    /// status is returned
    /// </summary>
	/// <param name= "relationshipType"> Relationship type</param>
	/// <param name= "role1"> String representing role of first object </param>
	/// <param name= "oid1"> Identifier of the first object, that is used by AcPpLinkManager to identify AcDb Object  </param>
	/// <param name= "role2"> String representing role of second object </param>
	/// <param name= "oid2"> Identifier of the second object that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          Relate (const ACHAR * relationshipType,
                                 const ACHAR * role1, const AcPpObjectId & oid1, 
                                 const ACHAR * role2, const AcPpObjectId & oid2);



    /// <summary>
    /// Establish specified relationship between two AcDbObject. 
    /// To create a relationship, the object roles must be specified.
    /// The relationship type has to exist in the schema 
    /// Link'ed with any cache row. If they are not, ePpDLObjectDoesNotHaveLink
    /// status is returned
    /// </summary>
	/// <param name= "relationshipType"> Relationship type</param>
	/// <param name= "role1"> String representing role of first object </param>
	/// <param name= "oid1"> AcDbObjectId of the first object </param>
	/// <param name= "role2"> String representing role of second object </param>
	/// <param name= "oid2"> AcDbObjectId of the second object </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          Relate (const ACHAR * relationshipType,
                                 const ACHAR * role1, const AcDbObjectId & oid1, 
                                 const ACHAR * role2, const AcDbObjectId & oid2);




    /// <summary>
    /// Establish specified relationship between two rows in the cache. 
    /// To create a relationship, the object roles must be specified.
    /// The relationship type has to exist in the schema 
    /// status is returned
    /// </summary>
	/// <param name= "relationshipType"> Relationship type</param>
	/// <param name= "role1"> String representing role of first object </param>
	/// <param name= "oid1"> ID of first object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "role2"> String representing role of second object </param>
	/// <param name= "oid2"> ID of second object that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          Relate (const ACHAR * relationshipType,
                                 const ACHAR * role1, const AcPpRowId & rid1, 
                                 const ACHAR * role2, const AcPpRowId & rid2);


    /// <summary>
    /// Establish ReferenceRelationship between two AcPpObject. Each object references 
    /// and is being referenced by another one. 
    /// Objects must be Link'ed with any cache row. If they are not, 
    /// ePpDLObjectDoesNotHaveLink status is returned
    /// This method is equivalent to the following two calls:
    /// Relate ("ReferenceRelationship", 
    ///         "Referencing", oid1,
    ///         "Referenced", oid2);
    /// Relate ("ReferenceRelationship", 
    ///         "Referencing", oid2,
    ///         "Referenced", oid1);
    /// </summary>
	/// <param name= "oid1"> Identifier of the first object, that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "oid2"> Identifier of the second object that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          Relate (const AcPpObjectId & oid1, const AcPpObjectId & oid2);

    /// <summary>
    /// Establish relationship between two AcDbObject. Objects must be 
    /// Link'ed with any cache row. If they are not,  ePpDLObjectDoesNotHaveLink 
    /// status is returned
    /// </summary>
	/// <param name= "rid1"> First of the two objects whose relationship is to be established </param>
	/// <param name= "rid2"> Second of the two objects whose relationship is to be established </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          Relate (const AcDbObjectId & oid1, const AcDbObjectId & oid2);


    /// <summary>
    /// Establish relationship between two AcPpRowIds
    /// </summary>
	/// <param name= "rid1"> ID of first object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "rid2"> ID of second object that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          Relate (const AcPpRowId & rid1, const AcPpRowId & rid2);

    /// <summary>
    /// Establish a relationship as defined in the AcPpCommonRelationship
    /// </summary>
	/// <param name= "rel"> Contains the relationship type, the roles, and the objects to be related. </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          Relate (const AcPpCommonRelationship & rel);

    /// <summary>
    /// Breaks  relationship between two AcPpObjects.
    /// </summary>
	/// <param name= "relationshipType"> Relationship type</param>
	/// <param name= "role1"> String representing role of first object </param>
	/// <param name= "oid1"> Identifier of the first object, that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "role2"> String representing role of second object </param>
	/// <param name= "oid2"> Identifier of the second object that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          Unrelate (const ACHAR * relationshipType,
                                   const ACHAR * role1, const AcPpObjectId & oid1, 
                                   const ACHAR * role2, const AcPpObjectId & oid2);


    /// <summary>
    /// Breaks  relationship between two AcDbObjects.
    /// </summary>
	/// <param name= "relationshipType"> Relationship type</param>
	/// <param name= "role1"> String representing role of first object </param>
	/// <param name= "oid1"> AcDbObjectId of the first object </param>
	/// <param name= "role2"> String representing role of second object </param>
	/// <param name= "oid2"> AcDbObjectId of the second object </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          Unrelate (const ACHAR * relationshipType,
                                   const ACHAR * role1, const AcDbObjectId & oid1, 
                                   const
                                    ACHAR * role2, const AcDbObjectId & oid2);



    /// <summary>
    /// Breaks  relationship between two rows in the cache.
    /// </summary>
	/// <param name= "relationshipType"> Relationship type</param>
	/// <param name= "role1"> String representing role of first object </param>
	/// <param name= "oid1"> ID of first object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "role2"> String representing role of second object </param>
	/// <param name= "oid2"> ID of second object that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          Unrelate (const ACHAR * relationshipType,
                                   const ACHAR * role1, const AcPpRowId & rid1, 
                                   const ACHAR * role2, const AcPpRowId & rid2);


	/// <summary>
    /// Breaks  reference relationships between two AcPpObjects.
    /// The same as 
    /// Unrelate ("ReferenceRelationship", 
    ///         "Referencing", oid1,
    ///         "Referenced", oid2);
    /// Unrelate ("ReferenceRelationship", 
    ///         "Referencing", oid2,
    ///         "Referenced", oid1);
    /// </summary>
	/// <param name= "oid1"> Identifier of the first object, that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "oid2"> Identifier of the second object that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          Unrelate (const AcPpObjectId & oid1, const AcPpObjectId & oid2);

    /// <summary>
    /// Breaks  relationship between two AcDbObjects.
    /// </summary>
	/// <param name= "oid1"> First of the two objects whose relationship is to be broken </param>
	/// <param name= "oid2"> Second of the two objects whose relationship is to be broken </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          Unrelate (const AcDbObjectId & oid1, const AcDbObjectId & oid2);


    /// <summary>
    /// Breaks  relationship between two rowids
    /// </summary>
	/// <param name= "rid1">ID of first object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "rid2"> ID of second object that uniquly identifies data object in the PnP Database </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          Unrelate (const AcPpRowId & rid1, const AcPpRowId & rid2);


    /// <summary>
    /// Breaks relationship defined in the AcPpCommonRelationship
    /// </summary>
	/// <param name= "rel"> Contains the relationship type, the roles, and the objects of the relationship to be broken. </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          Unrelate (const AcPpCommonRelationship & rel);

    /// <summary>
    /// Get an array of AcPpObjectId that are in specified relationship with 
    /// the object in the specified role
    /// </summary>
	/// <param name= "relationshipType"> Relationship type</param>
	/// <param name= "role1"> String representing role of first object </param>
	/// <param name= "oid1"> Identifier of the first object, that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "role2"> String representing role of second object </param>
	/// <param name= "oids"> Array of AcPpObjectId  </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          GetRelatedAcPpObjectIds (
                                    const ACHAR * relationshipType,
                                    const ACHAR * role1, const AcPpObjectId & oid1, 
                                    const ACHAR * role2, AcPpObjectIdArray & oids);


	/// <summary>
    /// Get related row IDs that are in specified relationship with the object in the specified role
    /// </summary>
	/// <param name= "relationshipType"> Relationship type</param>
	/// <param name= "role1"> String representing role of first object </param>
	/// <param name= "rid1"> ID of object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "role2"> String representing role of second object </param>
	/// <param name= "rids"> Array of objects that uniquly identifies data object in the PnP Database  </param>
	/// <returns> EPpDLStatus </returns>
    virtual EPpDLStatus   GetRelatedRowIds (
                                    const ACHAR * relationshipType,
                                    const ACHAR * role1, const AcPpRowId & rid1, 
                                    const ACHAR * role2, AcPpRowIdArray & rids);


    /// <summary>
    /// Get an array of AcPpRowIds related to the row via ReferenceRelationship
    /// </summary>
	/// <param name= "rid"> ID of object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "rids"> Array of objects that uniquly identifies data object in the PnP Database</param>
	/// <returns>EPpDLStatus </returns>
    virtual EPpDLStatus   GetRelatedRowIds       (const AcPpRowId & rid, 
                                                  AcPpRowIdArray & rids);


    /// <summary>
    /// Get an array of AcPpCommonRelationship Objects. Each item in the array
    /// describes relationship in which specified object participate
    /// </summary>
	/// <param name= "rid"> ID of object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "relationships"> array of AcPpCpmmonRelationship Objects </param>
	/// <returns>EPpDLStatus </returns>
    virtual EPpDLStatus   GetRelatedRowIds (
                                    const AcPpRowId & rid, 
                                    AcPpCommonRelationshipArray & relationships);

    /// <summary>
    /// Get an array of AcPpCommonRelationship Objects of specified relationship type. 
    /// Each item in the array
    /// describes relationship in which specified object participate
    /// </summary>
	/// <param name= "rid"> ID of object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "relationshipType"> Relationship type</param>
	/// <param name= "relationships"> array of AcPpCpmmonRelationship Objects </param>
	/// <returns>EPpDLStatus </returns>

    virtual EPpDLStatus   GetRelatedRowIds (
                                    const ACHAR *                 relationshipType,
                                    const AcPpRowId             & rid, 
                                    AcPpCommonRelationshipArray & relationships);



    /// <summary>
    /// Get an array of AcPpObjectId that are in specified relationship with 
    /// the object in the specified role
    /// </summary>
	/// <param name= "relationshipType"> Relationship type</param>
	/// <param name= "role1"> String representing role of first object </param>
	/// <param name= "oid1"> Identifier of the first AcDb Object </param>
	/// <param name= "role2"> String representing role of second object </param>
	/// <param name= "oids"> Array of AcDbObjectId  </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          GetRelatedAcDbObjectIds (
                                    const ACHAR * relationshipType,
                                    const ACHAR * role1, const AcDbObjectId & oid1, 
                                    const ACHAR * role2, AcDbObjectIdArray & oids);


    /// <summary>
    /// Get an array of AcPpObjectIds related to the object via ReferenceRelationship
    /// The same as 
    /// GetRelatedAcPpObjectIds ("ReferenceRelationship", 
    ///                          "Referencing", oid1,
    ///                          "Referenced", oids);
    /// </summary>
	/// <param name= "oid"> Identifier that is used by AcPpLinkManager to identify AcDb Object </param>
	/// <param name= "oids"> Array of AcPpObjectIds related to the specified AcPpObjectId</param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          GetRelatedAcPpObjectIds (const AcPpObjectId & oid, 
                                                  AcPpObjectIdArray & oids);

    /// <summary>
    /// Get an array of AcDbObjectId related to the specified object
    /// only object ids in the currently opened drawings are returned
    /// </summary>
	/// <param name= "oid"> AcDbObjectId </param>
	/// <param name= "oids"> Array of AcDbObjectId related to the specified object </param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          GetRelatedAcDbObjectIds (const AcDbObjectId & oid, 
                                                  AcDbObjectIdArray & oids);

    /// <summary>
    /// Merge two rows
    /// destination row inherits all sorce row relationships and links to
    /// AcPpObjects. The source row is deleted
    /// </summary>
	/// <param name= "dstId"> Destination ID of object that uniquly identifies data object in the PnP Database </param>
	/// <param name= "srcId"> Source ID of object that uniquly identifies data object in the PnP Database</param>
	/// <returns>EPpDLStatus </returns>
    EPpDLStatus          MergeRows  (AcPpRowId &dstId, AcPpRowId & srcId);


    /// <summary>
    /// Ensure that specified rows and immediate relatives are loaded
    /// This method could be used before operating on a collection of rows to 
    /// improve perfirmance
    /// </summary>
	/// <param name= "rowids"> Array of objects that uniquly identifies data object in the PnP Database</param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          EnsureRowsLoaded (AcPpRowIdArray & rowids);


    /// <summary>
    /// Add Data Link Operation listener
    /// </summary>
	/// <param name= "listener"> Pointer to Data Link Operation listener</param>
	/// <returns> Void </returns>
    void                 AddOperationListner (AcPpDataLinkOperationListener * listener);

    /// <summary>
    /// Remov Data Link Operation listener
    /// </summary>
	/// <param name= "listener"> Pointer to Data Link Operation listener</param>
	/// <returns> Void </returns>
    void                 RemoveOperationListner (AcPpDataLinkOperationListener * listener);


    /// <summary>
    /// Gets the PnPDatabase associated with the Link Manager as a 
    /// void pointer
    /// PnPDatabase object can be retrived as following:
    /// void * ptr = dlm->GetPnPDatabase ();
    /// GCHandle gch = GCHandle::operator GCHandle(System::IntPtr(ptr));
    /// PnPDatabase ^ db = (PnPDatabase ^ ) gch.Target;
    /// gch.Free () // must release
    /// </summary>
	/// <returns> </returns>
    void *               GetPnPDatabaseGCHandle ();

    /// <summary>
    /// returns true if tabname directly or inderectly derives from 
    /// basetab 
    /// </summary>
	/// <param name= "tabname"> String representing tab name</param>
	/// <param name= "basetab"> String representing base table</param>
	/// <returns> Returns true if tabname is directly or indirectly derived from base tab </returns>
    bool                 IsKindOf (const ACHAR * tabname, 
                                   const ACHAR * basetab);

    /// <summary>
    /// Returns the base table of the specified tabname 
    /// </summary>
	/// <param name= "tabname"> String representing tab name</param>
	/// <param name= "basetab"> String representing base table</param>
	/// <param name= "len"> Length of the buffer containing the base table name</param>
	/// <returns>EPpDLStatus </returns>
    EPpDLStatus          GetBaseTable (const ACHAR * tabname, 
                                       ACHAR * basetab, int len);

    /// <summary>
    /// Returns the collection of table names derived from the 
    /// specified one.
    /// </summary>
	/// <param name= "tabname"> String representing  </param>
	/// <param name= "dertabs"> Collection of table names derived from the specified one.</param>
	/// <returns>EPpDLStatus </returns>
    EPpDLStatus          GetDerivedTables (const ACHAR * tabname, 
                                           AcPpStringArray & dertabs);
    


    /// <summary>
    /// Returns all table attributes for the specified tabname 
    /// </summary>
	/// <param name= "tabname"> String representing the table name</param>
	/// <param name= "attrnames"> String array of attribute names</param>
	/// <param name= "attrvalues"> String array of attribute values </param>
	/// <param name= "attrtypes"> String array of attributes types</param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          GetTableAttributesForTable  (const ACHAR * tabname, 
                                                      AcPpStringArray & attrnames,
                                                      AcPpStringArray & attrvalues,
                                                      AcPpStringArray & attrtypes);

    /// <summary>
    /// Returns specified table attribute for the specified tabname 
    /// </summary>
	/// <param name= "tabname"> String representing the table name </param>
	/// <param name= "attrname"> String representing attribute names </param>
	/// <param name= "attrvalue"> String representing attribute values </param>
	/// <param name= "len1"> Buffer size determining length of attribute value </param>
	/// <param name= "attrtype"> Strign representing attribute type</param>
	/// <param name= "len2"> Buffer size determining length of attribute type </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          GetTableAttributeForTable  (const ACHAR * tabname, 
                                                     const ACHAR * attrname,
                                                     ACHAR * attrvalue, int len1,
                                                     ACHAR * attrtype, int len2);


    /// <summary>
    /// Returns all column attributes for the specified table column 
    /// </summary>
	/// <param name= "tabname"> String representing the table name </param>
	/// <param name= "colname"> Column attributes </param>
	/// <param name= "attrnames"> String array of attribute names</param>
	/// <param name= "attrvalues"> String array of attribute values </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          GetColumnAttributesForTable  (const ACHAR * tabname, 
                                                       const ACHAR * colname,
                                                       AcPpStringArray & attrnames,
                                                       AcPpStringArray & attrvalues);

    /// <summary>
    /// Returns specified column attribute for the specified table column 
    /// </summary>
	/// <param name= "tabname"> String representing the table name </param>
	/// <param name= "colname"> Column attributes </param>
	/// <param name= "attrnames"> String representing attribute names</param>
	/// <param name= "attrvalues"> String representing attribute values </param>
	/// <param name= "len"> Length determining the length on attribute values </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          GetColumnAttributeForTable  (const ACHAR * tabname, 
                                                      const ACHAR * colname,
                                                      const ACHAR * attrrame,
                                                      ACHAR * attrvalue, int len);

    /// <summary>
    /// Gets all properties of the given table
    /// </summary>
	/// <param name= "tabname"> String representing the table name </param>
	/// <param name= "propnames"> String array of property names </param>
	/// <param name= "propvals"> String array of property values</param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          GetDefaultValuesForAllProperties (
                                   const ACHAR * tabname,  
                                   AcPpStringArray & propnames,
                                   AcPpStringArray & propvals); 

    /// <summary>
    /// true Data Links Manager system class
    /// </summary>
	/// <param name= "name"> String representing the data links manager</param>
	/// <returns> Boolean </returns>
    bool                 IsSystemTable (const ACHAR * name);

    /// <summary>
    /// Checks whether a column is system or not.
    /// </summary>
    /// <param name= "tableName"> Table name</param>
    /// <param name= "columnName"> Column name</param>
    /// <returns> Boolean </returns>
    bool                 IsSystemColumn (const ACHAR * tableName,
                                         const ACHAR * columnName);

    /// <summary>
    /// true if a table with a specifed name is found
    /// </summary>
	/// <param name= "name"> String representing the table to look for</param>
	/// <returns> Boolean </returns>
    bool                 HasTable (const ACHAR * name);

    /// <summary>
    /// Tag registry manipulations 
    /// </summary>
	/// <param name ="name"> String representing tag </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          CreateTagRegistry (const ACHAR * name);

	/// <summary>
    ///  Enlist column in tag registry
    /// </summary>
	/// <param name ="name"> Tag name </param>
	/// <param name ="tabname">Table name </param>
	/// <param name ="colname"> Column name </param>
	/// <returns> EPpDLStatus </returns>
    EPpDLStatus          EnlistColumnInTagRegistry (const ACHAR * name, 
                                            const ACHAR * tabname,
                                            const ACHAR * colname);


    /// <summary>
    /// Given the tag registry name, table and column names enlisted in the 
    /// tag registry, original tag and id of the row id to which tag is going to be 
    /// assinged, return the candidate tag.
    /// The candidate tag is the internal value inserted into the tag registry. It may be 
    /// differnt from the original tag. The candiate tag is made by the 
    /// handler of AcPpDataLinkOperationListener::TagRegistryOperationOccurred (
    /// EPpTagRegistryAction::ePpCandidateTagNeeded) event
    /// </summary>
    /// <param name= "tagregname">Tag registry name.</param>
    /// <param name= "tabname">Enlisted table name.</param>
    /// <param name= "colname">Enlisted column name.</param>
    /// <param name= "rowid">Id of the row for which get candidate tag.</param>
    /// <param name= "tag">Original tag.</param>
	/// <param name= "candidatetag">Candidate tag. Caller must release the returned buffer.</param>
	/// <returns>Nothing.</returns>
    void                 GetCandidateTag (const ACHAR * tagregname, 
                                          const ACHAR * tabname,
                                          const ACHAR * colname,
                                          const AcPpRowId & rowid,
                                          const ACHAR * tag,
                                          ACHAR * &     candidatetag);
    
    
    /// <summary>
    /// Finds the ID of object that uniquly identifies data object in the PnP Database, 
    /// given a tag.
    /// The tag should be a candidate tag. Candidate tag may be different from the original 
    /// tag and is obtained for the given row using GetCandidateTag method.
    /// </summary>
	/// <param name= "name">Tag registry  name used for requesting the row</param>
	/// <param name= "tag"> tag used for requesting the row</param>
	/// <returns> Returns ID of object that uniquly identifies data object in the PnP Database </returns>
    AcPpRowId            FindRowByTag (const ACHAR * tagregname, const ACHAR * tag);


    /// <summary>
	/// Audit tag registry 
	///</summary>
	/// <param name= "tagregname">Tag registry to audit.</param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus		     AuditTagRegistry (const ACHAR * tagregname, AcPpAuditResults & res);

    /// <summary>
	/// Get tag registry names 
	///</summary>
	/// <param name= "tncoll">Collection of tag registry names.</param>
	/// <returns> Nothing.</returns>
    void                 GetTagRegistries (AcPpStringArray & tncoll);


    /// <summary>
	/// Get columns enlisted in tag registry 
	///</summary>
	/// <param name= "tagregname">Tag registry name.</param>
	/// <param name= "tabnames">Table names.</param>
	/// <param name= "colname">Column names.</param>
	/// <returns> EPpDLStatus</returns>
    EPpDLStatus          GetTagEnlistedColumns (const ACHAR * tagregname,
                                                AcPpStringArray & tabnames,
                                                AcPpStringArray & colname);


    /// <summary>
	/// Audit links ///</summary>
	/// <returns> EPpDLStatus</returns>try 
	EPpDLStatus		     AuditLinks  (AcPpAuditResults & res);

    /// <summary>
	/// Get disable undo recoording status. If true, data link manager 
    /// events are being recorded for undo
	///</summary>
	/// <returns>bool</returns>
    bool                 GetDisableUndoRecording ();

    /// <summary>
	/// Set disable undo recoording status. If true, data link manager 
    /// events are being recorded for undo
	///</summary>
    void                 SetDisableUndoRecording (bool b);

    /// <summary>
    /// Returns implementation 
    /// </summary>
	/// <returns> pointer to the implementation class AcPpDataLinksManagerImp </returns>
    AcPpDataLinksManagerImp *   Imp ();

protected:

    AcPpDataLinksManagerImp * m_imp;
};



