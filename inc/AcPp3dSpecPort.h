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

#define UNIT_NAME_LENGTH 8  // length of the unit name 

// nominal diameter
class AcPp3dNominalDiameter
{
public:

    // Supported units
    //
    enum EUnit
    {
        kUndefined = 0,
        kMm = 1,
        kInch = 2
    };

    DLL_SCOPE  static ACHAR * Metric;
    DLL_SCOPE  static ACHAR * Imperial;

    DLL_SCOPE AcPp3dNominalDiameter ();
    DLL_SCOPE AcPp3dNominalDiameter (double value);
    DLL_SCOPE AcPp3dNominalDiameter (AcPp3dNominalDiameter::EUnit unit, double value);
    DLL_SCOPE AcPp3dNominalDiameter (const ACHAR * unit, double value);
    DLL_SCOPE AcPp3dNominalDiameter (const AcPp3dNominalDiameter & other);
    DLL_SCOPE
    virtual ~AcPp3dNominalDiameter ();

    DLL_SCOPE  void operator= (const AcPp3dNominalDiameter & other);
    DLL_SCOPE  bool operator== (const AcPp3dNominalDiameter & other) const;
    DLL_SCOPE  bool operator!= (const AcPp3dNominalDiameter & other) const;
    DLL_SCOPE  bool operator< (const AcPp3dNominalDiameter & other) const;
    DLL_SCOPE  int  compare (const AcPp3dNominalDiameter & other) const;

    DLL_SCOPE  AcPp3dNominalDiameter::EUnit getEUnit () const;
    DLL_SCOPE  void  setEUnit (AcPp3dNominalDiameter::EUnit unit);
    DLL_SCOPE  const ACHAR * getUnit () const;
    DLL_SCOPE  void setUnit ( const ACHAR * u);
    DLL_SCOPE  double getValue () const;
    DLL_SCOPE  void setValue (double val);

    DLL_SCOPE  ACHAR * ToString (ACHAR * buff, int len) const;
    DLL_SCOPE  ACHAR * ToDisplayString (ACHAR * buff, int len) const;
    DLL_SCOPE  ACHAR * ToDisplayString (ACHAR * buff, int len,
                                        AcPp3dNominalDiameter::EUnit kTargetUnit,
                                        bool bIncludeNativeString) const;

    // return true if alternative nd is found
    DLL_SCOPE  bool AlternativeND (AcPp3dNominalDiameter & ndout) const;

    // returns true if conversion is possible
    DLL_SCOPE  
    static bool FromDisplayString (const ACHAR * buff, AcPp3dNominalDiameter & ndout);

    DLL_SCOPE
    static double getScale(AcPp3dNominalDiameter::EUnit fromUnit, AcPp3dNominalDiameter::EUnit toUnit);

private:
    double          m_val;
    ACHAR           m_unit [UNIT_NAME_LENGTH];
};

// array of nominal diameters
typedef AcArray<AcPp3dNominalDiameter> AcPp3dNDArray;

// port 
class AcPp3dSpecPort
{
friend class AcPp3dSpecPortImp;
friend class AcPp3dSpecPartImp;
friend class AcPp3dSpecPartReaderImp;
friend class AcPp3dSpecManagerImp;


protected:
                                    AcPp3dSpecPort        (AcPp3dSpecPortImp * imp);
public:
    DLL_SCOPE                       AcPp3dSpecPort       ();
    DLL_SCOPE                       AcPp3dSpecPort       (const AcPp3dSpecPort &src);

    DLL_SCOPE
    virtual                         ~AcPp3dSpecPort      ();

    // equal
    DLL_SCOPE
    bool                            operator ==          (const AcPp3dSpecPort &other);

    // assignment
    DLL_SCOPE
    AcPp3dSpecPort &                operator =           (const AcPp3dSpecPort &other);

    // get port name
    DLL_SCOPE
    virtual const ACHAR *           getName              () const;

    // get port nominal size
    DLL_SCOPE
    virtual const AcPp3dNominalDiameter  &       getNominalDiameter    () const;


    // get end condition
    DLL_SCOPE
    virtual const ACHAR *           getEndCondition       () const;

    // number of properties
    DLL_SCOPE
    virtual int                     propCount              () const;

    // Property names
    DLL_SCOPE
    virtual void                    propNames               (AcPpStringArray & output) const;

    // Property values accessors
    DLL_SCOPE
    virtual const AcPpValue *       propValue               (const ACHAR *paramName) const;

    // set property value
    DLL_SCOPE
    virtual void                    setPropValue            (const ACHAR *paramName, const AcPpValue & value);

    // assign new id to port
    DLL_SCOPE
    virtual void                    assignNewId             ();

    AcPp3dSpecPortImp          *    imp () { return m_imp; }

protected:
    AcPp3dSpecPortImp           *   m_imp; 
};

class AcPp3dNonSpecPort : public AcPp3dSpecPort
{
friend class AcPp3dSpecPortImp;

protected:
                                    AcPp3dNonSpecPort        (AcPp3dSpecPortImp * imp);
public:
    DLL_SCOPE                       AcPp3dNonSpecPort       ();
    DLL_SCOPE                       AcPp3dNonSpecPort       (const AcPp3dNonSpecPort &src);

    DLL_SCOPE
    virtual                         ~AcPp3dNonSpecPort      ();

    // equal
    DLL_SCOPE
    bool                            operator ==          (const AcPp3dNonSpecPort &other);

    // assignment
    DLL_SCOPE
    AcPp3dNonSpecPort &             operator =           (const AcPp3dNonSpecPort &other);
    // assignment
    DLL_SCOPE
    AcPp3dNonSpecPort &             operator =           (const AcPp3dSpecPort &other);

    DLL_SCOPE
    virtual void                    addPropValue            (const ACHAR * pname, const AcPpValue & value);

    DLL_SCOPE
    virtual void                    setNominalDiameter    (const AcPp3dNominalDiameter  & );

    DLL_SCOPE
    virtual void                    setEndCondition       (const ACHAR *);

    DLL_SCOPE
    virtual void                    setName               (const ACHAR *);
};
