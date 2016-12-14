////////////////////////////////////////////////////////////////////////
//	Author:		Peter Bonsma
//	Date:		20 February 2015
//	Project:	IFC Engine Series (example using DLL)
//
//	This code may be used and edited freely,
//	also for commercial projects in open and closed source software
//
//	In case of use of the DLL:
//	be aware of license fee for use of this DLL when used commercially
//	more info for commercial use:	contact@rdf.bg
//
//	more info for using the IFC Engine DLL in other languages
//	and creation of specific code examples:
//									peter.bonsma@rdf.bg
////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "extrudedPolygonIfc.h"


#ifdef WIN64
	extern	__int64	model,
					* aggrRelatedElements,
					* aggrRepresentations;
#else
	extern	__int32	model,
					* aggrRelatedElements,
					* aggrRepresentations;
#endif
	

void	createIfcExtrudedPolygonShape(POLYGON2D * polygon, double depth)
{
	ASSERT(aggrRepresentations);

#ifdef WIN64
	sdaiAppend((__int64) aggrRepresentations, sdaiINSTANCE, (void*) buildShapeRepresentationInstance(BODY_SWEPTSOLID_REPRESENTATION, polygon, depth));
#else
	sdaiAppend((__int32) aggrRepresentations, sdaiINSTANCE, (void*) buildShapeRepresentationInstance(BODY_SWEPTSOLID_REPRESENTATION, polygon, depth));
#endif
}

void	createIfcPolylineShape(double p0x, double p0y, double p1x, double p1y)
{
	ASSERT(aggrRepresentations);

#ifdef WIN64
	sdaiAppend((__int64) aggrRepresentations, sdaiINSTANCE, (void*) buildShapeRepresentationInstance(AXIS_CURVE2D_REPRESENTATION, p0x, p0y, p1x, p1y));
#else
	sdaiAppend((__int32) aggrRepresentations, sdaiINSTANCE, (void*) buildShapeRepresentationInstance(AXIS_CURVE2D_REPRESENTATION, p0x, p0y, p1x, p1y));
#endif
}


//
//
//		ShapeRepresentation
//
//


#ifdef WIN64
__int64	buildShapeRepresentationInstance(__int64 type, POLYGON2D * polygon, double depth)
#else
__int32	buildShapeRepresentationInstance(__int32 type, POLYGON2D * polygon, double depth)
#endif
{
#ifdef WIN64
	__int64	ifcShapeRepresentationInstance, * aggrItems;
#else
	__int32	ifcShapeRepresentationInstance, * aggrItems;
#endif

#ifdef UNICODE
	ifcShapeRepresentationInstance = sdaiCreateInstanceBN(model, (char*) L"IFCSHAPEREPRESENTATION");

	aggrItems = sdaiCreateAggrBN(ifcShapeRepresentationInstance, (char*) L"Items");
#else
	ifcShapeRepresentationInstance = sdaiCreateInstanceBN(model, "IFCSHAPEREPRESENTATION");

	aggrItems = sdaiCreateAggrBN(ifcShapeRepresentationInstance, "Items");
#endif
	switch	(type) {
		case  BODY_SWEPTSOLID_REPRESENTATION:
#ifdef WIN64
			sdaiAppend((__int64) aggrItems, sdaiINSTANCE, (void*) buildExtrudedAreaSolidInstance(polygon, depth));
#else
			sdaiAppend((__int32) aggrItems, sdaiINSTANCE, (void*) buildExtrudedAreaSolidInstance(polygon, depth));
#endif

#ifdef UNICODE
			sdaiPutAttrBN(ifcShapeRepresentationInstance, (char*) L"RepresentationIdentifier", sdaiUNICODE, L"Body");
			sdaiPutAttrBN(ifcShapeRepresentationInstance, (char*) L"RepresentationType", sdaiUNICODE, L"SweptSolid");
			sdaiPutAttrBN(ifcShapeRepresentationInstance, (char*) L"ContextOfItems", sdaiINSTANCE, (void*) getGeometricRepresentationContextInstance());
#else
			sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationIdentifier", sdaiSTRING, "Body");
			sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationType", sdaiSTRING, "SweptSolid");
			sdaiPutAttrBN(ifcShapeRepresentationInstance, "ContextOfItems", sdaiINSTANCE, (void*) getGeometricRepresentationContextInstance());
#endif
			break;
		default:
			ASSERT(false);
			break;
	}

	ASSERT(ifcShapeRepresentationInstance);

	return	ifcShapeRepresentationInstance;
}

#ifdef WIN64
__int64	buildShapeRepresentationInstance(__int64 type, double p0x, double p0y, double p1x, double p1y)
#else
__int32	buildShapeRepresentationInstance(__int32 type, double p0x, double p0y, double p1x, double p1y)
#endif
{
#ifdef WIN64
	__int64	ifcShapeRepresentationInstance, * aggrItems;
#else
	__int32	ifcShapeRepresentationInstance, * aggrItems;
#endif

#ifdef UNICODE
	ifcShapeRepresentationInstance = sdaiCreateInstanceBN(model, (char*) L"IFCSHAPEREPRESENTATION");

	aggrItems = sdaiCreateAggrBN(ifcShapeRepresentationInstance, (char*) L"Items");
#else
	ifcShapeRepresentationInstance = sdaiCreateInstanceBN(model, "IFCSHAPEREPRESENTATION");

	aggrItems = sdaiCreateAggrBN(ifcShapeRepresentationInstance, "Items");
#endif
	switch  (type) {
		case  AXIS_CURVE2D_REPRESENTATION:
#ifdef WIN64
			sdaiAppend((__int64) aggrItems, sdaiINSTANCE, (void*) buildPolylineInstance(p0x, p0y, p1x, p1y));
#else
			sdaiAppend((__int32) aggrItems, sdaiINSTANCE, (void*) buildPolylineInstance(p0x, p0y, p1x, p1y));
#endif

#ifdef UNICODE
			sdaiPutAttrBN(ifcShapeRepresentationInstance, (char*) L"RepresentationIdentifier", sdaiUNICODE, L"Axis");
			sdaiPutAttrBN(ifcShapeRepresentationInstance, (char*) L"RepresentationType", sdaiUNICODE, L"Curve2D");
			sdaiPutAttrBN(ifcShapeRepresentationInstance, (char*) L"ContextOfItems", sdaiINSTANCE, (void*) getGeometricRepresentationContextInstance());
#else
			sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationIdentifier", sdaiSTRING, "Axis");
			sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationType", sdaiSTRING, "Curve2D");
			sdaiPutAttrBN(ifcShapeRepresentationInstance, "ContextOfItems", sdaiINSTANCE, (void*) getGeometricRepresentationContextInstance());
#endif
			break;
		default:
			ASSERT(false);
			break;
	}

	ASSERT(ifcShapeRepresentationInstance);

	return	ifcShapeRepresentationInstance;
}


//
//
//		ArbitraryClosedProfileDef, CartesianPoint(2D), ExtrudedAreaSolid, Polyline
//
//


#ifdef WIN64
__int64	buildArbitraryClosedProfileDefInstance(POLYGON2D * polygon)
#else
__int32	buildArbitraryClosedProfileDefInstance(POLYGON2D * polygon)
#endif
{
#ifdef WIN64
	__int64	ifcArbitraryClosedProfileDefInstance;
#else
	__int32	ifcArbitraryClosedProfileDefInstance;
#endif

#ifdef UNICODE
	ifcArbitraryClosedProfileDefInstance = sdaiCreateInstanceBN(model, (char*) L"IFCARBITRARYCLOSEDPROFILEDEF");

	sdaiPutAttrBN(ifcArbitraryClosedProfileDefInstance, (char*) L"ProfileType", sdaiENUM, L"AREA");
	sdaiPutAttrBN(ifcArbitraryClosedProfileDefInstance, (char*) L"OuterCurve", sdaiINSTANCE, (void*) buildPolylineInstance(polygon));
#else
	ifcArbitraryClosedProfileDefInstance = sdaiCreateInstanceBN(model, "IFCARBITRARYCLOSEDPROFILEDEF");

	sdaiPutAttrBN(ifcArbitraryClosedProfileDefInstance, "ProfileType", sdaiENUM, "AREA");
	sdaiPutAttrBN(ifcArbitraryClosedProfileDefInstance, "OuterCurve", sdaiINSTANCE, (void*) buildPolylineInstance(polygon));
#endif

	ASSERT(ifcArbitraryClosedProfileDefInstance);

	return	ifcArbitraryClosedProfileDefInstance;
}

#ifdef WIN64
__int64	buildCartesianPointInstance(double x, double y)
#else
__int32	buildCartesianPointInstance(double x, double y)
#endif
{
#ifdef WIN64
	__int64	ifcCartesianPointInstance, * aggrCoordinates;
#else
	__int32	ifcCartesianPointInstance, * aggrCoordinates;
#endif

#ifdef UNICODE
	ifcCartesianPointInstance = sdaiCreateInstanceBN(model, (char*) L"IFCCARTESIANPOINT");

	aggrCoordinates = sdaiCreateAggrBN(ifcCartesianPointInstance, (char*) L"Coordinates");
#else
	ifcCartesianPointInstance = sdaiCreateInstanceBN(model, "IFCCARTESIANPOINT");

	aggrCoordinates = sdaiCreateAggrBN(ifcCartesianPointInstance, "Coordinates");
#endif
#ifdef WIN64
	sdaiAppend((__int64) aggrCoordinates, sdaiREAL, &x);
	sdaiAppend((__int64) aggrCoordinates, sdaiREAL, &y);
#else
	sdaiAppend((__int32) aggrCoordinates, sdaiREAL, &x);
	sdaiAppend((__int32) aggrCoordinates, sdaiREAL, &y);
#endif

	ASSERT(ifcCartesianPointInstance);

	return	ifcCartesianPointInstance;
}

#ifdef WIN64
__int64	buildExtrudedAreaSolidInstance(POLYGON2D * polygon, double depth)
#else
__int32	buildExtrudedAreaSolidInstance(POLYGON2D * polygon, double depth)
#endif
{
	MATRIX	matrix;
#ifdef WIN64
	__int64	ifcExtrudedAreaSolidInstance;
#else
	__int32	ifcExtrudedAreaSolidInstance;
#endif

	identityMatrix(&matrix);

#ifdef UNICODE
	ifcExtrudedAreaSolidInstance = sdaiCreateInstanceBN(model, (char*) L"IFCEXTRUDEDAREASOLID");

	sdaiPutAttrBN(ifcExtrudedAreaSolidInstance, (char*) L"SweptArea", sdaiINSTANCE, (void*) buildArbitraryClosedProfileDefInstance(polygon));
	sdaiPutAttrBN(ifcExtrudedAreaSolidInstance, (char*) L"Position", sdaiINSTANCE, (void*) buildAxis2Placement3DInstance(&matrix));
	sdaiPutAttrBN(ifcExtrudedAreaSolidInstance, (char*) L"ExtrudedDirection", sdaiINSTANCE, (void*) buildDirectionInstance((POINT3D*) &matrix._31));
	sdaiPutAttrBN(ifcExtrudedAreaSolidInstance, (char*) L"Depth", sdaiREAL, (void *) &depth);
#else
	ifcExtrudedAreaSolidInstance = sdaiCreateInstanceBN(model, "IFCEXTRUDEDAREASOLID");

	sdaiPutAttrBN(ifcExtrudedAreaSolidInstance, "SweptArea", sdaiINSTANCE, (void*) buildArbitraryClosedProfileDefInstance(polygon));
	sdaiPutAttrBN(ifcExtrudedAreaSolidInstance, "Position", sdaiINSTANCE, (void*) buildAxis2Placement3DInstance(&matrix));
	sdaiPutAttrBN(ifcExtrudedAreaSolidInstance, "ExtrudedDirection", sdaiINSTANCE, (void*) buildDirectionInstance((POINT3D*) &matrix._31));
	sdaiPutAttrBN(ifcExtrudedAreaSolidInstance, "Depth", sdaiREAL, (void *) &depth);
#endif

	ASSERT(ifcExtrudedAreaSolidInstance);

	return	ifcExtrudedAreaSolidInstance;
}

#ifdef WIN64
__int64	buildPolylineInstance(POLYGON2D * polygon)
#else
__int32	buildPolylineInstance(POLYGON2D * polygon)
#endif
{
#ifdef WIN64
	__int64	ifcPolylineInstance, * aggrPoints;
#else
	__int32	ifcPolylineInstance, * aggrPoints;
#endif

#ifdef UNICODE
	ifcPolylineInstance = sdaiCreateInstanceBN(model, (char*) L"IFCPOLYLINE");

	aggrPoints = sdaiCreateAggrBN(ifcPolylineInstance, (char*) L"Points");
#else
	ifcPolylineInstance = sdaiCreateInstanceBN(model, "IFCPOLYLINE");

	aggrPoints = sdaiCreateAggrBN(ifcPolylineInstance, "Points");
#endif
	double	x = polygon->point->x,
			y = polygon->point->y;
	while  (polygon) {
#ifdef WIN64
		sdaiAppend((__int64) aggrPoints, sdaiINSTANCE, (void*) buildCartesianPointInstance(polygon->point->x, polygon->point->y));
#else
		sdaiAppend((__int32) aggrPoints, sdaiINSTANCE, (void*) buildCartesianPointInstance(polygon->point->x, polygon->point->y));
#endif
		polygon = polygon->next;
	}
#ifdef WIN64
	sdaiAppend((__int64) aggrPoints, sdaiINSTANCE, (void*) buildCartesianPointInstance(x, y));
#else
	sdaiAppend((__int32) aggrPoints, sdaiINSTANCE, (void*) buildCartesianPointInstance(x, y));
#endif

	ASSERT(ifcPolylineInstance);

	return	ifcPolylineInstance;
}

#ifdef WIN64
__int64	buildPolylineInstance(double p0x, double p0y, double p1x, double p1y)
#else
__int32	buildPolylineInstance(double p0x, double p0y, double p1x, double p1y)
#endif
{
#ifdef WIN64
	__int64	ifcPolylineInstance, * aggrPoints;
#else
	__int32	ifcPolylineInstance, * aggrPoints;
#endif

#ifdef UNICODE
	ifcPolylineInstance = sdaiCreateInstanceBN(model, (char*) L"IFCPOLYLINE");

	aggrPoints = sdaiCreateAggrBN(ifcPolylineInstance, (char*) L"Points");
#else
	ifcPolylineInstance = sdaiCreateInstanceBN(model, "IFCPOLYLINE");

	aggrPoints = sdaiCreateAggrBN(ifcPolylineInstance, "Points");
#endif
#ifdef WIN64
	sdaiAppend((__int64) aggrPoints, sdaiINSTANCE, (void*) buildCartesianPointInstance(p0x, p0y));
	sdaiAppend((__int64) aggrPoints, sdaiINSTANCE, (void*) buildCartesianPointInstance(p1x, p1y));
#else
	sdaiAppend((__int32) aggrPoints, sdaiINSTANCE, (void*) buildCartesianPointInstance(p0x, p0y));
	sdaiAppend((__int32) aggrPoints, sdaiINSTANCE, (void*) buildCartesianPointInstance(p1x, p1y));
#endif

	ASSERT(ifcPolylineInstance);

	return	ifcPolylineInstance;
}
