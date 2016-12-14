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


#include "baseIfc.h"

#define		AXIS_CURVE2D_REPRESENTATION			101
#define		BODY_BOUNDINGBOX_REPRESENTATION		111
#define		BODY_BREP_REPRESENTATION			112
#define		BODY_SWEPTSOLID_REPRESENTATION		113


#ifdef WIN64
#ifdef UNICODE
__int64	createIfcWall(wchar_t * pWallName, double xOffset, double yOffset, double zOffset);
__int64	createIfcWallStandardCase(wchar_t * pWallName, double xOffset, double yOffset, double zOffset);
__int64	createIfcOpeningElement(wchar_t * pOpeningElementName, double xOffset, double yOffset, double zOffset, bool representation);
__int64	createIfcOpeningElement(wchar_t * pOpeningElementName,
								double xRefDirection, double yRefDirection, double zRefDirection,
								double xAxis, double yAxis, double zAxis,
								double xOffset, double yOffset, double zOffset,
								bool representation);
__int64	createIfcWindow(wchar_t * pWindowName, double xOffset, double yOffset, double zOffset, bool insideOpening, double overallHeight, double overallWidth);
__int64	createIfcWindow(wchar_t * pWindowName,
						double xRefDirection, double yRefDirection, double zRefDirection,
						double xAxis, double yAxis, double zAxis,
						double xOffset, double yOffset, double zOffset,
						bool insideOpening,
						double overallHeight,
						double overallWidth);
#else
__int64	createIfcWall(char * pWallName, double xOffset, double yOffset, double zOffset);
__int64	createIfcWallStandardCase(char * pWallName, double xOffset, double yOffset, double zOffset);
__int64	createIfcOpeningElement(char * pOpeningElementName, double xOffset, double yOffset, double zOffset, bool representation);
__int64	createIfcOpeningElement(char * pOpeningElementName,
								double xRefDirection, double yRefDirection, double zRefDirection,
								double xAxis, double yAxis, double zAxis,
								double xOffset, double yOffset, double zOffset,
								bool representation);
__int64	createIfcWindow(char * pWindowName, double xOffset, double yOffset, double zOffset, bool insideOpening, double overallHeight, double overallWidth);
__int64	createIfcWindow(char * pWindowName,
						double xRefDirection, double yRefDirection, double zRefDirection,
						double xAxis, double yAxis, double zAxis,
						double xOffset, double yOffset, double zOffset,
						bool insideOpening,
						double overallHeight,
						double overallWidth);
#endif
#else
#ifdef UNICODE
__int32	createIfcWall(wchar_t * pWallName, double xOffset, double yOffset, double zOffset);
__int32	createIfcWallStandardCase(wchar_t * pWallName, double xOffset, double yOffset, double zOffset);
__int32	createIfcOpeningElement(wchar_t * pOpeningElementName, double xOffset, double yOffset, double zOffset, bool representation);
__int32	createIfcOpeningElement(wchar_t * pOpeningElementName,
								double xRefDirection, double yRefDirection, double zRefDirection,
								double xAxis, double yAxis, double zAxis,
								double xOffset, double yOffset, double zOffset,
								bool representation);
__int32	createIfcWindow(wchar_t * pWindowName, double xOffset, double yOffset, double zOffset, bool insideOpening, double overallHeight, double overallWidth);
__int32	createIfcWindow(wchar_t * pWindowName,
						double xRefDirection, double yRefDirection, double zRefDirection,
						double xAxis, double yAxis, double zAxis,
						double xOffset, double yOffset, double zOffset,
						bool insideOpening,
						double overallHeight,
						double overallWidth);
#else
__int32	createIfcWall(char * pWallName, double xOffset, double yOffset, double zOffset);
__int32	createIfcWallStandardCase(char * pWallName, double xOffset, double yOffset, double zOffset);
__int32	createIfcOpeningElement(char * pOpeningElementName, double xOffset, double yOffset, double zOffset, bool representation);
__int32	createIfcOpeningElement(char * pOpeningElementName,
								double xRefDirection, double yRefDirection, double zRefDirection,
								double xAxis, double yAxis, double zAxis,
								double xOffset, double yOffset, double zOffset,
								bool representation);
__int32	createIfcWindow(char * pWindowName, double xOffset, double yOffset, double zOffset, bool insideOpening, double overallHeight, double overallWidth);
__int32	createIfcWindow(char * pWindowName,
						double xRefDirection, double yRefDirection, double zRefDirection,
						double xAxis, double yAxis, double zAxis,
						double xOffset, double yOffset, double zOffset,
						bool insideOpening,
						double overallHeight,
						double overallWidth);
#endif
#endif


//
//
//		ProductDefinitionShape
//
//


#ifdef WIN64
__int64	buildProductDefinitionShapeInstance();
#else
__int32	buildProductDefinitionShapeInstance();
#endif


//
//
//		IfcWall, IfcWallStandardCase, IfcOpeningElement, IfcWindow
//
//


#ifdef WIN64
#ifdef UNICODE
__int64	buildWallInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcWallInstancePlacement, wchar_t * pWallName);
__int64	buildWallStandardCaseInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcWallInstancePlacement, wchar_t * pWallName);
__int64	buildOpeningElementInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcOpeningElementInstancePlacement, wchar_t * pOpeningElementName, bool representation);
__int64	buildWindowInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcWindowInstancePlacement, wchar_t * pWindowName, double overallHeight, double overallWidth);
#else
__int64	buildWallInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcWallInstancePlacement, char * pWallName);
__int64	buildWallStandardCaseInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcWallInstancePlacement, char * pWallName);
__int64	buildOpeningElementInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcOpeningElementInstancePlacement, char * pOpeningElementName, bool representation);
__int64	buildWindowInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcWindowInstancePlacement, char * pWindowName, double overallHeight, double overallWidth);
#endif
#else
#ifdef UNICODE
__int32	buildWallInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcWallInstancePlacement, wchar_t * pWallName);
__int32	buildWallStandardCaseInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcWallInstancePlacement, wchar_t * pWallName);
__int32	buildOpeningElementInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcOpeningElementInstancePlacement, wchar_t * pOpeningElementName, bool representation);
__int32	buildWindowInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcWindowInstancePlacement, wchar_t * pWindowName, double overallHeight, double overallWidth);
#else
__int32	buildWallInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcWallInstancePlacement, char * pWallName);
__int32	buildWallStandardCaseInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcWallInstancePlacement, char * pWallName);
__int32	buildOpeningElementInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcOpeningElementInstancePlacement, char * pOpeningElementName, bool representation);
__int32	buildWindowInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcWindowInstancePlacement, char * pWindowName, double overallHeight, double overallWidth);
#endif
#endif


//
//
//		RelVoidsElement, RelFillsElement
//
//


#ifdef WIN64
__int64	buildRelVoidsElementInstance(__int64 ifcBuildingElementInstance, __int64 ifcOpeningElementInstance);
__int64	buildRelFillsElementInstance(__int64 ifcOpeningElementInstance, __int64 ifcBuildingElementInstance);
#else
__int32	buildRelVoidsElementInstance(__int32 ifcBuildingElementInstance, __int32 ifcOpeningElementInstance);
__int32	buildRelFillsElementInstance(__int32 ifcOpeningElementInstance, __int32 ifcBuildingElementInstance);
#endif


//
//
//		ProjectLibrary, RelDeclares
//
//


#ifdef WIN64
__int64	buildProjectLibrary();
__int64	buildRelDeclares_ProjectLibrary(__int64 ifcProjectLibraryInstance);
__int64	buildRelDeclares_WallType(__int64 ifcWallTypeInstance);
#else
__int32	buildProjectLibrary();
__int32	buildRelDeclares_ProjectLibrary(__int32 ifcProjectLibraryInstance);
__int32	buildRelDeclares_WallType(__int32 ifcWallTypeInstance);
#endif


//
//
//		MaterialConstituentSet, MaterialConstituent
//
//


#ifdef WIN64
__int64	buildMaterialConstituentSet();
#ifdef UNICODE
__int64	buildMaterialConstituent(wchar_t * material);
#else
__int64	buildMaterialConstituent(char * material);
#endif
#else
__int32	buildMaterialConstituentSet();
#ifdef UNICODE
__int32	buildMaterialConstituent(wchar_t * material);
#else
__int32	buildMaterialConstituent(char * material);
#endif
#endif


//
//
//		RelAssociatesMaterial, MaterialLayerSetUsage, MaterialLayerSet, MaterialLayer
//
//


#ifdef WIN64
__int64	buildRelAssociatesMaterial(__int64 ifcBuildingElementInstance, double thickness);
__int64	buildRelAssociatesMaterial(__int64 ifcBuildingElementInstance);
__int64	buildMaterialLayerSetUsage(double thickness);
__int64	buildMaterialLayerSet(double thickness);
__int64	buildMaterialLayer(double thickness);
__int64	buildMaterial();
#ifdef UNICODE
__int64	buildMaterial(wchar_t * name);
#else
__int64	buildMaterial(char * name);
#endif
#else
__int32	buildRelAssociatesMaterial(__int32 ifcBuildingElementInstance, double thickness);
__int32	buildRelAssociatesMaterial(__int32 ifcBuildingElementInstance);
__int32	buildMaterialLayerSetUsage(double thickness);
__int32	buildMaterialLayerSet(double thickness);
__int32	buildMaterialLayer(double thickness);
__int32	buildMaterial();
#ifdef UNICODE
__int32	buildMaterial(wchar_t * name);
#else
__int32	buildMaterial(char * name);
#endif
#endif
