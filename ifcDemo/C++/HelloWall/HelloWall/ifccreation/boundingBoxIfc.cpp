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
#include "boundingBoxIfc.h"
#include "extrudedPolygonIfc.h"

#ifdef WIN64
extern	__int64	model,
				* aggrRelatedElements,
				* aggrRepresentations,
				ifcBuildingStoreyInstancePlacement;
#else
extern	__int32	model,
				* aggrRelatedElements,
				* aggrRepresentations,
				ifcBuildingStoreyInstancePlacement;
#endif


#ifdef UNICODE
void	createIfcBoundingBoxShape(double width, double thickness, double height, wchar_t * representationIdentifier)
#else
void	createIfcBoundingBoxShape(double width, double thickness, double height, char * representationIdentifier)
#endif
{
	ASSERT(aggrRepresentations);

#ifdef WIN64
	sdaiAppend((__int64) aggrRepresentations, sdaiINSTANCE, (void*) buildShapeRepresentationInstance(BODY_BOUNDINGBOX_REPRESENTATION, width, thickness, height, representationIdentifier));
#else
	sdaiAppend((__int32) aggrRepresentations, sdaiINSTANCE, (void*) buildShapeRepresentationInstance(BODY_BOUNDINGBOX_REPRESENTATION, width, thickness, height, representationIdentifier));
#endif
}


//
//
//		BoundingBox, ShapeRepresentation
//
//


#ifdef WIN64
__int64	buildBoundingBoxInstance(double width, double thickness, double height)
#else
__int32	buildBoundingBoxInstance(double width, double thickness, double height)
#endif
{
#ifdef WIN64
	__int64	ifcBoundingBoxInstance;
#else
	__int32	ifcBoundingBoxInstance;
#endif

#ifdef UNICODE
	ifcBoundingBoxInstance = sdaiCreateInstanceBN(model, (char*) L"IFCBOUNDINGBOX");

	sdaiPutAttrBN(ifcBoundingBoxInstance, (char*) L"Corner", sdaiINSTANCE, (void*) buildCartesianPointInstance(0, 0, 0));
	sdaiPutAttrBN(ifcBoundingBoxInstance, (char*) L"XDim", sdaiREAL, &width);
	sdaiPutAttrBN(ifcBoundingBoxInstance, (char*) L"YDim", sdaiREAL, &thickness);
	sdaiPutAttrBN(ifcBoundingBoxInstance, (char*) L"ZDim", sdaiREAL, &height);
#else
	ifcBoundingBoxInstance = sdaiCreateInstanceBN(model, "IFCBOUNDINGBOX");

	sdaiPutAttrBN(ifcBoundingBoxInstance, "Corner", sdaiINSTANCE, (void*) buildCartesianPointInstance(0, 0, 0));
	sdaiPutAttrBN(ifcBoundingBoxInstance, "XDim", sdaiREAL, &width);
	sdaiPutAttrBN(ifcBoundingBoxInstance, "YDim", sdaiREAL, &thickness);
	sdaiPutAttrBN(ifcBoundingBoxInstance, "ZDim", sdaiREAL, &height);
#endif

	ASSERT(ifcBoundingBoxInstance);

	return	ifcBoundingBoxInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildShapeRepresentationInstance(__int64 type, double width, double thickness, double height, wchar_t * representationIdentifier)
#else
__int64	buildShapeRepresentationInstance(__int64 type, double width, double thickness, double height, char * representationIdentifier)
#endif
#else
#ifdef UNICODE
__int32	buildShapeRepresentationInstance(__int32 type, double width, double thickness, double height, wchar_t * representationIdentifier)
#else
__int32	buildShapeRepresentationInstance(__int32 type, double width, double thickness, double height, char * representationIdentifier)
#endif
#endif
{
#ifdef WIN64
	__int64	ifcShapeRepresentationInstance, * aggrItems;
#else
	__int32	ifcShapeRepresentationInstance, * aggrItems;
#endif

#ifdef UNICODE
	ifcShapeRepresentationInstance = sdaiCreateInstanceBN(model, (char*) L"IFCSHAPEREPRESENTATION");

	sdaiPutAttrBN(ifcShapeRepresentationInstance, (char*) L"ContextOfItems", sdaiINSTANCE, (void*) getGeometricRepresentationContextInstance());
#else
	ifcShapeRepresentationInstance = sdaiCreateInstanceBN(model, "IFCSHAPEREPRESENTATION");

	sdaiPutAttrBN(ifcShapeRepresentationInstance, "ContextOfItems", sdaiINSTANCE, (void*) getGeometricRepresentationContextInstance());
#endif
	switch  (type) {
		case  BODY_BOUNDINGBOX_REPRESENTATION:
#ifdef UNICODE
			aggrItems = sdaiCreateAggrBN(ifcShapeRepresentationInstance, (char*) L"Items");
			sdaiPutAttrBN(ifcShapeRepresentationInstance, (char*) L"RepresentationIdentifier", sdaiUNICODE, representationIdentifier);
			sdaiPutAttrBN(ifcShapeRepresentationInstance, (char*) L"RepresentationType", sdaiUNICODE, L"BoundingBox");
#else
			aggrItems = sdaiCreateAggrBN(ifcShapeRepresentationInstance, "Items");
			sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationIdentifier", sdaiSTRING, representationIdentifier);
			sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationType", sdaiSTRING, "BoundingBox");
#endif
#ifdef WIN64
			sdaiAppend((__int64) aggrItems, sdaiINSTANCE, (void*) buildBoundingBoxInstance(width, thickness, height));
#else
			sdaiAppend((__int32) aggrItems, sdaiINSTANCE, (void*) buildBoundingBoxInstance(width, thickness, height));
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
//		CartesianPoint(3D)
//
//



#ifdef WIN64
__int64	buildCartesianPointInstance(double x, double y, double z)
#else
__int32	buildCartesianPointInstance(double x, double y, double z)
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
	sdaiAppend((__int64) aggrCoordinates, sdaiREAL, &z);
#else
	sdaiAppend((__int32) aggrCoordinates, sdaiREAL, &x);
	sdaiAppend((__int32) aggrCoordinates, sdaiREAL, &y);
	sdaiAppend((__int32) aggrCoordinates, sdaiREAL, &z);
#endif

	ASSERT(ifcCartesianPointInstance);

	return	ifcCartesianPointInstance;
}
