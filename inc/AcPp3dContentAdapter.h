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
#include "acstring.h"
#include "AcPp3dSpecPart.h"
#include "dbmain.h"
#include "gevc3dar.h"

class AcPp3dContentAdapter
{
public:
    // Get/Create part block in the database
    //
    PNP3DCONTENT_API
    virtual bool                    getSymbol               (const AcPp3dPartSizeProperties &part,
                                                             AcDbDatabase *db,
                                                             AcDbObjectId &id) = 0;

    // check if newProps would require to update the graphics in currentBTRId
    //
    PNP3DCONTENT_API
	virtual bool 					isSymbolChanged			(const AcPp3dPartSizeProperties &newProps, 
															 AcDbDatabase* db, 
															 const AcDbObjectId& currentBTRId) = 0;

    // update the graphics specified by currentBTRId according to newProps and return the new block
	// handles cutback elbows and similar parts correctly
	// return true if new Block was generated successfully or no changed was needed
	// if no change was needed, newBTRId is set to currentBTRId
    //
    PNP3DCONTENT_API
	virtual bool 					updateSymbol			(const AcPp3dPartSizeProperties &newProps, 
															 AcDbDatabase* db, 
															 const AcDbObjectId& currentBTRId,
															 AcDbObjectId& newBTRId) = 0;

    // retrieve ports for cutback elbows without generating the block
    //
    PNP3DCONTENT_API
    virtual bool                    getCutbackElbowPorts    (const AcPp3dPartSizeProperties &part, 
                                                             AcGePoint3dArray& positions, 
                                                             AcGeVector3dArray& directions,
															 double& l1, double& l2) = 0;


    // take blockId and return Id of block that either 
    // is already scaled or can safely be scaled
    //
    PNP3DCONTENT_API 
	virtual bool                    getScalable             (const AcDbObjectId& blockId, 
                                                             AcDbObjectId& newBlockId);
protected:	
	PNP3DCONTENT_API
	bool							isValve					(const AcPp3dPartSizeProperties &part);

	
	PNP3DCONTENT_API
	bool							calculateCenterPointOfValveBody	(const AcDbObjectId &bodyBlockId, 
																	 AcGePoint3d &centerPt);
	
	PNP3DCONTENT_API
    bool							combineValveIfNeeded	(const AcPp3dPartSizeProperties &part,
															 AcDbDatabase *pDb,
                                                             const AcDbObjectId &oldBodyBlockId,
															 const AcDbObjectId &bodyBlockId,
															 AcDbObjectId &valveBlockId);
};
