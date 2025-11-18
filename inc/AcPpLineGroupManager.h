//
// $Header$
// $Change$
// $NoKeywords: $

// (C) Copyright 2007-2011 by Autodesk, Inc.
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
// DESCRIPTION: 


#pragma once

#include "dbmain.h"
#include "dbobjptr.h"
#include "AcString.h"
#include "AcPpDataLinks.h"
#include "PnPDllDef.h"

class PNIDOBJECTS_API AcPpLineGroupManager : public AcRxObject
{
public:
	ACRX_DECLARE_MEMBERS(AcPpLineGroupManager);

	enum GroupType   
	{      
		kPipeLineGroup = 0,
		kSignalLineGroup = 1 
	};  

	/// <summary> 
	/// Default constructor 
	/// </summary>
	AcPpLineGroupManager();

	/// <summary> 
	/// Constructor for AcPpLineGroupManager. 
	/// Pointer to the const current data links manager is supplied.
	/// </summary>
	/// <param name="pDLM"> A reference of a pointer points to a const AcPpDataLinksManager instance </param>
	AcPpLineGroupManager(AcPpDataLinksManager* pDLM);
	
	// Create a line group   
	//
	/// <summary>
    /// Creates a group row in the pnpdatabase 
    /// </summary>
	/// <param name= "type"> the group type of the to-be created group: pipe line group or signal line group </param>
	/// <param name= "groupId"> the group row id of the created group</param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus create(const GroupType& type, AcPpRowId& groupId);

	/// <summary>
    /// Creates a group row in the pnpdatabase 
    /// </summary>
	/// <param name= "strClassName"> the class name of the to-be created line group: pipelinegroup or signallinegroup </param>
	/// <param name= "groupId"> the group row id of the created group</param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus create(const AcString& strClassName, AcPpRowId& groupId);
	
	// Get group’s type   
	// 
	/// <summary>
    /// Get the group type from the group row id
    /// </summary>
	/// <param name= "groupId"> the group row id of the line group </param>
	/// <param name= "type"> the output group type</param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus type(const AcPpRowId& groupId, GroupType& type);

	/// <summary>
    /// Get the group type from the sline Id
    /// </summary>
	/// <param name= "lineId"> the acdb object id of the sline </param>
	/// <param name= "type"> the output group type</param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus type(const AcDbObjectId& lineId, GroupType& type);  
	
	// Get group’s class name
	//
	/// <summary>
    /// Get the class name from the group row id
    /// </summary>
	/// <param name= "groupId"> the group row id of the line group </param>
	/// <param name= "strClassName"> the class name of the line </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus className(const AcPpRowId& groupId, AcString& strClassName);

	/// <summary>
    /// Get the group row id(AcPpRowId) from a sline
    /// </summary>
	/// <param name= "slGroupId"> the output group row id  </param>
	/// <param name= "lineId"> the object id of the line in the acdb database</param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus groupId(const AcDbObjectId& lineId, AcPpRowId& slGroupId);

	/// <summary>
    /// Get the group row id(AcPpRowId) from a sline
    /// </summary>
	/// <param name= "slGroupId"> the output group row id  </param>
	/// <param name= "lineId"> the AcPpObjectId of the sline</param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus groupId(const AcPpObjectId& lineId, AcPpRowId& slGroupId);

	/// <summary>
    /// Get the group row id(AcPpRowId) from a sline
    /// </summary>
	/// <param name= "slGroupId"> the output group row id  </param>
	/// <param name= "lineId"> the row id of the sline</param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus groupId(const AcPpRowId& lineId, AcPpRowId& slGroupId);
	
	// Check to see if a line already belongs to a group
	//
	/// <summary>
    /// Check whether a sline belongs to a group
    /// </summary>
	/// <param name= "groupId"> the group row id of the group </param>
	/// <param name= "lineId"> the object id of the line in the acdb database </param>
	/// <param name= "result"> 
	/// Output boolean value to indicate whether a group contains the sline 
	/// </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus has(const AcPpRowId& groupId, const AcDbObjectId& lineId, bool& result);

	/// <summary>
    /// Check whether a sline belongs to a group
    /// </summary>
	/// <param name= "groupId"> the group row id of the group </param>
	/// <param name= "lineId"> the acpp object id of the line</param>
	/// <param name= "result"> 
	/// Output boolean value to indicate whether a group contains the sline 
	/// </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus has(const AcPpRowId& groupId, const AcPpObjectId& lineId, bool& result);

	/// <summary>
    /// Check whether a sline belongs to a group
    /// </summary>
	/// <param name= "groupId"> the group row id of the group </param>
	/// <param name= "lineId"> the row id of the line in the pnpdatabase</param>
	/// <param name= "result"> 
	/// Output boolean value to indicate whether a group contains the sline 
	/// </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus has(const AcPpRowId& groupId, const AcPpRowId& lineId, bool& result);

	/// <summary>
	/// Get the sline count in the group, only when count > 2, then the 
    /// group can have the ungroup operation.
    /// </summary>
	/// <param name= "groupId"> the group row id  </param>
	/// <param name= "result"> the sline number in the group</param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus count(const AcPpRowId& groupId, int& result);

	/// <summary>
    /// Merge the two groups together
	///
	/// the slines in the source group will be removed from the source group,
	/// then the source group row will be deleted, and then the slines in the
	/// source group previously will be added to the target group.
	///
    /// </summary>
	/// <param name= "dwgId">The dwg Id</param>
	/// <param name= "targetGroupRowId">the target(seed) id for propagation</param>
	/// <param name= "sourceGroupRowId">the source group id</param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus merge(long dwgId, AcPpRowId& targetGroupRowId, AcPpRowId& sourceGroupRowId);

	/// <summary>
    /// Get all the groups ids
	///
	/// Get all the line group row ids from the group table(PipeLineGroup/SignalLineGroup)
	///
    /// </summary>
	/// <param name= "type"> the group type  </param>
	/// <param name= "groupId"> the output group row ids  </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus groupIds(const GroupType& type, AcPpRowIdArray& groupRowIds);

	/// <summary>
    /// Get the names of all group tags.
    /// </summary>
    /// <param name="groupId">Input the type of the group row id</param>
	/// <param name="tagList">Output AcArray of group tag names</param>
    /// <returns>Returns ePpDLOk if successful.</returns>
    EPpDLStatus  tags(const AcPpRowId& groupId, AcStringArray &tagList);

	/// <summary>
    /// Get the names of all group services.
    /// </summary>
	/// <param name="type">Input the type of the group row id</param>
    /// <param name="tagList">Output AcArray of group service names</param>
    /// <returns>Returns ePpDLOk if successful.</returns>
    EPpDLStatus  services(const AcPpRowId& groupId, AcStringArray &serviceList);
	
	/// <summary>
    /// Add a SLINE to a group   
    /// </summary>
	/// <param name= "groupId"> the group Id  </param>
	/// <param name= "lineId"> the AcDbObjectId of the sline </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus add(const AcPpRowId& groupId, const AcDbObjectId& lineId);

	/// <summary>
    /// Add a SLINE to a group   
    /// </summary>
	/// <param name= "groupId"> the group Id  </param>
	/// <param name= "lineId"> the AcPpObjectId of the sline </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus add(const AcPpRowId& groupId, const AcPpObjectId& lineId);

	/// <summary>
    /// Add a SLINE to a group   
    /// </summary>
	/// <param name= "groupId"> the group Id  </param>
	/// <param name= "lineId"> the AcPpRowId of the sline </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus add(const AcPpRowId& groupId, const AcPpRowId& lineId);    
	
	/// <summary>
    /// Remove a SLINE from a group     
    /// </summary>
	/// <param name= "groupId"> the group Id  </param>
	/// <param name= "lineId"> the AcDbObjectId of the sline </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus remove(const AcPpRowId& groupId, const AcDbObjectId& lineId);

	/// <summary>
    /// Remove a SLINE from a group     
    /// </summary>
	/// <param name= "groupId"> the group Id  </param>
	/// <param name= "lineId"> the AcPpObjectId of the sline </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus remove(const AcPpRowId& groupId, const AcPpObjectId& lineId);

	/// <summary>
    /// Remove a SLINE from a group     
    /// </summary>
	/// <param name= "groupId"> the group Id  </param>
	/// <param name= "lineId"> the AcPpRowId of the sline </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus remove(const AcPpRowId& groupId, const AcPpRowId& lineId);

	/// <summary>
    /// Set/change to a group of an SLINE from a group
	/// If the SLINE already has a group assigned the group is removed first
    /// </summary>
	/// <param name= "groupId"> the new group Id  </param>
	/// <param name= "lineId"> the AcPpRowId of the sline </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus set(const AcPpRowId& groupId, const AcDbObjectId& lineId);

	/// <summary>
    /// Set/change to a group of an SLINE from a group
	/// If the SLINE already has a group assigned the group is removed first
    /// </summary>
	/// <param name= "groupId"> the new group Id  </param>
	/// <param name= "lineId"> the AcPpRowId of the sline </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus set(const AcPpRowId& groupId, const AcPpObjectId& lineId);

	/// <summary>
    /// Set/change to a group of an SLINE from a group
	/// If the SLINE already has a group assigned the group is removed first
    /// </summary>
	/// <param name= "groupId"> the new group Id  </param>
	/// <param name= "lineId"> the AcPpRowId of the sline </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus set(const AcPpRowId& groupId, const AcPpRowId& lineId);
	
	/// <summary>
    /// Get the list of SLINEs in group      
    /// </summary>
	/// <param name= "groupId"> the group Id  </param>
	/// <param name= "lineIds"> the output list of AcDbObjectId slines </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus lineIds(const AcPpRowId& groupId, AcDbObjectIdArray& lineIds);

	/// <summary>
    /// Get the list of SLINEs in group      
    /// </summary>
	/// <param name= "groupId"> the group Id  </param>
	/// <param name= "lineIds"> the output list of AcPpObjectId slines </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus lineIds(const AcPpRowId& groupId, AcPpObjectIdArray& lineIds);

	/// <summary>
    /// Get the list of SLINEs in group      
    /// </summary>
	/// <param name= "groupId"> the group Id  </param>
	/// <param name= "lineIds"> the output list of AcPpRowId slines </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus lineIds(const AcPpRowId& groupId, AcPpRowIdArray& lineIds);
	
	/// <summary>
    /// get the service of a group        
    /// </summary>
	/// <param name= "groupId"> the group Id  </param>
	/// <param name= "strService"> the output value of the service column </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus service(const AcPpRowId& groupId, AcString& strService);

	/// <summary>
    /// set the service of a group        
    /// </summary>
	/// <param name= "groupId"> the group Id  </param>
	/// <param name= "strService"> the value of the service column you want to set </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus setService(const AcPpRowId&  groupId, const AcString& strService);
	
	/// <summary>
    /// get the line number of a group      
    /// </summary>
	/// <param name= "groupId"> the group Id  </param>
	/// <param name= "strService"> the output value of the linenumber column </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus lineNumber(const AcPpRowId& groupId, AcString& strLineNumber);

	/// <summary>
    /// set the line number of the group      
    /// </summary>
	/// <param name= "groupId"> the group Id  </param>
	/// <param name= "strService"> the value of the linenumber column you want to set </param>
	/// <returns> EPpDLStatus</returns>
	EPpDLStatus setLineNumber(const AcPpRowId& groupId, const AcString& strLineNumber);
	
private:
	AcPpDataLinksManager* m_pLM;
};
