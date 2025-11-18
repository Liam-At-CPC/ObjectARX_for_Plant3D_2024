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

//-----------------------------------------------------------------------------
#include "dbidmap.h"
#include "AcPpDb3dPart.h"

class AcPpDb3dImpConnector;
class AcPpDb3dSubPart;

//-----------------------------------------------------------------------------
/// <summary>
/// Connector entity
/// </summary>
//
class PNP3DOBJECTS_API AcPpDb3dConnector : public AcPpDb3dPart
{
public:
    ACRX_DECLARE_MEMBERS(AcPpDb3dConnector);

    PNPDB3DAPI_DECLARE_IMPCLASS(AcPpDb3dImpConnector)
    PNPDB3DAPI_DECLARE_PARENTCLASS(AcPpDb3dPart)

    /// <summary>
    /// Default constructor.
    /// </summary>
    //
    AcPpDb3dConnector();
                                
protected:
    /// <summary>
    /// For internal use.
    /// </summary>
    //
	AcPpDb3dConnector(bool bIsImpDone);

public:
    /// <summary>
    /// Destructor
    /// </summary>
    //
    virtual ~AcPpDb3dConnector       ();


    //----- AcDbObject protocols
    //
    //- Dwg Filing protocol
    //
    virtual Acad::ErrorStatus   dwgOutFields    (AcDbDwgFiler *pFiler) const;
    virtual Acad::ErrorStatus   dwgInFields     (AcDbDwgFiler *pFiler);

    //- Dxf Filing protocol
    //
    virtual Acad::ErrorStatus   dxfOutFields    (AcDbDxfFiler *pFiler) const;
    virtual Acad::ErrorStatus   dxfInFields     (AcDbDxfFiler *pFiler);

	//----- AcDbEntity protocols
	//
	virtual Acad::ErrorStatus	setLayer		(AcDbObjectId newVal, 
												Adesk::Boolean doSubents = true, 
												bool allowHiddenLayer = false);

	virtual Acad::ErrorStatus	setLayer		(const ACHAR* newVal, 
												Adesk::Boolean doSubents = true, 
												bool allowHiddenLayer = false);
    
    virtual void                getEcs          (AcGeMatrix3d& retVal) const;

    // Piping
    //
    virtual const AcGePoint3d & getPosition         () const;
    virtual bool                setPosition         (const AcGePoint3d &p);
    
    virtual const AcGeVector3d &        getXAxis            () const;
    virtual const AcGeVector3d &        getZAxis            () const;
    virtual bool                        setOrientation      (const AcGeVector3d &xAxis,
                                                             const AcGeVector3d &zAxis);
    
    // Subentities
    //
	virtual Acad::ErrorStatus   addSubPart          (AcPpDb3dSubPart* pSubPart);
    virtual int                 numSubParts			() const;
	virtual Acad::ErrorStatus   getSubPart          (int index,
                                                     AcPpDb3dSubPart*& pSubPart) const;
    virtual Acad::ErrorStatus   removeSubPart       (int index);
    virtual bool                hasBlockSubPart     () const;

    // Subpart static ports
    // This function returns WCS ports, the way they are oriented inside Connecter
    // The order is also can be swapped, when a subpart is mirrored
    // It doesn't apply last port overrides. If the connector has it overridden,
    // you may need to replace the second port of the last subpart with the second Connector port
    //
    virtual Acad::ErrorStatus   getSubPartPorts     (int index,
                                                     AcPp3dPortArray &ports) const;


    // Get all the subpart as array
    //
	virtual Acad::ErrorStatus	getAllSubParts      (AcArray<AcPpDb3dSubPart*>& subParts) const;

    virtual AcPpDb3dPart       *getSubPart          (int index) const;

    /// <summary>
    /// True, if the path can be highlighted, i.e. it is not already highlighted,
    /// or in case of kNullSubentId, doesn't contain any highlighted subentities
    /// </summary>
    ///
    bool                        canHighlight        (const AcDbFullSubentPath &subEntityPath);

    // Slope tolerance (radians)
    //
    virtual double              getSlopeTolerance   () const;
    virtual void                setSlopeTolerance   (double tolerance);

    // Offset tolerance (size)
    //
    virtual double              getOffsetTolerance   () const;
    virtual void                setOffsetTolerance   (double tolerance);

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
    virtual Acad::ErrorStatus   getPorts            (AcPp3dPortArray &ports,
                                                     AcPpDb3dPart::EPortType type) const;
    
    /// <summary>
	/// Finds port by name
    /// </summary>
    /// <param name = "name"> Port name </param>
    /// <param name = "type"> Static, Dynamic or Both </param>
    /// <param name = "port"> Result port </param>
    /// <returns> true if the port exists, false - othewise </returns>
    //
    virtual bool                findPort            (const ACHAR *name,
                                                     AcPpDb3dPart::EPortType type,
                                                     AcPp3dPort &port) const;
     
    // Override last attachment port
    //                                                     
    virtual bool                getOverrideLastPort () const;
    virtual void                clearOverrideLastPort ();
    virtual void                setOverrideLastPort (const AcGePoint3d &position,
                                                     const AcGeVector3d &direction);

protected:

    // AcGiDrawable interface
    //
    virtual Adesk::UInt32       subSetAttributes   (AcGiDrawableTraits* pTraits);
    virtual Adesk::Boolean      subWorldDraw       (AcGiWorldDraw *mode);
    virtual void                subViewportDraw    (AcGiViewportDraw* pVd);

    // COM
    //    
    virtual Acad::ErrorStatus   subGetClassID      (CLSID* pClsid) const;
    
	//----- AcDbEntity protocols
	//
	virtual void				subSetDatabaseDefaults(AcDbDatabase* pDb);

    virtual Acad::ErrorStatus   subGetGeomExtents  (AcDbExtents& extents) const;

    virtual Acad::ErrorStatus   subIntersectWith   (const AcDbEntity* pEnt,
                                                 AcDb::Intersect intType, 
                                                 AcGePoint3dArray& points,
                                                 Adesk::GsMarker thisGsMarker = 0, 
                                                 Adesk::GsMarker otherGsMarker = 0) const;
    virtual Acad::ErrorStatus   subIntersectWith   (const AcDbEntity* pEnt,
                                                 AcDb::Intersect intType,
                                                 const AcGePlane& projPlane,
                                                 AcGePoint3dArray& points,
                                                 Adesk::GsMarker thisGsMarker = 0,
                                                 Adesk::GsMarker otherGsMarker = 0) const;
    
    /// <summary>
    /// This function provides a means by which AutoCAD and ObjectARX applications can ask the entity to apply a transformation matrix (xform) to itself.
    /// </summary>
    /// <param name = "xform">Input transformation matrix to be applied to the entity </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus   subTransformBy     (const AcGeMatrix3d& xform);

    // Subentity acquisition and manipulation
    //
    virtual  Acad::ErrorStatus  subGetSubentClassId(const AcDbFullSubentPath& path,
                                                 CLSID*                    clsId) const;
    virtual Acad::ErrorStatus   subTransformSubentPathsBy(
                                                 const AcDbFullSubentPathArray& paths,
                                                 const AcGeMatrix3d&            xform);
    virtual Acad::ErrorStatus   subGetSubentPathGeomExtents(
                                                 const AcDbFullSubentPath&      path, 
                                                 AcDbExtents&                   extents) const;   
    virtual Acad::ErrorStatus   subGetSubentPathsAtGsMarker(
                                                 AcDb::SubentType       type,
                                                 Adesk::GsMarker        gsMark, 
                                                 const AcGePoint3d&     pickPoint,
                                                 const AcGeMatrix3d&    viewXform, 
                                                 int&                   numPaths,
                                                 AcDbFullSubentPath*&   subentPaths, 
                                                 int                    numInserts = 0,
                                                 AcDbObjectId*          entAndInsertStack = NULL) const;
    virtual Acad::ErrorStatus   subGetGsMarkersAtSubentPath(
                                                 const AcDbFullSubentPath& subPath, 
                                                 AcArray<Adesk::GsMarker>& gsMarkers) const;
    virtual Acad::ErrorStatus   subGetGripPointsAtSubentPath(
                                                const AcDbFullSubentPath& path, 
                                                AcDbGripDataPtrArray& grips, 
                                                const double curViewUnitSize, 
                                                const int gripSize, 
                                                const AcGeVector3d& curViewDir, 
                                                const int bitflags) const;
	virtual Acad::ErrorStatus subMoveGripPointsAtSubentPaths(
												const AcDbFullSubentPathArray& paths, 
												const AcDbVoidPtrArray& gripAppData, 
												const AcGeVector3d& offset, 
												const int bitflags);
    virtual Acad::ErrorStatus   subDeleteSubentPaths(const AcDbFullSubentPathArray& paths);

    virtual Acad::ErrorStatus   subHighlight   (const AcDbFullSubentPath& subId = kNullSubent, 
                                                const Adesk::Boolean highlightAll = false) const;

    virtual Acad::ErrorStatus   subUnhighlight (const AcDbFullSubentPath& subId = kNullSubent, 
                                                const Adesk::Boolean highlightAll = false) const;

	/// <summary>
	/// Returns the entities comprised in the equipment
	/// </summary>
	/// <param name = "type"> Result entity set </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus	subExplode				(AcDbVoidPtrArray &entitySet) const;

    virtual bool                subIsContentSnappable   () const;
};
