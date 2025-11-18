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
#include "dbmain.h"
#include"AcPp3dPort.h"
#include "AcPpDb3dPart.h"

class AcPpDb3dImpIsoSymbol;

enum PnP3dIsoMessageEnclosure
{
	eP3dNoEnclosure,// No enclosure
	eP3dDiamondEndedBox,//Diamond ended box
	eP3dRoundEndedBox,//Round ended box
	eP3dRectangularBox,//Rectangular box
	eP3dCircular,//Circular enclosure
	eP3dTriangular,//Triangular enclosure (2 character limit)
	eP3dDiamondShaped,//Diamond shaped enclosure (3 character limit)
	eP3dDoubleCircle,//Double Circle
	eP3dEllipse,//Ellipse
	eP3dBIPIdentifier//B.I.P Identifier
};

class PNP3DOBJECTS_API AcPpDb3dIsoSymbol :
	public AcPpDb3dPart
{
public:
	ACRX_DECLARE_MEMBERS(AcPpDb3dIsoSymbol);

	PNPDB3DAPI_DECLARE_IMPCLASS(AcPpDb3dImpIsoSymbol)
	PNPDB3DAPI_DECLARE_PARENTCLASS(AcPpDb3dPart)

	AcPpDb3dIsoSymbol(void);
	virtual                                           ~AcPpDb3dIsoSymbol  (void);
	void                                              setBlockId             (AcDbObjectId id);
	AcDbObjectId                                      getBlockId             () const;
	virtual bool                                      setPosition            (const AcGePoint3d &pt);
	virtual AcGePoint3d                               position               () const;
	virtual bool                                      isAnchored             () const;
    virtual bool                                      partSizeProperties     (AcPp3dPartSizeProperties &part) const;
	virtual bool                                      portProperties         (const ACHAR *name,
		                                                                      AcPp3dSpecPort &port) const;
	virtual void                                      getAlignmentLines      (AcGeLineSeg3dArray& segs, 
		                                                                      AcGePoint3dArray& intersections,
                                                                              bool bExtendSegments);                                 
    virtual void                                      getTransformMatrix     (AcGeMatrix3d &retVal) const;                                         			
	virtual Acad::ErrorStatus                         dwgInFields            (AcDbDwgFiler *pFiler);
	virtual Acad::ErrorStatus                         dwgOutFields           (AcDbDwgFiler *pFiler) const;
	virtual Acad::ErrorStatus                         dxfOutFields           (AcDbDxfFiler* pFiler) const;
	virtual Acad::ErrorStatus                         dxfInFields            (AcDbDxfFiler* pFiler) ;
	virtual void                                      getEcs                 (AcGeMatrix3d &retVal) const;
protected:
	virtual Adesk::Boolean                            subWorldDraw           (AcGiWorldDraw *mode);
	virtual Acad::ErrorStatus                         subGetGeomExtents      (AcDbExtents& extents) const;
	virtual Acad::ErrorStatus                         subGetOsnapPoints      (AcDb::OsnapMode osnapMode,
		                                                                      Adesk::GsMarker gsSelectionMark,
		                                                                      const AcGePoint3d &pickPoint,
		                                                                      const AcGePoint3d &lastPoint,
		                                                                      const AcGeMatrix3d &viewXform,
		                                                                      AcGePoint3dArray &snapPoints,
		                                                                      AcDbIntArray &geomIds);
	virtual Acad::ErrorStatus                         subGetGripPoints       (AcDbGripDataPtrArray& grips,
		                                                                      const double          curViewUnitSize, 
		                                                                      const int             gripSize, 
	                                                                          const AcGeVector3d&   curViewDir, 
		                                                                      const int             bitflags) const;

	virtual Acad::ErrorStatus                         subTransformBy         (const AcGeMatrix3d& xform);
	virtual Acad::ErrorStatus                         subMoveGripPointsAt    (const AcDbVoidPtrArray& gripAppData, 
		                                                                      const AcGeVector3d&     offset,
		                                                                      const int               bitflags);
	virtual Acad::ErrorStatus                         subExplode             (AcDbVoidPtrArray &entitySet) const;
	virtual void                                      subList                ()const;
};

