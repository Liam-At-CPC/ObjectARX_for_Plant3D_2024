//
// (C) Copyright 2007-2008 by Autodesk, Inc.
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

namespace AcPpProjectSymbolStyleUtils
{
    /// <summary>
    /// Copy the specified style from the source database to the destination database.
    /// </summary>
    /// <param name ="strStyleName">Input style name string.</param>
    /// <param name ="sourceDb">Input source (drawing) database.</param>
    /// <param name ="sourceDb">Input destination (drawing) database.</param>
    /// <param name ="sourceDb">Output id of duplicated style.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    PNIDOBJECTS_API Acad::ErrorStatus copyStyle(const ACHAR* strStyleName,
                                AcDbDatabase*& sourceDb, 
                                AcDbDatabase*& destDb,
                                AcDbObjectId& newStyleId); 
    PNIDOBJECTS_API Acad::ErrorStatus copyStyle(const ACHAR* strStyleName,
        bool bAnnotationStyle,
        AcDbDatabase* sourceDb,
        AcDbDatabase* destDb,
        AcDbObjectId& newStyleId);

    /// <summary>
    /// Copy the specified block from the source database to the destination database.
    /// </summary>
    /// <param name ="strStyleName">Input block name string.</param>
    /// <param name ="sourceDb">Input source (drawing) database.</param>
    /// <param name ="sourceDb">Input destination (drawing) database.</param>
    /// <param name ="sourceDb">Output id of duplicated block.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    PNIDOBJECTS_API Acad::ErrorStatus copyBlock(const ACHAR* strBlockName,
                                AcDbDatabase*& sourceDb, 
                                AcDbDatabase*& destDb, 
                                AcDbObjectId& newBlockId);

}
