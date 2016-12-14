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


#include "extrudedPolygonIfc.h"


struct VECTOR3D {
	POINT3D			* point;
	VECTOR3D		* next;
};

struct POLYGON3D {
	VECTOR3D		* vector;
	VECTOR3D		* openingVector;
	POLYGON3D		* next;
};

struct SHELL {
	POLYGON3D		* polygon;
	SHELL			* next;
};


void	createIfcBRepShape(SHELL * shell);
void	createIfcBRepShape(SHELL * shell, double p0x, double p0y, double p1x, double p1y);


//
//
//		ShapeRepresentation
//
//


#ifdef WIN64
__int64	buildShapeRepresentationInstance(__int64 type, SHELL * shell);
#else
__int32	buildShapeRepresentationInstance(__int32 type, SHELL * shell);
#endif
