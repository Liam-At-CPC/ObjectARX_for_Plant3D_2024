//
// (C) Copyright 2009-2011 by Autodesk, Inc.
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
#include "PpConnectionManagerDefs.h"
#include "AcPp3dSpecPart.h"
#include "AcPpError.h"

class AcPp3dSpecManager;


// part in connector
class AcPp3dConnectorPart
{
    friend class AcPp3dConnectorPartImp;
public:
    CONN_DLL_SCOPE AcPp3dConnectorPart ();
    CONN_DLL_SCOPE AcPp3dConnectorPart (const AcPp3dPartSizeProperties & part, const ACHAR * port1, const ACHAR * port2);
    CONN_DLL_SCOPE AcPp3dConnectorPart (const AcPp3dConnectorPart & other);

    CONN_DLL_SCOPE 
    virtual ~AcPp3dConnectorPart ();

    CONN_DLL_SCOPE
    void operator = (const AcPp3dConnectorPart & other);

    CONN_DLL_SCOPE
    const ACHAR *					getInputPort () const;
    CONN_DLL_SCOPE
    const ACHAR *					getOutputPort () const;
    CONN_DLL_SCOPE
    const AcPp3dPartSizeProperties& getPart () const;

private:
    AcPp3dConnectorPartImp * m_imp;
};

// connector parts. 
class AcPp3dConnectorParts
{
    friend class AcPp3dConnectorPartsImp;

public:
    CONN_DLL_SCOPE
    AcPp3dConnectorParts ();

    CONN_DLL_SCOPE
    AcPp3dConnectorParts (const ACHAR * name, double slopeTolerance, double offsetTolerance);


    CONN_DLL_SCOPE
    virtual ~AcPp3dConnectorParts ();

    // this is joint name
    CONN_DLL_SCOPE
    const ACHAR *                  getName ();

    // spec parts in connection
    CONN_DLL_SCOPE
    AcArray<AcPp3dConnectorPart> & getParts ();

    // fittings
    CONN_DLL_SCOPE
    AcArray<AcPp3dConnectorPart> & getFittings ();

    // slope tolerance (degrees)
    CONN_DLL_SCOPE
    double                         getSlopeTolerance ();

    // offset tolerance (size)
    CONN_DLL_SCOPE
    double                         getOffsetTolerance ();

private:
    AcPp3dConnectorPartsImp * m_imp;
};

// connection mananger
class CONN_DLL_SCOPE AcPp3dConnectionManager
{
friend class AcPp3dConnectionManagerImp;
public:
									AcPp3dConnectionManager ();
                                    AcPp3dConnectionManager (const ACHAR* defaultConnConfigFile,
                                                             const ACHAR* ndUnits);
    virtual                         ~AcPp3dConnectionManager();
    

    // find out whether spec part 1 specified by specification name and partid
    // can be connected to part 2 from port1 to port2,
    // connector parts and fittings should come from specification specConn
    // In case of success, return connection paths;
    virtual  bool canConnect                                (const ACHAR       *   spec1,
                                                             const ACHAR           partGuid1,
                                                             const ACHAR       *   portName1,
                                                             const ACHAR       *   spec2,
                                                             const ACHAR           partGuid2,
                                                             const ACHAR       *   portName2,
                                                             const ACHAR       *   specConn,
                                                             AcPp3dSpecManager &   specman,
                                                             AcArray<AcPp3dConnectorParts*> & path,
                                                             AcPpErrorArray &errs);

    virtual  bool canConnect                                (const AcPp3dPartSizeProperties     &part1,
                                                             const ACHAR                    *portName1,
                                                             const AcPp3dPartSizeProperties     &part2,
                                                             const ACHAR                    *portName2,
                                                             const ACHAR                    *specConn,
                                                             AcPp3dSpecManager              &specman,
                                                             AcArray<AcPp3dConnectorParts*> &path,
                                                             AcPpErrorArray &errs);

    // Checks whether connection config has a joint for end types
    //
    virtual  bool hasConnection                             (const ACHAR *endType1,
                                                             const ACHAR *endType2);

    // Checks whether end types are compatible, i.e. can be used in the same joint, like PL and BV
    //
    virtual  bool isCompatibleEndTypes                      (const ACHAR *endType1,
                                                             const ACHAR *endType2);

    // Maximum tolerances in the connection config
    //
    virtual double                  getMaxSlopeTolerance    () const;
    virtual double                  getMaxOffsetTolerance   () const;

    // Pipe Bend
    //
    virtual bool                    isConnectPipeToBendWithWeld () const;
    virtual void                    setIsConnectPipeToBendWithWeld (bool flag);

    // Verifies that specified joint exists
    //
    virtual bool                    hasJoint                (const ACHAR *name) const;

public:
	AcPp3dConnectionManagerImp * Imp() const;

private:
    AcPp3dConnectionManagerImp * m_imp;

};
