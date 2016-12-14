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
#include "propertiesIfc.h"

#ifdef WIN64
	extern	__int64	model;
#else
	extern	__int32	model;
#endif

//
//
//		PropertySet, PropertySingleValue
//
//


#ifdef WIN64
#ifdef UNICODE
__int64	buildPropertySet(wchar_t * name, __int64 ** aggrHasProperties)
#else
__int64	buildPropertySet(char * name, __int64 ** aggrHasProperties)
#endif
#else
#ifdef UNICODE
__int32	buildPropertySet(wchar_t * name, __int32 ** aggrHasProperties)
#else
__int32	buildPropertySet(char * name, __int32 ** aggrHasProperties)
#endif
#endif
{
#ifdef WIN64
	__int64	ifcPropertySetInstance;
#else
	__int32	ifcPropertySetInstance;
#endif

#ifdef UNICODE
	ifcPropertySetInstance = sdaiCreateInstanceBN(model, (char*) L"IFCPROPERTYSET");

	sdaiPutAttrBN(ifcPropertySetInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcPropertySetInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcPropertySetInstance, (char*) L"Name", sdaiUNICODE, name);

	(* aggrHasProperties) = sdaiCreateAggrBN(ifcPropertySetInstance, (char*) L"HasProperties");
#else
	ifcPropertySetInstance = sdaiCreateInstanceBN(model, "IFCPROPERTYSET");

	sdaiPutAttrBN(ifcPropertySetInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcPropertySetInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcPropertySetInstance, "Name", sdaiSTRING, name);

	(* aggrHasProperties) = sdaiCreateAggrBN(ifcPropertySetInstance, "HasProperties");
#endif

	ASSERT(ifcPropertySetInstance);

	return	ifcPropertySetInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildPropertySingleValue(wchar_t * name, wchar_t * description, bool nominalValue)
#else
__int64	buildPropertySingleValue(char * name, char * description, bool nominalValue)
#endif
#else
#ifdef UNICODE
__int32	buildPropertySingleValue(wchar_t * name, wchar_t * description, bool nominalValue)
#else
__int32	buildPropertySingleValue(char * name, char * description, bool nominalValue)
#endif
#endif
{
#ifdef UNICODE
	return	buildPropertySingleValue(name, description, nominalValue, L"IFCBOOLEAN");
#else
	return	buildPropertySingleValue(name, description, nominalValue, "IFCBOOLEAN");
#endif
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildPropertySingleValue(wchar_t * name, wchar_t * description, bool nominalValue, wchar_t * typePath)
#else
__int64	buildPropertySingleValue(char * name, char * description, bool nominalValue, char * typePath)
#endif
#else
#ifdef UNICODE
__int32	buildPropertySingleValue(wchar_t * name, wchar_t * description, bool nominalValue, wchar_t * typePath)
#else
__int32	buildPropertySingleValue(char * name, char * description, bool nominalValue, char * typePath)
#endif
#endif
{
#ifdef WIN64
	__int64	ifcPropertySingleValueInstance;
#else
	__int32	ifcPropertySingleValueInstance;
#endif
	void	* nominalValueADB;
#ifdef UNICODE
	wchar_t	bTrue[2] = L"T", bFalse[2] = L"F"; 

	ifcPropertySingleValueInstance = sdaiCreateInstanceBN(model, (char*) L"IFCPROPERTYSINGLEVALUE");

	sdaiPutAttrBN(ifcPropertySingleValueInstance, (char*) L"Name", sdaiUNICODE, name);
	sdaiPutAttrBN(ifcPropertySingleValueInstance, (char*) L"Description", sdaiUNICODE, description);
#else
	char	bTrue[2] = "T", bFalse[2] = "F"; 

	ifcPropertySingleValueInstance = sdaiCreateInstanceBN(model, "IFCPROPERTYSINGLEVALUE");

	sdaiPutAttrBN(ifcPropertySingleValueInstance, "Name", sdaiSTRING, name);
	sdaiPutAttrBN(ifcPropertySingleValueInstance, "Description", sdaiSTRING, description);
#endif

	if	(nominalValue) {
		nominalValueADB = sdaiCreateADB(sdaiENUM, bTrue);
	} else {
		nominalValueADB = sdaiCreateADB(sdaiENUM, bFalse);
	}
#ifdef UNICODE
	sdaiPutADBTypePath(nominalValueADB, 1, (char*) typePath); 
	sdaiPutAttrBN(ifcPropertySingleValueInstance, (char*) L"NominalValue", sdaiADB, (void*) nominalValueADB);
#else
	sdaiPutADBTypePath(nominalValueADB, 1, typePath); 
	sdaiPutAttrBN(ifcPropertySingleValueInstance, "NominalValue", sdaiADB, (void*) nominalValueADB);
#endif

	ASSERT(ifcPropertySingleValueInstance);

	return	ifcPropertySingleValueInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildPropertySingleValue(wchar_t * name, wchar_t * description, double nominalValue)
#else
__int64	buildPropertySingleValue(char * name, char * description, double nominalValue)
#endif
#else
#ifdef UNICODE
__int32	buildPropertySingleValue(wchar_t * name, wchar_t * description, double nominalValue)
#else
__int32	buildPropertySingleValue(char * name, char * description, double nominalValue)
#endif
#endif
{
#ifdef UNICODE
	return	buildPropertySingleValue(name, description, nominalValue, L"IFCREAL");
#else
	return	buildPropertySingleValue(name, description, nominalValue, "IFCREAL");
#endif
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildPropertySingleValue(wchar_t * name, wchar_t * description, double nominalValue, wchar_t * typePath)
#else
__int64	buildPropertySingleValue(char * name, char * description, double nominalValue, char * typePath)
#endif
#else
#ifdef UNICODE
__int32	buildPropertySingleValue(wchar_t * name, wchar_t * description, double nominalValue, wchar_t * typePath)
#else
__int32	buildPropertySingleValue(char * name, char * description, double nominalValue, char * typePath)
#endif
#endif
{
#ifdef WIN64
	__int64	ifcPropertySingleValueInstance;
#else
	__int32	ifcPropertySingleValueInstance;
#endif
	void	* nominalValueADB;

#ifdef UNICODE
	ifcPropertySingleValueInstance = sdaiCreateInstanceBN(model, (char*) L"IFCPROPERTYSINGLEVALUE");

	sdaiPutAttrBN(ifcPropertySingleValueInstance, (char*) L"Name", sdaiUNICODE, name);
	sdaiPutAttrBN(ifcPropertySingleValueInstance, (char*) L"Description", sdaiUNICODE, description);
#else
	ifcPropertySingleValueInstance = sdaiCreateInstanceBN(model, "IFCPROPERTYSINGLEVALUE");

	sdaiPutAttrBN(ifcPropertySingleValueInstance, "Name", sdaiSTRING, name);
	sdaiPutAttrBN(ifcPropertySingleValueInstance, "Description", sdaiSTRING, description);
#endif

#ifdef WIN64
	nominalValueADB = sdaiCreateADB(sdaiREAL, (__int64*) &nominalValue);
#else
	nominalValueADB = sdaiCreateADB(sdaiREAL, (__int32*) &nominalValue);
#endif
#ifdef UNICODE
	sdaiPutADBTypePath(nominalValueADB, 1, (char*) typePath); 
	sdaiPutAttrBN(ifcPropertySingleValueInstance, (char*) L"NominalValue", sdaiADB, (void*) nominalValueADB);
#else
	sdaiPutADBTypePath(nominalValueADB, 1, typePath); 
	sdaiPutAttrBN(ifcPropertySingleValueInstance, "NominalValue", sdaiADB, (void*) nominalValueADB);
#endif

	ASSERT(ifcPropertySingleValueInstance);

	return	ifcPropertySingleValueInstance;
}


#ifdef WIN64
#ifdef UNICODE
__int64	buildPropertySingleValue(wchar_t * name, wchar_t * description, wchar_t * nominalValue)
#else
__int64	buildPropertySingleValue(char * name, char * description, char * nominalValue)
#endif
#else
#ifdef UNICODE
__int32	buildPropertySingleValue(wchar_t * name, wchar_t * description, wchar_t * nominalValue)
#else
__int32	buildPropertySingleValue(char * name, char * description, char * nominalValue)
#endif
#endif
{
#ifdef UNICODE
	return	buildPropertySingleValue(name, description, nominalValue, L"IFCTEXT");
#else
	return	buildPropertySingleValue(name, description, nominalValue, "IFCTEXT");
#endif
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildPropertySingleValue(wchar_t * name, wchar_t * description, wchar_t * nominalValue, wchar_t * typePath)
#else
__int64	buildPropertySingleValue(char * name, char * description, char * nominalValue, char * typePath)
#endif
#else
#ifdef UNICODE
__int32	buildPropertySingleValue(wchar_t * name, wchar_t * description, wchar_t * nominalValue, wchar_t * typePath)
#else
__int32	buildPropertySingleValue(char * name, char * description, char * nominalValue, char * typePath)
#endif
#endif
{
#ifdef WIN64
	__int64	ifcPropertySingleValueInstance;
#else
	__int32	ifcPropertySingleValueInstance;
#endif
	void	* nominalValueADB;

#ifdef UNICODE
	ifcPropertySingleValueInstance = sdaiCreateInstanceBN(model, (char*) L"IFCPROPERTYSINGLEVALUE");

	sdaiPutAttrBN(ifcPropertySingleValueInstance, (char*) L"Name", sdaiUNICODE, name);
	sdaiPutAttrBN(ifcPropertySingleValueInstance, (char*) L"Description", sdaiUNICODE, description);
#else
	ifcPropertySingleValueInstance = sdaiCreateInstanceBN(model, "IFCPROPERTYSINGLEVALUE");

	sdaiPutAttrBN(ifcPropertySingleValueInstance, "Name", sdaiSTRING, name);
	sdaiPutAttrBN(ifcPropertySingleValueInstance, "Description", sdaiSTRING, description);
#endif

#ifdef UNICODE
	nominalValueADB = sdaiCreateADB(sdaiUNICODE, nominalValue);
	sdaiPutADBTypePath(nominalValueADB, 1, (char*) typePath); 
	sdaiPutAttrBN(ifcPropertySingleValueInstance, (char*) L"NominalValue", sdaiADB, (void*) nominalValueADB);
#else
	nominalValueADB = sdaiCreateADB(sdaiSTRING, nominalValue);
	sdaiPutADBTypePath(nominalValueADB, 1, typePath); 
	sdaiPutAttrBN(ifcPropertySingleValueInstance, "NominalValue", sdaiADB, (void*) nominalValueADB);
#endif

	ASSERT(ifcPropertySingleValueInstance);

	return	ifcPropertySingleValueInstance;
}


//
//
//		ElementQuantity, QuantityLength, QuantityArea, QuantityVolume
//
//


#ifdef WIN64
#ifdef UNICODE
__int64	buildElementQuantity(wchar_t * name, __int64 ** aggrQuantities)
#else
__int64	buildElementQuantity(char * name, __int64 ** aggrQuantities)
#endif
#else
#ifdef UNICODE
__int32	buildElementQuantity(wchar_t * name, __int32 ** aggrQuantities)
#else
__int32	buildElementQuantity(char * name, __int32 ** aggrQuantities)
#endif
#endif
{
#ifdef WIN64
	__int64	ifcElementQuantityInstance;
#else
	__int32	ifcElementQuantityInstance;
#endif

#ifdef UNICODE
	ifcElementQuantityInstance = sdaiCreateInstanceBN(model, (char*) L"IFCELEMENTQUANTITY");

	sdaiPutAttrBN(ifcElementQuantityInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcElementQuantityInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcElementQuantityInstance, (char*) L"Name", sdaiUNICODE, name);

	(* aggrQuantities) = sdaiCreateAggrBN(ifcElementQuantityInstance, (char*) L"Quantities");
#else
	ifcElementQuantityInstance = sdaiCreateInstanceBN(model, "IFCELEMENTQUANTITY");

	sdaiPutAttrBN(ifcElementQuantityInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcElementQuantityInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());
	sdaiPutAttrBN(ifcElementQuantityInstance, "Name", sdaiSTRING, name);

	(* aggrQuantities) = sdaiCreateAggrBN(ifcElementQuantityInstance, "Quantities");
#endif

	ASSERT(ifcElementQuantityInstance);

	return	ifcElementQuantityInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildQuantityLength(wchar_t * name, wchar_t * description, double length)
#else
__int64	buildQuantityLength(char * name, char * description, double length)
#endif
#else
#ifdef UNICODE
__int32	buildQuantityLength(wchar_t * name, wchar_t * description, double length)
#else
__int32	buildQuantityLength(char * name, char * description, double length)
#endif
#endif
{
#ifdef WIN64
	__int64	ifcQuantityLengthInstance;
#else
	__int32	ifcQuantityLengthInstance;
#endif

#ifdef UNICODE
	ifcQuantityLengthInstance = sdaiCreateInstanceBN(model, (char*) L"IFCQUANTITYLENGTH");

	sdaiPutAttrBN(ifcQuantityLengthInstance, (char*) L"Name", sdaiUNICODE, name);
	sdaiPutAttrBN(ifcQuantityLengthInstance, (char*) L"Description", sdaiUNICODE, description);
	sdaiPutAttrBN(ifcQuantityLengthInstance, (char*) L"LengthValue", sdaiREAL, &length);
#else
	ifcQuantityLengthInstance = sdaiCreateInstanceBN(model, "IFCQUANTITYLENGTH");

	sdaiPutAttrBN(ifcQuantityLengthInstance, "Name", sdaiSTRING, name);
	sdaiPutAttrBN(ifcQuantityLengthInstance, "Description", sdaiSTRING, description);
	sdaiPutAttrBN(ifcQuantityLengthInstance, "LengthValue", sdaiREAL, &length);
#endif

	ASSERT(ifcQuantityLengthInstance);

	return	ifcQuantityLengthInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildQuantityArea(wchar_t * name, wchar_t * description, double area)
#else
__int64	buildQuantityArea(char * name, char * description, double area)
#endif
#else
#ifdef UNICODE
__int32	buildQuantityArea(wchar_t * name, wchar_t * description, double area)
#else
__int32	buildQuantityArea(char * name, char * description, double area)
#endif
#endif
{
#ifdef WIN64
	__int64	ifcQuantityAreaInstance;
#else
	__int32	ifcQuantityAreaInstance;
#endif

#ifdef UNICODE
	ifcQuantityAreaInstance = sdaiCreateInstanceBN(model, (char*) L"IFCQUANTITYAREA");

	sdaiPutAttrBN(ifcQuantityAreaInstance, (char*) L"Name", sdaiUNICODE, name);
	sdaiPutAttrBN(ifcQuantityAreaInstance, (char*) L"Description", sdaiUNICODE, description);
	sdaiPutAttrBN(ifcQuantityAreaInstance, (char*) L"AreaValue", sdaiREAL, &area);
#else
	ifcQuantityAreaInstance = sdaiCreateInstanceBN(model, "IFCQUANTITYAREA");

	sdaiPutAttrBN(ifcQuantityAreaInstance, "Name", sdaiSTRING, name);
	sdaiPutAttrBN(ifcQuantityAreaInstance, "Description", sdaiSTRING, description);
	sdaiPutAttrBN(ifcQuantityAreaInstance, "AreaValue", sdaiREAL, &area);
#endif

	ASSERT(ifcQuantityAreaInstance);

	return	ifcQuantityAreaInstance;
}

#ifdef WIN64
#ifdef UNICODE
__int64	buildQuantityVolume(wchar_t * name, wchar_t * description, double volume)
#else
__int64	buildQuantityVolume(char * name, char * description, double volume)
#endif
#else
#ifdef UNICODE
__int32	buildQuantityVolume(wchar_t * name, wchar_t * description, double volume)
#else
__int32	buildQuantityVolume(char * name, char * description, double volume)
#endif
#endif
{
#ifdef WIN64
	__int64	ifcQuantityVolumeInstance;
#else
	__int32	ifcQuantityVolumeInstance;
#endif

#ifdef UNICODE
	ifcQuantityVolumeInstance = sdaiCreateInstanceBN(model, (char*) L"IFCQUANTITYVOLUME");

	sdaiPutAttrBN(ifcQuantityVolumeInstance, (char*) L"Name", sdaiUNICODE, name);
	sdaiPutAttrBN(ifcQuantityVolumeInstance, (char*) L"Description", sdaiUNICODE, description);
	sdaiPutAttrBN(ifcQuantityVolumeInstance, (char*) L"VolumeValue", sdaiREAL, &volume);
#else
	ifcQuantityVolumeInstance = sdaiCreateInstanceBN(model, "IFCQUANTITYVOLUME");

	sdaiPutAttrBN(ifcQuantityVolumeInstance, "Name", sdaiSTRING, name);
	sdaiPutAttrBN(ifcQuantityVolumeInstance, "Description", sdaiSTRING, description);
	sdaiPutAttrBN(ifcQuantityVolumeInstance, "VolumeValue", sdaiREAL, &volume);
#endif

	ASSERT(ifcQuantityVolumeInstance);

	return	ifcQuantityVolumeInstance;
}


//
//
//		Pset_WallCommon, BaseQuantities_Wall, BaseQuantities_WallStandardCase, BaseQuantities_Opening, Pset_WindowCommon, BaseQuantities_Window
//
//


#ifdef WIN64
__int64	buildPset_WallCommon()
#else
__int32	buildPset_WallCommon()
#endif
{
#ifdef WIN64
	__int64	ifcPropertySetInstance, * aggrHasProperties;
#else
	__int32	ifcPropertySetInstance, * aggrHasProperties;
#endif

#ifdef UNICODE
	ifcPropertySetInstance = buildPropertySet(L"Pset_WallCommon", &aggrHasProperties);

#ifdef WIN64
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"Reference", L"Reference", L"", L"IFCIDENTIFIER"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"AcousticRating", L"AcousticRating", L"", L"IFCLABEL"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"FireRating", L"FireRating", L"", L"IFCLABEL"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"Combustible", L"Combustible", false));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"SurfaceSpreadOfFlame", L"SurfaceSpreadOfFlame", L"", L"IFCLABEL"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"ThermalTransmittance", L"ThermalTransmittance", 0.24, L"IFCTHERMALTRANSMITTANCEMEASURE"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"IsExternal", L"IsExternal", true));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"ExtendToStructure", L"ExtendToStructure", false));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"LoadBearing", L"LoadBearing", false));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"Compartmentation", L"Compartmentation", false));
#else
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"Reference", L"Reference", L"", L"IFCIDENTIFIER"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"AcousticRating", L"AcousticRating", L"", L"IFCLABEL"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"FireRating", L"FireRating", L"", L"IFCLABEL"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"Combustible", L"Combustible", false));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"SurfaceSpreadOfFlame", L"SurfaceSpreadOfFlame", L"", L"IFCLABEL"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"ThermalTransmittance", L"ThermalTransmittance", 0.24, L"IFCTHERMALTRANSMITTANCEMEASURE"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"IsExternal", L"IsExternal", true));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"ExtendToStructure", L"ExtendToStructure", false));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"LoadBearing", L"LoadBearing", false));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"Compartmentation", L"Compartmentation", false));
#endif
#else
	ifcPropertySetInstance = buildPropertySet("Pset_WallCommon", &aggrHasProperties);

#ifdef WIN64
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("Reference", "Reference", "", "IFCIDENTIFIER"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("AcousticRating", "AcousticRating", "", "IFCLABEL"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("FireRating", "FireRating", "", "IFCLABEL"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("Combustible", "Combustible", false));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("SurfaceSpreadOfFlame", "SurfaceSpreadOfFlame", "", "IFCLABEL"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("ThermalTransmittance", "ThermalTransmittance", 0.24, "IFCTHERMALTRANSMITTANCEMEASURE"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("IsExternal", "IsExternal", true));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("ExtendToStructure", "ExtendToStructure", false));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("LoadBearing", "LoadBearing", false));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("Compartmentation", "Compartmentation", false));
#else
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("Reference", "Reference", "", "IFCIDENTIFIER"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("AcousticRating", "AcousticRating", "", "IFCLABEL"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("FireRating", "FireRating", "", "IFCLABEL"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("Combustible", "Combustible", false));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("SurfaceSpreadOfFlame", "SurfaceSpreadOfFlame", "", "IFCLABEL"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("ThermalTransmittance", "ThermalTransmittance", 0.24, "IFCTHERMALTRANSMITTANCEMEASURE"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("IsExternal", "IsExternal", true));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("ExtendToStructure", "ExtendToStructure", false));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("LoadBearing", "LoadBearing", false));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("Compartmentation", "Compartmentation", false));
#endif
#endif

	ASSERT(ifcPropertySetInstance);

	return	ifcPropertySetInstance;
}

#ifdef WIN64
__int64	buildBaseQuantities_Wall(double width, double length, double height, double openingArea, double linearConversionFactor)
#else
__int32	buildBaseQuantities_Wall(double width, double length, double height, double openingArea, double linearConversionFactor)
#endif
{
#ifdef WIN64
	__int64	ifcElementQuantityInstance, * aggrQuantities;
#else
	__int32	ifcElementQuantityInstance, * aggrQuantities;
#endif
	double	grossSideArea = (length / linearConversionFactor) * (height / linearConversionFactor),
			netSideArea = grossSideArea - openingArea;

#ifdef UNICODE
	ifcElementQuantityInstance = buildElementQuantity(L"BaseQuantities", &aggrQuantities);

#ifdef WIN64
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Width", L"Width", width));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Length", L"Length", length));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"GrossFootprintArea", L"GrossFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"NetFootprintArea", L"NetFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"GrossSideArea", L"GrossSideArea", grossSideArea));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"NetSideArea", L"NetSideArea", netSideArea));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume(L"GrossVolume", L"GrossVolume", grossSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume(L"NetVolume", L"NetVolume", netSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Height", L"Height", height));
#else
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Width", L"Width", width));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Length", L"Length", length));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"GrossFootprintArea", L"GrossFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"NetFootprintArea", L"NetFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"GrossSideArea", L"GrossSideArea", grossSideArea));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"NetSideArea", L"NetSideArea", netSideArea));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume(L"GrossVolume", L"GrossVolume", grossSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume(L"NetVolume", L"NetVolume", netSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Height", L"Height", height));
#endif
#else
	ifcElementQuantityInstance = buildElementQuantity("BaseQuantities", &aggrQuantities);

#ifdef WIN64
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Width", "Width", width));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Length", "Length", length));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("GrossFootprintArea", "GrossFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("NetFootprintArea", "NetFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("GrossSideArea", "GrossSideArea", grossSideArea));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("NetSideArea", "NetSideArea", netSideArea));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume("GrossVolume", "GrossVolume", grossSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume("NetVolume", "NetVolume", netSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Height", "Height", height));
#else
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Width", "Width", width));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Length", "Length", length));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("GrossFootprintArea", "GrossFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("NetFootprintArea", "NetFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("GrossSideArea", "GrossSideArea", grossSideArea));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("NetSideArea", "NetSideArea", netSideArea));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume("GrossVolume", "GrossVolume", grossSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume("NetVolume", "NetVolume", netSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Height", "Height", height));
#endif
#endif

	ASSERT(ifcElementQuantityInstance);

	return	ifcElementQuantityInstance;
}

#ifdef WIN64
__int64	buildBaseQuantities_WallStandardCase(double width, double length, double height, double openingArea, double linearConversionFactor)
#else
__int32	buildBaseQuantities_WallStandardCase(double width, double length, double height, double openingArea, double linearConversionFactor)
#endif
{
#ifdef WIN64
	__int64	ifcElementQuantityInstance, * aggrQuantities;
#else
	__int32	ifcElementQuantityInstance, * aggrQuantities;
#endif

	double	grossSideArea = (length / linearConversionFactor) * (height / linearConversionFactor),
			netSideArea = grossSideArea - openingArea;

#ifdef UNICODE
	ifcElementQuantityInstance = buildElementQuantity(L"BaseQuantities", &aggrQuantities);

#ifdef WIN64
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Width", L"Width", width));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Length", L"Length", length));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"GrossFootprintArea", L"GrossFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"NetFootprintArea", L"NetFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"GrossSideArea", L"GrossSideArea", grossSideArea));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"NetSideArea", L"NetSideArea", netSideArea));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume(L"GrossVolume", L"GrossVolume", grossSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume(L"NetVolume", L"NetVolume", netSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Height", L"Height", height));
#else
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Width", L"Width", width));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Length", L"Length", length));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"GrossFootprintArea", L"GrossFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"NetFootprintArea", L"NetFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"GrossSideArea", L"GrossSideArea", grossSideArea));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea(L"NetSideArea", L"NetSideArea", netSideArea));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume(L"GrossVolume", L"GrossVolume", grossSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume(L"NetVolume", L"NetVolume", netSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Height", L"Height", height));
#endif
#else
	ifcElementQuantityInstance = buildElementQuantity("BaseQuantities", &aggrQuantities);

#ifdef WIN64
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Width", "Width", width));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Length", "Length", length));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("GrossFootprintArea", "GrossFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("NetFootprintArea", "NetFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("GrossSideArea", "GrossSideArea", grossSideArea));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("NetSideArea", "NetSideArea", netSideArea));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume("GrossVolume", "GrossVolume", grossSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume("NetVolume", "NetVolume", netSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Height", "Height", height));
#else
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Width", "Width", width));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Length", "Length", length));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("GrossFootprintArea", "GrossFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("NetFootprintArea", "NetFootprintArea", (length / linearConversionFactor) * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("GrossSideArea", "GrossSideArea", grossSideArea));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityArea("NetSideArea", "NetSideArea", netSideArea));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume("GrossVolume", "GrossVolume", grossSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityVolume("NetVolume", "NetVolume", netSideArea * (width / linearConversionFactor)));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Height", "Height", height));
#endif
#endif

	ASSERT(ifcElementQuantityInstance);

	return	ifcElementQuantityInstance;
}

#ifdef WIN64
__int64	buildBaseQuantities_Opening(double depth, double height, double width)
#else
__int32	buildBaseQuantities_Opening(double depth, double height, double width)
#endif
{
#ifdef WIN64
	__int64	ifcElementQuantityInstance, * aggrQuantities;
#else
	__int32	ifcElementQuantityInstance, * aggrQuantities;
#endif

#ifdef UNICODE
	ifcElementQuantityInstance = buildElementQuantity(L"BaseQuantities", &aggrQuantities);

#ifdef WIN64
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Depth", L"Depth", depth));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Height", L"Height", height));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Width", L"Width", width));
#else
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Depth", L"Depth", depth));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Height", L"Height", height));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Width", L"Width", width));
#endif
#else
	ifcElementQuantityInstance = buildElementQuantity("BaseQuantities", &aggrQuantities);

#ifdef WIN64
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Depth", "Depth", depth));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Height", "Height", height));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Width", "Width", width));
#else
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Depth", "Depth", depth));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Height", "Height", height));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Width", "Width", width));
#endif
#endif

	ASSERT(ifcElementQuantityInstance);

	return	ifcElementQuantityInstance;
}

#ifdef WIN64
__int64	buildPset_WindowCommon()
#else
__int32	buildPset_WindowCommon()
#endif
{
#ifdef WIN64
	__int64	ifcPropertySetInstance, * aggrHasProperties;
#else
	__int32	ifcPropertySetInstance, * aggrHasProperties;
#endif

#ifdef UNICODE
	ifcPropertySetInstance = buildPropertySet(L"Pset_WindowCommon", &aggrHasProperties);

#ifdef WIN64
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"Reference", L"Reference", L"", L"IFCIDENTIFIER"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"FireRating", L"FireRating", L"", L"IFCLABEL"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"AcousticRating", L"AcousticRating", L"", L"IFCLABEL"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"SecurityRating", L"SecurityRating", L"", L"IFCLABEL"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"IsExternal", L"IsExternal", true));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"Infiltration", L"Infiltration", 0.3, L"IFCVOLUMETRICFLOWRATEMEASURE"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"ThermalTransmittance", L"ThermalTransmittance", 0.24, L"IFCTHERMALTRANSMITTANCEMEASURE"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"GlazingAreaFraction", L"GlazingAreaFraction", 0.7, L"IFCPOSITIVERATIOMEASURE"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"SmokeStop", L"SmokeStop", false));
#else
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"Reference", L"Reference", L"", L"IFCIDENTIFIER"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"FireRating", L"FireRating", L"", L"IFCLABEL"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"AcousticRating", L"AcousticRating", L"", L"IFCLABEL"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"SecurityRating", L"SecurityRating", L"", L"IFCLABEL"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"IsExternal", L"IsExternal", true));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"Infiltration", L"Infiltration", 0.3, L"IFCVOLUMETRICFLOWRATEMEASURE"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"ThermalTransmittance", L"ThermalTransmittance", 0.24, L"IFCTHERMALTRANSMITTANCEMEASURE"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"GlazingAreaFraction", L"GlazingAreaFraction", 0.7, L"IFCPOSITIVERATIOMEASURE"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue(L"SmokeStop", L"SmokeStop", false));
#endif
#else
	ifcPropertySetInstance = buildPropertySet("Pset_WindowCommon", &aggrHasProperties);

#ifdef WIN64
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("Reference", "Reference", "", "IFCIDENTIFIER"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("FireRating", "FireRating", "", "IFCLABEL"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("AcousticRating", "AcousticRating", "", "IFCLABEL"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("SecurityRating", "SecurityRating", "", "IFCLABEL"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("IsExternal", "IsExternal", true));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("Infiltration", "Infiltration", 0.3, "IFCVOLUMETRICFLOWRATEMEASURE"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("ThermalTransmittance", "ThermalTransmittance", 0.24, "IFCTHERMALTRANSMITTANCEMEASURE"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("GlazingAreaFraction", "GlazingAreaFraction", 0.7, "IFCPOSITIVERATIOMEASURE"));
	sdaiAppend((__int64) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("SmokeStop", "SmokeStop", false));
#else
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("Reference", "Reference", "", "IFCIDENTIFIER"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("FireRating", "FireRating", "", "IFCLABEL"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("AcousticRating", "AcousticRating", "", "IFCLABEL"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("SecurityRating", "SecurityRating", "", "IFCLABEL"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("IsExternal", "IsExternal", true));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("Infiltration", "Infiltration", 0.3, "IFCVOLUMETRICFLOWRATEMEASURE"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("ThermalTransmittance", "ThermalTransmittance", 0.24, "IFCTHERMALTRANSMITTANCEMEASURE"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("GlazingAreaFraction", "GlazingAreaFraction", 0.7, "IFCPOSITIVERATIOMEASURE"));
	sdaiAppend((__int32) aggrHasProperties, sdaiINSTANCE, (void *) buildPropertySingleValue("SmokeStop", "SmokeStop", false));
#endif
#endif

	ASSERT(ifcPropertySetInstance);

	return	ifcPropertySetInstance;
}

#ifdef WIN64
__int64	buildBaseQuantities_Window(double height, double width)
#else
__int32	buildBaseQuantities_Window(double height, double width)
#endif
{
#ifdef WIN64
	__int64	ifcElementQuantityInstance, * aggrQuantities;
#else
	__int32	ifcElementQuantityInstance, * aggrQuantities;
#endif

#ifdef UNICODE
	ifcElementQuantityInstance = buildElementQuantity(L"BaseQuantities", &aggrQuantities);

#ifdef WIN64
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Height", L"Height", height));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Width", L"Width", width));
#else
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Height", L"Height", height));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength(L"Width", L"Width", width));
#endif
#else
	ifcElementQuantityInstance = buildElementQuantity("BaseQuantities", &aggrQuantities);

#ifdef WIN64
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Height", "Height", height));
	sdaiAppend((__int64) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Width", "Width", width));
#else
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Height", "Height", height));
	sdaiAppend((__int32) aggrQuantities, sdaiINSTANCE, (void *) buildQuantityLength("Width", "Width", width));
#endif
#endif

	ASSERT(ifcElementQuantityInstance);

	return	ifcElementQuantityInstance;
}


//
//
//		RelDefinesByProperties
//
//


#ifdef WIN64
__int64	buildRelDefinesByProperties(__int64 relatedObject, __int64 relatingPropertyDefinition)
#else
__int32	buildRelDefinesByProperties(__int32 relatedObject, __int32 relatingPropertyDefinition)
#endif
{
#ifdef WIN64
	__int64	ifcRelDefinesByPropertiesInstance, * aggrRelatedObjects;
#else
	__int32	ifcRelDefinesByPropertiesInstance, * aggrRelatedObjects;
#endif

#ifdef UNICODE
	ifcRelDefinesByPropertiesInstance = sdaiCreateInstanceBN(model, (char*) L"IFCRELDEFINESBYPROPERTIES");

	sdaiPutAttrBN(ifcRelDefinesByPropertiesInstance, (char*) L"GlobalId", sdaiUNICODE, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelDefinesByPropertiesInstance, (char*) L"OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	aggrRelatedObjects = sdaiCreateAggrBN(ifcRelDefinesByPropertiesInstance, (char*) L"RelatedObjects");
#else
	ifcRelDefinesByPropertiesInstance = sdaiCreateInstanceBN(model, "IFCRELDEFINESBYPROPERTIES");

	sdaiPutAttrBN(ifcRelDefinesByPropertiesInstance, "GlobalId", sdaiSTRING, (void*) CreateCompressedGuidString());
	sdaiPutAttrBN(ifcRelDefinesByPropertiesInstance, "OwnerHistory", sdaiINSTANCE, (void*) getOwnerHistoryInstance());

	aggrRelatedObjects = sdaiCreateAggrBN(ifcRelDefinesByPropertiesInstance, "RelatedObjects");
#endif
#ifdef WIN64
	sdaiAppend((__int64) aggrRelatedObjects, sdaiINSTANCE, (void *) relatedObject);
#else
	sdaiAppend((__int32) aggrRelatedObjects, sdaiINSTANCE, (void *) relatedObject);
#endif
#ifdef UNICODE
	sdaiPutAttrBN(ifcRelDefinesByPropertiesInstance, (char*) L"RelatingPropertyDefinition", sdaiINSTANCE, (void *) relatingPropertyDefinition);
#else
	sdaiPutAttrBN(ifcRelDefinesByPropertiesInstance, "RelatingPropertyDefinition", sdaiINSTANCE, (void *) relatingPropertyDefinition);
#endif

	ASSERT(ifcRelDefinesByPropertiesInstance);

	return	ifcRelDefinesByPropertiesInstance;
}
