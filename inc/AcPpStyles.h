//
// (C) Copyright 2007-2009, 2012, 2014 by Autodesk, Inc.
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
//
// AcPpStyles.h
//
//  DESCRIPTION: AcPpStyle API class declaration
//
//  AcRxObject
//    AcDbObject
//      AcPpStyle
//        AcPpLineStyle
//        AcPpAssetStyle
//        AcPpAnnotationStyle
//

#ifndef __ACPPSTYLES_H__
#define __ACPPSTYLES_H__

#pragma once

#include "AcString.h"
#include "dbapserv.h"
#include "PnPStyles.h"
#include "PnPDllDef.h"

class AcPpImpLineStyle;
class AcPpImpAssetStyle;
class AcPpImpOffPageConnectorStyle;


/// <summary>
/// LineStyle class.
/// </summary>
class PNIDOBJECTS_API AcPpLineStyle : public AcPpStyle
{
public:
    /// <summary>
	/// Smart line type enumeration.
	/// </summary>
    enum SlineType{
        /// <summary> Polyline line type </summary>
        kPolylineType = 0,
        /// <summary> Multiline line type</summary>
        kMultilineType = 1
    };

    /// <summary>
	/// Flag insertion type enumeration.
	/// </summary>
    enum FlagType{
        /// <summary> Prompt to insert a flag after a line has been drawn </summary>
        kPromptToInsertFlag = 0,
        /// <summary> No flag </summary>
        kNoFlag             = 1,
    };

    ACRX_DECLARE_MEMBERS(AcPpLineStyle);

    /// <summary>
	/// Default Constructor.
	/// </summary>
	AcPpLineStyle();

	/// <summary>
	/// Copy Constructor.
	/// </summary>
	AcPpLineStyle(const AcPpLineStyle&);

	/// <summary>
	/// Destructor.
	/// </summary>
    virtual ~AcPpLineStyle();

    AcPpLineStyle & operator=( const AcPpLineStyle & );

    /// <summary>
	/// Gets a value representating the gap priority of style.
	/// </summary>
	/// <returns> Value representating the gap priority of style </returns>
	int                         gapPriority() const;

	/// <summary>
	/// Sets a value representating the gap priority of style.
	/// </summary>
	/// <param name = "iGapPriority"> Value representating the gap priority of style </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setGapPriority(int iGapPriority);

    /// <summary>
	/// Gets a value representating whether the flow direction is shown.
	/// </summary>
	/// <returns> Value representating whether the flow direction is shown </returns>
	bool                        showFlowDirection() const;

	/// <summary>
	/// Sets a value representating whether the flow of style is shown.
	/// </summary>
	/// <param name = "bShowFlowDirection"> Value representating whether the flow of style is shown. </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setShowFlowDirection(bool bShowFlowDirection);

    /// <summary>
	/// Gets a value representating the flow arrow style id of style.
	/// </summary>
	/// <returns> Value representating the flow arrow style id of style </returns>
	AcDbObjectId                flowArrowStyleId() const;

	/// <summary>
	/// Sets a value representating the flow arrow style id of style.
	/// </summary>
	/// <param name = "styleId"> Value representating the flow arrow style id of style </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setFlowArrowStyleId(const AcDbObjectId& styleId);

    /// <summary>
	/// Gets a value representating the flag insertion behavior.
	/// </summary>
	/// <returns> Value representating flag insertion behavior </returns>
    virtual AcPpLineStyle::FlagType flagType() const;
    
    /// <summary>
	/// Sets a value representating the flag insertion behavior.
	/// </summary>
	/// <param name = "bShowFlowDirection"> Value representating flag insertion behavior </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus setFlagType(AcPpLineStyle::FlagType flagType);

    /// <summary>
	/// Gets a value representating the smart line type.
	/// </summary>
	/// <returns> Value representating line type </returns>
    virtual AcPpLineStyle::SlineType slineType() const;
    
    /// <summary>
	/// Sets a value representating the smart line type.
	/// </summary>
	/// <param name = "bShowFlowDirection"> Value representating line type </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus setSlineType(AcPpLineStyle::SlineType lineType);

    /// <summary>
	/// Gets a value representating the Mline style id of style.
	/// </summary>
	/// <returns> Value representating the Mline style id of style </returns>
	AcDbObjectId  mlineStyleId() const;

	/// <summary>
	/// Sets a value representating the Mline style id of style.
	/// </summary>
	/// <param name = "styleId"> Value representating the Mline style id of style </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus setMlineStyleId(const AcDbObjectId& styleId);

	/// <summary>
	/// This functions purpose is to allow the object to write out its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to write out the object's data </param>
	/// <returns>Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const ;

	/// <summary>
	/// This functions purpose is to allow the object to read in its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to read in the object's data </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) ;

    /// <summary>
	/// This functions purpose is to allow the object to write out its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to write out the object's data </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler *pFiler) const ;
    
	/// <summary>
	/// This functions purpose is to allow the object to read in its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to read in the object's data </param>
	/// <returns> Acad::ErrorStatus</returns>
	virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler *pFiler) ;	

	/// <summary>
	/// This function is called by AutoCAD when the AUDIT command is executed
	/// </summary>
	/// <param name =""> Passed in a pointer to an AcDbAuditInfo object </param>
	/// <returns> Acad::ErrorStatus</returns>
    virtual Acad::ErrorStatus   audit(AcDbAuditInfo* pAuditInfo);

protected:
	AcPpLineStyle(bool bImpDone);
};

/// <summary>
/// This class defines the asset style. Asset style includes Jointype, rotation, scaling, mirror, autonozzle, etc
/// </summary>
class PNIDOBJECTS_API AcPpAssetStyle : public AcPpStyle
{
public:
    /// <summary>
	/// Join type enumeration.
	/// </summary>
    enum JoinType{
		/// <summary> Asset is at the end of the sline </summary>
        kEndLine				= 0,
		/// <summary> Asset is inline</summary>
        kInLine					= 1,
		/// <summary> Asset is a segment breaker </summary>
        kSegmentBreaker			= 2,
		/// <summary> Asset is not joint to the sline</summary>
        kNoJoin					= 3,
		/// <summary> Asset breaks sline into 2 groups when inserted on it </summary>
		kSegmentGroupBreaker	= 4
    };

    ACRX_DECLARE_MEMBERS(AcPpAssetStyle);

    /// <summary>
	/// Default constructor.
	/// </summary>
	AcPpAssetStyle();

	/// <summary>
	/// Copy constructor.
	/// </summary>
	AcPpAssetStyle(const AcPpAssetStyle&);

	/// <summary>
	/// Destructor.
	/// </summary>
    virtual ~AcPpAssetStyle();

    AcPpAssetStyle & operator=( const AcPpAssetStyle & );
    
    /// <summary>
	/// Gets a value representing the join type of style.
	/// </summary>
	/// <returns> value representing the join type of style </returns>
	AcPpAssetStyle::JoinType         joinType() const;

	/// <summary>
	/// Sets a value representing the join type of style.
	/// </summary>
	/// <param name ="joinType"> value representing the join type of style </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setJoinType(AcPpAssetStyle::JoinType joinType);
    
    /// <summary>
	/// Gets a value representing whether style is rotated on insert.
	/// </summary>
	/// <returns> value representing whether style is rotated on insert </returns>
	bool                        rotateOnInsert() const;

	/// <summary>
	/// Sets a value representing whether style is rotated on insert.
	/// </summary>
	/// <param name ="rotateOnInsert"> value representing whether style is rotated on insert </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setRotateOnInsert(bool rotateOnInsert);

    /// <summary>
	/// Gets a value representing whether style is scaled on insert.
	/// </summary>
	/// <returns> value representing whether style is scaled on insert </returns>
	bool                        scaleOnInsert() const;

	/// <summary>
	/// Sets a value representing whether style is scaled on insert.
	/// </summary>
	/// <param name ="scaleOnInsert"> value representing whether style is scaled on insert </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setScaleOnInsert(bool scaleOnInsert);

    /// <summary>
	/// Gets a value representing whether style is mirrored on insert.
	/// </summary>
	/// <returns> value representing whether style is mirrored on insert </returns>
	bool                        mirrorOnInsert() const;

	/// <summary>
	/// Sets a value representing whether style is mirrored on insert.
	/// </summary>
	/// <param name ="mirrorOnInsert"> value representing whether style is mirrored on insert </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setMirrorOnInsert(bool mirrorOnInsert);

	/// <summary>
	/// Gets a value representing whether the scaling is Uniform or X/YIndependent.
	/// </summary>
	AcPpStyle::ScaleMode		scaleMode() const;

	/// <summary>
	/// Sets a value representing whether the scaling is Uniform or X/YIndependent.
	/// </summary>
	virtual Acad::ErrorStatus			setScaleMode(AcPpStyle::ScaleMode scalemode);

    /// <summary>
	/// Gets a value representing scale factor of style.
	/// </summary>
	/// <returns> value representing scale factor of style </returns>
	double                      scaleFactor() const;

	/// <summary>
	/// Sets a value representing scale factor of stlye.
	/// </summary>
	/// <param name ="scale"> value representing scale factor of stlye </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setScaleFactor(double scale);

    
	/// <summary>
	/// Function to determine if nozzle style id is set.
	/// </summary>
	/// <returns> Returns true if nozzle style id is set otherwise returns false </returns>
    bool                        autoNozzle() const;
	
	/// <summary>
	/// Gets a value representing the autonozzle style id of style.
	/// </summary>
	/// <returns> value representing the autonozzle style id of style </returns>
	AcDbObjectId                autoNozzleStyleId() const;

	/// <summary>
	/// Sets a value representing the autonozzle style id of style.
	/// </summary>
	/// <param name ="styleId"> value representing the autonozzle style id of style </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setAutoNozzleStyleId(const AcDbObjectId& styleId);

    /// <summary>
    /// Returns whether a DynamicAsset should be created 
    /// </summary>
	/// <param name ="bDynamic"> Is true is Dynamic asset is to be created </param>
	/// <returns>Acad::eOk if okay</returns>
	virtual Acad::ErrorStatus          isDynamicAssetRequired(bool& bDynamic) const; 


 	/// <summary>
	/// This functions purpose is to allow the object to write out its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to write out the object's data </param>
	/// <returns>Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const ;

	/// <summary>
	/// This functions purpose is to allow the object to read in its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to read in the object's data </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) ;

    /// <summary>
	/// This functions purpose is to allow the object to write out its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to write out the object's data </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler *pFiler) const ;
    
	/// <summary>
	/// This functions purpose is to allow the object to read in its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to read in the object's data </param>
	/// <returns> Acad::ErrorStatus</returns>
	virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler *pFiler) ;	

	/// <summary>
	/// This function is called by AutoCAD when the AUDIT command is executed
	/// </summary>
	/// <param name =""> Passed in a pointer to an AcDbAuditInfo object </param>
	/// <returns> Acad::ErrorStatus</returns>
    virtual Acad::ErrorStatus   audit(AcDbAuditInfo* pAuditInfo);

protected:
    AcPpAssetStyle(bool bImpDone);
};

/// <summary>
/// OffPageConnectorStyle Class
/// </summary>
class PNIDOBJECTS_API AcPpOffPageConnectorStyle :public AcPpAssetStyle
{
public:
    ACRX_DECLARE_MEMBERS(AcPpOffPageConnectorStyle);

	/// <summary>
	/// Default Constructor.
	/// </summary>
	AcPpOffPageConnectorStyle();
	
	/// <summary>
	/// Copy Constructor.
	/// </summary>
	AcPpOffPageConnectorStyle(const AcPpOffPageConnectorStyle&);

	/// <summary>
	/// Destructor.
	/// </summary>
    virtual ~AcPpOffPageConnectorStyle();
    AcPpOffPageConnectorStyle & operator=( const AcPpOffPageConnectorStyle & );

	/// <summary>
	/// This functions purpose is to allow the object to write out its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to write out the object's data </param>
	/// <returns>Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const ;

	/// <summary>
	/// This functions purpose is to allow the object to read in its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to read in the object's data </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) ;

    /// <summary>
	/// This functions purpose is to allow the object to write out its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to write out the object's data </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler *pFiler) const ;
    
	/// <summary>
	/// This functions purpose is to allow the object to read in its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to read in the object's data </param>
	/// <returns> Acad::ErrorStatus</returns>
	virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler *pFiler) ;
	
	/// <summary>
	/// This function is called by AutoCAD when the AUDIT command is executed.
	/// </summary>
	/// <param name = "pAuditInfo">  Passed in a pointer to an AcDbAuditInfo object  </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus   audit(AcDbAuditInfo* pAuditInfo);

protected:
	AcPpOffPageConnectorStyle(bool bImpDone);
};

#endif // __ACPPSTYLES_H__
