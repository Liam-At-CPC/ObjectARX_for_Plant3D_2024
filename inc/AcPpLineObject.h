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

//-----------------------------------------------------------------------------
//----- AcPpLineObject.h : Declaration of the AcPpLineObject and subclasses
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//----- Includes
//-----------------------------------------------------------------------------
#include "PnPDllDef.h"

//-----------------------------------------------------------------------------
//----- Forward declarations
//-----------------------------------------------------------------------------
class AcPpLineSegment;

class AcPpImpLineObject;
class AcPpImpLineObjectIterator;
class AcPpImpEndlineObject;
class AcPpImpInlineObject;
class AcPpImpInlineEntity;
class AcPpImpInlineIntersection;
class AcPpImpInlineGap;

/// <summary>
/// Abstract base class for line objects.
/// </summary>
class PNIDOBJECTS_API AcPpLineObject: public AcRxObject
{
protected:    
    /// <summary>
    /// Subclass constructor.
    /// </summary>
    AcPpLineObject(bool bImpDone);

public:
    ACRX_DECLARE_MEMBERS(AcPpLineObject);
    
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcPpLineObject();    

    /// <summary>
    /// Get position of this line object.
    /// </summary>
    /// <returns></returns>
    AcGePoint3d position() const;

    /// <summary>
    /// Set position of this line object.
    /// </summary>
    /// <param name="point">Input position.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setPosition(const AcGePoint3d& point);

    /// <summary>
    /// Get id of the line entity (if any) described by this line object.
    /// </summary>
    /// <returns>Returns AcDbObjectId::kNull if this line object does not describe
    /// an AcDbEntity (e.g. a user gap).
    /// </returns>
    AcDbObjectId objectId() const;

    /// <summary>
    /// Get id of the line entity described by this line object. 
    /// Defaults to AcDbObjectId::kNull.
    /// </summary>
    /// <param name="objId">Input id.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setObjectId(const AcDbObjectId& objId);
    
    /// <summary>
    /// Get index of line segment that this line object is connected to.
    /// </summary>
    /// <returns></returns>
    int segmentIndex() const;

    /// <summary>
    /// Get pointer to implementation instance.
    /// </summary>
    /// <returns></returns>
    AcPpImpLineObject* imp() const;

protected:
    /// <summary>
    /// Pointer to imp instance.
    /// </summary>
    AcPpImpLineObject *m_pImpLineObject;
};


/// <summary>
/// Abstract base class used to filter objects when iterating 
/// through the objects on a line.
/// </summary>
class AcPpLineObjectFilter
{
public:
    /// <summary>
    /// If the function returns true, then the item is allowed into the iterator. 
    /// If false, the item is skipped.
    /// </summary>
    /// <param name="pLineObject">Input pointer to line object.</param>
    /// <returns></returns>
    virtual bool filter(const AcPpLineObject* pLineObject) const = 0;
};


/// <summary>
/// This class is used to iterate objects on a line. 
/// The iterator will be created with the objects sorted in the order 
/// they are found on the line from start to end.
///
/// NOTE: 
/// The AcPpLineObject object returned by object() is only valid 
/// while the object that contains it is open. 
/// </summary>
class AcPpLineObjectIterator
{
private:
    /// <summary>
    /// Constructor.
    /// </summary>
    AcPpLineObjectIterator(AcPpLineSegment* pLineSeg, const AcPpLineObjectFilter* pFilter);

public:
    /// <summary>
    /// Destructor.
    /// </summary>
    PNIDOBJECTS_API ~AcPpLineObjectIterator();

    /// <summary>
    /// Returns true when the iteration process has reached the end.
    /// </summary>
    /// <returns></returns>
    PNIDOBJECTS_API bool done() const;

    /// <summary>
    /// Resets the iterator to the first AcPpLineObject object.
    /// </summary>
    PNIDOBJECTS_API void start();

    /// <summary>
    /// This function advances the iterator to the next available AcPpLineObject object.
    /// </summary>
    /// <param name="bForward">Input bool controlling the direction to move the iterator.</param>
    PNIDOBJECTS_API void step(bool bForward = true);

    /// <summary>
    /// Returns the AcPpLineObject object at the current iterator position.
    /// </summary>
    /// <returns></returns>
    PNIDOBJECTS_API AcPpLineObject* object();

    /// <summary>
    /// Get pointer to implementation instance.
    /// </summary>
    /// <returns></returns>
    PNIDOBJECTS_API AcPpImpLineObjectIterator* imp() const;

protected:
    /// <summary>
    /// Pointer to imp instance.
    /// </summary>
    AcPpImpLineObjectIterator* m_pImpLineObjectIterator;

    /// <summary>
    /// Friendship for private constructor.
    /// </summary>
    friend class AcPpImpLineSegment;

};


/// <summary>
/// End line entity (e.g. a line or an asset).
/// </summary>
class PNIDOBJECTS_API AcPpEndlineObject: public AcPpLineObject
{
public:
    ACRX_DECLARE_MEMBERS(AcPpEndlineObject);

    /// <summary>
    /// Default constructor.
    /// </summary>
    AcPpEndlineObject();

    /// <summary>
    /// Constructor.
    /// </summary>
    /// <param name="point">Input position.</param>
    /// <param name="entityId">Input id of end-line entity.</param>
    AcPpEndlineObject(const AcGePoint3d& point, const AcDbObjectId& entityId);

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcPpEndlineObject();

    /// <summary>
    /// Returns true if this entity is an asset, false otherwise.
    /// </summary>
    /// <returns></returns>
    bool isAsset() const;

    /// <summary>
    /// Returns <code>true</code> if this entity is a line segment, <code>false</code> otherwise.
    /// </summary>
    /// <returns></returns>
    bool isLineSegment() const;

    /// <summary>
    /// Get pointer to implementation instance.
    /// </summary>
    /// <returns></returns>
    AcPpImpEndlineObject* imp() const;
};


/// <summary>
/// Abstract inline object class.
/// </summary>
class PNIDOBJECTS_API AcPpInlineObject: public AcPpLineObject
{
protected:
    /// <summary>
    /// Subclass constructor.
    /// </summary>
    AcPpInlineObject(bool  bImpDone);    

public:
    ACRX_DECLARE_MEMBERS(AcPpInlineObject);

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcPpInlineObject();

    /// <summary>
    /// Get start point of gap.
    /// </summary>
    /// <returns></returns>
    AcGePoint3d startPoint() const;

    /// <summary>
    /// Set start point of gap.
    /// </summary>
    /// <param name="point">Input point position.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setStartPoint(const AcGePoint3d& point);
    
    /// <summary>
    /// Get end point of gap.
    /// </summary>
    /// <returns></returns>
    AcGePoint3d endPoint() const;

    /// <summary>
    /// Set end point of gap.
    /// </summary>
    /// <param name="point">Input point position.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setEndPoint(const AcGePoint3d& point);

    /// <summary>
    /// Get pointer to implementation instance.
    /// </summary>
    /// <returns></returns>
    AcPpImpInlineObject* imp() const;
};


/// <summary>
/// Inline entity (e.g. connection to a line, an asset, or block reference).
/// </summary>
class PNIDOBJECTS_API AcPpInlineEntity: public AcPpInlineObject
{
public:
    ACRX_DECLARE_MEMBERS(AcPpInlineEntity);
    
    /// <summary>
    /// Default constructor.
    /// </summary>
    AcPpInlineEntity();

    /// <summary>
    /// Constructor.
    /// </summary>
    /// <param name="point">Input position.</param>
    /// <param name="lineId">Input id of entity.</param>
    AcPpInlineEntity(const AcGePoint3d& point, const AcDbObjectId& entityId);
    
    /// <summary>
    /// Constructor.
    /// </summary>
    /// <param name="startPoint">Input position of entity start point.</param>
    /// <param name="endPoint">Input position of entity end point.</param>
    /// <param name="lineId">Input id of entity.</param>
    AcPpInlineEntity(const AcGePoint3d& startPoint, 
                     const AcGePoint3d& endPoint, 
                     const AcDbObjectId& entityId);
    
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcPpInlineEntity();

    /// <summary>
    /// Returns true if this entity is an asset, false otherwise.
    /// </summary>
    /// <returns></returns>
    bool isAsset() const;

    /// <summary>
    /// Returns <code>true</code> if this entity is a line segment, <code>false</code> otherwise.
    /// </summary>
    /// <returns></returns>
    bool isLineSegment() const;
    
    /// <summary>
    /// Get pointer to implementation instance.
    /// </summary>
    /// <returns></returns>
    AcPpImpInlineEntity* imp() const;
};


/// <summary>
/// The intersection of two line segments.
/// </summary>
class PNIDOBJECTS_API AcPpInlineIntersection: public AcPpInlineObject
{
public:
    ACRX_DECLARE_MEMBERS(AcPpInlineIntersection);

    /// <summary>
    /// Default constructor.
    /// </summary>
    AcPpInlineIntersection();

    /// <summary>
    /// Constructor.
    /// </summary>
    /// <param name="startPoint">Input position of gap start point.</param>
    /// <param name="endPoint">Input position of gap end point.</param>
    /// <param name="lineId">Input id of intersecting line.</param>
    AcPpInlineIntersection(const AcGePoint3d& startPoint, 
                           const AcGePoint3d& endPoint,
                           const AcDbObjectId& lineId);

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcPpInlineIntersection();


    /// <summary>
    /// Get pointer to implementation instance.
    /// </summary>
    /// <returns></returns>
    AcPpImpInlineIntersection* imp() const;
};


/// <summary>
/// An (user created) inline gap that also has gap symbols on either side of the gap 
/// as per the project manager preferences.
/// </summary>
/// <remarks>
/// The position of an (user created) inline gap is defined by the mid point of its
/// start and end points; the setPosition(...) always returns Acad::eNotApplicable.
///
/// An inline gap does not describe a database entity and thus its object-id should
/// always be left at its default value of AcDbObjectId::kNull; the setObjectId(...)
/// always returns Acad::eNotApplicable.
/// </remarks>
class PNIDOBJECTS_API AcPpInlineGap: public AcPpInlineObject
{
public:
    ACRX_DECLARE_MEMBERS(AcPpInlineGap);

    /// <summary>
    /// Default constructor.
    /// </summary>
    AcPpInlineGap();

    /// <summary>
    /// Constructor.
    /// </summary>
    /// <param name="startPoint">Input position of gap start point.</param>
    /// <param name="endPoint">Input position of gap end point.</param>
    AcPpInlineGap(const AcGePoint3d& startPoint, const AcGePoint3d& endPoint);

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcPpInlineGap();

    /// <summary>
    /// Get id of the first gap symbol.
    /// </summary>
    /// <returns></returns>
    AcDbObjectId gapSymbol1Id() const;

    /// <summary>
    /// Set the first gap symbol.
    /// </summary>
    /// <param name="idGapSymbol">Input id of gap symbol.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setGapSymbol1Id(const AcDbObjectId& idGapSymbol);

    /// <summary>
    /// Get id of the second gap symbol.
    /// </summary>
    /// <returns></returns>
    AcDbObjectId gapSymbol2Id() const;

    /// <summary>
    /// Set the second gap symbol.
    /// </summary>
    /// <param name="idGapSymbol">Input id of gap symbol.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setGapSymbol2Id(const AcDbObjectId& idGapSymbol);

    /// <summary>
    /// Get create gap symbols on add to line segment flag. Defaults to true.
    /// </summary>
    /// <remarks>
    /// If set to true, (new) gap symbols are created for this user gap
    /// when it is added to a line segment and no valid ids have been 
    /// specified for both gap symbols.
    /// </remarks>
    /// <returns></returns>
    bool createGapSymbols() const;

    /// <summary>
    /// Set create gap symbols on add to line segment flag.
    /// </summary>
    /// <remarks>
    /// If set to true, (new) gap symbols are created for this user gap
    /// when it is added to a line segment and no valid ids have been 
    /// specified for both gap symbols.
    /// </remarks>    
    /// <param name="">Input flag to create gap symbols.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setCreateGapSymbols(bool bCreateGapSymbols);

    /// <summary>
    /// Get pointer to implementation instance.
    /// </summary>
    /// <returns></returns>
    AcPpImpInlineGap* imp() const;

};
