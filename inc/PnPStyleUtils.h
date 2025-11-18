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
#include "PnPDllDef.h"

class AcPpDataLinksManager;

namespace AcPpStyleUtils
{
	/// <summary>
	/// Given the style id, returns the class name that the style is associated with
	/// </summary>
	/// <param name = "idStyle">Input style id.</param>
	/// <param name = "className">Output class name of style.</param>
	/// <returns>Returns Acad::eOk if successful.</returns>
    PNPCOMMONDBX_API Acad::ErrorStatus getClassNameFromStyleId(const AcDbObjectId& idStyle, AcString& className);

    /// <summary>
    /// Given the style name, return the styleId
    /// </summary>
    /// <param name = "styleName">Input style name string.</param>
    /// <param name = "styleId">Output style id.</param>
    /// <param name = "bAnnotationStyle">Indicates the search is for an Annotation Style</param>
    /// <param name = "b3d">Indicates the search is for a 3D Annotation Style.  Only valid 
    /// when bAnnotationStyle is also true.</param>
    /// <param name = "bSynchFromCache"></param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    PNPCOMMONDBX_API Acad::ErrorStatus getStyleIdFromName(const ACHAR* styleName,
                                         AcDbObjectId& styleId,
                                         bool bAnnotationStyle = false,
                                         bool b3d = false);
	/// <summary>
    /// Returns whether or not any of the format strings in the style contain the ".Tag" field.  
    /// Client is UI code that populates a droplist in the tagging dialog for
    /// selecting annotation style to show tag info immediately.
	/// </summary>
	/// <param name ="bHasTag">Output boolean query result.</param>
    /// <param name ="styleId">Input style id.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    PNPCOMMONDBX_API Acad::ErrorStatus styleContainsTag (bool& bHasTag, AcDbObjectId styleId);

	/// <summary>
    /// Returns whether or not any of the format strings in the style contain geometrical property. Only for 3d
	/// </summary>
	/// <param name ="bHasGeometry">Output boolean query result.</param>
    /// <param name ="styleId">Input style id.</param>
    /// <param name ="className">target class name.</param>
    /// <param name ="pDlm">Where to check ISGEOMETRY attribute.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    PNPCOMMONDBX_API Acad::ErrorStatus styleContainsGeometry (bool& bHasGeometry, AcDbObjectId styleId, const ACHAR *className, AcPpDataLinksManager *pDlm);
}
