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


class AcPp3dSpecPartReader
{
friend class AcPp3dSpecPartReaderImp;
friend class AcPp3dSpec;
friend class AcPp3dSpecBranchTablePartsImp;
friend class AcPp3dSpecManagerImp;
protected:
                                    AcPp3dSpecPartReader (AcPp3dSpecPartReaderImp * imp);
public:
    DLL_SCOPE
    virtual                         ~AcPp3dSpecPartReader ();

    // read next 
    DLL_SCOPE
    bool                             next ();
    DLL_SCOPE
    const AcPp3dSpecPart *           currentPart ();
    DLL_SCOPE
    void                             close ();
private:
    AcPp3dSpecPartReaderImp      *   m_imp;
};
