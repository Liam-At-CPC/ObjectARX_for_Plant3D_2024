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

#include "dbapserv.h"
#include "PnPDllDef.h"

namespace AcPpDictionaryUtils
{

    /// <summary>
    /// Get the P&ID root dictionary of the specified database. 
    /// </summary>
    /// <param name ="pDb">Input pointer to (drawing) database.</param>
    /// <param name ="pDict">Output pointer to requested dictionary.</param>
    /// <param name ="nMode">Input Open mode; for read or write.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    PNPCOMMONDBX_API Acad::ErrorStatus getRootDictionary(AcDbDatabase*& pDb,
                                        AcDbDictionary*& pDict, 
                                        AcDb::OpenMode nMode); 

    /// <summary>
    /// Get the style dictionary of the specified database.
    /// </summary>
    /// <param name ="pDb">Input pointer (drawing) database.</param>
    /// <param name ="pDict">Output pointer to requested dictionary.</param>
    /// <param name ="nMode">Input Open mode; for read or write.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    PNPCOMMONDBX_API Acad::ErrorStatus getStylesDictionary(AcDbDatabase*& pDb,
										 AcDbDictionary*& pDict, 
                                         AcDb::OpenMode nMode); 

    /// <summary>
    /// Get the annotation style dictionary of the specified database.
    /// </summary>
    /// <param name ="pDb">Input pointer (drawing) database.</param>
    /// <param name ="pDict">Output pointer to requested dictionary.</param>
    /// <param name ="nMode">Input Open mode; for read or write.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    PNPCOMMONDBX_API Acad::ErrorStatus getAnnotationStylesDictionary(AcDbDatabase*& pDb,
													AcDbDictionary*& pDict, 
													AcDb::OpenMode nMode); 

    /// <summary>
    /// Get the 3d annotation style dictionary of the specified database.
    /// </summary>
    /// <param name ="pDb">Input pointer (drawing) database.</param>
    /// <param name ="pDict">Output pointer to requested dictionary.</param>
    /// <param name ="nMode">Input Open mode; for read or write.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    PNPCOMMONDBX_API Acad::ErrorStatus get3dAnnotationStylesDictionary(AcDbDatabase*& pDb,
													AcDbDictionary*& pDict, 
													AcDb::OpenMode nMode); 

}
