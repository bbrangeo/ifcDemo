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


//
//
//		PropertySet, PropertySingleValue
//
//


#ifdef WIN64
#ifdef UNICODE
__int64	buildPropertySet(wchar_t * name, __int64 ** aggrHasProperties);
__int64	buildPropertySingleValue(wchar_t * name, wchar_t * description, bool nominalValue);
__int64	buildPropertySingleValue(wchar_t * name, wchar_t * description, bool nominalValue, wchar_t * typePath);
__int64	buildPropertySingleValue(wchar_t * name, wchar_t * description, double nominalValue);
__int64	buildPropertySingleValue(wchar_t * name, wchar_t * description, double nominalValue, wchar_t * typePath);
__int64	buildPropertySingleValue(wchar_t * name, wchar_t * description, wchar_t * nominalValue);
__int64	buildPropertySingleValue(wchar_t * name, wchar_t * description, wchar_t * nominalValue, wchar_t * typePath);
#else
__int64	buildPropertySet(char * name, __int64 ** aggrHasProperties);
__int64	buildPropertySingleValue(char * name, char * description, bool nominalValue);
__int64	buildPropertySingleValue(char * name, char * description, bool nominalValue, char * typePath);
__int64	buildPropertySingleValue(char * name, char * description, double nominalValue);
__int64	buildPropertySingleValue(char * name, char * description, double nominalValue, char * typePath);
__int64	buildPropertySingleValue(char * name, char * description, char * nominalValue);
__int64	buildPropertySingleValue(char * name, char * description, char * nominalValue, char * typePath);
#endif
#else
#ifdef UNICODE
__int32	buildPropertySet(wchar_t * name, __int32 ** aggrHasProperties);
__int32	buildPropertySingleValue(wchar_t * name, wchar_t * description, bool nominalValue);
__int32	buildPropertySingleValue(wchar_t * name, wchar_t * description, bool nominalValue, wchar_t * typePath);
__int32	buildPropertySingleValue(wchar_t * name, wchar_t * description, double nominalValue);
__int32	buildPropertySingleValue(wchar_t * name, wchar_t * description, double nominalValue, wchar_t * typePath);
__int32	buildPropertySingleValue(wchar_t * name, wchar_t * description, wchar_t * nominalValue);
__int32	buildPropertySingleValue(wchar_t * name, wchar_t * description, wchar_t * nominalValue, wchar_t * typePath);
#else
__int32	buildPropertySet(char * name, __int32 ** aggrHasProperties);
__int32	buildPropertySingleValue(char * name, char * description, bool nominalValue);
__int32	buildPropertySingleValue(char * name, char * description, bool nominalValue, char * typePath);
__int32	buildPropertySingleValue(char * name, char * description, double nominalValue);
__int32	buildPropertySingleValue(char * name, char * description, double nominalValue, char * typePath);
__int32	buildPropertySingleValue(char * name, char * description, char * nominalValue);
__int32	buildPropertySingleValue(char * name, char * description, char * nominalValue, char * typePath);
#endif
#endif


//
//
//		ElementQuantity, QuantityLength, QuantityArea, QuantityVolume
//
//


#ifdef WIN64
#ifdef UNICODE
__int64	buildElementQuantity(wchar_t * name, __int64 ** aggrQuantities);
__int64	buildQuantityLength(wchar_t * name, wchar_t * description, double length);
__int64	buildQuantityArea(wchar_t * name, wchar_t * description, double area);
__int64	buildQuantityVolume(wchar_t * name, wchar_t * description, double volume);
#else
__int64	buildElementQuantity(char * name, __int64 ** aggrQuantities);
__int64	buildQuantityLength(char * name, char * description, double length);
__int64	buildQuantityArea(char * name, char * description, double area);
__int64	buildQuantityVolume(char * name, char * description, double volume);
#endif
#else
#ifdef UNICODE
__int32	buildElementQuantity(wchar_t * name, __int32 ** aggrQuantities);
__int32	buildQuantityLength(wchar_t * name, wchar_t * description, double length);
__int32	buildQuantityArea(wchar_t * name, wchar_t * description, double area);
__int32	buildQuantityVolume(wchar_t * name, wchar_t * description, double volume);
#else
__int32	buildElementQuantity(char * name, __int32 ** aggrQuantities);
__int32	buildQuantityLength(char * name, char * description, double length);
__int32	buildQuantityArea(char * name, char * description, double area);
__int32	buildQuantityVolume(char * name, char * description, double volume);
#endif
#endif


//
//
//		Pset_WallCommon, BaseQuantities_Wall, BaseQuantities_WallStandardCase, BaseQuantities_Opening, Pset_WindowCommon, BaseQuantities_Window
//
//


#ifdef WIN64
__int64	buildPset_WallCommon();
__int64	buildBaseQuantities_Wall(double width, double length, double height, double openingArea, double linearConversionFactor);
__int64	buildBaseQuantities_WallStandardCase(double width, double length, double height, double openingArea, double linearConversionFactor);
__int64	buildBaseQuantities_Opening(double depth, double height, double width);
__int64	buildPset_WindowCommon();
__int64	buildBaseQuantities_Window(double height, double width);
#else
__int32	buildPset_WallCommon();
__int32	buildBaseQuantities_Wall(double width, double length, double height, double openingArea, double linearConversionFactor);
__int32	buildBaseQuantities_WallStandardCase(double width, double length, double height, double openingArea, double linearConversionFactor);
__int32	buildBaseQuantities_Opening(double depth, double height, double width);
__int32	buildPset_WindowCommon();
__int32	buildBaseQuantities_Window(double height, double width);
#endif


//
//
//		RelDefinesByProperties
//
//


#ifdef WIN64
__int64	buildRelDefinesByProperties(__int64 relatedObject, __int64 relatingPropertyDefinition);
#else
__int32	buildRelDefinesByProperties(__int32 relatedObject, __int32 relatingPropertyDefinition);
#endif
