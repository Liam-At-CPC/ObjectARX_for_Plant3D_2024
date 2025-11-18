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

//-----------------------------------------------------------------------------
//----- AcPpDynamicOffPage.h : Declaration of the AcPpDynamicOffPage
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "AcPpDynamicAsset.h"

class AcPpImpDynamicOffPage;

//-----------------------------------------------------------------------------
/// <summary>
/// DynamicOffPage class.
/// </summary>
class PNIDOBJECTS_API AcPpDynamicOffPage : public AcPpDynamicAsset
{
public:
	ACRX_DECLARE_MEMBERS(AcPpDynamicOffPage);

protected:
    AcPpDynamicOffPage(bool bImpDone);

public:
	/// <summary>
    /// Default constructor.
    /// </summary>
	AcPpDynamicOffPage();

	/// <summary>
    /// Destructor.
    /// </summary>
	virtual ~AcPpDynamicOffPage();

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

    // Functions overridden from AcPpDynamicAsset

    /// <summary>
    /// Must be called after DynamicAsset is db resident to
    /// evaluate and initialize the dynamic portions of the asset
    /// </sumary>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus initialize();

    /// <summary>
    /// Called to refresh the values in the dynamic portions of the asset
    /// </summary>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus refresh();

	/// <summary>
	/// This function is called by AutoCAD when the AUDIT command is executed. 
	/// The AcDbAuditInfo object pointed to by pAuditInfo contains member functions that are used to determine what to do and also to report the results of the audit operation on the object.
	/// </summary>
	/// <param name = "auditor">  </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus audit(AcDbAuditInfo* auditor);

	/// <summary>
	/// This function returns a boolean that indicated if the off-page connector is connected to another off-page connector.
    /// </summary>
	/// <returns> bool </returns>
    bool isMated() const;

	// Functions specific to AcPpDynamicOffPage

	/// <summary>
	/// This function returns pointer to AcPpImpDynamicOffPage class. 
	/// </summary>
	/// <returns> Pointer to  AcPpImpDynamicOffPage class</returns>	
    AcPpImpDynamicOffPage*       implementation() const;

protected:

    /// <summary> This function gets the grip points and supporting information about the grips for this entity. 
	/// The caller is responsible for freeing the AcDbGripData objects whose pointers are in the grips array.
	/// </summary>
	/// <param name = "grips">Array of pointers to dynamically allocated AcDbGripData objects, one for each grip point in the entity  </param>
	/// <param name = "curViewUnitSize"> Size, in pixels, of one drawing unit in the current viewport </param>
	/// <param name = "gripSize"> Current grip size, in pixels  </param>
	/// <param name = "curViewDir"> Vector describing the view direction in the current viewport </param>
	/// <param name = "bitflags"> Bitmap of one or more flags specified by the GetGripPointsFlags enumeration </param>
	/// <returns>Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subGetGripPoints(AcDbGripDataPtrArray& grips,
                                            const double curViewUnitSize,
                                            const int gripSize,
                                            const AcGeVector3d& curViewDir,
                                            const int bitflags) const;

	/// <summary>
	/// This function provides a means by which AutoCAD and ObjectARX applications can ask the entity to apply a transformation matrix (xform) to itself.
	/// </summary>
	/// <param name = "xform">Input transformation matrix to be applied to the entity </param>
	virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d& xform);

	/// <summary>
	/// Gets the corresponding COM wrapper class ID.
	/// </summary>
	/// <param name = "pClsid"> Class ID </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subGetClassID   (CLSID* pClsid) const;

    /// <summary>
    /// This function should dynamically create (using the C++ new operator) whatever entity objects are appropriate to be used to replace the entity after an explode operation has taken place. 
    /// Pointers to these entities are then appended to the entitySet array. Once the pointers have been appended, the function should return with a status of Acad::eOk.
    /// </summary>
    /// <param name = "entitySet"> Input array to contain pointers to new entities; this array may already contain pointers from other entities explode() methods; 
    /// output with all entities that result from exploding this entity, appended to the array </param>
    /// <returns>Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subExplode(AcDbVoidPtrArray& entitySet) const;

    /// <summary>
    /// This function gives control of deep clone operations to the object. 
    /// </summary>
    /// <param name = "pOwnerObject"> Input object to which the clones should be appended </param>
    /// <param name = "pClonedObject"> Returns a pointer to the cloned object, or NULL if not cloned </param>
    /// <param name = "idMap"> Input current object ID map </param>
    /// <param name = "isPrimary"> Input Boolean indicating whether this object is primary or owned </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subDeepClone (AcDbObject *pOwnerObject, AcDbObject *&pClonedObject, AcDbIdMapping &idMap, Adesk::Boolean isPrimary =true) const ;
} ;
