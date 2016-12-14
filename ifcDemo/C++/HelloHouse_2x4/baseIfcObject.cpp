////////////////////////////////////////////////////////////////////////
//  Author:  Peter Bonsma
//  Date:    31 July 2010
//  Project: IFC Engine Series (example using DLL)
//
//  This code may be used and edited freely,
//  also for commercial projects in open and closed source software
//
//  In case of use of the DLL:
//  be aware of license fee for use of this DLL when used commercially
//  more info for commercial use:	peter.bonsma@tno.nl
//
//  more info for using the IFC Engine DLL in other languages
//	and creation of specific code examples:
//									pim.vandenhelm@tno.nl
//								    peter.bonsma@rdf.bg
////////////////////////////////////////////////////////////////////////




#include "stdafx.h"
#include "baseIfcObject.h"

extern  int     model;

extern  int     * aggrRelatedElements;

extern  int     ifcBuildingInstancePlacement,
                ifcBuildingStoreyInstancePlacement;

int        * aggrRepresentations;

int         ifcOpeningElementInstancePlacement,
            ifcWallInstancePlacement,
            ifcSpaceInstancePlacement,
            ifcRoofInstancePlacement,
            ifcSlabInstancePlacement;

int		createIfcSpace(char * pSpaceName, transformationMatrixStruct matrix)
{
    int ifcSpaceInstance;

    //
    //      Build Space and add it to the BuildingStorey
    //
    ifcSpaceInstance = buildSpaceInstance(&matrix, ifcBuildingStoreyInstancePlacement, &ifcSpaceInstancePlacement, pSpaceName);
	sdaiAppend((int) aggrRelatedElements, sdaiINSTANCE, (void *) ifcSpaceInstance);

	return	ifcSpaceInstance;
}

int		createIfcRoof(char * pRoofName, transformationMatrixStruct matrix)
{
    int ifcRoofInstance;

    //
    //      Build Roof and add it to the BuildingStorey
    //
    ifcRoofInstance = buildRoofInstance(&matrix, ifcBuildingStoreyInstancePlacement, &ifcRoofInstancePlacement, pRoofName);
	sdaiAppend((int) aggrRelatedElements, sdaiINSTANCE, (void *) ifcRoofInstance);

	return	ifcRoofInstance;
}

int		createIfcSlab(char * pSlabName, transformationMatrixStruct matrix)
{
    int ifcSlabInstance;

    //
    //      Build Slab and add it to the BuildingStorey
    //
    ifcSlabInstance = buildSlabInstance(&matrix, ifcBuildingStoreyInstancePlacement, &ifcSlabInstancePlacement, pSlabName);
	sdaiAppend((int) aggrRelatedElements, sdaiINSTANCE, (void *) ifcSlabInstance);

	return	ifcSlabInstance;
}

int		createIfcWall(char * pWallName, transformationMatrixStruct matrix)
{
    int ifcWallInstance;

    //
    //      Build Wall and add it to the BuildingStorey
    //
    ifcWallInstance = buildWallInstance(&matrix, ifcBuildingStoreyInstancePlacement, &ifcWallInstancePlacement, pWallName);
	sdaiAppend((int) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWallInstance);

	return	ifcWallInstance;
}

int		createIfcWall(char * pWallName, double xOffset, double yOffset, double zOffset)
{
    transformationMatrixStruct  matrix;
    int ifcWallInstance;

    identityMatrix(&matrix);
    matrix._41 = xOffset;
    matrix._42 = yOffset;
    matrix._43 = zOffset;

    //
    //      Build Wall and add it to the BuildingStorey
    //
    ifcWallInstance = buildWallInstance(&matrix, ifcBuildingStoreyInstancePlacement, &ifcWallInstancePlacement, pWallName);
	sdaiAppend((int) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWallInstance);

	return	ifcWallInstance;
}

int		createIfcWallStandardCase(char * pWallName, double xOffset, double yOffset, double zOffset)
{
    transformationMatrixStruct  matrix;
    int ifcWallStandardCaseInstance;

    identityMatrix(&matrix);
    matrix._41 = xOffset;
    matrix._42 = yOffset;
    matrix._43 = zOffset;

    //
    //      Build Wall and add it to the BuildingStorey
    //
    ifcWallStandardCaseInstance = buildWallStandardCaseInstance(&matrix, ifcBuildingStoreyInstancePlacement, &ifcWallInstancePlacement, pWallName);
	sdaiAppend((int) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWallStandardCaseInstance);

	return	ifcWallStandardCaseInstance;
}

int		createIfcOpeningElement(char * pOpeningElementName, double xOffset, double yOffset, double zOffset, bool representation)
{
    transformationMatrixStruct  matrix;
    int ifcOpeningElementInstance;

    identityMatrix(&matrix);
    matrix._41 = xOffset;
    matrix._42 = yOffset;
    matrix._43 = zOffset;

    //
    //      Build Opening Element
    //
    ifcOpeningElementInstance = buildOpeningElementInstance(&matrix, ifcWallInstancePlacement, &ifcOpeningElementInstancePlacement, pOpeningElementName, representation);

	return	ifcOpeningElementInstance;
}

int		createIfcOpeningElement(char * pOpeningElementName,
                                double xRefDirection, double yRefDirection, double zRefDirection,
                                double xAxis, double yAxis, double zAxis,
                                double xOffset, double yOffset, double zOffset,
                                bool representation)
{
    transformationMatrixStruct  matrix;
    int ifcOpeningElementInstance;

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
    //      Build Opening Element
    //
    ifcOpeningElementInstance = buildOpeningElementInstance(&matrix, ifcWallInstancePlacement, &ifcOpeningElementInstancePlacement, pOpeningElementName, representation);

	return	ifcOpeningElementInstance;
}

int		createIfcDoor(char * pDoorName, double xOffset, double yOffset, double zOffset, bool insideOpening, double overallHeight, double overallWidth)
{
    transformationMatrixStruct  matrix;
    int ifcDoorInstance, ifcDoorInstancePlacement;

    identityMatrix(&matrix);
    matrix._41 = xOffset;
    matrix._42 = yOffset;
    matrix._43 = zOffset;

    if  (insideOpening) {
        //
        //      Build Door
        //
        ifcDoorInstance = buildDoorInstance(&matrix, ifcOpeningElementInstancePlacement, &ifcDoorInstancePlacement, pDoorName, overallHeight, overallWidth);
	    sdaiAppend((int) aggrRelatedElements, sdaiINSTANCE, (void *) ifcDoorInstance);
    } else {
        //
        //      Build Door and add it to the BuildingStorey
        //
        ifcDoorInstance = buildDoorInstance(&matrix, ifcBuildingStoreyInstancePlacement, &ifcDoorInstancePlacement, pDoorName, overallHeight, overallWidth);
	    sdaiAppend((int) aggrRelatedElements, sdaiINSTANCE, (void *) ifcDoorInstance);
    }

	return	ifcDoorInstance;
}

int		createIfcDoor(char * pDoorName,
                        double xRefDirection, double yRefDirection, double zRefDirection,
                        double xAxis, double yAxis, double zAxis,
                        double xOffset, double yOffset, double zOffset,
                        bool insideOpening,
                        double overallHeight,
                        double overallWidth)
{
    transformationMatrixStruct  matrix;
    int ifcDoorInstance, ifcDoorInstancePlacement;

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

    if  (insideOpening) {
        //
        //      Build Door
        //
        ifcDoorInstance = buildDoorInstance(&matrix, ifcOpeningElementInstancePlacement, &ifcDoorInstancePlacement, pDoorName, overallHeight, overallWidth);
	    sdaiAppend((int) aggrRelatedElements, sdaiINSTANCE, (void *) ifcDoorInstance);
    } else {
        //
        //      Build Door and add it to the BuildingStorey
        //
        ifcDoorInstance = buildDoorInstance(&matrix, ifcBuildingStoreyInstancePlacement, &ifcDoorInstancePlacement, pDoorName, overallHeight, overallWidth);
	    sdaiAppend((int) aggrRelatedElements, sdaiINSTANCE, (void *) ifcDoorInstance);
    }

	return	ifcDoorInstance;
}

int		createIfcWindow(char * pWindowName, double xOffset, double yOffset, double zOffset, bool insideOpening, double overallHeight, double overallWidth)
{
    transformationMatrixStruct  matrix;
    int ifcWindowInstance, ifcWindowInstancePlacement;

    identityMatrix(&matrix);
    matrix._41 = xOffset;
    matrix._42 = yOffset;
    matrix._43 = zOffset;

    if  (insideOpening) {
        //
        //      Build Window
        //
        ifcWindowInstance = buildWindowInstance(&matrix, ifcOpeningElementInstancePlacement, &ifcWindowInstancePlacement, pWindowName, overallHeight, overallWidth);
	    sdaiAppend((int) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWindowInstance);
    } else {
        //
        //      Build Window and add it to the BuildingStorey
        //
        ifcWindowInstance = buildWindowInstance(&matrix, ifcBuildingStoreyInstancePlacement, &ifcWindowInstancePlacement, pWindowName, overallHeight, overallWidth);
	    sdaiAppend((int) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWindowInstance);
    }

	return	ifcWindowInstance;
}

int		createIfcWindow(char * pWindowName,
                        double xRefDirection, double yRefDirection, double zRefDirection,
                        double xAxis, double yAxis, double zAxis,
                        double xOffset, double yOffset, double zOffset,
                        bool insideOpening,
                        double overallHeight,
                        double overallWidth)
{
    transformationMatrixStruct  matrix;
    int ifcWindowInstance, ifcWindowInstancePlacement;

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

    if  (insideOpening) {
        //
        //      Build Window
        //
        ifcWindowInstance = buildWindowInstance(&matrix, ifcOpeningElementInstancePlacement, &ifcWindowInstancePlacement, pWindowName, overallHeight, overallWidth);
	    sdaiAppend((int) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWindowInstance);
    } else {
        //
        //      Build Window and add it to the BuildingStorey
        //
        ifcWindowInstance = buildWindowInstance(&matrix, ifcBuildingStoreyInstancePlacement, &ifcWindowInstancePlacement, pWindowName, overallHeight, overallWidth);
	    sdaiAppend((int) aggrRelatedElements, sdaiINSTANCE, (void *) ifcWindowInstance);
    }

	ASSERT(ifcWindowInstance);

	return	ifcWindowInstance;
}


    
//
//
//		ProductDefinitionShape
//
//


int		buildProductDefinitionShapeInstance()
{
	int		ifcProductDefinitionShapeInstance;

	ifcProductDefinitionShapeInstance = sdaiCreateInstanceBN(model, "IFCPRODUCTDEFINITIONSHAPE");

	aggrRepresentations = sdaiCreateAggrBN(ifcProductDefinitionShapeInstance, "Representations");

	ASSERT(ifcProductDefinitionShapeInstance);

	return	ifcProductDefinitionShapeInstance;
}


//
//
//		IfcWall, IfcWallStandardCase, IfcOpeningElement, IfcWindow, IfcSpace, IfcFloor
//
//

int		buildRelDefinesByType(int relatedObjectInstance, int relatingTypeInstance)
{
	int		ifcRelDefinesByTypeInstance = sdaiCreateInstanceBN(model, "IFCRELDEFINESBYTYPE"), * aggrRelatedObjects;

	sdaiPutAttrBN(ifcRelDefinesByTypeInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelDefinesByTypeInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	aggrRelatedObjects = sdaiCreateAggrBN(ifcRelDefinesByTypeInstance, "RelatedObjects");
    sdaiAppend((int) aggrRelatedObjects, sdaiINSTANCE, (void*) relatedObjectInstance);
	sdaiPutAttrBN(ifcRelDefinesByTypeInstance, "RelatingType", sdaiINSTANCE, (void*) relatingTypeInstance);

	ASSERT(ifcRelDefinesByTypeInstance);

	return	ifcRelDefinesByTypeInstance;
}

int		buildWallTypeInstance(int ifcWallInstance, char * pWindowName, char * predefinedType)
{
	ASSERT(ifcWallInstance);

	int		ifcWallTypeInstance = sdaiCreateInstanceBN(model, "IFCWALLTYPE");

	sdaiPutAttrBN(ifcWallTypeInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcWallTypeInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcWallTypeInstance, "Name", sdaiSTRING, pWindowName);
	sdaiPutAttrBN(ifcWallTypeInstance, "Description", sdaiSTRING, "Description of Window Type");

	sdaiPutAttrBN(ifcWallTypeInstance, "PredefinedType", sdaiENUM, predefinedType);

	buildRelDefinesByType(ifcWallInstance, ifcWallTypeInstance);

	ASSERT(ifcWallTypeInstance);

	return	ifcWallTypeInstance;
}

int		buildWallInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcWallInstancePlacement, char * pWallName)
{
	int		ifcWallInstance = sdaiCreateInstanceBN(model, "IFCWALL");

	sdaiPutAttrBN(ifcWallInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcWallInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcWallInstance, "Name", sdaiSTRING, pWallName);
	sdaiPutAttrBN(ifcWallInstance, "Description", sdaiSTRING, "Description of Wall");

	(* ifcWallInstancePlacement) = buildLocalPlacementInstance(pMatrix, ifcPlacementRelativeTo);
	sdaiPutAttrBN(ifcWallInstance, "ObjectPlacement", sdaiINSTANCE, (void*) (* ifcWallInstancePlacement));
	sdaiPutAttrBN(ifcWallInstance, "Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());

	char	predefinedType[9] = "STANDARD";
	buildWallTypeInstance(ifcWallInstance, pWallName, predefinedType);
	sdaiPutAttrBN(ifcWallInstance, "PredefinedType", sdaiENUM, predefinedType);

	ASSERT(ifcWallInstance);

	return	ifcWallInstance;
}

int		buildWallStandardCaseInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcWallInstancePlacement, char * pWallName)
{
	int		ifcWallInstance = sdaiCreateInstanceBN(model, "IFCWALLSTANDARDCASE");

	sdaiPutAttrBN(ifcWallInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcWallInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcWallInstance, "Name", sdaiSTRING, pWallName);
	sdaiPutAttrBN(ifcWallInstance, "Description", sdaiSTRING, "Description of Wall");

	(* ifcWallInstancePlacement) = buildLocalPlacementInstance(pMatrix, ifcPlacementRelativeTo);
	sdaiPutAttrBN(ifcWallInstance, "ObjectPlacement", sdaiINSTANCE, (void*) (* ifcWallInstancePlacement));
	sdaiPutAttrBN(ifcWallInstance, "Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());

	char	predefinedType[9] = "STANDARD";
	buildWallTypeInstance(ifcWallInstance, pWallName, predefinedType);
	sdaiPutAttrBN(ifcWallInstance, "PredefinedType", sdaiENUM, predefinedType);

	ASSERT(ifcWallInstance);

	return	ifcWallInstance;
}

int		buildOpeningElementInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcOpeningElementInstancePlacement, char * pOpeningElementName, bool representation)
{
	int		ifcOpeningElementInstance = sdaiCreateInstanceBN(model, "IFCOPENINGELEMENT");

	sdaiPutAttrBN(ifcOpeningElementInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcOpeningElementInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcOpeningElementInstance, "Name", sdaiSTRING, pOpeningElementName);
	sdaiPutAttrBN(ifcOpeningElementInstance, "Description", sdaiSTRING, "Description of Opening");

	(* ifcOpeningElementInstancePlacement) = buildLocalPlacementInstance(pMatrix, ifcPlacementRelativeTo);
	sdaiPutAttrBN(ifcOpeningElementInstance, "ObjectPlacement", sdaiINSTANCE, (void*) (* ifcOpeningElementInstancePlacement));
    if  (representation) {
	    sdaiPutAttrBN(ifcOpeningElementInstance, "Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());
    }

	ASSERT(ifcOpeningElementInstance);

	return	ifcOpeningElementInstance;
}

int		buildDoorTypeInstance(int ifcDoorInstance, char * pWindowName, char * predefinedType, char * partitioningType)
{
	ASSERT(ifcDoorInstance);

	int		ifcDoorTypeInstance = sdaiCreateInstanceBN(model, "IFCDOORTYPE");

	sdaiPutAttrBN(ifcDoorTypeInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcDoorTypeInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcDoorTypeInstance, "Name", sdaiSTRING, pWindowName);
	sdaiPutAttrBN(ifcDoorTypeInstance, "Description", sdaiSTRING, "Description of Window Type");

	sdaiPutAttrBN(ifcDoorTypeInstance, "PredefinedType", sdaiENUM, predefinedType);
	sdaiPutAttrBN(ifcDoorTypeInstance, "PartitioningType", sdaiENUM, partitioningType);

	buildRelDefinesByType(ifcDoorInstance, ifcDoorTypeInstance);

	ASSERT(ifcDoorTypeInstance);

	return	ifcDoorTypeInstance;
}

int		buildDoorInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcDoorInstancePlacement, char * pDoorName, double overallHeight, double overallWidth)
{
	int		ifcDoorInstance = sdaiCreateInstanceBN(model, "IFCDOOR");

	sdaiPutAttrBN(ifcDoorInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcDoorInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcDoorInstance, "Name", sdaiSTRING, pDoorName);
	sdaiPutAttrBN(ifcDoorInstance, "Description", sdaiSTRING, "Description of Door");

	(* ifcDoorInstancePlacement) = buildLocalPlacementInstance(pMatrix, ifcPlacementRelativeTo);
	sdaiPutAttrBN(ifcDoorInstance, "ObjectPlacement", sdaiINSTANCE, (void*) (* ifcDoorInstancePlacement));
	sdaiPutAttrBN(ifcDoorInstance, "Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());

	char	predefinedType[7] = "DOOR", partitioningType[13] = "SINGLE_PANEL";
	buildDoorTypeInstance(ifcDoorInstance, pDoorName, predefinedType, partitioningType);
	sdaiPutAttrBN(ifcDoorInstance, "PredefinedType", sdaiENUM, predefinedType);
	sdaiPutAttrBN(ifcDoorInstance, "PartitioningType", sdaiENUM, partitioningType);

	sdaiPutAttrBN(ifcDoorInstance, "OverallHeight", sdaiREAL, &overallHeight);
	sdaiPutAttrBN(ifcDoorInstance, "OverallWidth", sdaiREAL, &overallWidth);

	ASSERT(ifcDoorInstance);

	return	ifcDoorInstance;
}

int		buildWindowTypeInstance(int ifcWindowInstance, char * pWindowName, char * predefinedType, char * partitioningType)
{
	ASSERT(ifcWindowInstance);

	int		ifcWindowTypeInstance = sdaiCreateInstanceBN(model, "IFCWINDOWTYPE");

	sdaiPutAttrBN(ifcWindowTypeInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcWindowTypeInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcWindowTypeInstance, "Name", sdaiSTRING, pWindowName);
	sdaiPutAttrBN(ifcWindowTypeInstance, "Description", sdaiSTRING, "Description of Window Type");

	sdaiPutAttrBN(ifcWindowTypeInstance, "PredefinedType", sdaiENUM, predefinedType);
	sdaiPutAttrBN(ifcWindowTypeInstance, "PartitioningType", sdaiENUM, partitioningType);

	buildRelDefinesByType(ifcWindowInstance, ifcWindowTypeInstance);

	ASSERT(ifcWindowTypeInstance);

	return	ifcWindowTypeInstance;
}

int		buildWindowInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcWindowInstancePlacement, char * pWindowName, double overallHeight, double overallWidth)
{
	ASSERT(ifcPlacementRelativeTo);

	int		ifcWindowInstance = sdaiCreateInstanceBN(model, "IFCWINDOW");

	sdaiPutAttrBN(ifcWindowInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcWindowInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcWindowInstance, "Name", sdaiSTRING, pWindowName);
	sdaiPutAttrBN(ifcWindowInstance, "Description", sdaiSTRING, "Description of Window");

	(* ifcWindowInstancePlacement) = buildLocalPlacementInstance(pMatrix, ifcPlacementRelativeTo);
	sdaiPutAttrBN(ifcWindowInstance, "ObjectPlacement", sdaiINSTANCE, (void*) (* ifcWindowInstancePlacement));
	sdaiPutAttrBN(ifcWindowInstance, "Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());

	char	predefinedType[7] = "WINDOW", partitioningType[13] = "SINGLE_PANEL";
	buildWindowTypeInstance(ifcWindowInstance, pWindowName, predefinedType, partitioningType);
	sdaiPutAttrBN(ifcWindowInstance, "PredefinedType", sdaiENUM, predefinedType);
	sdaiPutAttrBN(ifcWindowInstance, "PartitioningType", sdaiENUM, partitioningType);

	sdaiPutAttrBN(ifcWindowInstance, "OverallHeight", sdaiREAL, &overallHeight);
	sdaiPutAttrBN(ifcWindowInstance, "OverallWidth", sdaiREAL, &overallWidth);

	ASSERT(ifcWindowInstance);

	return	ifcWindowInstance;
}

int		buildSpaceInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcSpaceInstancePlacement, char * pSpaceName)
{
	int		ifcSpaceInstance = sdaiCreateInstanceBN(model, "IFCSPACE");

	sdaiPutAttrBN(ifcSpaceInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcSpaceInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcSpaceInstance, "Name", sdaiSTRING, pSpaceName);
	sdaiPutAttrBN(ifcSpaceInstance, "Description", sdaiSTRING, "Description of Space");

	(* ifcSpaceInstancePlacement) = buildLocalPlacementInstance(pMatrix, ifcPlacementRelativeTo);
	sdaiPutAttrBN(ifcSpaceInstance, "ObjectPlacement", sdaiINSTANCE, (void*) (* ifcSpaceInstancePlacement));
	sdaiPutAttrBN(ifcSpaceInstance, "Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());

	ASSERT(ifcSpaceInstance);

	return	ifcSpaceInstance;
}

int		buildRoofInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcRoofInstancePlacement, char * pRoofName)
{
	int		ifcRoofInstance = sdaiCreateInstanceBN(model, "IFCROOF");

	sdaiPutAttrBN(ifcRoofInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRoofInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcRoofInstance, "Name", sdaiSTRING, pRoofName);
	sdaiPutAttrBN(ifcRoofInstance, "Description", sdaiSTRING, "Description of Roof");

	(* ifcRoofInstancePlacement) = buildLocalPlacementInstance(pMatrix, ifcPlacementRelativeTo);
	sdaiPutAttrBN(ifcRoofInstance, "ObjectPlacement", sdaiINSTANCE, (void*) (* ifcRoofInstancePlacement));
	sdaiPutAttrBN(ifcRoofInstance, "Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());

	ASSERT(ifcRoofInstance);

	return	ifcRoofInstance;
}

int		buildSlabInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcSlabInstancePlacement, char * pSlabName)
{
	int		ifcSlabInstance = sdaiCreateInstanceBN(model, "IFCSLAB");

	sdaiPutAttrBN(ifcSlabInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcSlabInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcSlabInstance, "Name", sdaiSTRING, pSlabName);
	sdaiPutAttrBN(ifcSlabInstance, "Description", sdaiSTRING, "Description of Slab");

	(* ifcSlabInstancePlacement) = buildLocalPlacementInstance(pMatrix, ifcPlacementRelativeTo);
	sdaiPutAttrBN(ifcSlabInstance, "ObjectPlacement", sdaiINSTANCE, (void*) (* ifcSlabInstancePlacement));
	sdaiPutAttrBN(ifcSlabInstance, "Representation", sdaiINSTANCE, (void*) buildProductDefinitionShapeInstance());

	ASSERT(ifcSlabInstance);

	return	ifcSlabInstance;
}


//
//
//		RelVoidsElement, RelFillsElement
//
//


int		buildRelVoidsElementInstance(int ifcBuildingElementInstance, int ifcOpeningElementInstance)
{
	int		ifcRelVoidsElementInstance;

	ifcRelVoidsElementInstance = sdaiCreateInstanceBN(model, "IFCRELVOIDSELEMENT");

	sdaiPutAttrBN(ifcRelVoidsElementInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelVoidsElementInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	sdaiPutAttrBN(ifcRelVoidsElementInstance, "RelatingBuildingElement", sdaiINSTANCE, (void*) ifcBuildingElementInstance);
	sdaiPutAttrBN(ifcRelVoidsElementInstance, "RelatedOpeningElement", sdaiINSTANCE, (void*) ifcOpeningElementInstance);

	ASSERT(ifcRelVoidsElementInstance);

	return	ifcRelVoidsElementInstance;
}

int     buildRelFillsElementInstance(int ifcOpeningElementInstance, int ifcBuildingElementInstance)
{
	int		ifcRelFillsElementInstance;

	ifcRelFillsElementInstance = sdaiCreateInstanceBN(model, "IFCRELFILLSELEMENT");

	sdaiPutAttrBN(ifcRelFillsElementInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelFillsElementInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	sdaiPutAttrBN(ifcRelFillsElementInstance, "RelatingOpeningElement", sdaiINSTANCE, (void*) ifcOpeningElementInstance);
	sdaiPutAttrBN(ifcRelFillsElementInstance, "RelatedBuildingElement", sdaiINSTANCE, (void*) ifcBuildingElementInstance);

	return	ifcRelFillsElementInstance;
}


//
//
//      RelAssociatesMaterial, MaterialLayerSetUsage, MaterialLayerSet, MaterialLayer
//
//


int		buildRelAssociatesMaterial(int ifcBuildingElementInstance, int materialLayerSetUsage)
{
	int		ifcRelAssociatesMaterialInstance, * aggrRelatedObjects;

	ifcRelAssociatesMaterialInstance = sdaiCreateInstanceBN(model, "IFCRELASSOCIATESMATERIAL");

	sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	aggrRelatedObjects = sdaiCreateAggrBN(ifcRelAssociatesMaterialInstance, "RelatedObjects");
    sdaiAppend((int) aggrRelatedObjects, sdaiINSTANCE, (void*) ifcBuildingElementInstance);
	sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "RelatingMaterial", sdaiINSTANCE, (void*) materialLayerSetUsage);

	ASSERT(ifcRelAssociatesMaterialInstance);

	return	ifcRelAssociatesMaterialInstance;
}

int		buildRelAssociatesMaterial(int ifcBuildingElementInstance, double thickness)
{
	int		ifcRelAssociatesMaterialInstance, * aggrRelatedObjects;

	ifcRelAssociatesMaterialInstance = sdaiCreateInstanceBN(model, "IFCRELASSOCIATESMATERIAL");

	sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	aggrRelatedObjects = sdaiCreateAggrBN(ifcRelAssociatesMaterialInstance, "RelatedObjects");
    sdaiAppend((int) aggrRelatedObjects, sdaiINSTANCE, (void*) ifcBuildingElementInstance);
	sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "RelatingMaterial", sdaiINSTANCE, (void*) buildMaterialLayerSetUsage(thickness));

	return	ifcRelAssociatesMaterialInstance;
}

int     buildMaterialLayerSetUsage(double thickness)
{
	int		ifcMaterialLayerSetUsageInstance;
    double  offsetFromReferenceLine = -thickness/2;

	ifcMaterialLayerSetUsageInstance = sdaiCreateInstanceBN(model, "IFCMATERIALLAYERSETUSAGE");

	sdaiPutAttrBN(ifcMaterialLayerSetUsageInstance, "ForLayerSet", sdaiINSTANCE, (void*) buildMaterialLayerSet(thickness));
	sdaiPutAttrBN(ifcMaterialLayerSetUsageInstance, "LayerSetDirection", sdaiENUM, "AXIS2");
	sdaiPutAttrBN(ifcMaterialLayerSetUsageInstance, "DirectionSense", sdaiENUM, "POSITIVE");
	sdaiPutAttrBN(ifcMaterialLayerSetUsageInstance, "OffsetFromReferenceLine", sdaiREAL, &offsetFromReferenceLine);

	ASSERT(ifcMaterialLayerSetUsageInstance);

    return  ifcMaterialLayerSetUsageInstance;
}

int     buildMaterialLayerSet(double thickness)
{
	int		ifcMaterialLayerSetInstance, * aggrMaterialLayers;

	ifcMaterialLayerSetInstance = sdaiCreateInstanceBN(model, "IFCMATERIALLAYERSET");

	aggrMaterialLayers = sdaiCreateAggrBN(ifcMaterialLayerSetInstance, "MaterialLayers");
    sdaiAppend((int) aggrMaterialLayers, sdaiINSTANCE, (void*) buildMaterialLayer(thickness));

    return  ifcMaterialLayerSetInstance;
}

int     buildMaterialLayer(double thickness)
{
	int		ifcMaterialLayerInstance;

	ifcMaterialLayerInstance = sdaiCreateInstanceBN(model, "IFCMATERIALLAYER");

	sdaiPutAttrBN(ifcMaterialLayerInstance, "Material", sdaiINSTANCE, (void*) buildMaterial());
	sdaiPutAttrBN(ifcMaterialLayerInstance, "LayerThickness", sdaiREAL, &thickness);

    return  ifcMaterialLayerInstance;
}

int     buildMaterial()
{
	int		ifcMaterialInstance;

	ifcMaterialInstance = sdaiCreateInstanceBN(model, "IFCMATERIAL");

	sdaiPutAttrBN(ifcMaterialInstance, "Name", sdaiSTRING, (void*) "Name of the material used for the wall");

    return  ifcMaterialInstance;
}


//
//
//		RelSpaceBoundary
//
//


int		buildRelSpaceBoundaryInstance(int ifcRelatingSpaceInstance, int ifcRelatedBuildingElementInstance, char * pSpaceBoundaryName, char * pSpaceBoundaryDescription, transformationMatrixStruct * pMatrix, point2DListStruct * pPoints)
{
	int		ifcRelSpaceBoundaryInstance;

	ifcRelSpaceBoundaryInstance = sdaiCreateInstanceBN(model, "IFCRELSPACEBOUNDARY");

	sdaiPutAttrBN(ifcRelSpaceBoundaryInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelSpaceBoundaryInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcRelSpaceBoundaryInstance, "Name", sdaiSTRING, pSpaceBoundaryName);
	sdaiPutAttrBN(ifcRelSpaceBoundaryInstance, "Description", sdaiSTRING, pSpaceBoundaryDescription);

	sdaiPutAttrBN(ifcRelSpaceBoundaryInstance, "RelatingSpace", sdaiINSTANCE, (void*) ifcRelatingSpaceInstance);
	sdaiPutAttrBN(ifcRelSpaceBoundaryInstance, "RelatedBuildingElement", sdaiINSTANCE, (void*) ifcRelatedBuildingElementInstance);
	sdaiPutAttrBN(ifcRelSpaceBoundaryInstance, "ConnectionGeometry", sdaiINSTANCE, (void*) buildConnectionSurfaceGeometryInstance(pMatrix, pPoints));
	sdaiPutAttrBN(ifcRelSpaceBoundaryInstance, "PhysicalOrVirtualBoundary", sdaiENUM, "PHYSICAL");
	sdaiPutAttrBN(ifcRelSpaceBoundaryInstance, "InternalOrExternalBoundary", sdaiENUM, "EXTERNAL");

	ASSERT(ifcRelSpaceBoundaryInstance);

	return	ifcRelSpaceBoundaryInstance;
}

int		buildRelSpaceBoundary1stLevelInstance(int ifcRelatingSpaceInstance, int ifcRelatedBuildingElementInstance, char * pSpaceBoundaryName, char * pSpaceBoundaryDescription, transformationMatrixStruct * pMatrix, point2DListStruct * pPoints, int parentBoundary)
{
	int		ifcRelSpaceBoundary1stLevelInstance;

	ifcRelSpaceBoundary1stLevelInstance = sdaiCreateInstanceBN(model, "IFCRELSPACEBOUNDARY1ST	LEVEL");

	sdaiPutAttrBN(ifcRelSpaceBoundary1stLevelInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelSpaceBoundary1stLevelInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcRelSpaceBoundary1stLevelInstance, "Name", sdaiSTRING, pSpaceBoundaryName);
	sdaiPutAttrBN(ifcRelSpaceBoundary1stLevelInstance, "Description", sdaiSTRING, pSpaceBoundaryDescription);

	sdaiPutAttrBN(ifcRelSpaceBoundary1stLevelInstance, "RelatingSpace", sdaiINSTANCE, (void*) ifcRelatingSpaceInstance);
	sdaiPutAttrBN(ifcRelSpaceBoundary1stLevelInstance, "RelatedBuildingElement", sdaiINSTANCE, (void*) ifcRelatedBuildingElementInstance);
	sdaiPutAttrBN(ifcRelSpaceBoundary1stLevelInstance, "ConnectionGeometry", sdaiINSTANCE, (void*) buildConnectionSurfaceGeometryInstance(pMatrix, pPoints));
	sdaiPutAttrBN(ifcRelSpaceBoundary1stLevelInstance, "PhysicalOrVirtualBoundary", sdaiENUM, "PHYSICAL");
	sdaiPutAttrBN(ifcRelSpaceBoundary1stLevelInstance, "InternalOrExternalBoundary", sdaiENUM, "EXTERNAL");

	sdaiPutAttrBN(ifcRelSpaceBoundary1stLevelInstance, "ParentBoundary", sdaiINSTANCE, (void*) parentBoundary);

	ASSERT(ifcRelSpaceBoundary1stLevelInstance);
	
	return	ifcRelSpaceBoundary1stLevelInstance;
}


int		buildRelSpaceBoundary2ndLevelInstance(int ifcRelatingSpaceInstance, int ifcRelatedBuildingElementInstance, char * pSpaceBoundaryName, char * pSpaceBoundaryDescription, transformationMatrixStruct * pMatrix, point2DListStruct * pPoints, int parentBoundary, int correspondingBoundary)
{
	int		ifcRelSpaceBoundary2ndLevelInstance;

	ifcRelSpaceBoundary2ndLevelInstance = sdaiCreateInstanceBN(model, "IFCRELSPACEBOUNDARY2NDLEVEL");

	sdaiPutAttrBN(ifcRelSpaceBoundary2ndLevelInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelSpaceBoundary2ndLevelInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcRelSpaceBoundary2ndLevelInstance, "Name", sdaiSTRING, pSpaceBoundaryName);
	sdaiPutAttrBN(ifcRelSpaceBoundary2ndLevelInstance, "Description", sdaiSTRING, pSpaceBoundaryDescription);

	sdaiPutAttrBN(ifcRelSpaceBoundary2ndLevelInstance, "RelatingSpace", sdaiINSTANCE, (void*) ifcRelatingSpaceInstance);
	sdaiPutAttrBN(ifcRelSpaceBoundary2ndLevelInstance, "RelatedBuildingElement", sdaiINSTANCE, (void*) ifcRelatedBuildingElementInstance);
	sdaiPutAttrBN(ifcRelSpaceBoundary2ndLevelInstance, "ConnectionGeometry", sdaiINSTANCE, (void*) buildConnectionSurfaceGeometryInstance(pMatrix, pPoints));
	sdaiPutAttrBN(ifcRelSpaceBoundary2ndLevelInstance, "PhysicalOrVirtualBoundary", sdaiENUM, "PHYSICAL");
	sdaiPutAttrBN(ifcRelSpaceBoundary2ndLevelInstance, "InternalOrExternalBoundary", sdaiENUM, "EXTERNAL");

	sdaiPutAttrBN(ifcRelSpaceBoundary2ndLevelInstance, "ParentBoundary", sdaiINSTANCE, (void*) parentBoundary);
	sdaiPutAttrBN(ifcRelSpaceBoundary2ndLevelInstance, "CorrespondingBoundary", sdaiINSTANCE, (void*) correspondingBoundary);

	ASSERT(ifcRelSpaceBoundary2ndLevelInstance);
	
	return	ifcRelSpaceBoundary2ndLevelInstance;
}


int		buildConnectionSurfaceGeometryInstance(transformationMatrixStruct * pMatrix, point2DListStruct * pPoints)
{
	int		ifcConnectionSurfaceGeometryInstance;

	ifcConnectionSurfaceGeometryInstance = sdaiCreateInstanceBN(model, "IFCCONNECTIONSURFACEGEOMETRY");

	sdaiPutAttrBN(ifcConnectionSurfaceGeometryInstance, "SurfaceOnRelatingElement", sdaiINSTANCE, (void*) buildCurveBoundedPlaneInstance(pMatrix, pPoints));

	ASSERT(ifcConnectionSurfaceGeometryInstance);

	return	ifcConnectionSurfaceGeometryInstance;
}

int		buildCurveBoundedPlaneInstance(transformationMatrixStruct * pMatrix, point2DListStruct * pPoints)
{
	int		ifcCurveBoundedPlaneInstance;

	ifcCurveBoundedPlaneInstance = sdaiCreateInstanceBN(model, "IFCCURVEBOUNDEDPLANE");

	sdaiPutAttrBN(ifcCurveBoundedPlaneInstance, "BasisSurface", sdaiINSTANCE, (void*) buildPlaneInstance(pMatrix));
	sdaiPutAttrBN(ifcCurveBoundedPlaneInstance, "OuterBoundary", sdaiINSTANCE, (void*) build2DCompositeCurveInstance(pPoints));

	ASSERT(ifcCurveBoundedPlaneInstance);

	return	ifcCurveBoundedPlaneInstance;
}

int		buildPlaneInstance(transformationMatrixStruct * pMatrix)
{
	int		ifcPlaneInstance;

	ifcPlaneInstance = sdaiCreateInstanceBN(model, "IFCPLANE");

	sdaiPutAttrBN(ifcPlaneInstance, "Position", sdaiINSTANCE, (void*) buildAxis2Placement3DInstance(pMatrix));

	ASSERT(ifcPlaneInstance);

	return	ifcPlaneInstance;
}
  
int		build2DCompositeCurveInstance(point2DListStruct * pPoints)
{
	int		ifc2DCompositeCurveInstance, * aggrSegments;

//	ifc2DCompositeCurveInstance = sdaiCreateInstanceBN(model, "IFC2DCOMPOSITECURVE");
	ifc2DCompositeCurveInstance = sdaiCreateInstanceBN(model, "IFCCOMPOSITECURVE");

	aggrSegments = sdaiCreateAggrBN(ifc2DCompositeCurveInstance, "Segments");
    sdaiAppend((int) aggrSegments, sdaiINSTANCE, (void*) buildCompositeCurveSegmentInstance(pPoints));

	sdaiPutAttrBN(ifc2DCompositeCurveInstance, "SelfIntersect", sdaiENUM, "U");

	ASSERT(ifc2DCompositeCurveInstance);

	return	ifc2DCompositeCurveInstance;
}
  
int		buildCompositeCurveSegmentInstance(point2DListStruct * pPoints)
{
	int		ifcCompositeCurveSegmentInstance;

	ifcCompositeCurveSegmentInstance = sdaiCreateInstanceBN(model, "IFCCOMPOSITECURVESEGMENT");

	sdaiPutAttrBN(ifcCompositeCurveSegmentInstance, "Transition", sdaiENUM, "CONTINUOUS");
	sdaiPutAttrBN(ifcCompositeCurveSegmentInstance, "SameSense", sdaiENUM, "F");
	sdaiPutAttrBN(ifcCompositeCurveSegmentInstance, "ParentCurve", sdaiINSTANCE, (void*) buildPolylineInstance(pPoints));

	ASSERT(ifcCompositeCurveSegmentInstance);

	return	ifcCompositeCurveSegmentInstance;
}
  
int		buildPolylineInstance(point2DListStruct * pPoints)
{
	POINT2DLISTSTRUCT	* pFirstPoint = pPoints;
	int		ifcPolylineInstance, * aggrPoints;

	ifcPolylineInstance = sdaiCreateInstanceBN(model, "IFCPOLYLINE");

	aggrPoints = sdaiCreateAggrBN(ifcPolylineInstance, "Points");
	while  (pPoints) {
		sdaiAppend((int) aggrPoints, sdaiINSTANCE, (void*) buildCartesianPointInstance(pPoints));
		pPoints = pPoints->next;
	}
	sdaiAppend((int) aggrPoints, sdaiINSTANCE, (void*) buildCartesianPointInstance(pFirstPoint));

	ASSERT(ifcPolylineInstance);

	return	ifcPolylineInstance;
}
  
int		buildCartesianPointInstance(point2DListStruct * pPoint2D)
{
	int		ifcCartesianPointInstance, * aggrCoordinates;

	ifcCartesianPointInstance = sdaiCreateInstanceBN(model, "IFCCARTESIANPOINT");

	aggrCoordinates = sdaiCreateAggrBN(ifcCartesianPointInstance, "Coordinates");
    sdaiAppend((int) aggrCoordinates, sdaiREAL, &pPoint2D->x);
    sdaiAppend((int) aggrCoordinates, sdaiREAL, &pPoint2D->y);

	ASSERT(ifcCartesianPointInstance);

	return	ifcCartesianPointInstance;
}
  
