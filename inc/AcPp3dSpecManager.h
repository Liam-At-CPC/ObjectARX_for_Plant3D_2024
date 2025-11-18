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

#include <string>
#include "PpSpecManagerDefs.h"
#include "AcPp3dSpecPart.h"
#include "AcPp3dSpecPartReader.h"
#include "AcPp3dSpecBranchTableParts.h"

// completion status 
typedef enum _ESpecStatus
{
    eSpcOk,
    eSpcSpecNotFound,
    eSpcSpecNotLoaded,
	eSpcSpecNotCurrent
} ESpecStatus;


class AcPp3dSpecManager
{
friend class AcPp3dSpecManagerImp;
public:
    DLL_SCOPE                       AcPp3dSpecManager       (const ACHAR * path,
                                                             AcPp3dNominalDiameter::EUnit ndUnits,
                                                             std::wstring (*findSpec)(const ACHAR *));
    DLL_SCOPE
    virtual                         ~AcPp3dSpecManager      ();


    // load specification by name
    DLL_SCOPE
    ESpecStatus                     loadSpec                (const ACHAR * name);
    // release specificion
    DLL_SCOPE
    ESpecStatus                     releaseSpec             (const ACHAR * name);

    // release all specs
    DLL_SCOPE
    void                            releaseAllSpecs         ();

	// Does part belong to the specific spec
	DLL_SCOPE
	bool							hasPart					(const ACHAR * specName,
															 const ACHAR * partType);
    
    // Find part in the current spec
    // Returns AcPp3DSpecPartReader object that caller must destroy
    DLL_SCOPE
    virtual AcPp3dSpecPartReader *  selectParts             (const ACHAR *specName,
                                                             const ACHAR *partType,
                                                             const AcPpStringArray &propNames,
                                                             const AcPpValueArray  &propValues);

    DLL_SCOPE
    virtual AcPp3dSpecPartReader *  selectParts             (const ACHAR *specName,
                                                             const ACHAR *partType,
                                                             const ACHAR *filter,
                                                             const ACHAR *orderby);

    DLL_SCOPE
    virtual AcPp3dSpecPartReader *  selectParts             (const ACHAR *specName,
                                                             const ACHAR *partType,
                                                             const ACHAR *filter);

    // select parts by nominal size
    DLL_SCOPE
    virtual AcPp3dSpecPartReader *  selectParts            (const ACHAR    *specName,
                                                            const ACHAR    *partType,
                                                            const AcPp3dNominalDiameter & nsize);

    DLL_SCOPE
    virtual AcPp3dSpecPartReader *  selectPartByFamilyGuidNominalDiameter (
                                                            const ACHAR    *specName,
                                                            const ACHAR    *partType,
                                                            const ACHAR    *partFamilyId,
                                                            const AcPp3dNominalDiameter & nsize);


    DLL_SCOPE
    virtual AcPp3dSpecPartReader *  SelectPartsGroupByPartClassAndFaimlyId  (const ACHAR    *specName);


    DLL_SCOPE
    virtual AcPp3dSpecPartReader *  selectPartsAndPlaceholders (
                                                             const ACHAR    *specName,
                                                             const ACHAR    *partType,
                                                             const AcPp3dNominalDiameter & nsize);
	DLL_SCOPE
    virtual AcPp3dSpecPartReader *  selectPartsAndCustomParts (
                                                             const ACHAR    *specName,
															 const ACHAR    *specPath,
                                                             const ACHAR    *partType,
                                                             const AcPp3dNominalDiameter & nsize);

	DLL_SCOPE
    virtual	AcPp3dSpecPart * findCustomPart (const ACHAR *    specName,  const ACHAR *    specPath,   const ACHAR *    partGuid );


    // get nominal diameters for the given specification and part type
    // if part type is null or empty string all nd are returned
    DLL_SCOPE
    virtual bool                    getNominalDiameters     (const ACHAR *specName,
                                                             const ACHAR *partType,
                                                             AcPp3dNDArray & nds);

	// get nominal diameters for the given specification, part type and PartFamilyId
    // if PartFamilyId is null or empty string all partType nd are returned
    DLL_SCOPE
    virtual bool                    getPartFamilyNominalDiameters (const ACHAR *specName,
                                                                   const ACHAR *partType,
															       const ACHAR* partFamilyId,
                                                                   AcPp3dNDArray & nds);


	// get sizes for the given specification, part type and PartFamilyId
    // if PartFamilyId is null or empty string all partType nd are returned
    DLL_SCOPE
    virtual bool                    getPartFamilySizes		(const ACHAR *specName,
                                                             const ACHAR *partType,
															 const ACHAR* partFamilyId,
                                                             AcPp3dNominalDiameter::EUnit targetUnit,
                                                             bool bIncludeNativeString,
                                                             AcPpStringArray & sizes);

    // get nominal diameters for the given specification, part type and valve body type
    //
    DLL_SCOPE
    virtual bool                    getValveNominalDiameters(const ACHAR *specName,
                                                             const AcPpStringArray& valveSubTypes,
                                                             AcPp3dNDArray& nds);

    // get specification part
    // 
    DLL_SCOPE
    virtual AcPp3dSpecPart *        findPart                (const ACHAR *specName,
                                                             long partId);

    // get part by part guid
    DLL_SCOPE
    virtual AcPp3dSpecPart *        findPart                (const ACHAR *specName,
                                                             const ACHAR * guid);


    // get part use order for the given part type and numinal size
    // initialize array by part id
    // returns true if order is defined.
    DLL_SCOPE
    virtual bool                    getPartUseOrder         (const ACHAR *specName,
                                                             const ACHAR *partType,
                                                             const AcPp3dNominalDiameter & nd,
                                                             AcArray<long> & partIds);



    // find branch options for the give header/branch pair
    DLL_SCOPE
    virtual AcPp3dSpecBranchTableParts *        
                                    findBranchPartOptions   (const ACHAR *specName,
                                                             const AcPp3dNominalDiameter & header,
                                                             const AcPp3dNominalDiameter & branch);


    /// <summary>
    /// Gets the PartsRepository GCHandle the specification 
    /// void pointer
    /// PartsRepository  object can be retrived as following:
    /// void * ptr = specman->getPartsRepositoryGCHandle ();
    /// GCHandle gch = GCHandle::operator GCHandle(System::IntPtr(ptr));
    /// PartsRepository ^ rep = (PartsRepository ^ ) gch.Target;
    /// gch.Free () // must release
    /// </summary>
    DLL_SCOPE 
    void  *                         getPartsRepositoryGCHandle (const ACHAR * specname);

    DLL_SCOPE 
    static AcPp3dSpecPart *         makePart3dPart (void * vpart);

    DLL_SCOPE 
    static AcPp3dNonSpecPart *      make3dNonSpecPart (void * vpart);

    // Specification properties
 // get speficiation part properties
    DLL_SCOPE
    AcPpStringArray *               getSpecAvailablePartTypes (const ACHAR *specName);

    // get speficiation part properties
    DLL_SCOPE
    AcPpStringArray *               getSpecPartPropertyNames (const ACHAR *specName, const ACHAR * partType);

    // get speficiation part properties
    DLL_SCOPE
    AcPpStringArray *               getSpecPortPropertyNames (const ACHAR *specName, const ACHAR * partType);


    DLL_SCOPE
    static const ACHAR *            ElbowClassName ();
    DLL_SCOPE
    static const ACHAR *            PipeClassName ();
    DLL_SCOPE
    static const ACHAR *            ReducerClassName ();
    DLL_SCOPE
    static const ACHAR *            SupportClassName ();
    DLL_SCOPE
    static const ACHAR *            InstrumentClassName();
    

    // extension of the spec file
    DLL_SCOPE
    static const ACHAR *            SpecFileExtension ();

    // extension of the catalog file
    DLL_SCOPE
    static const ACHAR *            CatalogFileExtension ();

    // placeholder specification name
    DLL_SCOPE
    static const ACHAR *            PlaceholdersSpecName (AcPp3dNominalDiameter::EUnit unit);
    DLL_SCOPE
    static bool                     IsPlaceholderSpecName (const ACHAR *pName);

	// custom parts specification name
    DLL_SCOPE
    static const ACHAR *            CustomPartsSpecName (AcPp3dNominalDiameter::EUnit unit);
    DLL_SCOPE
    static bool                     IsCustomPartsSpecName (const ACHAR *pName);
    
	// pipe supports specification name
    DLL_SCOPE
    static const ACHAR *            PipeSupportsSpecName (AcPp3dNominalDiameter::EUnit unit = AcPp3dNominalDiameter::kUndefined);
    DLL_SCOPE
    static bool                     IsPipeSupportsSpecName (const ACHAR *pName);
    
    // instruemnts specification name
    DLL_SCOPE
        static const ACHAR *            InstrumentsSpecName(AcPp3dNominalDiameter::EUnit unit = AcPp3dNominalDiameter::kUndefined);
    DLL_SCOPE
        static bool                     IsInstrumentsSpecName(const ACHAR *pName);

protected:

    AcPp3dSpecManagerImp * m_imp;
};
