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
#include "AcPpDb3dSubPart.h"

//-----------------------------------------------------------------------------
class AcPpDb3dImpBoltSetSubPart;

//-----------------------------------------------------------------------------
class PNP3DOBJECTS_API AcPpDb3dBoltSetSubPart : public AcPpDb3dSubPart
{
public:

	ACRX_DECLARE_MEMBERS(AcPpDb3dBoltSetSubPart);

    PNPDB3DAPISUBPART_DECLARE_IMPCLASS(AcPpDb3dImpBoltSetSubPart)
    PNPDB3DAPISUBPART_DECLARE_PARENTCLASS(AcPpDb3dSubPart)

	AcPpDb3dBoltSetSubPart();
	virtual ~AcPpDb3dBoltSetSubPart();

protected:

	AcPpDb3dBoltSetSubPart(bool bImpDone);

public:

    //-----------------------------------------------------------------------------
	//----- AcDbObject protocols
    //
    virtual Acad::ErrorStatus       dwgOutFields        (AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus       dwgInFields         (AcDbDwgFiler* pFiler);

	virtual Acad::ErrorStatus       dxfOutFields        (AcDbDxfFiler* pFiler) const;
    virtual Acad::ErrorStatus       dxfInFields         (AcDbDxfFiler* pFiler);

    //-----------------------------------------------------------------------------
    //----- AcPpDb3dSubPart protocols
    //
    virtual Acad::ErrorStatus       
	getPorts(AcPp3dPortArray& ports, AcPpDb3dPart::EPortType type);

    virtual bool                    
	findPort(const ACHAR* szName, AcPpDb3dPart::EPortType type, AcPp3dPort& port);

	double	getLength() const;
	void	setLength(double length);

	double	getOffset() const;
	void	setOffset(double offset);

protected:

    //-----------------------------------------------------------------------------
	//----- AcGiDrawable protocols
    //
    virtual Adesk::Boolean			subWorldDraw       (AcGiWorldDraw * wd);

    //-----------------------------------------------------------------------------
    //----- AcDbEntity protocols
	//
    virtual Acad::ErrorStatus       subExplode          (AcDbVoidPtrArray &entitySet,
                                                         AcDbEntity *pParent,
                                                         const AcGeMatrix3d &blockMatrix) const;

    virtual Acad::ErrorStatus       subGetGeomExtents   (AcDbExtents& extents,
                                                         const AcGeMatrix3d& blockTrans) const;

    virtual Acad::ErrorStatus       highlight           (AcDbEntity *pParent,
                                                         const AcGeMatrix3d& blockTrans);
    virtual Acad::ErrorStatus       unhighlight         ();
    virtual bool                    isHighlighted       () const;
};
