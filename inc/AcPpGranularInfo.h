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
// AcPpGranularInfo.h
//
//  DESCRIPTION: AcPpStyle API class declaration
//
//    AcDbObject
//      AcPpGranularObject
//        AcPpGranularTubing
//        AcPpGranularTee
//		  AcPpGranularInlineAsset

#pragma once

#include "dbmain.h"
#include "PnPDllDef.h"

class AcPpImpGranularObject; 
class AcPpImpGranularTubing;
class AcPpImpGranularTee;
class AcPpImpGranularInlineAsset;
class AcPpImpGranularInfo;


//-----------------------------------------------------------------------------
class PNIDOBJECTS_API AcPpGranularObject : public AcDbObject
{

public:
	ACRX_DECLARE_MEMBERS(AcPpGranularObject);

	/// <summary>
	/// Default constructor. Creates a new AcPpImpGranularObject object. 
	/// </summary>
	AcPpGranularObject();

	/// <summary>
	/// Default destructor.  
	/// </summary>
	virtual ~AcPpGranularObject();

	/// <summary>
	/// This function returns the sequence number of the component on the line. 
	/// It starts from 1 and increases as we traverse from source to destination. 
	/// A sequence number of zero indicates the component isnot fully initialized
	/// </summary>
	/// <returns> Sequence number of the component </returns>	
	Adesk::UInt32 sequenceNumber() const;

	/// <summary>
	/// This function sets the sequence number of the component on the line. 
	/// It starts from 1 and increases as we traverse from source to destination. 
	/// </summary>
	/// <param name = "nSequenceNumber"> Sequence number of the component in Adesk::UInt32 </param>	
	void setSequenceNumber(const Adesk::UInt32 nSequenceNumber);

	/// <summary>
	/// The line segment id is a hard pointer to the line that owns the component. 
	/// </summary>
	/// <returns> Line segment ID as AcDbObjectId </returns>	
	AcDbObjectId lineId() const;

	/// <summary>
	/// This function sets the line segment id which is a hard pointer to the line that owns the component. 
	/// </summary>
	/// <param name = "lineId"> Line segment ID as reference to AcDbObjectId </param>	
	void setLineId(const AcDbObjectId& lineId);

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

protected:
	AcPpGranularObject(bool bImpDone);
	AcPpImpGranularObject *mpImpGranularObject; 
};

//-----------------------------------------------------------------------------
class PNIDOBJECTS_API AcPpGranularTubing : public AcPpGranularObject
{
public:
	ACRX_DECLARE_MEMBERS(AcPpGranularTubing);

	/// <summary>
	/// Default constructor. Creates a new AcPpImpGranularTubing object. 
	/// </summary>
	AcPpGranularTubing();

	/// <summary>
	/// Default destructor.  
	/// </summary>
	virtual ~AcPpGranularTubing();
	// AcDbObject overrides
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

protected:
	AcPpGranularTubing(bool bImpDone);
};

//-----------------------------------------------------------------------------
class PNIDOBJECTS_API AcPpGranularTee : public AcPpGranularObject
{

public:
	ACRX_DECLARE_MEMBERS(AcPpGranularTee);
	
	/// <summary>
	/// Default constructor. Creates a new AcPpImpGranularTee object. 
	/// </summary>
	AcPpGranularTee();

	/// <summary>
	/// Default destructor.  
	/// </summary>
	virtual ~AcPpGranularTee();

	/// <summary>
	/// The component id is a soft pointer to the other line segment object that is connected forming the tee.
	/// </summary>
	/// <returns> Component ID as AcDbObjectId </returns>	
	AcDbObjectId connectedLineId() const;

	/// <summary>
	/// This function sets the component ID which is a soft pointer to the other line segment object. 
	/// </summary>
	/// <param name = "entityId"> Reference of component ID  </param>	
	void setConnectedLineId(const AcDbObjectId& entityId);

	// AcDbObject overrides
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

protected:
	AcPpGranularTee(bool bImpDone);
};

//-----------------------------------------------------------------------------
class PNIDOBJECTS_API AcPpGranularInlineAsset : public AcPpGranularObject
{

public:
	ACRX_DECLARE_MEMBERS(AcPpGranularInlineAsset);

	/// <summary>
	/// Default constructor. Creates a new AcPpImpGranularInlineAsset object. 
	/// </summary>
	AcPpGranularInlineAsset();

	/// <summary>
	/// Default destructor.  
	/// </summary>
	virtual ~AcPpGranularInlineAsset();

	/// <summary>
	/// The component id is a soft pointer to the asset object that is connected. 
	/// This asset can be a block reference or an AcPpAsset object.
	/// </summary>
	/// <returns> Component ID as AcDbObjectId </returns>	
	AcDbObjectId assetId() const;

	/// <summary>
	/// This function sets the component ID which is a soft pointer to the asset object that is connected. 
	/// </summary>
	/// <param name = "entityId"> Reference of component ID </param>	
	void setAssetId(const AcDbObjectId& entityId);

	// AcDbObject overrides
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

protected:
	AcPpGranularInlineAsset(bool bImpDone);
};

//-----------------------------------------------------------------------------
PNIDOBJECTS_API typedef AcArray<AcPpGranularObject*> AcPpGranularObjectPtrArray;

/// <summary> Class used to create the component list and persist it in the DWG file.
/// It has a helper method to easily obtain the dictionary containing existing line components.
/// </summary>
class PNIDOBJECTS_API AcPpGranularInfo: public AcRxObject
{
public:
	ACRX_DECLARE_MEMBERS(AcPpGranularInfo);

	/// <summary>
	/// Default constructor
	/// </summary>
	AcPpGranularInfo();

	/// <summary>
	/// Constructor. Creates a new AcPpImpGranularInfo object. 
	/// </summary>
	/// <param name ="lineId"> Reference of the line ID </param>
	AcPpGranularInfo(const AcDbObjectId& lineId);

	/// <summary>
	/// Destructor. Deletes the AcPpImpGranularInfo object. 
	/// </summary>
	~AcPpGranularInfo();

	/// <summary>
	/// The line segment id refers to the line segment to use.
	/// </summary>
	/// <returns> Line segment id </returns>
	AcDbObjectId lineId() const;

	/// <summary>
	/// This function sets the line segment id to use..
	/// </summary>
	/// <param name="lineId"> Line segment ID to set </returns>
	void setLineId(const AcDbObjectId& lineId);

	/// <summary>
	/// This function is used to traverse the line from source to destination and produce a new list of line components. 
	/// The new list of line components is returned in the components parameter and they are memory only objects not persisted in the DWG file. 
	/// There is no need to delete these objects as the class will properly destroy them if the destructor is called before the save() method is invoked. 
	/// </summary>
	/// <param name="components"> Array of line components from source to destination </param>
	Acad::ErrorStatus generate(AcPpGranularObjectPtrArray& components);

	/// <summary>
	/// This function is used to persist the line component list in the DWG file. 
	/// </summary>
	Acad::ErrorStatus save() const;

	/// <summary>
	/// Helper function used to retrieve the AcPpLineComponents dictionary stored within the extension dictionary of the line segment. 
	/// </summary>
	/// <param name="pDict"> AcPpLineComponents dictionary </param>
	/// <param name="nMode"> This enumerated type provides the mode values used to specify how a database resident object is to be opened. </param>
	Acad::ErrorStatus getDictionary(AcDbDictionary*& pDict, AcDb::OpenMode nMode) const;

protected:
	AcPpImpGranularInfo *mpImpGranularInfo;

};