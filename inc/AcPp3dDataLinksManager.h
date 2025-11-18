//
// (C) Copyright 2008-2009 by Autodesk, Inc.
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

#include <time.h>
#include <acarray.h>
#include <AcString.h>
#include <PnPSharedUtilDLL.h>
#include <AcPp3dSpecPart.h>
#include <AcPp3dSpecPort.h>
#include <AcPpError.h>

#include "PnPDllDef.h"

// Line group data
class AcPp3dLineGroupData 
{
public:
    AcPp3dLineGroupData ()
    {
        m_lockedTimestamp = 0;
        m_bLocked         = false;
        m_rowId           = -1;

    }

    AcPp3dLineGroupData (int            rowId,
                         const ACHAR  * lnumber, 
                         bool           bLocked,
                         const ACHAR  * lockedBy, 
                         __int64        lockedTimestamp 
                         )
    {
        m_lineNumber      = lnumber;
        m_lockedBy        = lockedBy;
        m_bLocked         = bLocked;
        m_lockedTimestamp = lockedTimestamp;
        m_rowId           = rowId;
    }

    AcPp3dLineGroupData (const AcPp3dLineGroupData & other)
    {
        * this = other;
    }
    virtual ~AcPp3dLineGroupData ()
    {

    }

    void operator=(const AcPp3dLineGroupData & other)
    {
        m_lineNumber      = other.m_lineNumber;
        m_lockedBy        = other.m_lockedBy;
        m_bLocked         = other.m_bLocked;
        m_lockedTimestamp = other.m_lockedTimestamp;
        m_rowId           = other.m_rowId;

    }

    const ACHAR  *  lineNumber () const
    {
        return (const ACHAR *) m_lineNumber;
    }
    bool            isLocked () const
    {
        return m_bLocked;
    }
    const ACHAR  *  lockedBy () const
    {
        return (const ACHAR *) m_lockedBy;
    }

    // .net ticks
    const __int64  lockedTicks () const
    {
        return m_lockedTimestamp;
    }

    const __time64_t  lockedTime () const
    {
        // from .net ticks to __time64_t
        __int64 epoch = 621355968000000000;
        __int64 nanosecs = 10000000;

        return  (__time64_t)(m_lockedTimestamp - epoch) / nanosecs;
    }


    int             rowId () const
    {
        return m_rowId;
    }

protected:
    AcString       m_lineNumber;
    AcString       m_lockedBy;
    __int64         m_lockedTimestamp;
    bool            m_bLocked;
    int             m_rowId;
};


// 3d data links manage extension.
class PNP3DDATALINKS_API AcPp3dDataLinksManager
{
    friend class AcPp3dDataLinksManagerImp;
protected:
    AcPp3dDataLinksManager (AcPp3dDataLinksManagerImp * imp);
    virtual ~AcPp3dDataLinksManager ();
public:
    // get 3d data links manager that extends the specified on
    static AcPp3dDataLinksManager * Get3dLinksManager (AcPpDataLinksManager * man);
    // destroy all data link managers
    static void DestroyAll3dLinkManagers ();

    // destroys 3d links manager
    void Destroy3dLinksManager ();

    // returns general data links manager 
    AcPpDataLinksManager * DataLinksManager ();

    // create object in the project database and link it with the 
    // specified objectid. Properties are specified using 
    // specification part
    AcPpRowId Create3dPart (
                    const AcDbObjectId &  id,
                    int                   subIndex,
                    const AcPp3dPartSizeProperties &part,
                    AcPp3dNominalDiameter::EUnit linearUnit,
                    AcPp3dNominalDiameter::EUnit NDUnit,
                    AcPpErrorArray &errs);

    // update object in the project database
    // Properties are specified using specification part
    AcPpRowId Update3dPart (
                    const AcDbObjectId &  id,
                    int                   subIndex,
                    const AcPp3dPartSizeProperties &part,
                    AcPp3dNominalDiameter::EUnit linearUnit,
                    AcPp3dNominalDiameter::EUnit NDUnit,
                    AcPpErrorArray &errs);

    AcPp3dPartSizeProperties * Get3dPart (AcPpRowId rowId);
    bool    GetPropertiesFromClassName(const ACHAR* clsName,AcPpStringArray& propNames);


    // lock/inlock linegroup. Methods accepts linegroup or asset rowid.
    // if Asset id is specified, the linegroup it belongs to is locked.
    // It returns true if operation succeeded
    // bCommit true forces commiting lock status to the project database 
    bool LockLineGroup (AcPpRowId rowid, bool bLock, bool bCommit);

    // returns lock status for the linegroup specied by either rowid 
    // or bu line number
    bool IsLineGroupLocked (AcPpRowId rowid);
    bool IsLineGroupLocked (const ACHAR * lnumber);


    // Get line group info
    bool GetLineGroupInfo (const ACHAR * lnumber, AcPp3dLineGroupData & info);
    bool GetLineGroupInfo (AcPpRowId rowid,       AcPp3dLineGroupData & info);

    // return all line groups in the project.
    // if bWithPartsOnly only lg with parts are returned
    void GetLineGroups  (AcArray<AcPp3dLineGroupData> &names,
                         bool bWithPartsOnly);


    // reload specified linegroups
    void ReloadLineGroups (const AcPpRowIdArray & lgids);

    // reload all linegroups
    void ReloadLineGroups ();


    // remove unused line groups
    bool RemoveUnusedLineGroups (AcPpStringArray & removedlinenumbers);

    // remove unused ports
    bool RemoveUnusedPorts (AcPpStringArray & removedportids);

    // add missing ports
    bool AddMissingPorts (AcPpStringArray & addedportids);

    // Get nd untis 
    AcPp3dNominalDiameter::EUnit GetNDUnits ();

    // Set ND units
    void                        SetNDUnits (AcPp3dNominalDiameter::EUnit ndunits);

    void *                      GetProjectRepositoryGCHandler ();

                   
    AcPp3dDataLinksManagerImp * Imp ();

private:
    AcPp3dDataLinksManagerImp * m_imp;


};
