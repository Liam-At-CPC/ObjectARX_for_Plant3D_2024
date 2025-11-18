//
// (C) Copyright 2007-2009 by Autodesk, Inc.
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

class AcPpDb3dImpInlineAsset;

//-----------------------------------------------------------------------------
/// <summary>
/// Base abstract class for Pipes
/// </summary>
//
class PNP3DOBJECTS_API AcPpDb3dInlineAsset : public AcPpDb3dPart
{
public:
    ACRX_DECLARE_MEMBERS(AcPpDb3dInlineAsset);

    PNPDB3DAPI_DECLARE_IMPCLASS(AcPpDb3dImpInlineAsset)
    PNPDB3DAPI_DECLARE_PARENTCLASS(AcPpDb3dPart)

    /// <summary>
    /// Default constructor.
    /// </summary>
    //
    AcPpDb3dInlineAsset();

protected:
    /// <summary>
    /// For internal use.
    /// </summary>
    //
	AcPpDb3dInlineAsset(bool bIsImpDone);

public:
    /// <summary>
    /// Destructor
    /// </summary>
    //
    virtual ~AcPpDb3dInlineAsset       ();

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
    virtual void                getEcs          (AcGeMatrix3d& retVal) const;

    // Piping
    //
    virtual const AcDbObjectId &    getSymbolId         () const;
    virtual bool                    setSymbolId         (const AcDbObjectId &id);
    
    virtual const AcGePoint3d &     getPosition         () const;
    virtual bool                    setPosition         (const AcGePoint3d &p);

    virtual const AcGeVector3d &    getXAxis            () const;
    virtual const AcGeVector3d &    getZAxis            () const;
    virtual bool                    setOrientation      (const AcGeVector3d &xAxis,
                                                         const AcGeVector3d &zAxis);
    /// <summary>
    /// Get the overall insulation diameter of pipe (i.e. OuterDiameter + 2*InsulationThickness)
    /// </summary>
    virtual double               getInsulationDiameter() const;

    /// <summary>
    /// Set the overall insulation diameter of pipe (i.e. OuterDiameter + 2*InsulationThickness)
    /// </summary>
    virtual bool                 setInsulationDiameter(double dOuterDiameter);
                                                         
    // Ports
    
    /// <summary>
	/// This function is used to obtain the ports (connection locations) for the part.
    /// </summary>
    /// <param name = "ports"> Reference to a port array </param>
    /// <param name = "type"> Static, Dynamic or Both </param>
    /// <returns> Acad::ErrorStatus </returns>
    //
    virtual Acad::ErrorStatus getPorts          (AcPp3dPortArray &ports,
                                                 AcPpDb3dPart::EPortType type) const;
    
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
    /// Center of gravity point of the inlineAsset
    /// </summary>
	virtual AcGePoint3d centerOfGravity();

protected:

    //-----------------------------------------------------------------------------
    //----- AcDbEntity protocols
    //

    /// <summary>
    /// Returns the entities comprised in the equipment
    /// </summary>
    /// <param name = "type"> Result entity set </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus    subExplode     (AcDbVoidPtrArray &entitySet) const;

    virtual Acad::ErrorStatus   subGetGeomExtents(AcDbExtents& extents) const;
    
    /// <summary>
    /// This function provides a means by which AutoCAD and ObjectARX applications can ask the entity to apply a transformation matrix (xform) to itself.
    /// </summary>
    /// <param name = "xform">Input transformation matrix to be applied to the entity </param>
    /// <returns> Acad::ErrorStatus </returns>
    //
    virtual Acad::ErrorStatus       subTransformBy         (const AcGeMatrix3d& xform);

   	virtual Acad::ErrorStatus 		subGetCompoundObjectTransform(AcGeMatrix3d & xMat) const;

    virtual bool                    subIsContentSnappable() const;

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
                                              
    // AcGiDrawable interface
    //
    virtual Adesk::UInt32           subSetAttributes       (AcGiDrawableTraits* pTraits);
    virtual Adesk::Boolean          subWorldDraw           (AcGiWorldDraw *mode);
    virtual void                    subViewportDraw        (AcGiViewportDraw* pVd);
};
