//
// (C) Copyright 2007-2010 by Autodesk, Inc.
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

#include "AcString.h"
#include "gevec3d.h"
#include "gepnt3d.h"
#include "acarray.h"
#include "AcPp3dSpecPort.h"
#include "PnPDllDef.h"

class AcDbDwgFiler;
class AcDbDxfFiler;
class AcGeMatrix3d;
class AcGiCommonDraw;
class AcPp3dImpPort;

class PNP3DOBJECTS_API AcPp3dPort sealed
{
public:

    // Constuctor/destructor
    //
                             AcPp3dPort         ();
                             AcPp3dPort         (const AcPp3dPort &src);
    AcPp3dPort &             operator =         (const AcPp3dPort &src);
                             ~AcPp3dPort        ();

	// Overloaded operators
	//
	bool operator==	(const AcPp3dPort &port) const;
	bool operator!=	(const AcPp3dPort &port) const;
    
    // AcDbObject/AcDbEntity
    //

    /// <summary>
    /// This function transforms the port's position and direction.
    /// </summary>
    /// <param name="xform">Input transformation matrix.</param>
    /// <returns>Acad::ErrorStatus that indicates success or failure.</returns>
    ///
    Acad::ErrorStatus       transformBy         (const AcGeMatrix3d& xform);
    
    /// <summary>
    /// This function retrieves the port's name.
    /// </summary>
    /// <returns>Constant pointer to the port's name.</returns>
    ///
    const ACHAR *           getName             () const;

    /// <summary>
    /// This function is used to set the port's name.
    /// </summary>
    /// <param name="pName">Input port's name.</param>
    /// <returns>Boolean that indicates if the name was set.</returns>
    ///
    bool                    setName             (const ACHAR* pName);

    /// <summary>
    /// This function retrieves the port's position.
    /// </summary>
    /// <returns>Position in space.</returns>
    ///
    const AcGePoint3d &     getPosition         () const;

    /// <summary>
    /// This function sets the port's position.
    /// </summary>
    /// <param name="pt">Input port's new position.</param>
    ///
    void                    setPosition         (const AcGePoint3d& pt);

    /// <summary>
    /// This function retrieves the port's direction.
    /// </summary>
    /// <returns>The port's direction.</returns>
    ///
    const AcGeVector3d &    getDirection        () const;

    /// <summary>
    /// This function sets the port's direction.
    /// </summary>
    /// <param name="v">Input port's new direction.</param>
    ///
    void                    setDirection        (const AcGeVector3d& v);

    /// <summary>
    /// This function retrieves the port's engagement length.
    /// </summary>
    /// <returns>The port's engagement length.</returns>
    /// <remarks>
    /// This function is only applicable to dynamic ports. Static port properties
    /// are stored in the project database and are acquired through 
    /// AcPp3dPartSizeProperties::port() and the AcPp3dSpecPort class.
    /// </remarks>
    /// <seealso cref="AcPp3dNominalDiameter"/>
    /// <seealso cref="AcPp3dPartSizeProperties"/>
    ///
    double                  getEngagementLength () const;

    /// <summary>
    /// This function sets the port's engagement length.
    /// </summary>
    /// <param name="length">Input port's new engagement length.</param>
    /// <returns>Boolean that indicates if the engagement length was set.</returns>
    /// <remarks>
    /// This function is only applicable to dynamic ports. Static port properties
    /// are stored in the project database and are acquired through 
    /// AcPp3dPartSizeProperties::port() and the AcPp3dSpecPort class.
    /// </remarks>
    /// <seealso cref="AcPp3dNominalDiameter"/>
    /// <seealso cref="AcPp3dPartSizeProperties"/>
    ///
    bool                    setEngagementLength (double length);

    // Dynamic port
    //

    /// <summary>
    /// This function retrieves whether the port was dynamically added
    /// or always present with the object. A dynamic port is used for
    /// taps and other scenarios where a connection is made without an
    /// open port already available.
    /// </summary>
    /// <returns>Boolean that indicates if the port is dynamic.</returns>
    ///
    bool                    isDynamic           () const;

    /// <summary>
    /// This function sets whether the port is dynamic or not.
    /// </summary>
    /// <param name="bIsDynamic">Input boolean that indicates if the port or dynamic or not.</param>
    ///
    void					setIsDynamic		(bool bIsDynamic);

    /// <summary>
    /// This function retrieves the port's nominal diameter. 
    /// </summary>
    /// <returns>The nominal diameter.</returns>
    /// <remarks>
    /// This function is only applicable to dynamic ports. Static port properties
    /// are stored in the project database and are acquired through 
    /// AcPp3dPartSizeProperties::port() and the AcPp3dSpecPort class.
    /// </remarks>
    /// <seealso cref="AcPp3dNominalDiameter"/>
    /// <seealso cref="AcPp3dPartSizeProperties"/>
    /// <seealso cref="AcPp3dSpecPort"/>
    ///
    const AcPp3dNominalDiameter & getNominalDiameter () const;

    /// <summary>
    /// This function sets the port's nominal diameter.
    /// </summary>
    /// <param name="nd">Input port's nominal diameter.</param>
    /// <remarks>
    /// This function is only applicable to dynamic ports. Static port properties
    /// are stored in the project database and are acquired through 
    /// AcPp3dPartSizeProperties::port() and the AcPp3dSpecPort class.
    /// </remarks>
    /// <seealso cref="AcPp3dNominalDiameter"/>
    /// <seealso cref="AcPp3dPartSizeProperties"/>
    /// <seealso cref="AcPp3dSpecPort"/>
    ///
    void                    setNominalDiameter  (const AcPp3dNominalDiameter& nd);

    /// <summary>
    /// This function retrieves the port's end type.
    /// </summary>
    /// <returns>The port's end type.</returns>
    /// <remarks>
    /// This function is only applicable to dynamic ports. Static port properties
    /// are stored in the project database and are acquired through 
    /// AcPp3dPartSizeProperties::port() and the AcPp3dSpecPort class.
    /// </remarks>
    /// <seealso cref="AcPp3dPartSizeProperties"/>
    /// <seealso cref="AcPp3dSpecPort"/>
    ///
    const ACHAR *           getEndType          () const;

    /// <summary>
    /// This function sets the port's end type.
    /// </summary>
    /// <param name="pName">Input port's new end type.</param>
    /// <remarks>
    /// This function is only applicable to dynamic ports. Static port properties
    /// are stored in the project database and are acquired through 
    /// AcPp3dPartSizeProperties::port() and the AcPp3dSpecPort class.
    /// </remarks>
    /// <seealso cref="AcPp3dPartSizeProperties"/>
    /// <seealso cref="AcPp3dSpecPort"/>
    ///
    void                    setEndType          (const ACHAR *type);

    /// <summary>
    /// This function is used to determine if the port is empty.
    /// </summary>
    ///
    bool                    isNull              () const;

    /// <summary>
    /// This function is used to clear the port to an empty state.
    /// </summary>
    ///
    void                    setNull             ();

	// Symbolic port
	//

    /// <summary>
    /// This function retrives whether the port is symbolic or not. A symbolic
    /// port is used for non-piping connections between objects. These connections
    /// are never part of the piping model.
    /// </summary>
    ///
    bool                    isSymbolic          ()const;

    /// <summary>
    /// This function sets whether the port is symbolic or not.
    /// </summary>
    /// <param name="bIsSymbolic">Input boolean indicating symbolic state.</param>
    ///
    void					setIsSymbolic		(bool bIsSymbolic);

    // For internal use
    //
	AcPp3dImpPort*	imp() const;

private:

	AcPp3dImpPort*	m_pImp;
};

//-----------------------------------------------------------------------------
inline AcPp3dImpPort* AcPp3dPort::imp() const
{
	assert(m_pImp != NULL);
	return reinterpret_cast<AcPp3dImpPort*>(m_pImp);
}


// Array
//
template <typename T, typename R> class AcArray2 : public AcArray<T,R>
{
public:
    AcArray2(int initPhysicalLength = 0, int initGrowLength = 2);
};

template <class T, class R> AcArray2<T,R>::AcArray2(int physicalLength, int growLength)
    : AcArray(physicalLength, growLength)
{
}

typedef AcArray2<AcPp3dPort, AcArrayObjectCopyReallocator<AcPp3dPort> > AcPp3dPortArray;
