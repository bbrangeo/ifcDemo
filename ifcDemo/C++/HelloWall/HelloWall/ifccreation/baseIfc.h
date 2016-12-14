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


#include "../ifcengine/include/ifcengine.h"


struct	MATRIX {
	double			_11;
	double			_12;
	double			_13;
	double			_21;
	double			_22;
	double			_23;
	double			_31;
	double			_32;
	double			_33;
	double			_41;
	double			_42;
	double			_43;
};

struct	POINT3D {
	double			x;
	double			y;
	double			z;
#ifdef WIN64
	__int64			ifcCartesianPointInstance;
#else
	__int32			ifcCartesianPointInstance;
#endif
};


void	identityMatrix(MATRIX * matrix);
void	identityPoint(POINT3D * point);
#ifdef WIN64
__int64	* getTimeStamp();
#else
__int32	* getTimeStamp();
#endif


//
//
//	GUID
//
//


#ifdef UNICODE
static const wchar_t *cConversionTable64 =
	L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_$";

wchar_t	* CreateCompressedGuidString();
wchar_t	* getString64FromGuid(const GUID *pGuid, wchar_t * buf, size_t numberOfElements);
bool	cv_to_64(const unsigned long number, wchar_t *code, size_t numberOfElements, __int32 len);
#else
static const char *cConversionTable64 =
	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_$";

char	* CreateCompressedGuidString();
char	* getString64FromGuid(const GUID *pGuid, char * buf, size_t numberOfElements);
bool	cv_to_64(const unsigned long number, char *code, size_t numberOfElements, __int32 len);
#endif


#ifdef WIN64
#ifdef UNICODE
__int64	createEmptyIfcFile(wchar_t * ifcSchemaName, bool objectsWillBeAdded, wchar_t * lengthUnitConversion);
#else
__int64	createEmptyIfcFile(char * ifcSchemaName, bool objectsWillBeAdded, char * lengthUnitConversion);
#endif
#else
#ifdef UNICODE
__int32	createEmptyIfcFile(wchar_t * ifcSchemaName, bool objectsWillBeAdded, wchar_t * lengthUnitConversion);
#else
__int32	createEmptyIfcFile(char * ifcSchemaName, bool objectsWillBeAdded, char * lengthUnitConversion);
#endif
#endif
#ifdef UNICODE
bool	saveIfcFile(wchar_t * ifcFileName);
bool	saveIfcFileAsXml(wchar_t * ifcFileName);
#else
bool	saveIfcFile(char * ifcFileName);
bool	saveIfcFileAsXml(char * ifcFileName);
#endif


//
//
//		Application, Organization, Person (OwnerHistory, PersonAndOrganization)
//
//


#ifdef WIN64
__int64	getApplicationInstance();
__int64	getOrganizationInstance();
__int64	getOwnerHistoryInstance();
__int64	getPersonAndOrganizationInstance();
__int64	getPersonInstance();
#else
__int32	getApplicationInstance();
__int32	getOrganizationInstance();
__int32	getOwnerHistoryInstance();
__int32	getPersonAndOrganizationInstance();
__int32	getPersonInstance();
#endif


//
//
//		CartesianPoint, Direction, LocalPlacement (Axis2Placement)
//
//


#ifdef WIN64
__int64	buildAxis2Placement3DInstance(MATRIX * matrix);
__int64	buildCartesianPointInstance(POINT3D * point);
__int64	buildDirectionInstance(POINT3D * point);
__int64	buildLocalPlacementInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo);
#else
__int32	buildAxis2Placement3DInstance(MATRIX * matrix);
__int32	buildCartesianPointInstance(POINT3D * point);
__int32	buildDirectionInstance(POINT3D * point);
__int32	buildLocalPlacementInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo);
#endif


//
//
//		ConversionBasedUnit, DimensionalExponents, MeasureWithUnit, SIUnit, UnitAssignment
//
//


#ifdef WIN64
__int64	getConversionBasedUnitInstance();
__int64	getDimensionalExponentsInstance();
__int64	buildMeasureWithUnitInstance();
#ifdef UNICODE
__int64	buildSIUnitInstance(wchar_t * UnitType, wchar_t * Prefix, wchar_t * Name);
__int64	getUnitAssignmentInstance(wchar_t * lengthUnitConversion);
#else
__int64	buildSIUnitInstance(char * UnitType, char * Prefix, char * Name);
__int64	getUnitAssignmentInstance(char * lengthUnitConversion);
#endif
#else
__int32	getConversionBasedUnitInstance();
__int32	getDimensionalExponentsInstance();
__int32	buildMeasureWithUnitInstance();
#ifdef UNICODE
__int32	buildSIUnitInstance(wchar_t * UnitType, wchar_t * Prefix, wchar_t * Name);
__int32	getUnitAssignmentInstance(wchar_t * lengthUnitConversion);
#else
__int32	buildSIUnitInstance(char * UnitType, char * Prefix, char * Name);
__int32	getUnitAssignmentInstance(char * lengthUnitConversion);
#endif
#endif


//
//
//		RelAggregates, RelContainedInSpatialStructure
//
//


#ifdef WIN64
#ifdef UNICODE
__int64	buildRelAggregatesInstance(wchar_t * name, wchar_t * description, __int64 ifcRelatingObjectInstance, __int64 ifcRelatedObjectInstance);
__int64	buildRelContainedInSpatialStructureInstance(wchar_t * name, wchar_t * description, __int64 ifcRelatingStructureInstance, __int64 ** aggrRelatedElements);
#else
__int64	buildRelAggregatesInstance(char * name, char * description, __int64 ifcRelatingObjectInstance, __int64 ifcRelatedObjectInstance);
__int64	buildRelContainedInSpatialStructureInstance(char * name, char * description, __int64 ifcRelatingStructureInstance, __int64 ** aggrRelatedElements);
#endif
#else
#ifdef UNICODE
__int32	buildRelAggregatesInstance(wchar_t * name, wchar_t * description, __int32 ifcRelatingObjectInstance, __int32 ifcRelatedObjectInstance);
__int32	buildRelContainedInSpatialStructureInstance(wchar_t * name, wchar_t * description, __int32 ifcRelatingStructureInstance, __int32 ** aggrRelatedElements);
#else
__int32	buildRelAggregatesInstance(char * name, char * description, __int32 ifcRelatingObjectInstance, __int32 ifcRelatedObjectInstance);
__int32	buildRelContainedInSpatialStructureInstance(char * name, char * description, __int32 ifcRelatingStructureInstance, __int32 ** aggrRelatedElements);
#endif
#endif


//
//
//		Building, BuildingStorey, Project, Site
//
//


#ifdef WIN64
__int64	buildBuildingInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcBuildingInstancePlacement);
__int64	buildBuildingStoreyInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcBuildingStoreyInstancePlacement);
#ifdef UNICODE
__int64	getProjectInstance(wchar_t * lengthUnitConversion);
#else
__int64	getProjectInstance(char * lengthUnitConversion);
#endif
__int64	buildSiteInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcSiteInstancePlacement);
#else
__int32	buildBuildingInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcBuildingInstancePlacement);
__int32	buildBuildingStoreyInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcBuildingStoreyInstancePlacement);
#ifdef UNICODE
__int32	getProjectInstance(wchar_t * lengthUnitConversion);
#else
__int32	getProjectInstance(char * lengthUnitConversion);
#endif
__int32	buildSiteInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcSiteInstancePlacement);
#endif


//
//
//		WorldCoordinateSystem, GeometricRepresentationContext
//
//


#ifdef WIN64
__int64	getWorldCoordinateSystemInstance();
__int64	getGeometricRepresentationContextInstance();
#else
__int32	getWorldCoordinateSystemInstance();
__int32	getGeometricRepresentationContextInstance();
#endif


//
//
//		PostalAddress
//
//


#ifdef WIN64
__int64	buildPostalAddress();
#else
__int32	buildPostalAddress();
#endif
