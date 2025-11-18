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
#include "AcPpDb3dBlockSubPart.h"

//-----------------------------------------------------------------------------
class AcPpDb3dImpNozzleSubPart;

//-----------------------------------------------------------------------------
class PNP3DOBJECTS_API AcPpDb3dNozzleSubPart : public AcPpDb3dBlockSubPart
{
public:

	ACRX_DECLARE_MEMBERS(AcPpDb3dNozzleSubPart);

    PNPDB3DAPISUBPART_DECLARE_IMPCLASS(AcPpDb3dImpNozzleSubPart)
    PNPDB3DAPISUBPART_DECLARE_PARENTCLASS(AcPpDb3dBlockSubPart)

	AcPpDb3dNozzleSubPart();
	virtual ~AcPpDb3dNozzleSubPart();

protected:

	AcPpDb3dNozzleSubPart(bool bImpDone);

public:

    //-----------------------------------------------------------------------------
	//----- AcDbObject protocols
    //
    virtual Acad::ErrorStatus       dwgOutFields        (AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus       dwgInFields         (AcDbDwgFiler* pFiler);

	virtual Acad::ErrorStatus       dxfOutFields        (AcDbDxfFiler* pFiler) const;
    virtual Acad::ErrorStatus       dxfInFields         (AcDbDxfFiler* pFiler);


    //-----------------------------------------------------------------------------
    //----- AcDbEntity protocols
    //

    // Transformation relative to owning entity
    //
    virtual void                    getEcs              (AcGeMatrix3d& retVal) const;

    virtual bool                    partSizeProperties  (AcPp3dPartSizeProperties &part) const;

    // Set the nozzle index
    virtual void setIndex(int index);
    // Return the nozzle index
    virtual int  getIndex() const;

    virtual Acad::ErrorStatus   highlight               (AcDbEntity *pParent,
                                                         const AcGeMatrix3d& blockTrans);
    virtual Acad::ErrorStatus   unhighlight             ();

protected:

    //-----------------------------------------------------------------------------
    //----- AcDbEntity protocols
    //
    // Transformation relative to owning entity
    virtual Acad::ErrorStatus       subTransformBy      (const AcGeMatrix3d& xform);
};
