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


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "boundingBoxIfc.h"


struct	POINT2D {
	double			x;
	double			y;
};

struct	POLYGON2D {
	POINT2D			* point;
	POLYGON2D		* next;
};



void	createIfcExtrudedPolygonShape(POLYGON2D * polygon, double depth);
void	createIfcPolylineShape(double p0x, double p0y, double p1x, double p1y);


//
//
//		ShapeRepresentation
//
//


#ifdef WIN64
__int64	buildShapeRepresentationInstance(__int64 type, POLYGON2D * polygon, double depth);
__int64	buildShapeRepresentationInstance(__int64 type, double p0x, double p0y, double p1x, double p1y);
#else
__int32	buildShapeRepresentationInstance(__int32 type, POLYGON2D * polygon, double depth);
__int32	buildShapeRepresentationInstance(__int32 type, double p0x, double p0y, double p1x, double p1y);
#endif


//
//
//		ArbitraryClosedProfileDef, CartesianPoint(2D), ExtrudedAreaSolid, Polyline
//
//


#ifdef WIN64
__int64	buildArbitraryClosedProfileDefInstance(POLYGON2D * polygon);
__int64	buildCartesianPointInstance(double x, double y);
__int64	buildExtrudedAreaSolidInstance(POLYGON2D * polygon, double depth);
__int64	buildPolylineInstance(POLYGON2D * polygon);
__int64	buildPolylineInstance(double p0x, double p0y, double p1x, double p1y);
#else
__int32	buildArbitraryClosedProfileDefInstance(POLYGON2D * polygon);
__int32	buildCartesianPointInstance(double x, double y);
__int32	buildExtrudedAreaSolidInstance(POLYGON2D * polygon, double depth);
__int32	buildPolylineInstance(POLYGON2D * polygon);
__int32	buildPolylineInstance(double p0x, double p0y, double p1x, double p1y);
#endif
