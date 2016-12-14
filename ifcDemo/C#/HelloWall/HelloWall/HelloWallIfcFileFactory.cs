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
    /// Creates .ifc/.ifx files
    /// </summary>
    public class HelloWallIfcFileFactory : IfcFileFactory
    {
        #region Members

        /// <summary>
        /// Model (Model-View-Presenter)
        /// </summary>
        private HelloWallSettings _settings = null;

        /// <summary>
        /// Linear conversion factor
        /// </summary>
        private double _dLinearConversionFactor = 0;

        /// <summary>
        /// Organization instance
        /// </summary>
        private IfcHandle _ifcOrganizationInstance = 0;

        /// <summary>
        /// Application instance
        /// </summary>
        private IfcHandle _ifcApplicationInstance = 0;

        /// <summary>
        /// Owner history instance
        /// </summary>
        IfcHandle _ifcOwnerHistoryInstance = 0;

        /// <summary>
        /// Dimensional exponents instance
        /// </summary>
        IfcHandle _ifcDimensionalExponentsInstance = 0;

        /// <summary>
        /// Measure with unit instance
        /// </summary>
        IfcHandle _ifcMeasureWithUnitInstance = 0;

        /// <summary>
        /// Conversion based unit instance
        /// </summary>
        IfcHandle _ifcConversionBasedUnitInstance = 0;

        /// <summary>
        /// Unit assignment instance
        /// </summary>
        IfcHandle _ifcUnitAssignmentInstance = 0;

        /// <summary>
        /// World coordinate system instance
        /// </summary>
        IfcHandle _ifcWorldCoordinateSystemInstance = 0;

        /// <summary>
        /// Geometric representation context instance
        /// </summary>
        IfcHandle _ifcGeometricRepresentationContextInstance = 0;

        /// <summary>
        /// Project instance
        /// </summary>
        IfcHandle _ifcProjectInstance = 0;

        /// <summary>
        /// Site instance
        /// </summary>
        IfcHandle _ifcSiteInstance = 0;

        /// <summary>
        /// Building instance
        /// </summary>
        IfcHandle _ifcBuildingInstance = 0;

        /// <summary>
        /// Building storey instance
        /// </summary>
        IfcHandle _ifcBuildingStoreyInstance = 0;

        /// <summary>
        /// Building storey local placement instance
        /// </summary>
        IfcHandle _ifcBuildingStoreyLocalPlacementInstance = 0;

        /// <summary>
        /// Wall instance
        /// </summary>
        IfcHandle _ifcWallInstance = 0;

        /// <summary>
        /// Wall local placement
        /// </summary>
        IfcHandle _ifcWallLocalPlacementInstance = 0;

        /// <summary>
        /// Opening element instance
        /// </summary>
        IfcHandle _ifcOpeningElementInstance = 0;

        /// <summary>
        /// Opening local placement
        /// </summary>
        IfcHandle _ifcOpeningLocalPlacementInstance = 0;

        /// <summary>
        /// Related elements
        /// </summary>
        IfcHandle _ifcAggrRelatedElements = 0;

        /// <summary>
        /// Representations
        /// </summary>
        IfcHandle _ifcAggrRepresentations = 0;

        #endregion // Members

        /// <summary>
        /// ctor
        /// </summary>
        public HelloWallIfcFileFactory(HelloWallSettings settings)
            : base(settings.SchemaFile)
        {
            _settings = settings;
        }

        /// <summary>
        /// Entry point
        /// </summary>
        public void Build()
        {
            _dLinearConversionFactor = _settings.UseMeters ? 1 : 1000;

            CreateHeader();

            IfcHandle ifcPersonInstance = CreatePersonInstance("Peter", "Bonsma");

            _ifcOrganizationInstance = CreateOrganizationInstance("RDF", "RDF Ltd.");

            IfcHandle ifcPersonAndOrganizationInstance = CreatePersonAndOrganizationInstance(ifcPersonInstance, _ifcOrganizationInstance);

            _ifcApplicationInstance = CreateApplicationInstance();

            _ifcOwnerHistoryInstance = CreateOwnerHistory(ifcPersonAndOrganizationInstance, _ifcApplicationInstance);

            _ifcDimensionalExponentsInstance = CreateDimensionalExponentsInstance();

            _ifcMeasureWithUnitInstance = CreateMeasureWithUnitInstance();

            _ifcConversionBasedUnitInstance = CreateConversionBasedUnitInstance();

            _ifcUnitAssignmentInstance = CreateUnitAssignmentInstance();

            _ifcWorldCoordinateSystemInstance = CreateAxis2Placement3DInstance(POINT3D.IdentityPoint());

            _ifcGeometricRepresentationContextInstance = CreateGeometricRepresentationContextInstance(_ifcWorldCoordinateSystemInstance, 3, 0.00001);
            
            _ifcProjectInstance = CreatProjectInstance(_ifcOwnerHistoryInstance, _ifcUnitAssignmentInstance, _ifcGeometricRepresentationContextInstance);

            _ifcSiteInstance = CreatSiteInstance(_ifcOwnerHistoryInstance);

            _ifcBuildingInstance = CreatBuildingInstance(_ifcOwnerHistoryInstance, CreatePostalAddress());

            _ifcBuildingStoreyLocalPlacementInstance = CreateLocalPlacementInstance(MATRIX.IdentityMatrix(), 0);

            _ifcBuildingStoreyInstance = CreatBuildingStoreyInstance(_ifcOwnerHistoryInstance, _ifcBuildingStoreyLocalPlacementInstance);

            CreateRelAggregates("BuildingContainer", "BuildingContainer for BuildigStories", _ifcBuildingInstance, _ifcBuildingStoreyInstance);
            CreateRelAggregates("SiteContainer", "SiteContainer For Buildings", _ifcSiteInstance, _ifcBuildingInstance);
            CreateRelAggregates("ProjectContainer", "ProjectContainer for Sites", _ifcProjectInstance, _ifcSiteInstance);

            if (_settings.WallIsEnabled || _settings.OpeningIsEnabled || _settings.WindowIsEnabled)
            {
                CreateRelContainedInSpatialStructure("BuildingStoreyContainer", "BuildingStoreyContainer for Building Elements", _ifcBuildingStoreyInstance, ref _ifcAggrRelatedElements);
            }

            if (_settings.WallIsEnabled)
            {
                CreateWall();

                if (_settings.OpeningIsEnabled)
                {
                    CreateOpening();
                }
            }

            if (_settings.WindowIsEnabled && (!_settings.WallIsEnabled || (_settings.WallIsEnabled && _settings.OpeningIsEnabled)))
            {
                CreateWindow();
            }
        }        
                
        #region Wall

        /// <summary>
        /// Builds a wall
        /// </summary> 
        private void CreateWall()
        {
            double dWallWidth = _settings.WallWidth * 0.001 * _dLinearConversionFactor;
            double dWallHeight = _settings.WallHeight * 0.001 * _dLinearConversionFactor;
            double dWallThickness = _settings.WallThickness * 0.001 * _dLinearConversionFactor;

            double dOpeningWidth = _settings.OpeningWidth * 0.001 * _dLinearConversionFactor;
            double dOpeningHeight = _settings.OpeningHeight * 0.001 * _dLinearConversionFactor;
            double dOpeningXOffset = _settings.OpeningXOffset * 0.001 * _dLinearConversionFactor;
            double dOpeningZOffset = _settings.OpeningZOffset * 0.001 * _dLinearConversionFactor;

            // TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            _settings.WallBodyRepresentation = IfcBodyRepresentation.Tessellation;

            switch (_settings.WallBodyRepresentation)
            {
                case IfcBodyRepresentation.ExtrudedPolygon:
                    {
                        _ifcWallInstance = CreateWallStandardCaseInstance(_settings.WallName, 0, 0, 0, _ifcBuildingStoreyLocalPlacementInstance, ref _ifcWallLocalPlacementInstance);

                        CreateRelDefinesByPropertiesInstance(_ifcWallInstance, CreateWallCommonProperties());

                        if (_settings.IncludeQuantities)
                        {
                            double dOpeningArea = _settings.OpeningIsEnabled ?
                                (dOpeningWidth / _dLinearConversionFactor) * (dOpeningHeight / _dLinearConversionFactor) : 0;

                            CreateRelDefinesByPropertiesInstance(_ifcWallInstance, CreateWallBaseQuantities(
                                dWallThickness,
                                dWallWidth,
                                dWallHeight,
                                dOpeningArea,
                                _dLinearConversionFactor));
                        }

                        CreateRelAssociatesMaterialInstance(_ifcWallInstance, dWallThickness);

                        // Creates a polyline
                        IfcEngine.sdaiAppend(_ifcAggrRepresentations, IfcEngine.sdaiINSTANCE,
                            CreateShapeRepresentationInstance(_ifcGeometricRepresentationContextInstance, IfcRepresentation.AXIS_CURVE2D_REPRESENTATION,
                            0, dWallThickness / 2, dWallWidth, dWallThickness / 2));

                        POLYGON2D polygon = CreatePolygonStructureForSquare(0, 0, dWallWidth, dWallThickness);
                        CreateExtrudedPolygonShape(polygon, dWallHeight, _ifcGeometricRepresentationContextInstance, _ifcAggrRepresentations);
                    } // case IfcBodyRepresentation.ExtrudedPolygon:
                    break;

                case IfcBodyRepresentation.BRep:
                    {
                        _ifcWallInstance = CreateWallInstance(_settings.WallName, 0, 0, 0, _ifcBuildingStoreyLocalPlacementInstance, ref _ifcWallLocalPlacementInstance);

                        CreateRelDefinesByPropertiesInstance(_ifcWallInstance, CreateWallCommonProperties());

                        if (_settings.IncludeQuantities)
                        {
                            double dOpeningArea = _settings.OpeningIsEnabled ?
                                (dOpeningWidth / _dLinearConversionFactor) * (dOpeningHeight / _dLinearConversionFactor) : 0;

                            CreateRelDefinesByPropertiesInstance(_ifcWallInstance, CreateWallBaseQuantities(
                                dWallThickness,
                                dWallWidth,
                                dWallHeight,
                                dOpeningArea,
                                _dLinearConversionFactor));
                        }

                        SHELL shell = null;
                        if ((_settings.View == IfcView.Presentation) && _settings.OpeningIsEnabled)
                        {
                            shell = CreateShellStructureForCuboidWithOpening(0, 0, 0, dWallWidth, dWallThickness, dWallHeight,
                                dOpeningXOffset, dOpeningZOffset, dOpeningXOffset + dOpeningWidth, dOpeningZOffset + dOpeningHeight);
                        }
                        else
                        {
                            shell = CreateShellStructureForCuboid(0, 0, 0, dWallWidth, dWallThickness, dWallHeight);
                        }

                        CreateBRepShape(shell, 0, dWallThickness / 2, dWallWidth, dWallThickness / 2,
                            _ifcGeometricRepresentationContextInstance, _ifcAggrRepresentations);
                    } // case IfcBodyRepresentation.BRep:
                    break;

                case IfcBodyRepresentation.Tessellation:
                    {
                        _ifcWallInstance = CreateWallInstance(_settings.WallName, 0, 0, 0, _ifcBuildingStoreyLocalPlacementInstance, ref _ifcWallLocalPlacementInstance);

                        CreateRelDefinesByPropertiesInstance(_ifcWallInstance, CreateWallCommonProperties());

                        if (_settings.IncludeQuantities)
                        {
                            double dOpeningArea = _settings.OpeningIsEnabled ?
                                (dOpeningWidth / _dLinearConversionFactor) * (dOpeningHeight / _dLinearConversionFactor) : 0;

                            CreateRelDefinesByPropertiesInstance(_ifcWallInstance, CreateWallBaseQuantities(
                                dWallThickness,
                                dWallWidth,
                                dWallHeight,
                                dOpeningArea,
                                _dLinearConversionFactor));
                        }

                        SHELL shell = null;
                        if ((_settings.View == IfcView.Presentation) && _settings.OpeningIsEnabled)
                        {
                            // TODO
                            System.Diagnostics.Debug.Assert(false);
                            shell = CreateShellStructureForCuboidWithOpening(0, 0, 0, dWallWidth, dWallThickness, dWallHeight,
                                dOpeningXOffset, dOpeningZOffset, dOpeningXOffset + dOpeningWidth, dOpeningZOffset + dOpeningHeight);
                        }
                        else
                        {
                            shell = CreateShellStructureForCuboidTessellationMode(0, 0, 0, dWallWidth, dWallThickness, dWallHeight);
                        }

                        CreateTessellationShape(shell, 0, dWallThickness / 2, dWallWidth, dWallThickness / 2,
                            _ifcGeometricRepresentationContextInstance, _ifcAggrRepresentations);
                    } // case IfcBodyRepresentation.Tessellation:
                    break;

                default:
                    throw new Exception("Unknown option.");
            } // switch (_settings.WallBodyRepresentation)

            if (_settings.WallBoundingBox)
            {
                IfcEngine.sdaiAppend(_ifcAggrRepresentations, IfcEngine.sdaiINSTANCE,
                    CreateShapeRepresentationInstance(_ifcGeometricRepresentationContextInstance, IfcRepresentation.BODY_BOUNDINGBOX_REPRESENTATION,
                        dWallWidth, dWallThickness, dWallHeight, "Box"));
            }
        }

        /// <summary>
        /// Creates BaseQuantities: IFCWALL/IFCWALLSTANDARDCASE
        /// </summary>
        private IfcHandle CreateWallBaseQuantities(double dWidth, double dLength, double dHeight, double dOpeningArea, double dLinearConversionFactor)
        {
            IfcHandle ifcQuantities;
            IfcHandle ifcBaseQuantitiesInstance = CreateElementQuantityInstance("BaseQuantities", out ifcQuantities);

            double dGrossSideArea = (dLength / dLinearConversionFactor) * (dHeight / dLinearConversionFactor);
            double dNetSideArea = dGrossSideArea - dOpeningArea;

            IfcEngine.sdaiAppend(ifcQuantities, IfcEngine.sdaiINSTANCE, CreateQuantityLengthInstance("Width", "Width", dWidth));
            IfcEngine.sdaiAppend(ifcQuantities, IfcEngine.sdaiINSTANCE, CreateQuantityLengthInstance("Length", "Length", dLength));
            IfcEngine.sdaiAppend(ifcQuantities, IfcEngine.sdaiINSTANCE, CreateQuantityAreaInstance("GrossFootprintArea", "GrossFootprintArea", (dLength / dLinearConversionFactor) * (dWidth / dLinearConversionFactor)));
            IfcEngine.sdaiAppend(ifcQuantities, IfcEngine.sdaiINSTANCE, CreateQuantityAreaInstance("NetFootprintArea", "NetFootprintArea", (dLength / dLinearConversionFactor) * (dWidth / dLinearConversionFactor)));
            IfcEngine.sdaiAppend(ifcQuantities, IfcEngine.sdaiINSTANCE, CreateQuantityAreaInstance("GrossSideArea", "GrossSideArea", dGrossSideArea));
            IfcEngine.sdaiAppend(ifcQuantities, IfcEngine.sdaiINSTANCE, CreateQuantityAreaInstance("NetSideArea", "NetSideArea", dNetSideArea));
            IfcEngine.sdaiAppend(ifcQuantities, IfcEngine.sdaiINSTANCE, CreateQuantityVolumeInstance("GrossVolume", "GrossVolume", dGrossSideArea * (dWidth / dLinearConversionFactor)));
            IfcEngine.sdaiAppend(ifcQuantities, IfcEngine.sdaiINSTANCE, CreateQuantityVolumeInstance("NetVolume", "NetVolume", dNetSideArea * (dWidth / dLinearConversionFactor)));
            IfcEngine.sdaiAppend(ifcQuantities, IfcEngine.sdaiINSTANCE, CreateQuantityLengthInstance("Height", "Height", dHeight));

            return ifcBaseQuantitiesInstance;
        }

        /// <summary>
        /// Wall - common properties
        /// </summary>
        private IfcHandle CreateWallCommonProperties()
        {
            IfcHandle ifcAggrHasProperties = 0;
            IfcHandle ifcPropertySetInstance = CreatePropertySetInstance("Pset_WallCommon", _ifcOwnerHistoryInstance, ref ifcAggrHasProperties);

            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("Reference", "Reference", "", "IFCIDENTIFIER"));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("AcousticRating", "AcousticRating", "", "IFCLABEL"));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("FireRating", "FireRating", "", "IFCLABEL"));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("Combustible", "Combustible", false));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("SurfaceSpreadOfFlame", "SurfaceSpreadOfFlame", "", "IFCLABEL"));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("ThermalTransmittance", "ThermalTransmittance", 0.24, "IFCTHERMALTRANSMITTANCEMEASURE"));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("IsExternal", "IsExternal", true));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("ExtendToStructure", "ExtendToStructure", false));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("LoadBearing", "LoadBearing", false));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("Compartmentation", "Compartmentation", false));

            return ifcPropertySetInstance;
        }

        /// <summary>
        /// Creates IFCWALLSTANDARDCASE
        /// </summary>
        private IfcHandle CreateWallStandardCaseInstance(string strWallName, double dXOffset, double dYOffset, double dZOffset, IfcHandle ifcPlacementRelativeTo, ref IfcHandle ifcWallLocalPlacement)
        {
            IfcHandle ifcWallStandardCaseInstance = CreateInstance("IFCWALLSTANDARDCASE");

            IfcEngine.sdaiPutAttrBN(ifcWallStandardCaseInstance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
            IfcEngine.sdaiPutAttrBN(ifcWallStandardCaseInstance, "OwnerHistory", IfcEngine.sdaiINSTANCE, _ifcOwnerHistoryInstance);
            IfcEngine.sdaiPutAttrBN(ifcWallStandardCaseInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strWallName));
            IfcEngine.sdaiPutAttrBN(ifcWallStandardCaseInstance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Description of Wall"));

            MATRIX matrix = MATRIX.IdentityMatrix();
            matrix._d41 = dXOffset;
            matrix._d42 = dYOffset;
            matrix._d43 = dZOffset;
            ifcWallLocalPlacement = CreateLocalPlacementInstance(matrix, ifcPlacementRelativeTo);

            IfcEngine.sdaiPutAttrBN(ifcWallStandardCaseInstance, "ObjectPlacement", IfcEngine.sdaiINSTANCE, ifcWallLocalPlacement);
            IfcEngine.sdaiPutAttrBN(ifcWallStandardCaseInstance, "Representation", IfcEngine.sdaiINSTANCE, CreateProductDefinitionShape());

            CreateWallType(ifcWallStandardCaseInstance, _settings.WallName, "STANDARD");

            IfcEngine.sdaiPutAttrBN(ifcWallStandardCaseInstance, "PredefinedType", IfcEngine.sdaiENUM, "STANDARD");

            IfcEngine.sdaiAppend(_ifcAggrRelatedElements, IfcEngine.sdaiINSTANCE, ifcWallStandardCaseInstance);

            return ifcWallStandardCaseInstance;
        }

        /// <summary>
        /// Creates IFCWALL
        /// </summary>
        private IfcHandle CreateWallInstance(string strWallName, double dXOffset, double dYOffset, double dZOffset, IfcHandle ifcPlacementRelativeTo, ref IfcHandle ifcWallLocalPlacement)
        {
            IfcHandle ifcWallInstance = CreateInstance("IFCWALL");

            IfcEngine.sdaiPutAttrBN(ifcWallInstance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
            IfcEngine.sdaiPutAttrBN(ifcWallInstance, "OwnerHistory", IfcEngine.sdaiINSTANCE, _ifcOwnerHistoryInstance);
            IfcEngine.sdaiPutAttrBN(ifcWallInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strWallName));
            IfcEngine.sdaiPutAttrBN(ifcWallInstance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Description of Wall"));

            MATRIX matrix = MATRIX.IdentityMatrix();
            matrix._d41 = dXOffset;
            matrix._d42 = dYOffset;
            matrix._d43 = dZOffset;
            ifcWallLocalPlacement = CreateLocalPlacementInstance(matrix, ifcPlacementRelativeTo);

            IfcEngine.sdaiPutAttrBN(ifcWallInstance, "ObjectPlacement", IfcEngine.sdaiINSTANCE, ifcWallLocalPlacement);
            IfcEngine.sdaiPutAttrBN(ifcWallInstance, "Representation", IfcEngine.sdaiINSTANCE, CreateProductDefinitionShape());

            CreateWallType(ifcWallInstance, _settings.WallName, "STANDARD");

            IfcEngine.sdaiPutAttrBN(ifcWallInstance, "PredefinedType", IfcEngine.sdaiENUM, "STANDARD");

            IfcEngine.sdaiAppend(_ifcAggrRelatedElements, IfcEngine.sdaiINSTANCE, ifcWallInstance);

            return ifcWallInstance;
        }

        /// <summary>
        /// Creates IFCWALLTYPE
        /// </summary>
        private IfcHandle CreateWallType(IfcHandle ifcWallInstance, string strWallName, string strPedefinedType)
        {
            IfcHandle ifcWallTypeInstance = CreateInstance("IFCWALLTYPE");

            IfcEngine.sdaiPutAttrBN(ifcWallTypeInstance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
            IfcEngine.sdaiPutAttrBN(ifcWallTypeInstance, "OwnerHistory", IfcEngine.sdaiINSTANCE, _ifcOwnerHistoryInstance);
            IfcEngine.sdaiPutAttrBN(ifcWallTypeInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strWallName));
	        IfcEngine.sdaiPutAttrBN(ifcWallTypeInstance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Description of Wall Type"));
            IfcEngine.sdaiPutAttrBN(ifcWallTypeInstance, "PredefinedType", IfcEngine.sdaiENUM, strPedefinedType);

            CreateRelDefinesByType(ifcWallInstance, ifcWallTypeInstance);

            return ifcWallTypeInstance;
        }

        #endregion // Wall

        #region Opening

        /// <summary>
        /// Builds an opening
        /// </summary>
        private void CreateOpening()
        {
            double dWallThickness = _settings.WallThickness * 0.001 * _dLinearConversionFactor;
            double dOpeningXOffset = _settings.OpeningXOffset * 0.001 * _dLinearConversionFactor;
            double dOpeningZOffset = _settings.OpeningZOffset * 0.001 * _dLinearConversionFactor;
            double dOpeningHeight = _settings.OpeningHeight * 0.001 * _dLinearConversionFactor;
            double dOpeningWidth = _settings.OpeningWidth * 0.001 * _dLinearConversionFactor;

            MATRIX matrix = MATRIX.IdentityMatrix();
            matrix._d41 = dOpeningXOffset;
            matrix._d42 = 0;
            matrix._d43 = dOpeningZOffset;

            _ifcOpeningElementInstance = CreateOpeningElementInstance(matrix, _ifcWallLocalPlacementInstance, _settings.OpeningName,
                _settings.View == IfcView.Coordination, ref _ifcOpeningLocalPlacementInstance);

            if (_settings.IncludeQuantities)
            {
                CreateRelDefinesByPropertiesInstance(_ifcOpeningElementInstance, CreateOpeningBaseQuantities(dWallThickness, dOpeningHeight, dOpeningWidth));
            }

            CreateRelVoidsElementInstance(_ifcWallInstance, _ifcOpeningElementInstance);

            if (_settings.View == IfcView.Coordination)
            {
                switch (_settings.OpeningBodyRepresentation)
                {
                    case IfcBodyRepresentation.ExtrudedPolygon:
                        {
                            POLYGON2D polygon = CreatePolygonStructureForSquare(0, 0, dOpeningWidth, dWallThickness);
                            CreateExtrudedPolygonShape(polygon, dOpeningHeight, _ifcGeometricRepresentationContextInstance, _ifcAggrRepresentations);

                            CreateRelAssociatesMaterialInstance(_ifcOpeningElementInstance);
                        }
                        break;

                    case IfcBodyRepresentation.BRep:
                        {
                            SHELL shell = CreateShellStructureForCuboid(0, 0, 0, dOpeningWidth, dWallThickness, dOpeningHeight);
                            CreateBRepShape(shell, _ifcGeometricRepresentationContextInstance, _ifcAggrRepresentations);
                        }
                        break;

                    default:
                        throw new Exception("Unknown option.");
                }
            } // if (_settings.View == IfcView.Coordination)

            if (_settings.OpeningBoundingBox && (_settings.View == IfcView.Coordination))
            {
                IfcEngine.sdaiAppend(_ifcAggrRepresentations, IfcEngine.sdaiINSTANCE,
                    CreateShapeRepresentationInstance(_ifcGeometricRepresentationContextInstance, IfcRepresentation.BODY_BOUNDINGBOX_REPRESENTATION,
                        dOpeningWidth, dWallThickness, dOpeningHeight, "Box"));
            }
        }

        /// <summary>
        /// Creates BaseQuantities
        /// </summary>
        private IfcHandle CreateOpeningBaseQuantities(double dDepth, double dHeight, double dWidth)
        {
            IfcHandle ifcQuantities;
            IfcHandle ifcBaseQuantitiesInstance = CreateElementQuantityInstance("BaseQuantities", out ifcQuantities);

            IfcEngine.sdaiAppend(ifcQuantities, IfcEngine.sdaiINSTANCE, CreateQuantityLengthInstance("Depth", "Depth", dDepth));
            IfcEngine.sdaiAppend(ifcQuantities, IfcEngine.sdaiINSTANCE, CreateQuantityLengthInstance("Height", "Height", dHeight));
            IfcEngine.sdaiAppend(ifcQuantities, IfcEngine.sdaiINSTANCE, CreateQuantityLengthInstance("Width", "Width", dWidth));

            return ifcBaseQuantitiesInstance;
        }

        /// <summary>
        /// Creates IFCOPENINGELEMENT
        /// </summary>
        /// <returns></returns>
        private IfcHandle CreateOpeningElementInstance(MATRIX matrix, IfcHandle ifcPlacementRelativeTo, string strName, bool bRepresentation, ref IfcHandle ifcOpeningElementInstancePlacement)
        {
            IfcHandle ifcOpeningElementInstance = CreateInstance("IFCOPENINGELEMENT");

            IfcEngine.sdaiPutAttrBN(ifcOpeningElementInstance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
            IfcEngine.sdaiPutAttrBN(ifcOpeningElementInstance, "OwnerHistory", IfcEngine.sdaiINSTANCE, _ifcOwnerHistoryInstance);
            IfcEngine.sdaiPutAttrBN(ifcOpeningElementInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strName));
            IfcEngine.sdaiPutAttrBN(ifcOpeningElementInstance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Description of Opening"));
            IfcEngine.sdaiPutAttrBN(ifcOpeningElementInstance, "PredefinedType", IfcEngine.sdaiENUM, "OPENING");

            ifcOpeningElementInstancePlacement = CreateLocalPlacementInstance(matrix, ifcPlacementRelativeTo);
            IfcEngine.sdaiPutAttrBN(ifcOpeningElementInstance, "ObjectPlacement", IfcEngine.sdaiINSTANCE, ifcOpeningElementInstancePlacement);

            if (bRepresentation)
            {
                IfcEngine.sdaiPutAttrBN(ifcOpeningElementInstance, "Representation", IfcEngine.sdaiINSTANCE, CreateProductDefinitionShape());
            }

            return ifcOpeningElementInstance;
        }

        #endregion // Opening

        #region Window

        /// <summary>
        /// Builds an window
        /// </summary>
        private void CreateWindow()
        {
            double dWindowThickness = _settings.WindowThickness * 0.001 * _dLinearConversionFactor;
            double dWindowYOffset = _settings.WindowYOffset * 0.001 * _dLinearConversionFactor;
            double dOpeningHeight = _settings.OpeningHeight * 0.001 * _dLinearConversionFactor;
            double dOpeningWidth = _settings.OpeningWidth * 0.001 * _dLinearConversionFactor;
            double dWindowHeight = _settings.WindowHeight * 0.001 * _dLinearConversionFactor;
            double dWindowWidth = _settings.WindowWidth * 0.001 * _dLinearConversionFactor;

            MATRIX matrix = MATRIX.IdentityMatrix();
            matrix._d41 = 0;
            matrix._d42 = dWindowYOffset;
            matrix._d43 = 0;

            IfcHandle ifcWindowInstance = 0;
            IfcHandle ifcWindowLocalPlacementInstance = 0;

            if (_settings.WallIsEnabled && _settings.OpeningIsEnabled)
            {
                ifcWindowInstance = CreateWindowInstance(matrix, _ifcOpeningLocalPlacementInstance, _settings.WindowName,
                    dWindowHeight, dWindowWidth, ref ifcWindowLocalPlacementInstance);

                IfcEngine.sdaiAppend(_ifcAggrRelatedElements, IfcEngine.sdaiINSTANCE, ifcWindowInstance); 

                CreateRelFillsElementInstance(_ifcOpeningElementInstance, ifcWindowInstance);
            }
            else
            {
                matrix._d42 = 0;

                ifcWindowInstance = CreateWindowInstance(matrix, _ifcBuildingStoreyLocalPlacementInstance, _settings.WindowName,
                    dWindowHeight, dWindowWidth, ref ifcWindowLocalPlacementInstance);

                IfcEngine.sdaiAppend(_ifcAggrRelatedElements, IfcEngine.sdaiINSTANCE, ifcWindowInstance); 
            }          

            CreateRelDefinesByPropertiesInstance(ifcWindowInstance, CreateWindowCommonProperties());

            if (_settings.IncludeQuantities)
            {
                CreateRelDefinesByPropertiesInstance(ifcWindowInstance, CreateWindowBaseQuantities(dOpeningHeight, dOpeningWidth));
            }

            switch (_settings.WindowBodyRepresentation)
            {
                case IfcBodyRepresentation.ExtrudedPolygon:
                    {
                        POLYGON2D polygon = CreatePolygonStructureForSquare(0, 0, dOpeningWidth, dWindowThickness);
                        CreateExtrudedPolygonShape(polygon, dOpeningHeight, _ifcGeometricRepresentationContextInstance, _ifcAggrRepresentations);
                    }
                    break;

                case IfcBodyRepresentation.BRep:
                    {
                        SHELL shell = CreateShellStructureForCuboid(0, 0, 0, dOpeningWidth, dWindowThickness, dOpeningHeight);
                        CreateBRepShape(shell, _ifcGeometricRepresentationContextInstance, _ifcAggrRepresentations);
                    }
                    break;

                default:
                    throw new Exception("Unknown option.");
            }

            if (_settings.WindowBoundingBox)
            {
                IfcEngine.sdaiAppend(_ifcAggrRepresentations, IfcEngine.sdaiINSTANCE,
                    CreateShapeRepresentationInstance(_ifcGeometricRepresentationContextInstance, IfcRepresentation.BODY_BOUNDINGBOX_REPRESENTATION,
                        dOpeningWidth, dWindowThickness, dOpeningHeight, "Box"));
            }
        }

        /// <summary>
        /// Creates BaseQuantities
        /// </summary>
        private IfcHandle CreateWindowBaseQuantities(double dHeight, double dWidth)
        {
            IfcHandle ifcQuantities;
            IfcHandle ifcBaseQuantitiesInstance = CreateElementQuantityInstance("BaseQuantities", out ifcQuantities);

            IfcEngine.sdaiAppend(ifcQuantities, IfcEngine.sdaiINSTANCE, CreateQuantityLengthInstance("Height", "Height", dHeight));
            IfcEngine.sdaiAppend(ifcQuantities, IfcEngine.sdaiINSTANCE, CreateQuantityLengthInstance("Width", "Width", dWidth));

            return ifcBaseQuantitiesInstance;
        }

        /// <summary>
        /// Window - common properties
        /// </summary>
        private IfcHandle CreateWindowCommonProperties()
        {
            IfcHandle ifcAggrHasProperties = 0;
            IfcHandle ifcPropertySetInstance = CreatePropertySetInstance("Pset_WindowCommon", _ifcOwnerHistoryInstance, ref ifcAggrHasProperties);

            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("Reference", "Reference", "", "IFCIDENTIFIER"));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("FireRating", "FireRating", "", "IFCLABEL"));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("AcousticRating", "AcousticRating", "", "IFCLABEL"));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("SecurityRating", "SecurityRating", "", "IFCLABEL"));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("IsExternal", "IsExternal", true));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("Infiltration", "Infiltration", 0.3, "IFCVOLUMETRICFLOWRATEMEASURE"));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("ThermalTransmittance", "ThermalTransmittance", 0.24, "IFCTHERMALTRANSMITTANCEMEASURE"));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("GlazingAreaFraction", "GlazingAreaFraction", 0.7, "IFCPOSITIVERATIOMEASURE"));
            IfcEngine.sdaiAppend(ifcAggrHasProperties, IfcEngine.sdaiINSTANCE, CreatePropertySingleValueInstance("SmokeStop", "SmokeStop", false));

            return ifcPropertySetInstance;
        }

        /// <summary>
        /// Creates IFCWINDOW
        /// </summary>
        /// <returns></returns>
        private IfcHandle CreateWindowInstance(MATRIX matrix, IfcHandle ifcPlacementRelativeTo, string strName, double dOverallHeight, double dOverallWidth, ref IfcHandle ifcWindowInstancePlacement)
        {
            IfcHandle ifcWindowInstance = CreateInstance("IFCWINDOW");

            IfcEngine.sdaiPutAttrBN(ifcWindowInstance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
            IfcEngine.sdaiPutAttrBN(ifcWindowInstance, "OwnerHistory", IfcEngine.sdaiINSTANCE, _ifcOwnerHistoryInstance);
            IfcEngine.sdaiPutAttrBN(ifcWindowInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strName));
            IfcEngine.sdaiPutAttrBN(ifcWindowInstance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Description of Window"));

            ifcWindowInstancePlacement = CreateLocalPlacementInstance(matrix, ifcPlacementRelativeTo);

            IfcEngine.sdaiPutAttrBN(ifcWindowInstance, "ObjectPlacement", IfcEngine.sdaiINSTANCE, ifcWindowInstancePlacement);
            IfcEngine.sdaiPutAttrBN(ifcWindowInstance, "Representation", IfcEngine.sdaiINSTANCE, CreateProductDefinitionShape());

            IfcEngine.sdaiPutAttrBN(ifcWindowInstance, "PredefinedType", IfcEngine.sdaiENUM, "WINDOW");
            IfcEngine.sdaiPutAttrBN(ifcWindowInstance, "PartitioningType", IfcEngine.sdaiENUM, "SINGLE_PANEL");

            IfcEngine.sdaiPutAttrBN(ifcWindowInstance, "OverallHeight", IfcEngine.sdaiREAL, ref dOverallHeight);
            IfcEngine.sdaiPutAttrBN(ifcWindowInstance, "OverallWidth", IfcEngine.sdaiREAL, ref dOverallWidth);

            return ifcWindowInstance;
        }

        #endregion // Window

        #region Common

        /// <summary>
        /// Creates a header
        /// </summary>
        private void CreateHeader()
        {
            string strDescription = "ViewDefinition ";
            strDescription += "[";
            strDescription += _settings.View == IfcView.Coordination ? "CoordinationView" : "PresentationView";
            strDescription += _settings.IncludeQuantities ? ", QuantityTakeOffAddOnView" : "";
            strDescription += "]";

            IfcEngine.SetSPFFHeaderItem(this.ModelInstance, 0, 0, IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strDescription));
            IfcEngine.SetSPFFHeaderItem(this.ModelInstance, 0, 1, IfcEngine.sdaiSTRING, string.Empty);
            IfcEngine.SetSPFFHeaderItem(this.ModelInstance, 1, 0, IfcEngine.sdaiSTRING, "2;1");
            IfcEngine.SetSPFFHeaderItem(this.ModelInstance, 2, 0, IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(Path.GetFileName(_settings.OutputFile)));
            IfcEngine.SetSPFFHeaderItem(this.ModelInstance, 3, 0, IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CreateTimeStamp()));
            IfcEngine.SetSPFFHeaderItem(this.ModelInstance, 4, 0, IfcEngine.sdaiSTRING, "Architect");
            IfcEngine.SetSPFFHeaderItem(this.ModelInstance, 4, 1, IfcEngine.sdaiSTRING, string.Empty);
            IfcEngine.SetSPFFHeaderItem(this.ModelInstance, 5, 0, IfcEngine.sdaiSTRING, "Building Designer Office");
            IfcEngine.SetSPFFHeaderItem(this.ModelInstance, 6, 0, IfcEngine.sdaiSTRING, "IFC Engine DLL 2015");
            IfcEngine.SetSPFFHeaderItem(this.ModelInstance, 7, 0, IfcEngine.sdaiSTRING, "Hello Wall example");
            IfcEngine.SetSPFFHeaderItem(this.ModelInstance, 8, 0, IfcEngine.sdaiSTRING, "The authorising person");
            IfcEngine.SetSPFFHeaderItem(this.ModelInstance, 9, 0, IfcEngine.sdaiSTRING, IfcSchemaFile.GetVersionAsString(_settings.SchemaFile));
            IfcEngine.SetSPFFHeaderItem(this.ModelInstance, 9, 1, IfcEngine.sdaiSTRING, string.Empty);
        }

        /// <summary>
        /// Creates IFCAPPLICATION
        /// </summary>
        private IfcHandle CreateApplicationInstance()
        {
            IfcHandle ifcApplicationInstance = CreateInstance("IFCAPPLICATION", (instance) =>
            {
                IfcEngine.sdaiPutAttrBN(instance, "ApplicationDeveloper", IfcEngine.sdaiINSTANCE, _ifcOrganizationInstance);
                IfcEngine.sdaiPutAttrBN(instance, "Version", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("0.10"));
                IfcEngine.sdaiPutAttrBN(instance, "ApplicationFullName", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Test Application"));
                IfcEngine.sdaiPutAttrBN(instance, "ApplicationIdentifier", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("TA 1001"));
            });

            return ifcApplicationInstance;
        }

        /// <summary>
        /// Creates IFCRELDEFINESBYTYPE
        /// </summary>
        private IfcHandle CreateRelDefinesByType(IfcHandle ifcRelatedObjectInstance, IfcHandle ifcRelatingTypeInstance)
        {
            IfcHandle ifcRelDefinesByTypeInstance = CreateInstance("IFCRELDEFINESBYTYPE");

            IfcEngine.sdaiPutAttrBN(ifcRelDefinesByTypeInstance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
            IfcEngine.sdaiPutAttrBN(ifcRelDefinesByTypeInstance, "OwnerHistory", IfcEngine.sdaiINSTANCE, _ifcOwnerHistoryInstance);

            IfcHandle ifcAggrRelatedObjects = IfcEngine.sdaiCreateAggrBN(ifcRelDefinesByTypeInstance, "RelatedObjects");
            IfcEngine.sdaiAppend(ifcAggrRelatedObjects, IfcEngine.sdaiINSTANCE, ifcRelatedObjectInstance);

            IfcEngine.sdaiPutAttrBN(ifcRelDefinesByTypeInstance, "RelatingType", IfcEngine.sdaiINSTANCE, ifcRelatingTypeInstance);

            return ifcRelDefinesByTypeInstance;
        }

        /// <summary>
        /// Creates IFCPRODUCTDEFINITIONSHAPE
        /// </summary>
        private IfcHandle CreateProductDefinitionShape()
        {
            IfcHandle ifcProductDefinitionShapeInstance = CreateInstance("IFCPRODUCTDEFINITIONSHAPE");

            _ifcAggrRepresentations = IfcEngine.sdaiCreateAggrBN(ifcProductDefinitionShapeInstance, "Representations");

            return ifcProductDefinitionShapeInstance;
        }
     
        /// <summary>
        /// Creates IFCPOSTALADDRESS
        /// </summary>
        private IfcHandle CreatePostalAddress()
        {
            IfcHandle ifcPostalAddressInstance = CreateInstance("IFCPOSTALADDRESS");

            IfcHandle ifcAddressLines = IfcEngine.sdaiCreateAggrBN(ifcPostalAddressInstance, "AddressLines");
            IfcEngine.sdaiAppend(ifcAddressLines, IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("RDF Ltd."));
            IfcEngine.sdaiAppend(ifcAddressLines, IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Main Office"));
            IfcEngine.sdaiPutAttrBN(ifcPostalAddressInstance, "PostalBox", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("32"));
		    IfcEngine.sdaiPutAttrBN(ifcPostalAddressInstance, "Town", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Bankya"));
		    IfcEngine.sdaiPutAttrBN(ifcPostalAddressInstance, "Region", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Sofia"));
		    IfcEngine.sdaiPutAttrBN(ifcPostalAddressInstance, "PostalCode", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("1320"));
		    IfcEngine.sdaiPutAttrBN(ifcPostalAddressInstance, "Country", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Bulgaria"));

            return ifcPostalAddressInstance;
        }

        /// <summary>
        /// Creates IFCRELAGGREGATES
        /// </summary>
        private void CreateRelAggregates(string strName, string strDescription, IfcHandle ifcRelatingObjectInstance, IfcHandle ifcRelatedObjectInstance)
        {
            IfcHandle ifcRelAggregatesInstance = CreateInstance("IFCRELAGGREGATES");

            IfcEngine.sdaiPutAttrBN(ifcRelAggregatesInstance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
            IfcEngine.sdaiPutAttrBN(ifcRelAggregatesInstance, "OwnerHistory", IfcEngine.sdaiINSTANCE, _ifcOwnerHistoryInstance);
            IfcEngine.sdaiPutAttrBN(ifcRelAggregatesInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strName));
            IfcEngine.sdaiPutAttrBN(ifcRelAggregatesInstance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strDescription));
            IfcEngine.sdaiPutAttrBN(ifcRelAggregatesInstance, "RelatingObject", IfcEngine.sdaiINSTANCE, ifcRelatingObjectInstance);

            IfcHandle ifcAggrRelatedObjects = IfcEngine.sdaiCreateAggrBN(ifcRelAggregatesInstance, "RelatedObjects");
            IfcEngine.sdaiAppend(ifcAggrRelatedObjects, IfcEngine.sdaiINSTANCE, ifcRelatedObjectInstance);
        }

        /// <summary>
        /// Creates IFCRELCONTAINEDINSPATIALSTRUCTURE
        /// </summary>
        private void CreateRelContainedInSpatialStructure(string strName, string strDescription, IfcHandle ifcRelatingObjectInstance, ref IfcHandle ifcAggrRelatedElements)
        {
            IfcHandle ifcRelContainedInSpatialStructureInstance = CreateInstance("IFCRELCONTAINEDINSPATIALSTRUCTURE");

	        IfcEngine.sdaiPutAttrBN(ifcRelContainedInSpatialStructureInstance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
            IfcEngine.sdaiPutAttrBN(ifcRelContainedInSpatialStructureInstance, "OwnerHistory", IfcEngine.sdaiINSTANCE, _ifcOwnerHistoryInstance);
	        IfcEngine.sdaiPutAttrBN(ifcRelContainedInSpatialStructureInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Default Building"));
	        IfcEngine.sdaiPutAttrBN(ifcRelContainedInSpatialStructureInstance, "Description", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("Contents of Building Storey"));

            ifcAggrRelatedElements = IfcEngine.sdaiCreateAggrBN(ifcRelContainedInSpatialStructureInstance, "RelatedElements");
            IfcEngine.sdaiPutAttrBN(ifcRelContainedInSpatialStructureInstance, "RelatingStructure", IfcEngine.sdaiINSTANCE, ifcRelatingObjectInstance);
        }

        /// <summary>
        /// Creates IFCRELDEFINESBYPROPERTIES
        /// </summary>
        private IfcHandle CreateRelDefinesByPropertiesInstance(IfcHandle ifcRelatedObject, IfcHandle ifcRelatingPropertyDefinition)
        {
            IfcHandle ifcRelDefinesByPropertiesInstance = CreateInstance("IFCRELDEFINESBYPROPERTIES");

            IfcEngine.sdaiPutAttrBN(ifcRelDefinesByPropertiesInstance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
            IfcEngine.sdaiPutAttrBN(ifcRelDefinesByPropertiesInstance, "OwnerHistory", IfcEngine.sdaiINSTANCE, _ifcOwnerHistoryInstance);

            IfcHandle ifcAggrRelatedObjects = IfcEngine.sdaiCreateAggrBN(ifcRelDefinesByPropertiesInstance, "RelatedObjects");
            IfcEngine.sdaiAppend(ifcAggrRelatedObjects, IfcEngine.sdaiINSTANCE, ifcRelatedObject);

            IfcEngine.sdaiPutAttrBN(ifcRelDefinesByPropertiesInstance, "RelatingPropertyDefinition", IfcEngine.sdaiINSTANCE, ifcRelatingPropertyDefinition);

            return ifcRelDefinesByPropertiesInstance;
        }

        /// <summary>
        /// Creates IFCRELFILLSELEMENT
        /// </summary>
        private IfcHandle CreateRelFillsElementInstance(IfcHandle ifcOpeningElementInstance, IfcHandle ifcBuildingElementInstance)
        {
            IfcHandle ifcRelFillsElementInstance = CreateInstance("IFCRELFILLSELEMENT");

            IfcEngine.sdaiPutAttrBN(ifcRelFillsElementInstance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
            IfcEngine.sdaiPutAttrBN(ifcRelFillsElementInstance, "OwnerHistory", IfcEngine.sdaiINSTANCE, _ifcOwnerHistoryInstance);

            IfcEngine.sdaiPutAttrBN(ifcRelFillsElementInstance, "RelatingOpeningElement", IfcEngine.sdaiINSTANCE, ifcOpeningElementInstance);
            IfcEngine.sdaiPutAttrBN(ifcRelFillsElementInstance, "RelatedBuildingElement", IfcEngine.sdaiINSTANCE, ifcBuildingElementInstance);

            return ifcRelFillsElementInstance;
        }

        /// <summary>
        /// Creates IFCELEMENTQUANTITY
        /// </summary>
        private IfcHandle CreateElementQuantityInstance(string strName, out IfcHandle ifcQuantities)
        {
            IfcHandle ifcElementQuantityInstance = CreateInstance("IFCELEMENTQUANTITY");

            IfcEngine.sdaiPutAttrBN(ifcElementQuantityInstance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
            IfcEngine.sdaiPutAttrBN(ifcElementQuantityInstance, "OwnerHistory", IfcEngine.sdaiINSTANCE, _ifcOwnerHistoryInstance);
            IfcEngine.sdaiPutAttrBN(ifcElementQuantityInstance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(strName));

            ifcQuantities = IfcEngine.sdaiCreateAggrBN(ifcElementQuantityInstance, "Quantities");

            return ifcElementQuantityInstance;
        }

        /// <summary>
        /// Creates IFCRELASSOCIATESMATERIAL
        /// </summary>
        private IfcHandle CreateRelAssociatesMaterialInstance(IfcHandle ifcBuildingElementInstance)
        {
            IfcHandle ifcRelAssociatesMaterialInstance = CreateInstance("IFCRELASSOCIATESMATERIAL");

            IfcEngine.sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
            IfcEngine.sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "OwnerHistory", IfcEngine.sdaiINSTANCE, _ifcOwnerHistoryInstance);

            IfcHandle ifcRelatedObjects = IfcEngine.sdaiCreateAggrBN(ifcRelAssociatesMaterialInstance, "RelatedObjects");
            IfcEngine.sdaiAppend(ifcRelatedObjects, IfcEngine.sdaiINSTANCE, ifcBuildingElementInstance);

            IfcEngine.sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "RelatingMaterial", IfcEngine.sdaiINSTANCE, CreateMaterialConstituentSetInstance());

            return ifcRelAssociatesMaterialInstance;
        }

        /// <summary>
        /// Creates IFCRELASSOCIATESMATERIAL
        /// </summary>
        private IfcHandle CreateRelAssociatesMaterialInstance(IfcHandle ifcBuildingElementInstance, double dThickness)
        {
            IfcHandle ifcRelAssociatesMaterialInstance = CreateInstance("IFCRELASSOCIATESMATERIAL");

            IfcEngine.sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
            IfcEngine.sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "OwnerHistory", IfcEngine.sdaiINSTANCE, _ifcOwnerHistoryInstance);

            IfcHandle ifcRelatedObjects = IfcEngine.sdaiCreateAggrBN(ifcRelAssociatesMaterialInstance, "RelatedObjects");
            IfcEngine.sdaiAppend(ifcRelatedObjects, IfcEngine.sdaiINSTANCE, ifcBuildingElementInstance);

            IfcEngine.sdaiPutAttrBN(ifcRelAssociatesMaterialInstance, "RelatingMaterial", IfcEngine.sdaiINSTANCE, CreateMaterialLayerSetUsageInstance(dThickness));

            return ifcRelAssociatesMaterialInstance;
        }

        /// <summary>
        /// Creates IFCUNITASSIGNMENT
        /// </summary>
        private IfcHandle CreateUnitAssignmentInstance()
        {
            IfcHandle ifcUnitAssignmentInstance = CreateInstance("IFCUNITASSIGNMENT", (instance) =>
            {
                IfcHandle ifcAggrUnits = IfcEngine.sdaiCreateAggrBN(instance, "Units");
                if (ifcAggrUnits == 0)
                {
                    throw new Exception("Can't create units.");
                }

                // LENGTHUNIT
                {
                    IfcHandle ifcUnit = CreateSIUnitInstance("LENGTHUNIT", _settings.UseMeters ? string.Empty : "MILLI", "METRE", 0);
                    IfcEngine.sdaiAppend(ifcAggrUnits, IfcEngine.sdaiINSTANCE, ifcUnit);
                }

                // AREAUNIT
                {
                    IfcHandle ifcUnit = CreateSIUnitInstance("AREAUNIT", string.Empty, "SQUARE_METRE", 0);
                    IfcEngine.sdaiAppend(ifcAggrUnits, IfcEngine.sdaiINSTANCE, ifcUnit);
                }

                // VOLUMEUNIT
                {
                    IfcHandle ifcUnit = CreateSIUnitInstance("VOLUMEUNIT", string.Empty, "CUBIC_METRE", 0);
                    IfcEngine.sdaiAppend(ifcAggrUnits, IfcEngine.sdaiINSTANCE, ifcUnit);
                }

                IfcEngine.sdaiAppend(ifcAggrUnits, IfcEngine.sdaiINSTANCE, ref _ifcConversionBasedUnitInstance);

                // SOLIDANGLEUNIT
                {
                    IfcHandle ifcUnit = CreateSIUnitInstance("SOLIDANGLEUNIT", string.Empty, "STERADIAN", 0);
                    IfcEngine.sdaiAppend(ifcAggrUnits, IfcEngine.sdaiINSTANCE, ifcUnit);
                }

                // MASSUNIT
                {
                    IfcHandle ifcUnit = CreateSIUnitInstance("MASSUNIT", string.Empty, "GRAM", 0);
                    IfcEngine.sdaiAppend(ifcAggrUnits, IfcEngine.sdaiINSTANCE, ifcUnit);
                }

                // TIMEUNIT
                {
                    IfcHandle ifcUnit = CreateSIUnitInstance("TIMEUNIT", string.Empty, "SECOND", 0);
                    IfcEngine.sdaiAppend(ifcAggrUnits, IfcEngine.sdaiINSTANCE, ifcUnit);
                }

                // THERMODYNAMICTEMPERATUREUNIT
                {
                    IfcHandle ifcUnit = CreateSIUnitInstance("THERMODYNAMICTEMPERATUREUNIT", string.Empty, "DEGREE_CELSIUS", 0);
                    IfcEngine.sdaiAppend(ifcAggrUnits, IfcEngine.sdaiINSTANCE, ifcUnit);
                }

                // LUMINOUSINTENSITYUNIT
                {
                    IfcHandle ifcUnit = CreateSIUnitInstance("LUMINOUSINTENSITYUNIT", string.Empty, "LUMEN", 0);
                    IfcEngine.sdaiAppend(ifcAggrUnits, IfcEngine.sdaiINSTANCE, ifcUnit);
                }
            });

            return ifcUnitAssignmentInstance;
        }

        /// <summary>
        /// Creates IFCDIMENSIONALEXPONENTS
        /// </summary>
        private IfcHandle CreateDimensionalExponentsInstance()
        {
            IfcHandle ifcDimensionalExponentsInstance = CreateInstance("IFCDIMENSIONALEXPONENTS", (instance) =>
            {
                IfcHandle ifcLengthExponent = 0;
                IfcEngine.sdaiPutAttrBN(instance, "LengthExponent", IfcEngine.sdaiINTEGER, ref ifcLengthExponent);

                IfcHandle ifcMassExponent = 0;
                IfcEngine.sdaiPutAttrBN(instance, "MassExponent", IfcEngine.sdaiINTEGER, ref ifcMassExponent);

                IfcHandle ifcTimeExponent = 0;
                IfcEngine.sdaiPutAttrBN(instance, "TimeExponent", IfcEngine.sdaiINTEGER, ref ifcTimeExponent);

                IfcHandle ifcElectricCurrentExponent = 0;
                IfcEngine.sdaiPutAttrBN(instance, "ElectricCurrentExponent", IfcEngine.sdaiINTEGER, ref ifcElectricCurrentExponent);

                IfcHandle ifcThermodynamicTemperatureExponent = 0;
                IfcEngine.sdaiPutAttrBN(instance, "ThermodynamicTemperatureExponent", IfcEngine.sdaiINTEGER, ref ifcThermodynamicTemperatureExponent);

                IfcHandle ifcAmountOfSubstanceExponent = 0;
                IfcEngine.sdaiPutAttrBN(instance, "AmountOfSubstanceExponent", IfcEngine.sdaiINTEGER, ref ifcAmountOfSubstanceExponent);

                IfcHandle ifcLuminousIntensityExponent = 0;
                IfcEngine.sdaiPutAttrBN(instance, "LuminousIntensityExponent", IfcEngine.sdaiINTEGER, ref ifcLuminousIntensityExponent);
            });

            return ifcDimensionalExponentsInstance;
        }

        /// <summary>
        /// Creates IFCMEASUREWITHUNIT
        /// </summary>
        private IfcHandle CreateMeasureWithUnitInstance()
        {
            IfcHandle ifcMeasureWithUnitInstance = CreateInstance("IFCMEASUREWITHUNIT", (instance) =>
            {
                double dValueComponent = 0.01745;
                IfcHandle ifcValueComponentADB = IfcEngine.sdaiCreateADB(IfcEngine.sdaiREAL, ref dValueComponent);
                IfcEngine.sdaiPutADBTypePath(ifcValueComponentADB, 1, "IFCPLANEANGLEMEASURE");

                IfcEngine.sdaiPutAttrBN(instance, "ValueComponent", IfcEngine.sdaiADB, ifcValueComponentADB);

                IfcHandle ifcPlaneAngelUnit = CreateSIUnitInstance("PLANEANGLEUNIT", string.Empty, "RADIAN", 0);
                IfcEngine.sdaiPutAttrBN(instance, "UnitComponent", IfcEngine.sdaiINSTANCE, ifcPlaneAngelUnit);
            });

            return ifcMeasureWithUnitInstance;
        }

        /// <summary>
        /// Creates IFCCONVERSIONBASEDUNIT
        /// </summary>
        private IfcHandle CreateConversionBasedUnitInstance()
        {
            IfcHandle ifcConversionBasedUnitInstance = CreateInstance("IFCCONVERSIONBASEDUNIT", (instance) =>
            {
                IfcEngine.sdaiPutAttrBN(instance, "Dimensions", IfcEngine.sdaiINSTANCE, _ifcDimensionalExponentsInstance);
                IfcEngine.sdaiPutAttrBN(instance, "UnitType", IfcEngine.sdaiENUM, "PLANEANGLEUNIT");
                IfcEngine.sdaiPutAttrBN(instance, "Name", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes("DEGREE"));
                IfcEngine.sdaiPutAttrBN(instance, "ConversionFactor", IfcEngine.sdaiINSTANCE, _ifcMeasureWithUnitInstance);
            });

            return ifcConversionBasedUnitInstance;
        }

        /// <summary>
        /// Creates IFCRELVOIDSELEMENT
        /// </summary>
        /// <returns></returns>
        private IfcHandle CreateRelVoidsElementInstance(IfcHandle ifcBuildingElementInstance, IfcHandle ifcOpeningElementInstance)
        {
            IfcHandle ifcRelVoidsElementInstance = CreateInstance("IFCRELVOIDSELEMENT");

            IfcEngine.sdaiPutAttrBN(ifcRelVoidsElementInstance, "GlobalId", IfcEngine.sdaiUNICODE, Encoding.Unicode.GetBytes(CompressedGuidFactory.Build()));
            IfcEngine.sdaiPutAttrBN(ifcRelVoidsElementInstance, "OwnerHistory", IfcEngine.sdaiINSTANCE, _ifcOwnerHistoryInstance);

            IfcEngine.sdaiPutAttrBN(ifcRelVoidsElementInstance, "RelatingBuildingElement", IfcEngine.sdaiINSTANCE, ifcBuildingElementInstance);
            IfcEngine.sdaiPutAttrBN(ifcRelVoidsElementInstance, "RelatedOpeningElement", IfcEngine.sdaiINSTANCE, ifcOpeningElementInstance);

            return ifcRelVoidsElementInstance;
        }

        /// <summary>
        /// Stores model
        /// </summary> 
        public void SaveAsIFC()
        {
            base.SaveAsIFC(_settings.OutputFile);
        }

        /// <summary>
        /// Stores model
        /// </summary>
        public void SaveAsIFCX()
        {
            base.SaveAsIFCX(_settings.OutputFile);
        }

        #endregion // Common
    }
}
