//
// (C) Copyright 2007-2008 by Autodesk, Inc.
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
//----- AcPpDynamicAsset.h : Declaration of the AcPpDynamicAsset
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "AcPpAsset.h"

class AcPpImpDynamicAsset;

//-----------------------------------------------------------------------------
/// <summary>
/// DynamicAsset class.
/// </summary>
class PNIDOBJECTS_API AcPpDynamicAsset : public AcPpAsset
{
public:
	ACRX_DECLARE_MEMBERS(AcPpDynamicAsset);

protected:
    AcPpDynamicAsset(bool bImpDone);

public:
	/// <summary>
    /// Default constructor.
    /// </summary>
	AcPpDynamicAsset();

	/// <summary>
    /// Destructor.
    /// </summary>
	virtual ~AcPpDynamicAsset();

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
	/// Called from within erase() before anything else is done. 
	/// The default implementation is to return Acad::eOk. 
	/// However, when overridden in custom classes, it provides a hook into the erase operation.
	/// </summary>
	/// <param name = "erasing"> Passed in copy of the erasing argument that was passed into the erase() function call that triggered this subErase() call </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus subErase (Adesk::Boolean erasing);

	/// <summary>
    /// Sets a value representing the style id of this asset.
    /// </summary>
	virtual Acad::ErrorStatus setStyleId(const AcDbObjectId& styleId);

    /// <summary>
    /// Gets a collection of values representing the ids of the attachment
    /// points of this asset.
    /// </summary>
    virtual Acad::ErrorStatus getAttachmentPoints(AcGePoint3dArray& points) const;

	// Functions specific to AcPpDynamicAsset

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
    /// Call this method to regenerate the nested blockreference when
    /// the Styles definining block definition has been changed.
    /// </summary>
    virtual Acad::ErrorStatus reApplyStyle();

	/// <summary>
    /// Returns whether a DynamicAsset should be created
    /// for the given block definition
    /// </summary>
	/// <param name ="bDynamic"> </param>
	/// <param name ="blockDefinitionId"> </param>
	/// <returns> Acad::ErrorStatus </returns>
    static Acad::ErrorStatus blockRequiresDynamicAsset(bool& bDynamic, 
        const AcDbObjectId& blockDefinitionId);

	/// <summary>
	/// This function returns pointer to AcPpImpDynamicAsset class. 
	/// </summary>
	/// <returns> Pointer to  AcPpImpDynamicAsset class</returns>	
    AcPpImpDynamicAsset*       implementation() const;

protected:

    /// <summary>
    /// This function gives control of deep clone operations to the object. 
    /// </summary>
    /// <param name = "pOwnerObject"> Input object to which the clones should be appended </param>
    /// <param name = "pClonedObject"> Returns a pointer to the cloned object, or NULL if not cloned </param>
    /// <param name = "idMap"> Input current object ID map </param>
    /// <param name = "isPrimary"> Input Boolean indicating whether this object is primary or owned </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subDeepClone (AcDbObject *pOwnerObject, AcDbObject *&pClonedObject, AcDbIdMapping &idMap, Adesk::Boolean isPrimary =true) const ;

    /// <summary>
    /// This function should dynamically create (using the C++ new operator) whatever entity objects are appropriate to be used to replace the entity after an explode operation has taken place. 
    /// Pointers to these entities are then appended to the entitySet array. Once the pointers have been appended, the function should return with a status of Acad::eOk.
    /// </summary>
    /// <param name = "entitySet"> Input array to contain pointers to new entities; this array may already contain pointers from other entities explode() methods; 
    /// output with all entities that result from exploding this entity, appended to the array </param>
    /// <returns>Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subExplode(AcDbVoidPtrArray& entitySet) const;

    /// <summary>
	/// Gets the corresponding COM wrapper class ID.
	/// </summary>
	/// <param name = "pClsid"> Class ID </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subGetClassID   (CLSID* pClsid) const;
} ;
