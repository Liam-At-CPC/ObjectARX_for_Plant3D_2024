//
// (C) Copyright 2011 by Autodesk, Inc.
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
#include "acppdb3disosymbol.h"

class AcPpDb3dImpIsoSphereSymbol;

class PNP3DOBJECTS_API AcPpDb3dIsoSphereSymbol :
	public AcPpDb3dIsoSymbol
{
public:
	ACRX_DECLARE_MEMBERS(AcPpDb3dIsoSphereSymbol);

	PNPDB3DAPI_DECLARE_IMPCLASS(AcPpDb3dImpIsoSphereSymbol)
	PNPDB3DAPI_DECLARE_PARENTCLASS(AcPpDb3dIsoSymbol)

	AcPpDb3dIsoSphereSymbol(void);
	virtual                               ~AcPpDb3dIsoSphereSymbol        (void);
	Acad::ErrorStatus                      setRadius                         (double dRadius);
	Acad::ErrorStatus                      getRadius                         (double & dRadius) const;
    virtual void                           getTransformMatrix                (AcGeMatrix3d &retVal) const;
    //Custom entity protocols
	virtual Acad::ErrorStatus              dwgInFields                       (AcDbDwgFiler *pFiler);
	virtual Acad::ErrorStatus              dwgOutFields                      (AcDbDwgFiler *pFiler) const;
	virtual Acad::ErrorStatus              dxfOutFields                      (AcDbDxfFiler* pFiler) const;
	virtual Acad::ErrorStatus              dxfInFields                       (AcDbDxfFiler* pFiler) ;

protected:
	virtual Acad::ErrorStatus              subGetOsnapPoints                 (AcDb::OsnapMode osnapMode,
		                                                                      Adesk::GsMarker gsSelectionMark,
		                                                                      const AcGePoint3d &pickPoint,
		                                                                      const AcGePoint3d &lastPoint,
		                                                                      const AcGeMatrix3d &viewXform,
		                                                                      AcGePoint3dArray &snapPoints,
		                                                                      AcDbIntArray &geomIds);
	virtual Acad::ErrorStatus             subGetGripPoints                   (AcDbGripDataPtrArray& grips,
	                                                                          const double curViewUnitSize, 
	                                                                          const int gripSize, 
		                                                                      const AcGeVector3d&   curViewDir, 
		                                                                      const int bitflags) const;
	virtual Acad::ErrorStatus             subMoveGripPointsAt                (const AcDbVoidPtrArray& gripAppData, 
		                                                                      const AcGeVector3d& offset,
		                                                                      const int bitflags);
	virtual Acad::ErrorStatus             subTransformBy                     (const AcGeMatrix3d& xform);
};


