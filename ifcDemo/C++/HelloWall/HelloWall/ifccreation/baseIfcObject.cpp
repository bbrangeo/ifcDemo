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
#include "baseIfcObject.h"

#ifdef WIN64
extern	__int64	model,
				* aggrRelatedElements,
				* aggr_ifcRelDeclaresInstance_RelatedDefinitions_ProjectLibrary,
				ifcBuildingInstancePlacement,
				ifcBuildingStoreyInstancePlacement,
				ifcProjectInstance,
				ifcRelDeclaresInstance;

__int64			* aggrRepresentations,
				ifcOpeningElementInstancePlacement,
				ifcWallInstancePlacement,
				* aggr_ifcRelDeclaresInstance_RelatedDefinitions;
#else
extern	__int32	model,
				* aggrRelatedElements,
				* aggr_ifcRelDeclaresInstance_RelatedDefinitions_ProjectLibrary,
				ifcBuildingInstancePlacement,
				ifcBuildingStoreyInstancePlacement,
				ifcProjectInstance,
				ifcRelDeclaresInstance;

__int32			* aggrRepresentations,
				ifcOpeningElementInstancePlacement,
				ifcWallInstancePlacement,
				* aggr_ifcRelDeclaresInstance_RelatedDefinitions;
#endif


#ifdef	WIN64
#ifdef	UNICODE
__int64	createIfcWall(wchar_t * pWallName, double xOffset, double yOffset, double zOffset)
#else
__int64	createIfcWall(char * pWallName, double xOffset, double yOffset, double zOffset)
#endif
#else
#ifdef	UNICODE
__int32	createIfcWall(wchar_t * pWallName, double xOffset, double yOffset, double zOffset)
#else
__int32	createIfcWall(char * pWallName, double xOffset, double yOffset, double zOffset)
#endif
#endif
{
	MATRIX	matrix;
#ifdef	WIN64
	__int64	ifcWallInstance;
#else
	__int32	ifcWallInstance;
#endif

	identityMatrix(&matrix);
	matrix._41 = xOffset;
	matrix._42 = yOffset;
	matrix._43 = zOffset;

	//
	//		Build Wall and add it to the BuildingStorey
	//
	ifcWallInstance = buildWallInstance(&matrix, ifcBuildingStoreyInstancePlacement, &ifcWallInstancePlacement, pWallName);
#ifdef	WIN64
	sdaiAppend((__int64) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWallInstance);
#else
	sdaiAppend((__int32) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWallInstance);
#endif

	ASSERT(ifcWallInstance);

	return	ifcWallInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	createIfcWallStandardCase(wchar_t * pWallName, double xOffset, double yOffset, double zOffset)
#else
__int64	createIfcWallStandardCase(char * pWallName, double xOffset, double yOffset, double zOffset)
#endif
#else
#ifdef UNICODE
__int32	createIfcWallStandardCase(wchar_t * pWallName, double xOffset, double yOffset, double zOffset)
#else
__int32	createIfcWallStandardCase(char * pWallName, double xOffset, double yOffset, double zOffset)
#endif
#endif
{
	MATRIX	matrix;
#ifdef WIN64
	__int64	ifcWallStandardCaseInstance;
#else
	__int32	ifcWallStandardCaseInstance;
#endif

	identityMatrix(&matrix);
	matrix._41 = xOffset;
	matrix._42 = yOffset;
	matrix._43 = zOffset;

	//
	//		Build Wall and add it to the BuildingStorey
	//
	ifcWallStandardCaseInstance = buildWallStandardCaseInstance(&matrix, ifcBuildingStoreyInstancePlacement, &ifcWallInstancePlacement, pWallName);
#ifdef WIN64
	sdaiAppend((__int64) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWallStandardCaseInstance);
#else
	sdaiAppend((__int32) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWallStandardCaseInstance);
#endif

	ASSERT(ifcWallStandardCaseInstance);

	return	ifcWallStandardCaseInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	createIfcOpeningElement(wchar_t * pOpeningElementName, double xOffset, double yOffset, double zOffset, bool representation)
#else
__int64	createIfcOpeningElement(char * pOpeningElementName, double xOffset, double yOffset, double zOffset, bool representation)
#endif
#else
#ifdef UNICODE
__int32	createIfcOpeningElement(wchar_t * pOpeningElementName, double xOffset, double yOffset, double zOffset, bool representation)
#else
__int32	createIfcOpeningElement(char * pOpeningElementName, double xOffset, double yOffset, double zOffset, bool representation)
#endif
#endif
{
	MATRIX	matrix;
#ifdef WIN64
	__int64	ifcOpeningElementInstance;
#else
	__int32	ifcOpeningElementInstance;
#endif

	identityMatrix(&matrix);
	matrix._41 = xOffset;
	matrix._42 = yOffset;
	matrix._43 = zOffset;

	//
	//		Build Opening Element
	//
	ifcOpeningElementInstance = buildOpeningElementInstance(&matrix, ifcWallInstancePlacement, &ifcOpeningElementInstancePlacement, pOpeningElementName, representation);

	ASSERT(ifcOpeningElementInstance);

	return	ifcOpeningElementInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	createIfcOpeningElement(wchar_t * pOpeningElementName,
#else
__int64	createIfcOpeningElement(char * pOpeningElementName,
#endif
#else
#ifdef UNICODE
__int32	createIfcOpeningElement(wchar_t * pOpeningElementName,
#else
__int32	createIfcOpeningElement(char * pOpeningElementName,
#endif
#endif
								double xRefDirection, double yRefDirection, double zRefDirection,
								double xAxis, double yAxis, double zAxis,
								double xOffset, double yOffset, double zOffset,
								bool representation)
{
	MATRIX	matrix;
#ifdef WIN64
	__int64	ifcOpeningElementInstance;
#else
	__int32	ifcOpeningElementInstance;
#endif

	identityMatrix(&matrix);
	matrix._11 = xRefDirection;
	matrix._12 = yRefDirection;
	matrix._13 = zRefDirection;
	matrix._31 = xAxis;
	matrix._32 = yAxis;
	matrix._33 = zAxis;
	matrix._41 = xOffset;
	matrix._42 = yOffset;
	matrix._43 = zOffset;

	//
	//		Build Opening Element
	//
	ifcOpeningElementInstance = buildOpeningElementInstance(&matrix, ifcWallInstancePlacement, &ifcOpeningElementInstancePlacement, pOpeningElementName, representation);

	ASSERT(ifcOpeningElementInstance);

	return	ifcOpeningElementInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	createIfcWindow(wchar_t * pWindowName, double xOffset, double yOffset, double zOffset, bool insideOpening, double overallHeight, double overallWidth)
#else
__int64	createIfcWindow(char * pWindowName, double xOffset, double yOffset, double zOffset, bool insideOpening, double overallHeight, double overallWidth)
#endif
#else
#ifdef UNICODE
__int32	createIfcWindow(wchar_t * pWindowName, double xOffset, double yOffset, double zOffset, bool insideOpening, double overallHeight, double overallWidth)
#else
__int32	createIfcWindow(char * pWindowName, double xOffset, double yOffset, double zOffset, bool insideOpening, double overallHeight, double overallWidth)
#endif
#endif
{
	MATRIX	matrix;
#ifdef WIN64
	__int64	ifcWindowInstance, ifcWindowInstancePlacement;
#else
	__int32	ifcWindowInstance, ifcWindowInstancePlacement;
#endif

	identityMatrix(&matrix);
	matrix._41 = xOffset;
	matrix._42 = yOffset;
	matrix._43 = zOffset;

	if	(insideOpening) {
		//
		//		Build Window
		//
		ifcWindowInstance = buildWindowInstance(&matrix, ifcOpeningElementInstancePlacement, &ifcWindowInstancePlacement, pWindowName, overallHeight, overallWidth);
#ifdef WIN64
		sdaiAppend((__int64) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWindowInstance);
#else
		sdaiAppend((__int32) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWindowInstance);
#endif
	} else {
		//
		//		Build Window and add it to the BuildingStorey
		//
		ifcWindowInstance = buildWindowInstance(&matrix, ifcBuildingStoreyInstancePlacement, &ifcWindowInstancePlacement, pWindowName, overallHeight, overallWidth);
#ifdef WIN64
		sdaiAppend((__int64) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWindowInstance);
#else
		sdaiAppend((__int32) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWindowInstance);
#endif
	}

	ASSERT(ifcWindowInstance);

	return	ifcWindowInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	createIfcWindow(wchar_t * pWindowName,
#else
__int64	createIfcWindow(char * pWindowName,
#endif
#else
#ifdef UNICODE
__int32	createIfcWindow(wchar_t * pWindowName,
#else
__int32	createIfcWindow(char * pWindowName,
#endif
#endif
						double xRefDirection, double yRefDirection, double zRefDirection,
						double xAxis, double yAxis, double zAxis,
						double xOffset, double yOffset, double zOffset,
						bool insideOpening,
						double overallHeight,
						double overallWidth)
{
	MATRIX	matrix;
#ifdef WIN64
	__int64	ifcWindowInstance, ifcWindowInstancePlacement;
#else
	__int32	ifcWindowInstance, ifcWindowInstancePlacement;
#endif

	identityMatrix(&matrix);
	matrix._11 = xRefDirection;
	matrix._12 = yRefDirection;
	matrix._13 = zRefDirection;
	matrix._31 = xAxis;
	matrix._32 = yAxis;
	matrix._33 = zAxis;
	matrix._41 = xOffset;
	matrix._42 = yOffset;
	matrix._43 = zOffset;

	if	(insideOpening) {
		//
		//		Build Window
		//
		ifcWindowInstance = buildWindowInstance(&matrix, ifcOpeningElementInstancePlacement, &ifcWindowInstancePlacement, pWindowName, overallHeight, overallWidth);
#ifdef WIN64
		sdaiAppend((__int64) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWindowInstance);
#else
		sdaiAppend((__int32) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWindowInstance);
#endif
	} else {
		//
		//		Build Window and add it to the BuildingStorey
		//
		ifcWindowInstance = buildWindowInstance(&matrix, ifcBuildingStoreyInstancePlacement, &ifcWindowInstancePlacement, pWindowName, overallHeight, overallWidth);
#ifdef WIN64
		sdaiAppend((__int64) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWindowInstance);
#else
		sdaiAppend((__int32) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWindowInstance);
#endif
	}

	ASSERT(ifcWindowInstance);

	return	ifcWindowInstance;
}


//
//
//		ProductDefinitionShape
//
//


#ifdef WIN64
__int64	buildProductDefinitionShapeInstance()
#else
__int32	buildProductDefinitionShapeInstance()
#endif
{
#ifdef WIN64
	__int64	ifcProductDefinitionShapeInstance;
#else
	__int32	ifcProductDefinitionShapeInstance;
#endif

#ifdef UNICODE
	ifcProductDefinitionShapeInstance = sdaiCreateInstanceBN(model, (char*) L"IFCPRODUCTDEFINITIONSHAPE");

	aggrRepresentations = sdaiCreateAggrBN(ifcProductDefinitionShapeInstance, (char*) L"Representations");
#else
	ifcProductDefinitionShapeInstance = sdaiCreateInstanceBN(model, "IFCPRODUCTDEFINITIONSHAPE");

	aggrRepresentations = sdaiCreateAggrBN(ifcProductDefinitionShapeInstance, "Representations");
#endif

	ASSERT(ifcProductDefinitionShapeInstance);

	return	ifcProductDefinitionShapeInstance;
}


//
//
//		IfcWall, IfcWallStandardCase, IfcOpeningElement, IfcWindow
//
//


#ifdef WIN64
__int64	buildRelDefinesByType(__int64 relatedObjectInstance, __int64 relatingTypeInstance)
#else
__int32	buildRelDefinesByType(__int32 relatedObjectInstance, __int32 relatingTypeInstance)
#endif
{
#ifdef WIN64
	__int64	ifcRelDefinesByTypeInstance, * aggrRelatedObjects;
#else
	__int32	ifcRelDefinesByTypeInstance, * aggrRelatedObjects;
#endif

#ifdef UNICODE
	ifcRelDefinesByTypeInstance = sdaiCreateInstanceBN(model, (char*) L"IFCRELDEFINESBYTYPE");

	sdaiPutAttrBN(ifcRelDefinesByTypeInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelDefinesByTypeInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	aggrRelatedObjects = sdaiCreateAggrBN(ifcRelDefinesByTypeInstance, (char*) L"RelatedObjects");
#else
	ifcRelDefinesByTypeInstance = sdaiCreateInstanceBN(model, "IFCRELDEFINESBYTYPE");

	sdaiPutAttrBN(ifcRelDefinesByTypeInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelDefinesByTypeInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	aggrRelatedObjects = sdaiCreateAggrBN(ifcRelDefinesByTypeInstance, "RelatedObjects");
#endif
#ifdef WIN64
	sdaiAppend((__int64) aggrRelatedObjects, sdaiINSTANCE, (void*) relatedObjectInstance);
#else
	sdaiAppend((__int32) aggrRelatedObjects, sdaiINSTANCE, (void*) relatedObjectInstance);
#endif
#ifdef UNICODE
	sdaiPutAttrBN(ifcRelDefinesByTypeInstance, (char*) L"RelatingType", sdaiINSTANCE, (void*) relatingTypeInstance);
#else
	sdaiPutAttrBN(ifcRelDefinesByTypeInstance, "RelatingType", sdaiINSTANCE, (void*) relatingTypeInstance);
#endif

	ASSERT(ifcRelDefinesByTypeInstance);

	return	ifcRelDefinesByTypeInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildWallTypeInstance(__int64 ifcWallInstance, wchar_t * pWindowName, wchar_t * predefinedType)
#else
__int64	buildWallTypeInstance(__int64 ifcWallInstance, char * pWindowName, char * predefinedType)
#endif
#else
#ifdef UNICODE
__int32	buildWallTypeInstance(__int32 ifcWallInstance, wchar_t * pWindowName, wchar_t * predefinedType)
#else
__int32	buildWallTypeInstance(__int32 ifcWallInstance, char * pWindowName, char * predefinedType)
#endif
#endif
{
	ASSERT(ifcWallInstance);

#ifdef WIN64
	__int64	ifcWallTypeInstance;
#else
	__int32	ifcWallTypeInstance;
#endif

#ifdef UNICODE
	ifcWallTypeInstance = sdaiCreateInstanceBN(model, (char*) L"IFCWALLTYPE");

	sdaiPutAttrBN(ifcWallTypeInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcWallTypeInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcWallTypeInstance, (char*) L"Name", sdaiUNICODE, pWindowName);
	sdaiPutAttrBN(ifcWallTypeInstance, (char*) L"Description", sdaiUNICODE, L"Description of Window Type");

	sdaiPutAttrBN(ifcWallTypeInstance, (char*) L"PredefinedType", sdaiENUM, predefinedType);
#else
	ifcWallTypeInstance = sdaiCreateInstanceBN(model, "IFCWALLTYPE");

	sdaiPutAttrBN(ifcWallTypeInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcWallTypeInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcWallTypeInstance, "Name", sdaiSTRING, pWindowName);
	sdaiPutAttrBN(ifcWallTypeInstance, "Description", sdaiSTRING, "Description of Window Type");

	sdaiPutAttrBN(ifcWallTypeInstance, "PredefinedType", sdaiENUM, predefinedType);
#endif

	buildRelDefinesByType(ifcWallInstance, ifcWallTypeInstance);

	ASSERT(ifcWallTypeInstance);

#ifdef	IFC4
	//
	//	Add to IfcRelDeclares
	//
	buildRelDeclares_WallType(ifcWallTypeInstance);
#endif

	return	ifcWallTypeInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildWallInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcWallInstancePlacement, wchar_t * pWallName)
#else
__int64	buildWallInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcWallInstancePlacement, char * pWallName)
#endif
#else
#ifdef UNICODE
__int32	buildWallInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcWallInstancePlacement, wchar_t * pWallName)
#else
__int32	buildWallInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcWallInstancePlacement, char * pWallName)
#endif
#endif
{
	ASSERT(ifcPlacementRelativeTo);

#ifdef WIN64
	__int64	ifcWallInstance;
#else
	__int32	ifcWallInstance;
#endif

#ifdef UNICODE
	ifcWallInstance = sdaiCreateInstanceBN(model, (char*) L"IFCWALL");

	sdaiPutAttrBN(ifcWallInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcWallInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcWallInstance, (char*) L"Name", sdaiUNICODE, pWallName);
	sdaiPutAttrBN(ifcWallInstance, (char*) L"Description", sdaiUNICODE, L"Description of Wall");
#else
	ifcWallInstance = sdaiCreateInstanceBN(model, "IFCWALL");

	sdaiPutAttrBN(ifcWallInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcWallInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcWallInstance, "Name", sdaiSTRING, pWallName);
	sdaiPutAttrBN(ifcWallInstance, "Description", sdaiSTRING, "Description of Wall");
#endif

	(* ifcWallInstancePlacement) = buildLocalPlacementInstance(matrix, ifcPlacementRelativeTo);
#ifdef UNICODE
	sdaiPutAttrBN(ifcWallInstance, (char*) L"ObjectPlacement", sdaiINSTANCE, (void*) (* ifcWallInstancePlacement));
	sdaiPutAttrBN(ifcWallInstance, (char*) L"Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());

	wchar_t	predefinedType[9] = L"STANDARD";
#else
	sdaiPutAttrBN(ifcWallInstance, "ObjectPlacement", sdaiINSTANCE, (void*) (* ifcWallInstancePlacement));
	sdaiPutAttrBN(ifcWallInstance, "Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());

	char	predefinedType[9] = "STANDARD";
#endif
	buildWallTypeInstance(ifcWallInstance, pWallName, predefinedType);
#ifdef UNICODE
	sdaiPutAttrBN(ifcWallInstance, (char*) L"PredefinedType", sdaiENUM, predefinedType);
#else
	sdaiPutAttrBN(ifcWallInstance, "PredefinedType", sdaiENUM, predefinedType);
#endif

	ASSERT(ifcWallInstance);

	return	ifcWallInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildWallStandardCaseInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcWallInstancePlacement, wchar_t * pWallName)
#else
__int64	buildWallStandardCaseInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcWallInstancePlacement, char * pWallName)
#endif
#else
#ifdef UNICODE
__int32	buildWallStandardCaseInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcWallInstancePlacement, wchar_t * pWallName)
#else
__int32	buildWallStandardCaseInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcWallInstancePlacement, char * pWallName)
#endif
#endif
{
	ASSERT(ifcPlacementRelativeTo);

#ifdef WIN64
	__int64	ifcWallInstance;
#else
	__int32	ifcWallInstance;
#endif

#ifdef UNICODE
	ifcWallInstance = sdaiCreateInstanceBN(model, (char*) L"IFCWALLSTANDARDCASE");

	sdaiPutAttrBN(ifcWallInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcWallInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcWallInstance, (char*) L"Name", sdaiUNICODE, pWallName);
	sdaiPutAttrBN(ifcWallInstance, (char*) L"Description", sdaiUNICODE, L"Description of Wall");
#else
	ifcWallInstance = sdaiCreateInstanceBN(model, "IFCWALLSTANDARDCASE");

	sdaiPutAttrBN(ifcWallInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcWallInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcWallInstance, "Name", sdaiSTRING, pWallName);
	sdaiPutAttrBN(ifcWallInstance, "Description", sdaiSTRING, "Description of Wall");
#endif

	(* ifcWallInstancePlacement) = buildLocalPlacementInstance(matrix, ifcPlacementRelativeTo);
#ifdef UNICODE
	sdaiPutAttrBN(ifcWallInstance, (char*) L"ObjectPlacement", sdaiINSTANCE, (void*) (* ifcWallInstancePlacement));
	sdaiPutAttrBN(ifcWallInstance, (char*) L"Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());

	wchar_t	predefinedType[9] = L"STANDARD";
#else
	sdaiPutAttrBN(ifcWallInstance, "ObjectPlacement", sdaiINSTANCE, (void*) (* ifcWallInstancePlacement));
	sdaiPutAttrBN(ifcWallInstance, "Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());

	char	predefinedType[9] = "STANDARD";
#endif
	buildWallTypeInstance(ifcWallInstance, pWallName, predefinedType);
#ifdef UNICODE
	sdaiPutAttrBN(ifcWallInstance, (char*) L"PredefinedType", sdaiENUM, predefinedType);
#else
	sdaiPutAttrBN(ifcWallInstance, "PredefinedType", sdaiENUM, predefinedType);
#endif

	ASSERT(ifcWallInstance);

	return	ifcWallInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildOpeningElementInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcOpeningElementInstancePlacement, wchar_t * pOpeningElementName, bool representation)
#else
__int64	buildOpeningElementInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcOpeningElementInstancePlacement, char * pOpeningElementName, bool representation)
#endif
#else
#ifdef UNICODE
__int32	buildOpeningElementInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcOpeningElementInstancePlacement, wchar_t * pOpeningElementName, bool representation)
#else
__int32	buildOpeningElementInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcOpeningElementInstancePlacement, char * pOpeningElementName, bool representation)
#endif
#endif
{
	ASSERT(ifcPlacementRelativeTo);

#ifdef WIN64
	__int64	ifcOpeningElementInstance;
#else
	__int32	ifcOpeningElementInstance;
#endif

#ifdef UNICODE
	ifcOpeningElementInstance = sdaiCreateInstanceBN(model, (char*) L"IFCOPENINGELEMENT");

	sdaiPutAttrBN(ifcOpeningElementInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcOpeningElementInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcOpeningElementInstance, (char*) L"Name", sdaiUNICODE, pOpeningElementName);
	sdaiPutAttrBN(ifcOpeningElementInstance, (char*) L"Description", sdaiUNICODE, L"Description of Opening");

	wchar_t	predefinedType[8] = L"OPENING";
	sdaiPutAttrBN(ifcOpeningElementInstance, (char*) L"PredefinedType", sdaiENUM, predefinedType);
#else
	ifcOpeningElementInstance = sdaiCreateInstanceBN(model, "IFCOPENINGELEMENT");

	sdaiPutAttrBN(ifcOpeningElementInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcOpeningElementInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcOpeningElementInstance, "Name", sdaiSTRING, pOpeningElementName);
	sdaiPutAttrBN(ifcOpeningElementInstance, "Description", sdaiSTRING, "Description of Opening");

	char	predefinedType[8] = "OPENING";
	sdaiPutAttrBN(ifcOpeningElementInstance, "PredefinedType", sdaiENUM, predefinedType);
#endif

	(* ifcOpeningElementInstancePlacement) = buildLocalPlacementInstance(matrix, ifcPlacementRelativeTo);
#ifdef UNICODE
	sdaiPutAttrBN(ifcOpeningElementInstance, (char*) L"ObjectPlacement", sdaiINSTANCE, (void*) (* ifcOpeningElementInstancePlacement));
#else
	sdaiPutAttrBN(ifcOpeningElementInstance, "ObjectPlacement", sdaiINSTANCE, (void*) (* ifcOpeningElementInstancePlacement));
#endif
	if	(representation) {
#ifdef UNICODE
		sdaiPutAttrBN(ifcOpeningElementInstance, (char*) L"Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());
#else
		sdaiPutAttrBN(ifcOpeningElementInstance, "Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());
#endif
	}

	ASSERT(ifcOpeningElementInstance);

	return	ifcOpeningElementInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildWindowTypeInstance(__int64 ifcWindowInstance, wchar_t * pWindowName, wchar_t * predefinedType, wchar_t * partitioningType)
#else
__int64	buildWindowTypeInstance(__int64 ifcWindowInstance, char * pWindowName, char * predefinedType, char * partitioningType)
#endif
#else
#ifdef UNICODE
__int32	buildWindowTypeInstance(__int32 ifcWindowInstance, wchar_t * pWindowName, wchar_t * predefinedType, wchar_t * partitioningType)
#else
__int32	buildWindowTypeInstance(__int32 ifcWindowInstance, char * pWindowName, char * predefinedType, char * partitioningType)
#endif
#endif
{
	ASSERT(ifcWindowInstance);

#ifdef WIN64
	__int64	ifcWindowTypeInstance;
#else
	__int32	ifcWindowTypeInstance;
#endif

#ifdef UNICODE
	ifcWindowTypeInstance = sdaiCreateInstanceBN(model, (char*) L"IFCWINDOWTYPE");

	sdaiPutAttrBN(ifcWindowTypeInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcWindowTypeInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcWindowTypeInstance, (char*) L"Name", sdaiUNICODE, pWindowName);
	sdaiPutAttrBN(ifcWindowTypeInstance, (char*) L"Description", sdaiUNICODE, L"Description of Window Type");

	sdaiPutAttrBN(ifcWindowTypeInstance, (char*) L"PredefinedType", sdaiENUM, predefinedType);
	sdaiPutAttrBN(ifcWindowTypeInstance, (char*) L"PartitioningType", sdaiENUM, partitioningType);
#else
	ifcWindowTypeInstance = sdaiCreateInstanceBN(model, "IFCWINDOWTYPE");

	sdaiPutAttrBN(ifcWindowTypeInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcWindowTypeInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcWindowTypeInstance, "Name", sdaiSTRING, pWindowName);
	sdaiPutAttrBN(ifcWindowTypeInstance, "Description", sdaiSTRING, "Description of Window Type");

	sdaiPutAttrBN(ifcWindowTypeInstance, "PredefinedType", sdaiENUM, predefinedType);
	sdaiPutAttrBN(ifcWindowTypeInstance, "PartitioningType", sdaiENUM, partitioningType);
#endif

	buildRelDefinesByType(ifcWindowInstance, ifcWindowTypeInstance);

	//
	//	Add to IfcRelDeclares
	//
	buildRelDeclares_WallType(ifcWindowTypeInstance);

	ASSERT(ifcWindowTypeInstance);

	return	ifcWindowTypeInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildWindowInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcWindowInstancePlacement, wchar_t * pWindowName, double overallHeight, double overallWidth)
#else
__int64	buildWindowInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcWindowInstancePlacement, char * pWindowName, double overallHeight, double overallWidth)
#endif
#else
#ifdef UNICODE
__int32	buildWindowInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcWindowInstancePlacement, wchar_t * pWindowName, double overallHeight, double overallWidth)
#else
__int32	buildWindowInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcWindowInstancePlacement, char * pWindowName, double overallHeight, double overallWidth)
#endif
#endif
{
	ASSERT(ifcPlacementRelativeTo);

#ifdef WIN64
	__int64	ifcWindowInstance;
#else
	__int32	ifcWindowInstance;
#endif

#ifdef UNICODE
	ifcWindowInstance = sdaiCreateInstanceBN(model, (char*) L"IFCWINDOW");

	sdaiPutAttrBN(ifcWindowInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcWindowInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcWindowInstance, (char*) L"Name", sdaiUNICODE, pWindowName);
	sdaiPutAttrBN(ifcWindowInstance, (char*) L"Description", sdaiUNICODE, L"Description of Window");
#else
	ifcWindowInstance = sdaiCreateInstanceBN(model, "IFCWINDOW");

	sdaiPutAttrBN(ifcWindowInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcWindowInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcWindowInstance, "Name", sdaiSTRING, pWindowName);
	sdaiPutAttrBN(ifcWindowInstance, "Description", sdaiSTRING, "Description of Window");
#endif

	(* ifcWindowInstancePlacement) = buildLocalPlacementInstance(matrix, ifcPlacementRelativeTo);
#ifdef UNICODE
	sdaiPutAttrBN(ifcWindowInstance, (char*) L"ObjectPlacement", sdaiINSTANCE, (void*) (* ifcWindowInstancePlacement));
	sdaiPutAttrBN(ifcWindowInstance, (char*) L"Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());

	wchar_t	predefinedType[7] = L"WINDOW", partitioningType[13] = L"SINGLE_PANEL";
#else
	sdaiPutAttrBN(ifcWindowInstance, "ObjectPlacement", sdaiINSTANCE, (void*) (* ifcWindowInstancePlacement));
	sdaiPutAttrBN(ifcWindowInstance, "Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());

	char	predefinedType[7] = "WINDOW", partitioningType[13] = "SINGLE_PANEL";
#endif
#ifdef IFC4
	buildWindowTypeInstance(ifcWindowInstance, pWindowName, predefinedType, partitioningType);
#endif
#ifdef UNICODE
	sdaiPutAttrBN(ifcWindowInstance, (char*) L"PredefinedType", sdaiENUM, predefinedType);
	sdaiPutAttrBN(ifcWindowInstance, (char*) L"PartitioningType", sdaiENUM, partitioningType);

	sdaiPutAttrBN(ifcWindowInstance, (char*) L"OverallHeight", sdaiREAL, &overallHeight);
	sdaiPutAttrBN(ifcWindowInstance, (char*) L"OverallWidth", sdaiREAL, &overallWidth);
#else
	sdaiPutAttrBN(ifcWindowInstance, "PredefinedType", sdaiENUM, predefinedType);
	sdaiPutAttrBN(ifcWindowInstance, "PartitioningType", sdaiENUM, partitioningType);

	sdaiPutAttrBN(ifcWindowInstance, "OverallHeight", sdaiREAL, &overallHeight);
	sdaiPutAttrBN(ifcWindowInstance, "OverallWidth", sdaiREAL, &overallWidth);
#endif

	ASSERT(ifcWindowInstance);

	return	ifcWindowInstance;
}


//
//
//		RelVoidsElement, RelFillsElement
//
//


#ifdef WIN64
__int64	buildRelVoidsElementInstance(__int64 ifcBuildingElementInstance, __int64 ifcOpeningElementInstance)
#else
__int32	buildRelVoidsElementInstance(__int32 ifcBuildingElementInstance, __int32 ifcOpeningElementInstance)
#endif
{
	ASSERT(ifcBuildingElementInstance  &&  ifcOpeningElementInstance);

#ifdef WIN64
	__int64	ifcRelVoidsElementInstance;
#else
	__int32	ifcRelVoidsElementInstance;
#endif

#ifdef UNICODE
	ifcRelVoidsElementInstance = sdaiCreateInstanceBN(model, (char*) L"IFCRELVOIDSELEMENT");

	sdaiPutAttrBN(ifcRelVoidsElementInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelVoidsElementInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	sdaiPutAttrBN(ifcRelVoidsElementInstance, (char*) L"RelatingBuildingElement", sdaiINSTANCE, (void*) ifcBuildingElementInstance);
	sdaiPutAttrBN(ifcRelVoidsElementInstance, (char*) L"RelatedOpeningElement", sdaiINSTANCE, (void*) ifcOpeningElementInstance);
#else
	ifcRelVoidsElementInstance = sdaiCreateInstanceBN(model, "IFCRELVOIDSELEMENT");

	sdaiPutAttrBN(ifcRelVoidsElementInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelVoidsElementInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	sdaiPutAttrBN(ifcRelVoidsElementInstance, "RelatingBuildingElement", sdaiINSTANCE, (void*) ifcBuildingElementInstance);
	sdaiPutAttrBN(ifcRelVoidsElementInstance, "RelatedOpeningElement", sdaiINSTANCE, (void*) ifcOpeningElementInstance);
#endif

	ASSERT(ifcRelVoidsElementInstance);

	return	ifcRelVoidsElementInstance;
}

#ifdef WIN64
__int64	buildRelFillsElementInstance(__int64 ifcOpeningElementInstance, __int64 ifcBuildingElementInstance)
#else
__int32	buildRelFillsElementInstance(__int32 ifcOpeningElementInstance, __int32 ifcBuildingElementInstance)
#endif
{
	ASSERT(ifcOpeningElementInstance  &&  ifcBuildingElementInstance);

#ifdef WIN64
	__int64	ifcRelFillsElementInstance;
#else
	__int32	ifcRelFillsElementInstance;
#endif

#ifdef UNICODE
	ifcRelFillsElementInstance = sdaiCreateInstanceBN(model, (char*) L"IFCRELFILLSELEMENT");

	sdaiPutAttrBN(ifcRelFillsElementInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelFillsElementInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	sdaiPutAttrBN(ifcRelFillsElementInstance, (char*) L"RelatingOpeningElement", sdaiINSTANCE, (void*) ifcOpeningElementInstance);
	sdaiPutAttrBN(ifcRelFillsElementInstance, (char*) L"RelatedBuildingElement", sdaiINSTANCE, (void*) ifcBuildingElementInstance);
#else
	ifcRelFillsElementInstance = sdaiCreateInstanceBN(model, "IFCRELFILLSELEMENT");

	sdaiPutAttrBN(ifcRelFillsElementInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelFillsElementInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	sdaiPutAttrBN(ifcRelFillsElementInstance, "RelatingOpeningElement", sdaiINSTANCE, (void*) ifcOpeningElementInstance);
	sdaiPutAttrBN(ifcRelFillsElementInstance, "RelatedBuildingElement", sdaiINSTANCE, (void*) ifcBuildingElementInstance);
#endif

	ASSERT(ifcRelFillsElementInstance);

	return	ifcRelFillsElementInstance;
}


//
//
//		ProjectLibrary, RelDeclares
//
//


#ifdef WIN64
__int64	buildProjectLibrary()
#else
__int32	buildProjectLibrary()
#endif
{
#ifdef WIN64
	__int64	ifcProjectLibraryInstance;
#else
	__int32	ifcProjectLibraryInstance;
#endif

#ifdef UNICODE
	ifcProjectLibraryInstance = sdaiCreateInstanceBN(model, (char*) L"IFCPROJECTLIBRARY");

	sdaiPutAttrBN(ifcProjectLibraryInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcProjectLibraryInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
#else
	ifcProjectLibraryInstance = sdaiCreateInstanceBN(model, "IFCPROJECTLIBRARY");

	sdaiPutAttrBN(ifcProjectLibraryInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcProjectLibraryInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
#endif

	buildRelDeclares_ProjectLibrary(ifcProjectLibraryInstance);

	ASSERT(ifcProjectLibraryInstance);

	return	ifcProjectLibraryInstance;
}


#ifdef WIN64
__int64	buildRelDeclares_ProjectLibrary(__int64 ifcProjectLibraryInstance)
#else
__int32	buildRelDeclares_ProjectLibrary(__int32 ifcProjectLibraryInstance)
#endif
{
#ifdef WIN64
	__int64	ifcRelDeclaresInstance = 0;
#else
	__int32	ifcRelDeclaresInstance = 0;
#endif

	ASSERT(ifcProjectLibraryInstance);

	if	(aggr_ifcRelDeclaresInstance_RelatedDefinitions_ProjectLibrary == 0) {
#ifdef UNICODE
		ifcRelDeclaresInstance = sdaiCreateInstanceBN(model, (char*) L"IFCRELDECLARES");

		sdaiPutAttrBN(ifcRelDeclaresInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
		sdaiPutAttrBN(ifcRelDeclaresInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

		aggr_ifcRelDeclaresInstance_RelatedDefinitions_ProjectLibrary = sdaiCreateAggrBN(ifcRelDeclaresInstance, (char*) L"RelatedDefinitions");
#else
		ifcRelDeclaresInstance = sdaiCreateInstanceBN(model, "IFCRELDECLARES");

		sdaiPutAttrBN(ifcRelDeclaresInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
		sdaiPutAttrBN(ifcRelDeclaresInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

		aggr_ifcRelDeclaresInstance_RelatedDefinitions_ProjectLibrary = sdaiCreateAggrBN(ifcRelDeclaresInstance, "RelatedDefinitions");
#endif
#ifdef WIN64
		sdaiAppend((__int64) aggr_ifcRelDeclaresInstance_RelatedDefinitions_ProjectLibrary, sdaiINSTANCE, (void*) ifcProjectInstance);
#else
		sdaiAppend((__int32) aggr_ifcRelDeclaresInstance_RelatedDefinitions_ProjectLibrary, sdaiINSTANCE, (void*) ifcProjectInstance);
#endif
#ifdef UNICODE
		sdaiPutAttrBN(ifcRelDeclaresInstance, (char*) L"RelatingContext", sdaiINSTANCE, (void*) ifcProjectLibraryInstance);
#else
		sdaiPutAttrBN(ifcRelDeclaresInstance, "RelatingContext", sdaiINSTANCE, (void*) ifcProjectLibraryInstance);
#endif
	} else {
#ifdef WIN64
		sdaiAppend((__int64) aggr_ifcRelDeclaresInstance_RelatedDefinitions_ProjectLibrary, sdaiINSTANCE, (void*) ifcProjectInstance);
#else
		sdaiAppend((__int32) aggr_ifcRelDeclaresInstance_RelatedDefinitions_ProjectLibrary, sdaiINSTANCE, (void*) ifcProjectInstance);
#endif
	}

	ASSERT(ifcRelDeclaresInstance);

	return	ifcRelDeclaresInstance;
}

#ifdef	WIN64
__int64	buildRelDeclares_WallType(__int64 ifcWallTypeInstance)
#else
__int32	buildRelDeclares_WallType(__int32 ifcWallTypeInstance)
#endif
{
	ASSERT(ifcWallTypeInstance);

	if	(ifcRelDeclaresInstance == 0) {
#ifdef UNICODE
		ifcRelDeclaresInstance = sdaiCreateInstanceBN(model, (char*) L"IFCRELDECLARES");

		sdaiPutAttrBN(ifcRelDeclaresInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
		sdaiPutAttrBN(ifcRelDeclaresInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

		aggr_ifcRelDeclaresInstance_RelatedDefinitions = sdaiCreateAggrBN(ifcRelDeclaresInstance, (char*) L"RelatedDefinitions");
#else
		ifcRelDeclaresInstance = sdaiCreateInstanceBN(model, "IFCRELDECLARES");

		sdaiPutAttrBN(ifcRelDeclaresInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
		sdaiPutAttrBN(ifcRelDeclaresInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

		aggr_ifcRelDeclaresInstance_RelatedDefinitions = sdaiCreateAggrBN(ifcRelDeclaresInstance, "RelatedDefinitions");
#endif
#ifdef	WIN64
		sdaiAppend((__int64) aggr_ifcRelDeclaresInstance_RelatedDefinitions, sdaiINSTANCE, (void*) ifcWallTypeInstance);
#else
		sdaiAppend((__int32) aggr_ifcRelDeclaresInstance_RelatedDefinitions, sdaiINSTANCE, (void*) ifcWallTypeInstance);
#endif
		sdaiPutAttrBN(ifcRelDeclaresInstance, "RelatingContext", sdaiINSTANCE, (void*) buildProjectLibrary());
	} else {
#ifdef	WIN64
		sdaiAppend((__int64) aggr_ifcRelDeclaresInstance_RelatedDefinitions, sdaiINSTANCE, (void*) ifcWallTypeInstance);
#else
		sdaiAppend((__int32) aggr_ifcRelDeclaresInstance_RelatedDefinitions, sdaiINSTANCE, (void*) ifcWallTypeInstance);
#endif
	}

	ASSERT(ifcRelDeclaresInstance);

	return	ifcRelDeclaresInstance;
}



//
//
//		MaterialConstituentSet, MaterialConstituent
//
//


#ifdef WIN64
__int64	buildMaterialConstituentSet()
#else
__int32	buildMaterialConstituentSet()
#endif
{
#ifdef WIN64
	__int64	ifcMaterialConstituentSetInstance, * aggrMaterialConstituents;
#else
	__int32	ifcMaterialConstituentSetInstance, * aggrMaterialConstituents;
#endif

#ifdef UNICODE
	ifcMaterialConstituentSetInstance = sdaiCreateInstanceBN(model, (char*) L"IFCMATERIALCONSTITUENTSET");

	sdaiPutAttrBN(ifcMaterialConstituentSetInstance, (char*) L"Name", sdaiUNICODE, L"Constituent Set for Window");

	aggrMaterialConstituents = sdaiCreateAggrBN(ifcMaterialConstituentSetInstance, (char*) L"MaterialConstituents");
#ifdef WIN64
	sdaiAppend((__int64) aggrMaterialConstituents, sdaiINSTANCE, (void*) buildMaterialConstituent(L"Glass"));
	sdaiAppend((__int64) aggrMaterialConstituents, sdaiINSTANCE, (void*) buildMaterialConstituent(L"Wood"));
#else
	sdaiAppend((__int32) aggrMaterialConstituents, sdaiINSTANCE, (void*) buildMaterialConstituent(L"Glass"));
	sdaiAppend((__int32) aggrMaterialConstituents, sdaiINSTANCE, (void*) buildMaterialConstituent(L"Wood"));
#endif
#else
	ifcMaterialConstituentSetInstance = sdaiCreateInstanceBN(model, "IFCMATERIALCONSTITUENTSET");

	sdaiPutAttrBN(ifcMaterialConstituentSetInstance, "Name", sdaiSTRING, "Constituent Set for Window");

	aggrMaterialConstituents = sdaiCreateAggrBN(ifcMaterialConstituentSetInstance, "MaterialConstituents");
#ifdef WIN64
	sdaiAppend((__int64) aggrMaterialConstituents, sdaiINSTANCE, (void*) buildMaterialConstituent("Glass"));
	sdaiAppend((__int64) aggrMaterialConstituents, sdaiINSTANCE, (void*) buildMaterialConstituent("Wood"));
#else
	sdaiAppend((__int32) aggrMaterialConstituents, sdaiINSTANCE, (void*) buildMaterialConstituent("Glass"));
	sdaiAppend((__int32) aggrMaterialConstituents, sdaiINSTANCE, (void*) buildMaterialConstituent("Wood"));
#endif
#endif

	ASSERT(ifcMaterialConstituentSetInstance);

	return	ifcMaterialConstituentSetInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildMaterialConstituent(wchar_t * material)
#else
__int64	buildMaterialConstituent(char * material)
#endif
#else
#ifdef UNICODE
__int32	buildMaterialConstituent(wchar_t * material)
#else
__int32	buildMaterialConstituent(char * material)
#endif
#endif
{
#ifdef WIN64
	__int64	ifcMaterialConstituentInstance;
#else
	__int32	ifcMaterialConstituentInstance;
#endif

#ifdef UNICODE
	ifcMaterialConstituentInstance = sdaiCreateInstanceBN(model, (char*) L"IFCMATERIALCONSTITUENT");

	sdaiPutAttrBN(ifcMaterialConstituentInstance, (char*) L"Name", sdaiUNICODE, L"Framing");
	sdaiPutAttrBN(ifcMaterialConstituentInstance, (char*) L"Material", sdaiINSTANCE, (void*) buildMaterial(material));
#else
	ifcMaterialConstituentInstance = sdaiCreateInstanceBN(model, "IFCMATERIALCONSTITUENT");

	sdaiPutAttrBN(ifcMaterialConstituentInstance, "Name", sdaiSTRING, "Framing");
	sdaiPutAttrBN(ifcMaterialConstituentInstance, "Material", sdaiINSTANCE, (void*) buildMaterial(material));
#endif

	ASSERT(ifcMaterialConstituentInstance);

	return	ifcMaterialConstituentInstance;
}



//
//
//		RelAssociatesMaterial, MaterialLayerSetUsage, MaterialLayerSet, MaterialLayer
//
//


#ifdef WIN64
__int64	buildRelAssociatesMaterial(__int64 ifcBuildingElementInstance, double thickness)
#else
__int32	buildRelAssociatesMaterial(__int32 ifcBuildingElementInstance, double thickness)
#endif
{
	ASSERT(ifcBuildingElementInstance);

#ifdef	WIN64
	__int64	ifcRelAssociatesMaterialInstance, * aggrRelatedObjects;
#else
	__int32	ifcRelAssociatesMaterialInstance, * aggrRelatedObjects;
#endif

#ifdef UNICODE
	ifcRelAssociatesMaterialInstance = sdaiCreateInstanceBN(model, (char*) L"IFCRELASSOCIATESMATERIAL");

	sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	aggrRelatedObjects = sdaiCreateAggrBN(ifcRelAssociatesMaterialInstance, (char*) L"RelatedObjects");
#else
	ifcRelAssociatesMaterialInstance = sdaiCreateInstanceBN(model, "IFCRELASSOCIATESMATERIAL");

	sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	aggrRelatedObjects = sdaiCreateAggrBN(ifcRelAssociatesMaterialInstance, "RelatedObjects");
#endif
#ifdef	WIN64
	sdaiAppend((__int64) aggrRelatedObjects, sdaiINSTANCE, (void*) ifcBuildingElementInstance);
#else
	sdaiAppend((__int32) aggrRelatedObjects, sdaiINSTANCE, (void*) ifcBuildingElementInstance);
#endif
#ifdef UNICODE
	sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, (char*) L"RelatingMaterial", sdaiINSTANCE, (void*) buildMaterialLayerSetUsage(thickness));
#else
	sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "RelatingMaterial", sdaiINSTANCE, (void*) buildMaterialLayerSetUsage(thickness));
#endif

	ASSERT(ifcRelAssociatesMaterialInstance);

	return	ifcRelAssociatesMaterialInstance;
}

#ifdef WIN64
__int64	buildRelAssociatesMaterial(__int64 ifcBuildingElementInstance)
#else
__int32	buildRelAssociatesMaterial(__int32 ifcBuildingElementInstance)
#endif
{
	ASSERT(ifcBuildingElementInstance);

#ifdef WIN64
	__int64	ifcRelAssociatesMaterialInstance, * aggrRelatedObjects;
#else
	__int32	ifcRelAssociatesMaterialInstance, * aggrRelatedObjects;
#endif

	ifcRelAssociatesMaterialInstance = sdaiCreateInstanceBN(model, "IFCRELASSOCIATESMATERIAL");

	sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	aggrRelatedObjects = sdaiCreateAggrBN(ifcRelAssociatesMaterialInstance, "RelatedObjects");
#ifdef WIN64
	sdaiAppend((__int64) aggrRelatedObjects, sdaiINSTANCE, (void*) ifcBuildingElementInstance);
#else
	sdaiAppend((__int32) aggrRelatedObjects, sdaiINSTANCE, (void*) ifcBuildingElementInstance);
#endif
	sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "RelatingMaterial", sdaiINSTANCE, (void*) buildMaterialConstituentSet());

	ASSERT(ifcRelAssociatesMaterialInstance);

	return	ifcRelAssociatesMaterialInstance;
}

#ifdef WIN64
__int64	buildMaterialLayerSetUsage(double thickness)
#else
__int32	buildMaterialLayerSetUsage(double thickness)
#endif
{
#ifdef WIN64
	__int64	ifcMaterialLayerSetUsageInstance;
#else
	__int32	ifcMaterialLayerSetUsageInstance;
#endif
	double	offsetFromReferenceLine = -thickness/2;

	ifcMaterialLayerSetUsageInstance = sdaiCreateInstanceBN(model, "IFCMATERIALLAYERSETUSAGE");

	sdaiPutAttrBN(ifcMaterialLayerSetUsageInstance, "ForLayerSet", sdaiINSTANCE, (void*) buildMaterialLayerSet(thickness));
	sdaiPutAttrBN(ifcMaterialLayerSetUsageInstance, "LayerSetDirection", sdaiENUM, "AXIS2");
	sdaiPutAttrBN(ifcMaterialLayerSetUsageInstance, "DirectionSense", sdaiENUM, "POSITIVE");
	sdaiPutAttrBN(ifcMaterialLayerSetUsageInstance, "OffsetFromReferenceLine", sdaiREAL, &offsetFromReferenceLine);

	ASSERT(ifcMaterialLayerSetUsageInstance);

	return	ifcMaterialLayerSetUsageInstance;
}

#ifdef WIN64
__int64	buildMaterialLayerSet(double thickness)
#else
__int32	buildMaterialLayerSet(double thickness)
#endif
{
#ifdef WIN64
	__int64	ifcMaterialLayerSetInstance, * aggrMaterialLayers;
#else
	__int32	ifcMaterialLayerSetInstance, * aggrMaterialLayers;
#endif

	ifcMaterialLayerSetInstance = sdaiCreateInstanceBN(model, "IFCMATERIALLAYERSET");

	aggrMaterialLayers = sdaiCreateAggrBN(ifcMaterialLayerSetInstance, "MaterialLayers");
#ifdef WIN64
	sdaiAppend((__int64) aggrMaterialLayers, sdaiINSTANCE, (void*) buildMaterialLayer(thickness));
#else
	sdaiAppend((__int32) aggrMaterialLayers, sdaiINSTANCE, (void*) buildMaterialLayer(thickness));
#endif

	ASSERT(ifcMaterialLayerSetInstance);

	return	ifcMaterialLayerSetInstance;
}

#ifdef WIN64
__int64	buildMaterialLayer(double thickness)
#else
__int32	buildMaterialLayer(double thickness)
#endif
{
#ifdef WIN64
	__int64	ifcMaterialLayerInstance;
#else
	__int32	ifcMaterialLayerInstance;
#endif

	ifcMaterialLayerInstance = sdaiCreateInstanceBN(model, "IFCMATERIALLAYER");

	sdaiPutAttrBN(ifcMaterialLayerInstance, "Material", sdaiINSTANCE, (void*) buildMaterial());
	sdaiPutAttrBN(ifcMaterialLayerInstance, "LayerThickness", sdaiREAL, &thickness);

	ASSERT(ifcMaterialLayerInstance);

	return	ifcMaterialLayerInstance;
}

#ifdef WIN64
__int64	buildMaterial()
#else
__int32	buildMaterial()
#endif
{
#ifdef UNICODE
	return	buildMaterial(L"Name of the material used for the wall");
#else
	return	buildMaterial("Name of the material used for the wall");
#endif
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildMaterial(wchar_t * name)
#else
__int64	buildMaterial(char * name)
#endif
#else
#ifdef UNICODE
__int32	buildMaterial(wchar_t * name)
#else
__int32	buildMaterial(char * name)
#endif
#endif
{
#ifdef WIN64
	__int64	ifcMaterialInstance;
#else
	__int32	ifcMaterialInstance;
#endif

#ifdef UNICODE
	ifcMaterialInstance = sdaiCreateInstanceBN(model, (char*) L"IFCMATERIAL");

	sdaiPutAttrBN(ifcMaterialInstance, (char*) L"Name", sdaiUNICODE, (void*) name);
#else
	ifcMaterialInstance = sdaiCreateInstanceBN(model, "IFCMATERIAL");

	sdaiPutAttrBN(ifcMaterialInstance, "Name", sdaiSTRING, (void*) name);
#endif

	ASSERT(ifcMaterialInstance);

	return	ifcMaterialInstance;
}
