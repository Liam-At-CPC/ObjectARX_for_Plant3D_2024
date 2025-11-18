//
// (C) Copyright 2008 by Autodesk, Inc.
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

namespace AcPpFormatStringUtils
{
	/// <summary>
	/// This function is used to determine if a format string is valid and can be evaluated.
	/// </summary>
	/// <param name = "pFormatString"> Format string to validate </param>
	/// <returns>bool </returns>
	PNPCOMMONDBX_API bool isValid(const ACHAR* pFormatString);

	/// <summary>
	/// This function evaluates a format string for a specific entity in the drawing.
	/// The resulting value must be freed by the caller.
	/// </summary>
	/// <param name = "pResult"> Out parameter that receives the evaluated string.</param>
	/// <param name = "pFormatStr"> Format string to evaluate.</param>
	/// <param name = "targetId"> Object to use when obtaining property values.</param>
	/// <returns>Acad::ErrorStatus </returns>
	PNPCOMMONDBX_API Acad::ErrorStatus evaluate(ACHAR*& pResult, const ACHAR* pFormatStr, const AcDbObjectId& targetId);

    /// <summary>
	/// This function evaluates a format string for a specific row in the project.
	/// The resulting value must be freed by the caller.
	/// </summary>
	/// <param name = "pResult"> Out parameter that receives the evaluated string.</param>
	/// <param name = "pFormatStr"> Format string to evaluate.</param>
	/// <param name = "rowId"> RowId to use when obtaining property values.</param>
    /// <param name = "pLm"> Data Links Manager to which rowId belongs.</param>
	/// <returns>Acad::ErrorStatus </returns>
	PNPCOMMONDBX_API Acad::ErrorStatus evaluate(ACHAR*& pResult, const ACHAR* pFormatStr, AcPpRowId rowId, AcPpDataLinksManager* pLm);
};