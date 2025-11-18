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
#include "PnPDllDef.h"

namespace AcPpAnnotationUtils
{

    /// <summary>
    /// Causes the simple or compound annotation to:
    /// Re-evaluate any string values against the associated target
    /// If Linked and bRePosition, reposition itself with 
    ///   respect to the target.  Caller can optionally forgo any
    ///   positional change (e.g. if they know in advance it is
    ///   not required) by passing bRePosition false).
    /// </summary>
    /// <param name="annotId">Input id of annotation to refresh.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    PNPCOMMONDBX_API Acad::ErrorStatus refresh(const AcDbObjectId& annotId);

    /// <summary>
    /// Tests if the specified entity is being used as a PnID Annotation.
    /// </summary>
    /// <param name="pEnt">Input pointer to entity.</param>
    /// <returns>Returns true if specified entity is a PnID Annotation.</returns>
    PNPCOMMONDBX_API bool isAnnotation(AcDbEntity* pEnt);

    /// <summary>
    /// Tests if the specified entity is being used as a PnID Annotation.
    /// </summary>
    /// <param name="entId">Input id of entity.</param>
    /// <returns>Returns true if specified entity is a PnID Annotation.</returns>
    PNPCOMMONDBX_API bool isAnnotation(const AcDbObjectId& entId);
}
