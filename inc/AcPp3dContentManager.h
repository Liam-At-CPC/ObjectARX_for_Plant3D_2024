//
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

#pragma once

#include "PnP3dContent.h"
#include "AcPp3dSpecPart.h"
#include "AcString.h"
#include "AcArray.h"
#include "gevc3dar.h"
#include "dbmain.h"
#include <map>

class AcPp3dContentAdapter;

class AcPp3dContentManager
{
public:
    // Access manager object
    //
    PNP3DCONTENT_API
    static AcPp3dContentManager &   getContentManager       ();
    
    // Adapters
    //
    PNP3DCONTENT_API
    virtual void                    registerAdapter         (const ACHAR *adapterName,
                                                             AcPp3dContentAdapter *pAdapter);
    PNP3DCONTENT_API
    virtual void                    unRegisterAdapter       (const ACHAR *adapterName);
    PNP3DCONTENT_API
    virtual void                    getAdapterNames         (AcArray<AcString> &names) const;
    PNP3DCONTENT_API
    virtual AcPp3dContentAdapter *  findAdapter             (const ACHAR *adapterName) const;
    
    // Get/Create part block in the database
    //
    PNP3DCONTENT_API
    virtual bool                    getSymbol               (const AcPp3dPartSizeProperties &part,
                                                             AcDbDatabase *db,
                                                             AcDbObjectId &id);
    PNP3DCONTENT_API
    virtual bool                    getSymbolWithUnits      (const AcPp3dPartSizeProperties &part,
                                                             AcDbDatabase *db,
                                                             AcDbObjectId &id,
                                                             AcPp3dNominalDiameter::EUnit unit);
    
    // check if newProps would require to update the graphics in currentBTRId
    //
    PNP3DCONTENT_API
	virtual bool 					isSymbolChanged			(const AcPp3dPartSizeProperties &newProps, 
															 AcDbDatabase* db, 
															 const AcDbObjectId& currentBTRId);

    // update the graphics specified by currentBTRId according to newProps and return the new block
	// handles cutback elbows and similar parts correctly
	// return true if new Block was generated successfully or no changed was needed
	// if no change was needed, newBTRId is set to currentBTRId
    //
    PNP3DCONTENT_API
	virtual bool 					updateSymbol			(const AcPp3dPartSizeProperties &newProps, 
															 AcDbDatabase* db, 
															 const AcDbObjectId& currentBTRId,
															 AcDbObjectId& newBTRId,
                                                             AcPp3dNominalDiameter::EUnit unit);

    // retrieve ports for cutback elbows without generating the block
    //
    PNP3DCONTENT_API
    virtual bool                    getCutbackElbowPorts    (const AcPp3dPartSizeProperties &part, 
                                                             AcGePoint3dArray& positions, 
                                                             AcGeVector3dArray& directions,
															 double& l1,
															 double& l2,
                                                             AcPp3dNominalDiameter::EUnit unit);

    // Implementetaion
    //
                                    AcPp3dContentManager    ();
    virtual                         ~AcPp3dContentManager   ();
    void                            unload                  ();

    // Utilities
    //
    PNP3DCONTENT_API
    virtual bool                    unitScaleBlock          (const AcDbObjectId blockId,
                                                             AcPp3dNominalDiameter::EUnit unit,
                                                             double scale,
                                                             AcDbObjectId& newBlockId,
                                                             AcPp3dContentAdapter* pAdapter);

protected:
    bool                            scaleBlockXData         (const AcDbObjectId blockId,
                                                             AcPp3dNominalDiameter::EUnit unit,
                                                             double scale);

    std::map<AcString, AcPp3dContentAdapter *> m_Adapters;
};
