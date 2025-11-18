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
#include "AcPpAnnotation.h"
#include "PnPDllDef.h"

class AcPpPnIDImpAnnotation;

/// <summary>
/// A utility class for querying and modifying PnID annotations.
/// </summary>
/// <remarks>
/// An AcPpAnnotation instance needs to be initialized by a call to 'initialize()', 
/// or with a call to one of the 'create' methods before use.
///
/// If the (block-definition) attributes of a style-based annotation have been modified
/// since its initialization, a reinitialization is necessary for the format-string methods
/// to be cognizant of the latest changes.
/// </remarks>
class AcPpPnIDAnnotation : public AcPpAnnotation
{
public:
    PNIDOBJECTS_API ACRX_DECLARE_MEMBERS(AcPpPnIDAnnotation);

    /// <summary>
    /// Constructor. 
    /// </summary>
    /// <remarks>
    /// A null annotation id is acceptable in the case the user wants to 
    /// create a new annotation or use setObjectId().
    /// </remarks>
    /// <param name="annotationId">Input annotation id; defaults to null.</param>
    PNIDOBJECTS_API AcPpPnIDAnnotation(const AcDbObjectId& annotationId = AcDbObjectId::kNull);

    /// <summary>
    /// Destructor. 
    /// </summary>
    PNIDOBJECTS_API virtual ~AcPpPnIDAnnotation();


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
    PNIDOBJECTS_API virtual Acad::ErrorStatus create(const AcGePoint3d& position,
                             const AcDbObjectId& styleId,
                             const AcDbObjectId& targetId,
                             const AcDbObjectId& spaceId = AcDbObjectId::kNull,
                             bool bIgnoreAutoInsertOffset = false,
                             bool bRetainMinWidths = false);

    /// <summary>
    /// Refresh this annotation.
    /// </summary>
    /// <returns>Returns Acad::eOk if successful.</returns>    
    PNIDOBJECTS_API virtual Acad::ErrorStatus refresh();

private:
    AcPpPnIDImpAnnotation* implementation();

};
