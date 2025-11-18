//
// (C) Copyright 2009 by Autodesk, Inc.
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

#include "PpSpecManagerDefs.h"
#include "AcPp3dSpecPart.h"


/////////////////////////////////////////////////////////////////////////////////
// class AcPp3dSpecBranchTableParts
//
// Results of querying spec branch table
// for the given header/branch there could be multiple options.
// each may have multiple parts
/////////////////////////////////////////////////////////////////////////////////
class AcPp3dSpecBranchTableParts
{
friend class AcPp3dSpecBranchTablePartsImp;
friend class AcPp3dSpec;

protected:
    AcPp3dSpecBranchTableParts (AcPp3dSpecBranchTablePartsImp * imp);

public:
    DLL_SCOPE
    virtual ~ AcPp3dSpecBranchTableParts ();

    // header size
    DLL_SCOPE
    const AcPp3dNominalDiameter & getHeader () const;

    // branch size
    DLL_SCOPE
    const AcPp3dNominalDiameter & getBranch () const;

    // returns the number of branch options for the give header/branch combination
    // branch options are ordered according to their priorities - the first one is the
    // preferred
    DLL_SCOPE
    int                           BranchOptionsCount () const;

    // gets the branch option by index.  
    DLL_SCOPE
    AcPp3dSpecPartReader *        BranchOption (int idx);  

protected:

    AcPp3dSpecBranchTablePartsImp * m_imp;

};