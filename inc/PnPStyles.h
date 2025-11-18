//
// (C) Copyright 2009 by Autodesk, Inc.
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

#ifndef __PNPSTYLES_H__
#define __PNPSTYLES_H__

#pragma once

#include "AcString.h"
#include "dbapserv.h"
#include "PnPDllDef.h"

class AcPpImpStyle;
class AcPpImpAnnotationStyle;


/// <summary>
/// This is the base class for describing various asset style properties. 
/// </summary>
class PNPCOMMONDBX_API AcPpStyle : public AcDbObject
{
public:

	/// <summary>
	/// Scale mode enumeration.
	/// </summary>
	enum ScaleMode{
		kUniform        = 0,
		kXYIndependent  = 1,
	};

	/// <summary>
	/// Tag type enumeration.
	/// </summary>
    enum TagType{
		/// <summary> Tag values are set automatically </summary>
        kAutomatic       = 0,
		/// <summary> Tag values are prompted before they are set</summary>
        kPrompt          = 1,
		/// <summary> No tag values </summary>
        kNoTag           = 2
    };

public:
    ACRX_DECLARE_MEMBERS(AcPpStyle);

	/// <summary>
	/// Copy Constructor.
	/// </summary>
	AcPpStyle(const AcPpStyle&);

	/// <summary>
	/// Destructor.
	/// </summary>
    virtual ~AcPpStyle();

    AcPpStyle & operator=( const AcPpStyle & );

	virtual Acad::ErrorStatus copyFrom(const AcPpStyle& style); 

    //common properties
    /// <summary>
    /// Gets a value representing the name of this style.
    /// </summary>
	/// <param name ="name">Value representing the name of this style </param>
	/// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus           getName(AcString& name) const;

	/// <summary>
    /// Sets a value representing the name of this style.
    /// </summary>
	/// <param name ="pName"> Value representing the name of this style </param>
	/// <returns>Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setName(const ACHAR * pName);

    /// <summary>
    /// Gets a value representing the description of this style.
    /// </summary>
	/// <returns> Value representing the description of this style </returns>
	const ACHAR*                description() const;

	/// <summary>
    /// Sets a value representing the description of this style.
    /// </summary>
	/// <param name ="pDescription"> Value representing the description of this style </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setDescription(const ACHAR * pDescription);

    /// <summary>
    /// Gets a value representing the class name of this style.
    /// </summary>
	/// <returns> Value representing the class name of this style </returns>
	const ACHAR*                styleClassName() const;

	/// <summary>
    /// Sets a value representing the class name of this style.
    /// </summary>
	/// <param name ="pClassName"> Value representing the class name of this style </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setStyleClassName(const ACHAR * pClassName);

    /// <summary>
    /// Gets a value representing the color of this style.
    /// </summary>
	/// <returns> Value representing the color of this style </returns>
	AcCmColor                   color() const;

	/// <summary>
    /// Sets a value representing the color of this style.
    /// </summary>
	/// <param name ="color"> Value representing the color of this style </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setColor(const AcCmColor& color);

    /// <summary>
    /// Gets a value representing the layer id of this style.
    /// </summary>
	/// <returns> Value representing the layer id of this style </returns>
	AcDbObjectId                layerId() const;

	/// <summary>
    /// Sets a value representing the layer id of this style.
    /// </summary>
	/// <param name ="newVal"> Value representing the layer id of this style </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setLayer(const AcDbObjectId& newVal);

    /// <summary>
    /// Gets a value representing the line weight of this style.
    /// </summary>
	/// <returns> Value representing the line weight of this style </returns>
	AcDb::LineWeight            lineWeight() const;

	/// <summary>
    /// Sets a value representing the line weight of this style.
    /// </summary>
	/// <param name ="lineWeight"> Value representing the line weight of this style </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setLineWeight(AcDb::LineWeight lineWeight);

    /// <summary>
    /// Gets a value representing the line type id of this style.
    /// </summary>
	/// <returns> Value representing the line type id of this style </returns>
	AcDbObjectId                linetypeId() const;

	/// <summary>
    /// Sets a value representing the line type id of this style.
    /// </summary>
	/// <param name ="newVal"> Value representing the line type id of this style </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setLinetype(const AcDbObjectId& newVal);

    /// <summary>
    /// Gets a value representing the line type scale of this style.
    /// </summary>
	/// <returns> Value representing the line type scale of this style </returns>
	double                      linetypeScale() const;

	/// <summary>
    /// Sets a value representing the line type scale of this style.
    /// </summary>
	/// <param name ="newVal"> Value representing the line type scale of this style </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setLinetypeScale(double newVal);

    /// <summary>
    /// Gets a value representing the plot style of this style.
    /// </summary>
	/// <returns> Value representing the plot style of this style </returns>
	const ACHAR*                plotStyleName() const;

	/// <summary>
    /// Sets a value representing the plot style of this style.
    /// </summary>
	/// <param name ="pName"> Value representing the plot style of this style </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setPlotStyleName(const ACHAR* pName);
    
	/// <summary>
    /// Gets a value representing the symbol name of this style.
    /// </summary>
	/// <returns> Value representing the symbol name of this style </returns>
    const ACHAR*                symbolName() const;

	/// <summary>
    /// Sets a value representing the symbol name of this style.
    /// </summary>
	/// <param name ="symbolName"> Value representing the symbol name of this style </param>
	virtual Acad::ErrorStatus  setSymbolName(const ACHAR* symbolName);


	/// <summary>
    /// Gets a value representing the symbol path of this style.
    /// </summary>
	/// <returns> Value representing the symbol path of this style </returns>
    const ACHAR*                symbolPath();


	/// <summary>
    /// Sets a value representing the symbol path of this style.
    /// </summary>
	/// <param name ="symbolName"> Value representing the symbol path of this style </param>
	virtual Acad::ErrorStatus setSymbolPath(const ACHAR* symbolPath);

   	/// <summary>
    /// Sets a value representing the symbol name and symbol path.
    /// </summary>
	/// <param name ="symbolName"> Value representing the symbol type of this style </param>
	/// <param name ="symbolPath"> Value representing the symbol path of this style </param>
	/// <param name ="newSybmolName"> Value representing the symbol name of this style </param>
	/// <returns> Acad::ErrorStatus  </returns> 
	virtual Acad::ErrorStatus           setSymbolNamePath(const ACHAR* symbolName, const ACHAR* symbolPath, const ACHAR* newSybmolName = NULL);


	/// <summary>
    /// Gets a value representing the block table record id.
    /// </summary>
	/// <returns> block table record id as reference to AcDbObject class </returns> 
    AcDbObjectId           blockTableRecord() const;

	/// <summary>
    /// Sets a value representing the block table record id.
    /// </summary>
	/// <param name ="id"> block table record id as reference to AcDbObject class</param>
	/// <returns> Acad::ErrorStatus </returns> 
	virtual Acad::ErrorStatus setBlockTableRecord(const AcDbObjectId& id); 
    
	/// <summary>
    /// Gets a value representing whether this asset is using the current color.
    /// </summary>
	/// <returns> Value representing whether this asset is using the current color </returns>
    bool                        isUsingDatabaseColor() const;

	/// <summary>
    /// Sets a value representing whether this asset is using the current color.
    /// </summary>
	/// <param name ="bUseCurrentColor"> Value representing whether this asset is using the current color </param>
    virtual Acad::ErrorStatus           setUseDatabaseColor(bool bUseCurrentColor);

	/// <summary>
    /// Gets a value representing whether this asset is using the current layer.
    /// </summary>
	/// <returns> Value representing whether this asset is using the current layer </returns>
    bool                        isUsingDatabaseLayer() const;

	/// <summary>
    /// Sets a value representing whether this asset is using the current layer.
    /// </summary>
	/// <param name ="bUseCurrentLayer"> Value representing whether this asset is using the current layer </param>
    virtual Acad::ErrorStatus           setUseDatabaseLayer(bool bUseCurrentLayer);

	/// <summary>
    /// Gets a value representing whether this asset is using the current line type.
    /// </summary>
	/// <returns> Value representing whether this asset is using the current line type </returns>
    bool                        isUsingDatabaseLinetype() const;

	/// <summary>
    /// Sets a value representing whether this asset is using the current line type.
    /// </summary>
	/// <param name ="bUseCurrentLinetype"> Value representing whether this asset is using the current line type </param>
    virtual Acad::ErrorStatus           setUseDatabaseLinetype(bool bUseCurrentLinetype);

	/// <summary>
    /// Gets a value representing whether this asset is using the current line type scale.
    /// </summary>
	/// <returns> Value representing whether this asset is using the current line type scale </returns>
    bool                        isUsingDatabaseLinetypeScale() const;

	/// <summary>
    /// Sets a value representing whether this asset is using the current line type scale.
    /// </summary>
	/// <param name ="bUseCurrentLinetypeScale"> Value representing whether this asset is using the current line type scale </param>
    Acad::ErrorStatus           setUseDatabaseLinetypeScale(bool bUseCurrentLinetypeScale);

	/// <summary>
    /// Gets a value representing whether this asset is using the current plot style.
    /// </summary>
	/// <returns> Value representing whether this asset is using the current plot style </returns>
    bool                        isUsingDatabasePlotStyle() const;

	/// <summary>
    /// Sets a value representing whether this asset is using the current plot style.
    /// </summary>
	/// <param name ="bUseCurrentPlotStyle"> Value representing whether this asset is using the current plot style </param>
    virtual Acad::ErrorStatus           setUseDatabasePlotStyle(bool bUseCurrentPlotStyle);

	/// <summary>
    /// Gets a value representing whether this asset is using the current line weight.
    /// </summary>
	/// <returns> Value representing whether this asset is using the current line weight </returns>
    bool                        isUsingDatabaseLineWeight() const;

	/// <summary>
    /// Sets a value representing whether this asset is using the current line weight.
    /// </summary>
	/// <param name ="bUseCurrentLineWeight"> Value representing whether this asset is using the current line weight  </param>
    virtual Acad::ErrorStatus           setUseDatabaseLineWeight(bool bUseCurrentLineWeight);

    /// <summary>
    /// Gets a value representing the tag type of this style.
    /// </summary>
	/// <returns> Value representing the tag type of this style</returns>
	AcPpStyle::TagType          tagType() const;

	/// <summary>
    /// Sets a value representing the tag type of this style.
    /// </summary>
	/// <param name ="tagType"> Value representing the tag type of this style </param>
    virtual Acad::ErrorStatus           setTagType(AcPpStyle::TagType tagType);

	/// <summary>
	/// This function is called by dwgOut(). Its purpose is to allow the object to write out its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to write out the object's data </param>
	/// <returns>Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const ;
	
	/// <summary>
	/// This function is called by dwgIn(). Its purpose is to allow the object to read in its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to read in the object's data </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) ;

	/// <summary>
	/// This function is called by dxfOut(). Its purpose is to allow the object to write out its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to write out the object's data </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler *pFiler) const ;

	/// <summary>
	/// This function is called by dwgIn(). Its purpose is to allow the object to read in its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to read in the object's data </param>
	/// <returns> </returns>
	virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler *pFiler) ;

	/// <summary>
	/// This function is called by AutoCAD when the AUDIT command is executed. 
	/// The AcDbAuditInfo object pointed to by pAuditInfo contains member functions that are used to determine what to do and also to report the results of the audit operation on the object.
	/// </summary>
	/// <param name = "auditor"> Passed in a pointer to an AcDbAuditInfo object </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus   audit(AcDbAuditInfo* pAuditInfo);	

	AcPpImpStyle* imp() const; 

protected:
								AcPpStyle(bool bImpDone);
	AcPpImpStyle*				mpImpStyle;

	/// <summary>
	/// Default Constructor.
	/// </summary>
	AcPpStyle();

};

/// <summary>
/// This class defines the annotation style. Derived from AcPpStyle.
/// </summary>
class PNPCOMMONDBX_API AcPpAnnotationStyle : public AcPpStyle
{
public:
	/// <summary>
	/// AutoInsert Options enumeration.
	/// </summary>
    enum AutoInsertOptions
    {
        kNoAutoInsert  = 0,
        kAutoInsertWithPrompt  = 1,
        kAutoInsert   = 2,
    };

    enum OrientationOptions
    {
        kOrthogonal = 0,
        kHorizontal = 1,
        kVertical   = 2,
        kAligned    = 3
    };

    enum LeaderOptions
    {
        kNoLeader = 0,
        kPromptForLeader = 1
    };

public:
    ACRX_DECLARE_MEMBERS(AcPpAnnotationStyle);

	/// <summary>
	/// Default Constructor.
	/// </summary>
    AcPpAnnotationStyle(unsigned short b3d = 0);

	/// <summary>
	/// Copy Constructor.
	/// </summary>
	AcPpAnnotationStyle(const AcPpAnnotationStyle&);

	/// <summary>
	/// Destructor.
	/// </summary>
    virtual ~AcPpAnnotationStyle();
    AcPpAnnotationStyle & operator=( const AcPpAnnotationStyle & );

	/// <summary>
	/// Gets a value representing whether target properties are used.
	/// </summary>
	/// <returns> Value representing whether target properties are used </returns>
	bool useTargetProperties() const;

	/// <summary>
	/// Sets a value representing whether target properties are used.
	/// </summary>
	/// <param name ="bUseTarget"> Value representing whether target properties are used </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus           setUseTargetProperties(bool bUseTarget);

    /// <summary>
	/// Gets a value representing whether style is linked.
	/// </summary>
	/// <returns> value representing whether style is linked </returns>
	bool                        linked() const;

	/// <summary>
	/// Sets a value representing whether style is linked.
	/// </summary>
	/// <param name ="bLinked"> Value representing whether style is linked </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus setLinked(bool bLinked);

    /// <summary>
	/// Gets a value representing autoinsert options of style.
	/// </summary>
	/// <returns> Value representing autoinsert options of style </returns>
	AcPpAnnotationStyle::AutoInsertOptions  autoInsert() const;

	/// <summary>
	/// Sets a value representing autoinsert options of style.
	/// </summary>
	/// <param name ="nOptions"> Value representing autoinsert options of style </param>
    virtual Acad::ErrorStatus           setAutoInsert(AcPpAnnotationStyle::AutoInsertOptions nOptions);
    
    /// <summary>
	/// Gets a value representing positional offset of style.
	/// </summary>
	/// <returns> Value representing positional offset of style </returns>
	AcGePoint2d                 positionalOffset() const;

	/// <summary>
	/// Sets a value representing positional offset of style.
	/// </summary>
	/// <param name ="offset"> Value representing positional offset of style </param>
    virtual Acad::ErrorStatus           setPositionalOffset(const AcGePoint2d& offset);

	/// <summary>
	/// Gets a value representing whether the scale is independent or not.
	/// </summary>
	AcPpStyle::ScaleMode		scaleMode() const;

	/// <summary>
	/// Sets a value representing whether the scale is independent or not.
	/// </summary>
	virtual Acad::ErrorStatus			setScaleMode(AcPpStyle::ScaleMode scalemode);

    /// <summary>
	/// Gets a value representing whether style is scaled on insert.
	/// </summary>
	/// <returns> Value representing whether style is scaled on insert </returns>
	bool                        scaleOnInsert() const;

	/// <summary>
	/// Sets a value representing whether style is scaled on insert.
	/// </summary>
	/// <param name ="scaleOnInsert"> Value representing whether style is scaled on insert </param>
    virtual Acad::ErrorStatus setScaleOnInsert(bool scaleOnInsert);

	/// <summary>
	/// Gets a value representing scale factor of style.
	/// </summary>
	/// <returns>Scale factor </returns>
    double                      scaleFactor() const;

	/// <summary>
	/// Sets a value representing scale factor of style.
	/// </summary>
	/// <param name ="scale"> Scale factor to set</param>
    virtual Acad::ErrorStatus           setScaleFactor(double scale);

    /// <summary>
	/// Gets a value representing orientation of the style.
	/// </summary>
	/// <returns>Orientation </returns>
    AcPpAnnotationStyle::OrientationOptions orientation() const;

    /// <summary>
	/// Sets a value representing orientation of the style.
	/// </summary>
	/// <param name ="o"> Orientation to set</param>
    virtual Acad::ErrorStatus setOrientation(AcPpAnnotationStyle::OrientationOptions o);

    /// <summary>
	/// Gets a value representing the style's leader support.
	/// </summary>
	/// <returns> value representing whether style is linked </returns>
    AcPpAnnotationStyle::LeaderOptions leader() const;

	/// <summary>
	/// Sets a value representing the style'ls leader support.
	/// </summary>
	/// <param name ="bLeader"> Value representing how the style supports a leader </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus setLeader(AcPpAnnotationStyle::LeaderOptions leaderOpt);


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
	AcPpAnnotationStyle(bool bImpDone);
};


#endif // __PNPSTYLES_H__
