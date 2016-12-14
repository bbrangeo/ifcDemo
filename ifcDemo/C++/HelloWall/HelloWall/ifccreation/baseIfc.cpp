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
#include "baseIfc.h"

#ifdef WIN64
__int64	model = 0,
		timeStamp,
		* aggrRelatedElements,
		* aggr_ifcRelDeclaresInstance_RelatedDefinitions_ProjectLibrary,
		ifcApplicationInstance,
		ifcBuildingInstance,
		ifcBuildingInstancePlacement,
		ifcBuildingStoreyInstance,
		ifcBuildingStoreyInstancePlacement,
		ifcBuildOwnerHistoryInstance,
		ifcConversionBasedUnitInstance,
		ifcDimensionalExponentsInstance,
		ifcGeometricRepresentationContextInstance,
		ifcOrganizationInstance,
		ifcPersonAndOrganizationInstance,
		ifcPersonInstance,
		ifcPostalAddressInstance,
		ifcProjectInstance,
		ifcRelDeclaresInstance,
		ifcSiteInstance,
		ifcSiteInstancePlacement,
		ifcUnitAssignmentInstance;
#else
__int32	model = 0,
		timeStamp,
		* aggrRelatedElements,
		* aggr_ifcRelDeclaresInstance_RelatedDefinitions_ProjectLibrary,
		ifcApplicationInstance,
		ifcBuildingInstance,
		ifcBuildingInstancePlacement,
		ifcBuildingStoreyInstance,
		ifcBuildingStoreyInstancePlacement,
		ifcBuildOwnerHistoryInstance,
		ifcConversionBasedUnitInstance,
		ifcDimensionalExponentsInstance,
		ifcGeometricRepresentationContextInstance,
		ifcOrganizationInstance,
		ifcPersonAndOrganizationInstance,
		ifcPersonInstance,
		ifcPostalAddressInstance,
		ifcProjectInstance,
		ifcRelDeclaresInstance,
		ifcSiteInstance,
		ifcSiteInstancePlacement,
		ifcUnitAssignmentInstance;
#endif


#ifdef WIN64
#ifdef UNICODE
__int64	createEmptyIfcFile(wchar_t * ifcSchemaName, bool objectsWillBeAdded, wchar_t * lengthUnitConversion)
#else
__int64	createEmptyIfcFile(char * ifcSchemaName, bool objectsWillBeAdded, char * lengthUnitConversion)
#endif
#else
#ifdef UNICODE
__int32	createEmptyIfcFile(wchar_t * ifcSchemaName, bool objectsWillBeAdded, wchar_t * lengthUnitConversion)
#else
__int32	createEmptyIfcFile(char * ifcSchemaName, bool objectsWillBeAdded, char * lengthUnitConversion)
#endif
#endif
{
	MATRIX	matrix;
	
#ifdef UNICODE
	model = sdaiCreateModelBNUnicode(1, 0, ifcSchemaName);
#else
	model = sdaiCreateModelBN(1, 0, ifcSchemaName);
#endif

	if	(model) {
		identityMatrix(&matrix);

		ifcApplicationInstance = 0;
		ifcBuildOwnerHistoryInstance = 0;
		ifcConversionBasedUnitInstance = 0;
		ifcDimensionalExponentsInstance = 0;
		ifcGeometricRepresentationContextInstance = 0;
		ifcOrganizationInstance = 0;
		ifcPersonAndOrganizationInstance = 0;
		ifcPersonInstance = 0;
		ifcPostalAddressInstance = 0;
		ifcUnitAssignmentInstance = 0;

		ifcRelDeclaresInstance = 0;

		aggr_ifcRelDeclaresInstance_RelatedDefinitions_ProjectLibrary = 0;

		//
		//	Build standard IFC structures
		//

		//
		//		Build standard IFC objects
		//
		ifcProjectInstance = getProjectInstance(lengthUnitConversion);
		ifcSiteInstance = buildSiteInstance(&matrix, 0, &ifcSiteInstancePlacement);
		ifcBuildingInstance = buildBuildingInstance(&matrix, ifcSiteInstancePlacement, &ifcBuildingInstancePlacement);
		ifcBuildingStoreyInstance = buildBuildingStoreyInstance(&matrix, ifcBuildingInstancePlacement, &ifcBuildingStoreyInstancePlacement);

		//
		//		Build relations
		//
#ifdef UNICODE
		buildRelAggregatesInstance(L"BuildingContainer", L"BuildingContainer for BuildigStories", ifcBuildingInstance, ifcBuildingStoreyInstance);
		buildRelAggregatesInstance(L"SiteContainer", L"SiteContainer For Buildings", ifcSiteInstance, ifcBuildingInstance);
		buildRelAggregatesInstance(L"ProjectContainer", L"ProjectContainer for Sites", ifcProjectInstance, ifcSiteInstance);
#else
		buildRelAggregatesInstance("BuildingContainer", "BuildingContainer for BuildigStories", ifcBuildingInstance, ifcBuildingStoreyInstance);
		buildRelAggregatesInstance("SiteContainer", "SiteContainer For Buildings", ifcSiteInstance, ifcBuildingInstance);
		buildRelAggregatesInstance("ProjectContainer", "ProjectContainer for Sites", ifcProjectInstance, ifcSiteInstance);
#endif

		if	(objectsWillBeAdded) {
#ifdef UNICODE
			buildRelContainedInSpatialStructureInstance(L"BuildingStoreyContainer", L"BuildingStoreyContainer for Building Elements", ifcBuildingStoreyInstance, &aggrRelatedElements);
#else
			buildRelContainedInSpatialStructureInstance("BuildingStoreyContainer", "BuildingStoreyContainer for Building Elements", ifcBuildingStoreyInstance, &aggrRelatedElements);
#endif
		}

		return	model;
	} else {
		return	0;
	}
}

#ifdef UNICODE
bool	saveIfcFile(wchar_t * ifcFileName)
#else
bool	saveIfcFile(char * ifcFileName)
#endif
{
	if	(model) {
		//
		//	Save the created configuration
		//
#ifdef UNICODE
		sdaiSaveModelBNUnicode(model, ifcFileName);
#else
		sdaiSaveModelBN(model, ifcFileName);
#endif

		return	true;
	} else {
		return	false;
	}
}

#ifdef UNICODE
bool	saveIfcFileAsXml(wchar_t * ifcFileName)
#else
bool	saveIfcFileAsXml(char * ifcFileName)
#endif
{
	if	(model) {
		//
		//  Save the created configuration
		//
#ifdef UNICODE
		sdaiSaveModelAsXmlBNUnicode(model, ifcFileName);
#else
		sdaiSaveModelAsXmlBN(model, ifcFileName);
#endif

		return	true;
	} else {
		return	false;
	}
}

void	identityMatrix(MATRIX * matrix)
{
	matrix->_11 = 1;
	matrix->_12 = 0;
	matrix->_13 = 0;
	matrix->_21 = 0;
	matrix->_22 = 1;
	matrix->_23 = 0;
	matrix->_31 = 0;
	matrix->_32 = 0;
	matrix->_33 = 1;
	matrix->_41 = 0;
	matrix->_42 = 0;
	matrix->_43 = 0;
}

void	identityPoint(POINT3D * point)
{
	point->x = 0;
	point->y = 0;
	point->z = 0;
}

#ifdef WIN64
__int64	* getTimeStamp()
#else
__int32	* getTimeStamp()
#endif
{
#ifdef WIN64
	timeStamp = (__int64) time(0);
#else
	timeStamp = (__int32) time(0);
#endif

	return	&timeStamp;
}


//
//
//	GUID
//
//


#ifdef UNICODE
wchar_t	* CreateCompressedGuidString()
#else
char	* CreateCompressedGuidString()
#endif
{
#ifdef UNICODE
	wchar_t	* buf = (wchar_t*) malloc(23 * sizeof(wchar_t));
#else
	char	* buf = (char*) malloc(23 * sizeof(char));
#endif
	GUID	guid = GUID_NULL;

	//
	// Call to the function from Microsoft
	//
	CoCreateGuid(&guid);

	if	(memcmp(&GUID_NULL, &guid, sizeof(GUID)) == 0) {
		return	0;
	}

	return	getString64FromGuid(&guid, buf, 23);
}

#ifdef UNICODE
wchar_t	* getString64FromGuid(const GUID *pGuid, wchar_t * buf, size_t numberOfElements)
#else
char	* getString64FromGuid(const GUID *pGuid, char * buf, size_t numberOfElements)
#endif
{
	unsigned long	num[6];
#ifdef UNICODE
	wchar_t			str[6][5];
#else
	char			str[6][5];
#endif
	__int32			i, n;

	//
	// Creation of six 32 Bit integers from the components of the GUID structure
	//
	num[0] = (unsigned long) (pGuid->Data1 / 16777216);                                                 //    16. byte  (pGuid->Data1 / 16777216) is the same as (pGuid->Data1 >> 24)
	num[1] = (unsigned long) (pGuid->Data1 % 16777216);                                                 // 15-13. bytes (pGuid->Data1 % 16777216) is the same as (pGuid->Data1 & 0xFFFFFF)
	num[2] = (unsigned long) (pGuid->Data2 * 256 + pGuid->Data3 / 256);                                 // 12-10. bytes
	num[3] = (unsigned long) ((pGuid->Data3 % 256) * 65536 + pGuid->Data4[0] * 256 + pGuid->Data4[1]);  // 09-07. bytes
	num[4] = (unsigned long) (pGuid->Data4[2] * 65536 + pGuid->Data4[3] * 256 + pGuid->Data4[4]);       // 06-04. bytes
	num[5] = (unsigned long) (pGuid->Data4[5] * 65536 + pGuid->Data4[6] * 256 + pGuid->Data4[7]);       // 03-01. bytes
	//
	// Conversion of the numbers into a system using a base of 64
	//
	buf[0]='\0';
	n = 3;
	for  (i = 0; i < 6; i++) {
		if	(!cv_to_64(num[i], str[i], 5, n)) {
			return	0;
		}
#ifdef UNICODE
		wcscat_s(buf, numberOfElements, str[i]);
#else
		strcat_s(buf, numberOfElements, str[i]);
#endif
		n = 5;
	}
	return	buf;
}

#ifdef UNICODE
bool	cv_to_64(const unsigned long number, wchar_t *code, size_t numberOfElements, __int32 len)
#else
bool	cv_to_64(const unsigned long number, char *code, size_t numberOfElements, __int32 len)
#endif
{
	unsigned long	act;
	__int32			iDigit, nDigits;
#ifdef UNICODE
	wchar_t			result[5];
#else
	char			result[5];
#endif

	if	(len > 5)
		return	false;

	act = number;
	nDigits = len - 1;

	for  (iDigit = 0; iDigit < nDigits; iDigit++) {
		result[nDigits - iDigit - 1] = cConversionTable64[(__int32) (act % 64)];
		act /= 64;
	}
	result[len - 1] = '\0';

	if	(act != 0)
		return	false;

#ifdef UNICODE
	wcscpy_s(code, numberOfElements, result);
#else
	strcpy_s(code, numberOfElements, result);
#endif
	return	true;
}


//
//
//		Application, Organization, Person (OwnerHistory, PersonAndOrganization)
//
//


#ifdef WIN64
__int64	getApplicationInstance()
#else
__int32	getApplicationInstance()
#endif
{
	if	(!ifcApplicationInstance) {
#ifdef UNICODE
		ifcApplicationInstance = sdaiCreateInstanceBN(model, (char*) L"IFCAPPLICATION");

		sdaiPutAttrBN(ifcApplicationInstance, (char*) L"ApplicationDeveloper", sdaiINSTANCE, (void*) getOrganizationInstance());
		sdaiPutAttrBN(ifcApplicationInstance, (char*) L"Version", sdaiUNICODE, L"0.10");
		sdaiPutAttrBN(ifcApplicationInstance, (char*) L"ApplicationFullName", sdaiUNICODE, L"Test Application");
		sdaiPutAttrBN(ifcApplicationInstance, (char*) L"ApplicationIdentifier", sdaiUNICODE, L"TA 1001");
#else
		ifcApplicationInstance = sdaiCreateInstanceBN(model, "IFCAPPLICATION");

		sdaiPutAttrBN(ifcApplicationInstance, "ApplicationDeveloper", sdaiINSTANCE, (void*) getOrganizationInstance());
		sdaiPutAttrBN(ifcApplicationInstance, "Version", sdaiSTRING, "0.10");
		sdaiPutAttrBN(ifcApplicationInstance, "ApplicationFullName", sdaiSTRING, "Test Application");
		sdaiPutAttrBN(ifcApplicationInstance, "ApplicationIdentifier", sdaiSTRING, "TA 1001");
#endif
	}

	ASSERT(ifcApplicationInstance);

	return	ifcApplicationInstance;
}

#ifdef WIN64
__int64	getOrganizationInstance()
#else
__int32	getOrganizationInstance()
#endif
{
	if	(!ifcOrganizationInstance) {
#ifdef UNICODE
		ifcOrganizationInstance = sdaiCreateInstanceBN(model, (char*) L"IFCORGANIZATION");

		sdaiPutAttrBN(ifcOrganizationInstance, (char*) L"Name", sdaiUNICODE, L"RDF");
		sdaiPutAttrBN(ifcOrganizationInstance, (char*) L"Description", sdaiUNICODE, L"RDF Ltd.");
#else
		ifcOrganizationInstance = sdaiCreateInstanceBN(model, "IFCORGANIZATION");

		sdaiPutAttrBN(ifcOrganizationInstance, "Name", sdaiSTRING, "RDF");
		sdaiPutAttrBN(ifcOrganizationInstance, "Description", sdaiSTRING, "RDF Ltd.");
#endif
	}

	ASSERT(ifcOrganizationInstance);

	return	ifcOrganizationInstance;
}

#ifdef WIN64
__int64	getOwnerHistoryInstance()
#else
__int32	getOwnerHistoryInstance()
#endif
{
	if	(!ifcBuildOwnerHistoryInstance) {
#ifdef UNICODE
		ifcBuildOwnerHistoryInstance = sdaiCreateInstanceBN(model, (char*) L"IFCOWNERHISTORY");

		sdaiPutAttrBN(ifcBuildOwnerHistoryInstance, (char*) L"OwningUser", sdaiINSTANCE, (void*) getPersonAndOrganizationInstance());
		sdaiPutAttrBN(ifcBuildOwnerHistoryInstance, (char*) L"OwningApplication", sdaiINSTANCE, (void*) getApplicationInstance());
		sdaiPutAttrBN(ifcBuildOwnerHistoryInstance, (char*) L"ChangeAction", sdaiENUM, L"ADDED");
		sdaiPutAttrBN(ifcBuildOwnerHistoryInstance, (char*) L"CreationDate", sdaiINTEGER, (void*) getTimeStamp());
#else
		ifcBuildOwnerHistoryInstance = sdaiCreateInstanceBN(model, "IFCOWNERHISTORY");

		sdaiPutAttrBN(ifcBuildOwnerHistoryInstance, "OwningUser", sdaiINSTANCE, (void*) getPersonAndOrganizationInstance());
		sdaiPutAttrBN(ifcBuildOwnerHistoryInstance, "OwningApplication", sdaiINSTANCE, (void*) getApplicationInstance());
		sdaiPutAttrBN(ifcBuildOwnerHistoryInstance, "ChangeAction", sdaiENUM, "ADDED");
		sdaiPutAttrBN(ifcBuildOwnerHistoryInstance, "CreationDate", sdaiINTEGER, (void*) getTimeStamp());
#endif
	}

	ASSERT(ifcBuildOwnerHistoryInstance);

	return	ifcBuildOwnerHistoryInstance;
}

#ifdef WIN64
__int64	getPersonAndOrganizationInstance()
#else
__int32	getPersonAndOrganizationInstance()
#endif
{
	if	(!ifcPersonAndOrganizationInstance) {
#ifdef UNICODE
		ifcPersonAndOrganizationInstance = sdaiCreateInstanceBN(model, (char*) L"IFCPERSONANDORGANIZATION");

		sdaiPutAttrBN(ifcPersonAndOrganizationInstance, (char*) L"ThePerson", sdaiINSTANCE, (void*) getPersonInstance());
		sdaiPutAttrBN(ifcPersonAndOrganizationInstance, (char*) L"TheOrganization", sdaiINSTANCE, (void*) getOrganizationInstance());
#else
		ifcPersonAndOrganizationInstance = sdaiCreateInstanceBN(model, "IFCPERSONANDORGANIZATION");

		sdaiPutAttrBN(ifcPersonAndOrganizationInstance, "ThePerson", sdaiINSTANCE, (void*) getPersonInstance());
		sdaiPutAttrBN(ifcPersonAndOrganizationInstance, "TheOrganization", sdaiINSTANCE, (void*) getOrganizationInstance());
#endif
	}

	ASSERT(ifcPersonAndOrganizationInstance);

	return	ifcPersonAndOrganizationInstance;
}

#ifdef WIN64
__int64	getPersonInstance()
#else
__int32	getPersonInstance()
#endif
{
	if	(!ifcPersonInstance) {
#ifdef UNICODE
		ifcPersonInstance = sdaiCreateInstanceBN(model, (char*) L"IFCPERSON");

		sdaiPutAttrBN(ifcPersonInstance, (char*) L"GivenName", sdaiUNICODE, L"Peter");
		sdaiPutAttrBN(ifcPersonInstance, (char*) L"FamilyName", sdaiUNICODE, L"Bonsma");
#else
		ifcPersonInstance = sdaiCreateInstanceBN(model, "IFCPERSON");

		sdaiPutAttrBN(ifcPersonInstance, "GivenName", sdaiSTRING, "Peter");
		sdaiPutAttrBN(ifcPersonInstance, "FamilyName", sdaiSTRING, "Bonsma");
#endif
	}

	ASSERT(ifcPersonInstance);

	return	ifcPersonInstance;
}


//
//
//		CartesianPoint, Direction, LocalPlacement (Axis2Placement)
//
//


#ifdef WIN64
__int64	buildAxis2Placement3DInstance(MATRIX * matrix)
#else
__int32	buildAxis2Placement3DInstance(MATRIX * matrix)
#endif
{
#ifdef WIN64
	__int64	ifcAxis2Placement3DInstance;
#else
	__int32	ifcAxis2Placement3DInstance;
#endif

#ifdef UNICODE
	ifcAxis2Placement3DInstance = sdaiCreateInstanceBN(model, (char*) L"IFCAXIS2PLACEMENT3D");

	sdaiPutAttrBN(ifcAxis2Placement3DInstance, (char*) L"Location", sdaiINSTANCE, (void*) buildCartesianPointInstance((POINT3D*) &matrix->_41));
	sdaiPutAttrBN(ifcAxis2Placement3DInstance, (char*) L"Axis", sdaiINSTANCE, (void*) buildDirectionInstance((POINT3D*) &matrix->_31));
	sdaiPutAttrBN(ifcAxis2Placement3DInstance, (char*) L"RefDirection", sdaiINSTANCE, (void*) buildDirectionInstance((POINT3D*) &matrix->_11));
#else
	ifcAxis2Placement3DInstance = sdaiCreateInstanceBN(model, "IFCAXIS2PLACEMENT3D");

	sdaiPutAttrBN(ifcAxis2Placement3DInstance, "Location", sdaiINSTANCE, (void*) buildCartesianPointInstance((POINT3D*) &matrix->_41));
	sdaiPutAttrBN(ifcAxis2Placement3DInstance, "Axis", sdaiINSTANCE, (void*) buildDirectionInstance((POINT3D*) &matrix->_31));
	sdaiPutAttrBN(ifcAxis2Placement3DInstance, "RefDirection", sdaiINSTANCE, (void*) buildDirectionInstance((POINT3D*) &matrix->_11));
#endif

	ASSERT(ifcAxis2Placement3DInstance);

	return	ifcAxis2Placement3DInstance;
}

#ifdef WIN64
__int64	buildCartesianPointInstance(POINT3D * point)
#else
__int32	buildCartesianPointInstance(POINT3D * point)
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
	sdaiAppend((__int64) aggrCoordinates, sdaiREAL, &point->x);
	sdaiAppend((__int64) aggrCoordinates, sdaiREAL, &point->y);
	sdaiAppend((__int64) aggrCoordinates, sdaiREAL, &point->z);
#else
	sdaiAppend((__int32) aggrCoordinates, sdaiREAL, &point->x);
	sdaiAppend((__int32) aggrCoordinates, sdaiREAL, &point->y);
	sdaiAppend((__int32) aggrCoordinates, sdaiREAL, &point->z);
#endif

	ASSERT(ifcCartesianPointInstance);

	return	ifcCartesianPointInstance;
}

#ifdef WIN64
__int64	buildDirectionInstance(POINT3D * point)
#else
__int32	buildDirectionInstance(POINT3D * point)
#endif
{
#ifdef WIN64
	__int64	ifcDirectionInstance, * aggrDirectionRatios;
#else
	__int32	ifcDirectionInstance, * aggrDirectionRatios;
#endif

#ifdef UNICODE
	ifcDirectionInstance = sdaiCreateInstanceBN(model, (char*) L"IFCDIRECTION");

	aggrDirectionRatios = sdaiCreateAggrBN(ifcDirectionInstance, (char*) L"DirectionRatios");
#else
	ifcDirectionInstance = sdaiCreateInstanceBN(model, "IFCDIRECTION");

	aggrDirectionRatios = sdaiCreateAggrBN(ifcDirectionInstance, "DirectionRatios");
#endif
#ifdef WIN64
	sdaiAppend((__int64) aggrDirectionRatios, sdaiREAL, &point->x);
	sdaiAppend((__int64) aggrDirectionRatios, sdaiREAL, &point->y);
	sdaiAppend((__int64) aggrDirectionRatios, sdaiREAL, &point->z);
#else
	sdaiAppend((__int32) aggrDirectionRatios, sdaiREAL, &point->x);
	sdaiAppend((__int32) aggrDirectionRatios, sdaiREAL, &point->y);
	sdaiAppend((__int32) aggrDirectionRatios, sdaiREAL, &point->z);
#endif

	ASSERT(ifcDirectionInstance);

	return	ifcDirectionInstance;
}

#ifdef WIN64
__int64	buildLocalPlacementInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo)
#else
__int32	buildLocalPlacementInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo)
#endif
{
#ifdef WIN64
	__int64	ifcLocalPlacementInstance;
#else
	__int32	ifcLocalPlacementInstance;
#endif

#ifdef UNICODE
	ifcLocalPlacementInstance = sdaiCreateInstanceBN(model, (char*) L"IFCLOCALPLACEMENT");
#else
	ifcLocalPlacementInstance = sdaiCreateInstanceBN(model, "IFCLOCALPLACEMENT");
#endif

	if	(ifcPlacementRelativeTo) {
#ifdef UNICODE
		sdaiPutAttrBN(ifcLocalPlacementInstance, (char*) L"PlacementRelTo", sdaiINSTANCE, (void*) ifcPlacementRelativeTo);
#else
		sdaiPutAttrBN(ifcLocalPlacementInstance, "PlacementRelTo", sdaiINSTANCE, (void*) ifcPlacementRelativeTo);
#endif
	}
#ifdef UNICODE
	sdaiPutAttrBN(ifcLocalPlacementInstance, (char*) L"RelativePlacement", sdaiINSTANCE, (void*) buildAxis2Placement3DInstance(matrix));
#else
	sdaiPutAttrBN(ifcLocalPlacementInstance, "RelativePlacement", sdaiINSTANCE, (void*) buildAxis2Placement3DInstance(matrix));
#endif

	ASSERT(ifcLocalPlacementInstance);

	return	ifcLocalPlacementInstance;
}


//
//
//		ConversionBasedUnit, DimensionalExponents, MeasureWithUnit, SIUnit, UnitAssignment
//
//


#ifdef WIN64
__int64	getConversionBasedUnitInstance()
#else
__int32	getConversionBasedUnitInstance()
#endif
{
	if	(!ifcConversionBasedUnitInstance) {
#ifdef UNICODE
		ifcConversionBasedUnitInstance = sdaiCreateInstanceBN(model, (char*) L"IFCCONVERSIONBASEDUNIT");

		sdaiPutAttrBN(ifcConversionBasedUnitInstance, (char*) L"Dimensions", sdaiINSTANCE, (void*) getDimensionalExponentsInstance());
		sdaiPutAttrBN(ifcConversionBasedUnitInstance, (char*) L"UnitType", sdaiENUM, L"PLANEANGLEUNIT");
		sdaiPutAttrBN(ifcConversionBasedUnitInstance, (char*) L"Name", sdaiUNICODE, L"DEGREE");
		sdaiPutAttrBN(ifcConversionBasedUnitInstance, (char*) L"ConversionFactor", sdaiINSTANCE, (void*) buildMeasureWithUnitInstance());
#else
		ifcConversionBasedUnitInstance = sdaiCreateInstanceBN(model, "IFCCONVERSIONBASEDUNIT");

		sdaiPutAttrBN(ifcConversionBasedUnitInstance, "Dimensions", sdaiINSTANCE, (void*) getDimensionalExponentsInstance());
		sdaiPutAttrBN(ifcConversionBasedUnitInstance, "UnitType", sdaiENUM, "PLANEANGLEUNIT");
		sdaiPutAttrBN(ifcConversionBasedUnitInstance, "Name", sdaiSTRING, "DEGREE");
		sdaiPutAttrBN(ifcConversionBasedUnitInstance, "ConversionFactor", sdaiINSTANCE, (void*) buildMeasureWithUnitInstance());
#endif
	}

	ASSERT(ifcConversionBasedUnitInstance);

	return	ifcConversionBasedUnitInstance;
}

#ifdef WIN64
__int64	getDimensionalExponentsInstance()
#else
__int32	getDimensionalExponentsInstance()
#endif
{
	if	(!ifcDimensionalExponentsInstance) {
#ifdef WIN64
		__int64	LengthExponent = 0,
#else
		__int32	LengthExponent = 0,
#endif
				MassExponent = 0,
				TimeExponent = 0,
				ElectricCurrentExponent = 0,
				ThermodynamicTemperatureExponent = 0,
				AmountOfSubstanceExponent = 0,
				LuminousIntensityExponent = 0;

#ifdef UNICODE
		ifcDimensionalExponentsInstance = sdaiCreateInstanceBN(model, (char*) L"IFCDIMENSIONALEXPONENTS");

		sdaiPutAttrBN(ifcDimensionalExponentsInstance, (char*) L"LengthExponent", sdaiINTEGER, &LengthExponent);
		sdaiPutAttrBN(ifcDimensionalExponentsInstance, (char*) L"MassExponent", sdaiINTEGER, &MassExponent);
		sdaiPutAttrBN(ifcDimensionalExponentsInstance, (char*) L"TimeExponent", sdaiINTEGER, &TimeExponent);
		sdaiPutAttrBN(ifcDimensionalExponentsInstance, (char*) L"ElectricCurrentExponent", sdaiINTEGER, &ElectricCurrentExponent);
		sdaiPutAttrBN(ifcDimensionalExponentsInstance, (char*) L"ThermodynamicTemperatureExponent", sdaiINTEGER, &ThermodynamicTemperatureExponent);
		sdaiPutAttrBN(ifcDimensionalExponentsInstance, (char*) L"AmountOfSubstanceExponent", sdaiINTEGER, &AmountOfSubstanceExponent);
		sdaiPutAttrBN(ifcDimensionalExponentsInstance, (char*) L"LuminousIntensityExponent", sdaiINTEGER, &LuminousIntensityExponent);
#else
		ifcDimensionalExponentsInstance = sdaiCreateInstanceBN(model, "IFCDIMENSIONALEXPONENTS");

		sdaiPutAttrBN(ifcDimensionalExponentsInstance, "LengthExponent", sdaiINTEGER, &LengthExponent);
		sdaiPutAttrBN(ifcDimensionalExponentsInstance, "MassExponent", sdaiINTEGER, &MassExponent);
		sdaiPutAttrBN(ifcDimensionalExponentsInstance, "TimeExponent", sdaiINTEGER, &TimeExponent);
		sdaiPutAttrBN(ifcDimensionalExponentsInstance, "ElectricCurrentExponent", sdaiINTEGER, &ElectricCurrentExponent);
		sdaiPutAttrBN(ifcDimensionalExponentsInstance, "ThermodynamicTemperatureExponent", sdaiINTEGER, &ThermodynamicTemperatureExponent);
		sdaiPutAttrBN(ifcDimensionalExponentsInstance, "AmountOfSubstanceExponent", sdaiINTEGER, &AmountOfSubstanceExponent);
		sdaiPutAttrBN(ifcDimensionalExponentsInstance, "LuminousIntensityExponent", sdaiINTEGER, &LuminousIntensityExponent);
#endif
	}

	ASSERT(ifcDimensionalExponentsInstance);

	return	ifcDimensionalExponentsInstance;
}

#ifdef WIN64
__int64	buildMeasureWithUnitInstance()
#else
__int32	buildMeasureWithUnitInstance()
#endif
{
#ifdef WIN64
	__int64	ifcMeasureWithUnitInstance;
#else
	__int32	ifcMeasureWithUnitInstance;
#endif
	void	* valueComponentADB;
	double	valueComponent= 0.01745;

#ifdef UNICODE
	ifcMeasureWithUnitInstance = sdaiCreateInstanceBN(model, (char*) L"IFCMEASUREWITHUNIT");
#else
	ifcMeasureWithUnitInstance = sdaiCreateInstanceBN(model, "IFCMEASUREWITHUNIT");
#endif

	valueComponentADB = sdaiCreateADB(sdaiREAL, &valueComponent);
#ifdef UNICODE
	sdaiPutADBTypePath(valueComponentADB, 1, (char*) L"IFCPLANEANGLEMEASURE"); 
	sdaiPutAttrBN(ifcMeasureWithUnitInstance, (char*) L"ValueComponent", sdaiADB, (void*) valueComponentADB);

	sdaiPutAttrBN(ifcMeasureWithUnitInstance, (char*) L"UnitComponent", sdaiINSTANCE, (void*) buildSIUnitInstance(L"PLANEANGLEUNIT", 0, L"RADIAN"));
#else
	sdaiPutADBTypePath(valueComponentADB, 1, "IFCPLANEANGLEMEASURE"); 
	sdaiPutAttrBN(ifcMeasureWithUnitInstance, "ValueComponent", sdaiADB, (void*) valueComponentADB);

	sdaiPutAttrBN(ifcMeasureWithUnitInstance, "UnitComponent", sdaiINSTANCE, (void*) buildSIUnitInstance("PLANEANGLEUNIT", 0, "RADIAN"));
#endif

	ASSERT(ifcMeasureWithUnitInstance);

	return	ifcMeasureWithUnitInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildSIUnitInstance(wchar_t * UnitType, wchar_t * Prefix, wchar_t * Name)
#else
__int64	buildSIUnitInstance(char * UnitType, char * Prefix, char * Name)
#endif
#else
#ifdef UNICODE
__int32	buildSIUnitInstance(wchar_t * UnitType, wchar_t * Prefix, wchar_t * Name)
#else
__int32	buildSIUnitInstance(char * UnitType, char * Prefix, char * Name)
#endif
#endif
{
#ifdef WIN64
	__int64	ifcSIUnitInstance;
#else
	__int32	ifcSIUnitInstance;
#endif

#ifdef UNICODE
	ifcSIUnitInstance = sdaiCreateInstanceBN(model, (char*) L"IFCSIUNIT");

	sdaiPutAttrBN(ifcSIUnitInstance, (char*) L"Dimensions", sdaiINTEGER, 0);
	sdaiPutAttrBN(ifcSIUnitInstance, (char*) L"UnitType", sdaiENUM, UnitType);
#else
	ifcSIUnitInstance = sdaiCreateInstanceBN(model, "IFCSIUNIT");

	sdaiPutAttrBN(ifcSIUnitInstance, "Dimensions", sdaiINTEGER, 0);
	sdaiPutAttrBN(ifcSIUnitInstance, "UnitType", sdaiENUM, UnitType);
#endif
	if	(Prefix) {
#ifdef UNICODE
		sdaiPutAttrBN(ifcSIUnitInstance, (char*) L"Prefix", sdaiENUM, Prefix);
#else
		sdaiPutAttrBN(ifcSIUnitInstance, "Prefix", sdaiENUM, Prefix);
#endif
	}
#ifdef UNICODE
	sdaiPutAttrBN(ifcSIUnitInstance, (char*) L"Name", sdaiENUM, Name);
#else
	sdaiPutAttrBN(ifcSIUnitInstance, "Name", sdaiENUM, Name);
#endif

	ASSERT(ifcSIUnitInstance);

	return	ifcSIUnitInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	getUnitAssignmentInstance(wchar_t * lengthUnitConversion)
#else
__int64	getUnitAssignmentInstance(char * lengthUnitConversion)
#endif
#else
#ifdef UNICODE
__int32	getUnitAssignmentInstance(wchar_t * lengthUnitConversion)
#else
__int32	getUnitAssignmentInstance(char * lengthUnitConversion)
#endif
#endif
{
#ifdef WIN64
	__int64	* aggrUnits;
#else
	__int32	* aggrUnits;
#endif

	if	(!ifcUnitAssignmentInstance) {
#ifdef UNICODE
		ifcUnitAssignmentInstance = sdaiCreateInstanceBN(model, (char*) L"IFCUNITASSIGNMENT");

		aggrUnits = sdaiCreateAggrBN(ifcUnitAssignmentInstance, (char*) L"Units");
#else
		ifcUnitAssignmentInstance = sdaiCreateInstanceBN(model, "IFCUNITASSIGNMENT");

		aggrUnits = sdaiCreateAggrBN(ifcUnitAssignmentInstance, "Units");
#endif
#ifdef WIN64
#ifdef UNICODE
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"LENGTHUNIT", lengthUnitConversion, L"METRE"));
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"AREAUNIT", 0, L"SQUARE_METRE"));
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"VOLUMEUNIT", 0, L"CUBIC_METRE"));
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) getConversionBasedUnitInstance());
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"SOLIDANGLEUNIT", 0, L"STERADIAN"));
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"MASSUNIT", 0, L"GRAM"));
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"TIMEUNIT", 0, L"SECOND"));
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"THERMODYNAMICTEMPERATUREUNIT", 0, L"DEGREE_CELSIUS"));
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"LUMINOUSINTENSITYUNIT", 0, L"LUMEN"));
#else
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("LENGTHUNIT", lengthUnitConversion, "METRE"));
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("AREAUNIT", 0, "SQUARE_METRE"));
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("VOLUMEUNIT", 0, "CUBIC_METRE"));
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) getConversionBasedUnitInstance());
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("SOLIDANGLEUNIT", 0, "STERADIAN"));
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("MASSUNIT", 0, "GRAM"));
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("TIMEUNIT", 0, "SECOND"));
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("THERMODYNAMICTEMPERATUREUNIT", 0, "DEGREE_CELSIUS"));
		sdaiAppend((__int64) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("LUMINOUSINTENSITYUNIT", 0, "LUMEN"));
#endif
#else
#ifdef UNICODE
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"LENGTHUNIT", lengthUnitConversion, L"METRE"));
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"AREAUNIT", 0, L"SQUARE_METRE"));
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"VOLUMEUNIT", 0, L"CUBIC_METRE"));
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) getConversionBasedUnitInstance());
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"SOLIDANGLEUNIT", 0, L"STERADIAN"));
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"MASSUNIT", 0, L"GRAM"));
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"TIMEUNIT", 0, L"SECOND"));
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"THERMODYNAMICTEMPERATUREUNIT", 0, L"DEGREE_CELSIUS"));
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance(L"LUMINOUSINTENSITYUNIT", 0, L"LUMEN"));
#else
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("LENGTHUNIT", lengthUnitConversion, "METRE"));
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("AREAUNIT", 0, "SQUARE_METRE"));
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("VOLUMEUNIT", 0, "CUBIC_METRE"));
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) getConversionBasedUnitInstance());
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("SOLIDANGLEUNIT", 0, "STERADIAN"));
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("MASSUNIT", 0, "GRAM"));
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("TIMEUNIT", 0, "SECOND"));
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("THERMODYNAMICTEMPERATUREUNIT", 0, "DEGREE_CELSIUS"));
		sdaiAppend((__int32) aggrUnits, sdaiINSTANCE, (void*) buildSIUnitInstance("LUMINOUSINTENSITYUNIT", 0, "LUMEN"));
#endif
#endif
	}

	ASSERT(ifcUnitAssignmentInstance);

	return	ifcUnitAssignmentInstance;
}


//
//
//		RelAggregates, RelContainedInSpatialStructure
//
//


#ifdef WIN64
#ifdef UNICODE
__int64	buildRelAggregatesInstance(wchar_t * name, wchar_t * description, __int64 ifcRelatingObjectInstance, __int64 ifcRelatedObjectInstance)
#else
__int64	buildRelAggregatesInstance(char * name, char * description, __int64 ifcRelatingObjectInstance, __int64 ifcRelatedObjectInstance)
#endif
#else
#ifdef UNICODE
__int32	buildRelAggregatesInstance(wchar_t * name, wchar_t * description, __int32 ifcRelatingObjectInstance, __int32 ifcRelatedObjectInstance)
#else
__int32	buildRelAggregatesInstance(char * name, char * description, __int32 ifcRelatingObjectInstance, __int32 ifcRelatedObjectInstance)
#endif
#endif
{
	ASSERT(ifcRelatingObjectInstance  &&  ifcRelatedObjectInstance);

#ifdef WIN64
	__int64	ifcRelAggregatesInstance, * aggrRelatedObjects;
#else
	__int32	ifcRelAggregatesInstance, * aggrRelatedObjects;
#endif

#ifdef UNICODE
	ifcRelAggregatesInstance = sdaiCreateInstanceBN(model, (char*) L"IFCRELAGGREGATES");

	sdaiPutAttrBN(ifcRelAggregatesInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelAggregatesInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcRelAggregatesInstance, (char*) L"Name", sdaiUNICODE, name);
	sdaiPutAttrBN(ifcRelAggregatesInstance, (char*) L"Description", sdaiUNICODE, description);
	sdaiPutAttrBN(ifcRelAggregatesInstance, (char*) L"RelatingObject", sdaiINSTANCE, (void*) ifcRelatingObjectInstance);
	aggrRelatedObjects = sdaiCreateAggrBN(ifcRelAggregatesInstance, (char*) L"RelatedObjects");
#else
	ifcRelAggregatesInstance = sdaiCreateInstanceBN(model, "IFCRELAGGREGATES");

	sdaiPutAttrBN(ifcRelAggregatesInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelAggregatesInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcRelAggregatesInstance, "Name", sdaiSTRING, name);
	sdaiPutAttrBN(ifcRelAggregatesInstance, "Description", sdaiSTRING, description);
	sdaiPutAttrBN(ifcRelAggregatesInstance, "RelatingObject", sdaiINSTANCE, (void*) ifcRelatingObjectInstance);
	aggrRelatedObjects = sdaiCreateAggrBN(ifcRelAggregatesInstance, "RelatedObjects");
#endif
#ifdef WIN64
	sdaiAppend((__int64) aggrRelatedObjects, sdaiINSTANCE, (void*) ifcRelatedObjectInstance);
#else
	sdaiAppend((__int32) aggrRelatedObjects, sdaiINSTANCE, (void*) ifcRelatedObjectInstance);
#endif

	ASSERT(ifcRelAggregatesInstance);

	return	ifcRelAggregatesInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildRelContainedInSpatialStructureInstance(wchar_t * name, wchar_t * description, __int64 ifcRelatingStructureInstance, __int64 ** aggrRelatedElements)
#else
__int64	buildRelContainedInSpatialStructureInstance(char * name, char * description, __int64 ifcRelatingStructureInstance, __int64 ** aggrRelatedElements)
#endif
#else
#ifdef UNICODE
__int32	buildRelContainedInSpatialStructureInstance(wchar_t * name, wchar_t * description, __int32 ifcRelatingStructureInstance, __int32 ** aggrRelatedElements)
#else
__int32	buildRelContainedInSpatialStructureInstance(char * name, char * description, __int32 ifcRelatingStructureInstance, __int32 ** aggrRelatedElements)
#endif
#endif
{
	ASSERT(ifcRelatingStructureInstance);

#ifdef WIN64
	__int64	ifcRelContainedInSpatialStructureInstance;
#else
	__int32	ifcRelContainedInSpatialStructureInstance;
#endif

#ifdef UNICODE
	ifcRelContainedInSpatialStructureInstance = sdaiCreateInstanceBN(model, (char*) L"IFCRELCONTAINEDINSPATIALSTRUCTURE");

	sdaiPutAttrBN(ifcRelContainedInSpatialStructureInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelContainedInSpatialStructureInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcRelContainedInSpatialStructureInstance, (char*) L"Name", sdaiUNICODE, L"Default Building");
	sdaiPutAttrBN(ifcRelContainedInSpatialStructureInstance, (char*) L"Description", sdaiUNICODE, L"Contents of Building Storey");
	(* aggrRelatedElements) = sdaiCreateAggrBN(ifcRelContainedInSpatialStructureInstance, (char*) L"RelatedElements");
	sdaiPutAttrBN(ifcRelContainedInSpatialStructureInstance, (char*) L"RelatingStructure", sdaiINSTANCE, (void*) ifcRelatingStructureInstance);
#else
	ifcRelContainedInSpatialStructureInstance = sdaiCreateInstanceBN(model, "IFCRELCONTAINEDINSPATIALSTRUCTURE");

	sdaiPutAttrBN(ifcRelContainedInSpatialStructureInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelContainedInSpatialStructureInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcRelContainedInSpatialStructureInstance, "Name", sdaiSTRING, "Default Building");
	sdaiPutAttrBN(ifcRelContainedInSpatialStructureInstance, "Description", sdaiSTRING, "Contents of Building Storey");
	(* aggrRelatedElements) = sdaiCreateAggrBN(ifcRelContainedInSpatialStructureInstance, "RelatedElements");
	sdaiPutAttrBN(ifcRelContainedInSpatialStructureInstance, "RelatingStructure", sdaiINSTANCE, (void*) ifcRelatingStructureInstance);
#endif

	ASSERT(ifcRelContainedInSpatialStructureInstance);

	return	ifcRelContainedInSpatialStructureInstance;
}


//
//
//		Building, BuildingStorey, Project, Site
//
//


#ifdef WIN64
__int64	buildBuildingInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcBuildingInstancePlacement)
#else
__int32	buildBuildingInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcBuildingInstancePlacement)
#endif
{
	ASSERT(ifcPlacementRelativeTo);

#ifdef WIN64
	__int64	ifcBuildingInstance;
#else
	__int32	ifcBuildingInstance;
#endif

#ifdef UNICODE
	ifcBuildingInstance = sdaiCreateInstanceBN(model, (char*) L"IFCBUILDING");

	sdaiPutAttrBN(ifcBuildingInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcBuildingInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcBuildingInstance, (char*) L"Name", sdaiUNICODE, L"Default Building");
	sdaiPutAttrBN(ifcBuildingInstance, (char*) L"Description", sdaiUNICODE, L"Description of Default Building");
#else
	ifcBuildingInstance = sdaiCreateInstanceBN(model, "IFCBUILDING");

	sdaiPutAttrBN(ifcBuildingInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcBuildingInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcBuildingInstance, "Name", sdaiSTRING, "Default Building");
	sdaiPutAttrBN(ifcBuildingInstance, "Description", sdaiSTRING, "Description of Default Building");
#endif

	(* ifcBuildingInstancePlacement) = buildLocalPlacementInstance(matrix, ifcPlacementRelativeTo);
#ifdef UNICODE
	sdaiPutAttrBN(ifcBuildingInstance, (char*) L"ObjectPlacement", sdaiINSTANCE, (void*) (* ifcBuildingInstancePlacement));
	sdaiPutAttrBN(ifcBuildingInstance, (char*) L"CompositionType", sdaiENUM, L"ELEMENT");

	sdaiPutAttrBN(ifcBuildingInstance, (char*) L"BuildingAddress", sdaiINSTANCE, (void*) buildPostalAddress());
#else
	sdaiPutAttrBN(ifcBuildingInstance, "ObjectPlacement", sdaiINSTANCE, (void*) (* ifcBuildingInstancePlacement));
	sdaiPutAttrBN(ifcBuildingInstance, "CompositionType", sdaiENUM, "ELEMENT");

	sdaiPutAttrBN(ifcBuildingInstance, "BuildingAddress", sdaiINSTANCE, (void*) buildPostalAddress());
#endif

	ASSERT(ifcBuildingInstance);

	return	ifcBuildingInstance;
}

#ifdef WIN64
__int64	buildBuildingStoreyInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcBuildingStoreyInstancePlacement)
#else
__int32	buildBuildingStoreyInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcBuildingStoreyInstancePlacement)
#endif
{
	ASSERT(ifcPlacementRelativeTo);

#ifdef WIN64
	__int64	ifcBuildingStoreyInstance;
#else
	__int32	ifcBuildingStoreyInstance;
#endif
	double	elevation = 0;

#ifdef UNICODE
	ifcBuildingStoreyInstance = sdaiCreateInstanceBN(model, (char*) L"IFCBUILDINGSTOREY");

	sdaiPutAttrBN(ifcBuildingStoreyInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcBuildingStoreyInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcBuildingStoreyInstance, (char*) L"Name", sdaiUNICODE, L"Default Building Storey");
	sdaiPutAttrBN(ifcBuildingStoreyInstance, (char*) L"Description", sdaiUNICODE, L"Description of Default Building Storey");
#else
	ifcBuildingStoreyInstance = sdaiCreateInstanceBN(model, "IFCBUILDINGSTOREY");

	sdaiPutAttrBN(ifcBuildingStoreyInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcBuildingStoreyInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcBuildingStoreyInstance, "Name", sdaiSTRING, "Default Building Storey");
	sdaiPutAttrBN(ifcBuildingStoreyInstance, "Description", sdaiSTRING, "Description of Default Building Storey");
#endif

	(* ifcBuildingStoreyInstancePlacement) = buildLocalPlacementInstance(matrix, ifcPlacementRelativeTo);
#ifdef UNICODE
	sdaiPutAttrBN(ifcBuildingStoreyInstance, (char*) L"ObjectPlacement", sdaiINSTANCE, (void*) (* ifcBuildingStoreyInstancePlacement));
	sdaiPutAttrBN(ifcBuildingStoreyInstance, (char*) L"CompositionType", sdaiENUM, L"ELEMENT");
	sdaiPutAttrBN(ifcBuildingStoreyInstance, (char*) L"Elevation", sdaiREAL, &elevation);
#else
	sdaiPutAttrBN(ifcBuildingStoreyInstance, "ObjectPlacement", sdaiINSTANCE, (void*) (* ifcBuildingStoreyInstancePlacement));
	sdaiPutAttrBN(ifcBuildingStoreyInstance, "CompositionType", sdaiENUM, "ELEMENT");
	sdaiPutAttrBN(ifcBuildingStoreyInstance, "Elevation", sdaiREAL, &elevation);
#endif

	ASSERT(ifcBuildingStoreyInstance);

	return	ifcBuildingStoreyInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	getProjectInstance(wchar_t * lengthUnitConversion)
#else
__int64	getProjectInstance(char * lengthUnitConversion)
#endif
#else
#ifdef UNICODE
__int32	getProjectInstance(wchar_t * lengthUnitConversion)
#else
__int32	getProjectInstance(char * lengthUnitConversion)
#endif
#endif
{
#ifdef WIN64
	__int64	* aggrRepresentationContexts = 0;
#else
	__int32	* aggrRepresentationContexts = 0;
#endif

	if	(!ifcProjectInstance) {
#ifdef UNICODE
		ifcProjectInstance = sdaiCreateInstanceBN(model, (char*) L"IFCPROJECT");

		sdaiPutAttrBN(ifcProjectInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
		sdaiPutAttrBN(ifcProjectInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
		sdaiPutAttrBN(ifcProjectInstance, (char*) L"Name", sdaiUNICODE, L"Default Project");
		sdaiPutAttrBN(ifcProjectInstance, (char*) L"Description", sdaiUNICODE, L"Description of Default Project");
		sdaiPutAttrBN(ifcProjectInstance, (char*) L"UnitsInContext", sdaiINSTANCE, (void*) getUnitAssignmentInstance(lengthUnitConversion));
		aggrRepresentationContexts = sdaiCreateAggrBN(ifcProjectInstance, (char*) L"RepresentationContexts");
#else
		ifcProjectInstance = sdaiCreateInstanceBN(model, "IFCPROJECT");

		sdaiPutAttrBN(ifcProjectInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
		sdaiPutAttrBN(ifcProjectInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
		sdaiPutAttrBN(ifcProjectInstance, "Name", sdaiSTRING, "Default Project");
		sdaiPutAttrBN(ifcProjectInstance, "Description", sdaiSTRING, "Description of Default Project");
		sdaiPutAttrBN(ifcProjectInstance, "UnitsInContext", sdaiINSTANCE, (void*) getUnitAssignmentInstance(lengthUnitConversion));
		aggrRepresentationContexts = sdaiCreateAggrBN(ifcProjectInstance, "RepresentationContexts");
#endif
#ifdef WIN64
		sdaiAppend((__int64) aggrRepresentationContexts, sdaiINSTANCE, (void*) getGeometricRepresentationContextInstance());
#else
		sdaiAppend((__int32) aggrRepresentationContexts, sdaiINSTANCE, (void*) getGeometricRepresentationContextInstance());
#endif
	}

	ASSERT(ifcProjectInstance);

	return	ifcProjectInstance;
}

#ifdef WIN64
__int64	buildSiteInstance(MATRIX * matrix, __int64 ifcPlacementRelativeTo, __int64 * ifcSiteInstancePlacement)
#else
__int32	buildSiteInstance(MATRIX * matrix, __int32 ifcPlacementRelativeTo, __int32 * ifcSiteInstancePlacement)
#endif
{
	ASSERT(ifcPlacementRelativeTo == 0);

#ifdef WIN64
	__int64	ifcSiteInstance, * aggrRefLatitude, * aggrRefLongitude,
#else
	__int32	ifcSiteInstance, * aggrRefLatitude, * aggrRefLongitude,
#endif
			refLat_x = 24, refLat_y = 28, refLat_z = 0, refLong_x = 54, refLong_y = 25, refLong_z = 0;

#ifdef UNICODE
	ifcSiteInstance = sdaiCreateInstanceBN(model, (char*) L"IFCSITE");

	sdaiPutAttrBN(ifcSiteInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcSiteInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcSiteInstance, (char*) L"Name", sdaiUNICODE, L"Default Site");
	sdaiPutAttrBN(ifcSiteInstance, (char*) L"Description", sdaiUNICODE, L"Description of Default Site");
#else
	ifcSiteInstance = sdaiCreateInstanceBN(model, "IFCSITE");

	sdaiPutAttrBN(ifcSiteInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcSiteInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcSiteInstance, "Name", sdaiSTRING, "Default Site");
	sdaiPutAttrBN(ifcSiteInstance, "Description", sdaiSTRING, "Description of Default Site");
#endif

	(* ifcSiteInstancePlacement) = buildLocalPlacementInstance(matrix, ifcPlacementRelativeTo);
#ifdef UNICODE
	sdaiPutAttrBN(ifcSiteInstance, (char*) L"ObjectPlacement", sdaiINSTANCE, (void*) (* ifcSiteInstancePlacement));
	sdaiPutAttrBN(ifcSiteInstance, (char*) L"CompositionType", sdaiENUM, L"ELEMENT");

	aggrRefLatitude = sdaiCreateAggrBN(ifcSiteInstance, (char*) L"RefLatitude");
#else
	sdaiPutAttrBN(ifcSiteInstance, "ObjectPlacement", sdaiINSTANCE, (void*) (* ifcSiteInstancePlacement));
	sdaiPutAttrBN(ifcSiteInstance, "CompositionType", sdaiENUM, "ELEMENT");

	aggrRefLatitude = sdaiCreateAggrBN(ifcSiteInstance, "RefLatitude");
#endif
#ifdef WIN64
	sdaiAppend((__int64) aggrRefLatitude, sdaiINTEGER, &refLat_x);
	sdaiAppend((__int64) aggrRefLatitude, sdaiINTEGER, &refLat_y);
	sdaiAppend((__int64) aggrRefLatitude, sdaiINTEGER, &refLat_z);
#else
	sdaiAppend((__int32) aggrRefLatitude, sdaiINTEGER, &refLat_x);
	sdaiAppend((__int32) aggrRefLatitude, sdaiINTEGER, &refLat_y);
	sdaiAppend((__int32) aggrRefLatitude, sdaiINTEGER, &refLat_z);
#endif

#ifdef UNICODE
	aggrRefLongitude = sdaiCreateAggrBN(ifcSiteInstance, (char*) L"RefLongitude");
#else
	aggrRefLongitude = sdaiCreateAggrBN(ifcSiteInstance, "RefLongitude");
#endif
#ifdef WIN64
	sdaiAppend((__int64) aggrRefLongitude, sdaiINTEGER, &refLong_x);
	sdaiAppend((__int64) aggrRefLongitude, sdaiINTEGER, &refLong_y);
	sdaiAppend((__int64) aggrRefLongitude, sdaiINTEGER, &refLong_z);
#else
	sdaiAppend((__int32) aggrRefLongitude, sdaiINTEGER, &refLong_x);
	sdaiAppend((__int32) aggrRefLongitude, sdaiINTEGER, &refLong_y);
	sdaiAppend((__int32) aggrRefLongitude, sdaiINTEGER, &refLong_z);
#endif

	double	refElevation = 10;
#ifdef UNICODE
	sdaiPutAttrBN(ifcSiteInstance, (char*) L"RefElevation", sdaiREAL, &refElevation);
#else
	sdaiPutAttrBN(ifcSiteInstance, "RefElevation", sdaiREAL, &refElevation);
#endif

	ASSERT(ifcSiteInstance);

	return	ifcSiteInstance;
}


//
//
//		WorldCoordinateSystem, GeometricRepresentationContext
//
//


#ifdef WIN64
__int64	getWorldCoordinateSystemInstance()
#else
__int32	getWorldCoordinateSystemInstance()
#endif
{
	POINT3D	point;
	identityPoint(&point);

#ifdef WIN64
	__int64	ifcWorldCoordinateSystemInstance;
#else
	__int32	ifcWorldCoordinateSystemInstance;
#endif

#ifdef UNICODE
	ifcWorldCoordinateSystemInstance = sdaiCreateInstanceBN(model, (char*) L"IFCAXIS2PLACEMENT3D");
	
	sdaiPutAttrBN(ifcWorldCoordinateSystemInstance, (char*) L"Location", sdaiINSTANCE, (void*) buildCartesianPointInstance(&point));
#else
	ifcWorldCoordinateSystemInstance = sdaiCreateInstanceBN(model, "IFCAXIS2PLACEMENT3D");
	
	sdaiPutAttrBN(ifcWorldCoordinateSystemInstance, "Location", sdaiINSTANCE, (void*) buildCartesianPointInstance(&point));
#endif

	ASSERT(ifcWorldCoordinateSystemInstance);

	return	ifcWorldCoordinateSystemInstance;
}

#ifdef WIN64
__int64	getGeometricRepresentationContextInstance()
#else
__int32	getGeometricRepresentationContextInstance()
#endif
{
	if	(!ifcGeometricRepresentationContextInstance) {
		double	precision = 0.00001;
#ifdef WIN64
		__int64	coordinateSpaceDimension = 3;
#else
		__int32	coordinateSpaceDimension = 3;
#endif

#ifdef UNICODE
		ifcGeometricRepresentationContextInstance = sdaiCreateInstanceBN(model, (char*) L"IFCGEOMETRICREPRESENTATIONCONTEXT");

		sdaiPutAttrBN(ifcGeometricRepresentationContextInstance, (char*) L"ContextType", sdaiUNICODE, L"Model");
		sdaiPutAttrBN(ifcGeometricRepresentationContextInstance, (char*) L"CoordinateSpaceDimension", sdaiINTEGER, &coordinateSpaceDimension);
		sdaiPutAttrBN(ifcGeometricRepresentationContextInstance, (char*) L"Precision", sdaiREAL, &precision);
		sdaiPutAttrBN(ifcGeometricRepresentationContextInstance, (char*) L"WorldCoordinateSystem", sdaiINSTANCE, (void*) getWorldCoordinateSystemInstance());
#else
		ifcGeometricRepresentationContextInstance = sdaiCreateInstanceBN(model, "IFCGEOMETRICREPRESENTATIONCONTEXT");

		sdaiPutAttrBN(ifcGeometricRepresentationContextInstance, "ContextType", sdaiSTRING, "Model");
		sdaiPutAttrBN(ifcGeometricRepresentationContextInstance, "CoordinateSpaceDimension", sdaiINTEGER, &coordinateSpaceDimension);
		sdaiPutAttrBN(ifcGeometricRepresentationContextInstance, "Precision", sdaiREAL, &precision);
		sdaiPutAttrBN(ifcGeometricRepresentationContextInstance, "WorldCoordinateSystem", sdaiINSTANCE, (void*) getWorldCoordinateSystemInstance());
#endif

		POINT3D	point;
		point.ifcCartesianPointInstance = 0;
		point.x = 0;
		point.y = 1;
		point.z = 0;

#ifdef UNICODE
		sdaiPutAttrBN(ifcGeometricRepresentationContextInstance, (char*) L"TrueNorth", sdaiINSTANCE, (void*) buildDirectionInstance(&point));
#else
		sdaiPutAttrBN(ifcGeometricRepresentationContextInstance, "TrueNorth", sdaiINSTANCE, (void*) buildDirectionInstance(&point));
#endif
	}

	ASSERT(ifcGeometricRepresentationContextInstance);

	return	ifcGeometricRepresentationContextInstance;
}


//
//
//		PostalAddress
//
//


#ifdef WIN64
__int64	buildPostalAddress()
#else
__int32	buildPostalAddress()
#endif
{
	if	(!ifcPostalAddressInstance) {
#ifdef WIN64
		__int64	* addressLines;
#else
		__int32	* addressLines;
#endif

#ifdef UNICODE
		ifcPostalAddressInstance = sdaiCreateInstanceBN(model, (char*) L"IFCPOSTALADDRESS");

		addressLines = sdaiCreateAggrBN(ifcPostalAddressInstance, (char*) L"AddressLines");
#ifdef WIN64
		sdaiAppend((__int64) addressLines, sdaiUNICODE, (char*) L"RDF Ltd.");
		sdaiAppend((__int64) addressLines, sdaiUNICODE, (char*) L"Main Office");
#else
		sdaiAppend((__int32) addressLines, sdaiUNICODE, (char*) L"RDF Ltd.");
		sdaiAppend((__int32) addressLines, sdaiUNICODE, (char*) L"Main Office");
#endif

		sdaiPutAttrBN(ifcPostalAddressInstance, (char*) L"PostalBox", sdaiUNICODE, L"32");
		sdaiPutAttrBN(ifcPostalAddressInstance, (char*) L"Town", sdaiUNICODE, L"Bankya");
		sdaiPutAttrBN(ifcPostalAddressInstance, (char*) L"Region", sdaiUNICODE, L"Sofia");
		sdaiPutAttrBN(ifcPostalAddressInstance, (char*) L"PostalCode", sdaiUNICODE, L"1320");
		sdaiPutAttrBN(ifcPostalAddressInstance, (char*) L"Country", sdaiUNICODE, L"Bulgaria");
#else
		ifcPostalAddressInstance = sdaiCreateInstanceBN(model, "IFCPOSTALADDRESS");

		addressLines = sdaiCreateAggrBN(ifcPostalAddressInstance, "AddressLines");
#ifdef WIN64
		sdaiAppend((__int64) addressLines, sdaiSTRING, "RDF Ltd.");
		sdaiAppend((__int64) addressLines, sdaiSTRING, "Main Office");
#else
		sdaiAppend((__int32) addressLines, sdaiSTRING, "RDF Ltd.");
		sdaiAppend((__int32) addressLines, sdaiSTRING, "Main Office");
#endif

		sdaiPutAttrBN(ifcPostalAddressInstance, "PostalBox", sdaiSTRING, "32");
		sdaiPutAttrBN(ifcPostalAddressInstance, "Town", sdaiSTRING, "Bankya");
		sdaiPutAttrBN(ifcPostalAddressInstance, "Region", sdaiSTRING, "Sofia");
		sdaiPutAttrBN(ifcPostalAddressInstance, "PostalCode", sdaiSTRING, "1320");
		sdaiPutAttrBN(ifcPostalAddressInstance, "Country", sdaiSTRING, "Bulgaria");
#endif
	}

	ASSERT(ifcPostalAddressInstance);

	return	ifcPostalAddressInstance;
}
