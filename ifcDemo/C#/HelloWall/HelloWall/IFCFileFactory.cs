using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
#if WIN64
using IfcHandle = System.Int64;
#else
using IfcHandle = System.Int32;
#endif

namespace HelloWall
{
    /// <summary>
    /// Representation
    /// </summary>
    public enum IfcRepresentation
    {
        AXIS_CURVE2D_REPRESENTATION = 101,
        BODY_BOUNDINGBOX_REPRESENTATION = 111,
        BODY_BREP_REPRESENTATION = 112,
        BODY_SWEPTSOLID_REPRESENTATION = 113,
        BODY_TESSELLATION_REPRESENTATION = 114,
    }

    /// <summary>
    /// Helper for creating of .ifc/.ifx file
    /// </summary>
    public class IfcFileFactory : IDisposable
    {
        #region Members

        #endregion // Members

        /// <summary>
        /// ctor
        /// </summary>
        public IfcFileFactory(string strSchemaFile)
        {
            if (string.IsNullOrEmpty(strSchemaFile))
            {
                throw new ArgumentNullException("Schema file empty.");
            }

            this.ModelInstance = IfcEngine.sdaiCreateModelBNUnicode(1, null, Encoding.Unicode.GetBytes(strSchemaFile));
            if (this.ModelInstance == 0)
            {
                throw new Exception("Can't create a model.");
            }
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcHandle ModelInstance
        {
            get;
            private set;
        }

        /// <summary>
        /// Time stamp (IFC format)
        /// </summary>
        public string CreateTimeStamp()
        {
            string strTimeStamp = DateTime.Now.Year.ToString();
            strTimeStamp += "-";
            strTimeStamp += DateTime.Now.Month.ToString("D2");
            strTimeStamp += "-";
            strTimeStamp += DateTime.Now.Day.ToString("D2");
            strTimeStamp += "T";
            strTimeStamp += DateTime.Now.Hour.ToString("D2");
            strTimeStamp += ":";
            strTimeStamp += DateTime.Now.Minute.ToString("D2");
            strTimeStamp += ":";
            strTimeStamp += DateTime.Now.Second.ToString("D2");

            return strTimeStamp;
        }

        /// <summary>
        /// Creates an instance
        /// </summary>
        /// <returns></returns>
        public IfcHandle CreateInstance(string strInstance)
        {
            IfcHandle ifcInstance = IfcEngine.sdaiCreateInstanceBN(this.ModelInstance, strInstance);
            if (ifcInstance == 0)
            {
                System.Console.Out.WriteLine(string.Format("Can't create an instance of {0}.", strInstance));
            }

            return ifcInstance;
        }
        
        /// <summary>
        /// Creates/inits an instance
        /// </summary>
        /// <returns></returns>
        public IfcHandle CreateInstance(string strInstance, Action<IfcHandle> Init)
        {
            IfcHandle ifcInstance = IfcEngine.sdaiCreateInstanceBN(this.ModelInstance, strInstance);
            if (ifcInstance == 0)
            {
                throw new Exception(string.Format("Can't create an instance of {0}.", strInstance));
            }

            Init(ifcInstance);

            return ifcInstance;
        }

        /// <summary>
        /// Stores model
        /// </summary>
        public void SaveAsIFC(string strFileName)
        {
            if (this.ModelInstance == 0)
            {
                throw new Exception("Model is not initialized.");
            }

            IfcEngine.sdaiSaveModelBNUnicode(this.ModelInstance, Encoding.Unicode.GetBytes(strFileName));
        }

        /// <summary>
        /// Stores model
        /// </summary>
        public void SaveAsIFCX(string strFileName)
        {
            if (this.ModelInstance == 0)
            {
                throw new Exception("Model is not initialized.");
            }

            string strOutputFileName = strFileName;
            if (Path.GetExtension(strOutputFileName) != ".ifx")
            {
                strOutputFileName += ".ifx";
            }

            IfcEngine.sdaiSaveModelAsXmlBNUnicode(this.ModelInstance, Encoding.Unicode.GetBytes(strOutputFileName));
        }

        /// <summary>
        /// Creates IFCPERSON
        /// </summary>
        public IfcHandle CreatePersonInstance(string strName, string strDescription)
        {
            IfcHandle ifcPersonnInstance = CreateInstance("IFCPERSON", (instance) =>
            {
                IfcEngine.sdaiPutAttrBN(instance, "GivenName", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strName));
                IfcEngine.sdaiPutAttrBN(instance, "FamilyName", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strDescription));
            });

            return ifcPersonnInstance;
        }

        /// <summary>
        /// Creates IFCORGANIZATION
        /// </summary>
        public IfcHandle CreateOrganizationInstance(string strName, string strDescription)
        {
            IfcHandle ifcOrganizationInstance = CreateInstance("IFCORGANIZATION", (instance) =>
            {
                IfcEngine.sdaiPutAttrBN(instance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strName));
                IfcEngine.sdaiPutAttrBN(instance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strDescription));
            });

            return ifcOrganizationInstance;
        }

        /// <summary>
        /// Creates IFCPERSONANDORGANIZATION
        /// </summary>
        public IfcHandle CreatePersonAndOrganizationInstance(IfcHandle ifcPersonInstance, IfcHandle ifcOrganizationInstance)
        {
            IfcHandle ifcPersonAndOrganizationInstance = CreateInstance("IFCPERSONANDORGANIZATION", (instance) =>
            {
                IfcEngine.sdaiPutAttrBN(instance, "ThePerson", IfcEngine.sdaiINSTANCE, ifcPersonInstance);
                IfcEngine.sdaiPutAttrBN(instance, "TheOrganization", IfcEngine.sdaiINSTANCE, ifcOrganizationInstance);
            });

            return ifcPersonAndOrganizationInstance;
        }

        /// <summary>
        /// Creates IFCOWNERHISTORY
        /// </summary>
        public IfcHandle CreateOwnerHistory(IfcHandle ifcPersonAndOrganizationInstance, IfcHandle ifcApplicationInstance)
        {
            IfcHandle ifcOwnerHistoryInstance = CreateInstance("IFCOWNERHISTORY", (instance) =>
            {
                IfcEngine.sdaiPutAttrBN(instance, "OwningUser", IfcEngine.sdaiINSTANCE, ifcPersonAndOrganizationInstance);
                IfcEngine.sdaiPutAttrBN(instance, "OwningApplication", IfcEngine.sdaiINSTANCE, ifcApplicationInstance);
                IfcEngine.sdaiPutAttrBN(instance, "ChangeAction", IfcEngine.sdaiENUM, "ADDED");

                IfcHandle ifcTimeStamp = IfcEngine.getTimeStamp(this.ModelInstance);
                IfcEngine.sdaiPutAttrBN(instance, "CreationDate", IfcEngine.sdaiINTEGER, ref ifcTimeStamp);
            });

            return ifcOwnerHistoryInstance;
        }

        /// <summary>
        /// Creates IFCAXIS2PLACEMENT3D
        /// </summary>
        public IfcHandle CreateAxis2Placement3DInstance(POINT3D point)
        {
            IfcHandle ifcAxis2Placement3DInstance = CreateInstance("IFCAXIS2PLACEMENT3D", (instance) =>
            {
                IfcHandle ifcCartesianPointInstance = CreateCartesianPointInstance(point);
                IfcEngine.sdaiPutAttrBN(instance, "Location", IfcEngine.sdaiINSTANCE, ifcCartesianPointInstance);
            });

            return ifcAxis2Placement3DInstance;
        }

        /// <summary>
        /// Creates IFCSIUNIT
        /// </summary>
        public IfcHandle CreateSIUnitInstance(string strUnitType, string strPrefix, string strName, IfcHandle ifcDimensions)
        {
            IfcHandle ifcSIUnitInstance = CreateInstance("IFCSIUNIT");

            IfcEngine.sdaiPutAttrBN(ifcSIUnitInstance, "UnitType", IfcEngine.sdaiENUM, strUnitType);            

            if (!string.IsNullOrEmpty(strPrefix))
            {
                IfcEngine.sdaiPutAttrBN(ifcSIUnitInstance, "Prefix", IfcEngine.sdaiENUM, strPrefix);
            }

            IfcEngine.sdaiPutAttrBN(ifcSIUnitInstance, "Name", IfcEngine.sdaiENUM, strName);            
            IfcEngine.sdaiPutAttrBN(ifcSIUnitInstance, "Dimensions", IfcEngine.sdaiINTEGER, ifcDimensions);

            return ifcSIUnitInstance;
        }

        /// <summary>
        /// Creates IFCAXIS2PLACEMENT3D
        /// </summary>
        public IfcHandle CreateAxis2Placement3DInstance(MATRIX matrix)
        {
            IfcHandle ifcAxis2Placement3DInstance = CreateInstance("IFCAXIS2PLACEMENT3D");

            IfcEngine.sdaiPutAttrBN(ifcAxis2Placement3DInstance, "Location", IfcEngine.sdaiINSTANCE, CreateCartesianPointInstance(matrix._d41, matrix._d42, matrix._d43));
            IfcEngine.sdaiPutAttrBN(ifcAxis2Placement3DInstance, "Axis", IfcEngine.sdaiINSTANCE, CreateDirectionInstance(matrix._d31, matrix._d32, matrix._d33));
            IfcEngine.sdaiPutAttrBN(ifcAxis2Placement3DInstance, "RefDirection", IfcEngine.sdaiINSTANCE, CreateDirectionInstance(matrix._d11, matrix._d12, matrix._d13));

            return ifcAxis2Placement3DInstance;
        }

        /// <summary>
        /// Creates IFCCARTESIANPOINT
        /// </summary>
        public IfcHandle CreateCartesianPointInstance(double dX, double dY)
        {
            IfcHandle ifcCartesianPointInstance = CreateInstance("IFCCARTESIANPOINT");

            IfcHandle ifcCoordinates = IfcEngine.sdaiCreateAggrBN(ifcCartesianPointInstance, "Coordinates");

            IfcEngine.sdaiAppend(ifcCoordinates, IfcEngine.sdaiREAL, ref dX);
            IfcEngine.sdaiAppend(ifcCoordinates, IfcEngine.sdaiREAL, ref dY);

            return ifcCartesianPointInstance;
        }

        /// <summary>
        /// Creates IFCCARTESIANPOINT
        /// </summary>
        public IfcHandle CreateCartesianPointInstance(double dX, double dY, double dZ)
        {
            IfcHandle ifcCartesianPointInstance = CreateInstance("IFCCARTESIANPOINT");

            IfcHandle ifcCoordinates = IfcEngine.sdaiCreateAggrBN(ifcCartesianPointInstance, "Coordinates");

            IfcEngine.sdaiAppend(ifcCoordinates, IfcEngine.sdaiREAL, ref dX);
            IfcEngine.sdaiAppend(ifcCoordinates, IfcEngine.sdaiREAL, ref dY);
            IfcEngine.sdaiAppend(ifcCoordinates, IfcEngine.sdaiREAL, ref dZ);

            return ifcCartesianPointInstance;
        }

        /// <summary>
        /// Creates IFCCARTESIANPOINT
        /// </summary>
        public IfcHandle CreateCartesianPointInstance(POINT3D point)
        {
            return CreateCartesianPointInstance(point.X, point.Y, point.Z);
        }

        /// <summary>
        /// Creates IFCDIRECTION
        /// </summary>
        public IfcHandle CreateDirectionInstance(double dX, double dY, double dZ)
        {
            IfcHandle ifcDirectionInstance = CreateInstance("IFCDIRECTION");

            IfcHandle ifcDirectionRatios = IfcEngine.sdaiCreateAggrBN(ifcDirectionInstance, "DirectionRatios");

            IfcEngine.sdaiAppend(ifcDirectionRatios, IfcEngine.sdaiREAL, ref dX);
            IfcEngine.sdaiAppend(ifcDirectionRatios, IfcEngine.sdaiREAL, ref dY);
            IfcEngine.sdaiAppend(ifcDirectionRatios, IfcEngine.sdaiREAL, ref dZ);

            return ifcDirectionInstance;
        }

        /// <summary>
        /// Creates IFCDIRECTION
        /// </summary>
        public IfcHandle CreateDirectionInstance(POINT3D point)
        {
            return CreateDirectionInstance(point.X, point.Y, point.Z);
        }

        /// <summary>
        /// Creates IFCLOCALPLACEMENT
        /// </summary>
        public IfcHandle CreateLocalPlacementInstance(MATRIX matrix, IfcHandle iPlacementRelativeTo)
        {
            IfcHandle ifcLocalPlacementInstance = CreateInstance("IFCLOCALPLACEMENT");

            IfcEngine.sdaiPutAttrBN(ifcLocalPlacementInstance, "PlacementRelTo", IfcEngine.sdaiINSTANCE, iPlacementRelativeTo);
            IfcEngine.sdaiPutAttrBN(ifcLocalPlacementInstance, "RelativePlacement", IfcEngine.sdaiINSTANCE, CreateAxis2Placement3DInstance(matrix));

            return ifcLocalPlacementInstance;
        }

        /// <summary>
        /// Creates IFCPROPERTYSET
        /// </summary>
        public IfcHandle CreatePropertySetInstance(string strName, IfcHandle ifcOwnerHistoryInstance, ref IfcHandle ifcAggrHasProperties)
        {
            IfcHandle ifcPropertySetInstance = CreateInstance("IFCPROPERTYSET");

            IfcEngine.sdaiPutAttrBN(ifcPropertySetInstance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
            IfcEngine.sdaiPutAttrBN(ifcPropertySetInstance, "OwnerHistory", IfcEngine.sdaiINSTANCE, ifcOwnerHistoryInstance);
            IfcEngine.sdaiPutAttrBN(ifcPropertySetInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strName));

            ifcAggrHasProperties = IfcEngine.sdaiCreateAggrBN(ifcPropertySetInstance, "HasProperties");

            return ifcPropertySetInstance;
        }

        /// <summary>
        /// Creates IFCPROPERTYSINGLEVALUE
        /// </summary>
        public IfcHandle CreatePropertySingleValueInstance(string strName, string strDescription, bool bNominalValue, string strTypePath)
        {
            IfcHandle ifcPropertySingleValueInstance = CreateInstance("IFCPROPERTYSINGLEVALUE");

            IfcEngine.sdaiPutAttrBN(ifcPropertySingleValueInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strName));
            IfcEngine.sdaiPutAttrBN(ifcPropertySingleValueInstance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strDescription));

            IfcHandle ifcNominalValueADB = IfcEngine.sdaiCreateADB(IfcEngine.sdaiENUM, bNominalValue ? IfcEngine.TRUE : IfcEngine.FALSE);
            IfcEngine.sdaiPutADBTypePath(ifcNominalValueADB, 1, strTypePath);
            IfcEngine.sdaiPutAttrBN(ifcPropertySingleValueInstance, "NominalValue", IfcEngine.sdaiADB, ifcNominalValueADB);

            return ifcPropertySingleValueInstance;
        }

        /// <summary>
        /// Creates IFCPROPERTYSINGLEVALUE
        /// </summary>
        public IfcHandle CreatePropertySingleValueInstance(string strName, string strDescription, bool bNominalValue)
        {
            return CreatePropertySingleValueInstance(strName, strDescription, bNominalValue, "IFCBOOLEAN");
        }

        /// <summary>
        /// Creates IFCPROPERTYSINGLEVALUE
        /// </summary>
        public IfcHandle CreatePropertySingleValueInstance(string strName, string strDescription, string strNominalValue, string strTypePath)
        {
            IfcHandle ifcPropertySingleValueInstance = CreateInstance("IFCPROPERTYSINGLEVALUE");

            IfcEngine.sdaiPutAttrBN(ifcPropertySingleValueInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strName));
            IfcEngine.sdaiPutAttrBN(ifcPropertySingleValueInstance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strDescription));

            IfcHandle ifcNominalValueADB = IfcEngine.sdaiCreateADB(IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strNominalValue));
            IfcEngine.sdaiPutADBTypePath(ifcNominalValueADB, 1, strTypePath);
            IfcEngine.sdaiPutAttrBN(ifcPropertySingleValueInstance, "NominalValue", IfcEngine.sdaiADB, ifcNominalValueADB);

            return ifcPropertySingleValueInstance;
        }

        /// <summary>
        /// Creates IFCPROPERTYSINGLEVALUE
        /// </summary>
        public IfcHandle CreatePropertySingleValueInstance(string strName, string strDescription, double dNominalValue, string strTypePath)
        {
            IfcHandle ifcPropertySingleValueInstance = CreateInstance("IFCPROPERTYSINGLEVALUE");

            IfcEngine.sdaiPutAttrBN(ifcPropertySingleValueInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strName));
            IfcEngine.sdaiPutAttrBN(ifcPropertySingleValueInstance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strDescription));

            IfcHandle ifcNominalValueADB = IfcEngine.sdaiCreateADB(IfcEngine.sdaiREAL, ref dNominalValue);
            IfcEngine.sdaiPutADBTypePath(ifcNominalValueADB, 1, strTypePath);
            IfcEngine.sdaiPutAttrBN(ifcPropertySingleValueInstance, "NominalValue", IfcEngine.sdaiADB, ifcNominalValueADB);

            return ifcPropertySingleValueInstance;
        }

        /// <summary>
        /// Creates IFCQUANTITYLENGTH
        /// </summary>
        public IfcHandle CreateQuantityLengthInstance(string strName, string strDescription, double dLength)
        {
            IfcHandle ifcQuantityLengthInstance = CreateInstance("IFCQUANTITYLENGTH");

            IfcEngine.sdaiPutAttrBN(ifcQuantityLengthInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strName));
            IfcEngine.sdaiPutAttrBN(ifcQuantityLengthInstance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strDescription));
            IfcEngine.sdaiPutAttrBN(ifcQuantityLengthInstance, "LengthValue", IfcEngine.sdaiREAL, ref dLength);

            return ifcQuantityLengthInstance;
        }

        /// <summary>
        /// Creates IFCQUANTITYAREA
        /// </summary>
        public IfcHandle CreateQuantityAreaInstance(string strName, string strDescription, double dArea)
        {
            IfcHandle ifcQuantityAreaInstance = CreateInstance("IFCQUANTITYAREA");

            IfcEngine.sdaiPutAttrBN(ifcQuantityAreaInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strName));
            IfcEngine.sdaiPutAttrBN(ifcQuantityAreaInstance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strDescription));
            IfcEngine.sdaiPutAttrBN(ifcQuantityAreaInstance, "AreaValue", IfcEngine.sdaiREAL, ref dArea);

            return ifcQuantityAreaInstance;
        }

        /// <summary>
        /// Creates IFCQUANTITYVOLUME
        /// </summary>
        public IfcHandle CreateQuantityVolumeInstance(string strName, string strDescription, double dVolume)
        {
            IfcHandle ifcQuantityVolumeInstance = CreateInstance("IFCQUANTITYVOLUME");

            IfcEngine.sdaiPutAttrBN(ifcQuantityVolumeInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strName));
            IfcEngine.sdaiPutAttrBN(ifcQuantityVolumeInstance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strDescription));
            IfcEngine.sdaiPutAttrBN(ifcQuantityVolumeInstance, "VolumeValue", IfcEngine.sdaiREAL, ref dVolume);

            return ifcQuantityVolumeInstance;
        }

        /// <summary>
        /// Creates IFCMATERIALLAYERSETUSAGE
        /// </summary>
        public IfcHandle CreateMaterialLayerSetUsageInstance(double dThickness)
        {
            IfcHandle ifcMaterialLayerSetUsageInstance = CreateInstance("IFCMATERIALLAYERSETUSAGE");

            IfcEngine.sdaiPutAttrBN(ifcMaterialLayerSetUsageInstance, "ForLayerSet", IfcEngine.sdaiINSTANCE, CreateMaterialLayerSetInstance(dThickness));
            IfcEngine.sdaiPutAttrBN(ifcMaterialLayerSetUsageInstance, "LayerSetDirection", IfcEngine.sdaiENUM, "AXIS2");
            IfcEngine.sdaiPutAttrBN(ifcMaterialLayerSetUsageInstance, "DirectionSense", IfcEngine.sdaiENUM, "POSITIVE");

            double dOffsetFromReferenceLine = -dThickness / 2;
            IfcEngine.sdaiPutAttrBN(ifcMaterialLayerSetUsageInstance, "OffsetFromReferenceLine", IfcEngine.sdaiREAL, ref dOffsetFromReferenceLine);

            return ifcMaterialLayerSetUsageInstance;
        }        

        /// <summary>
        /// Creates IFCMATERIALLAYERSET
        /// </summary>
        public IfcHandle CreateMaterialLayerSetInstance(double dThickness)
        {
            IfcHandle ifcMaterialLayerSetInstance = CreateInstance("IFCMATERIALLAYERSET");

            IfcHandle ifcMaterialLayers = IfcEngine.sdaiCreateAggrBN(ifcMaterialLayerSetInstance, "MaterialLayers");
            IfcEngine.sdaiAppend(ifcMaterialLayers, IfcEngine.sdaiINSTANCE, CreateMaterialLayerInstance(dThickness));

            return ifcMaterialLayerSetInstance;
        }

        /// <summary>
        /// Creates IFCMATERIALLAYER
        /// </summary>
        public IfcHandle CreateMaterialLayerInstance(double dThickness)
        {
            IfcHandle ifcMaterialLayerInstance = CreateInstance("IFCMATERIALLAYER");

            IfcEngine.sdaiPutAttrBN(ifcMaterialLayerInstance, "Material", IfcEngine.sdaiINSTANCE, CreateMaterialInstance("Name of the material used for the wall"));
            IfcEngine.sdaiPutAttrBN(ifcMaterialLayerInstance, "LayerThickness", IfcEngine.sdaiREAL, ref dThickness);

            return ifcMaterialLayerInstance;
        }

        /// <summary>
        /// Creates IFCMATERIAL
        /// </summary>
        public IfcHandle CreateMaterialInstance(string strName)
        {
            IfcHandle ifcMaterialInstance = CreateInstance("IFCMATERIAL");

            IfcEngine.sdaiPutAttrBN(ifcMaterialInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strName));

            return ifcMaterialInstance;
        }

        /// <summary>
        /// Creates IFCGEOMETRICREPRESENTATIONCONTEXT
        /// </summary>
        public IfcHandle CreateGeometricRepresentationContextInstance(IfcHandle ifcWorldCoordinateSystemInstance, IfcHandle ifcCoordinateSpaceDimension, double dPrecision)
        {
            IfcHandle ifcGeometricRepresentationContextInstance = CreateInstance("IFCGEOMETRICREPRESENTATIONCONTEXT");

            IfcEngine.sdaiPutAttrBN(ifcGeometricRepresentationContextInstance, "ContextType", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Model"));

            IfcHandle ifcCoordinateSpaceDimensionRef = ifcCoordinateSpaceDimension;
            IfcEngine.sdaiPutAttrBN(ifcGeometricRepresentationContextInstance, "CoordinateSpaceDimension", IfcEngine.sdaiINTEGER, ref ifcCoordinateSpaceDimensionRef);

            IfcEngine.sdaiPutAttrBN(ifcGeometricRepresentationContextInstance, "Precision", IfcEngine.sdaiREAL, ref dPrecision);
            IfcEngine.sdaiPutAttrBN(ifcGeometricRepresentationContextInstance, "WorldCoordinateSystem", IfcEngine.sdaiINSTANCE, ifcWorldCoordinateSystemInstance);
            IfcEngine.sdaiPutAttrBN(ifcGeometricRepresentationContextInstance, "TrueNorth", IfcEngine.sdaiINSTANCE, CreateDirectionInstance(0, 1, 0));

            return ifcGeometricRepresentationContextInstance;
        }

        /// <summary>
        /// Creates IFCPROJECT
        /// </summary>
        public IfcHandle CreatProjectInstance(IfcHandle ifcOwnerHistoryInstance, IfcHandle ifcUnitAssignmentInstance, IfcHandle ifcGeometricRepresentationContextInstance)
        {
            IfcHandle ifcProjectInstance = CreateInstance("IFCPROJECT", (instance) =>
            {
                IfcEngine.sdaiPutAttrBN(instance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
                IfcEngine.sdaiPutAttrBN(instance, "OwnerHistory", IfcEngine.sdaiINSTANCE, ifcOwnerHistoryInstance);
                IfcEngine.sdaiPutAttrBN(instance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Default Project"));
                IfcEngine.sdaiPutAttrBN(instance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Description of Default Project"));
                IfcEngine.sdaiPutAttrBN(instance, "UnitsInContext", IfcEngine.sdaiINSTANCE, ifcUnitAssignmentInstance);

                IfcHandle ifcRepresentationContexts = IfcEngine.sdaiCreateAggrBN(instance, "RepresentationContexts");
                IfcEngine.sdaiAppend(ifcRepresentationContexts, IfcEngine.sdaiINSTANCE, ifcGeometricRepresentationContextInstance);
            });

            return ifcProjectInstance;
        }

        /// <summary>
        /// Creates IFCSITE
        /// </summary>
        public IfcHandle CreatSiteInstance(IfcHandle ifcOwnerHistoryInstance)
        {
            IfcHandle ifcSiteInstance = CreateInstance("IFCSITE", (instance) =>
            {
                IfcEngine.sdaiPutAttrBN(instance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
                IfcEngine.sdaiPutAttrBN(instance, "OwnerHistory", IfcEngine.sdaiINSTANCE, ifcOwnerHistoryInstance);
                IfcEngine.sdaiPutAttrBN(instance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Default Site"));
                IfcEngine.sdaiPutAttrBN(instance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Description of Default Site"));

                MATRIX matrix = MATRIX.IdentityMatrix();
                IfcHandle ifcPlacementRelativeTo = 0;
                IfcHandle ifcLocalPlacement = CreateLocalPlacementInstance(matrix, ifcPlacementRelativeTo);
                IfcEngine.sdaiPutAttrBN(instance, "ObjectPlacement", IfcEngine.sdaiINSTANCE, ifcLocalPlacement);

                IfcEngine.sdaiPutAttrBN(instance, "CompositionType", IfcEngine.sdaiENUM, "ELEMENT");

                IfcHandle ifcRefLatitude = IfcEngine.sdaiCreateAggrBN(instance, "RefLatitude");

                IfcHandle ifcRefLatX = 24;
                IfcEngine.sdaiAppend(ifcRefLatitude, IfcEngine.sdaiINTEGER, ref ifcRefLatX);

                IfcHandle ifcRefLatY = 28;
                IfcEngine.sdaiAppend(ifcRefLatitude, IfcEngine.sdaiINTEGER, ref ifcRefLatY);

                IfcHandle ifcRefLatZ = 0;
                IfcEngine.sdaiAppend(ifcRefLatitude, IfcEngine.sdaiINTEGER, ref ifcRefLatZ);

                IfcHandle ifcRefLongitude = IfcEngine.sdaiCreateAggrBN(instance, "RefLongitude");

                IfcHandle ifcRefLongX = 54;
                IfcEngine.sdaiAppend(ifcRefLongitude, IfcEngine.sdaiINTEGER, ref ifcRefLongX);

                IfcHandle ifcRefLongY = 25;
                IfcEngine.sdaiAppend(ifcRefLongitude, IfcEngine.sdaiINTEGER, ref ifcRefLongY);

                IfcHandle ifcRefLongZ = 0;
                IfcEngine.sdaiAppend(ifcRefLongitude, IfcEngine.sdaiINTEGER, ref ifcRefLongZ);

                double dRefElevation = 10;
                IfcEngine.sdaiPutAttrBN(instance, "RefElevation", IfcEngine.sdaiREAL, ref dRefElevation);
            });

            return ifcSiteInstance;
        }

        /// <summary>
        /// Creates IFCBUILDING
        /// </summary>
        public IfcHandle CreatBuildingInstance(IfcHandle ifcOwnerHistoryInstance, IfcHandle ifcPostalAdsress)
        {
            IfcHandle ifcBuildingInstance = CreateInstance("IFCBUILDING", (instance) =>
            {
                IfcEngine.sdaiPutAttrBN(instance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
                IfcEngine.sdaiPutAttrBN(instance, "OwnerHistory", IfcEngine.sdaiINSTANCE, ifcOwnerHistoryInstance);

                IfcEngine.sdaiPutAttrBN(instance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Default Building"));
                IfcEngine.sdaiPutAttrBN(instance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Description of Default Building"));

                MATRIX matrix = MATRIX.IdentityMatrix();
                IfcHandle ifcPlacementRelativeTo = 0;
                IfcHandle ifcLocalPlacement = CreateLocalPlacementInstance(matrix, ifcPlacementRelativeTo);
                IfcEngine.sdaiPutAttrBN(instance, "ObjectPlacement", IfcEngine.sdaiINSTANCE, ifcLocalPlacement);

                IfcEngine.sdaiPutAttrBN(instance, "CompositionType", IfcEngine.sdaiENUM, "ELEMENT");
                IfcEngine.sdaiPutAttrBN(instance, "BuildingAddress", IfcEngine.sdaiINSTANCE, ifcPostalAdsress);
            });

            return ifcBuildingInstance;
        }

        /// <summary>
        /// Creates IFCBUILDINGSTOREY
        /// </summary>
        public IfcHandle CreatBuildingStoreyInstance(IfcHandle ifcOwnerHistoryInstance, IfcHandle ifcBuildingStoreyLocalPlacementInstance)
        {
            IfcHandle ifcBuildingStoreyInstance = CreateInstance("IFCBUILDINGSTOREY", (instance) =>
            {
                IfcEngine.sdaiPutAttrBN(instance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
                IfcEngine.sdaiPutAttrBN(instance, "OwnerHistory", IfcEngine.sdaiINSTANCE, ifcOwnerHistoryInstance);
                IfcEngine.sdaiPutAttrBN(instance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Default Building Storey"));
                IfcEngine.sdaiPutAttrBN(instance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Description of Default Building Storey"));
                IfcEngine.sdaiPutAttrBN(instance, "ObjectPlacement", IfcEngine.sdaiINSTANCE, ifcBuildingStoreyLocalPlacementInstance);
                IfcEngine.sdaiPutAttrBN(instance, "CompositionType", IfcEngine.sdaiENUM, "ELEMENT");

                double dElevation = 0;
                IfcEngine.sdaiPutAttrBN(instance, "Elevation", IfcEngine.sdaiREAL, ref dElevation);
            });

            return ifcBuildingStoreyInstance;
        }

        /// <summary>
        /// Creates IFCSHAPEREPRESENTATION
        /// </summary>
        public IfcHandle CreateShapeRepresentationInstance(IfcHandle ifcGeometricRepresentationContextInstance, IfcRepresentation representation, double dP0x, double dP0y, double dP1x, double dP1y)
        {
            IfcHandle ifcShapeRepresentationInstance = CreateInstance("IFCSHAPEREPRESENTATION");

            if (representation == IfcRepresentation.AXIS_CURVE2D_REPRESENTATION)
            {
                IfcHandle ifcItems = IfcEngine.sdaiCreateAggrBN(ifcShapeRepresentationInstance, "Items");
                IfcEngine.sdaiAppend(ifcItems, IfcEngine.sdaiINSTANCE, CreatePolylineInstance(dP0x, dP0y, dP1x, dP1y));

                IfcEngine.sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationIdentifier", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Axis"));
                IfcEngine.sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationType", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Curve2D"));
                IfcEngine.sdaiPutAttrBN(ifcShapeRepresentationInstance, "ContextOfItems", IfcEngine.sdaiINSTANCE, ifcGeometricRepresentationContextInstance);
            }
            else
            {
                System.Diagnostics.Debug.Assert(false, "Unsupported representation.");
            }

            return ifcShapeRepresentationInstance;
        }

        /// <summary>
        /// Creates IFCSHAPEREPRESENTATION
        /// </summary>
        public IfcHandle CreateShapeRepresentationInstance(IfcHandle ifcGeometricRepresentationContextInstance, IfcRepresentation representation, POLYGON2D polygon, double dDepth)
        {
            IfcHandle ifcShapeRepresentationInstance = CreateInstance("IFCSHAPEREPRESENTATION");

            if (representation == IfcRepresentation.BODY_SWEPTSOLID_REPRESENTATION)
            {
                IfcHandle ifcItems = IfcEngine.sdaiCreateAggrBN(ifcShapeRepresentationInstance, "Items");
                IfcEngine.sdaiAppend(ifcItems, IfcEngine.sdaiINSTANCE, CreateExtrudedAreaSolidInstance(polygon, dDepth));

                IfcEngine.sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationIdentifier", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Body"));
			    IfcEngine.sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationType", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("SweptSolid"));
                IfcEngine.sdaiPutAttrBN(ifcShapeRepresentationInstance, "ContextOfItems", IfcEngine.sdaiINSTANCE, ifcGeometricRepresentationContextInstance);
            }
            else
            {
                System.Diagnostics.Debug.Assert(false, "Unsupported representation.");
            }

            return ifcShapeRepresentationInstance;
        }

        /// <summary>
        /// Creates IFCSHAPEREPRESENTATION
        /// </summary>
        public IfcHandle CreateShapeRepresentationInstance(IfcHandle ifcGeometricRepresentationContextInstance, IfcRepresentation representation, double dWidth, double dThickness, double dHeight, string strRepresentationIdentifier)
        {
            IfcHandle ifcShapeRepresentationInstance = CreateInstance("IFCSHAPEREPRESENTATION");

            if (representation == IfcRepresentation.BODY_BOUNDINGBOX_REPRESENTATION)
            {
                IfcEngine.sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationIdentifier", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strRepresentationIdentifier));
                IfcEngine.sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationType", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("BoundingBox"));
                IfcEngine.sdaiPutAttrBN(ifcShapeRepresentationInstance, "ContextOfItems", IfcEngine.sdaiINSTANCE, ifcGeometricRepresentationContextInstance);

                IfcHandle ifcItems = IfcEngine.sdaiCreateAggrBN(ifcShapeRepresentationInstance, "Items");
                IfcEngine.sdaiAppend(ifcItems, IfcEngine.sdaiINSTANCE, CreateBoundingBoxInstance(dWidth, dThickness, dHeight));
            }
            else
            {
                System.Diagnostics.Debug.Assert(false, "Unsupported representation.");
            }

            return ifcShapeRepresentationInstance;
        }

        /// <summary>
        /// Creates IFCSHAPEREPRESENTATION
        /// </summary>
        public IfcHandle CreateShapeRepresentationInstance(IfcHandle ifcGeometricRepresentationContextInstance, IfcRepresentation representation, IList<SHELL> shells)
        {
            IfcHandle ifcShapeRepresentationInstance = CreateInstance("IFCSHAPEREPRESENTATION");

            switch (representation)
            {
                case IfcRepresentation.BODY_BREP_REPRESENTATION:
                    {
                        IfcHandle ifcItems = IfcEngine.sdaiCreateAggrBN(ifcShapeRepresentationInstance, "Items");

                        IfcEngine.sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationIdentifier", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Body"));
                        IfcEngine.sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationType", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Brep"));
                        IfcEngine.sdaiPutAttrBN(ifcShapeRepresentationInstance, "ContextOfItems", IfcEngine.sdaiINSTANCE, ifcGeometricRepresentationContextInstance);

                        foreach (var shell in shells)
                        {
                            IfcHandle ifcClosedShellInstance = CreateInstance("IFCCLOSEDSHELL");
                            IfcHandle ifcCfsFaces = IfcEngine.sdaiCreateAggrBN(ifcClosedShellInstance, "CfsFaces");

                            foreach (var polygon in shell.Polygons)
                            {
                                IfcHandle ifcPolyLoopInstance = CreateInstance("IFCPOLYLOOP");
                                IfcHandle ifcPolygon = IfcEngine.sdaiCreateAggrBN(ifcPolyLoopInstance, "Polygon");

                                foreach (var vector in polygon.Vectors)
                                {
                                    foreach (var point in vector)
                                    {
                                        if (point.CartesianPointInstance == 0)
                                        {
                                            point.CartesianPointInstance = CreateCartesianPointInstance(point);
                                        }

                                        IfcEngine.sdaiAppend(ifcPolygon, IfcEngine.sdaiINSTANCE, point.CartesianPointInstance);
                                    }
                                } // foreach (var vector in ...

                                IfcHandle ifcFaceOuterBoundInstance = CreateInstance("IFCFACEOUTERBOUND");
                                IfcEngine.sdaiPutAttrBN(ifcFaceOuterBoundInstance, "Bound", IfcEngine.sdaiINSTANCE, ifcPolyLoopInstance);
                                IfcEngine.sdaiPutAttrBN(ifcFaceOuterBoundInstance, "Orientation", IfcEngine.sdaiENUM, IfcEngine.TRUE);

                                IfcHandle ifcFaceInstance = CreateInstance("IFCFACE");
                                IfcHandle ifcBounds = IfcEngine.sdaiCreateAggrBN(ifcFaceInstance, "Bounds");

                                IfcEngine.sdaiAppend(ifcBounds, IfcEngine.sdaiINSTANCE, ifcFaceOuterBoundInstance);
                                IfcEngine.sdaiAppend(ifcCfsFaces, IfcEngine.sdaiINSTANCE, ifcFaceInstance);

                                if (polygon.OpeningVectors.Count > 0)
                                {
                                    ifcPolyLoopInstance = CreateInstance("IFCPOLYLOOP");
                                    ifcPolygon = IfcEngine.sdaiCreateAggrBN(ifcPolyLoopInstance, "Polygon");

                                    foreach (var openingVector in polygon.OpeningVectors)
                                    {
                                        foreach (var point in openingVector)
                                        {
                                            if (point.CartesianPointInstance == 0)
                                            {
                                                point.CartesianPointInstance = CreateCartesianPointInstance(point);
                                            }

                                            IfcEngine.sdaiAppend(ifcPolygon, IfcEngine.sdaiINSTANCE, point.CartesianPointInstance);
                                        }
                                    } // foreach (var openingVector in ...

                                    IfcHandle ifcFaceBoundInstance = CreateInstance("IFCFACEBOUND");
						            IfcEngine.sdaiPutAttrBN(ifcFaceBoundInstance, "Bound", IfcEngine.sdaiINSTANCE, ifcPolyLoopInstance);
                                    IfcEngine.sdaiPutAttrBN(ifcFaceBoundInstance, "Orientation", IfcEngine.sdaiENUM, IfcEngine.TRUE);

                                    IfcEngine.sdaiAppend(ifcBounds, IfcEngine.sdaiINSTANCE, ifcFaceBoundInstance);
                                } // if (polygon.OpeningVectors.Count > 0)
                            } // foreach (var polygon in ...

                            IfcHandle ifcFacetedBrepInstance = CreateInstance("IFCFACETEDBREP");
                            IfcEngine.sdaiPutAttrBN(ifcFacetedBrepInstance, "Outer", IfcEngine.sdaiINSTANCE, ifcClosedShellInstance);

                            IfcEngine.sdaiAppend(ifcItems, IfcEngine.sdaiINSTANCE, ifcFacetedBrepInstance);
                        } // foreach (var shell in ...
                    } // case IfcRepresentation.BODY_BREP_REPRESENTATION
                    break;

                case IfcRepresentation.BODY_TESSELLATION_REPRESENTATION:
                    {
                        IfcHandle ifcItems = IfcEngine.sdaiCreateAggrBN(ifcShapeRepresentationInstance, "Items");

                        IfcEngine.sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationIdentifier", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Body"));
                        IfcEngine.sdaiPutAttrBN(ifcShapeRepresentationInstance, "RepresentationType", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Tessellation"));
                        IfcEngine.sdaiPutAttrBN(ifcShapeRepresentationInstance, "ContextOfItems", IfcEngine.sdaiINSTANCE, ifcGeometricRepresentationContextInstance);

                        foreach (var shell in shells)
                        {
                            IfcHandle ifcTriangulatedFaceSet = CreateInstance("IfcTriangulatedFaceSet");

                            System.Diagnostics.Debug.Assert((shell.Polygons.Count == 1) && (shell.Polygons[0].Vectors.Count == 1));

                            #region CoordList

                            IfcHandle ifcCoordinates = CreateInstance("IfcCartesianPointList3D");
                            IfcHandle ifcCoordList = IfcEngine.sdaiCreateAggrBN(ifcCoordinates, "CoordList");

                            foreach (var point in shell.Polygons[0].Vectors[0])
                            {
                                if (point.CartesianPointInstance == 0)
                                {
                                    point.CartesianPointInstance = CreateCartesianPointInstance(point);
                                }

                                IfcEngine.sdaiAppend(ifcCoordList, IfcEngine.sdaiINSTANCE, point.CartesianPointInstance);
                            }

                            IfcEngine.sdaiPutAttrBN(ifcTriangulatedFaceSet, "Coordinates", IfcEngine.sdaiINSTANCE, ifcCoordinates);

                            #endregion // CoordList

                            #region CoordIndex

                            IfcHandle i1 = CreateInstance("IfcInteger");
                            IfcEngine.sdaiAppend(i1, IfcEngine.sdaiINTEGER, 111);
                            IfcEngine.sdaiAppend(i1, IfcEngine.sdaiINTEGER, 111);
                            IfcEngine.sdaiAppend(i1, IfcEngine.sdaiINTEGER, 111);

                            IfcHandle ifcCoordIndex = IfcEngine.sdaiCreateAggrBN(ifcTriangulatedFaceSet, "CoordIndex");

                            IfcEngine.sdaiAppend(i1, IfcEngine.sdaiINSTANCE, i1);

                            #endregion // CoordIndex

                            IfcEngine.sdaiAppend(ifcItems, IfcEngine.sdaiINSTANCE, ifcTriangulatedFaceSet);
                        } // foreach (var shell in ...
                    } // case IfcRepresentation.BODY_BREP_REPRESENTATION
                    break;

                default:
                    System.Diagnostics.Debug.Assert(false, "Unsupported representation.");
                    break;
            } // switch (representation)

            return ifcShapeRepresentationInstance;
        }

        /// <summary>
        /// Creates IFCEXTRUDEDAREASOLID
        /// </summary>
        public IfcHandle CreateExtrudedAreaSolidInstance(POLYGON2D polygon, double dDepth)
        {
            IfcHandle ifcExtrudedAreaSolidInstance = CreateInstance("IFCEXTRUDEDAREASOLID");

            MATRIX matrix = MATRIX.IdentityMatrix();

            IfcEngine.sdaiPutAttrBN(ifcExtrudedAreaSolidInstance, "SweptArea", IfcEngine.sdaiINSTANCE, CreateArbitraryClosedProfileDefInstance(polygon));
            IfcEngine.sdaiPutAttrBN(ifcExtrudedAreaSolidInstance, "Position", IfcEngine.sdaiINSTANCE, CreateAxis2Placement3DInstance(matrix));
            IfcEngine.sdaiPutAttrBN(ifcExtrudedAreaSolidInstance, "ExtrudedDirection", IfcEngine.sdaiINSTANCE, CreateDirectionInstance(matrix._d31, matrix._d32, matrix._d33));
            IfcEngine.sdaiPutAttrBN(ifcExtrudedAreaSolidInstance, "Depth", IfcEngine.sdaiREAL, ref dDepth);

            return ifcExtrudedAreaSolidInstance;
        }

        /// <summary>
        /// Creates IFCARBITRARYCLOSEDPROFILEDEF
        /// </summary>
        public IfcHandle CreateArbitraryClosedProfileDefInstance(POLYGON2D polygon)
        {
            IfcHandle ifcArbitraryClosedProfileDefInstance = CreateInstance("IFCARBITRARYCLOSEDPROFILEDEF");

            IfcEngine.sdaiPutAttrBN(ifcArbitraryClosedProfileDefInstance, "ProfileType", IfcEngine.sdaiENUM, "AREA");
            IfcEngine.sdaiPutAttrBN(ifcArbitraryClosedProfileDefInstance, "OuterCurve", IfcEngine.sdaiINSTANCE, CreatePolylineInstance(polygon));

            return ifcArbitraryClosedProfileDefInstance;
        }

        /// <summary>
        /// Creates IFCPOLYLINE
        /// </summary>
        public IfcHandle CreatePolylineInstance(POLYGON2D polygon)
        {
            IfcHandle ifcPolylineInstance = CreateInstance("IFCPOLYLINE");

            if (polygon.Count > 0)
            {
                IfcHandle ifcPoints = IfcEngine.sdaiCreateAggrBN(ifcPolylineInstance, "Points");
                foreach (POINT2D point in polygon)
                {
                    IfcEngine.sdaiAppend(ifcPoints, IfcEngine.sdaiINSTANCE, CreateCartesianPointInstance(point.X, point.Y));
                }

                IfcEngine.sdaiAppend(ifcPoints, IfcEngine.sdaiINSTANCE, CreateCartesianPointInstance(polygon[0].X, polygon[0].Y));
            }

            return ifcPolylineInstance;
        }

        /// <summary>
        /// Creates IFCPOLYLINE
        /// </summary>
        public IfcHandle CreatePolylineInstance(double dP0x, double dP0y, double dP1x, double dP1y)
        {
            IfcHandle ifcPolylineInstance = CreateInstance("IFCPOLYLINE");

            IfcHandle ifcPoints = IfcEngine.sdaiCreateAggrBN(ifcPolylineInstance, "Points");
            IfcEngine.sdaiAppend(ifcPoints, IfcEngine.sdaiINSTANCE, CreateCartesianPointInstance(dP0x, dP0y));
            IfcEngine.sdaiAppend(ifcPoints, IfcEngine.sdaiINSTANCE, CreateCartesianPointInstance(dP1x, dP1y));

            return ifcPolylineInstance;
        }

        /// <summary>
        /// Creates IFCBOUNDINGBOX
        /// </summary>
        public IfcHandle CreateBoundingBoxInstance(double dWidth, double dThickness, double dHeight)
        {
            IfcHandle ifcBoundingBoxInstance = CreateInstance("IFCBOUNDINGBOX");

            IfcEngine.sdaiPutAttrBN(ifcBoundingBoxInstance, "Corner", IfcEngine.sdaiINSTANCE, CreateCartesianPointInstance(0, 0, 0));
            IfcEngine.sdaiPutAttrBN(ifcBoundingBoxInstance, "XDim", IfcEngine.sdaiREAL, ref dWidth);
            IfcEngine.sdaiPutAttrBN(ifcBoundingBoxInstance, "YDim", IfcEngine.sdaiREAL, ref dThickness);
            IfcEngine.sdaiPutAttrBN(ifcBoundingBoxInstance, "ZDim", IfcEngine.sdaiREAL, ref dHeight);

            return ifcBoundingBoxInstance;
        }

        /// <summary>
        /// Creates IFCMATERIALCONSTITUENT
        /// </summary>
        public IfcHandle CreateMaterialConstituentInstance(string strName)
        {
            IfcHandle ifcMaterialConstituentInstance = CreateInstance("IFCMATERIALCONSTITUENT");

            IfcEngine.sdaiPutAttrBN(ifcMaterialConstituentInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Framing"));
            IfcEngine.sdaiPutAttrBN(ifcMaterialConstituentInstance, "Material", IfcEngine.sdaiINSTANCE, CreateMaterialInstance(strName));

            return ifcMaterialConstituentInstance;
        }

        /// <summary>
        /// Creates IFCMATERIALCONSTITUENTSET
        /// </summary>
        public IfcHandle CreateMaterialConstituentSetInstance()
        {
            IfcHandle ifcMaterialConstituentSetInstance = CreateInstance("IFCMATERIALCONSTITUENTSET");

            IfcEngine.sdaiPutAttrBN(ifcMaterialConstituentSetInstance, "Name", IfcEngine.sdaiUNICODE,Encoding.Unicode.GetBytes("Constituent Set for Window"));

	        IfcHandle ifcMaterialConstituents = IfcEngine.sdaiCreateAggrBN(ifcMaterialConstituentSetInstance, "MaterialConstituents");

            IfcEngine.sdaiAppend(ifcMaterialConstituents, IfcEngine.sdaiINSTANCE, CreateMaterialConstituentInstance("Glass"));
	        IfcEngine.sdaiAppend(ifcMaterialConstituents, IfcEngine.sdaiINSTANCE, CreateMaterialConstituentInstance("Wood"));

            return ifcMaterialConstituentSetInstance;
        }

        /// <summary>
        /// Creates a polygon
        /// </summary>
        public POLYGON2D CreatePolygonStructureForSquare(double dMinX, double dMinY, double dMaxX, double dMaxY)
        {
	        POLYGON2D polygon = new POLYGON2D();

	        polygon.Add(new POINT2D(dMinX, dMinY));
            polygon.Add(new POINT2D(dMinX, dMaxY));
            polygon.Add(new POINT2D(dMaxX, dMaxY));
            polygon.Add(new POINT2D(dMaxX, dMinY));

	        return	polygon;
        }

        /// <summary>
        /// Creates an extruded shape
        /// </summary>
        public void CreateExtrudedPolygonShape(POLYGON2D polygon, double dDepth, IfcHandle ifcGeometricRepresentationContextInstance, IfcHandle ifcAggrRepresentations)
        {
            IfcHandle ifcShapeRepresentationInstance = CreateShapeRepresentationInstance(ifcGeometricRepresentationContextInstance,
                IfcRepresentation.BODY_SWEPTSOLID_REPRESENTATION, polygon, dDepth);

            IfcEngine.sdaiAppend(ifcAggrRepresentations, IfcEngine.sdaiINSTANCE, ifcShapeRepresentationInstance);
        }

        /// <summary>
        /// Creates B-Rep shape
        /// </summary>
        /// <param name="shell"></param>
        public void CreateBRepShape(SHELL shell, IfcHandle ifcGeometricRepresentationContextInstance, IfcHandle ifcAggrRepresentations)
        {
            IfcHandle ifcShapeRepresentationInstance = CreateShapeRepresentationInstance(ifcGeometricRepresentationContextInstance, 
                IfcRepresentation.BODY_BREP_REPRESENTATION, new List<SHELL>() { shell });

            IfcEngine.sdaiAppend(ifcAggrRepresentations, IfcEngine.sdaiINSTANCE, ifcShapeRepresentationInstance);
        }

        /// <summary>
        /// Creates B-Rep shape
        /// </summary>
        /// <param name="shell"></param>
        public void CreateBRepShape(SHELL shell, double dP0x, double dP0y, double dP1x, double dP1y, IfcHandle ifcGeometricRepresentationContextInstance, IfcHandle ifcAggrRepresentations)
        {
            IfcHandle ifcShapeRepresentationInstance = CreateShapeRepresentationInstance(ifcGeometricRepresentationContextInstance, 
                IfcRepresentation.AXIS_CURVE2D_REPRESENTATION, dP0x, dP0y, dP1x, dP1y);
            IfcEngine.sdaiAppend(ifcAggrRepresentations, IfcEngine.sdaiINSTANCE,ifcShapeRepresentationInstance);

            ifcShapeRepresentationInstance = CreateShapeRepresentationInstance(ifcGeometricRepresentationContextInstance,
                IfcRepresentation.BODY_BREP_REPRESENTATION, new List<SHELL>() { shell });
            IfcEngine.sdaiAppend(ifcAggrRepresentations, IfcEngine.sdaiINSTANCE, ifcShapeRepresentationInstance);
        }

        /// <summary>
        /// Creates Tessellation shape
        /// </summary>
        /// <param name="shell"></param>
        public void CreateTessellationShape(SHELL shell, double dP0x, double dP0y, double dP1x, double dP1y, IfcHandle ifcGeometricRepresentationContextInstance, IfcHandle ifcAggrRepresentations)
        {
            IfcHandle ifcShapeRepresentationInstance = CreateShapeRepresentationInstance(ifcGeometricRepresentationContextInstance,
                IfcRepresentation.AXIS_CURVE2D_REPRESENTATION, dP0x, dP0y, dP1x, dP1y);
            IfcEngine.sdaiAppend(ifcAggrRepresentations, IfcEngine.sdaiINSTANCE, ifcShapeRepresentationInstance);

            ifcShapeRepresentationInstance = CreateShapeRepresentationInstance(ifcGeometricRepresentationContextInstance,
                IfcRepresentation.BODY_TESSELLATION_REPRESENTATION, new List<SHELL>() { shell });
            IfcEngine.sdaiAppend(ifcAggrRepresentations, IfcEngine.sdaiINSTANCE, ifcShapeRepresentationInstance);
        }

        /// <summary>
        /// Creates a cuboid
        /// </summary>
        public SHELL CreateShellStructureForCuboid(double dMinX, double dMinY, double dMinZ, double dMaxX, double dMaxY, double dMaxZ)
        {
            SHELL shell = new SHELL();

            VECTOR3D vector = new VECTOR3D();
            vector.Add(new POINT3D(dMinX, dMinY, dMinZ));
            vector.Add(new POINT3D(dMaxX, dMinY, dMinZ));
            vector.Add(new POINT3D(dMinX, dMaxY, dMinZ));
            vector.Add(new POINT3D(dMaxX, dMaxY, dMinZ));
            vector.Add(new POINT3D(dMinX, dMinY, dMaxZ));
            vector.Add(new POINT3D(dMaxX, dMinY, dMaxZ));
            vector.Add(new POINT3D(dMinX, dMaxY, dMaxZ));
            vector.Add(new POINT3D(dMaxX, dMaxY, dMaxZ));
            
            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[0], vector[2], vector[3], vector[1]));
            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[4], vector[5], vector[7], vector[6]));
            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[0], vector[4], vector[6], vector[2]));
            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[2], vector[6], vector[7], vector[3]));
            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[3], vector[7], vector[5], vector[1]));
            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[1], vector[5], vector[4], vector[0]));

            return shell;
        }

        /// <summary>
        /// Creates a cuboid for tesselation mode; http://www.buildingsmart-tech.org/ifc/IFC4/final/html/schema/ifcgeometricmodelresource/lexical/ifctriangulatedfaceset.htm
        /// </summary>
        public SHELL CreateShellStructureForCuboidTessellationMode(double dMinX, double dMinY, double dMinZ, double dMaxX, double dMaxY, double dMaxZ)
        {
            SHELL shell = new SHELL();

            VECTOR3D vector = new VECTOR3D();
            vector.Add(new POINT3D(dMinX, dMinY, dMinZ));
            vector.Add(new POINT3D(dMaxX, dMinY, dMinZ));
            vector.Add(new POINT3D(dMinX, dMaxY, dMinZ));
            vector.Add(new POINT3D(dMaxX, dMaxY, dMinZ));
            vector.Add(new POINT3D(dMinX, dMinY, dMaxZ));
            vector.Add(new POINT3D(dMaxX, dMinY, dMaxZ));
            vector.Add(new POINT3D(dMinX, dMaxY, dMaxZ));
            vector.Add(new POINT3D(dMaxX, dMaxY, dMaxZ));

            POLYGON3D polygon = new POLYGON3D();
            polygon.Vectors.Add(vector);

            shell.Polygons.Add(polygon);

            return shell;
        }

        /// <summary>
        /// Creates a cuboid
        /// </summary>
        public SHELL CreateShellStructureForCuboidWithOpening(double dMinX, double dMinY, double dMinZ, double dMaxX, double dMaxY, double dMaxZ
            , double dMinXOpening, double dMinZOpening, double dMaxXOpening, double dMaxZOpening)
        {
            SHELL shell = new SHELL();

            VECTOR3D vector = new VECTOR3D();
            vector.Add(new POINT3D(dMinX, dMinY, dMinZ));
            vector.Add(new POINT3D(dMaxX, dMinY, dMinZ));
            vector.Add(new POINT3D(dMinX, dMaxY, dMinZ));
            vector.Add(new POINT3D(dMaxX, dMaxY, dMinZ));
            vector.Add(new POINT3D(dMinX, dMinY, dMaxZ));
            vector.Add(new POINT3D(dMaxX, dMinY, dMaxZ));
            vector.Add(new POINT3D(dMinX, dMaxY, dMaxZ));
            vector.Add(new POINT3D(dMaxX, dMaxY, dMaxZ));
            vector.Add(new POINT3D(dMinXOpening, dMinY, dMinZOpening));
            vector.Add(new POINT3D(dMaxXOpening, dMinY, dMinZOpening));
            vector.Add(new POINT3D(dMinXOpening, dMaxY, dMinZOpening));
            vector.Add(new POINT3D(dMaxXOpening, dMaxY, dMinZOpening));
            vector.Add(new POINT3D(dMinXOpening, dMinY, dMaxZOpening));
            vector.Add(new POINT3D(dMaxXOpening, dMinY, dMaxZOpening));
            vector.Add(new POINT3D(dMinXOpening, dMaxY, dMaxZOpening));
            vector.Add(new POINT3D(dMaxXOpening, dMaxY, dMaxZOpening));

            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[0], vector[2], vector[3], vector[1]));
            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[4], vector[5], vector[7], vector[6]));
            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[0], vector[4], vector[6], vector[2]));
            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[2], vector[6], vector[7], vector[3]));
            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[3], vector[7], vector[5], vector[1]));
            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[1], vector[5], vector[4], vector[0]));
            
            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[0 + 8], vector[1 + 8], vector[3 + 8], vector[2 + 8]));
            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[4 + 8], vector[6 + 8], vector[7 + 8], vector[5 + 8]));
            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[0 + 8], vector[2 + 8], vector[6 + 8], vector[4 + 8]));
            shell.Polygons.Add(Create3DPolygonWith4Vectors(vector[3 + 8], vector[1 + 8], vector[5 + 8], vector[7 + 8]));

            Add3DPolygonOpeningWith4Vectors(shell.Polygons[3], vector[2 + 8], vector[3 + 8], vector[7 + 8], vector[6 + 8]);
            Add3DPolygonOpeningWith4Vectors(shell.Polygons[5], vector[1 + 8], vector[0 + 8], vector[4 + 8], vector[5 + 8]);

            return shell;
        }

        /// <summary>
        /// Creates a polygon
        /// </summary>
        POLYGON3D Create3DPolygonWith4Vectors(POINT3D pointI, POINT3D pointII, POINT3D pointIII, POINT3D pointIV)
        {
            POLYGON3D polygon = new POLYGON3D();            

            {
                VECTOR3D vector = new VECTOR3D();
                vector.Add(pointI);

                polygon.Vectors.Add(vector);
            }

            {
                VECTOR3D vector = new VECTOR3D();
                vector.Add(pointII);

                polygon.Vectors.Add(vector);
            }

            {
                VECTOR3D vector = new VECTOR3D();
                vector.Add(pointIII);

                polygon.Vectors.Add(vector);
            }

            {
                VECTOR3D vector = new VECTOR3D();
                vector.Add(pointIV);

                polygon.Vectors.Add(vector);
            }

            return polygon;
        }

        /// <summary>
        /// Creates a polygon
        /// </summary>
        void Add3DPolygonOpeningWith4Vectors(POLYGON3D polygon, POINT3D pointI, POINT3D pointII, POINT3D pointIII, POINT3D pointIV)
        {
            {
                VECTOR3D vector = new VECTOR3D();
                vector.Add(pointI);

                polygon.OpeningVectors.Add(vector);
            }

            {
                VECTOR3D vector = new VECTOR3D();
                vector.Add(pointII);

                polygon.OpeningVectors.Add(vector);
            }

            {
                VECTOR3D vector = new VECTOR3D();
                vector.Add(pointIII);

                polygon.OpeningVectors.Add(vector);
            }

            {
                VECTOR3D vector = new VECTOR3D();
                vector.Add(pointIV);

                polygon.OpeningVectors.Add(vector);
            }
        }

        /// <summary>
        /// IDisposable
        /// </summary>
        public virtual void Dispose()
        {
            if (this.ModelInstance != 0)
            {
                IfcEngine.sdaiCloseModel(this.ModelInstance);

                this.ModelInstance = 0;
            }
        }
    }
}
