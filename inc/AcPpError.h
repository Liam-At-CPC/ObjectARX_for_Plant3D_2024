//
// (C) Copyright 2009-2010 by Autodesk, Inc.
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

#include <string>
#include <vector>


template <class _Ty> class AcPpArrayTmpl : public std::vector<_Ty>
{
public:
    void append (const AcPpArrayTmpl<_Ty> &src)
    {
        insert(begin(), src.begin(), src.end());
    }
};


template <class _Ty> class AcPpErrorTmpl
{
public:
    AcPpErrorTmpl ()
        {
        }

    AcPpErrorTmpl (const _Ty &err)
        {
            setErr (err);
        }

    AcPpErrorTmpl (const _Ty &err,
                   const AcPpArrayTmpl<AcPpErrorTmpl> &arr)
        {
            setErr (err);
            setSubErrors (arr);
        }
	AcPpErrorTmpl(const _Ty &errID, const _Ty &err)
		{
			setErrID(errID);
			setErr (err);
		}
	AcPpErrorTmpl(const _Ty &errID, const _Ty &err, const AcPpArrayTmpl<AcPpErrorTmpl> &arr)
		{
			setErrID(errID);
			setErr (err);
			setSubErrors (arr);
		}
    AcPpErrorTmpl (const AcPpErrorTmpl &src)
        {
            *this = src;
        }

    virtual ~AcPpErrorTmpl ()
        {
        }

    AcPpErrorTmpl & operator = (const AcPpErrorTmpl &src)
        {
            setErrID (src.getErrID());
			setErr (src.getErr());
            setSubErrors (src.getSubErrors());
            return *this;
        }

    void setErr (const _Ty &err)
        {
            m_Err = err;
        }

    const _Ty & getErr () const
        {
            return m_Err;
        }

    void setSubErrors (const AcPpArrayTmpl<AcPpErrorTmpl> &arr)
        {
            m_SubErrors = arr;
        }

    const AcPpArrayTmpl<AcPpErrorTmpl> & getSubErrors () const
        {
            return m_SubErrors;
        }
	void setErrID(const _Ty &errID)
		{
			m_ErrID = errID;
		}
	 const _Ty & getErrID () const
        {
            return m_ErrID;
        }
protected:
	_Ty							  m_ErrID;
    _Ty                           m_Err;
    AcPpArrayTmpl<AcPpErrorTmpl>  m_SubErrors;
};


typedef AcPpErrorTmpl<std::wstring>     AcPpError;
typedef AcPpArrayTmpl<AcPpError>        AcPpErrorArray;