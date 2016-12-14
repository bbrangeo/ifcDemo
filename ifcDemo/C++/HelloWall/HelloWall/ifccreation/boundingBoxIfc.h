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


#include "baseIfcObject.h"


#ifdef UNICODE
void	createIfcBoundingBoxShape(double width, double thickness, double height, wchar_t * representationIdentifier);
#else
void	createIfcBoundingBoxShape(double width, double thickness, double height, char * representationIdentifier);
#endif


//
//
//		BoundingBox, ShapeRepresentation
//
//


#ifdef WIN64
__int64	buildBoundingBoxInstance(double width, double thickness, double height);
#ifdef UNICODE
__int64	buildShapeRepresentationInstance(__int64 type, double width, double thickness, double height, wchar_t * representationIdentifier);
#else
__int64	buildShapeRepresentationInstance(__int64 type, double width, double thickness, double height, char * representationIdentifier);
#endif
#else
__int32	buildBoundingBoxInstance(double width, double thickness, double height);
#ifdef UNICODE
__int32	buildShapeRepresentationInstance(__int32 type, double width, double thickness, double height, wchar_t * representationIdentifier);
#else
__int32	buildShapeRepresentationInstance(__int32 type, double width, double thickness, double height, char * representationIdentifier);
#endif
#endif


//
//
//		CartesianPoint(3D)
//
//


#ifdef WIN64
__int64	buildCartesianPointInstance(double x, double y, double z);
#else
__int32	buildCartesianPointInstance(double x, double y, double z);
#endif
