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

#include "basetsd.h"
#include "PpSpecManagerDefs.h"
#include "AcPp3dSpecPort.h"

// class AcPp3dSpecPort;

// properties of an AcPpDb3dPart
// this is a restricted interface to the AcPp3dSpecPartImp 
// These properties need not stem from a part repository,
// therefore expect getDomain(), getName(), getDefinition(),
// getSpec(), getType(), and getPartId() to return the 
// empty string.
//
class AcPp3dPartSizeProperties
{
friend class AcPp3dSpecPart;
friend class AcPp3dSpecPartImp;
friend class AcPp3dSpecPartReaderImp;
friend class AcPp3dSpecManagerImp;

protected:
                                    AcPp3dPartSizeProperties (AcPp3dSpecPartImp * imp);
public:
    DLL_SCOPE                       AcPp3dPartSizeProperties ();
    DLL_SCOPE                       AcPp3dPartSizeProperties (const AcPp3dPartSizeProperties &src);
    DLL_SCOPE                       AcPp3dPartSizeProperties (const AcPp3dPartSizeProperties &src, bool bDetach);

    DLL_SCOPE
    virtual                         ~AcPp3dPartSizeProperties();

    DLL_SCOPE
    static const ACHAR*             lengthUnitPropertyName();

    // operators
    // assignment
    DLL_SCOPE
    AcPp3dPartSizeProperties &      operator =           (const AcPp3dPartSizeProperties &src);
    // equal. Parts are equal if spec and part id both match or if all other properties match
    DLL_SCOPE
    bool                            operator ==          (const AcPp3dPartSizeProperties &other);

    // Property geeometry parameters that defines its graphical representation

    // Graphical domain. Should map to content adapter
    DLL_SCOPE
    virtual const ACHAR *           getDomain               () const;
    DLL_SCOPE
    virtual void                    setDomain               (const ACHAR *name);

    // Name of geometry in domain  (parameteric script, etc
    DLL_SCOPE
    virtual const ACHAR *           getName                 () const;
    DLL_SCOPE
    virtual void                    setName                 (const ACHAR *name);

    // definition of geometry. Domain/Nae specific
    DLL_SCOPE
    virtual const ACHAR *           getDefinition           () const;
    DLL_SCOPE
    virtual void                    setDefinition           (const ACHAR *name);

    DLL_SCOPE
    virtual const AcPp3dNominalDiameter &        getNominalDiameter      () const;
    DLL_SCOPE
    virtual void                    setNominalDiameter      (const AcPp3dNominalDiameter & nd);

    DLL_SCOPE
    virtual AcPp3dNominalDiameter::EUnit         getLinearUnit           () const;
    DLL_SCOPE
    virtual void                    setLinearUnit           (AcPp3dNominalDiameter::EUnit unit);

    DLL_SCOPE
    virtual const ACHAR *           getOriginalVersion      () const;

    // Regular properties

    // number of properties
    DLL_SCOPE
    virtual int                     propCount               () const;

    // Property names
    DLL_SCOPE
    virtual void                    propNames               (AcPpStringArray & output) const;

    // Property values accessors
    DLL_SCOPE
    virtual const AcPpValue *       propValue               (const ACHAR *paramName) const;
    DLL_SCOPE
    virtual void                    setPropValue            (const ACHAR *paramName, const AcPpValue & value);

    // Specificaton name
    DLL_SCOPE
    virtual const ACHAR *           getSpec                 () const;
    DLL_SCOPE
    virtual void                    setSpec                 (const ACHAR *spec);

    // part id that uniquely identified part in the spec. May change in a new revision of spec
    DLL_SCOPE
    virtual int                     getPartId               () const;
    DLL_SCOPE
    virtual void                    setPartId               (int partid);

    // part guid that uniquely identify the part and is not supposed to change in  spec 
    // revisons
    DLL_SCOPE
    virtual const ACHAR *           getPartGuid             () const;
    DLL_SCOPE
    virtual void                    setPartGuid             (const ACHAR *guid);


    // part type
    DLL_SCOPE
    virtual const ACHAR *           getType                 () const;
    DLL_SCOPE
    virtual void                    setType                 (const ACHAR *type);

    // number of ports explicitly defined in spec. It may be less that the 
    // number of ports in content. This means that all ports are equal in the 
    // spec sense (ignoring graphical parameters)
    DLL_SCOPE
    virtual int                     portCount               () const;

    // port names
    DLL_SCOPE
    virtual void                    portNames               (AcPpStringArray & output) const;

    // get port by name
    DLL_SCOPE
    virtual const AcPp3dSpecPort *  port              (const ACHAR * portName) const;

    // get principal port
    DLL_SCOPE
    virtual const AcPp3dSpecPort *  principalPort     () const;

    DLL_SCOPE
    virtual bool                    renamePort        (const ACHAR * oldName, const ACHAR * newName);

    // Units
    //
    DLL_SCOPE
    bool                            needUnitScale     (AcPp3dNominalDiameter::EUnit targetUnit,
                                                       double &scale) const;

    // Size property
    //
    DLL_SCOPE
    static void                     formatSizeDisplay (AcPpValue &displaySize,
                                                       const ACHAR *size,
                                                       AcPp3dNominalDiameter::EUnit targetUnit,
                                                       bool bIncludeNativeString,
                                                       AcPp3dNominalDiameter::EUnit partUnit);
    DLL_SCOPE
    static void                     sizeFromDisplay   (AcPpValue &size,
                                                       const ACHAR *displaySize);


    DLL_SCOPE
    virtual void                    serialize         (char * & buffer, INT_PTR & len);

    DLL_SCOPE
    virtual bool                    deserialize       (const char * buffer, INT_PTR len);

    AcPp3dSpecPartImp *             Imp               ()  { return m_imp;}

protected:
	const AcPpValue *				getSpecValue	  () const;

protected:
    AcPp3dSpecPartImp           *   m_imp; 
};

// specification part
// 
// Spec parts, in contrast to AcPp3dPartSizeProperties, 
// really stem from a parts repository (either a spec or a catalog)
// if the part stems from a catalog, it may still return "" for getSpec()
// if the part stems from a spec, it is expected to return a valid spec name
//
class AcPp3dSpecPart : public AcPp3dPartSizeProperties
{
friend class AcPp3dSpecPartImp;
friend class AcPp3dSpecPartReaderImp;
friend class AcPp3dSpecManagerImp;

protected:
                                    AcPp3dSpecPart       (AcPp3dSpecPartImp * imp);
public:
    DLL_SCOPE                       AcPp3dSpecPart       ();
    DLL_SCOPE                       AcPp3dSpecPart       (const AcPp3dSpecPart &src);
    DLL_SCOPE                       AcPp3dSpecPart       (const AcPp3dSpecPart &src, bool bDetach);

    DLL_SCOPE
    virtual                         ~AcPp3dSpecPart      ();

    // operators
    // assignment
    DLL_SCOPE
    AcPp3dSpecPart &                operator =           (const AcPp3dSpecPart &src);
    // equal. Parts are equal if spec and part id both match
    DLL_SCOPE
    bool                            operator ==          (const AcPp3dSpecPart &other);

    // upgrade an AcPp3dPartSizeProperties object
    DLL_SCOPE
    void                            assignFrom           (const AcPp3dPartSizeProperties &src);
};

class AcPp3dNonSpecPart : public AcPp3dPartSizeProperties
{
friend class AcPp3dSpecPartImp;
friend class AcPp3dSpecManagerImp;

protected:
                                    AcPp3dNonSpecPart       (AcPp3dSpecPartImp * imp);
public:
    DLL_SCOPE                       AcPp3dNonSpecPart       ();
    DLL_SCOPE                       AcPp3dNonSpecPart       (const AcPp3dPartSizeProperties &src);
    DLL_SCOPE                       AcPp3dNonSpecPart       (const AcPp3dPartSizeProperties &src, bool bDetach);

    DLL_SCOPE
    virtual                         ~AcPp3dNonSpecPart      ();

    // operators
    // assignment
    DLL_SCOPE
    AcPp3dNonSpecPart &             operator =           (const AcPp3dPartSizeProperties &src);

    // equal. Parts are equal if spec and part id both match
    DLL_SCOPE
    bool                            operator ==          (const AcPp3dPartSizeProperties &other);

    DLL_SCOPE
    virtual void                    addPropValue         (const ACHAR * pname, const AcPpValue & value);

    DLL_SCOPE
    virtual void                    addPort              (const AcPp3dSpecPort & port);

    DLL_SCOPE
    virtual bool                    replacePort          (const ACHAR * portName,
                                                          const AcPp3dSpecPort & port);

    DLL_SCOPE
    virtual bool                    removePort           (const ACHAR * portName);
};
