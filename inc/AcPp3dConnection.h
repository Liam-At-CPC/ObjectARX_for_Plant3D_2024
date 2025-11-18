//
// (C) Copyright 2008-2010 by Autodesk, Inc.
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

//-----------------------------------------------------------------------------
class AcPp3dImpConnection;
class AcPp3dImpPair;
class AcPpObjectId;

//-----------------------------------------------------------------------------
class PNP3DOBJECTS_API AcPp3dPair
{
public:

	// Constructors
	//
	AcPp3dPair();
	AcPp3dPair(const AcPp3dPair& from);
	AcPp3dPair(const AcDbObjectId& objId, const AcPp3dPort& port);

	// Destructor (non-virtual so do not derive from this class)
	//
	~AcPp3dPair();

	// Overloaded operators
	//
	AcPp3dPair& operator=(const AcPp3dPair& from);
	bool operator==(const AcPp3dPair& pair) const;

	// AcPp3dPair
	//
	const AcDbObjectId& objectId() const;
	void setObjectId(const AcDbObjectId& objId);

    const AcPpObjectId& PpObjectId() const;
    void setPpObjectId(const AcPpObjectId& objId);

	const AcPp3dPort& port() const;
	void setPort(const AcPp3dPort& port);

	void clear();

    // This is only true when loading in a saved pair but the 
    // partId is not available because it belongs to a drawing
    // not enlisted in the context the pair is saved to.
    // Only applicable in XREF scenarios.
    //
    bool isUnresolved() const;

    // This is true when the object and port are not represented
    // in the project database and is only applicable in an
    // AcDb context. In other words, the AcDbObjectId is available
    // but there is no AcPpObjectId.
    //
    bool isDrawingOnly() const;

    // For internal use only
    //
	AcPp3dImpPair*	imp() const;

protected:
	
	AcPp3dImpPair*	m_pImp;
};

__forceinline AcPp3dImpPair* AcPp3dPair::imp() const
{
	assert(m_pImp != NULL);
    return m_pImp;
}

PNP3DOBJECTS_API typedef AcArray2<AcPp3dPair, AcArrayObjectCopyReallocator<AcPp3dPair>> AcPp3dPairArray;

//-----------------------------------------------------------------------------
class PNP3DOBJECTS_API AcPp3dConnection
{
public:
	
	// Constructors
	//
	AcPp3dConnection();
	AcPp3dConnection(const AcPp3dConnection& from);
	AcPp3dConnection(const AcPp3dPair& pair1, const AcPp3dPair& pair2);

	// Destructor (non-virtual so do not derive from this class)
	//
	~AcPp3dConnection();

	// Overloaded operators
	//
	AcPp3dConnection& operator=(const AcPp3dConnection& from);
	bool operator==(const AcPp3dConnection& conn)const;

	// AcPp3dConnection
	//
	const AcPp3dPair& pair1() const;
	void setPair1(const AcPp3dPair& pair);

	const AcPp3dPair& pair2() const;
	void setPair2(const AcPp3dPair& pair);

	const AcDbObjectId& objectId1() const;
	void setObjectId1(const AcDbObjectId& objId);

	const AcPp3dPort& port1() const;
	void setPort1(const AcPp3dPort& port);

	const AcDbObjectId& objectId2() const;
	void setObjectId2(const AcDbObjectId& objId);

	const AcPp3dPort& port2() const;
	void setPort2(const AcPp3dPort& port);

	void clear();

    bool isExternal() const;
    bool isDrawingOnly() const;

    // For internal use only
    //
	AcPp3dImpConnection*	imp() const;

protected:
	
	AcPp3dImpConnection*	m_pImp;
};

__forceinline AcPp3dImpConnection* AcPp3dConnection::imp() const
{
	assert(m_pImp != NULL);
    return m_pImp;
}

PNP3DOBJECTS_API typedef AcArray2<AcPp3dConnection, AcArrayObjectCopyReallocator<AcPp3dConnection>> AcPp3dConnectionArray;
