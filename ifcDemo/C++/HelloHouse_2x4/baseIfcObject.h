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


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "baseIfc.h"


typedef struct POINT2DLISTSTRUCT {
	double				x;
	double				y;
    POINT2DLISTSTRUCT	* next;
}	point2DListStruct;


int		createIfcWall(char * pWallName, transformationMatrixStruct matrix);
int		createIfcWall(char * pWallName, double xOffset, double yOffset, double zOffset);
int		createIfcWallStandardCase(char * pWallName, double xOffset, double yOffset, double zOffset);
int		createIfcOpeningElement(char * pOpeningElementName, double xOffset, double yOffset, double zOffset, bool representation);
int		createIfcOpeningElement(char * pOpeningElementName,
                                double xRefDirection, double yRefDirection, double zRefDirection,
                                double xAxis, double yAxis, double zAxis,
                                double xOffset, double yOffset, double zOffset,
                                bool representation);
int		createIfcDoor(char * pDoorName, double xOffset, double yOffset, double zOffset, bool insideOpening, double overallHeight, double overallWidth);
int		createIfcDoor(char * pDoorName,
                      double xRefDirection, double yRefDirection, double zRefDirection,
                      double xAxis, double yAxis, double zAxis,
                      double xOffset, double yOffset, double zOffset,
                      bool insideOpening,
                      double overallHeight,
                      double overallWidth);
int		createIfcWindow(char * pWindowName, double xOffset, double yOffset, double zOffset, bool insideOpening, double overallHeight, double overallWidth);
int		createIfcWindow(char * pWindowName,
                        double xRefDirection, double yRefDirection, double zRefDirection,
                        double xAxis, double yAxis, double zAxis,
                        double xOffset, double yOffset, double zOffset,
                        bool insideOpening,
                        double overallHeight,
                        double overallWidth);
int		createIfcSpace(char * pSpaceName, transformationMatrixStruct matrix);
int		createIfcRoof(char * pRoofName, transformationMatrixStruct matrix);
int		createIfcSlab(char * pSlabName, transformationMatrixStruct matrix);


//
//
//		ProductDefinitionShape
//
//


int		buildProductDefinitionShapeInstance();


//
//
//		IfcWall, IfcWallStandardCase, IfcOpeningElement, IfcWindow, IfcSpace, IfcFloor, IfcSlab
//
//


int		buildWallInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcWallInstancePlacement, char * pWallName);
int		buildWallStandardCaseInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcWallInstancePlacement, char * pWallName);
int		buildOpeningElementInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcOpeningElementInstancePlacement, char * pOpeningElementName, bool representation);
int		buildDoorInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcDoorInstancePlacement, char * pDoorName, double overallHeight, double overallWidth);
int		buildWindowInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcWindowInstancePlacement, char * pWindowName, double overallHeight, double overallWidth);
int		buildSpaceInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcSpaceInstancePlacement, char * pSpaceName);
int		buildRoofInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcRoofInstancePlacement, char * pRoofName);
int		buildSlabInstance(transformationMatrixStruct * pMatrix, int ifcPlacementRelativeTo, int * ifcSlabInstancePlacement, char * pSlabName);


//
//
//		RelVoidsElement, RelFillsElement
//
//


int		buildRelVoidsElementInstance(int ifcBuildingElementInstance, int ifcOpeningElementInstance);
int     buildRelFillsElementInstance(int ifcOpeningElementInstance, int ifcBuildingElementInstance);


//
//
//      RelAssociatesMaterial, MaterialLayerSetUsage, MaterialLayerSet, MaterialLayer
//
//


int		buildRelAssociatesMaterial(int ifcBuildingElementInstance, double thickness);
int     buildMaterialLayerSetUsage(double thickness);
int     buildMaterialLayerSet(double thickness);
int     buildMaterialLayer(double thickness);
int     buildMaterial();


//
//
//		RelSpaceBoundary
//
//


int		buildRelSpaceBoundaryInstance(int ifcRelatingSpaceInstance, int ifcRelatedBuildingElementInstance, char * pSpaceBoundaryName, char * pSpaceBoundaryDescription, transformationMatrixStruct * pMatrix, point2DListStruct * pPoints);
int		buildRelSpaceBoundary1stLevelInstance(int ifcRelatingSpaceInstance, int ifcRelatedBuildingElementInstance, char * pSpaceBoundaryName, char * pSpaceBoundaryDescription, transformationMatrixStruct * pMatrix, point2DListStruct * pPoints, int parentBoundary);
int		buildRelSpaceBoundary2ndLevelInstance(int ifcRelatingSpaceInstance, int ifcRelatedBuildingElementInstance, char * pSpaceBoundaryName, char * pSpaceBoundaryDescription, transformationMatrixStruct * pMatrix, point2DListStruct * pPoints, int parentBoundary, int correspondingBoundary);
int		buildConnectionSurfaceGeometryInstance(transformationMatrixStruct * pMatrix, point2DListStruct * pPoints);
int		buildCurveBoundedPlaneInstance(transformationMatrixStruct * pMatrix, point2DListStruct * pPoints);
int		buildPlaneInstance(transformationMatrixStruct * pMatrix);
int		build2DCompositeCurveInstance(point2DListStruct * pPoints);
int		buildCompositeCurveSegmentInstance(point2DListStruct * pPoints);
int		buildPolylineInstance(point2DListStruct * pPoints);
int		buildCartesianPointInstance(point2DListStruct * pPoint2D);