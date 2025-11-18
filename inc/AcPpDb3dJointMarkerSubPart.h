//
// (C) Copyright 2008-2009 by Autodesk, Inc.
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
#include "AcPpDb3dSubPart.h"

//-----------------------------------------------------------------------------
class AcPpDb3dImpJointMarkerSubPart;

//-----------------------------------------------------------------------------
class PNP3DOBJECTS_API AcPpDb3dJointMarkerSubPart : public AcPpDb3dSubPart
{
public:

	ACRX_DECLARE_MEMBERS(AcPpDb3dJointMarkerSubPart);

    PNPDB3DAPISUBPART_DECLARE_IMPCLASS(AcPpDb3dImpJointMarkerSubPart)
    PNPDB3DAPISUBPART_DECLARE_PARENTCLASS(AcPpDb3dSubPart)

	AcPpDb3dJointMarkerSubPart();
	virtual ~AcPpDb3dJointMarkerSubPart();

protected:

	AcPpDb3dJointMarkerSubPart(bool bImpDone);

public:

    //-----------------------------------------------------------------------------
	//----- AcDbObject protocols
    //

    //-----------------------------------------------------------------------------
    //----- AcPpDb3dSubPart protocols
    //
    virtual Acad::ErrorStatus       
    getPorts(AcPp3dPortArray& ports, AcPpDb3dPart::EPortType type);

    virtual bool                    
    findPort(const ACHAR* szName, AcPpDb3dPart::EPortType type, AcPp3dPort& port);

protected:

    //-----------------------------------------------------------------------------
	//----- AcGiDrawable protocols
    //
    virtual Adesk::Boolean			subWorldDraw       (AcGiWorldDraw * wd);
    virtual void                    subViewportDraw    (AcGiViewportDraw* pVd);

    //-----------------------------------------------------------------------------
    //----- AcDbEntity protocols
	//
    virtual Acad::ErrorStatus       subExplode          (AcDbVoidPtrArray &entitySet,
                                                         AcDbEntity *pParent,
                                                         const AcGeMatrix3d &blockMatrix) const;

    virtual Acad::ErrorStatus       subGetGeomExtents   (AcDbExtents& extents,
                                                         const AcGeMatrix3d& blockTrans) const;
};
