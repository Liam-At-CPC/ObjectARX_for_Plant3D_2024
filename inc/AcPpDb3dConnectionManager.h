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

//-----------------------------------------------------------------------------
#include "AcPp3dPort.h"
#include "AcPp3dConnection.h"
#include "PnPDllDef.h"

//-----------------------------------------------------------------------------
class AcPpDb3dImpConnectionManager;
class AcPpDb3dPart;

/// <summary>
/// This class is used to organize connection related functionality. It is usable
/// to connect or disconnect objects in the drawing or to query current connection
/// state. Any connectivity changes made through this class are applied to the
/// object models in the drawing file and propagated to the model in the data-cache.
/// </summary>
///
class PNP3DOBJECTS_API AcPpDb3dConnectionManager
{
public:

	AcPpDb3dConnectionManager();
	virtual ~AcPpDb3dConnectionManager();

    /// <summary>
    /// This function is used to determine if two drawing objects can be connected.
    /// </summary>
    /// <param name="pair1">First piping object id and port.</param>
    /// <param name="pair2">Second piping object id and port.</param>
    /// <param name="bCanConnect">Reference to boolean that indicates if a connection is possible.</param>
    /// <returns>Acad:ErrorStatus used to determine if the function succeeded or not.</returns>
    ///
	virtual Acad::ErrorStatus	canConnect(const AcPp3dPair& pair1,
										   const AcPp3dPair& pair2,
										   /*[out]*/ bool& bCanConnect) const;

    /// <summary>
    /// This function is used to connect two drawing objects.
    /// </summary>
    /// <param name="pair1">First piping object id and port.</param>
    /// <param name="pair2">Second piping object id and port.</param>
    /// <returns>Acad:ErrorStatus used to determine if the function succeeded or not.</returns>
    ///
	virtual Acad::ErrorStatus	connect(const AcPp3dPair& pair1,
										const AcPp3dPair& pair2) const;

    /// <summary>
    /// This function is used to disconnect two drawing objects.
    /// </summary>
    /// <param name="pair1">First piping object id and port.</param>
    /// <param name="pair2">Second piping object id and port</param>
    /// <returns>Acad:ErrorStatus used to determine if the function succeeded or not.</returns>
    /// <remarks>
    ///
	virtual Acad::ErrorStatus	disconnect(const AcDbObjectId& part1ObjId, 
										   const AcDbObjectId& part2ObjId) const;

    /// <summary>
    /// This function is used to determine if an object is connected atleast once.
    /// </summary>
    /// <param name="objId">Piping object id to check.</param>
    /// <param name="bIsConnected">Reference to a bool that is assigned.</param>
    /// <returns>Acad:ErrorStatus used to determine if the function succeeded or not.</returns>
    ///
	virtual Acad::ErrorStatus	isConnected(const AcDbObjectId& objId, 
											/*[out]*/ bool& bIsConnected) const; 

    /// <summary>
    /// This function is used to determine if an object is connected atleast once.
    /// </summary>
    /// <param name="pPart">Piping object pointer to check.</param>
    /// <param name="bIsConnected">Reference to a bool that is assigned.</param>
    /// <returns>Acad:ErrorStatus used to determine if the function succeeded or not.</returns>
    ///
	virtual Acad::ErrorStatus	isConnected(AcPpDb3dPart* pPart, 
											/*[out]*/ bool& bIsConnected) const; 

    /// <summary>
    /// This function is used to determine if an object is connected on a specific port.
    /// </summary>
    /// <param name="pair">Piping object id and port to check.</param>
    /// <param name="bIsConnected">Reference to a bool that is assigned.</param>
    /// <returns>Acad:ErrorStatus used to determine if the function succeeded or not.</returns>
    ///
	virtual Acad::ErrorStatus	isConnected(const AcPp3dPair& pair, 
											/*[out]*/ bool& bIsConnected) const; 

    /// <summary>
    /// This function is used to obtain the piping object and specific port connected to
    /// the specified piping object and port.
    /// </summary>
    /// <param name="pair">Piping object id and port to check.</param>
    /// <param name="connectedPair">Reference to piping object and port to assign.</param>
    /// <returns>Acad:ErrorStatus used to determine if the function succeeded or not.</returns>
    ///
	virtual Acad::ErrorStatus	getConnectedPairAt(const AcPp3dPair& pair,
											       /*[out]*/ AcPp3dPair& connectedPair) const;

    /// <summary>
    /// This function is used to obtain the connections of piping object.
    /// </summary>
    /// <param name="objId">Piping object id to check.</param>
    /// <param name="connections">Reference to array of connection to fill.</param>
    /// <returns>Acad:ErrorStatus used to determine if the function succeeded or not.</returns>
    ///
	virtual Acad::ErrorStatus	getConnections(const AcDbObjectId& objId, 
											   /*[out]*/ AcPp3dConnectionArray& connections) const;

    /// <summary>
    /// This function is used to obtain the connections of piping object.
    /// </summary>
    /// <param name="pPart">Piping object pointer to check.</param>
    /// <param name="connections">Reference to array of connection to fill.</param>
    /// <returns>Acad:ErrorStatus used to determine if the function succeeded or not.</returns>
    ///
	virtual Acad::ErrorStatus	getConnections(AcPpDb3dPart* pPart, 
								 		       /*[out]*/ AcPp3dConnectionArray& connections) const;

protected:
	
	AcPpDb3dImpConnectionManager*	imp() const;
	AcPpDb3dImpConnectionManager*	m_pImp;
};

__forceinline AcPpDb3dImpConnectionManager* AcPpDb3dConnectionManager::imp() const
{
	assert(m_pImp != NULL);
    return static_cast<AcPpDb3dImpConnectionManager *>(m_pImp);
}
