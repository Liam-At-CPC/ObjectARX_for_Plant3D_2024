//
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

#pragma once

//-----------------------------------------------------------------------------
#include "dbmain.h"
#include "AcPp3dPort.h"
#include "AcPp3dSpecPart.h"
#include "AcPp3dSpecPort.h"
#include "AcArray.h"
#include "gelnsg3d.h"
#include "PnPDb3dApi.h"
#include "PnPDllDef.h"

class AcPpDb3dImpPart;
typedef AcArray<AcGeLineSeg3d, AcArrayObjectCopyReallocator<AcGeLineSeg3d>> AcGeLineSeg3dArray;

#define PNPDB3DAPI_DECLARE_IMPCLASS(IMPCLASS) \
    PNPDB3DAPI_DECLARE_IMPCLASS_IMPOBJ(IMPCLASS, mpImp)

#define PNPDB3DAPI_DECLARE_PARENTCLASS(PARENTCLASS) \
    typedef PARENTCLASS ParentClassType;

//-----------------------------------------------------------------------------
/// <summary>
/// Base class for all 3dPiping entities
/// </summary>
//
class PNP3DOBJECTS_API AcPpDb3dPart : public AcDbEntity
{
public:
    
    ACRX_DECLARE_MEMBERS(AcPpDb3dPart);

    PNPDB3DAPI_DECLARE_IMPCLASS(AcPpDb3dImpPart)
    PNPDB3DAPI_DECLARE_PARENTCLASS(AcDbEntity)
    
    enum EPortType
    {
        kStatic     = 0x01,
        kDynamic    = 0x02,
        kBoth       = 0x03,
		kSymbolic   = 0x04,
        kAll        = 0x07
    };

    /// <summary>
    /// Default constructor.
    /// </summary>
    //
    AcPpDb3dPart();

protected:
    /// <summary>
    /// For internal use.
    /// </summary>
    //
	AcPpDb3dPart(bool bIsImpDone);

public:
    /// <summary>
    /// Destructor
    /// </summary>
    //
    virtual ~AcPpDb3dPart       ();

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

    /// <summary>
    /// This function is called by AutoCAD when the AUDIT command is executed. 
    /// The AcDbAuditInfo object pointed to by pAuditInfo contains member functions that are used to determine what to do and also to report the results of the audit operation on the object.
    /// </summary>
    /// <param name = "pAuditInfo">  </param>
    /// <returns> Acad::ErrorStatus </returns>
    //
    virtual Acad::ErrorStatus audit(AcDbAuditInfo *pAuditInfo);

    //-----------------------------------------------------------------------------
    //----- AcDbEntity protocols
    //

    /// <summary>
	/// This function is used to obtain the ports (connection locations) for the part.
    /// </summary>
    /// <param name = "ports"> Reference to a port array </param>
    /// <param name = "type"> Static, Dynamic or Both </param>
    /// <returns> Acad::ErrorStatus </returns>
    //
  
    virtual Acad::ErrorStatus getPorts          (AcPp3dPortArray &ports,
                                                 AcPpDb3dPart::EPortType type) const;
    
    /// <summary>
	/// Finds port by name
    /// </summary>
    /// <param name = "name"> Port name </param>
    /// <param name = "type"> Static, Dynamic or Both </param>
    /// <param name = "port"> Result port </param>
    /// <returns> true if the port exists, false - otherwise </returns>
    //   
    virtual bool              findPort          (const ACHAR *name,
                                                 AcPpDb3dPart::EPortType type,
                                                 AcPp3dPort &port) const;

    /// <summary>
    /// Generates an unused port name for a dynamic port suitable for adding
    /// to this part.
    /// </summary>
    /// Provide an unused name for a dynamic or symbolic port
    /// <param name= "bSymbolic">Indicates if this is a Symbolic port</param>
    /// <returns> The port name </returns>
    ///   
    virtual AcString generateDynamicPortName(bool bSymbolic);

    /// Add a new port to the part
    /// <param name= "port">Port to add</param>
    /// <returns> false if port to add has no name or a port with the same name already exists.</returns>
    //    
    virtual bool addPort(const AcPp3dPort& port);

    /// Remove port from part 
    /// <param name="name">Name of the port to remove</param>
    /// <returns>true if port removed, false if port with given name was not found</returns>
    //   
    virtual bool removePort(const ACHAR *name);

    /// <summary>
	/// get properties for the part
    /// </summary>
    /// <returns> pointer to part properties if they exist, 0 - otherwise. </returns>
    // 
    virtual bool            partSizeProperties  (AcPp3dPartSizeProperties &part) const;


    /// <summary>
	/// get class name for the part
    /// </summary>
    /// <returns> copy class name to the supplied  buffer if exists, 0 - otherwise. </returns>
    //   
    virtual bool            partSizeClass  (ACHAR *strName, int len) const;

    /// <summary>
	/// get properties for the port
    /// </summary>
    //   
    virtual bool            portProperties      (const ACHAR *name,
                                                 AcPp3dSpecPort &port) const;

    /// <summary>
    /// Returns line segments and insertion points representing this
    /// part's alignment line.
    /// </summary>
    /// <param name = "segs"> Line Segments contributing to the alignment line </param>
    /// <param name = "insersections"> Intersection points between line segments </param>
    /// <param name = "bExtendSegments"> If true, segments will be extended on a small gap over intersection line </param>
    /// <returns> void </returns>
    // 
    virtual void getAlignmentLines(AcGeLineSeg3dArray& segs,
                                   AcGePoint3dArray& intersections,
                                   bool bExtendSegments);

	/// <summary>
	/// The same, but using dynamic ports as well
    /// </summary>
    virtual void getAlignmentLinesWithDynamicPorts(AcGeLineSeg3dArray& segs,
                                   AcGePoint3dArray& intersections,
                                   bool bExtendSegments);

    /// <summary>
    /// Returns center lines for pipes, assets, and connectors.
    /// Similar to getAlignmentLines(), except may contain arcs for elbows, if bTrueArc is true
    /// </summary>
    /// <param name = "segs"> Line Segments contributing to the center line </param>
    /// <param name = "bTrueArc"> If true, genereates arc for an elbow </param>
    /// <param name = "pArc"> That arc or NULL </param>
    /// <returns> void </returns>
    //
    virtual void getCenterLines   (AcGeLineSeg3dArray &segs,
                                   bool bTrueArc,
                                   AcGeCircArc3d *&pArc);

	/// <summary>
	/// Returns the anchored state of an entity
    /// </summary>
    virtual bool isAnchored() const;

	/// <summary>
	/// Sets the position of the entity.
    /// </summary>
    virtual bool setPosition(const AcGePoint3d &);

 	/// <summary>
	/// Returns the anchored state of an entity
    /// </summary>
    /// <returns>Always returns (0,0,0) for AcPpDb3dPart</returns>
    virtual const AcGePoint3d &getPosition() const;

	/// <summary>
	/// Sets the placement lock on the entity.
    /// </summary>
    /// <param name = "bLock"> The boolean value that is set on the placement lock</param>
    /// <returns>Returns the error status of the operation</returns>
    virtual Acad::ErrorStatus setPlacementLock(const Adesk::Boolean& bLock);


	/// <summary>
	/// Gets the placement lock value on the entity.
    /// </summary>
    /// <returns>Returns the current placement lock value on the entity</returns>
    virtual Adesk::Boolean isPlacementLocked() const;

	/// <summary>
	/// Sets the amount of cutback to display on the port.
    /// </summary>
    virtual bool setEngagementLength(const ACHAR* portName, double length);

    /// <summary>
	/// Find if user set the CoG manually
    /// </summary>
    /// <returns> true if the user set the CoG manually, else false </returns>
    //
    
    virtual Adesk::Boolean isUserCenterOfGravity();

	/// <summary>
	/// Manually set the position of the center of gravity
    /// </summary>
    virtual Acad::ErrorStatus setCenterOfGravity(AcGePoint3d &cog);

	/// <summary>
	/// Get the center of gravity point
    /// </summary>
    virtual AcGePoint3d centerOfGravity();

	/// <summary>
	/// Set whether the center of gravity is edited by user.
    /// </summary>
	void setIsUserCenterOfGravity(bool bIsUserState = true);

protected:
    AcPpDb3dImpPart* mpImp;

    //----- AcDbObject protocols
    //
    /// <summary>
    /// This function is called by AutoCAD during deep clone operations
    /// </summary>
    /// <param name = "pOwnerObject"> Passed in pointer to the clone's owner object </param>
    /// <param name = "pClonedObject"> Output pointer to the cloned object, or NULL if no clone was made </param>
    /// <param name = "idMap"> Input of the current Id Map for this clone operation </param>
    /// <param name = "isPrimary"> Indicates whether this object is being cloned by itself or by its owner </param>
    virtual Acad::ErrorStatus subDeepClone(AcDbObject* pOwnerObject, 
                                        AcDbObject*& pClonedObject, 
                                        AcDbIdMapping& idMap, 
                                        Adesk::Boolean isPrimary = true) const;

    /// <summary>
    /// This function is called by AutoCAD during wblock clone operations
    /// </summary>
    /// <param name = "pOwnerObject"> Passed in pointer to the clone's owner object </param>
    /// <param name = "pClonedObject"> Output pointer to the cloned object, or NULL if no clone was made </param>
    /// <param name = "idMap"> Input of the current Id Map for this clone operation </param>
    /// <param name = "isPrimary"> Indicates whether this object is being cloned by itself or by its owner </param>
    virtual Acad::ErrorStatus subWblockClone(AcRxObject* pOwnerObject, 
                                          AcDbObject*& pClonedObject, 
                                          AcDbIdMapping& idMap, 
                                          Adesk::Boolean isPrimary = true) const;

    //-----------------------------------------------------------------------------
    //----- AcDbEntity protocols
    //
    //- Graphics protocol
    //
    /// <summary> 
    /// Whenever a regeneration of the entity's graphics is required, AutoCAD calls this function to generate the graphics primitives that will represent this entity on screen. 
    /// This function will then provide a generic set of 3D graphics primitives that AutoCAD will adjust for each viewport's parameters as they are displayed.
    ///</summary>
    /// <param name ="mode"> Input pointer to fully initialized AcGiWorldDraw object </param>
    /// <returns> Adesk::Boolean </returns>
    virtual Adesk::Boolean subWorldDraw (AcGiWorldDraw *mode);
    virtual void           subViewportDraw(AcGiViewportDraw* pVd);

	/// <summary>
	/// Returns the entities comprised in this entity
	/// </summary>
	/// <param name = "type"> Result entity set </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus subExplode(AcDbVoidPtrArray &entitySet) const;
    
	/// <summary>
	/// This function provides a means by which AutoCAD and ObjectARX applications can ask the entity to apply a transformation matrix (xform) to itself.
	/// </summary>
	/// <param name = "xform">Input transformation matrix to be applied to the entity </param>
    /// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d& xform);

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
                                              
    // Grips
    //
    virtual Acad::ErrorStatus   subGetGripPoints       (AcDbGripDataPtrArray& grips,
                                                     const double          curViewUnitSize, 
                                                     const int             gripSize, 
                                                     const AcGeVector3d&   curViewDir, 
                                                     const int             bitflags) const;
    virtual Acad::ErrorStatus   subMoveGripPointsAt    (const AcDbVoidPtrArray& gripAppData, 
                                                     const AcGeVector3d&     offset,
                                                     const int               bitflags);
    virtual void                subGripStatus          (const AcDb::GripStat status);
	virtual void				dragStatus(const AcDb::DragStat status);

    virtual void subList() const;

    virtual Acad::ErrorStatus subGetStretchPoints   (AcGePoint3dArray& points) const;
    virtual Acad::ErrorStatus subMoveStretchPointsAt(const AcDbIntArray& indices,
                                                     const AcGeVector3d& offset);
};
