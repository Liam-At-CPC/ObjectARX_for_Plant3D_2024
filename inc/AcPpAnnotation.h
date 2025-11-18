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

#pragma once

#include "dbid.h"
#include "dbmain.h"
#include "acstring.h"

#include <map>

#include "AcPpDataLinks.h"
#include "PnPStyles.h"

class AcPpImpAnnotation;

/// <summary>
/// A base utility class for querying and modifying Plant annotations.
/// </summary>
/// <remarks>
/// An AcPpAnnotation instance needs to be initialized by a call to 'initialize()', 
/// or with a call to one of the 'create' methods before using any of the 
/// formatString methods.  
///
/// In general, prefer instantiating one of the derived classes rather than the
/// base class for most behavior, or utilize AcPpAnnotationUtils to exercise
/// Annotation behavior in a part-agnostic way.
///
/// If the (block-definition) attributes of a style-based annotation have been modified
/// since its initialization, a reinitialization is necessary for the format-string methods
/// to be cognizant of the latest changes.
/// </remarks>
class PNPCOMMONDBX_API AcPpAnnotation : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcPpAnnotation);

    /// <summary>
    /// Constructor. 
    /// </summary>
    /// <remarks>
    /// A null annotation id is acceptable in the case the user wants to 
    /// create a new annotation or use setObjectId().
    /// </remarks>
    /// <param name="annotationId">Input annotation id; defaults to null.</param>
    AcPpAnnotation(const AcDbObjectId& annotationId = AcDbObjectId::kNull);

    /// <summary>
    /// Destructor. 
    /// </summary>
    virtual ~AcPpAnnotation();

    /// <summary>
    /// Check if the annotation object id specified in the constructor or setObjectId()
    /// belongs to a valid PnID annotation.
    /// </summary>
    /// <remarks>
    /// This method does not need to be called if create() or createSimple() is to be used.
    /// </remarks>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus initialize();

    /// <summary>
    /// Create an annotation style based annotation.
    /// </summary>
    /// <param name="position">Input position of annotation.</param>
    /// <param name="styleId">Input id of annotation style.</param>
    /// <param name="targetId">Input id of annotation target.</param>
    /// <param name="spaceId">Input id of space (e.g. model or paper) to create annotation in; defaults to target's space.</param>
    /// <param name="bIgnoreAutoInsertOffset">Input - if true, uses position and ignores Auto-Insert offest values.</param>
    /// <param name="bRetainMinWidths">Input - if true, annotation graphics retain their original width when text shrinks.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    virtual Acad::ErrorStatus create(const AcGePoint3d& position, 
                             const AcDbObjectId& styleId,
                             const AcDbObjectId& targetId,
                             const AcDbObjectId& spaceId = AcDbObjectId::kNull,
                             bool bIgnoreAutoInsertOffset = false,
                             bool bRetainMinWidths = false);

    /// <summary>
    /// Create a simple, free-standing annotation.
    /// </summary>
    /// <param name="position">Input position of annotation.</param>
    /// <param name="dblRotation">Input rotation angle of annotation.</param>
    /// <param name="pFormattedField">Input pre-formatted field string.</param>
    /// <param name="targetId">Input id of annotation target.</param>
    /// <param name="spaceId">Input id of space (e.g. model or paper) to create annotation in; defaults to target's space.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus createSimple(const AcGePoint3d& position, 
                                   double dblRotation,
                                   const ACHAR* pFormattedField,
                                   const AcDbObjectId& targetId,
                                   const AcDbObjectId& spaceId = AcDbObjectId::kNull);

    /// <summary>
    /// Get the object id of this annotation.
    /// </summary>
    /// <returns></returns>
    AcDbObjectId objectId() const;

    /// <summary>
    /// Set the object id of this annotation.
    /// </summary>
    /// <remarks>
    /// Equivalent to constructor + initialize() call and can be used to switch 
    /// to another annotation or if kNull is initially passed in to the constructor.
    /// </remarks>
    /// <param name="annotId">Input annotation id.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setObjectId(const AcDbObjectId& annotId);

    /// <summary>
    /// Get the object id of this annotation's target.
    /// </summary>
    /// <returns></returns>
    AcDbObjectId      targetId() const;

    /// <summary>
    /// Set the object id of this annotation's target.
    /// </summary>
    /// <param name="targetId">Input annotation target id.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setTargetId(const AcDbObjectId& targetId);

    /// <summary>
    /// Get the data cache id of this annotation.
    /// </summary>
    /// <returns></returns>
    AcPpRowId cacheId() const;

    /// <summary>
    /// Get the data cache id of this annotation's target.
    /// </summary>
    /// <returns></returns>
    AcPpRowId targetCacheId() const;

    /// <summary>
    /// Get the offset of this annotation’s position to the target’s position.
    /// </summary>
    /// <returns></returns>
    AcGePoint2d       offset() const;

    /// <summary>
    /// Set the offset of this annotation’s position to the target’s position.
    /// </summary>
    /// <param name="offset">Input annotation offset.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setOffset(const AcGePoint2d& offset);

    /// <summary>
    /// Check if this is a free-standing annotation.
    /// </summary>
    /// <returns></returns>
    bool              isFreeStanding() const;

    /// <summary>
    /// Set if this is a free-standing annotation.
    /// </summary>
    /// <param name="bFreeStanding">Input free-standing annotation flag.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setIsFreeStanding(bool bFreeStanding);

    /// <summary>
    /// Check the orientation of this annotation.
    /// </summary>
    /// <returns></returns>
    AcPpAnnotationStyle::OrientationOptions orientation() const;

    /// <summary>
    /// Set the orientation of this annotation.
    /// </summary>
    /// <param name="bFreeStanding">Input free-standing annotation flag.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setOrientation(AcPpAnnotationStyle::OrientationOptions o);

    /// <summary>
    /// Get the style object id of this (style-based) annotation.
    /// </summary>
    /// <returns>Returns AcDbObject::kNull if this is not a style-based annotation.</returns>
    AcDbObjectId      styleId() const;

    /// <summary>
    /// Set the style object id of this (style-based) annotation and rebuilds its block reference.
    /// </summary>
    /// <remarks>
    /// Annotation style id is only valid with “compound” annotations and 
    /// calling this method on a simple annotation will return an error status.
    /// </remarks>
    /// <param name="styleId">Input annotation style object id.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setStyleId(const AcDbObjectId& styleId);

    /// <summary>
    /// Get the number of format strings in this annotation.
    /// </summary>
    /// <returns>Returns -1 on error.</returns>
    int numFormatStrings() const;

    /// <summary>
    /// Get the format string at the specified index.
    /// </summary>
    /// <param name="nIndex">Input index.</param>
    /// <returns>Returns NULL on error.</returns>
    const ACHAR*      formatString(int nIndex) const;

    /// <summary>
    /// Set the format string at the specified index.
    /// </summary>
    /// <param name="nIndex">Input index.</param>
    /// <param name="pFormat">Input new format string.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setFormatString(int nIndex, const ACHAR* pFormat);

    /// <summary>
    /// Get the pre-processed format string at the specified index.
    /// </summary>
    /// <remarks>
    /// Pre-processed format strings are used for auto-generated variables.
    /// </remarks>
    /// <param name="nIndex">Input index.</param>
    /// <returns>Returns NULL on error.</returns>
    const ACHAR*      preProcFormatString(int nIndex) const;

    /// <summary>
    /// Set the pre-processed format string at the specified index.
    /// </summary>
    /// <remarks>
    /// Pre-processed format strings are used for auto-generated variables.
    /// </remarks>
    /// <param name="nIndex">Input index.</param>
    /// <param name="pPreProcFormat">Input new pre-processed format string.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setPreProcFormatString(int nIndex, const ACHAR* pPreProcFormat);

    /// <summary>
    /// Get the retain-minimum-width boolean flag.
    /// </summary>
    /// <returns></returns>
    bool              retainMinWidths() const;

    /// <summary>
    /// Set the retain-minimum-width boolean flag.
    /// </summary>
    /// <param name="bRetain">Input boolean flag value.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setRetainMinWidths(bool bRetain);

    /// <summary>
    /// Transform this annotation and perform any necessary leader work.
    /// </summary>
    /// <param name="xform">Input transformation matrix.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>    
    Acad::ErrorStatus transformBy(const AcGeMatrix3d& xform);

    /// <summary>
    /// Get the visibility of this annotation.
    /// </summary>
    /// <returns></returns>
    AcDb::Visibility visibility() const;

    /// <summary>
    /// Set the visibility of this annotation.
    /// </summary>
    /// <param name="nVisibility">Input visibility value.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setVisibility(AcDb::Visibility nVisibility);

    /// <summary>
    /// Get the leaders attached to this annotation.
    /// </summary>
    /// <param name="leaderIds">Output leader object id array.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus getLeaders(AcDbObjectIdArray& leaderIds);

    /// <summary>
    /// Refresh this annotation.
    /// </summary>
    /// <returns>Returns Acad::eOk if successful.</returns>    
    virtual Acad::ErrorStatus refresh();

protected:
    /// <summary>
	/// Constructor
	/// </summary>
    /// <param name="annotationId">Input annotation id; defaults to null.</param>
	/// <param name = "bImpDone"> Boolean parameter. Pass it as true if the imp object is already created. </param>
	/// <exception cref=""> None </exception>
	/// <returns> None </returns>
    AcPpAnnotation(bool bImpDone, const AcDbObjectId& annotationId = AcDbObjectId::kNull);

    /// <summary>
    /// Object id of this annotation (instance).
    /// </summary>
    AcDbObjectId m_annotId;

private:
    bool m_bInitialized;
    std::map<int, AcDbObjectId> m_indexAttribMap;

protected:
    AcPpImpAnnotation* m_pImpAnnotation;

};
