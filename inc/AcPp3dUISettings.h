//
// (C) Copyright 2008-2011 by Autodesk, Inc.
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

#include "AcString.h"
#include "AcArray.h"
#include "AdAChar.h"
#include "AcPp3dSpecPort.h"
#include "AcPpDataLinks.h"
#include "AcPp3dDataLinksManager.h"


class AcCmColor;
class CTime;

// Reactor
//
class AcPp3dUISettingsReactor
{
public:

    // Group your settings (usually by feature) so that reactors can
    // decide which settings are interesting to them.  The pattern is
    // to define a lower bound, then your settings, then the upper
    // bound.  We will waste two values per group, but the coding
    // will be simpler.  We can afford to waste a few values given
    // a 32-bit signed integer for enumeration constants.

    enum ESetting
    {
        // Compass
        kCompassLowerBound,
        kCompassColor,
        kCompassDiameter,
        kCompassEnabled,
        kCompassSnapEnabled,
        kCompassSnapIncrement,
        kCompassTickmarkEnabled,
        kCompassTickmarkIncrement,
        kCompassToleranceRoutingEnabled,
        kCompassToleranceSnapIncrement,
        kCompassUpperBound,

        // Piping
        kPipingLowerBound,
        kSpec,
        kSize,
        kOffset,
        kOffsetConnect,
        kElevation,
        kSlope,
        kCutback,
        kStubin,
        kLineNumber,
        kLineNumberList,
        kThresholdAngle,
        kPipeBend,
        kPipingUpperBound,

		// Grip edit mode
		//
		kGripEditMode,

        // Disconnect markers
        //
        kDisplayMarkers,

        // Insulation
        //
        kDisplayInsulation,

        // Placeholder
        //
        kDisplayPlaceholder,

        // Size display
        //
        kDisplayNativeSize,

		// Ortho Editor
		//
		kOrthoViewName,
		kOrthoViewType,
		kOrthoViewScale,
		//kOrthoView

		// Pipe Supports
		//
		kLockPointOfSupport,
    };

    virtual void            settingChanged          (AcPp3dUISettingsReactor::ESetting type)
    {
    }
};


// Settings
//
class AcPp3dUISettings
{
public:
    // Specs in the current project
    //
    virtual const ACHAR *   getCurrentSpec            () = 0;
    virtual bool            setCurrentSpec            (const ACHAR *spec) = 0;
    virtual void            getAllSpecs               (AcArray<AcString> &specs) = 0;
	virtual void			ClearSpecsCache		      () = 0;

    // Project Units
    //
    virtual AcPp3dNominalDiameter::EUnit getProjectUnit() = 0;
    virtual AcPp3dNominalDiameter::EUnit getNDProjectUnit() = 0;
    
    // Sizes in the current spec
    //
    virtual const ACHAR *   getCurrentSize          () = 0;
    virtual bool            setCurrentSize          (const ACHAR *size) = 0;
    virtual void            getAllSizes             (AcArray<AcString> &sizes) = 0;	
    
    // Get nominal diameters from specified spec
    //
    virtual void            getNominalSizes          (const ACHAR *spec, AcArray<AcString> &sizes) = 0;
    virtual void            getNominalSizes          (const ACHAR *spec, AcPp3dNDArray &sizes) = 0;

    // Offset
    //
    enum EJust
    {
        kTL = 0,
        kTC = 1,
        kTR = 2,
        kCL = 3,
        kCC = 4,
        kCR = 5,
        kBL = 6,
        kBC = 7,
        kBR = 8
    };

    virtual AcPp3dUISettings::EJust getJustification() = 0;
    virtual void            setJustification        (AcPp3dUISettings::EJust just) = 0;
    virtual double          getOffsetU              () = 0;
    virtual void            setOffsetU              (double offset) = 0;
    virtual double          getOffsetV              () = 0;
    virtual void            setOffsetV              (double offset) = 0;

    // Offset connect
    //
    virtual bool            getOffsetConnectFlag    () = 0;
    virtual void            setOffsetConnectFlag    (bool flag) = 0;
    
    // Elevation
    //
    virtual double          getElevation            () = 0;
    virtual void            setElevation            (double elevation) = 0;
    virtual bool            getLockElevationFlag    () = 0;
    virtual void            setLockElevationFlag    (bool flag) = 0;

	// Supports lock point
	//
    virtual bool            getLockPointOfSupport   () const = 0;
    virtual void			setLockPointOfSupport   (bool val) = 0;
    

    // Slope piping
    //
    virtual bool            getSlopeFlag            () = 0;
    virtual void            setSlopeFlag            (bool flag) = 0;
    virtual double          getSlopeRise            () = 0;
    virtual void            setSlopeRise            (double rise) = 0;
    virtual double          getSlopeRun             () = 0;
    virtual void            setSlopeRun             (double run) = 0;

    // Cutback elbow
    //
    virtual bool            getCutbackFlag          () = 0;
    virtual void            setCutbackFlag          (bool flag) = 0;

    // Stub-in mode in pipe routing
    //
    virtual bool            getStubinFlag           () = 0;
    virtual void            setStubinFlag           (bool flag) = 0;

    // Line Number
    //
    virtual const ACHAR *   getCurrentLineNumber    () = 0;
    virtual bool            setCurrentLineNumber    (const ACHAR *name) = 0;
    virtual void            getAllPipingLineNumbers (AcArray<AcPp3dLineGroupData> &lgroups, bool bWithPartsOnly) = 0;
    virtual void            getAllPIDLineNumbers    (AcArray<AcString> &names) = 0;
    
    // Slope Threshold angle
    //
    virtual double          getThresholdAngle       () = 0;
    virtual bool            setThresholdAngle       (double angle) = 0;

    // Pipe Bend
    //
    virtual bool            getPipeBendFlag         () = 0;
    virtual void            setPipeBendFlag         (bool flag) = 0;

    // Compass
    //
    virtual AcCmColor & getCompassColor           (AcCmColor &) const = 0;
    virtual unsigned    getCompassDiameter                   () const = 0;
    virtual bool        getCompassEnabled                    () const = 0;
    virtual bool        getCompassSnapEnabled                () const = 0;
    virtual double &    getCompassSnapIncrement      (double &) const = 0;
    virtual bool        getCompassTickmarkEnabled            () const = 0;
    virtual double &    getCompassTickmarkIncrement  (double &) const = 0;
    virtual bool        getCompassToleranceRoutingEnabled    () const = 0;
    virtual double &    getCompassToleranceSnapIncrement
                                                     (double &) const = 0;
    virtual void setCompassColor                   (const AcCmColor &) = 0;
    virtual void setCompassDiameter                (unsigned)         = 0;
    virtual void setCompassEnabled                 (bool)             = 0;
    virtual void setCompassSnapEnabled             (bool)             = 0;
    virtual void setCompassSnapIncrement           (const double &)   = 0;
    virtual void setCompassTickmarkEnabled         (bool)             = 0;
    virtual void setCompassTickmarkIncrement       (const double &)   = 0;
    virtual void setCompassToleranceRoutingEnabled (bool)             = 0;
    virtual void setCompassToleranceSnapIncrement  (const double &)   = 0;

    // Display disconnect markers
    //
    virtual bool    getPlantConnectionMarkerEnabled() const = 0;
    virtual void    setPlantConnectionMarkerEnabled(bool) = 0;

    // Insulation
    virtual bool    getDisplayInsulation() const = 0;
    virtual void    setDisplayInsulation(bool) = 0;
    virtual int     getPlantInsulationMode() const = 0;
    virtual void    setPlantInsulationMode(int mode) = 0;

    // Placeholder
    virtual bool    getDisplayPlaceholder() const = 0;
    virtual void    setDisplayPlaceholder(bool) = 0;

    // Size display
    //
    virtual bool    getDisplayNativeSize() const = 0;
    virtual void    setDisplayNativeSize(bool) = 0;

	// Ortho Editor
	virtual const ACHAR *    getOrthoViewName() const = 0;
    virtual bool             setOrthoViewName(const ACHAR *name) = 0;

	virtual const ACHAR *    getOrthoView() const = 0;
    virtual bool             setOrthoView(const ACHAR *name) = 0;

	virtual const ACHAR *    getOrthoScale() const = 0;
    virtual bool             setOrthoScale(const ACHAR *name) = 0;

	// Grip edit mode
	//
	enum EGripEditMode
	{
		kPipeSegment = 0,
		kPipeLine    = 1
	};

	virtual AcPp3dUISettings::EGripEditMode getGripEditMode() = 0;
	virtual void            setGripEditMode        (AcPp3dUISettings::EGripEditMode mode) = 0;
    
    // ...

    // Reactors
    //
    virtual  void           addReactor              (AcPp3dUISettingsReactor *pReactor) = 0;
    virtual  void           removeReactor           (AcPp3dUISettingsReactor *pReactor) = 0;
    virtual  void           notify                  (AcPp3dUISettingsReactor::ESetting event) = 0;


    // Changing several variables (kDisplayMarkers, kDisplayInsulation, kDisplayPlaceholder)
    // will cause current dwg to regen (scan, seach for affected parts...)
    // Below methods allow to temporary disable that
    //
    virtual bool            getRegenDwgOnVarChange  () const = 0;
    virtual void            setRegenDwgOnVarChange  (bool flag) = 0;
};
