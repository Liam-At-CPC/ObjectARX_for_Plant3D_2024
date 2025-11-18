//
// (C) Copyright 2007-2008 by Autodesk, Inc.
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

//-----------------------------------------------------------------------------
//----- AcPpLineSegment.h : Declaration of the AcPpLineSegment
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "dbcurve.h"
#include "AcPpAsset.h"
#include "AcPpDataLinks.h"
#include "AcPpLineObject.h"
#include "PnPDllDef.h"

class AcPpImpLineSegment;

/// <summary>
/// Represents a line segment. Each line segment is defined by  properties like tag, size, spec, service, line number  
/// </summary>
class PNIDOBJECTS_API AcPpLineSegment : public AcDbCurve
{

    friend class AcPpImpLineSegment;

public:
	 ACRX_DECLARE_MEMBERS(AcPpLineSegment) ;

public:
	/// <summary>
    /// Default constructor.
    /// </summary>
	AcPpLineSegment () ;

    /// <summary>
    /// Destructor.
    /// </summary>
	virtual ~AcPpLineSegment () ;


    /// <summary>
    /// This function is called when proxy graphics are being generated.
    /// </summary>
	virtual void saveAs(AcGiWorldDraw* mode, AcDb::SaveType st);

 	/// <summary>
	/// This functions purpose is to allow the object to write out its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to write out the object's data </param>
	/// <returns>Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const ;

	/// <summary>
	/// This functions purpose is to allow the object to read in its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to read in the object's data </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) ;

    /// <summary>
	/// This functions purpose is to allow the object to write out its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to write out the object's data </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler *pFiler) const ;
    
	/// <summary>
	/// This functions purpose is to allow the object to read in its data.
	/// </summary>
	/// <param name = "pFiler"> Passed in pointer to filer to use to read in the object's data </param>
	/// <returns> Acad::ErrorStatus</returns>
	virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler *pFiler) ;

    //- SubXXX() methods (self notification)
	/// <summary>
	/// Called from within erase() before anything else is done
	/// </summary>
	/// <param name = "erasing">  Passed in copy of the erasing argument that was passed into the erase() function call that triggered this subErase() call</param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus subErase (Adesk::Boolean erasing) ;

	/// <summary>
	/// Called from within close() before anything else is done. 
	/// </summary>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus subClose () ;

    //----- clone
   /// <summary>
	/// This function creates a clone of the object and returns a pointer to the clone. 
	/// If the function is not successful in creating the clone, then NULL is returned.
	/// </summary>
	/// <returns> pointer to AcRxObject class </returns>
	virtual AcRxObject* clone() const;

    //----- AcDbCurve protocols
    //- Curve property tests.
	/// <summary>
	/// This function is called by AutoCAD when the AUDIT command is executed
	/// </summary>
	/// <param name =""> Passed in a pointer to an AcDbAuditInfo object </param>
	/// <returns> Acad::ErrorStatus</returns>
	virtual Acad::ErrorStatus audit(AcDbAuditInfo* auditor);

    //- Get planar and start/end geometric properties.
	/// <summary>
	/// This function returns with startPoint set to the start point (in WCS coordinates) of the curve.
	/// </summary>
	/// <param name =""> Returns the starting point of the curve </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getStartPoint (AcGePoint3d &point) const ;

	/// <summary>
	/// In this class and in derived classes, this function returns with endPoint set to the end point (in WCS coordinates) of the curve
	/// </summary>
	/// <param name =""> Returns the endpoint of the curve </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getEndPoint (AcGePoint3d &point) const ;

	/// <summary>
	/// This function returns Adesk::kTrue if, and only if, the curve is closed; that is, its start point is identical to its end point. 
	/// Otherwise, it returns Adesk::kFalse.
	/// </summary>
	/// <returns> Returns Acad::kFalse in the default implementation. </returns>
	virtual Adesk::Boolean isClosed() const;

	/// <summary>
	/// This function returns Adesk::kTrue if, and only if, the curve has an infinite range in both directions and there is a period value T such that there is a point on curve at (u + T) = point on curve (u), for any parameter u. 
	/// If the curve is not periodic, then Adesk::kFalse is returned.
	/// </summary>
	/// <param name =""> </param>
	/// <returns> The default implementation returns Adesk::kFalse. </returns>
	virtual Adesk::Boolean isPeriodic() const;

	/// <summary>
	/// This function returns Adesk::kTrue if and only if there is a plane that contains the entity. 
	/// Otherwise Adesk::kFalse is returned.
	/// </summary>
	/// <returns> Adesk::kFalse in the default implementation </returns>
	virtual Adesk::Boolean isPlanar() const;

	/// <summary>
	/// Derived from AcDbEntity::getPlane. If the entity is planar, then the plane containing the entity is returned in plane and flag is set to AcDb::kPlanar
	/// </summary>
	/// <param name ="plane"> Returns the plane which contains the curve </param>
	/// <param name ="planarity"> Returns the curve's configuration. </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getPlane(AcGePlane& plane, AcDb::Planarity& planarity) const;

	/// <summary>
	/// This function returns with startParam set to the start parameter on the curve
	/// </summary>
	/// <param name ="param"> Returns the parameter of the start of the curve </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getStartParam(double& param) const;

	/// <summary>
	/// The implementation of this function in derived classes should return with endParam set to the parameter of the endpoint of the curve.
	/// </summary>
	/// <param name ="param"> Returns the parameter of the end of the curve </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getEndParam(double& param) const;

	/// <summary>
	/// This function determines the point on the curve that corresponds to the param parameter, and returns the point in point. point is in WCS coordinates.
	/// </summary>
	/// <param name ="param"> Input parameter on the curve at which the point is desired </param>
	/// <param name ="point"> Returns the point on the curve </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getPointAtParam(double param, AcGePoint3d& point) const;

	/// <summary>
	/// This function determines the parameter of the curve at point and returns the parameter in param.
	/// </summary>
	/// <param name ="point"> Input point (in WCS coordinates) on the curve at which the parameter is desired </param>
	/// <param name ="param"> Returns the parameter of the curve at point </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getParamAtPoint(const AcGePoint3d& point, double& param) const;

	/// <summary>
	/// Calculates the length of the curve’s segment from the curve’s start point to the point specified by param
	/// </summary>
	/// <param name ="param"> Input parameter specifying a point on curve </param>
	/// <param name ="dist"> Returns the length of the curve’s segment from the curve’s beginning to the point specified by param </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getDistAtParam(double param, double& dist) const;

	/// <summary>
	/// This function determines the parameter of the curve at the location that is a distance of dist along the curve from the curve start, 
	/// and returns the parameter in param.
	/// </summary>
	/// <param name ="dist"> Input distance along the curve from the beginning of the curve to the location for the desired parameter </param>
	/// <param name ="param"> Returns parameter at the location specified by dist </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getParamAtDist(double dist, double& param) const;

	/// <summary>
	/// Calculates the length of the curve’s segment between the curve’s start point and point and returns the length in distance
	/// </summary>
	/// <param name ="point"> Input point (in WCS coordinates) on the curve </param>
	/// <param name ="dist"> Returns the length of the curve's segment between the curve's start point and point </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getDistAtPoint(const AcGePoint3d& point, double& dist) const;

	/// <summary>
	/// This function determines the point on the curve that is a distance of dist along the curve from the curve start, and returns the point in point.
	/// point is in WCS coordinates.
	/// </summary>
	/// <param name ="dist"> Input distance along the curve from the beginning of the curve to the location of the desired point </param>
	/// <param name ="point"> Returns the point located at the location specified by dist </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getPointAtDist(double dist, AcGePoint3d& point) const;

	// Derivative information.
	/// <summary>
	/// Here and in derived classes, this function is implemented to evaluate the first derivative at the location on the curve specified by param,
	/// and sets firstDeriv to the result (in WCS coordinates).
	/// </summary>
	/// <param name ="param"> Input parameter of location on curve at which to find the first derivative </param>
	/// <param name ="firstDeriv"> Returns the first derivative of the curve at param </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getFirstDeriv(double param, AcGeVector3d& firstDeriv) const;

	/// <summary>
	/// This function evaluates the first derivative of the curve at point and sets firstDeriv to the result, 
	/// in both this class and derived classes. 
	/// </summary>
	/// <param name ="point"> Input point on curve at which to find the first derivative </param>
	/// <param name ="firstDeriv"> Returns the first derivative of the curve at point </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getFirstDeriv(const AcGePoint3d& point, AcGeVector3d& firstDeriv) const;

	/// <summary>
	/// Evaluates the second derivative of the curve at point and sets secDeriv to the result
	/// </summary>
	/// <param name ="param"> Input parameter of location on the curve at which to find the second derivative </param>
	/// <param name ="secDeriv"> Returns the second derivative of the curve at param </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getSecondDeriv(double param, AcGeVector3d& secDeriv) const;

	/// <summary>
	/// Evaluates the second derivative of the curve at point and sets secDeriv to the result.
	/// </summary>
	/// <param name ="point"> Input point on the curve at which to find the second derivative </param>
	/// <param name ="secDeriv"> Returns the second derivative of the curve at point </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getSecondDeriv(const AcGePoint3d& point, AcGeVector3d& secDeriv) const;

	// Get a projected copy of the curve.
	/// <summary>
	/// This function creates a new curve entity that is the result of projecting the curve along the projPlane’s normal onto the projPlane and sets projCurve to point to the newly created curve
	/// </summary>
	/// <param name ="plane"> Input plane onto which the curve is to be projected </param>
	/// <param name ="projCrv"> Returns pointing to the newly created projected curve </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus
		getOrthoProjectedCurve(const AcGePlane& plane, AcDbCurve*& projCrv) const;

	/// <summary>
	/// This function creates a new curve entity that is the result of projecting the curve parallel to projDir onto the projPlane and sets projCurve to point to the newly created curve
	/// </summary>
	/// <param name ="plane"> Input plane onto which the curve is to be projected </param>
	/// <param name ="projDir"> Input direction (in WCS coordinates) of the projection </param>
	/// <param name ="projCrv"> Returns pointing to the newly created projected curve </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus
		getProjectedCurve(const AcGePlane& plane, const AcGeVector3d& projDir, AcDbCurve*& projCrv) const;

	// Get offset, spline and split copies of the curve.
	/// <summary>
	/// This function creates one or more entities that together make up the result of offsetting the curve by the distance offsetDist
	/// </summary>
	/// <param name ="offsetDist"> Input distance to offset the curve </param>
	/// <param name ="offsetCurves"> Returns an array of pointers to the resulting curve(s) </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getOffsetCurves(double offsetDist, AcDbVoidPtrArray& offsetCurves) const;

	/// <summary>
	/// This function creates a new AcDbSpline entity, sets it to be as close an approximation as possible to the curve, 
	/// and then returns with spline pointing to the newly created spline entity.
	/// </summary>
	/// <param name ="spline"> Returns pointing to an AcDbSpline approximation of the curve </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getSpline(AcDbSpline*& spline) const;

	/// <summary>
	/// This function creates one or more entities that are all subcurves of the original
	/// </summary>
	/// <param name ="params"> Input array of parameters on the curve </param>
	/// <param name ="curveSegments"> Returns with pointers to newly created entities that are subcurves of the original </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus getSplitCurves(const AcGeDoubleArray& params, AcDbVoidPtrArray& curveSegments) const;

	/// <summary>
	/// This function creates one or more entities that are all subcurves of the original
	/// </summary>
	/// <param name ="points"> Input array of points (in WCS coordinates) on the curve </param>
	/// <param name ="curveSegments"> Returns with pointers to newly created entities that are subcurves of the original </param>
	/// <returns> Acad::ErrorStatus  </returns>
	virtual Acad::ErrorStatus getSplitCurves(const AcGePoint3dArray& points, AcDbVoidPtrArray& curveSegments) const;

	// Extend the curve.
	/// <summary>
	/// This function extends the beginning or end of the curve to the new point determined by the newParam value.
	/// </summary>
	/// <param name ="newParam"> New start or end parameter on the curve </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus extend(double newParam);

	/// <summary>
	/// This function extends the curve to the point toPoint
	/// </summary>
	/// <param name ="extendStart"> Input Boolean indicating whether to extend the curve’s start or end </param>
	/// <param name ="toPoint"> Input new start or end point of the curve </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus extend(Adesk::Boolean extendStart, const AcGePoint3d& toPoint);

	// Area calculation.
	/// <summary>
	/// Get area of the entity
	/// </summary>
	/// <param name ="area"> Area of the entity </param>
	/// <returns> Acad::ErrorStatus</returns>
	virtual Acad::ErrorStatus getArea(double& area) const;

	/// <summary>
	/// This function finds the point on the curve that is nearest to givenPnt and sets pointOnCurve to the result.
	/// </summary>
	/// <param name ="givenPnt"> Input point (in WCS coordinates) for which to find nearest point on curve </param>
	/// <param name ="pointOnCurve"> Returns the point (in WCS coordinates) on the curve that is nearest to givenPnt </param>
	/// <param name ="extend"> Input Boolean indicating whether or not to extend curve in search for nearest point </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus
	getClosestPointTo(const AcGePoint3d& givenPnt, AcGePoint3d& pointOnCurve,
					  Adesk::Boolean extend = Adesk::kFalse) const;

	/// <summary>
	/// This function projects the curve onto the plane defined by givenPnt and normal, 
	/// finds the point on the projected curve that is nearest to givenPnt, 
	/// then projects this nearest point back onto the original curve and sets pointOnCurve to the result.
	/// </summary>
	/// <param name ="givenPnt"> Input point (in WCS coordinates) for which to find nearest point on curve </param>
	/// <param name ="direction"> Input normal vector (in WCS coordinates) for plane to project onto </param>
	/// <param name ="pointOnCurve"> Returns the point (in WCS coordinates) on the curve that is nearest to givenPnt </param>
	/// <param name ="extend"> Input Boolean indicating whether or not to extend curve in search for nearest point </param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus
	getClosestPointTo(const AcGePoint3d& givenPnt, const AcGeVector3d& direction,
					  AcGePoint3d& pointOnCurve, Adesk::Boolean extend = Adesk::kFalse) const;

	/// <summary>
	///This function is called when a drag operation involving this entity is starting, ending, or aborting. 
	/// The status argument provides information about what is happening with the drag operation.
	/// </summary>
	/// <param name ="status"> Value describing the status of the drag operation; one of the values from the DragStat enumeration </param>
	/// <returns> </returns>
	virtual void                dragStatus(
                                const AcDb::DragStat status);

    /////////////////////////////////////////////
    // AcPpLineSegment specific methods.
    ////////////////////////////////////////////

    // Accessor/Modifier functions
    /// <summary>
    /// Gets the number of vertices in this line segment.
    /// </summary>
    /// <returns>Number of vertices.</returns>
	Adesk::Int32        numVerts() const;

    /// <summary>
    /// Gets the vertices of this segment.
    /// </summary>
    /// <param name="vertices">Input AcGePoint3dArray of vertex points</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus   getVertices(AcGePoint3dArray& vertices) const;

    /// <summary>
    /// Gets the bulge factors of this segment.
    /// </summary>
    /// <param name="vertices">Input AcArray<double> of bulge factors</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus   getBulges(AcArray<double>& bulges) const;

    /// <summary>
    /// Append a vertex point to this segment.
    /// </summary>
	/// <param name="index">Index on line segment where to add vertex</param>
    /// <param name="pt">Input point to append to line segment</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus   addVertexAt(Adesk::Int32 index, const AcGePoint3d& pt, double bulge = 0); // adds the point at the end of the array.

    /// <summary>
    /// Remove the vertex point at the specified index.
    /// </summary>
    /// <param name="index">Input array index to insert at</param>
    /// <param name="pt">Input point to remove from line segment</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus   removeVertexAt(Adesk::Int32 index); // removes the indexed (0 based) point from the array.

    /// <summary>
    /// Replace a vertex point at the specified index.
    /// </summary>
    /// <param name="index">Input array index to replace at</param>
    /// <param name="pt">Input new vertex point</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus   setPointAt(Adesk::Int32 index, const AcGePoint3d& pt); // replaces the indexed (0 based) point in the array.

    /// <summary>
    /// Get the bulge factor at the specified vertex index.
    /// </summary>
    /// <param name="index">Input vertex index to set the bulge factor at.</param>
    /// <param name="dbBulge">Input bulge factor.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus   getBulgeAt(Adesk::Int32 index, double& dbBulge) const;
    
    /// <summary>
    /// Set the bulge factor at the specified vertex index.
    /// </summary>
    /// <param name="index">Input vertex index to set the bulge factor at.</param>
    /// <param name="dbBulge">Output bulge factor.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus   setBulgeAt(Adesk::Int32 index, double dbBulge);
    
    /// <summary>
    ///  Checks if the segment at the specified index is a curved segment.
    /// </summary>
    /// <param name="index"></param>
    /// <returns>Returns Acad::kTrue if specified segment is curved.</returns>
	Adesk::Boolean      isCurvedSegment(Adesk::Int32 index) const;

	/// <summary>
    /// Get the cache id of this line segment.
    /// </summary>
    /// <returns>AcPpRowId cache id.</returns>
	AcPpRowId                   cacheId() const;

    /// <summary>
    /// Get the style id of this line segment.
    /// </summary>
    /// <returns>AcDbObjectId style id.</returns>
	AcDbObjectId                styleId() const;

    /// <summary>
    /// Set the style id of this line segment.
    /// </summary>
    /// <param name="styleId">Input AcDbObjectId of the style</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus           setStyleId(const AcDbObjectId& styleId);

    /// <summary>
    /// Get the tag style id of this line segment.
    /// </summary>
    /// <returns>AcDbObjectId tag style id.</returns>
	AcDbObjectId                tagStyleId() const;

    /// <summary>
    /// Set the tag style id of this line segment.
    /// </summary>
    /// <param name="tagStyleId">Input AcDbObjectId of the tag style</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus           setTagStyleId(const AcDbObjectId& tagStyleId);
   
    /// <summary>
    /// Add an annotation to this line segment.
    /// </summary>
    /// <param name="annotationId"></param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus           addAnnotation(const AcDbObjectId& annotationId);
 
	/// <summary>
    /// Remove an annotation from this line segment.
    /// </summary>
    /// <param name="annotationId"></param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus           removeAnnotation(const AcDbObjectId& annotationId);

	/// <summary>
    /// Gets a collection of values representing the ids of the
    /// annotations of this line segment.
    /// </summary>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus           getAnnotations(AcDbObjectIdArray& ids) const;

	// Line index related functions

	/// <summary>
    /// Gets a value representing the index of the line at or near the specified
    /// point, with a tolerance of 1.0e-04 units.
    /// </summary>
    /// <param name="bIsVertex">Input toggle</param>
    /// <param name="pt">Input point on or near the line</param>
    /// <returns>Index of the line</returns>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus   		getIndexAtPoint(int& index, bool &bIsVertex, const AcGePoint3d& pt, double dTolerance = 1.0e-04) const;

	/// <summary>
    /// Adds the specified line object to this line segment.
    /// </summary>
    /// <param name="pLineObject">Input pointer to new line object.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus addLineObject(const AcPpLineObject* pLineObject);

    /// <summary>
    /// Commits changes specified by the updated line object to this line segment.
    /// </summary>
    /// <param name="pLineObject">Input pointer to the (updated) line object.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus editLineObject(const AcPpLineObject* pLineObject);

    /// <summary>
    /// Removes the specified line object from this line segment.
    /// </summary>
    /// <param name="pLineObject">Input pointer to the line object.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus removeLineObject(const AcPpLineObject* pLineObject);
    
    /// <summary>
    /// Gets the line object iterator of this line. The iterator will return line objects
    /// in the order they are found on the line from start to end.
    /// </summary>
    /// <returns>Returns a pointer to the line object iterator.</returns>
	AcPpLineObjectIterator* lineObjectIterator(const AcPpLineObjectFilter* pFilter = NULL) const;

    /// <summary>
    /// For internal use.
    /// </summary>
	AcPpImpLineSegment*          implementation();

	// style override functions
	/// <summary>
    /// Sets value representing the color
    /// </summary>
	/// <param name ="color"> Value representing the color </param>
	/// <param name ="doSubents"> </param>
    /// <returns> Acad::ErrorStatus</returns>
	virtual Acad::ErrorStatus	setColor(const AcCmColor& color,   Adesk::Boolean doSubents = true, AcDbDatabase *pDb = NULL);

	/// <summary>
    /// Sets value representing the color index
    /// </summary>
	/// <param name ="color"> Value representing the color index </param>
	/// <param name ="doSubents"> </param>	
    /// <returns>Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus   setColorIndex(Adesk::UInt16 color, Adesk::Boolean doSubents = true);

	/// <summary>
    /// Sets value representing the layer
    /// </summary>
	/// <param name ="newVal"> Value representing the layer </param>
	/// <param name ="doSubents"> </param>
	/// <param name ="allowHiddenLayer"> </param>
    /// <returns> Acad::ErrorStatus</returns>
	virtual Acad::ErrorStatus   setLayer(const ACHAR* newVal, Adesk::Boolean doSubents = true,
										 bool allowHiddenLayer = false);

	/// <summary>
    /// Sets value representing the layer
    /// </summary>
	/// <param name ="newVal"> Value representing the layer </param>
	/// <param name ="doSubents"> </param>
	/// <param name ="allowHiddenLayer"> </param>
    /// <returns> Acad::ErrorStatus</returns>
	virtual Acad::ErrorStatus   setLayer(AcDbObjectId newVal, Adesk::Boolean doSubents = true,
										 bool allowHiddenLayer = false);

	/// <summary>
    /// Sets value representing line type
    /// </summary>
	/// <param name ="newVal"> Value representing line type </param>
	/// <param name ="doSubents"> </param>
    /// <returns> Acad::ErrorStatus</returns>
	virtual Acad::ErrorStatus   setLinetype(const ACHAR* newVal, Adesk::Boolean doSubents = true);

	/// <summary>
    /// Sets value representing line type
    /// </summary>
	/// <param name ="newVal"> Value representing line type </param>
	/// <param name ="doSubents"> </param>
    /// <returns> Acad::ErrorStatus</returns>
	virtual Acad::ErrorStatus   setLinetype(AcDbObjectId newVal, Adesk::Boolean doSubents = true);

	/// <summary>
    /// Sets value representing line weight
    /// </summary>
	/// <param name ="newVal"> Value representing line weight </param>
	/// <param name ="doSubents"> </param>
    /// <returns>Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus   setLineWeight(AcDb::LineWeight newVal, Adesk::Boolean doSubents = true);

	/// <summary>
    ///  Sets value representing line type scale
    /// </summary>
	/// <param name ="newval"> Value representing line type scale </param>
	/// <param name ="doSubents"> </param>
    /// <returns>Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus   setLinetypeScale(double newval, Adesk::Boolean doSubents = true);

	/// <summary>
    /// Sets a value representing plot style name
    /// </summary>
	/// <param name ="newName"> name of the plot style </param>
	/// <param name ="doSubents"> </param>
    /// <returns>Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus   setPlotStyleName(const ACHAR* newName, Adesk::Boolean doSubents = true);

	/// <summary>
    /// Sets a value representing plot style name
    /// </summary>
	/// <param name ="newType"> New plot style name type to set </param>
	/// <param name ="newId"> </param>
	/// <param name ="doSubents"> </param>
    /// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus   setPlotStyleName(AcDb::PlotStyleNameType newType, AcDbObjectId newId = AcDbObjectId::kNull,
												 Adesk::Boolean doSubents = true);

    // For Typicals:

	/// <summary>
    /// Gets a value representing the class name of this line segment.
    /// </summary>
	/// <param name ="bFetchFromDataCache">boolean to determine if the class name is to be fetched from the Data Links </param>
    /// <returns>Class name.</returns>
	AcString                    lineClassName(bool bFetchFromDataCache = true);

	/// <summary>
    /// Gets a value representing the tag value of this line segment.
    /// </summary>
	/// <param name ="bFetchFromDataCache">boolean to determine if the tag value is to be fetched from the Data Links </param>
    /// <returns>Tag value.</returns>
	AcString                    tagValue(bool bFetchFromDataCache = true);

	/// <summary>
    /// Highlight only the S-line of this line segment.
    /// </summary>
	/// <param name = "subId">  Input AcDbFullSubentPath that identifies the subentity to highlight</param>
	/// <param name = "highlightAll">  Input Boolean indicating whether to highlight in all viewports</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus highlightOnlySline(const AcDbFullSubentPath& subId = kNullSubent,
                                         const Adesk::Boolean highlightAll = false) const;

	/// <summary>
    /// Unhighlight only the S-line of this line segment.
    /// </summary>
	/// <param name = "subId">  Input AcDbFullSubentPath that identifies the subentity to unhighlight</param>
	/// <param name = "highlightAll">  Input Boolean indicating whether to unhighlight in all viewports</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
	Acad::ErrorStatus unhighlightOnlySline(const AcDbFullSubentPath& subId = kNullSubent,
                                           const Adesk::Boolean highlightAll = false) const;

protected:

    /// <summary>
    /// This function provides a way for a custom entity to override the graphical attribute settings (such as color and lineweight) specified in the given AcGiDrawableTraits object. 
    /// For example, to override the color, use the AcGiDrawableTraits object's setColor() function. 
    /// </summary>
    /// <param name = "traits"> Input/output pointer to AcGiDrawableTraits object </param>
    /// <returns> Adesk::UInt32 </returns>
    virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits * traits) ;

	/// <summary>
	/// This function gives control of deep clone operations to the object. 
	/// </summary>
	/// <param name = "pOwnerObject"> Input object to which the clones should be appended </param>
	/// <param name = "pClonedObject"> Returns a pointer to the cloned object, or NULL if not cloned </param>
	/// <param name = "idMap"> Input current object ID map </param>
	/// <param name = "isPrimary"> Input Boolean indicating whether this object is primary or owned </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subDeepClone (AcDbObject *pOwnerObject, AcDbObject *&pClonedObject, AcDbIdMapping &idMap, Adesk::Boolean isPrimary =true) const ;

	/// <summary>
	/// This function is almost identical to AcDbObject::deepClone, except that an AcDbWblockCloneFiler is used and ownership is not carried across database boundaries. 
	/// </summary>
	/// <param name = "pOwnerObject"> Input object to which the clones should be appended. If the owner has not been cloned, then the AcDbDatabase must be passed in. </param>
	/// <param name = "pClonedObject">Returns the cloned object, or NULL if not cloned </param>
	/// <param name = "idMap"> Input current object ID map</param>
	/// <param name = "isPrimary"> Input Boolean indicating whether this object is primary or owned</param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subWblockClone (AcRxObject *pOwnerObject, AcDbObject *&pClonedObject, AcDbIdMapping &idMap, Adesk::Boolean isPrimary =true) const ;

	/// <summary>
	///	This function is defined at the AcDbObject level. It is overridden for every other class that traces its derivation to AcDbObject, and is represented by a different COM object type. 
	/// Thus, if you create a custom entity derived from AcDbEntity, and do not override getClassID(), this function returns the CLSID for AcadEntity. 
	/// This means your custom entities will have at least base-level functionality, even if you do not provide COM support for them.
	/// </summary>
	/// <param name = "pClsid"> COM wrapper class ID </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subGetClassID   (CLSID* pClsid) const;

    /// <summary>
	/// If worldDraw() returns Adesk::kFalse, then AutoCAD calls this function once for each viewport that is currently active in the AutoCAD editor
	/// </summary>
	/// <param name="mode"> Input pointer to fully initialized AcGiViewportDraw object </param>
	/// <returns> </returns>
    virtual void subViewportDraw (AcGiViewportDraw *mode) ;

	/// <summary> 
	/// Whenever a regeneration of the entity's graphics is required, AutoCAD calls this function to generate the graphics primitives that will represent this entity on screen. 
	/// This function will then provide a generic set of 3D graphics primitives that AutoCAD will adjust for each viewport's parameters as they are displayed.
	///</summary>
	/// <param name ="mode"> Input pointer to fully initialized AcGiWorldDraw object </param>
	/// <returns> Adesk::Boolean </returns>
    virtual Adesk::Boolean subWorldDraw (AcGiWorldDraw *mode) ;

	/// <summary>
	/// This function must use the material provided in osnapMode, gsSelectionMark, pickPoint, lastPoint, and viewXform to determine all appropriate osnap points for the entity. 
	/// It must then append all such osnap points to the snapPoints array.
	/// </summary>
	/// <param name = "osnapMode">Input osnap mode being requested  </param>
	/// <param name = "gsSelectionMark"> Input GS marker of the subentity involved in the object snap operation </param>
	/// <param name = "pickPoint"> Input point (in WCS coordinates) picked during the object snap operation  </param>
	/// <param name = "lastPoint"> Input point (in WCS coordinates) selected just before pickPoint </param>
	/// <param name = "viewXform"> Input transformation matrix to transform from WCS to DCS  </param>
	/// <param name = "snapPoints"> Input pre-existing array to append osnap points to (may already contain points); output with object snap points appended  </param>
	/// <param name = "geomIds"> Not in use </param>
	/// <returns> Acad::ErrorStatus</returns>
    virtual Acad::ErrorStatus subGetOsnapPoints (AcDb::OsnapMode osnapMode, Adesk::GsMarker gsSelectionMark, const AcGePoint3d &pickPoint, const AcGePoint3d &lastPoint,
        const AcGeMatrix3d &viewXform, AcGePoint3dArray &snapPoints, AcDbIntArray &geomIds) const ;

	/// <summary> This function gets the grip points and supporting information about the grips for this entity. 
	/// The caller is responsible for freeing the AcDbGripData objects whose pointers are in the grips array.
	/// </summary>
	/// <param name = "grips">Array of pointers to dynamically allocated AcDbGripData objects, one for each grip point in the entity  </param>
	/// <param name = "curViewUnitSize"> Size, in pixels, of one drawing unit in the current viewport </param>
	/// <param name = "gripSize"> Current grip size, in pixels  </param>
	/// <param name = "curViewDir"> Vector describing the view direction in the current viewport </param>
	/// <param name = "bitflags"> Bitmap of one or more flags specified by the GetGripPointsFlags enumeration </param>
	/// <returns>Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subGetGripPoints (AcDbGripDataPtrArray &grips, const double curViewUnitSize, const int gripSize,
                                             const AcGeVector3d &curViewDir, const int bitflags) const ;

	/// <summary>
	/// This function is intended to be called by the host application to move the grip points during a grip edit of the entity. 
	/// </summary>
	/// <param name = "gripAppData"> Input array of pointers, one for each grip point to be moved; these are the appData pointers from the AcDbGripData objects for the grip points to be moved </param>
	/// <param name = "offset"> Vector, in WCS coordinates, indicating the direction and magnitude of the translation to be applied to the grips </param>
	/// <param name = "bitflags"> Reserved for future use, currently zero </param>
	/// <returns>Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subMoveGripPointsAt (const AcDbVoidPtrArray &gripAppData, const AcGeVector3d &offset, const int bitflags) ;

	/// <summary>
	/// This function should append to the stretchPoints array any points that are to treated as stretch points for the entity.
	/// </summary>
	/// <param name = "stretchPoints"> Input pre-existing array to append the stretch points to; output with the entity's stretch points appended  </param>
	/// <returns> </returns>
	virtual Acad::ErrorStatus subGetStretchPoints(AcGePoint3dArray& stretchPoints) const;

	/// <summary>
	///This function is intended to be called by AutoCAD during execution of a stretch command in which the entity has been selected. 
	/// </summary>
	/// <param name = "indices"> Input array containing index values (which correspond to stretch points reported by the getStretchPoints() method) that indicate which stretch points are being translated </param>
	/// <param name = "offset"> Input vector (in WCS coordinates) indicating the direction and magnitude that the stretch points have been translated </param>
	/// <returns> Acad::ErrorStatus</returns>
	virtual Acad::ErrorStatus subMoveStretchPointsAt(const AcDbIntArray& indices, const AcGeVector3d& offset);

	/// <summary>
	/// This function uses the AcDbSubentId object within the subPath object to determine which GS markers within the entity are appropriate. 
	/// Any GS markers that match are appended to the gsMarkers array.
	/// </summary>
	/// <param name="subPath"> Input AcDbFullSubentPath object that contains an AcDbSubentId object with the information necessary to 
	/// determine the subentity (or subentities) for which the GS Marker(s) is requested. </param>
	/// <param name="gsMarkers"> Output array with the GSMarker(s) for the subentity (or subentities) </param>
	/// <returns> </returns>
    virtual Acad::ErrorStatus subGetGsMarkersAtSubentPath(
        const AcDbFullSubentPath& subPath,
		AcArray<Adesk::GsMarker>& gsMarkers) const;

	/// <summary>
	///
	/// </summary>
	/// <param name="type"> Input subentity type desired</param>
	/// <param name="gsMark"> Input GS marker representing a specific subentity </param>
	/// <param name="pickPoint"> Input point (in WCS coordinates) picked during selection of the entity (this point will be on or very near the desired subentity)</param>
	/// <param name="viewXform"> Input transformation matrix to transform from WCS to DCS </param>
	/// <param name="numPaths"> Output number of AcDbFullSubentPath objects in the subentPaths array</param>
	/// <param name="subentPaths"> Output address of a dynamically allocated array of one or more AcDbFullSubentPaths generated from the GS marker 
	/// and other information passed into this function</param>
	/// <param name="numInserts"> Input number of object IDs for AcDbBlockReferences in entAndInsertStack </param>
	/// <param name="entAndInsertStack"> Input array of objectIds of the objects that are the nested containers of the subentity </param>
	/// <returns> </returns>
    virtual Acad::ErrorStatus subGetSubentPathsAtGsMarker(
        AcDb::SubentType type,
        Adesk::GsMarker gsMark,
        const AcGePoint3d& pickPoint,
        const AcGeMatrix3d& viewXform,
        int& numPaths,
        AcDbFullSubentPath*& subentPaths,
        int numInserts = 0,
        AcDbObjectId* entAndInsertStack = NULL) const;

	/// <summary>
	/// Returns grip information about a subentity on the object
	/// </summary>
	/// <param name="path"> Input the AcDbFullSubentPath to the subentity</param>
	/// <param name="grips"> Output an array of pointers to dynamically allocated AcDbGripData objects, 
	/// one for each grip point in the subentity</param>
	/// <param name="curViewUnitSize"> Input size, in pixels, of one drawing unit in the current viewport</param>
	/// <param name="gripSize"> Input current grip size, in pixels</param>
	/// <param name="curViewDir"> Input vector describing the view direction in the current viewport</param>
	/// <param name="bitflags"> Input bitmap of one or more flags specified by the GetGripPointsFlags enumeration</param>
	/// <returns> </returns>
    virtual Acad::ErrorStatus subGetGripPointsAtSubentPath(
        const AcDbFullSubentPath& path,
        AcDbGripDataPtrArray& grips,
        const double curViewUnitSize,
        const int gripSize,
        const AcGeVector3d& curViewDir,
        const int bitflags) const;

	/// <summary>
	///
	/// </summary>
	/// <param name="paths"> Input an array of one or more AcDbFullSubentPath objects exposing the grips to move</param>
	/// <param name="gripAppData"> Input an array of pointers, one for each grip point to be moved; these are the appData pointers from the AcDbGripData objects for the grip points to be moved </param>
	/// <param name="offset"> Input the vector, in WCS coordinates, indicating the direction and magnitude of the translation to be applied to the grips </param>
	/// <param name="bitflags"> Reserved for future use; currently zero </param>
	/// <returns>Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subMoveGripPointsAtSubentPaths(
        const AcDbFullSubentPathArray& paths,
        const AcDbVoidPtrArray& gripAppData,
        const AcGeVector3d& offset,
        const int bitflags);

	/// <summary>
	/// Applies a geometric transformation to one or more subentities on an object.
	/// </summary>
	/// <param name="paths"> Input an array of one or more AcDbFullSubentPath objects identifying the subentities to transform</param>
	/// <param name="xform"> Input the WCS transformation to apply to each of the supplied subentities </param>
	/// <returns> </returns>
    virtual Acad::ErrorStatus subTransformSubentPathsBy(
        const AcDbFullSubentPathArray& paths, 
        const AcGeMatrix3d& xform);

	/// <summary>
	/// This function uses the AcDbFullSubentPath id to determine which subentity in the entity is desired. 
	/// It then highlights that subentity on screen. If no AcDbFullSubentPath argument is provided, then the entire entity will be highlighted.
	/// </summary>
	/// <param name = "subId">  Input AcDbFullSubentPath that identifies the subentity to highlight</param>
	/// <param name = "highlightAll">  Input Boolean indicating whether to highlight in all viewports</param>
	/// <returns>Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subHighlight(
        const AcDbFullSubentPath& subId = kNullSubent,
        const Adesk::Boolean highlightAll = false) const;

	/// <summary>
	/// This function uses the AcDbFullSubentPath id to determine which subentity in the entity is desired. 
	/// It then unhighlights that subentity on screen. If no AcDbFullSubentPath argument is provided, then the entire entity will be unhighlighted.
	/// </summary>
	/// <param name = "subId"> Input AcDbFullSubentPath that identifies which subentity to unhighlight </param>
	/// <param name = "highlightAll"> Input Boolean indicating whether to unhighlight in all viewports </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subUnhighlight(
        const AcDbFullSubentPath& subId = kNullSubent,
        const Adesk::Boolean highlightAll = false) const;

	/// <summary>
	/// This function is called with a status value of kGripsToBeDeleted when the grips for the entity are about to be deleted in the host application. 
	/// This notification allows the entity to perform any required resource management tasks before the grip's AcDbGripData objects and any alternate basepoint objects pointed to by the AcDbGripData objects are deleted. 
	/// This notification may be sent more than once for a given grip edit session.
	/// If the grip edit session is not over when this notification is sent, the entity will subsequently receive a call to its getGripPoints() function to acquire new grip points to be used by the grip edit session.
	/// This function is called with a status value of kDimDataToBeDeleted whenever the dynamic dimensions for the entity are about to be deleted.
	/// This function is called with a status value of kGripsDone when the grips for the entity have been deleted in the host application and the entity is no longer involved in any grip edit operations.
	/// </summary>
	/// <param name = "status">  Value describing the status of the grip operation; one of the values from the GripStatus enumeration </param>
	/// <returns> </returns>
    virtual void subGripStatus(const AcDb::GripStat status);

	/// <summary>
	/// This function is called with a status value of kGripsToBeDeleted when the grips for the subentity are about 
	/// to be deleted in the host application
	/// </summary>
	/// <param name="status"> Input the status of the grip operation </param>
	/// <param name="subentity"> Input the subobject on the object whose grip status changed </param>
	/// <returns> </returns>
    virtual void subSubentGripStatus(const AcDb::GripStat status,const AcDbFullSubentPath& subentity);

	/// <summary>
	/// This function is primarily intended for AutoCAD to call as part of an explode operation that includes this entity.
	/// </summary>
	/// <param name =""> Input array to contain pointers to new entities; this array may already contain pointers from other entities explode() methods;
	/// output with all entities that result from exploding this entity, appended to the array </param>
	/// <returns> Acad::ErrorStatus</returns>
    virtual Acad::ErrorStatus subExplode(AcDbVoidPtrArray& entitySet) const;

	/// <summary>
	/// This function is intended to be called from AutoCAD whenever the entity is selected during the LIST command.
	/// </summary>
    virtual void		      subList() const;

	/// <summary>
	/// Calculates and returns the corner points (in WCS coordinates) of a box (with edges parallel to the WCS X, Y, and Z axes) that encloses the 3D extents of the entity, 
	/// and returns those points as an instance of class AcDbExtents in the "extents" parameter
	/// </summary>
	/// <param name ="extents"> Output entity's extents </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus   subGetGeomExtents(AcDbExtents& extents) const;

    /// <summary>
	/// It finds the intersections of the entity pointed to by pEnt and all the edges of the bounding box of this entity.
	/// </summary>
	/// <param name ="pEnt"> Input entity with which "this" entity is to intersect </param>
	/// <param name ="intType"> Input type of intersection requested </param>
	/// <param name ="points"> Output with the points of intersection appended </param>
	/// <param name ="thisGsMarker"> Input GS marker of subentity of "this" entity that's involved in the intersection operation. Use the 0 default if not applicable </param>
	/// <param name ="otherGsMarker"> Input GS marker of subentity of the entity pointed to by pEnt that's involved in the intersection operation. Use the 0 default if not applicable </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus 
	subIntersectWith(const AcDbEntity* pEnt, AcDb::Intersect intType, AcGePoint3dArray& points, 
				  Adesk::GsMarker thisGsMarker = 0, Adesk::GsMarker otherGsMarker = 0) const;

	/// <summary>
	/// It finds the intersections of the entity pointed to by pEnt and all the edges of the bounding box of this entity.
	/// </summary>
	/// <param name ="pEnt"> Input entity with which "this" entity is to intersect </param>
	/// <param name ="intType"> Input type of intersection requested </param>
	/// <param name ="projPlane"> Input projection plane for the apparent intersection of the two entities </param>
	/// <param name ="points"> Output with the points of intersection appended </param>
	/// <param name ="thisGsMarker"> Input GS marker of subentity of "this" entity that's involved in the intersection operation. Use the 0 default if not applicable. </param>
	/// <param name ="otherGsMarker"> Input GS marker of subentity of the entity pointed to by pEnt that's involved in the intersection operation. Use the 0 default if not applicable.</param>
	/// <returns> Acad::ErrorStatus </returns>
	virtual Acad::ErrorStatus 
	subIntersectWith(const AcDbEntity* pEnt, AcDb::Intersect intType, const AcGePlane& projPlane, 
				  AcGePoint3dArray& points, Adesk::GsMarker thisGsMarker = 0, Adesk::GsMarker otherGsMarker = 0) const;

    /// <summary>
	/// This function provides a means by which AutoCAD and ObjectARX applications can ask the entity to apply a transformation matrix (xform) to itself.
	/// </summary>
	/// <param name ="xform"> Input transformation matrix to be applied to the entity </param>
	/// <returns> Acad::ErrorStatus </returns>
    virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d& xform);

    /// <summary>
    /// Undo
    /// </summary>
    virtual Acad::ErrorStatus applyPartialUndo  (AcDbDwgFiler* undoFiler,
                                                 AcRxClass*    classObj);

private:

   AcPpImpLineSegment* mpImpLineSegment;
};

