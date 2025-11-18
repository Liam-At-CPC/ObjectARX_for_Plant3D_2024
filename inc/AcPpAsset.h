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

//-----------------------------------------------------------------------------
//----- AcPpAsset.h : Declaration of the AcPpAsset
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "dbmain.h"
#include "dbobjptr.h"
#include "AcPpDataLinks.h"
#include "PnPDllDef.h"

class AcPpImpAsset;
//-----------------------------------------------------------------------------
/// <summary>
/// The AcPpAsset class includes all functions that helps developers define Asset behaviour.
/// </summary>
class PNIDOBJECTS_API AcPpAsset : public AcDbEntity {

    friend class AcPpImpAsset;

public:
     ACRX_DECLARE_MEMBERS(AcPpAsset);

    //add type info, what the type value means has not be determined ultimately

/// <summary>
/// Asset type enumeration.
/// </summary>
    enum AssetType
    {
        kUnAssigned         = -1,       //  -1--- not assigned 
        kNozzle             = 0,        //  0---- nozzle
        kInlineAsset        = 1,        //  1---- inside asset
        kEndAsset           = 2,        //  2---- end asset
        kOffPageConnector   = 3,        //  3---- off page connector
        kFlowArrow          = 4,        //  4---- flow arrow
        kSpecBreak          = 5,        //  5---- spec break
        kControlValve       = 6,        //  6---- control valve: body
        kActuator           = 7,        //  7---- control valve: actuator
        kFlag			    = 8			//  8---- Flag
        // NOTE: If you add enum values, also update the AssetType enum in mgAsset.h
    };

/// <summary>
/// Asset context enumeration.
/// </summary>
    enum AssetContext
    {
        kContextUnAssigned  = -1,       //  -1--- not assigned
        kContextInline      = 0,        //  0---- Asset BEHAVING like an Inline Component
        kContextStart       = 1,        //  1---- Asset BEHAVING like a Start Component
        kContextEnd         = 2,        //  2---- Asset BEHAVING like an  End Component
        kContextNozzle      = 3,        //  3---- Asset BEHAVING like a Nozzle
        kContextAll         = 4         //  4---- Assets BEHAVING like Inline/Start/End Components
    };

protected:
    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name = "bImpDone"> Boolean parameter. Pass it as true if the imp object is already created. </param>
    /// <exception cref=""> None </exception>
    /// <returns> None </returns>
    AcPpAsset (bool bImpDone) ;

public:
     /// <summary>
    /// Default constructor.
    /// </summary>
    AcPpAsset () ;

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcPpAsset () ;

    //----- AcDbObject protocols

    /// <summary>
    /// This function is called when proxy graphics are being generated.
    /// </summary>
    virtual void saveAs(AcGiWorldDraw* mode, AcDb::SaveType st);

    //- Dwg Filing protocol
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

    //- Dxf Filing protocol
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

    //- SubXXX() methods (self notification)
    /// <summary>
    /// Called from within erase() before anything else is done. The default implementation is to return Acad::eOk.
    /// However, when overridden in custom classes, it provides a hook into the erase operation. 
    /// If it returns anything other than Acad::eOk, then the erase operation is immediately terminated.
    /// </summary>
    /// <param name = "erasing">  Passed in copy of the erasing argument that was passed into the erase() function call that triggered this subErase() call</param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subErase (Adesk::Boolean erasing) ;


    /// <summary>
    /// Called from within close() before anything else is done. The default implementation is to return Acad::eOk. 
    /// However, when overridden in custom classes, it provides a hook into the close operation. 
    /// If it returns anything other than Acad::eOk, then the close operation is immediately terminated.
    /// </summary>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subClose () ;

    /// <summary>
    /// This function creates a clone of the object and returns a pointer to the clone. 
    /// If the function is not successful in creating the clone, then NULL is returned.
    /// </summary>
    /// <returns> pointer to AcRxObject class </returns>
    virtual AcRxObject*        clone() const;

    /// <summary>
    /// This function is called by AutoCAD when the AUDIT command is executed. 
    /// The AcDbAuditInfo object pointed to by pAuditInfo contains member functions that are used to determine what to do and also to report the results of the audit operation on the object.
    /// </summary>
    /// <param name = "auditor">  </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus audit(AcDbAuditInfo* auditor);

    /// <summary>
    /// This function is called when a drag operation involving this entity is starting, ending, or aborting. 
    /// The status argument provides information about what is happening with the drag operation.
    /// </summary>
    /// <param name = "status">Value describing the status of the drag operation; one of the values from the DragStat enumeration  </param>
    virtual void              dragStatus(const AcDb::DragStat status);

    // Functions specific to AcPpAsset

    /// <summary>
    /// Sets a value representing the position of this asset.
    /// </summary>
    /// <param name = "location"> Value representing the position of this asset </param>
    void setPosition(const AcGePoint3d& location);

    /// <summary>
    /// Gets a value representing the position of this asset.
    /// </summary>
    /// <returns> Value representing the position of this asset </returns>
    AcGePoint3d position() const;

    /// <summary>
    /// Sets a value representing the normal of this asset.
    /// </summary>
    /// <param name = "normal"> Value representing the normal of this asset </param>
    void setNormal(const AcGeVector3d& normal);

    /// <summary>
    /// Gets a value representing the normal of this asset.
    /// </summary>
    /// <returns> Value representing the normal of this asset </returns>
    AcGeVector3d normal() const;

    /// <summary>
    /// Sets a value representing the X-axis of this asset.
    /// </summary>
    /// <param name = "xAxis"> Value representing the X-axis of this asset </param>
    void setXAxis(const AcGeVector3d& xAxis);

    /// <summary>
    /// Gets a value representing the X-axis of this asset.
    /// </summary>
    /// <returns> Value representing the X-axis of this asset </returns>
    AcGeVector3d        xAxis() const;

    /// <summary>
    /// Gets a value representing the X-axis angle of this asset.
    /// </summary>
    /// <returns> Value representing the X-axis angle of this asset</returns>
    double xAxisAngle() const;

    /// <summary>
    /// Sets a value representing the id of the owner of this asset.
    /// </summary>
    /// <param name = "ownerId"> Value representing the id of the owner of this asset </param>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus   setOwnerAssetId(const AcDbObjectId& ownerId);

    /// <summary>
    /// Gets a value representing the id of the owner of this asset.
    /// </summary>
    /// <returns> Value representing the id of the owner of this asset </returns>
    AcDbObjectId        ownerAssetId() const;
    
    /// <summary>
    /// Gets a collection of values representing the ids of line segments
    /// that are associated with this asset, in the specified context.
    /// </summary>
    /// <param name="ids">Line Segment ID Array</param>
    /// <param name="assetContext">Asset context</param>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus   getLineSegmentIds(AcDbObjectIdArray& ids, const AcPpAsset::AssetContext& assetContext = AcPpAsset::kContextUnAssigned) const;

    /// <summary>
    /// Disassociate a line segment from this asset.
    /// </summary>
    /// <param name="id">Id of line segment</param>
    /// <param name="assetContext">Asset context</param>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus   removeLineSegmentId(const AcDbObjectId& id, const AcPpAsset::AssetContext& assetContext = AcPpAsset::kContextUnAssigned);
 
    /// <summary>
    /// Associate a line segment with this asset.
    /// </summary>
    /// <param name="id">Id of line segment</param>
    /// <param name="assetContext">Asset context</param>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus   addLineSegmentId(const AcDbObjectId& id, const AcPpAsset::AssetContext& assetContext = AcPpAsset::kContextUnAssigned);
 
    /// <summary>
    /// Associate a collection of line segments with this asset.
    /// </summary>
    /// <param name="ids">Collection of line segment ids</param>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus   addLineSegmentIds(const AcDbObjectIdArray& ids);
  
    /// <summary>
    /// Sets a value representing whether this asset is with
    /// a S-line.
    /// </summary>
    /// <param name = "bIsWithSline"> Bool value representing whether the asset is with S-line </param>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus  setIsWithSline( bool bIsWithSline );

    /// <summary>
    /// Gets a value representing whether this asset is with
    /// a S-line.
    /// </summary>
    /// <returns> Bool value representing whether the asset is with S-line</returns>
    bool isWithSline() const;

    /// <summary>
    /// Gets a value representing the block table record id of this asset.
    /// </summary>
    /// <returns> Value representing the block table record id of this asset </returns>
    AcDbObjectId blockTableRecord() const;
 
    /// <summary>
    /// Sets a value representing the block table record id of this asset. Overrides style.
    /// </summary>
    /// <returns> Value representing the block table record id of this asset </returns>
    virtual Acad::ErrorStatus setBlockTableRecord(const AcDbObjectId& blockId);

    /// <summary>
    /// Gets a value representing the block transformation matrix of this asset.
    /// </summary>
    /// <returns> Value representing the block transformation matrix of this asset </returns>
    virtual AcGeMatrix3d blockTransform() const;
 
    /// <summary>
    /// Sets a value representing the block transformation matrix of this asset.
    /// </summary>
    /// <param name = "xform"> Value representing the block transformation matrix of this asset </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus setBlockTransform(const AcGeMatrix3d& xform);
 
    /// <summary>
    /// Gets a value representing the cache id of this asset.
    /// </summary>
    /// <returns> Value representing the cache id of this asset </returns>
    AcPpRowId  cacheId() const;
 
    /// <summary>
    /// Sets a value representing the style id of this asset.
    /// </summary>
    /// <param name = "styleId"> Value representing the style id of this asset </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus   setStyleId(const AcDbObjectId& styleId);

    /// <summary>
    /// Gets a value representing the style id of this asset.
    /// </summary>
    /// <returns> Value representing the style id of this asset </returns>
    AcDbObjectId        styleId() const;
 
    /// <summary>
    /// Sets a value representing the tag style id of this asset.
    /// </summary>
    /// <param name = "tagStyleId"> Value representing the tag style id of this asset </param>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus setTagStyleId(const AcDbObjectId& tagStyleId);
 
    /// <summary>
    /// Gets a value representing the tag style id of this asset.
    /// </summary>
    /// <returns> Value representing the tag style id of this asset </returns>
    AcDbObjectId        tagStyleId() const;

    /// <summary>
    /// Sets a value representing the group id of this asset.
    /// </summary>
    /// <param name = "styleId"> Value representing the group id of this asset </param>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus setGroupId(const AcDbObjectId& styleId);
 
    /// <summary>
    /// Gets a value representing the group id of this asset.
    /// </summary>
    /// <returns> Returns the value repsenting the group id of this asset </returns>
    AcDbObjectId groupId() const;
 
    /// <summary>
    /// Sets a value representing the scale of this asset.
    /// </summary>
    /// <param name = "scale3d"> Value representing the scale of this asset </param>
    /// <returns> Acad::ErrorStatus </returns>
    Acad::ErrorStatus setScaleFactors(const AcGeScale3d& scale3d);

    /// <summary>
    /// Gets a value representing the scale of this asset.
    /// </summary>
    /// <returns> Value representing the scale of the asset </returns>
     AcGeScale3d scaleFactors() const;
 
    /// <summary>
    /// Sets a value representing the type of this asset.
    /// </summary>
    /// <param name = "iType"> Value representing the type of asset</param>
    void setType(AcPpAsset::AssetType iType);
 
    /// <summary>
    /// Gets a value representing the type of this asset.
    /// </summary>
    /// <returns> The value representing the type of asset </returns>	
    AcPpAsset::AssetType type() const;

    /// <summary>
    /// Sets a value representing whether this asset is flipped.
    /// </summary>
    /// <param name = "bFlipped"> Boolean switch to set the flip </param>
    void setIsFlipped(bool bFlipped);
 
    /// <summary>
    /// Gets a value representing whether this asset is flipped.
    /// </summary>
    /// <returns> Returns true if flipped </returns>	
    bool isFlipped();
 
    /// <summary>
    /// Make this asset an owner of the specified asset.
    /// </summary>
    /// <param name="ownedId">Id of asset</param>
    /// <returns> Acad::ErrorStatus </returns>	
    Acad::ErrorStatus   addOwnedAsset(const AcDbObjectId& ownedId);
 
    /// <summary>
    /// Remove ownership of the specified asset.
    /// </summary>
    /// <param name="ownedId">Id of asset</param>
    /// <returns> Acad::ErrorStatus </returns>	
    Acad::ErrorStatus   removeOwnedAsset(const AcDbObjectId& ownedId);
 
    /// <summary>
    /// Gets a collection of values representing the ids of assets that 
    /// this asset owns.
    /// </summary>
    /// <param name = "ids"> Collection of values representing the ids of assets that 
    /// this asset owns </param>
    /// <returns> Acad::ErrorStatus </returns>	
    Acad::ErrorStatus   getOwnedAssets(AcDbObjectIdArray& ids) const;

    /// <summary>
    /// Add the specified annotation to this asset.
    /// </summary>
    /// <param name="annotationId">Id of annotation</param>
    /// <returns> Acad::ErrorStatus </returns>	
    Acad::ErrorStatus   addAnnotation(const AcDbObjectId& annotationId);
 
    /// <summary>
    /// Remove the specified annotation from this asset.
    /// </summary>
    /// <param name="annotationId">Id of annotation</param>
    /// <returns> Acad::ErrorStatus </returns>	
    Acad::ErrorStatus   removeAnnotation(const AcDbObjectId& annotationId);
 
    /// <summary>
    /// Gets a collection of values representing the ids of the annotations
    /// of this asset.
    /// </summary>
    /// <param name = "ids"> Collection of values representing the ides of the annotations </param>
    /// <returns> Acad::ErrorStatus </returns>	
    Acad::ErrorStatus   getAnnotations(AcDbObjectIdArray& ids) const;
 
    /// <summary>
    /// Gets a collection of values representing the ids of the attachment
    /// points of this asset.
    /// </summary>
    /// <param name = "points"> Attachement points contained in AcGePoint3dArray </param>
    /// <returns> Acad::ErrorStatus </returns>	
    virtual Acad::ErrorStatus   getAttachmentPoints(AcGePoint3dArray& points) const;

    /// <summary>
    /// Gets a value representing the class name of this asset.
    /// </summary>
    /// <param name = "bFetchFromDataCache"> Boolean deciding whether to fetch the tag value from data cache. Defaulted to true </param>
    /// <returns> AcString representing the class name </returns>	
    AcString            assetClassName(bool bFetchFromDataCache = true);
 
    /// <summary>
    /// Gets a value representing the tag value of this asset.
    /// </summary>
    /// <param name = "bFetchFromDataCache"> Boolean deciding whether to fetch the tag value from data cache. Defaulted to true </param>
    /// <returns> AcString representing the tag value </returns>	
    AcString            tagValue(bool bFetchFromDataCache = true);

    // Utility functions    

    /// <summary>
    /// This function returns pointer to AcPpImpAsset class
    /// </summary>
    /// <returns> Pointer to  AcPpImpAsset class</returns>	
    AcPpImpAsset*       implementation();

    // style overrides

    /// <summary>
    /// Function to set new color
    /// </summary>
    /// <param name = "color"> AcCmColor representing the new color to set </param>
    /// <param name = "doSubents"> Adesk::Boolean </param>	
    /// <returns> Acad::ErrorStatus </returns>	
    virtual Acad::ErrorStatus	setColor(const AcCmColor& color,   Adesk::Boolean doSubents = true, AcDbDatabase *pDb = NULL);

    /// <summary>
    /// Function to set new color index
    /// </summary>
    /// <param name = "color"> Adesk::UInt16 representing the color index to set </param>
    /// <param name = "doSubents"> Adesk::Boolean </param>	
    /// <returns> Acad::ErrorStatus </returns>	
    virtual Acad::ErrorStatus   setColorIndex(Adesk::UInt16 color, Adesk::Boolean doSubents = true);

    /// <summary>
    /// Function to set new layer
    /// </summary>
    /// <param name = "newVal"> String representing new layer </param>
    /// <param name = "doSubents"> Adesk::Boolean </param>	
    /// <param name = "allowHiddenLayer"> Boolean to allow hidden layer. Defaulted to false </param>
    /// <returns> Acad::ErrorStatus </returns>	
    virtual Acad::ErrorStatus   setLayer(const ACHAR* newVal, Adesk::Boolean doSubents = true,
                                         bool allowHiddenLayer = false);

    /// <summary>
    /// Function to set new layer
    /// </summary>
    /// <param name = "newVal"> AcDbObjectId of the new layer to set</param>
    /// <param name = "doSubents"> Adesk::Boolean </param>	
    /// <param name = "allowHiddenLayer">  Boolean to allow hidden layer. Defaulted to false</param>
    /// <returns> Acad::ErrorStatus </returns>	
    virtual Acad::ErrorStatus   setLayer(AcDbObjectId newVal, Adesk::Boolean doSubents = true,
                                         bool allowHiddenLayer = false);

    /// <summary>
    /// Function to set new line type
    /// </summary>
    /// <param name = "newVal">  String representing the new line type</param>
    /// <param name = "doSubents"> Adesk::Boolean </param>	
    /// <returns> Acad::ErrorStatus </returns>	
    virtual Acad::ErrorStatus   setLinetype(const ACHAR* newVal, Adesk::Boolean doSubents = true);


    /// <summary>
    /// Function to set new line type
    /// </summary>
    /// <param name = "newVal"> AcDbObjectId of the new line type to set</param>
    /// <param name = "doSubents"> Adesk::Boolean </param>	
    /// <returns> Acad::ErrorStatus </returns>	
    virtual Acad::ErrorStatus   setLinetype(AcDbObjectId newVal, Adesk::Boolean doSubents = true);

    /// <summary>
    /// Function to set line weight
    /// </summary>
    /// <param name = "newVal"> New line weight value to set </param>
    /// <param name = "doSubents"> Adesk::Boolean </param>	
    /// <returns> Acad::ErrorStatus </returns>	
    virtual Acad::ErrorStatus   setLineWeight(AcDb::LineWeight newVal, Adesk::Boolean doSubents = true);

    /// <summary>
    /// Set line type scale
    /// </summary>
    /// <param name = "newval"> Scale factor to set </param>
    /// <param name = "doSubents"> Adesk::Boolean </param>	
    /// <returns> Acad::ErrorStatus </returns>	
    virtual Acad::ErrorStatus   setLinetypeScale(double newval, Adesk::Boolean doSubents = true);

    /// <summary>
    /// Set plot style name
    /// </summary>
    /// <param name = "newName"> New plot style name </param>
    /// <param name = "doSubents"> Adesk::Boolean </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus   setPlotStyleName(const ACHAR* newName, Adesk::Boolean doSubents = true);

    /// <summary>
    /// Set plot style name
    /// </summary>
    /// <param name = "newType"> New AcDb::PlotStyleNameType </param>
    /// <param name = "newId"> AcDbObjectId newId. Default is NULL </param>
    /// <param name = "doSubents"> Adesk::Boolean </param>	
    /// <returns> Acad::ErrorStatus </returns>	
    virtual Acad::ErrorStatus   setPlotStyleName(AcDb::PlotStyleNameType newType, AcDbObjectId newId = AcDbObjectId::kNull,
                                                 Adesk::Boolean doSubents = true);

    //helper Functions for End Code valve 
    /// <summary>
    /// usesEndCodes
    /// </summary>
    /// <param name = "bUsesEndCodes"> bool bUsesEndCodes </param>
    /// <returns> Acad::ErrorStatus </returns>	
    Acad::ErrorStatus AcPpAsset::usesEndCodes(bool& bUsesEndCodes) const ;

    /// <summary>
    /// get Points And Rotations for endcoded valves
    /// </summary>
    /// <param name = "endCodePoints"> AcGePoint3dArray& endCodePoints </param>
    /// <param name = "rotations"> AcArray<double>& rotations </param>
    /// <returns> Acad::ErrorStatus </returns>	
    Acad::ErrorStatus AcPpAsset::getEndCodePointsAndRotations(AcGePoint3dArray& endCodePoints,
                                                                AcArray<double>& rotations) const ;
    /// <summary>
    /// endCodeBlockId
    /// </summary>
    /// <returns> AcDbObjectId </returns>	
    AcDbObjectId AcPpAsset::endCodeBlockId() const ;

    /// <summary>
    /// Highlight only the Asset itself.
    /// </summary>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus highlightOnlyAsset() const;

    /// <summary>
    /// Unhighlight only the Asset itself.
    /// </summary>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus unhighlightOnlyAsset() const;

protected:

    //visivility protocol
    /// <summary>
    /// This method sets the visibility of an asset to the value specified by newVal. If the entity owns subentities and doSubents == Adesk::kTrue, then the visibility change will be applied to the subentities as well. 
    /// </summary>
    /// <param name = "newVal"> Input visibility value to which the asset will be set; possible AcDb::Visibility values are:AcDb::kInvisibleAcDb::kVisible.
    /// <param name = "doSubents"> Input Boolean indicating whether to propagate the change to any subentities the asset may own. 
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subSetVisibility(AcDb::Visibility newVal, Adesk::Boolean doSubents = true);

    /// <summary>
    /// This method returns the asset's current visibility state.
    /// </summary>
    /// <returns> AcDb::Visibility </returns>
    virtual AcDb::Visibility subVisibility() const;

    /// <summary>
    /// This function provides a way for a custom entity to override the graphical attribute settings (such as color and lineweight) specified in the given AcGiDrawableTraits object. 
    /// For example, to override the color, use the AcGiDrawableTraits object's setColor() function. 
    /// </summary>
    /// <param name = "traits"> Input/output pointer to AcGiDrawableTraits object </param>
    /// <returns> Adesk::UInt32 </returns>
    virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits * traits) ;

    /// <summary>
    /// This function gives control of deep clone operations to the object. 
    /// </summary>
    /// <param name = "pOwnerObject"> Input object to which the clones should be appended </param>
    /// <param name = "pClonedObject"> Returns a pointer to the cloned object, or NULL if not cloned </param>
    /// <param name = "idMap"> Input current object ID map </param>
    /// <param name = "isPrimary"> Input Boolean indicating whether this object is primary or owned </param>
    /// <returns> Acad::ErrorStatus </returns>
     virtual Acad::ErrorStatus subDeepClone (AcDbObject *pOwnerObject, AcDbObject *&pClonedObject, AcDbIdMapping &idMap, Adesk::Boolean isPrimary =true) const ;

    /// <summary>
    /// This function is almost identical to AcDbObject::deepClone, except that an AcDbWblockCloneFiler is used and ownership is not carried across database boundaries. 
    /// Subcloning is based on hard owner and hard pointer connections.
    /// </summary>
    /// <param name = "pOwnerObject"> Input object to which the clones should be appended. If the owner has not been cloned, then the AcDbDatabase must be passed in. </param>
    /// <param name = "pClonedObject">Returns the cloned object, or NULL if not cloned </param>
    /// <param name = "idMap"> Input current object ID map</param>
    /// <param name = "isPrimary"> Input Boolean indicating whether this object is primary or owned</param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subWblockClone (AcRxObject *pOwnerObject, AcDbObject *&pClonedObject, AcDbIdMapping &idMap, Adesk::Boolean isPrimary =true) const ;

    /// <summary>
    ///	This function is defined at the AcDbObject level. It is overridden for every other class that traces its derivation to AcDbObject, and is represented by a different COM object type. 
    /// Thus, if you create a custom entity derived from AcDbEntity, and do not override getClassID(), this function returns the CLSID for AcadEntity. 
    /// This means your custom entities will have at least base-level functionality, even if you do not provide COM support for them.
    /// </summary>
    /// <param name = "pClsid"> COM wrapper class ID </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subGetClassID   (CLSID* pClsid) const;

    /// <summary> 
    /// Whenever a regeneration of the entity's graphics is required, AutoCAD calls this function to generate the graphics primitives that will represent this entity on screen. 
    /// This function will then provide a generic set of 3D graphics primitives that AutoCAD will adjust for each viewport's parameters as they are displayed.
    ///</summary>
    /// <param name ="mode"> Input pointer to fully initialized AcGiWorldDraw object </param>
    /// <returns> Adesk::Boolean </returns>
    virtual Adesk::Boolean subWorldDraw (AcGiWorldDraw *mode) ;

    /// <summary>
    /// This function must use the material provided in osnapMode, gsSelectionMark, pickPoint, lastPoint, and viewXform to determine all appropriate osnap points for the entity. 
    /// It must then append all such osnap points to the snapPoints array.
    /// </summary>
    /// <param name = "osnapMode">Input osnap mode being requested  </param>
    /// <param name = "gsSelectionMark"> Input GS marker of the subentity involved in the object snap operation </param>
    /// <param name = "pickPoint"> Input point (in WCS coordinates) picked during the object snap operation  </param>
    /// <param name = "lastPoint"> Input point (in WCS coordinates) selected just before pickPoint </param>
    /// <param name = "viewXform"> Input transformation matrix to transform from WCS to DCS  </param>
    /// <param name = "snapPoints"> Input pre-existing array to append osnap points to (may already contain points); output with object snap points appended  </param>
    /// <param name = "geomIds"> Not in use </param>
    /// <returns> Acad::ErrorStatus</returns>
    virtual Acad::ErrorStatus subGetOsnapPoints (AcDb::OsnapMode osnapMode, Adesk::GsMarker gsSelectionMark, const AcGePoint3d &pickPoint, const AcGePoint3d &lastPoint,
                                              const AcGeMatrix3d &viewXform, AcGePoint3dArray &snapPoints, AcDbIntArray &geomIds) const;

    /// <summary>
    /// This function gets the grip points and supporting information about the grips for this entity. 
    /// The caller is responsible for freeing the AcDbGripData objects whose pointers are in the grips array.
    /// </summary>
    /// <param name = "grips">Array of pointers to dynamically allocated AcDbGripData objects, one for each grip point in the entity  </param>
    /// <param name = "curViewUnitSize"> Size, in pixels, of one drawing unit in the current viewport </param>
    /// <param name = "gripSize"> Current grip size, in pixels  </param>
    /// <param name = "curViewDir"> Vector describing the view direction in the current viewport </param>
    /// <param name = "bitflags"> Bitmap of one or more flags specified by the GetGripPointsFlags enumeration </param>
    /// <returns>Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subGetGripPoints (AcDbGripDataPtrArray &grips, const double curViewUnitSize, const int gripSize,
                                             const AcGeVector3d &curViewDir, const int bitflags) const ;
    /// <summary>
    /// This function is intended to be called by the host application to move the grip points during a grip edit of the entity. 
    /// </summary>
    /// <param name = "gripAppData"> Input array of pointers, one for each grip point to be moved; these are the appData pointers from the AcDbGripData objects for the grip points to be moved </param>
    /// <param name = "offset"> Vector, in WCS coordinates, indicating the direction and magnitude of the translation to be applied to the grips </param>
    /// <param name = "bitflags"> Reserved for future use, currently zero </param>
    /// <returns>Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subMoveGripPointsAt (const AcDbVoidPtrArray &gripAppData, const AcGeVector3d &offset, const int bitflags) ;

    /// <summary>
    /// This function should append to the stretchPoints array any points that are to treated as stretch points for the entity.
    /// </summary>
    /// <param name = "stretchPoints"> Input pre-existing array to append the stretch points to; output with the entity's stretch points appended  </param>
    /// <returns> </returns>
    virtual Acad::ErrorStatus subGetStretchPoints(AcGePoint3dArray& stretchPoints) const;

    /// <summary>
    ///This function is intended to be called by AutoCAD during execution of a stretch command in which the entity has been selected. 
    ///However, it is certainly possible for ObjectARX applications to call this function.
    ///
    /// This function must modify the entity such that the stretch points identified by the indices array are translated to the direction and magnitude specified by the offset vector (which is in WCS coordinates). 
    /// How this affects the rest of the entity is, of course, dependent on the entity, but any other effects must also be taken care of by this function since this is the function that is expected to do all entity modifications that result from the stretch operation.
    /// </summary>
    /// <param name = "indices"> Input array containing index values (which correspond to stretch points reported by the getStretchPoints() method) that indicate which stretch points are being translated </param>
    /// <param name = "offset"> Input vector (in WCS coordinates) indicating the direction and magnitude that the stretch points have been translated </param>
    /// <returns> Acad::ErrorStatus</returns>
    virtual Acad::ErrorStatus subMoveStretchPointsAt(const AcDbIntArray& indices, const AcGeVector3d& offset);

    /// <summary>
    /// This function should dynamically create (using the C++ new operator) whatever entity objects are appropriate to be used to replace the entity after an explode operation has taken place. 
    /// Pointers to these entities are then appended to the entitySet array. Once the pointers have been appended, the function should return with a status of Acad::eOk.
    /// </summary>
    /// <param name = "entitySet"> Input array to contain pointers to new entities; this array may already contain pointers from other entities explode() methods; 
    /// output with all entities that result from exploding this entity, appended to the array </param>
    /// <returns>Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subExplode(AcDbVoidPtrArray& entitySet) const;

    /// <summary>
    /// Function usage
    ///
    /// This function is intended to be called from AutoCAD whenever the entity is selected during the LIST command. 
    /// However, it can be called from ObjectARX applications if desired.
    ///
    /// This function will print entity specific information to the AutoCAD command line.
    ///
    /// Function implementation in derived classes
    ///
    /// When implementing this function in a derived class, the first thing that should be done in the function is to make a call to assertReadEnabled(). 
    /// The next thing to do is to call the parent class's list() method to allow the parent class to list it's information 
    /// (the parent class should in turn call its parent class first and so on up the inheritance chain until AcDbObject is reached. This way all the entity's information will be properly printed out in order). 
    /// Once the parent class's list function has been called then a series of ads_printf() calls can be used to list whatever information is desired.
    ///
    /// Default implementation
    ///
    /// Lists out the entity's DXF name, the layer, the space the entity resides in (model or paper), and the entity's handle.
    /// </summary>
    virtual void		      subList() const;

    /// <summary>
    /// This function provides a means by which AutoCAD and ObjectARX applications can ask the entity to apply a transformation matrix (xform) to itself.
    /// </summary>
    /// <param name = "xform">Input transformation matrix to be applied to the entity </param>
    virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d& xform);
    
    /// <summary>
    /// This function is intended to be overridden by derived classes that are compound objects (in other words, objects that behave like blocks in the display list).
    /// </summary>
    /// <param name = "xMat"> Output filled in with transformation matrix used for nested objects </param>
    virtual Acad::ErrorStatus subGetCompoundObjectTransform(AcGeMatrix3d & xMat) const;

    /// <summary>
    /// This function is called with a status value of kGripsToBeDeleted when the grips for the entity are about to be deleted in the host application. 
    /// This notification allows the entity to perform any required resource management tasks before the grip's AcDbGripData objects and any alternate basepoint objects pointed to by the AcDbGripData objects are deleted. 
    /// This notification may be sent more than once for a given grip edit session.
    /// If the grip edit session is not over when this notification is sent, the entity will subsequently receive a call to its getGripPoints() function to acquire new grip points to be used by the grip edit session.
    /// This function is called with a status value of kDimDataToBeDeleted whenever the dynamic dimensions for the entity are about to be deleted.
    ///This function is called with a status value of kGripsDone when the grips for the entity have been deleted in the host application and the entity is no longer involved in any grip edit operations.
    /// </summary>
    /// <param name = "status">  Value describing the status of the grip operation; one of the values from the GripStatus enumeration </param>
    /// <returns> </returns>
    virtual void subGripStatus(const AcDb::GripStat status);

    /// <summary>
    /// This function uses the AcDbFullSubentPath id to determine which subentity in the entity is desired. 
    /// It then highlights that subentity on screen. If no AcDbFullSubentPath argument is provided, then the entire entity will be highlighted.
    /// </summary>
    /// <param name = "subId">  Input AcDbFullSubentPath that identifies the subentity to highlight</param>
    /// <param name = "highlightAll">  Input Boolean indicating whether to highlight in all viewports</param>
    /// <returns>Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subHighlight(const AcDbFullSubentPath& subId = kNullSubent,
                                           const Adesk::Boolean highlightAll = false) const;

    /// <summary>
    /// This function uses the AcDbFullSubentPath id to determine which subentity in the entity is desired. 
    /// It then unhighlights that subentity on screen. If no AcDbFullSubentPath argument is provided, then the entire entity will be unhighlighted.
    /// </summary>
    /// <param name = "subId"> Input AcDbFullSubentPath that identifies which subentity to unhighlight </param>
    /// <param name = "highlightAll"> Input Boolean indicating whether to unhighlight in all viewports </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subUnhighlight(const AcDbFullSubentPath& subId = kNullSubent,
                                             const Adesk::Boolean highlightAll = false) const;

    /// <summary>
    /// Function to get the geometric extents of the asset
    /// </summary>
    /// <param name = "extents"> Geometric extents of the asset </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus   subGetGeomExtents(AcDbExtents& extents) const;

    /// <summary>
    /// It projects this entity and the pEnt entity onto the projPlane, finds the intersection points, and then projects the intersection points back onto this entity. 
    /// So, all points appended to the points array will be on this entity. The projections are done parallel to the projPlane's normal vector.
    /// </summary>
    /// <param name = "pEnt"> Input entity with which "this" entity is to intersect </param>
    /// <param name = "intType"> Input type of intersection requested; the possible AcDb::Intersect values are:
    /// AcDb::kOnBothOperands - Do not extend either entity. This results in only calculating intersections where the two entitys' geometry actually intersect 
    /// AcDb::kExtendThis - Extend this entity (if necessary) when calculating intersections, but do not extend the pEnt entity. 
    /// AcDb::kExtendArg - Extend the pEnt entity (if necessary) when calculating intersections, but do not extend this entity. 
    /// AcDb::kExtendBoth - Extend both the pEnt entity and this entity (if necessary) when calculating intersections  </param>

    /// <param name = "projPlane">  Input projection plane for the apparent intersection of the two entities </param>
    /// <param name = "thisGsMarker"> Input GS marker of subentity of "this" entity that's involved in the intersection operation. Use the 0 default if not applicable. </param>
    /// <param name = "otherGsMarker"> Input GS marker of subentity of the entity pointed to by pEnt that's involved in the intersection operation. Use the 0 default if not applicable </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subIntersectWith(const AcDbEntity* pEnt, AcDb::Intersect intType, const AcGePlane& projPlane,
                  AcGePoint3dArray& points, Adesk::GsMarker thisGsMarker = 0, Adesk::GsMarker otherGsMarker = 0) const;

    /// <summary>
    /// It finds the intersections of the entity pointed to by pEnt and all the edges of the bounding box of this entity.
    /// </summary>
    /// <param name = "pEnt"> Input entity with which "this" entity is to intersect </param>
    /// <param name = "intType"> Input type of intersection requested </param>
    /// <param name = "points">  Output with the points of intersection appended </param>
    /// <param name = "thisGsMarker"> Input GS marker of subentity of "this" entity that's involved in the intersection operation. Use the 0 default if not applicable </param>
    /// <param name = "otherGsMarker"> Input GS marker of subentity of the entity pointed to by pEnt that's involved in the intersection operation. Use the 0 default if not applicable </param>
    /// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus
    subIntersectWith(const AcDbEntity* pEnt, AcDb::Intersect intType, AcGePoint3dArray& points,
                  Adesk::GsMarker thisGsMarker = 0, Adesk::GsMarker otherGsMarker = 0) const;

    /// <summary>
    /// This function uses the AcDbSubentId object within the subPath object to determine which GS markers within the entity are appropriate. 
    /// Any GS markers that match are appended to the gsMarkers array.
    /// </summary>
    /// <param name="subPath"> Input AcDbFullSubentPath object that contains an AcDbSubentId object with the information necessary to 
    /// determine the subentity (or subentities) for which the GS Marker(s) is requested. </param>
    /// <param name="gsMarkers"> Output array with the GSMarker(s) for the subentity (or subentities) </param>
    /// <returns> </returns>
    virtual Acad::ErrorStatus subGetGsMarkersAtSubentPath(
        const AcDbFullSubentPath& subPath,
        AcArray<Adesk::GsMarker>& gsMarkers) const;

    /// <summary>
    ///
    /// </summary>
    /// <param name="type"> Input subentity type desired</param>
    /// <param name="gsMark"> Input GS marker representing a specific subentity </param>
    /// <param name="pickPoint"> Input point (in WCS coordinates) picked during selection of the entity (this point will be on or very near the desired subentity)</param>
    /// <param name="viewXform"> Input transformation matrix to transform from WCS to DCS </param>
    /// <param name="numPaths"> Output number of AcDbFullSubentPath objects in the subentPaths array</param>
    /// <param name="subentPaths"> Output address of a dynamically allocated array of one or more AcDbFullSubentPaths generated from the GS marker 
    /// and other information passed into this function</param>
    /// <param name="numInserts"> Input number of object IDs for AcDbBlockReferences in entAndInsertStack </param>
    /// <param name="entAndInsertStack"> Input array of objectIds of the objects that are the nested containers of the subentity </param>
    /// <returns> </returns>
    virtual Acad::ErrorStatus subGetSubentPathsAtGsMarker(
        AcDb::SubentType type,
        Adesk::GsMarker gsMark,
        const AcGePoint3d& pickPoint,
        const AcGeMatrix3d& viewXform,
        int& numPaths,
        AcDbFullSubentPath*& subentPaths,
        int numInserts = 0,
        AcDbObjectId* entAndInsertStack = NULL) const;

    /// <summary>
    /// Undo
    /// </summary>
    virtual Acad::ErrorStatus applyPartialUndo  (AcDbDwgFiler* undoFiler,
                                                 AcRxClass*    classObj);

protected:

    AcPpImpAsset* mpImpAsset;
} ;
