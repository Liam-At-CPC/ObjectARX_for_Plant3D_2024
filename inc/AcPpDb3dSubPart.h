//
// (C) Copyright 2008-2010 by Autodesk, Inc.
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
#include "AcPpDb3dPart.h"
#include "PnPDb3dApi.h"

#define PNPDB3DAPISUBPART_DECLARE_IMPCLASS(IMPCLASS) \
    PNPDB3DAPI_DECLARE_IMPCLASS_IMPOBJ(IMPCLASS, m_pImp)

#define PNPDB3DAPISUBPART_DECLARE_PARENTCLASS(PARENTCLASS) \
    typedef PARENTCLASS ParentClassType;

//-----------------------------------------------------------------------------
class AcPpDb3dImpSubPart;
class AcPpDb3dConnector;
class AcPp3dPartSizeProperties;
class AcGsNode;
class AcPpObjectId;

//-----------------------------------------------------------------------------
class PNP3DOBJECTS_API AcPpDb3dSubPart : public AcGiDrawable
{
private:

	AcPpDb3dSubPart();

protected:

	AcPpDb3dSubPart(bool bImpDone);

public:

	ACRX_DECLARE_MEMBERS(AcPpDb3dSubPart);

    PNPDB3DAPISUBPART_DECLARE_IMPCLASS(AcPpDb3dImpSubPart)
    PNPDB3DAPISUBPART_DECLARE_PARENTCLASS(AcGiDrawable)

	virtual ~AcPpDb3dSubPart();

    //-----------------------------------------------------------------------------
	//----- AcDbObject protocols
    //
    virtual Acad::ErrorStatus       dwgOutFields        (AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus       dwgInFields         (AcDbDwgFiler* pFiler);

	virtual Acad::ErrorStatus       dxfOutFields        (AcDbDxfFiler* pFiler) const;
    virtual Acad::ErrorStatus       dxfInFields         (AcDbDxfFiler* pFiler);

    //-----------------------------------------------------------------------------
	//----- AcGiDrawable protocols
    //

    // Persistent/transient
    virtual Adesk::Boolean			isPersistent		(void) const;
    virtual AcDbObjectId			id					(void) const;

    //-----------------------------------------------------------------------------
    //----- AcDbEntity protocols
	//
    virtual Acad::ErrorStatus       explode             (AcDbVoidPtrArray &entitySet,
                                                         AcDbEntity *pParent,
                                                         const AcGeMatrix3d &blockMatrix) const PNPDB3DAPI_SEALED;

    virtual Acad::ErrorStatus       getGeomExtents      (AcDbExtents& extents,
                                                         const AcGeMatrix3d& blockTrans) const PNPDB3DAPI_SEALED;
    virtual Acad::ErrorStatus       transformBy         (const AcGeMatrix3d& xform) PNPDB3DAPI_SEALED;
    virtual Acad::ErrorStatus       intersectWith       (const AcDbEntity* pEnt,
                                                         AcDb::Intersect intType,
                                                         AcGePoint3dArray& points,
                                                         Adesk::GsMarker thisGsMarker,
                                                         Adesk::GsMarker otherGsMarker,
                                                         const AcGeMatrix3d& blockTrans) const PNPDB3DAPI_SEALED;
    virtual Acad::ErrorStatus       intersectWith       (const AcDbEntity* pEnt,
                                                         AcDb::Intersect intType,
                                                         const AcGePlane& projPlane,
                                                         AcGePoint3dArray& points,
                                                         Adesk::GsMarker thisGsMarker,
                                                         Adesk::GsMarker otherGsMarker,
                                                         const AcGeMatrix3d& blockTrans) const PNPDB3DAPI_SEALED;

    //-----------------------------------------------------------------------------
    //----- AcPpDb3dSubPart protocols
	//
    virtual Acad::ErrorStatus       
	getPorts(AcPp3dPortArray& ports, AcPpDb3dPart::EPortType type);

    virtual bool                    
	findPort(const ACHAR* szName, AcPpDb3dPart::EPortType type, AcPp3dPort& port);

    virtual bool getMirrorFlag() const;
    virtual void setMirrorFlag(bool bMirror);
    
    virtual double getRotation() const;
    virtual void   setRotation(double dblRotation);

	virtual AcPpDb3dPart*      getParent() const;
	virtual Acad::ErrorStatus  setParent(AcPpDb3dPart* pParent);

    virtual bool            partSizeProperties  (AcPp3dPartSizeProperties &part) const;
    virtual bool            partSizeClass  (ACHAR *strName, int len) const;


    virtual Adesk::Boolean commonDraw(AcGiCommonDraw* mode, const AcGeMatrix3d& blockTrans, bool bIsWorldDraw);


    virtual bool                isNonSpecFastener       ();

    virtual Acad::ErrorStatus   highlight               (AcDbEntity *pParent,
                                                         const AcGeMatrix3d& blockTrans);
    virtual Acad::ErrorStatus   unhighlight             ();
    virtual bool                isHighlighted           () const;

protected:

    ImpClassType* m_pImp;

    void assertReadEnabled() const;
    void assertWriteEnabled(Adesk::Boolean autoUndo = true,
							Adesk::Boolean recordModified = true);

    //-----------------------------------------------------------------------------
    //----- AcGiDrawable protocols
    //
    virtual Adesk::UInt32           subSetAttributes    (AcGiDrawableTraits * traits);
    virtual Adesk::Boolean          subWorldDraw        (AcGiWorldDraw * wd);
    virtual void                    subViewportDraw     (AcGiViewportDraw * vd);

    //-----------------------------------------------------------------------------
    //----- AcDbEntity protocols
    //
    virtual Acad::ErrorStatus       subExplode          (AcDbVoidPtrArray &entitySet,
                                                         AcDbEntity *pParent,
                                                         const AcGeMatrix3d &blockMatrix) const;
    virtual Acad::ErrorStatus       subGetGeomExtents   (AcDbExtents& extents,
                                                         const AcGeMatrix3d& blockTrans) const;
    virtual Acad::ErrorStatus       subTransformBy      (const AcGeMatrix3d& xform);
    virtual Acad::ErrorStatus       subIntersectWith    (const AcDbEntity* pEnt,
                                                         AcDb::Intersect intType,
                                                         AcGePoint3dArray& points,
                                                         Adesk::GsMarker thisGsMarker,
                                                         Adesk::GsMarker otherGsMarker,
                                                         const AcGeMatrix3d& blockTrans) const;
    virtual Acad::ErrorStatus       subIntersectWith    (const AcDbEntity* pEnt,
                                                         AcDb::Intersect intType,
                                                         const AcGePlane& projPlane,
                                                         AcGePoint3dArray& points,
                                                         Adesk::GsMarker thisGsMarker,
                                                         Adesk::GsMarker otherGsMarker,
                                                         const AcGeMatrix3d& blockTrans) const;

    // helpers
    // get AcPpObjectId for subpart
    bool                            partPpObjectId      (AcPpObjectId & oid) const;

};
