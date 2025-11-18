//
// $Header$
// $Change$
// $NoKeywords: $

// (C) Copyright 2013 by Autodesk, Inc. 
//
/// The information contained herein is confidential, proprietary
// to Autodesk,  Inc.,        and considered a trade secret as defined
// in section 499C of the penal code of the State of California.
// Use of  this information  by  anyone  other        than  authorized
// employees of Autodesk, Inc.        is granted  only under a written
// non-disclosure agreement,  expressly  prescribing  the  scope
// and manner of such use.
//

#pragma once
#include "AcPpDataLinks.h"
#include "PnPDllDef.h"

class AcPpOffpageConnectionManager : public AcRxObject
{
	// Default constuctor uses current data links manager
	//
public:
	/// <summary> 
	/// Default constructor 
	/// </summary>
	PNIDOBJECTS_API AcPpOffpageConnectionManager();

	/// <summary> 
	/// Default constructor 
	/// </summary>
	/// <param name="pDLM"> A reference of a pointer points to AcPpDataLinksManager instance </param>
	PNIDOBJECTS_API AcPpOffpageConnectionManager(AcPpDataLinksManager* pDLM);

	/// <summary> 
	/// Connect two OPCs 
	/// </summary>
	/// <param name="opcId1"> A reference of the first opc AcDbObjectId </param>
	/// <param name="opcId2"> A reference of the second opc AcDbObjectId </param>
	/// <returns> EPpDLStatus</returns>
	PNIDOBJECTS_API EPpDLStatus connect(const AcDbObjectId& opcId1, const AcDbObjectId& opcId2);

	/// <summary> 
	/// Connect two OPCs 
	/// </summary>
	/// <param name="opcId1"> A reference of the first opc AcPpObjectId </param>
	/// <param name="opcId2"> A reference of the second opc AcPpObjectId </param>
	/// <returns> EPpDLStatus</returns>
	PNIDOBJECTS_API EPpDLStatus connect(const AcPpObjectId& opcId1, const AcPpObjectId& opcId2);

	/// <summary> 
	/// Connect two OPCs 
	/// </summary>
	/// <param name="opcId1"> A reference of the first opc AcPpRowId </param>
	/// <param name="opcId2"> A reference of the second opc AcPpRowId </param>
	/// <returns> EPpDLStatus</returns>
	PNIDOBJECTS_API EPpDLStatus connect(const AcPpRowId& opcId1, const AcPpRowId& opcId2);

	/// <summary> 
	/// Disconnect relationship of the OPC
	/// </summary>
	/// <param name="opcId1"> A reference of the opc AcDbObjectId </param>
	/// <returns> EPpDLStatus</returns>
	PNIDOBJECTS_API EPpDLStatus disconnect(const AcDbObjectId& opcId);

	/// <summary> 
	/// Disconnect relationship of the OPC
	/// </summary>
	/// <param name="opcId1"> A reference of the opc AcPpObjectId </param>
	/// <returns> EPpDLStatus</returns>
	PNIDOBJECTS_API EPpDLStatus disconnect(const AcPpObjectId& opcId);

	/// <summary> 
	/// Disconnect relationship of the OPC
	/// </summary>
	/// <param name="opcId1"> A reference of the opc AcPpRowId </param>
	/// <returns> EPpDLStatus</returns>
	PNIDOBJECTS_API EPpDLStatus disconnect(const AcPpRowId& opcId);

	/// <summary> 
	/// Check an OPC is connected or not
	/// </summary>
	/// <param name="opcId1"> A reference of the opc AcDbObjectId </param>
	/// <param name="isCnt"> opc is connected </param>
	/// <returns> EPpDLStatus</returns>
	PNIDOBJECTS_API EPpDLStatus isConnected(const AcDbObjectId& opcId, bool& isCnt);

	/// <summary> 
	/// Check an OPC is connected or not
	/// </summary>
	/// <param name="opcId1"> A reference of the opc AcPpObjectId </param>
	/// <param name="isCnt"> opc is connected </param>
	/// <returns> EPpDLStatus</returns>
	PNIDOBJECTS_API EPpDLStatus isConnected(const AcPpObjectId& opcId, bool& isCnt);

	/// <summary> 
	/// Check an OPC is connected or not
	/// </summary>
	/// <param name="opcId1"> A reference of the opc AcPpRowId </param>
	/// <param name="isCnt"> opc is connected </param>
	/// <returns> EPpDLStatus</returns>
	PNIDOBJECTS_API EPpDLStatus isConnected(const AcPpRowId& opcId, bool& isCnt);

	/// <summary> 
	/// Get the related OPC
	/// </summary>
	/// <param name="opcId"> A reference of the opc const AcDbObjectId</param>
	/// <param name="otherId"> the output related OPC AcPpObjectId</param>
	/// <returns> EPpDLStatus</returns>
	PNIDOBJECTS_API EPpDLStatus getConnected(const AcDbObjectId& opcId, AcPpObjectId& otherId);

	/// <summary> 
	/// Get the related OPC
	/// </summary>
	/// <param name="opcId"> A reference of the opc const AcDbObjectId</param>
	/// <param name="otherId"> the output related OPC AcPpRowId</param>
	/// <returns> EPpDLStatus</returns>
	PNIDOBJECTS_API EPpDLStatus getConnected(const AcDbObjectId& opcId, AcPpRowId& otherId);

	/// <summary> 
	/// Get the related OPC
	/// </summary>
	/// <param name="opcId"> A reference of the opc const AcPpObjectId</param>
	/// <param name="otherId">the output related OPC AcPpObjectId</param>
	/// <returns> EPpDLStatus</returns>
	PNIDOBJECTS_API EPpDLStatus getConnected(const AcPpObjectId& opcId, AcPpObjectId& otherId);

	/// <summary> 
	/// Get the related OPC
	/// </summary>
	/// <param name="opcId"> A reference of the opc const AcPpObjectId</param>
	/// <param name="otherId"> the output related OPC AcPpRowId</param>
	/// <returns> EPpDLStatus</returns>
	PNIDOBJECTS_API EPpDLStatus getConnected(const AcPpObjectId& opcId, AcPpRowId& otherId);

	/// <summary> 
	/// Get the related OPC
	/// </summary>
	/// <param name="opcId"> A reference of the opc const AcPpRowId</param>
	/// <param name="otherId"> the output related OPC AcPpObjectId</param>
	/// <returns> EPpDLStatus</returns>
	PNIDOBJECTS_API EPpDLStatus getConnected(const AcPpRowId& opcId, AcPpObjectId& otherId);

	/// <summary> 
	/// Get the related OPC
	/// </summary>
	/// <param name="opcId"> A reference of the opc const AcPpRowId</param>
	/// <param name="otherId"> the output related OPC AcPpObjectId</param>
	/// <returns> EPpDLStatus</returns>
	PNIDOBJECTS_API EPpDLStatus getConnected(const AcPpRowId& opcId, AcPpRowId& otherId);

private:
	AcPpDataLinksManager* m_pDLM;
};

