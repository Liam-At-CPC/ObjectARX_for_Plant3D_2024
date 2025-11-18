//
// (C) Copyright 2007 by Autodesk, Inc.
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

// Forward declares
class AcPpLineSegment;
class AcPpImpGranularDwfManager;

/// <summary>
/// AcPpGranularDwfReactor is used to receive notifications during DWF
/// publishing regarding AcPpLineSegment decomposition.
/// </summary>
class AcPpGranularDwfReactor
{
public:

	/// <summary>
	/// Sent out when an AcPpLineSegment is about to be decomposed. 
	/// pLineSegment is opened in AcDb::kForRead mode.
	/// </summary>
	virtual void OnDecomposeBegin(AcPpLineSegment*& pLineSegment) = 0;

	/// <summary>
	/// Sent out after a temporary entity representing a part of a 
	/// sub-component is added to the drawing. pEntity is opened in 
	/// AcDb::kForWrite mode.
	/// </summary>
	virtual void OnGranularEntityAppended(AcDbEntity*& pEntity, int nSequence) = 0;

	/// <summary>
	/// Sent out the decomposition of an AcPpLineSegment is complete. 
	/// pLineSegment is opened in AcDb::kForRead mode.
	/// </summary>
	virtual void OnDecomposeEnded(AcPpLineSegment*& pLineSegment) = 0;
};

/// <summary>
/// AcPpGranularDwfManager is used to add / remove reactors into the
/// DWF publishing mechanism that decomposes AcPpLineSegment into
/// granular components.
/// </summary>
class AcPpGranularDwfManager
{
public:

	/// <summary>
	/// Add a reactor.
	/// </summary>
	virtual void addReactor(AcPpGranularDwfReactor* pReactor) = 0;

	/// <summary>
	/// Remove a reactor.
	/// </summary>
	virtual void removeReactor(AcPpGranularDwfReactor* pReactor) = 0;

	/// <summary>
	/// For internal use only.
	/// </summary>
	virtual AcPpImpGranularDwfManager* implementation() = 0;
};


