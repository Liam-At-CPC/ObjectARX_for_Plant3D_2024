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
#include "AcPpDb3dPart.h"
#include "AcPpDb3dNozzleSubPart.h"

class AcPpDb3dImpEquipment;

//-----------------------------------------------------------------------------
/// <summary>
/// Equipment entity
/// </summary>
///
/// <remarks>
///
/// <para>This entity will be used for both fabricated and parametric equipment.
/// It can have nozzle subentities, see remarks below.</para>
///
/// <para>Nozzles and owning Equipment</para>
///
/// <para>Subentity nozzle are represented by instances of AcPpDb3dNozzleSubPart. Each 
/// AcPpDb3dNozzleSubPart holds the AcDbObjectId of a AutoCAD BlockTableRecord which 
/// contains the nozzles graphics, along with the port data that is stored as EED 
/// attached to the BlockTableRecord. Additionally, each AcPpDb3dNozzleSubPart has a 
/// index value that has to be unique in regard to its owning Equipment. The index, 
/// which can be set or queried by:</para>
/// 
/// <code>
/// 	AcPpDb3dNozzleSubPart::setIndex();
/// 	AcPpDb3dNozzleSubPart::getIndex() const;
/// </code>
/// 	 
/// <para>...acts as the GS marker used within worldDraw() and viewportDraw() as 
/// part of the nozzles data cache id and as the port number that will be used by 
/// the owning Equipment when publishing a nozzles port (see below for more 
/// details). AcPpDb3dNozzleSubPart instances can be added 
/// to and removed from an AcPpDb3dEquipment entity using the <c>addSubPart()</c> members
/// and removed using <c>removeSubPart</c>.</para>
/// 
/// <para>To avoid messing with data cache entries in case a nozzle is removed from 
/// equipment the subIndex values will not change; the removed nozzle subIndex 
/// remains unused until another nozzle is added, in this case the subIndex will be 
/// reassigned to the newly added nozzle. Although using non-consecutive GS markers
/// does not seem to be common practice AutoCAD does not complain.</para>
/// 
/// <para>Nozzle port publishing</para>
/// 
/// <para>Instances of AcPpDb3dEquipment may have static ports defined within the object 
/// itself, this is normally the case with so called "parametric" equipment that is 
/// generated from a fixed set of parameters and has a fixed number of nozzles. 
/// Unlike that, "fabricated" equipment is built from an arbitrary number of 
/// primitives and can have any number of nozzles added. Since pipe always be 
/// connected via a nozzle (no connection can be made to equipment withouth having a 
/// nozzle!), and the nozzles themselves contain the ports necessary to connect pipe 
/// AcPpDb3dEquipment "publishes" the outer port of all nozzles to the outside 
/// world.</para> 
/// 
/// <para>More exactly, when getPorts() or findPort() is called for AcPpDb3dEquipment it 
/// will iterator over all attached nozzles, find their "outer" port, copy that port 
/// into the returned AcPpDb3dPort object, transform it and rename the copied port, 
/// using the unique subentity index (stored within the nozzle). Thus, an 
/// AcPpDb3dEquipment object containing 2 nozzles, like that (nozzles are described 
/// with their ports and their subIndex value):</para>
///
/// <code>
/// 	AcPpDb3dEquipment
/// 		AcPpDb3dNozzleSubPart("S1","S2",5)
/// 		AcPpDb3dNozzleSubPart("S1","S2",8)
/// </code>
/// 
/// <para>will publish two ports "S5" and "S8":</para>
/// 
/// <code>
/// 	AcPpDb3dEquipment("S5","S8")
/// </code>
/// 
/// <para>"S5" is generated from nozzle 5, renaming its port "S1", and "S8" is generated 
/// from nozzle 8, also renaming the "S1" port ("S1", by default, is the nozzles 
/// "outer" port).</para>
///
/// </remarks>
class PNP3DOBJECTS_API AcPpDb3dEquipment : public AcPpDb3dPart
{
public:
    ACRX_DECLARE_MEMBERS(AcPpDb3dEquipment);

    PNPDB3DAPI_DECLARE_IMPCLASS(AcPpDb3dImpEquipment)
    PNPDB3DAPI_DECLARE_PARENTCLASS(AcPpDb3dPart)

    /// <summary>
    /// Default constructor.
    /// </summary>
    AcPpDb3dEquipment();
                                
protected:
    /// <summary>
    /// For internal use.
    /// </summary>
	AcPpDb3dEquipment(bool bIsImpDone);

public:
    /// <summary>
    /// Destructor
    /// </summary>
    virtual ~AcPpDb3dEquipment       ();

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

    // StellaSubentity protocol
    //


    /// <summary>
    /// Add a subpart (aka nozzle) to equipment.
    /// <summary>
    /// <param name="subIndex">Subentity index of subpart. Will be generated and returned using this parameter</param>
    /// <param name="newSubPart">Pointer to new sub part</param>
    /// <returns>Return true on sucess, false otherwise</returns>
    virtual bool                addSubPart       (int                   &subIndex,
                                                  AcPpDb3dNozzleSubPart *newSubPart);
    /// <summary>
    /// Add a subpart (aka nozzle) to equipment.
    /// <summary>
    /// <remarks><paramref name="newSubPart"/> must already have the subentity index set.</remarks>
    /// <param name="newSubPart">Pointer to new sub part</param>
    /// <returns>Return true on sucess, false otherwise</returns>
    virtual bool                addSubPart       (AcPpDb3dNozzleSubPart *newSubPart);

    /// <summary>
    /// Remove subpart from equipment
    /// </summary>
    /// <param name="subIndex">Subentity index of part to remove</param>
    /// <returns>Return true on sucess, false otherwise</returns>
    virtual bool                removeSubPart    (int subIndex); 

    /// <summary>
    /// Remove subpart from equipment
    /// </summary>
    /// <param name="port">Port attached to subpart to remove.</param>
    /// <returns>Return true on sucess, false otherwise</returns>
    virtual bool                removeSubPart    (const AcPp3dPort& port); 

    /// <summary>
    /// Remove all subparts from equipment
    /// </summary>
    /// <returns>Return true on sucess, false otherwise</returns>
    virtual bool                removeAllSubParts();

    /// <summary>
    /// Return number of subparts
    /// </summary>
    /// <returns>Returns number of subparts</returns>
    virtual int                 numSubParts	     () const;

    /// <summary>
    /// Return all subparts
    /// </summary>
    /// <param name="arr">Array containing all subparts after successful completion.</param>
    /// <returns>Returns Acad::eOk on success.</returns>
    virtual Acad::ErrorStatus   getAllSubParts   (AcArray<AcPpDb3dNozzleSubPart *>& arr) const;

    /// <summary>
    /// Return single subpart
    /// </summary>
    /// <param name="index">Subentity index of subpart to be returned</param>
    /// <param name="pSubPart">Points to subpart after sucessful completion</param>
    /// <returns>Returns Acad::eOk on success, Acad::eInvalidIndex on failure.</returns>
    virtual Acad::ErrorStatus   getSubPart       (int index,
                                                  AcPpDb3dNozzleSubPart*& pSubPart) const;

    /// <summary>
    /// Return subentity id for port
    /// </summary>
    /// <param name="port">port whose nozzle subentity id should be returned</param>
    /// <returns>Returns nozzle subentity on success, zero on failure.</returns>
    virtual int                 getPortSubIndex  (const AcPp3dPort& port) const;

    /// <summary>
    /// Return subentity id for port index
    /// </summary>
    /// <param name="portIndex">port index whose nozzle subentity id should be returned</param>
    /// <returns>Returns nozzle subentity on success, zero on failure.</returns>
    virtual int                 getPortSubIndex  (int portIndex) const;

    /// <summary>
    /// True, if the path can be highlighted, i.e. it is not already highlighted,
    /// or in case of kNullSubentId, doesn't contain any highlighted subentities
    /// </summary>
    ///
    bool                        canHighlight     (const AcDbFullSubentPath &subEntityPath);



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
    /// Return position of equipment in WCS coordinates.
    /// </summary>
    virtual const AcGePoint3d&  getPosition         () const;

    /// <summary>
    /// Set position of equipment in WCS coordinates.
    /// </summary>
    virtual bool                setPosition         (const AcGePoint3d &p);

    /// <summary>
    /// Return x-Axis of equipment in WCS coordinates.
	/// The result vector may need to be normalized before use.
    /// </summary>
    virtual const AcGeVector3d& getXAxis            () const;

    /// <summary>
    /// Set normal of equipment in WCS coordinates.
    /// </summary>
    virtual bool                setXAxis            (const AcGeVector3d &normal);

    /// <summary>
    /// Return z-Axis of equipment in WCS coordinates.
	/// The result vector may need to be normalized before use.
    /// </summary>
    virtual const AcGeVector3d& getZAxis            () const;

    /// <summary>
    /// Set normal of equipment in WCS coordinates.
    /// </summary>
    virtual bool                setZAxis            (const AcGeVector3d &normal);
    
    /// <summary>
    /// Get rotation of equipment
    /// </summary>
    virtual double              getRotation         () const;

    /// <summary>
    /// Set rotation of equipment
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
    /// Return port properties of given port
    /// </summary>
    /// <param name="name">Name of port</param>
    /// <param name="port">Returned port if port name exists</param>
    /// <returns>true on success, false otherwise.</param>
    virtual bool               portProperties   (const ACHAR *name,
                                                 AcPp3dSpecPort &port);


    /// <summary>
    /// Returns anchored status of entity
    /// </summary>
    /// <returns>true if entity is anchored, i.e. should not be moved when attached entities move</returns>
	virtual bool isAnchored() const;


    /// <summary>
    /// Helper method to generate an output port name for equipment nozzle
    /// </summary>
    /// <param name="index">port index</param>
    /// <param name="buf">output buffer</param>
    /// <param name="len">buffer length</param>
    /// <returns>port name</returns>
    static ACHAR *generatePortName(int index, ACHAR *buf, int len);
                                                 
    /// <summary>
    /// Gets the placement lock value on the entity.
    /// <returns>Returns the current placement lock value on the entity</returns>
    virtual Adesk::Boolean isPlacementLocked() const;

	/// <summary>
    /// Center of gravity point of equipment
    /// </summary>
	virtual AcGePoint3d centerOfGravity();

protected:

    //----- AcDbObject protocols
    //

    /// <summary>
    /// This function is called by AutoCAD during deep clone operations
    /// <summary>
    /// <param name = "pOwnerObject"> Passed in pointer to the clone's owner object </param>
    /// <param name = "pClonedObject"> Output pointer to the cloned object, or NULL if no clone was made </param>
    /// <param name = "idMap"> Input of the current Id Map for this clone operation </param>
    /// <param name = "isPrimary"> Indicates whether this object is being cloned by itself or by its owner </param>
    virtual Acad::ErrorStatus subDeepClone(AcDbObject* pOwnerObject, 
                                        AcDbObject*& pClonedObject, 
                                        AcDbIdMapping& idMap, 
                                        Adesk::Boolean isPrimary = true) const;
    
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
    /// <summary> Overridden from AcDbEntity</summary>
    virtual Acad::ErrorStatus   subIntersectWith   (const AcDbEntity* pEnt,
                                                 AcDb::Intersect intType, 
                                                 AcGePoint3dArray& points,
                                                 Adesk::GsMarker thisGsMarker = 0, 
                                                 Adesk::GsMarker otherGsMarker = 0) const;
    /// <summary> Overridden from AcDbEntity</summary>
    virtual Acad::ErrorStatus   subIntersectWith   (const AcDbEntity* pEnt,
                                                 AcDb::Intersect intType,
                                                 const AcGePlane& projPlane,
                                                 AcGePoint3dArray& points,
                                                 Adesk::GsMarker thisGsMarker = 0,
                                                 Adesk::GsMarker otherGsMarker = 0) const;
    
 
    virtual Acad::ErrorStatus   subGetOsnapPoints  (AcDb::OsnapMode osnapMode,
                                                 Adesk::GsMarker gsSelectionMark,
                                                 const AcGePoint3d &pickPoint,
                                                 const AcGePoint3d &lastPoint,
                                                 const AcGeMatrix3d &viewXform,
                                                 AcGePoint3dArray &snapPoints,
                                                 AcDbIntArray &geomIds) const;

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

    // Subentity protocol
    //


    /// <summary> Overridden from AcDbEntity</summary>
    virtual Acad::ErrorStatus   subGetSubentClassId(const AcDbFullSubentPath& path,
                                                 CLSID*                    clsId) const;

    /// <summary> Overridden from AcDbEntity</summary>
    virtual Acad::ErrorStatus   subTransformSubentPathsBy(
                                                 const AcDbFullSubentPathArray& paths,
                                                 const AcGeMatrix3d&            xform);

    /// <summary> Overridden from AcDbEntity</summary>
    virtual Acad::ErrorStatus   subGetSubentPathGeomExtents(
                                                 const AcDbFullSubentPath&      path, 
                                                 AcDbExtents&                   extents) const;   

    /// <summary> Overridden from AcDbEntity</summary>
    virtual Acad::ErrorStatus   subGetSubentPathsAtGsMarker(
                                                 AcDb::SubentType       type,
                                                 Adesk::GsMarker        gsMark, 
                                                 const AcGePoint3d&     pickPoint,
                                                 const AcGeMatrix3d&    viewXform, 
                                                 int&                   numPaths,
                                                 AcDbFullSubentPath*&   subentPaths, 
                                                 int                    numInserts = 0,
                                                 AcDbObjectId*          entAndInsertStack = NULL) const;

    /// <summary> Overridden from AcDbEntity</summary>
    virtual Acad::ErrorStatus   subGetGsMarkersAtSubentPath(
                                                 const AcDbFullSubentPath& subPath, 
                                                 AcArray<Adesk::GsMarker>& gsMarkers) const;

    /// <summary> Overridden from AcDbEntity</summary>
    virtual Acad::ErrorStatus   subDeleteSubentPaths(const AcDbFullSubentPathArray& paths);

    /// <summary> Overridden from AcDbEntity</summary>
    virtual Acad::ErrorStatus   subHighlight(
                                        const AcDbFullSubentPath& subId = kNullSubent, 
                                        const Adesk::Boolean highlightAll = false) const;

    virtual Acad::ErrorStatus   subUnhighlight(
                                        const AcDbFullSubentPath& subId = kNullSubent, 
                                        const Adesk::Boolean highlightAll = false) const;

    // Grips
    //
    virtual Acad::ErrorStatus   subGetGripPointsAtSubentPath(
                                                 const AcDbFullSubentPath& path, 
                                                 AcDbGripDataPtrArray& grips, 
                                                 const double curViewUnitSize, 
                                                 const int gripSize, 
                                                 const AcGeVector3d& curViewDir, 
                                                 const int bitflags) const;

    virtual Acad::ErrorStatus   subMoveGripPointsAtSubentPaths(
                                                 const AcDbFullSubentPathArray& paths, 
                                                 const AcDbVoidPtrArray& gripAppData, 
                                                 const AcGeVector3d& offset, 
                                                 const int bitflags);

    /// <summary>
    /// Returns the entities comprised in the equipment
    /// </summary>
    /// <param name = "type"> Result entity set </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus   subExplode(AcDbVoidPtrArray& entitySet) const;

    virtual Acad::ErrorStatus   subGetCompoundObjectTransform(AcGeMatrix3d & xMat) const;
    virtual bool                subIsContentSnappable   () const;
};
