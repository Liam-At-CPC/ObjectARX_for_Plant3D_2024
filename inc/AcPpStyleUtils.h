//
// (C) Copyright 2007-2009, 2014 by Autodesk, Inc.
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

#include "AdAChar.h"
#include "PnPDllDef.h"

class AcDbDatabase;
class AcDbObjectId;
class AcPpStyle;

namespace AcPpPnIDStyleUtils
{
    /// <summary>
    /// Add the style, <paramref name="pStyle"/>, to the style
    /// dictionary in database <paramref name="pDb"/>.  The
    /// string, <paramref name="styleName"/>, is the name of
    /// the new style, and will be used as the key in the
    /// style dictionary.
    /// </summary>
    /// <param name="pStyle">The style object to add. The
    /// database object must be opened for write access.</param>
    /// <param name="styleName">The name of the style.</param>
    /// <param name="pDb">The database whose style dictionary
    /// will be modified.</param>
    /// <returns>Acad::ErrorStatus</returns>
    PNIDOBJECTS_API Acad::ErrorStatus addStyle(AcPpStyle*    pStyle,
                               const ACHAR*  styleName,
                               AcDbDatabase* pDb);

    /// <summary>
    /// Given the style name, return the styleId
    /// </summary>
    /// <param name = "styleName">Input style name string.</param>
    /// <param name = "styleId">Output style id.</param>
    /// <param name = "bAnnotationStyle">Indicates that the search is for a PnID annotation style,
    /// rather than a Graphical style.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    PNIDOBJECTS_API Acad::ErrorStatus getStyleIdFromName(const ACHAR* styleName,
                                         AcDbObjectId& styleId,
                                         bool bAnnotationStyle = false);

    /// <summary>
    /// Returns whether a DynamicAsset should be created given a style-id
    /// for the given graphical style
    /// </summary>
    /// <param name ="bDynamic">Output boolean query result.</param>
    /// <param name ="styleId">Input style id.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    PNIDOBJECTS_API Acad::ErrorStatus styleRequiresDynamicAsset(bool& bDynamic,
                                                const AcDbObjectId& styleId);
}
