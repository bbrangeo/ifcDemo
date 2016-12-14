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
#include "BRepIfc.h"


#ifdef WIN64
	extern	__int64	model,
					* aggrRelatedElements,
					* aggrRepresentations;
#else
	extern	__int32	model,
					* aggrRelatedElements,
					* aggrRepresentations;
#endif


void	createIfcBRepShape(SHELL * shell)
{
	ASSERT(aggrRepresentations);

#ifdef WIN64
	sdaiAppend((__int64) aggrRepresentations, sdaiINSTANCE, (void*) buildShapeRepresentationInstance(BODY_BREP_REPRESENTATION, shell));
#else
	sdaiAppend((__int32) aggrRepresentations, sdaiINSTANCE, (void*) buildShapeRepresentationInstance(BODY_BREP_REPRESENTATION, shell));
#endif
}

void	createIfcBRepShape(SHELL * shell, double p0x, double p0y, double p1x, double p1y)
{
	ASSERT(aggrRepresentations);

#ifdef WIN64
	sdaiAppend((__int64) aggrRepresentations, sdaiINSTANCE, (void*) buildShapeRepresentationInstance(AXIS_CURVE2D_REPRESENTATION, p0x, p0y, p1x, p1y));
	sdaiAppend((__int64) aggrRepresentations, sdaiINSTANCE, (void*) buildShapeRepresentationInstance(BODY_BREP_REPRESENTATION, shell));
#else
	sdaiAppend((__int32) aggrRepresentations, sdaiINSTANCE, (void*) buildShapeRepresentationInstance(AXIS_CURVE2D_REPRESENTATION, p0x, p0y, p1x, p1y));
	sdaiAppend((__int32) aggrRepresentations, sdaiINSTANCE, (void*) buildShapeRepresentationInstance(BODY_BREP_REPRESENTATION, shell));
#endif
}


//
//
//		ShapeRepresentation
//
//


#ifdef WIN64
__int64	buildShapeRepresentationInstance(__int64 type, SHELL * shell)
#else
__int32	buildShapeRepresentationInstance(__int32 type, SHELL * shell)
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
		case  BODY_BREP_REPRESENTATION:
#ifdef UNICODE
			sdaiPutAttrBN(ifcShapeRepresentationInstance, (char*) L"RepresentationIdentifier", sdaiUNICODE, L"Body");
			sdaiPutAttrBN(ifcShapeRepresentationInstance, (char*) L"RepresentationType", sdaiUNICODE, L"Brep");
			sdaiPutAttrBN(ifcShapeRepresentationInstance, (char*) L"ContextOfItems", sdaiINSTANCE, (void*) getGeometricRepresentationContextInstance());
#else
			sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationIdentifier", sdaiSTRING, "Body");
			sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationType", sdaiSTRING, "Brep");
			sdaiPutAttrBN(ifcShapeRepresentationInstance, "ContextOfItems", sdaiINSTANCE, (void*) getGeometricRepresentationContextInstance());
#endif

			while  (shell) {
				POLYGON3D	* polygon = shell->polygon;
#ifdef WIN64
				__int64	ifcFacetedBrepInstance, ifcClosedShellInstance, * aggrCfsFaces;
#else
				__int32	ifcFacetedBrepInstance, ifcClosedShellInstance, * aggrCfsFaces;
#endif

#ifdef UNICODE
				ifcClosedShellInstance = sdaiCreateInstanceBN(model, (char*) L"IFCCLOSEDSHELL");
				aggrCfsFaces = sdaiCreateAggrBN(ifcClosedShellInstance, (char*) L"CfsFaces");
#else
				ifcClosedShellInstance = sdaiCreateInstanceBN(model, "IFCCLOSEDSHELL");
				aggrCfsFaces = sdaiCreateAggrBN(ifcClosedShellInstance, "CfsFaces");
#endif

				while  (polygon) {
					VECTOR3D	* vector = polygon->vector;
#ifdef WIN64
					__int64	ifcPolyLoopInstance, * aggrPolygon,
							ifcFaceOuterBoundInstance,
							ifcFaceInstance, * aggrBounds;
#else
					__int32	ifcPolyLoopInstance, * aggrPolygon,
							ifcFaceOuterBoundInstance,
							ifcFaceInstance, * aggrBounds;
#endif

#ifdef UNICODE
					ifcPolyLoopInstance = sdaiCreateInstanceBN(model, (char*) L"IFCPOLYLOOP");
					aggrPolygon = sdaiCreateAggrBN(ifcPolyLoopInstance, (char*) L"Polygon");
#else
					ifcPolyLoopInstance = sdaiCreateInstanceBN(model, "IFCPOLYLOOP");
					aggrPolygon = sdaiCreateAggrBN(ifcPolyLoopInstance, "Polygon");
#endif

					while  (vector) {
						POINT3D	* point = vector->point;
						//
						//	Check if point is already written
						//
						if	(!point->ifcCartesianPointInstance) {
							point->ifcCartesianPointInstance = buildCartesianPointInstance(point->x, point->y, point->z);
						}

#ifdef WIN64
						sdaiAppend((__int64) aggrPolygon, sdaiINSTANCE, (void *) point->ifcCartesianPointInstance);
#else
						sdaiAppend((__int32) aggrPolygon, sdaiINSTANCE, (void *) point->ifcCartesianPointInstance);
#endif
						vector = vector->next;
					}

#ifdef UNICODE
					ifcFaceOuterBoundInstance = sdaiCreateInstanceBN(model, (char*) L"IFCFACEOUTERBOUND");
					sdaiPutAttrBN(ifcFaceOuterBoundInstance, (char*) L"Bound", sdaiINSTANCE, (void *) ifcPolyLoopInstance);
					sdaiPutAttrBN(ifcFaceOuterBoundInstance, (char*) L"Orientation", sdaiENUM, L"T");

					ifcFaceInstance = sdaiCreateInstanceBN(model, (char*) L"IFCFACE");
					aggrBounds = sdaiCreateAggrBN(ifcFaceInstance, (char*) L"Bounds");
#else
					ifcFaceOuterBoundInstance = sdaiCreateInstanceBN(model, "IFCFACEOUTERBOUND");
					sdaiPutAttrBN(ifcFaceOuterBoundInstance, "Bound", sdaiINSTANCE, (void *) ifcPolyLoopInstance);
					sdaiPutAttrBN(ifcFaceOuterBoundInstance, "Orientation", sdaiENUM, "T");

					ifcFaceInstance = sdaiCreateInstanceBN(model, "IFCFACE");
					aggrBounds = sdaiCreateAggrBN(ifcFaceInstance, "Bounds");
#endif
#ifdef WIN64
					sdaiAppend((__int64) aggrBounds, sdaiINSTANCE, (void *) ifcFaceOuterBoundInstance);

					sdaiAppend((__int64) aggrCfsFaces, sdaiINSTANCE, (void *) ifcFaceInstance);
#else
					sdaiAppend((__int32) aggrBounds, sdaiINSTANCE, (void *) ifcFaceOuterBoundInstance);

					sdaiAppend((__int32) aggrCfsFaces, sdaiINSTANCE, (void *) ifcFaceInstance);
#endif

					if	(polygon->openingVector) {
#ifdef WIN64
						__int64	ifcFaceBoundInstance;
#else
						__int32	ifcFaceBoundInstance;
#endif

						vector = polygon->openingVector;

#ifdef UNICODE
						ifcPolyLoopInstance = sdaiCreateInstanceBN(model, (char*) L"IFCPOLYLOOP");
						aggrPolygon = sdaiCreateAggrBN(ifcPolyLoopInstance, (char*) L"Polygon");
#else
						ifcPolyLoopInstance = sdaiCreateInstanceBN(model, "IFCPOLYLOOP");
						aggrPolygon = sdaiCreateAggrBN(ifcPolyLoopInstance, "Polygon");
#endif

						while  (vector) {
							POINT3D	* point = vector->point;
							//
							//	Check if point is already written
							//
							if	(!point->ifcCartesianPointInstance) {
								point->ifcCartesianPointInstance = buildCartesianPointInstance(point->x, point->y, point->z);
							}

#ifdef WIN64
							sdaiAppend((__int64) aggrPolygon, sdaiINSTANCE, (void *) point->ifcCartesianPointInstance);
#else
							sdaiAppend((__int32) aggrPolygon, sdaiINSTANCE, (void *) point->ifcCartesianPointInstance);
#endif

							vector = vector->next;
						}

#ifdef UNICODE
						ifcFaceBoundInstance = sdaiCreateInstanceBN(model, (char*) L"IFCFACEBOUND");
						sdaiPutAttrBN(ifcFaceBoundInstance, (char*) L"Bound", sdaiINSTANCE, (void *) ifcPolyLoopInstance);
						sdaiPutAttrBN(ifcFaceBoundInstance, (char*) L"Orientation", sdaiENUM, L"T");
#else
						ifcFaceBoundInstance = sdaiCreateInstanceBN(model, "IFCFACEBOUND");
						sdaiPutAttrBN(ifcFaceBoundInstance, "Bound", sdaiINSTANCE, (void *) ifcPolyLoopInstance);
						sdaiPutAttrBN(ifcFaceBoundInstance, "Orientation", sdaiENUM, "T");
#endif

#ifdef WIN64
						sdaiAppend((__int64) aggrBounds, sdaiINSTANCE, (void *) ifcFaceBoundInstance);
#else
						sdaiAppend((__int32) aggrBounds, sdaiINSTANCE, (void *) ifcFaceBoundInstance);
#endif
					}

					polygon = polygon->next;
				}

#ifdef UNICODE
				ifcFacetedBrepInstance = sdaiCreateInstanceBN(model, (char*) L"IFCFACETEDBREP");
				sdaiPutAttrBN(ifcFacetedBrepInstance, (char*) L"Outer", sdaiINSTANCE, (void *) ifcClosedShellInstance);
#else
				ifcFacetedBrepInstance = sdaiCreateInstanceBN(model, "IFCFACETEDBREP");
				sdaiPutAttrBN(ifcFacetedBrepInstance, "Outer", sdaiINSTANCE, (void *) ifcClosedShellInstance);
#endif

#ifdef WIN64
				sdaiAppend((__int64) aggrItems, sdaiINSTANCE, (void*) ifcFacetedBrepInstance);
#else
				sdaiAppend((__int32) aggrItems, sdaiINSTANCE, (void*) ifcFacetedBrepInstance);
#endif

				shell = shell->next;
			}
			break;
		default:
			ASSERT(false);
			break;
	}

	ASSERT(ifcShapeRepresentationInstance);

	return	ifcShapeRepresentationInstance;
}
