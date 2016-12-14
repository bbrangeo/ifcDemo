////////////////////////////////////////////////////////////////////////
//  Author:  Peter Bonsma
//  Project: IFC Engine Series (example using DLL)
//
//  This code may be used and edited freely,
//  also for commercial projects in open and closed source software
//
//  In case of use of the DLL:
//  be aware of license fee for use of this DLL when used commercially
//  more info for commercial use:	peter.bonsma@rdf.bg
//
//  more info for using the IFC Engine DLL in other languages
//	and creation of specific code examples:
//								    peter.bonsma@rdf.bg
////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "IFCEngineInteract.h"
#include "matrixVectorOperations.h"

#include "ifcengine\include\ifcengine.h"
#include "ifcengine\include\engine.h"

#include <math.h>


//#include	<stdint.h>

#if defined(WIN64) || defined(__LP64__)
	#define int __int64
#else
	#define int __int32
#endif

int		glCnt, totalNoFiles = 0, totalNoObjects = 0, totalNoTriangles = 0;

int		ifcModel = 0;

STRUCT_INSTANCES	* first_instance = 0;

char	* ifcSchemaName_IFC2x3 = 0,
		* ifcSchemaName_IFC4 = 0,
        * ifcResultDir = 0;

extern  char    resultDir[1024];
extern  int     resultDirLength,
                skipCnt;

void    clean()
{
    while  (first_instance) {
        STRUCT_INSTANCES    * instance = first_instance;

        first_instance = first_instance->next;

        if  (instance->globalId) {
            free(instance->globalId);
        }
		free(instance->entityName);

        free(instance);
    }
}

__int32		length(char * txt)
{
    __int32 i = 0;
    while  (txt[i]) {
        i++;
    }
    return  i;
}

int     cmp(char * txtI, char * txtII)
{
    int  i = 0;

    if  (txtI) {
        if  (!txtII) {
            return  1;
        }
    } else {
        if  (txtII) {
            return  -1;
        } else {
            return  0;
        }
    }

    while  (txtI[i]) {
        if  (txtI[i] != txtII[i]) {
            if  (txtI[i] < txtII[i]) {
                return  -1;
            } else {
                ////ASSERT(txtI[i] > txtII[i]);
                return  1;
            }
        }

        i++;
    }

    if  (txtII[i]) {
        return  -1;
    } else {
        return  0;
    }
}

void    AddObject(int id, char * globalId, char * entityName)
{
    STRUCT_INSTANCES    * instance = new(STRUCT_INSTANCES);

	instance->id = id;

	if	( (globalId)  &&
		  (globalId[0]) ) {
        instance->globalId = new char[length(globalId)+1];
        memcpy(instance->globalId, globalId, length(globalId)+1);
	} else {
		instance->globalId = NULL;
	}

    instance->entityName = new char[length(entityName)+1];
    memcpy(instance->entityName, entityName, length(entityName)+1);

    if  (first_instance) {
        STRUCT_INSTANCES    * previous_instance = NULL,
                            * current_instance = first_instance;
        while  ( (current_instance)  &&
                 (cmp(current_instance->globalId, instance->globalId) < 0) ) {
            previous_instance = current_instance;
            current_instance = current_instance->next;
        }

        if  (previous_instance) {
            instance->next = previous_instance->next;
            previous_instance->next = instance;
        } else {
            instance->next = first_instance;
            first_instance = instance;
        }
    } else {
        first_instance = instance;
        first_instance->next = NULL;
    }
}

void	RetrieveObjects(int ifcModel, FILE * file, char * entityName, char * entityGroupName, CStatic * status, CStatic * totalObjects)
{
	int					cnt = 0;
	char				buffer[512];

    CString info = "Model read correctly\nSearching for IFC objects in ";
    info += entityGroupName;
    info += "\n";
    _itoa_s((__int32) glCnt, buffer, 512, 10);
    info += buffer;
    info += " IFC objects found untill now";

    status->SetWindowText(info);

	int	* ifcInstances = sdaiGetEntityExtentBN(ifcModel, entityName),
		noIfcInstances = sdaiGetMemberCount(ifcInstances);
	if	(noIfcInstances) {
		for (int i = 0; i < noIfcInstances; ++i) {
			int	ifcInstance = 0;
			engiGetAggrElement(ifcInstances, i, sdaiINSTANCE, &ifcInstance);

			char	* globalId = 0;
			sdaiGetAttrBN(ifcInstance, "GlobalId", sdaiSTRING, &globalId);

            info = "Model read correctly\nSearching for IFC objects in ";
            info += entityGroupName;
            info += "\n";
            _itoa_s((__int32) ++glCnt, buffer, 512, 10);
			info += buffer;
            info += " IFC objects found untill now";

            status->SetWindowText(info);

            _itoa_s((__int32) ++totalNoObjects, buffer, 512, 10);
            totalObjects->SetWindowText(buffer);

            cnt++;
			AddObject(ifcInstance, globalId, entityName);
		}

        info = "Model read correctly\nSearching for IFC objects in ";
        info += entityGroupName;
        info += "\n";
        _itoa_s((__int32) glCnt, buffer, 512, 10);
        info += buffer;
        info += " IFC objects found untill now";

        status->SetWindowText(info);

        _itoa_s((__int32) totalNoObjects, buffer, 512, 10);
        totalObjects->SetWindowText(buffer);
	}
    
    if  (cnt) {
		fprintf(file, "\t\t<%s>%i</%s>\n", entityName, cnt, entityName);
    }
}

bool    contains(char * txtI, char * txtII)
{
	if	(!txtI  ||  !txtII) {
		return	false;
	}
    int    i = 0;
    while  (txtI[i]  &&  txtII[i]) {
        if  (txtI[i] != txtII[i]) {
            return  false;
        }
        i++;
    }
    if  (txtII[i]) {
        return    false;
    } else {
        return    true;
    }
}

void	GetUnits(int ifcModel, FILE * file, int ifcProjectInstance)
{
    int ifcUnitAssignmentInstance = 0;
    sdaiGetAttrBN(ifcProjectInstance, "UnitsInContext", sdaiINSTANCE, &ifcUnitAssignmentInstance);

	if	(ifcUnitAssignmentInstance) {
		int	ifcConversianBasedUnit_TYPE = sdaiGetEntity(ifcModel, "IFCCONVERSIONBASEDUNIT"),
			ifcSIUnit_TYPE = sdaiGetEntity(ifcModel, "IFCSIUNIT");

		int * unit_set = 0, unit_cnt, i = 0;
		sdaiGetAttrBN(ifcUnitAssignmentInstance, "Units", sdaiAGGR, &unit_set);
		unit_cnt = sdaiGetMemberCount(unit_set);
		for (i = 0; i < unit_cnt; ++i) {
			int		ifcUnitInstance = 0;
			engiGetAggrElement(unit_set, i, sdaiINSTANCE, &ifcUnitInstance);
			if	(sdaiGetInstanceType(ifcUnitInstance) == ifcConversianBasedUnit_TYPE) {
				int	ifcMeasureWithUnitInstance = 0;
				sdaiGetAttrBN(ifcUnitInstance, "ConversionFactor", sdaiINSTANCE, &ifcMeasureWithUnitInstance);
				if	(ifcMeasureWithUnitInstance) {
					int	ifcSIUnitInstance = 0;
					sdaiGetAttrBN(ifcMeasureWithUnitInstance, "UnitComponent", sdaiINSTANCE, &ifcSIUnitInstance);
					if	(sdaiGetInstanceType(ifcSIUnitInstance) == ifcSIUnit_TYPE) {
						char	* unitType = 0, * prefix = 0, * name = 0;
						sdaiGetAttrBN(ifcSIUnitInstance, "UnitType", sdaiSTRING, &unitType);
						sdaiGetAttrBN(ifcSIUnitInstance, "Prefix", sdaiSTRING, &prefix);
						sdaiGetAttrBN(ifcSIUnitInstance, "Name", sdaiSTRING, &name);

						fprintf(file, "\t\t\t<unit>\n");
						if	(name) {
							fprintf(file, "\t\t\t\t<name>%s</name>\n", name);
						}
						if	(prefix) {
							fprintf(file, "\t\t\t\t<prefix>%s</prefix>\n", prefix);
						}
						if	(unitType) {
							fprintf(file, "\t\t\t\t<unitType>%s</unitType>\n", unitType);
						}
						fprintf(file, "\t\t\t</unit>\n");
					} else {
						////ASSERT(false);
					}
				} else {
					////ASSERT(false);
				}
			} else if  (sdaiGetInstanceType(ifcUnitInstance) == ifcSIUnit_TYPE) {

				char	* unitType = 0, * prefix = 0, * name = 0;
				sdaiGetAttrBN(ifcUnitInstance, "UnitType", sdaiSTRING, &unitType);
				sdaiGetAttrBN(ifcUnitInstance, "Prefix", sdaiSTRING, &prefix);
				sdaiGetAttrBN(ifcUnitInstance, "Name", sdaiSTRING, &name);

				fprintf(file, "\t\t\t<unit>\n");
				if	(name) {
					fprintf(file, "\t\t\t\t<name>%s</name>\n", name);
				}
				if	(prefix) {
					fprintf(file, "\t\t\t\t<prefix>%s</prefix>\n", prefix);
				}
				if	(unitType) {
					fprintf(file, "\t\t\t\t<unitType>%s</unitType>\n", unitType);
				}
				fprintf(file, "\t\t\t</unit>\n");
			} else {
		//		////ASSERT(false);
			}
		}
	}
}

void	GetProjects(int ifcModel, FILE * file)
{
	int	* ifcProjectInstances = sdaiGetEntityExtentBN(ifcModel, "IFCPROJECT"),
		noIfcProjectInstances = sdaiGetMemberCount(ifcProjectInstances);
	if	(noIfcProjectInstances) {
        fprintf(file, "\t<ifcProjects>\n");
		for (int i = 0; i < noIfcProjectInstances; ++i) {
			char	* globalId = 0, * name = 0, * description = 0;
			int		ifcProjectInstance = 0;
			engiGetAggrElement(ifcProjectInstances, i, sdaiINSTANCE, &ifcProjectInstance);

			sdaiGetAttrBN(ifcProjectInstance, "GlobalId", sdaiSTRING, &globalId);
			sdaiGetAttrBN(ifcProjectInstance, "Name", sdaiSTRING, &name);
			sdaiGetAttrBN(ifcProjectInstance, "Description", sdaiSTRING, &description);

			fprintf(file, "\t\t<ifcProject>\n");
            fprintf(file, "\t\t\t<globalid>%s</globalid>\n", globalId);
			if	(name) {
				fprintf(file, "\t\t\t<name>%s</name>\n", name);
			}
			if	(description) {
	            fprintf(file, "\t\t\t<description>%s</description>\n", description);
			}
			GetUnits(ifcModel, file, ifcProjectInstance);
			fprintf(file, "\t\t</ifcProject>\n");
		}
        fprintf(file, "\t</ifcProjects>\n");
	}
}

int		StartLoadingIfcFile(char * fileName, char * name, CStatic * status, CStatic * totalFiles, CStatic * totalObjects, CStatic * totalTriangles)
{
    char    buffer[512];

    _itoa_s((__int32) ++totalNoFiles, buffer, 512, 10);
    totalFiles->SetWindowText(buffer);

    if  (skipCnt) {
        skipCnt--;
        memcpy(buffer, "IFC model skipped, ", sizeof("IFC model skipped, "));
        _itoa_s((__int32) skipCnt, &buffer[strlen(buffer)], 512 - strlen(buffer), 10);
        memcpy(&buffer[strlen(buffer)], " more to skip", sizeof(" more to skip"));
        status->SetWindowText(buffer);
    } else {
        if  (ifcModel) {
		    sdaiCloseModel(ifcModel);
            ifcModel = 0;

            clean();
        }

        status->SetWindowText("Reading IFC model from disk");

	    ifcModel = sdaiOpenModelBN(0, fileName, ifcSchemaName_IFC2x3);

		FILE	* file = 0;
		//
		//	Check if this file is an IFC2x3 file or IFC4
		//
		bool	is_IFC2x3_file = false, is_IFC4_file = false;
		char	* fileSchema = 0;
		GetSPFFHeaderItem(ifcModel, 9, 0, sdaiSTRING, &fileSchema);
		if	(contains(fileSchema, "IFC4")  ||  contains(fileSchema, "IFC2x4")  ||  contains(fileSchema, "IFC2X4")) {
			sdaiCloseModel(ifcModel);
			ifcModel = sdaiOpenModelBN(0, fileName, ifcSchemaName_IFC4);
			is_IFC4_file = true;
		} else {
			if	(contains(fileSchema, "IFC2x3")  ||  contains(fileSchema, "IFC2X3")  ||  contains(fileSchema, "IFC2x2")  ||  contains(fileSchema, "IFC2X2")  ||  contains(fileSchema, "IFC2x_")  ||  contains(fileSchema, "IFC2X_")  ||  contains(fileSchema, "IFC20")) {
				is_IFC2x3_file = true;
			} else {
				////ASSERT(false);
			}
		}
		
		memcpy(&resultDir[resultDirLength-1], name, length(name)+1);
		int k = resultDirLength + length(name) - 1;
		while  (k > 0  &&  resultDir[k] != '.') {
			k--;
		}
		resultDir[++k] = 'x';
		resultDir[++k] = 'm';
		resultDir[++k] = 'l';
		resultDir[++k] = 0;

		if	( (ifcModel)  &&
			  (fopen_s(&file, resultDir, "w") == 0) ) {

			status->SetWindowText("Model read correctly\nSearching for IFC objects");

			fprintf(file, "<results>\n");
			fprintf(file, "\t<meta>\n");
			fprintf(file, "\t\t<location>%s</location>\n", fileName);

			glCnt = 0;

			fprintf(file, "\t</meta>\n");

			GetProjects(ifcModel, file);

			fprintf(file, "\t<objects>\n");

			if	(is_IFC2x3_file) {
				//	inherits from IfcProduct
				RetrieveObjects(ifcModel, file, _T("IFCANNOTATION"), _T("Annotation"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCBEAM"), _T("Beam"), status, totalObjects);

				//	inherits from IfcSpatialStructureElement
				RetrieveObjects(ifcModel, file, _T("IFCBUILDING"), _T("Building"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCBUILDINGELEMENT"), _T("Building Element"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCBUILDINGELEMENTCOMPONENT"), _T("Building Element Component"), status, totalObjects);

				//	inherits from IfcBuildingElementComponent
				RetrieveObjects(ifcModel, file, _T("IFCBUILDINGELEMENTPART"), _T("Building Element Part"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCBUILDINGELEMENTPROXY"), _T("Building Element Proxy"), status, totalObjects);

				//	inherits from IfcSpatialStructureElement
				RetrieveObjects(ifcModel, file, _T("IFCBUILDINGSTOREY"), _T("Building Storey"), status, totalObjects);

				//	inherits from IfcEdgeFeature
				RetrieveObjects(ifcModel, file, _T("IFCCHAMFEREDGEFEATURE"), _T("Chamfer Edge Feature"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCCOLUMN"), _T("Column"), status, totalObjects);		

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCCOVERING"), _T("Covering"), status, totalObjects);		

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCCURTAINWALL"), _T("Curtain Wall"), status, totalObjects);

				//	inherits from IfcElementComponent
				RetrieveObjects(ifcModel, file, _T("IFCDISCRETEACCESSORY"), _T("Discrete Accessory"), status, totalObjects);		

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCDISTRIBUTIONCHAMBERELEMENT"), _T("Distribution Chamber Element"), status, totalObjects);

				//	inherits from IfcDistributionElement
				RetrieveObjects(ifcModel, file, _T("IFCDISTRIBUTIONCONTROLELEMENT"), _T("Distribution Control Element"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCDISTRIBUTIONELEMENT"), _T("Distribution Element"), status, totalObjects);

				//	inherits from IfcDistributionElement
				RetrieveObjects(ifcModel, file, _T("IFCDISTRIBUTIONFLOWELEMENT"), _T("Distribution Flow Element"), status, totalObjects);

				//	inherits from IfcPort
				RetrieveObjects(ifcModel, file, _T("IFCDISTRIBUTIONPORT"), _T("Distribution Port"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCDOOR"), _T("Door"), status, totalObjects);

				//	inherits from IfcFeatureElementSubtraction
				RetrieveObjects(ifcModel, file, _T("IFCEDGEFEATURE"), _T("Edge Feature"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCELECTRICALELEMENT"), _T("Electrical Element"), status, totalObjects);

				//	inherits from IfcFlowController
				RetrieveObjects(ifcModel, file, _T("IFCELECTRICDISTRIBUTIONPOINT"), _T("Electric Distribution Point"), status, totalObjects);		

				//	inherits from IfcProduct
				RetrieveObjects(ifcModel, file, _T("IFCELEMENT"), _T("Element"), status, totalObjects);		

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCELEMENTASSEMBLY"), _T("Element Assembly"), status, totalObjects);		

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCELEMENTCOMPONENT"), _T("Element Component"), status, totalObjects);

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCENERGYCONVERSIONDEVICE"), _T("Energy Conversion Device"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCEQUIPMENTELEMENT"), _T("Equipment Element"), status, totalObjects);

				//	inherits from IfcElementComponent
				RetrieveObjects(ifcModel, file, _T("IFCFASTENER"), _T("Fastener"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCFEATUREELEMENT"), _T("Feature Element"), status, totalObjects);

				//	inherits from IfcFeatureElement
				RetrieveObjects(ifcModel, file, _T("IFCFEATUREELEMENTADDITION"), _T("Feature Element Addition"), status, totalObjects);

				//	inherits from IfcFeatureElement
				RetrieveObjects(ifcModel, file, _T("IFCFEATUREELEMENTSUBTRACTION"), _T("Feature Element Subtraction"), status, totalObjects);

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCFLOWCONTROLLER"), _T("Flow Controller"), status, totalObjects);

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCFLOWFITTING"), _T("Flow Fitting"), status, totalObjects);

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCFLOWMOVINGDEVICE"), _T("Flow Moving Device"), status, totalObjects);		

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCFLOWSEGMENT"), _T("Flow Segment"), status, totalObjects);		

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCFLOWSTORAGEDEVICE"), _T("Flow Storage Device"), status, totalObjects);		

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCFLOWTERMINAL"), _T("Flow Terminal"), status, totalObjects);

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCFLOWTREATMENTDEVICE"), _T("Flow Treatment Device"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCFOOTING"), _T("Footing"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCFURNISHINGELEMENT"), _T("Furnishing Element"), status, totalObjects);

				//	inherits from IfcProduct
				RetrieveObjects(ifcModel, file, _T("IFCGRID"), _T("Grid"), status, totalObjects);

				//	inherits from IfcFastener
				RetrieveObjects(ifcModel, file, _T("IFCMECHANICALFASTENER"), _T("Mechanical Fastener"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCMEMBER"), _T("Member"), status, totalObjects);

				//	inherits from IfcObjectDefinition
				RetrieveObjects(ifcModel, file, _T("IFCOBJECT"), _T("Object"), status, totalObjects);

				//	inherits from IfcRoot
				RetrieveObjects(ifcModel, file, _T("IFCOBJECTDEFINITION"), _T("Object Definition"), status, totalObjects);

				//	inherits from IfcFeatureElementSubtraction
				RetrieveObjects(ifcModel, file, _T("IFCOPENINGELEMENT"), _T("Opening Element"), status, totalObjects);		

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCPILE"), _T("Pile"), status, totalObjects);		

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCPLATE"), _T("Plate"), status, totalObjects);		

				//	inherits from IfcProduct
				RetrieveObjects(ifcModel, file, _T("IFCPORT"), _T("Port"), status, totalObjects);

				//	inherits from IfcObject
				RetrieveObjects(ifcModel, file, _T("IFCPRODUCT"), _T("Product"), status, totalObjects);

				//	inherits from IfcFeatureElementAddition
				RetrieveObjects(ifcModel, file, _T("IFCPROJECTIONELEMENT"), _T("Projection Element"), status, totalObjects);

				//	inherits from IfcProduct
				RetrieveObjects(ifcModel, file, _T("IFCPROXY"), _T("Proxy"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCRAILING"), _T("Railing"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCRAMP"), _T("Ramp"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCRAMPFLIGHT"), _T("Ramp Flight"), status, totalObjects);

				//	inherits from IfcReinforcingElement
				RetrieveObjects(ifcModel, file, _T("IFCREINFORCINGBAR"), _T("Reinforcing Bar"), status, totalObjects);

				//	inherits from IfcBuildingElementComponent
				RetrieveObjects(ifcModel, file, _T("IFCREINFORCINGELEMENT"), _T("Reinforcing Element"), status, totalObjects);

				//	inherits from IfcReinforcingElement
				RetrieveObjects(ifcModel, file, _T("IFCREINFORCINGMESH"), _T("Reinforcing Mesh"), status, totalObjects);		

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCROOF"), _T("Roof"), status, totalObjects);		

				//	inherits from <root>
//				RetrieveObjects(ifcModel, file, _T("IFCROOT"), _T("Root"), status, totalObjects);		

				//	inherits from IfcEdgeFeature
				RetrieveObjects(ifcModel, file, _T("IFCROUNDEDEDGEFEATURE"), _T("Rounded Edge Feature"), status, totalObjects);

				//	inherits from IfcSpatialStructureElement
				RetrieveObjects(ifcModel, file, _T("IFCSITE"), _T("Site"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCSLAB"), _T("Slab"), status, totalObjects);

				//	inherits from IfcSpatialStructureElement
				RetrieveObjects(ifcModel, file, _T("IFCSPACE"), _T("Space"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCSTAIR"), _T("Stair"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCSTAIRFLIGHT"), _T("Stair Flight"), status, totalObjects);

				//	inherits from IfcStructuralActivity
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALACTION"), _T("Structural Action"), status, totalObjects);

				//	inherits from IfcProduct
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALACTIVITY"), _T("Structural Activity"), status, totalObjects);

				//	inherits from IfcStructuralItem
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALCONNECTION"), _T("Structural Connection"), status, totalObjects);

				//	inherits from IfcStructuralConnection
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALCURVECONNECTION"), _T("Structural Curve Connection"), status, totalObjects);		

				//	inherits from IfcStructuralMember
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALCURVEMEMBER"), _T("Structural Curve Member"), status, totalObjects);		

				//	inherits from IfcStructuralCurveMember
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALCURVEMEMBERVARYING"), _T("Structural Curve Member Varying"), status, totalObjects);		

				//	inherits from IfcProduct
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALITEM"), _T("Structural Item"), status, totalObjects);

				//	inherits from IfcStructuralAction
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALLINEARACTION"), _T("Structural Linear Action"), status, totalObjects);

				//	inherits from IfcStructuralLinearAction
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALLINEARACTIONVARYING"), _T("Structural Linear Action Varying"), status, totalObjects);

				//	inherits from IfcStructuralItem
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALMEMBER"), _T("Structural Member"), status, totalObjects);

				//	inherits from IfcStructuralAction
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALPLANARACTION"), _T("Structural Planar Action"), status, totalObjects);

				//	inherits from IfcStructuralPlanarAction
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALPLANARACTIONVARYING"), _T("Structural Planar Action Varying"), status, totalObjects);

				//	inherits from IfcStructuralAction
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALPOINTACTION"), _T("Structural Point Action"), status, totalObjects);

				//	inherits from IfcStructuralConnection
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALPOINTCONNECTION"), _T("Structural Point Connection"), status, totalObjects);

				//	inherits from IfcStructuralReaction
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALPOINTREACTION"), _T("Structural Point Reaction"), status, totalObjects);

				//	inherits from IfcStructuralActivity
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALREACTION"), _T("Structural Reaction"), status, totalObjects);

				//	inherits from IfcStructuralConnection
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALSURFACECONNECTION"), _T("Structural Surface Connection"), status, totalObjects);

				//	inherits from IfcStructuralMember
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALSURFACEMEMBER"), _T("Structural Surface Member"), status, totalObjects);

				//	inherits from IfcStructuralSurfaceMember
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALSURFACEMEMBERVARYING"), _T("Structural Surface Member Varying"), status, totalObjects);

				//	inherits from IfcReinforcingElement
				RetrieveObjects(ifcModel, file, _T("IFCTENDON"), _T("Tendon"), status, totalObjects);

				//	inherits from IfcReinforcingElement
				RetrieveObjects(ifcModel, file, _T("IFCTENDONANCHOR"), _T("Tendon Anchor"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCTRANSPORTELEMENT"), _T("Transport Element"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCVIRTUALELEMENT"), _T("Virtual Element"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCWALL"), _T("Wall"), status, totalObjects);

				//	inherits from IfcWall
				RetrieveObjects(ifcModel, file, _T("IFCWALLSTANDARDCASE"), _T("Walls Standard Case"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCWINDOW"), _T("Window"), status, totalObjects);
			} else if  (is_IFC4_file) {
				//	inherits from IfcDistributionControlElement
				RetrieveObjects(ifcModel, file, _T("IFCACTUATOR"), _T("Actuator"), status, totalObjects);

				//	inherits from IfcFlowTerminal
				RetrieveObjects(ifcModel, file, _T("IFCAIRTERMINAL"), _T("Air Terminal"), status, totalObjects);

				//	inherits from IfcFlowController
				RetrieveObjects(ifcModel, file, _T("IFCAIRTERMINALBOX"), _T("Air Terminal Box"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCAIRTOAIRHEATRECOVERY"), _T("Air To Air Heat Recovery"), status, totalObjects);

				//	inherits from IfcDistributionControlElement
				RetrieveObjects(ifcModel, file, _T("IFCALARM"), _T("Alarm"), status, totalObjects);

				//	inherits from IfcProduct
				RetrieveObjects(ifcModel, file, _T("IFCANNOTATION"), _T("Annotation"), status, totalObjects);

				//	inherits from IfcFlowTerminal
				RetrieveObjects(ifcModel, file, _T("IFCAUDIOVISUALAPPLIANCE"), _T("Audio Visual Appliance"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCBEAM"), _T("Beam"), status, totalObjects);

				//	inherits from IfcBeam
				RetrieveObjects(ifcModel, file, _T("IFCBEAMSTANDARDCASE"), _T("Beam Standard Case"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCBOILER"), _T("Boiler"), status, totalObjects);

				//	inherits from IfcSpatialStructureElement
				RetrieveObjects(ifcModel, file, _T("IFCBUILDING"), _T("Building"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCBUILDINGELEMENT"), _T("Building Element"), status, totalObjects);

				//	inherits from IfcElementComponent
				RetrieveObjects(ifcModel, file, _T("IFCBUILDINGELEMENTPART"), _T("Building Element Part"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCBUILDINGELEMENTPROXY"), _T("Building Element Proxy"), status, totalObjects);

				//	inherits from IfcSpatialStructureElement
				RetrieveObjects(ifcModel, file, _T("IFCBUILDINGSTOREY"), _T("Building Storey"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCBURNER"), _T("Burner"), status, totalObjects);

				//	inherits from IfcFlowFitting
				RetrieveObjects(ifcModel, file, _T("IFCCABLECARRIERFITTING"), _T("Cable Carrier Fitting"), status, totalObjects);

				//	inherits from IfcFlowSegment
				RetrieveObjects(ifcModel, file, _T("IFCCABLECARRIERSEGMENT"), _T("Cable Carrier Segment"), status, totalObjects);

				//	inherits from IfcFlowFitting
				RetrieveObjects(ifcModel, file, _T("IFCCABLEFITTING"), _T("Cable Fitting"), status, totalObjects);

				//	inherits from IfcFlowSegment
				RetrieveObjects(ifcModel, file, _T("IFCCABLESEGMENT"), _T("Cable Segment"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCCHILLER"), _T("Chiller"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCCHIMNEY"), _T("Chimney"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCCIVILELEMENT"), _T("Civil Element"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCCOIL"), _T("Coil"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCCOLUMN"), _T("Column"), status, totalObjects);

				//	inherits from IfcColumn
				RetrieveObjects(ifcModel, file, _T("IFCCOLUMNSTANDARDCASE"), _T("Column Standard Case"), status, totalObjects);

				//	inherits from IfcFlowTerminal
				RetrieveObjects(ifcModel, file, _T("IFCCOMMUNICATIONSAPPLIANCE"), _T("Communications Appliance"), status, totalObjects);

				//	inherits from IfcFlowMovingDevice
				RetrieveObjects(ifcModel, file, _T("IFCCOMPRESSOR"), _T("Compressor"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCCONDENSER"), _T("Condenser"), status, totalObjects);

				//	inherits from IfcDistributionControlElement
				RetrieveObjects(ifcModel, file, _T("IFCCONTROLLER"), _T("Controller"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCCOOLEDBEAM"), _T("Cooled Beam"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCCOOLINGTOWER"), _T("Cooling Tower"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCCOVERING"), _T("Covering"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCCURTAINWALL"), _T("Curtain Wall"), status, totalObjects);

				//	inherits from IfcFlowController
				RetrieveObjects(ifcModel, file, _T("IFCDAMPER"), _T("Damper"), status, totalObjects);

				//	inherits from IfcElementComponent
				RetrieveObjects(ifcModel, file, _T("IFCDISCRETEACCESSORY"), _T("Discrete Accessory"), status, totalObjects);

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCDISTRIBUTIONCHAMBERELEMENT"), _T("Distribution Chamber Element"), status, totalObjects);

				//	inherits from IfcDistributionElement
				RetrieveObjects(ifcModel, file, _T("IFCDISTRIBUTIONCONTROLELEMENT"), _T("Distribution Control Element"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCDISTRIBUTIONELEMENT"), _T("Distribution Element"), status, totalObjects);

				//	inherits from IfcDistributionElement
				RetrieveObjects(ifcModel, file, _T("IFCDISTRIBUTIONFLOWELEMENT"), _T("Distribution Flow Element"), status, totalObjects);

				//	inherits from IfcPort
				RetrieveObjects(ifcModel, file, _T("IFCDISTRIBUTIONPORT"), _T("Distribution Port"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCDOOR"), _T("Door"), status, totalObjects);

				//	inherits from IfcDoor
				RetrieveObjects(ifcModel, file, _T("IFCDOORSTANDARDCASE"), _T("Door Standard Case"), status, totalObjects);

				//	inherits from IfcFlowFitting
				RetrieveObjects(ifcModel, file, _T("IFCDUCTFITTING"), _T("Duct Fitting"), status, totalObjects);

				//	inherits from IfcFlowSegment
				RetrieveObjects(ifcModel, file, _T("IFCDUCTSEGMENT"), _T("Duct Segment"), status, totalObjects);

				//	inherits from IfcFlowTreatmentDevice
				RetrieveObjects(ifcModel, file, _T("IFCDUCTSILENCER"), _T("Duct Silencer"), status, totalObjects);

				//	inherits from IfcFlowTerminal
				RetrieveObjects(ifcModel, file, _T("IFCELECTRICAPPLIANCE"), _T("Electric Appliance"), status, totalObjects);

				//	inherits from IfcFlowController
				RetrieveObjects(ifcModel, file, _T("IFCELECTRICDISTRIBUTIONBOARD"), _T("Electric Distribution Board"), status, totalObjects);

				//	inherits from IfcFlowStorageDevice
				RetrieveObjects(ifcModel, file, _T("IFCELECTRICFLOWSTORAGEDEVICE"), _T("Electric Flow Storage Device"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCELECTRICGENERATOR"), _T("Electric Generator"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCELECTRICMOTOR"), _T("Electric Motor"), status, totalObjects);

				//	inherits from IfcFlowController
				RetrieveObjects(ifcModel, file, _T("IFCELECTRICTIMECONTROL"), _T("Electric Time Control"), status, totalObjects);

				//	inherits from IfcProduct
				RetrieveObjects(ifcModel, file, _T("IFCELEMENT"), _T("Element"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCELEMENTASSEMBLY"), _T("Element Assembly"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCELEMENTCOMPONENT"), _T("Element Component"), status, totalObjects);

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCENERGYCONVERSIONDEVICE"), _T("Energy Conversion Device"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCENGINE"), _T("Engine"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCEVAPORATIVECOOLER"), _T("Evaporative Cooler"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCEVAPORATOR"), _T("Evaporator"), status, totalObjects);

				//	inherits from IfcExternalSpatialStructureElement
				RetrieveObjects(ifcModel, file, _T("IFCEXTERNALSPATIALELEMENT"), _T("External Spatial Element"), status, totalObjects);

				//	inherits from IfcSpatialElement
				RetrieveObjects(ifcModel, file, _T("IFCEXTERNALSPATIALSTRUCTUREELEMENT"), _T("External Spatial Structure Element"), status, totalObjects);

				//	inherits from IfcFlowMovingDevice
				RetrieveObjects(ifcModel, file, _T("IFCFAN"), _T("Fan"), status, totalObjects);

				//	inherits from IfcElementComponent
				RetrieveObjects(ifcModel, file, _T("IFCFASTENER"), _T("Fastener"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCFEATUREELEMENT"), _T("Feature Element"), status, totalObjects);

				//	inherits from IfcFeatureElement
				RetrieveObjects(ifcModel, file, _T("IFCFEATUREELEMENTADDITION"), _T("Feature Element Addition"), status, totalObjects);

				//	inherits from IfcFeatureElement
				RetrieveObjects(ifcModel, file, _T("IFCFEATUREELEMENTSUBTRACTION"), _T("Feature Element Subtraction"), status, totalObjects);

				//	inherits from IfcFlowTreatmentDevice
				RetrieveObjects(ifcModel, file, _T("IFCFILTER"), _T("Filter"), status, totalObjects);

				//	inherits from IfcFlowTerminal
				RetrieveObjects(ifcModel, file, _T("IFCFIRESUPPRESSIONTERMINAL"), _T("Fire Suppression Terminal"), status, totalObjects);

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCFLOWCONTROLLER"), _T("Flow Controller"), status, totalObjects);

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCFLOWFITTING"), _T("Flow Fitting"), status, totalObjects);

				//	inherits from IfcDistributionControlElement
				RetrieveObjects(ifcModel, file, _T("IFCFLOWINSTRUMENT"), _T("Flow Instrument"), status, totalObjects);

				//	inherits from IfcFlowController
				RetrieveObjects(ifcModel, file, _T("IFCFLOWMETER"), _T("Flow Meter"), status, totalObjects);

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCFLOWMOVINGDEVICE"), _T("Flow Moving Device"), status, totalObjects);

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCFLOWSEGMENT"), _T("Flow Segment"), status, totalObjects);

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCFLOWSTORAGEDEVICE"), _T("Flow Storage Device"), status, totalObjects);

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCFLOWTERMINAL"), _T("Flow Terminal"), status, totalObjects);

				//	inherits from IfcDistributionFlowElement
				RetrieveObjects(ifcModel, file, _T("IFCFLOWTREATMENTDEVICE"), _T("Flow Treatment Device"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCFOOTING"), _T("Footing"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCFURNISHINGELEMENT"), _T("Furnishing Element"), status, totalObjects);

				//	inherits from IfcFurnishingElement
				RetrieveObjects(ifcModel, file, _T("IFCFURNITURE"), _T("Furniture"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCGEOGRAPHICELEMENT"), _T("Geographic Element"), status, totalObjects);

				//	inherits from IfcProduct
				RetrieveObjects(ifcModel, file, _T("IFCGRID"), _T("Grid"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCHEATEXCHANGER"), _T("Heat Exchanger"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCHUMIDIFIER"), _T("Humidifier"), status, totalObjects);

				//	inherits from IfcFlowTreatmentDevice
				RetrieveObjects(ifcModel, file, _T("IFCINTERCEPTOR"), _T("Interceptor"), status, totalObjects);

				//	inherits from IfcFlowFitting
				RetrieveObjects(ifcModel, file, _T("IFCJUNCTIONBOX"), _T("Junction Box"), status, totalObjects);

				//	inherits from IfcFlowTerminal
				RetrieveObjects(ifcModel, file, _T("IFCLAMP"), _T("Lamp"), status, totalObjects);

				//	inherits from IfcFlowTerminal
				RetrieveObjects(ifcModel, file, _T("IFCLIGHTFIXTURE"), _T("Light Fixture"), status, totalObjects);

				//	inherits from IfcElementComponent
				RetrieveObjects(ifcModel, file, _T("IFCMECHANICALFASTENER"), _T("Mechanical Fastener"), status, totalObjects);

				//	inherits from IfcFlowTerminal
				RetrieveObjects(ifcModel, file, _T("IFCMEDICALDEVICE"), _T("Medical Device"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCMEMBER"), _T("Member"), status, totalObjects);

				//	inherits from IfcMember
				RetrieveObjects(ifcModel, file, _T("IFCMEMBERSTANDARDCASE"), _T("Member Standard Case"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCMOTORCONNECTION"), _T("Motor Connection"), status, totalObjects);

				//	inherits from IfcFeatureElementSubtraction
				RetrieveObjects(ifcModel, file, _T("IFCOPENINGELEMENT"), _T("Opening Element"), status, totalObjects);

				//	inherits from IfcOpeningElement
				RetrieveObjects(ifcModel, file, _T("IFCOPENINGSTANDARDCASE"), _T("Opening Standard Case"), status, totalObjects);

				//	inherits from IfcFlowTerminal
				RetrieveObjects(ifcModel, file, _T("IFCOUTLET"), _T("Outlet"), status, totalObjects);

				//	inherits fromIfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCPILE"), _T("Pile"), status, totalObjects);

				//	inherits from IfcFlowFitting
				RetrieveObjects(ifcModel, file, _T("IFCPIPEFITTING"), _T("Pipe Fitting"), status, totalObjects);

				//	inherits from IfcFlowSegment
				RetrieveObjects(ifcModel, file, _T("IFCPIPESEGMENT"), _T("Pipe Segment"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCPLATE"), _T("Plate"), status, totalObjects);

				//	inherits from IfcPlate
				RetrieveObjects(ifcModel, file, _T("IFCPLATESTANDARDCASE"), _T("Plate Standard Case"), status, totalObjects);

				//	inherits from IfcProduct
				RetrieveObjects(ifcModel, file, _T("IFCPORT"), _T("Port"), status, totalObjects);

				//	inherits from IfcObject
				RetrieveObjects(ifcModel, file, _T("IFCPRODUCT"), _T("Product"), status, totalObjects);

				//	inherits from IfcFeatureElementAddition
				RetrieveObjects(ifcModel, file, _T("IFCPROJECTIONELEMENT"), _T("Projection Element"), status, totalObjects);

				//	inherits from IfcFlowController
				RetrieveObjects(ifcModel, file, _T("IFCPROTECTIVEDEVICE"), _T("Protective Device"), status, totalObjects);

				//	inherits from IfcDistributionControlElement
				RetrieveObjects(ifcModel, file, _T("IFCPROTECTIVEDEVICETRIPPINGUNIT"), _T("Protective Device Tripping Unit"), status, totalObjects);

				//	inherits from IfcProduct
				RetrieveObjects(ifcModel, file, _T("IFCPROXY"), _T("Proxy"), status, totalObjects);

				//	inherits from IfcFlowMovingDevice
				RetrieveObjects(ifcModel, file, _T("IFCPUMP"), _T("Pump"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCRAILING"), _T("Railing"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCRAMP"), _T("Ramp"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCRAMPFLIGHT"), _T("Ramp Flight"), status, totalObjects);

				//	inherits from IfcReinforcingElement
				RetrieveObjects(ifcModel, file, _T("IFCREINFORCINGBAR"), _T("Reinforcing Bar"), status, totalObjects);

				//	inherits from IfcElementComponent
				RetrieveObjects(ifcModel, file, _T("IFCREINFORCINGELEMENT"), _T("Reinforcing Element"), status, totalObjects);

				//	inherits from IfcReinforcingElement
				RetrieveObjects(ifcModel, file, _T("IFCREINFORCINGMESH"), _T("Reinforcing Mesh"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCROOF"), _T("Roof"), status, totalObjects);

				//	inherits from IfcFlowTerminal
				RetrieveObjects(ifcModel, file, _T("IFCSANITARYTERMINAL"), _T("Sanitary Terminal"), status, totalObjects);

				//	inherits from IfcDistributionControlElement
				RetrieveObjects(ifcModel, file, _T("IFCSENSOR"), _T("Sensor"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCSHADINGDEVICE"), _T("Shading Device"), status, totalObjects);

				//	inherits from IfcSpatialStructureElement
				RetrieveObjects(ifcModel, file, _T("IFCSITE"), _T("Site"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCSLAB"), _T("Slab"), status, totalObjects);

				//	inherits from IfcSlab
				RetrieveObjects(ifcModel, file, _T("IFCSLABELEMENTEDCASE"), _T("Slab Elemented Case"), status, totalObjects);

				//	inherits from IfcSlab
				RetrieveObjects(ifcModel, file, _T("IFCSLABSTANDARDCASE"), _T("Slab Standard Case"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCSOLARDEVICE"), _T("Solar Device"), status, totalObjects);

				//	inherits from IfcSpatialStructureElement
				RetrieveObjects(ifcModel, file, _T("IFCSPACE"), _T("Space"), status, totalObjects);

				//	inherits from IfcFlowTerminal
				RetrieveObjects(ifcModel, file, _T("IFCSPACEHEATER"), _T("Space Heater"), status, totalObjects);

				//	inherits from IfcProduct
				RetrieveObjects(ifcModel, file, _T("IFCSPATIALELEMENT"), _T("Spatial Element"), status, totalObjects);

				//	inherits from IfcSpatialElement
				RetrieveObjects(ifcModel, file, _T("IFCSPATIALSTRUCTUREELEMENT"), _T("Spatial Structure Element"), status, totalObjects);

				//	inherits from IfcSpatialElement
				RetrieveObjects(ifcModel, file, _T("IFCSPATIALZONE"), _T("Spatial Zone"), status, totalObjects);

				//	inherits from IfcFlowTerminal
				RetrieveObjects(ifcModel, file, _T("IFCSTACKTERMINAL"), _T("Stack Terminal"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCSTAIR"), _T("Stair"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCSTAIRFLIGHT"), _T("Stair Flight"), status, totalObjects);

				//	inherits from IfcStructuralActivity
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALACTION"), _T("Structural Action"), status, totalObjects);

				//	inherits from IfcProduct
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALACTIVITY"), _T("Structural Activity"), status, totalObjects);

				//	inherits from IfcStructuralItem
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALCONNECTION"), _T("Structural Connection"), status, totalObjects);

				//	inherits from IfcStructuralAction
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALCURVEACTION"), _T("Structural Curve Action"), status, totalObjects);

				//	inherits from IfcStructuralConnection
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALCURVECONNECTION"), _T("Structural Curve Connection"), status, totalObjects);

				//	inherits from IfcStructuralMember
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALCURVEMEMBER"), _T("Structural Curve Member"), status, totalObjects);

				//	inherits from IfcStructuralCurveMember
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALCURVEMEMBERVARYING"), _T("Structural Curve Member Varying"), status, totalObjects);

				//	inherits from IfcStructuralReaction
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALCURVEREACTION"), _T("Structural Curve Reaction"), status, totalObjects);

				//	inherits from IfcProduct
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALITEM"), _T("Structural Item"), status, totalObjects);

				//	inherits from IfcStructuralCurveAction
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALLINEARACTION"), _T("Structural Linear Action"), status, totalObjects);

				//	inherits from IfcStructuralItem
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALMEMBER"), _T("Structural Member"), status, totalObjects);

				//	inherits from IfcStructuralSurfaceAction
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALPLANARACTION"), _T("Structural Planar Action"), status, totalObjects);

				//	inherits from IfcStructuralAction
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALPOINTACTION"), _T("Structural Point Action"), status, totalObjects);

				//	inherits from IfcStructuralConnection
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALPOINTCONNECTION"), _T("Structural Point Connection"), status, totalObjects);

				//	inherits from IfcStructuralReaction
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALPOINTREACTION"), _T("Structural Point Reaction"), status, totalObjects);

				//	inherits from IfcStructuralActivity
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALREACTION"), _T("Structural Reaction"), status, totalObjects);

				//	inherits from IfcStructuralAction
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALSURFACEACTION"), _T("Structural Surface Action"), status, totalObjects);

				//	inherits from IfcStructuralConnection
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALSURFACECONNECTION"), _T("Structural Surface Connection"), status, totalObjects);

				//	inherits from IfcStructuralMember
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALSURFACEMEMBER"), _T("Structural Surface Member"), status, totalObjects);

				//	inherits from IfcStructuralSurfaceMember
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALSURFACEMEMBERVARYING"), _T("Structural Surface Member Varying"), status, totalObjects);

				//	inherits from IfcStructuralReaction
				RetrieveObjects(ifcModel, file, _T("IFCSTRUCTURALSURFACEREACTION"), _T("Structural Surface Reaction"), status, totalObjects);

				//	inherits from IfcFeatureElement
				RetrieveObjects(ifcModel, file, _T("IFCSURFACEFEATURE"), _T("Surface Feature"), status, totalObjects);

				//	inherits from IfcFlowController
				RetrieveObjects(ifcModel, file, _T("IFCSWITCHINGDEVICE"), _T("Switching Device"), status, totalObjects);

				//	inherits from IfcFurnishingElement
				RetrieveObjects(ifcModel, file, _T("IFCSYSTEMFURNITUREELEMENT"), _T("System Furniture Element"), status, totalObjects);

				//	inherits from IfcFlowStorageDevice
				RetrieveObjects(ifcModel, file, _T("IFCTANK"), _T("Tank"), status, totalObjects);

				//	inherits from IfcReinforcingElement
				RetrieveObjects(ifcModel, file, _T("IFCTENDON"), _T("Tendon"), status, totalObjects);

				//	inherits from IfcReinforcingElement
				RetrieveObjects(ifcModel, file, _T("IFCTENDONANCHOR"), _T("Tendon Anchor"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCTRANSFORMER"), _T("Transformer"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCTRANSPORTELEMENT"), _T("Transport Element"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCTUBEBUNDLE"), _T("Tube Bundle"), status, totalObjects);

				//	inherits from IfcDistributionControlElement
				RetrieveObjects(ifcModel, file, _T("IFCUNITARYCONTROLELEMENT"), _T("Unitary Control Element"), status, totalObjects);

				//	inherits from IfcEnergyConversionDevice
				RetrieveObjects(ifcModel, file, _T("IFCUNITARYEQUIPMENT"), _T("Unitary Equipment"), status, totalObjects);

				//	inherits from IfcFlowController
				RetrieveObjects(ifcModel, file, _T("IFCVALVE"), _T("Valve"), status, totalObjects);

				//	inherits from IfcElementComponent
				RetrieveObjects(ifcModel, file, _T("IFCVIBRATIONISOLATOR"), _T("Vibration Isolator"), status, totalObjects);

				//	inherits from IfcElement
				RetrieveObjects(ifcModel, file, _T("IFCVIRTUALELEMENT"), _T("Virtual Element"), status, totalObjects);

				//	inherits from IfcFeatureElementSubtraction
				RetrieveObjects(ifcModel, file, _T("IFCVOIDINGFEATURE"), _T("Voiding Feature"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCWALL"), _T("Wall"), status, totalObjects);

				//	inherits from IfcWall
				RetrieveObjects(ifcModel, file, _T("IFCWALLELEMENTEDCASE"), _T("Wall Elemented Case"), status, totalObjects);

				//	inherits from IfcWall
				RetrieveObjects(ifcModel, file, _T("IFCWALLSTANDARDCASE"), _T("Wall Standard Case"), status, totalObjects);

				//	inherits from IfcFlowTerminal
				RetrieveObjects(ifcModel, file, _T("IFCWASTETERMINAL"), _T("Waste Terminal"), status, totalObjects);

				//	inherits from IfcBuildingElement
				RetrieveObjects(ifcModel, file, _T("IFCWINDOW"), _T("Window"), status, totalObjects);

				//	inherits from IfcWindow
				RetrieveObjects(ifcModel, file, _T("IFCWINDOWSTANDARDCASE"), _T("Window Standard Case"), status, totalObjects);
			}

			fprintf(file, "\t</objects>\n");
			fprintf(file, "\t<geometry>\n");

			ReadObjectVisualization(file, status, totalTriangles);

			fprintf(file, "\t</geometry>\n");
			fprintf(file, "</results>\n");
			fclose(file);
		} else {
			_itoa_s((__int32) --totalNoFiles, buffer, 512, 10);
			totalFiles->SetWindowText(buffer);

			return	-1;
		}
	}

	return	0;
}

double  Abs(double value)
{
	if  (value < 0) {
		return  -value;
	} else {
		return  value;
	}
}

void	ReadObjectVisualization(FILE * file, CStatic * status, CStatic * totalTriangles)
{
	int			cnt = 0;
	char		buffer[512];
	CString		info;

	STRUCT_INSTANCES	* instance;

	__int64	owlModel = 0;
	owlGetModel(ifcModel, &owlModel);

	int	setting = 0, mask = 0;
	mask += (int) flagbit2;			//    PRECISION (32/64 bit)
	mask += (int) flagbit3;			//	  INDEX ARRAY (32/64 bit)
	mask += (int) flagbit5;			//    NORMALS
	mask += (int) flagbit8;			//    TRIANGLES
	mask += (int) flagbit12;		//    WIREFRAME


	setting = 0;
	setting += (int) flagbit2;		//    DOUBLE PRECISION (double)
#ifndef	WIN64
	setting += 0;			        //    32 BIT INDEX ARRAY (Int32)
#else
	setting += (int) flagbit3;		//    64 BIT INDEX ARRAY (Int64)
#endif
	setting += 0;					//    NORMALS OFF
	setting += (int) flagbit8;		//    TRIANGLES ON
	setting += 0;					//    WIREFRAME OFF
	SetFormat(owlModel, setting, mask);

    instance = first_instance;
	while  (instance) {
        info = "Model read correctly\n";
        _itoa_s((__int32) glCnt, buffer, 512, 10);
		info += buffer;
        info += " IFC objects found\n";
        info += "Generating geometry of IFC object '";
        info += instance->globalId;
        info += "'\n";
        _itoa_s((__int32) ++cnt, buffer, 512, 10);
		info += buffer;
        info += " of ";
        _itoa_s((__int32) glCnt, buffer, 512, 10);
		info += buffer;
        status->SetWindowText(info);

		MATRIX	transformationMatrix;
		VECTOR3	minVector, maxVector;//, vector;

		//clock_t	before = clock();
//		struct timeval te; 
//		gettimeofday(&te, NULL); // get current time
//		long long millisecondsBefore = te.tv_sec*1000LL + te.tv_usec/1000;

		__int64	owlInstance = 0, owlModel = 0;
		double	* vertexBuffer = 0;
		int		vertexBufferSize = 0, indexBufferSize = 0, * indexBuffer = 0;
        if  (instance->id  &&  instance->globalId) {
			MatrixIdentity(&transformationMatrix);
			Vector3Identity(&minVector);
			Vector3Identity(&maxVector);

double	_11 = 0, _12 = 0, _13 = 0, _14 = 0,
		_21 = 0, _22 = 0, _23 = 0, _24 = 0,
		_31 = 0, _32 = 0, _33 = 0, _34 = 0,
		_41 = 0, _42 = 0, _43 = 0, _44 = 0;

getInstanceDerivedTransformationMatrix(ifcModel, instance->id,
							&_11, &_12, &_13, &_14,
							&_21, &_22, &_23, &_24,
							&_31, &_32, &_33, &_34,
							&_41, &_42, &_43, &_44);

		    initializeModellingInstance(ifcModel, &vertexBufferSize, &indexBufferSize, 0, instance->id);

			if	(vertexBufferSize  &&  indexBufferSize) {
				vertexBuffer = new double[3 * vertexBufferSize];
				indexBuffer = new int[indexBufferSize];
				finalizeModelling(ifcModel, (float *) vertexBuffer, (int *) indexBuffer, 0);

				owlGetModel(ifcModel, &owlModel);
				owlGetInstance(ifcModel, instance->id, &owlInstance);
			}
		}

        if  (owlInstance) {
            fprintf(file, "\t\t<instance>\n");
            fprintf(file, "\t\t\t<globalid>%s</globalid>\n", instance->globalId);
            fprintf(file, "\t\t\t<entity>%s</entity>\n", instance->entityName);

			SetBoundingBoxReference(owlInstance, &transformationMatrix, &minVector, &maxVector);

			double	centroid[3],
					volume = GetCentroid(owlInstance, (int64_t *) vertexBuffer, (int64_t *) indexBuffer, centroid),
//					volume = GetVolume(owlInstance, (int64_t *) vertexBuffer, (int64_t *) indexBuffer),
					area = GetArea(owlInstance, (int64_t *) vertexBuffer, (int64_t *) indexBuffer),
					perimeter = GetPerimeter(owlInstance);

            fprintf(file, "\t\t\t<volume>%f</volume>\n", volume);
            fprintf(file, "\t\t\t<area>%f</area>\n", area);
            fprintf(file, "\t\t\t<perimeter>%f</perimeter>\n", perimeter);

			fprintf(file, "\t\t\t<centroid>\n");
            fprintf(file, "\t\t\t\t<x>%f</x>\n", centroid[0]);
            fprintf(file, "\t\t\t\t<y>%f</y>\n", centroid[1]);
            fprintf(file, "\t\t\t\t<z>%f</z>\n", centroid[2]);
            fprintf(file, "\t\t\t</centroid>\n");
            
			fprintf(file, "\t\t\t<boundingBox>\n");
            fprintf(file, "\t\t\t\t<minVector>\n");
            fprintf(file, "\t\t\t\t\t<x>%f</x>\n", minVector.x);
            fprintf(file, "\t\t\t\t\t<y>%f</y>\n", minVector.y);
            fprintf(file, "\t\t\t\t\t<z>%f</z>\n", minVector.z);
			fprintf(file, "\t\t\t\t</minVector>\n");
            fprintf(file, "\t\t\t\t<maxVector>\n");
            fprintf(file, "\t\t\t\t\t<x>%f</x>\n", maxVector.x);
            fprintf(file, "\t\t\t\t\t<y>%f</y>\n", maxVector.y);
            fprintf(file, "\t\t\t\t\t<z>%f</z>\n", maxVector.z);
			fprintf(file, "\t\t\t\t</maxVector>\n");
            fprintf(file, "\t\t\t\t<transformationMatrix>\n");
            fprintf(file, "\t\t\t\t\t<_11>%f</_11>\n", transformationMatrix._11);
			fprintf(file, "\t\t\t\t\t<_12>%f</_12>\n", transformationMatrix._12);
            fprintf(file, "\t\t\t\t\t<_13>%f</_13>\n", transformationMatrix._13);
            fprintf(file, "\t\t\t\t\t<_21>%f</_21>\n", transformationMatrix._21);
			fprintf(file, "\t\t\t\t\t<_22>%f</_22>\n", transformationMatrix._22);
            fprintf(file, "\t\t\t\t\t<_23>%f</_23>\n", transformationMatrix._23);
            fprintf(file, "\t\t\t\t\t<_31>%f</_31>\n", transformationMatrix._31);
			fprintf(file, "\t\t\t\t\t<_32>%f</_32>\n", transformationMatrix._32);
            fprintf(file, "\t\t\t\t\t<_33>%f</_33>\n", transformationMatrix._33);
            fprintf(file, "\t\t\t\t\t<_41>%f</_41>\n", transformationMatrix._41);
			fprintf(file, "\t\t\t\t\t<_42>%f</_42>\n", transformationMatrix._42);
            fprintf(file, "\t\t\t\t\t<_43>%f</_43>\n", transformationMatrix._43);
			fprintf(file, "\t\t\t\t</transformationMatrix>\n");
            fprintf(file, "\t\t\t</boundingBox>\n");

            fprintf(file, "\t\t</instance>\n");

			if	(vertexBuffer) {
				delete[] vertexBuffer;
				vertexBuffer = 0;
			}
			if	(indexBuffer) {
				delete[] indexBuffer;
				indexBuffer = 0;
			}

//#ifndef	WIN64
			cleanMemory(ifcModel, 0);
//#endif
		}

		//
		//	Check time
		//
//		clock_t	after = clock();
//		struct timeval te; 
//		gettimeofday(&te, NULL); // get current time
//		long long millisecondsAfter = te.tv_sec*1000LL + te.tv_usec/1000;
//			double	seconds = difftime(before,time(0));
//			int		milliSeconds = (int) (1000 * seconds);

		int u = 0;

		instance = instance->next;
	}
}

#undef int 
