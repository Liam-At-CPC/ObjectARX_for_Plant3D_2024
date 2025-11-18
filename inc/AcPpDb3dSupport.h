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

//-----------------------------------------------------------------------------
#include "AcPpDb3dPart.h"

class AcPpDb3dImpSupport;

//-----------------------------------------------------------------------------
/// <summary>
/// Pipe Support entity
/// </summary>
///
/// <remarks>
///
/// </remarks>
class PNP3DOBJECTS_API AcPpDb3dSupport  : public AcPpDb3dPart
{
public:
    ACRX_DECLARE_MEMBERS(AcPpDb3dSupport);

    PNPDB3DAPI_DECLARE_IMPCLASS(AcPpDb3dImpSupport)
    PNPDB3DAPI_DECLARE_PARENTCLASS(AcPpDb3dPart)

    /// <summary>
    /// Default constructor.
    /// </summary>
    AcPpDb3dSupport();
                                
protected:
    /// <summary>
    /// For internal use.
    /// </summary>
	AcPpDb3dSupport(bool bIsImpDone);

public:
    /// <summary>
    /// Destructor
    /// </summary>
    virtual ~AcPpDb3dSupport       ();

    //----- AcDbObject protocols
    //
    //- Dwg Filing protocol
    //
    /// <summary>
    /// This function is called by dwgOut(). Its purpose is to allow the object to write out its data.
    /// </summary>
    /// <param name = "pFiler"> Passed in pointer to filer to use to write out the object's data </param>
    /// <returns>Acad::ErrorStatus </returns>
    //
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const;

    /// <summary>
    /// This function is called by dwgIn(). Its purpose is to allow the object to read in its data.
    /// </summary>
    /// <param name = "pFiler"> Passed in pointer to filer to use to read in the object's data </param>
    /// <returns> Acad::ErrorStatus </returns>
    //
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler);

    //- Dxf Filing protocol
    //
    /// <summary>
    /// This function is called by dxfOut(). Its purpose is to allow the object to write out its data.
    /// </summary>
    /// <param name = "pFiler"> Passed in pointer to filer to use to write out the object's data </param>
    /// <returns> Acad::ErrorStatus </returns>
    //
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler *pFiler) const;

    /// <summary>
    /// This function is called by dwgIn(). Its purpose is to allow the object to read in its data.
    /// </summary>
    /// <param name = "pFiler"> Passed in pointer to filer to use to read in the object's data </param>
    /// <returns> Acad::ErrorStatus </returns>
    //
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler *pFiler);
  
    //-----------------------------------------------------------------------------
    //----- AcDbEntity protocols
    //

    /// <summary> Overridden from AcDbEntity</summary>
    virtual void                getEcs          (AcGeMatrix3d& retVal) const;

    // Stella Piping protocol
    //

    /// <summary>
    /// Return object id of block table record containing symbol graphics
    /// </summary>
    virtual const AcDbObjectId& getSymbolId         () const;
 
    /// <summary>
    /// Set object id of block table record containing symbol graphics
    /// </summary>
    virtual bool                setSymbolId         (const AcDbObjectId &id);
    
    /// <summary>
    /// Return position of support in WCS coordinates.
    /// </summary>
    virtual const AcGePoint3d&  getPosition         () const;

    /// <summary>
    /// Set position of support in WCS coordinates.
    /// </summary>
    virtual bool                setPosition         (const AcGePoint3d &p);

        /// <summary>
    /// Return x axis of support in WCS coordinates.
    /// </summary>
    virtual const AcGeVector3d& getXAxis           () const;

    /// <summary>
    /// Set x axis of support in WCS coordinates.
    /// </summary>
    virtual bool                setXAxis           (const AcGeVector3d &normal);

    /// <summary>
    /// Return normal of support in WCS coordinates.
    /// </summary>
    virtual const AcGeVector3d& getZAxis           () const;

    /// <summary>
    /// Set normal of support in WCS coordinates.
    /// </summary>
    virtual bool                setZAxis           (const AcGeVector3d &normal);
    
    /// <summary>
    /// Get rotation of support
    /// </summary>
    virtual double              getRotation         () const;

    /// <summary>
    /// Set rotation of support
    /// </summary>
    virtual bool                setRotation         (double rotation);


    // Ports protocol
    //
    
    /// <summary>
	/// This function is used to obtain the ports (connection locations) for the part.
    /// </summary>
    /// <param name = "ports"> Reference to a port array </param>
    /// <param name = "type"> Static, Dynamic or Both </param>
    /// <returns>Returns Acad::eOk on success</returns>
    //
    virtual Acad::ErrorStatus getPorts          (AcPp3dPortArray &ports,
                                                 AcPpDb3dPart::EPortType type) const;
    
    /// <summary>
	/// Finds port by name
    /// </summary>
    /// <param name = "name"> Port name </param>
    /// <param name = "type"> Static, Dynamic or Both </param>
    /// <param name = "port"> Result port </param>
    /// <returns> true if the port exists, false - othewise </returns>
    //
    virtual bool              findPort          (const ACHAR *name,
                                                 AcPpDb3dPart::EPortType type,
                                                 AcPp3dPort &port) const;

    /// <summary>
    /// Returns anchored status of entity
    /// </summary>
    /// <returns>true if entity is anchored, i.e. should not be moved when attached entities move</returns>
	virtual bool isAnchored() const;

	/// <summary>
    /// Center of gravity point of support
    /// </summary>
	virtual AcGePoint3d centerOfGravity();
                                                 
protected:

    // COM
    /// <summary>
    /// Return COM class id
    /// </summary>
    virtual Acad::ErrorStatus   subGetClassID      (CLSID* pClsid) const;

    //-----------------------------------------------------------------------------
    //----- AcDbEntity protocols
    //

    /// <summary> Overridden from AcDbEntity</summary>
    virtual Acad::ErrorStatus   subGetGeomExtents  (AcDbExtents& extents) const;
    
    //- Graphics protocol
    //

    /// <summary> Overridden from AcDbEntity</summary>
    virtual Adesk::Boolean subWorldDraw (AcGiWorldDraw *mode);

    /// <summary> Overridden from AcDbEntity</summary>
    virtual void           subViewportDraw    (AcGiViewportDraw* pVd);

    /// <summary> Overridden from AcDbEntity</summary>
    virtual Adesk::UInt32  subSetAttributes   (AcGiDrawableTraits* pTraits);

    /// <summary> Overridden from AcDbEntity</summary>
    virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d& xform);

    /// <summary>
    /// Returns the entities comprised in this entity
    /// </summary>
    /// <param name = "type"> Result entity set </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subExplode(AcDbVoidPtrArray &entitySet) const; 

    virtual Acad::ErrorStatus subGetCompoundObjectTransform(AcGeMatrix3d & xMat) const;
    virtual bool              subIsContentSnappable() const;

	/// <summary>
	/// This function must use the material provided in osnapMode, gsSelectionMark, pickPoint, lastPoint, and viewXform to determine all appropriate osnap points for the entity. 
	/// It must then append all such osnap points to the snapPoints array.
	/// </summary>
	/// <param name = "osnapMode">Input osnap mode being requested  </param>
	/// <param name = "gsSelectionMark"> Input GS marker of the subentity involved in the object snap operation </param>
	/// <param name = "pickPoint"> Input point (in WCS coordinates) picked during the object snap operation  </param>
	/// <param name = "lastPoint"> Input point (in WCS coordinates) selected just before pickPoint </param>
	/// <param name = "viewXform"> Input transformation matrix to transform from WCS to DCS  </param>
	/// <param name = "snapPoints"> Input pre-existing array to append osnap points to (may already contain points); output with object snap points appended  </param>
	/// <param name = "geomIds"> Not in use </param>
	/// <returns> Acad::ErrorStatus</returns>
    //
	virtual Acad::ErrorStatus subGetOsnapPoints (AcDb::OsnapMode osnapMode,
                                              Adesk::GsMarker gsSelectionMark,
                                              const AcGePoint3d &pickPoint,
                                              const AcGePoint3d &lastPoint,
		                                      const AcGeMatrix3d &viewXform,
                                              AcGePoint3dArray &snapPoints,
                                              AcDbIntArray &geomIds) const;
                                              
};
