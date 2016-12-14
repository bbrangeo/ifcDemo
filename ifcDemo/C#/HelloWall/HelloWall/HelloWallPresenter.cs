using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using HelloWall.Properties;
using System.IO;

namespace HelloWall
{
    /// <summary>
    /// Presenter (Model-View-Presenter)
    /// </summary>
    public class HelloWallPresenter
    {
        #region Members

        /// <summary>
        /// The Presenter is updating the View (MVP)
        /// </summary>
        private bool _bSkipValidation = false;

        #endregion // Members

        /// <summary>
        /// ctor
        /// </summary>
        public HelloWallPresenter(HelloWallSettings settings, IHelloWallView view)
        {
            if (settings == null)
            {
                throw new Exception("Settings (MVP) is null.");
            }

            this.Settings = settings;

            if (view == null)
            {
                throw new Exception("View (MVP) is null.");
            }

            this.View = view;

            this.View.Presenter = this;
        }

        /// <summary>
        /// The View => Presenter
        /// </summary>
        public void OnLoad()
        {
            try
            {
                UpdateGeneralUI();

                UpdateWallUI();

                UpdateOpeningUI();

                UpdateWindowUI();

                ValidateUI();
            }
            catch (Exception exception)
            {
                System.Diagnostics.Debug.Assert(false, exception.Message);

                this.View.SetError(HelloWallViewProperties.CREATE_IFC_BUTTON, "Internal error. " + exception.Message);
            }
        }

        /// <summary>
        /// The View => Presenter
        /// </summary>
        public void OnTestMode()
        {
            try
            {
                string strSchemaFile = this.GetProperty<string>(HelloWallViewProperties.SCHEMA_FILE).ToString();
                string strOutputFile = this.GetProperty<string>(HelloWallViewProperties.OUTPUT_FILE).ToString();

                string strOutputFolder = Path.GetDirectoryName(strOutputFile);

                #region Test1
                {
                    HelloWallSettings settings = new HelloWallSettings();
                    settings.SchemaFile = strSchemaFile;
                    settings.OutputFile = strOutputFolder + @"\Test1.ifc";
                    settings.View = IfcView.Coordination;
                    settings.WallIsEnabled = false;
                    settings.OpeningIsEnabled = false;
                    settings.WindowIsEnabled = false;

                    using (HelloWallIfcFileFactory factory = new HelloWallIfcFileFactory(settings))
                    {
                        factory.Build();
                        factory.SaveAsIFC();
                    }
                }
                #endregion // Test1

                #region Test2
                {
                    HelloWallSettings settings = new HelloWallSettings();
                    settings.SchemaFile = strSchemaFile;
                    settings.OutputFile = strOutputFolder + @"\Test2.ifc";
                    settings.View = IfcView.Coordination;
                    settings.WallIsEnabled = true;
                    settings.OpeningIsEnabled = false;
                    settings.WindowIsEnabled = false;

                    using (HelloWallIfcFileFactory factory = new HelloWallIfcFileFactory(settings))
                    {
                        factory.Build();
                        factory.SaveAsIFC();
                    }
                }
                #endregion // Test2

                #region Test3
                {
                    HelloWallSettings settings = new HelloWallSettings();
                    settings.SchemaFile = strSchemaFile;
                    settings.OutputFile = strOutputFolder + @"\Test3.ifc";
                    settings.View = IfcView.Coordination;
                    settings.WallIsEnabled = true;
                    settings.OpeningIsEnabled = true;
                    settings.WindowIsEnabled = false;

                    using (HelloWallIfcFileFactory factory = new HelloWallIfcFileFactory(settings))
                    {
                        factory.Build();
                        factory.SaveAsIFC();
                    }
                }
                #endregion // Test3

                #region Test4
                {
                    HelloWallSettings settings = new HelloWallSettings();
                    settings.SchemaFile = strSchemaFile;
                    settings.OutputFile = strOutputFolder + @"\Test4.ifc";
                    settings.View = IfcView.Coordination;
                    settings.WallIsEnabled = true;
                    settings.OpeningIsEnabled = true;
                    settings.WindowIsEnabled = true;

                    using (HelloWallIfcFileFactory factory = new HelloWallIfcFileFactory(settings))
                    {
                        factory.Build();
                        factory.SaveAsIFC();
                    }
                }
                #endregion // Test4

                #region Test5
                {
                    HelloWallSettings settings = new HelloWallSettings();
                    settings.SchemaFile = strSchemaFile;
                    settings.OutputFile = strOutputFolder + @"\Test5.ifc";
                    settings.View = IfcView.Coordination;
                    settings.WallIsEnabled = false;
                    settings.OpeningIsEnabled = false;
                    settings.WindowIsEnabled = true;

                    using (HelloWallIfcFileFactory factory = new HelloWallIfcFileFactory(settings))
                    {
                        factory.Build();
                        factory.SaveAsIFC();
                    }
                }
                #endregion // Test5

                #region Test6
                {
                    HelloWallSettings settings = new HelloWallSettings();
                    settings.SchemaFile = strSchemaFile;
                    settings.OutputFile = strOutputFolder + @"\Test6.ifc";
                    settings.View = IfcView.Presentation;
                    settings.WallIsEnabled = true;
                    settings.OpeningIsEnabled = true;
                    settings.WindowIsEnabled = true;

                    using (HelloWallIfcFileFactory factory = new HelloWallIfcFileFactory(settings))
                    {
                        factory.Build();
                        factory.SaveAsIFC();
                    }
                }
                #endregion // Test6

                #region Test7
                {
                    HelloWallSettings settings = new HelloWallSettings();
                    settings.SchemaFile = strSchemaFile;
                    settings.OutputFile = strOutputFolder + @"\Test7.ifc";
                    settings.View = IfcView.Coordination;
                    settings.WallIsEnabled = true;
                    settings.WallBodyRepresentation = IfcBodyRepresentation.ExtrudedPolygon;
                    settings.OpeningIsEnabled = true;
                    settings.OpeningBodyRepresentation = IfcBodyRepresentation.ExtrudedPolygon;
                    settings.WindowIsEnabled = false;

                    using (HelloWallIfcFileFactory factory = new HelloWallIfcFileFactory(settings))
                    {
                        factory.Build();
                        factory.SaveAsIFC();
                    }
                }
                #endregion // Test7
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Helper
        /// </summary>
        private void ValidateUI()
        {
            if (_bSkipValidation)
            {
                return;
            }

            if (!ValidateGeneralUI())
            {
                return;
            }

            if (!ValidateWallUI())
            {
                return;
            }

            if (!ValidateOpeningUI())
            {
                return;
            }

            if (!ValidateWindowUI())
            {
                return;
            }

            this.View.SetError(string.Empty, string.Empty);
        }

        /// <summary>
        /// Helper
        /// </summary>
        /// <returns></returns>
        private bool ValidateGeneralUI()
        {
            string strSchemaFile = this.GetProperty<string>(HelloWallViewProperties.SCHEMA_FILE);
            if (string.IsNullOrEmpty(strSchemaFile))
            {
                this.View.SetError(HelloWallViewProperties.SCHEMA_FILE, "There is no Schema file selected.");

                return false;
            }

            string strOutputFile = this.GetProperty<string>(HelloWallViewProperties.OUTPUT_FILE);
            if (string.IsNullOrEmpty(strOutputFile))
            {
                this.View.SetError(HelloWallViewProperties.OUTPUT_FILE, "There is no Output file selected.");

                return false;
            }

            return true;
        }

        /// <summary>
        /// Helper
        /// </summary>
        /// <returns></returns>
        private bool ValidateWallUI()
        {
            bool bWallIsEnabled = this.GetProperty<bool>(HelloWallViewProperties.WALL_IS_ENABLED);
            if (!bWallIsEnabled)
            {
                this.SetProperty(HelloWallViewProperties.WALL_SETTINGS_ARE_ENABLED, false);

                return true;
            }

            this.SetProperty(HelloWallViewProperties.WALL_SETTINGS_ARE_ENABLED, true);

            IfcView view = this.GetProperty<IfcView>(HelloWallViewProperties.VIEW);

            this.SetProperty(HelloWallViewProperties.WALL_EXTRUDED_POLYGON_IS_ENABLED, view == IfcView.Coordination);
            if (view == IfcView.Presentation)
            {
                this.SetProperty(HelloWallViewProperties.WALL_BODY_REPRESENTATION, IfcBodyRepresentation.BRep);
            }

            string strWallName = this.View.GetProperty(HelloWallViewProperties.WALL_NAME).ToString();
            if (string.IsNullOrEmpty(strWallName))
            {
                this.View.SetError(HelloWallViewProperties.WALL_NAME, "Wall name is empty.");

                return false;
            }

            string strWallThickness = this.View.GetProperty(HelloWallViewProperties.WALL_THICKNESS).ToString();
            if (!this.IsInteger(strWallThickness))
            {
                this.View.SetError(HelloWallViewProperties.WALL_THICKNESS, Resources.ERR_INVALID_INTEGER);

                return false;
            }

            string strWallHeight = this.View.GetProperty(HelloWallViewProperties.WALL_HEIGHT).ToString();
            if (!this.IsInteger(strWallHeight))
            {
                this.View.SetError(HelloWallViewProperties.WALL_HEIGHT, Resources.ERR_INVALID_INTEGER);

                return false;
            }

            string strWallWidth = this.View.GetProperty(HelloWallViewProperties.WALL_WIDTH).ToString();
            if (!this.IsInteger(strWallWidth))
            {
                this.View.SetError(HelloWallViewProperties.WALL_WIDTH, Resources.ERR_INVALID_INTEGER);

                return false;
            }

            return true;
        }

        /// <summary>
        /// Helper
        /// </summary>
        /// <returns></returns>
        private bool ValidateOpeningUI()
        {
            bool bWallIsEnabled = this.GetProperty<bool>(HelloWallViewProperties.WALL_IS_ENABLED);
            if (!bWallIsEnabled)
            {
                this.SetProperty(HelloWallViewProperties.OPENING_UI_IS_ENABLED, false);

                return true;
            }

            this.SetProperty(HelloWallViewProperties.OPENING_UI_IS_ENABLED, true);

            bool bOpeningIsEnabled = this.GetProperty<bool>(HelloWallViewProperties.OPENING_IS_ENABLED);
            if (!bOpeningIsEnabled)
            {
                this.SetProperty(HelloWallViewProperties.OPENING_SETTINGS_ARE_ENABLED, false);

                return true;
            }

            this.SetProperty(HelloWallViewProperties.OPENING_SETTINGS_ARE_ENABLED, true);

            IfcView view = this.GetProperty<IfcView>(HelloWallViewProperties.VIEW);

            this.SetProperty(HelloWallViewProperties.OPENING_EXTRUDED_POLYGON_IS_ENABLED, view == IfcView.Coordination);
            if (view == IfcView.Presentation)
            {
                this.SetProperty(HelloWallViewProperties.OPENING_BODY_REPRESENTATION, IfcBodyRepresentation.BRep);
            }

            this.SetProperty(HelloWallViewProperties.OPENING_BOUNDING_BOX_IS_ENABLED, view == IfcView.Coordination);

            string strOpeningName = this.View.GetProperty(HelloWallViewProperties.OPENING_NAME).ToString();
            if (string.IsNullOrEmpty(strOpeningName))
            {
                this.View.SetError(HelloWallViewProperties.OPENING_NAME, "Opening name is empty.");

                return false;
            }

            string strOpeningXOffset = this.View.GetProperty(HelloWallViewProperties.OPENING_X_OFFSET).ToString();
            if (!this.IsInteger(strOpeningXOffset))
            {
                this.View.SetError(HelloWallViewProperties.OPENING_X_OFFSET, Resources.ERR_INVALID_INTEGER);

                return false;
            }

            string strOpeningYOffset = this.View.GetProperty(HelloWallViewProperties.OPENING_Z_OFFSET).ToString();
            if (!this.IsInteger(strOpeningYOffset))
            {
                this.View.SetError(HelloWallViewProperties.OPENING_Z_OFFSET, Resources.ERR_INVALID_INTEGER);

                return false;
            }

            string strOpeningHeight = this.View.GetProperty(HelloWallViewProperties.OPENING_HEIGHT).ToString();
            if (!this.IsInteger(strOpeningHeight))
            {
                this.View.SetError(HelloWallViewProperties.OPENING_HEIGHT, Resources.ERR_INVALID_INTEGER);

                return false;
            }

            this.SetProperty(HelloWallViewProperties.WINDOW_HEIGHT, strOpeningHeight);            

            string strOpeningWidth = this.View.GetProperty(HelloWallViewProperties.OPENING_WIDTH).ToString();
            if (!this.IsInteger(strOpeningWidth))
            {
                this.View.SetError(HelloWallViewProperties.OPENING_WIDTH, Resources.ERR_INVALID_INTEGER);

                return false;
            }

            this.SetProperty(HelloWallViewProperties.WINDOW_WIDTH, strOpeningWidth);

            // Validate position/measures
            if (view == IfcView.Presentation)
            {
                int iWallHeight = int.Parse(this.GetProperty<string>(HelloWallViewProperties.WALL_HEIGHT));
                int iWallWidth = int.Parse(this.GetProperty<string>(HelloWallViewProperties.WALL_WIDTH));
                int iOpeningHeight = int.Parse(this.GetProperty<string>(HelloWallViewProperties.OPENING_HEIGHT));
                int iOpeningWidth = int.Parse(this.GetProperty<string>(HelloWallViewProperties.OPENING_WIDTH));
                int iOpeningXOffset = int.Parse(this.GetProperty<string>(HelloWallViewProperties.OPENING_X_OFFSET));
                int iOpeningZOffset = int.Parse(this.GetProperty<string>(HelloWallViewProperties.OPENING_Z_OFFSET));

                if ((iOpeningXOffset <= 0) ||
                    (iOpeningXOffset + iOpeningWidth >= iWallWidth) ||
                    (iOpeningZOffset <= 0) ||
                    (iOpeningZOffset + iOpeningHeight >= iWallHeight))
                {
                    this.View.SetError(HelloWallViewProperties.CREATE_IFC_BUTTON, Resources.ERR_OPENING_MEASURES);

                    return false;
                }
            }

            return true;
        }

        /// <summary>
        /// Helper
        /// </summary>
        /// <returns></returns>
        private bool ValidateWindowUI()
        {
            bool bWallIsEnabled = this.GetProperty<bool>(HelloWallViewProperties.WALL_IS_ENABLED);
            bool bOpeningIsEnabled = this.GetProperty<bool>(HelloWallViewProperties.OPENING_IS_ENABLED);

            bool bWindowUIIsEnabled = !bWallIsEnabled/*the Opening is disabled too*/ || 
                (bWallIsEnabled && bOpeningIsEnabled)/*both the Wall and the Opening are disabled*/;

            if (!bWindowUIIsEnabled)
            {
                this.SetProperty(HelloWallViewProperties.WINDOW_UI_IS_ENABLED, false);

                return true;
            }

            this.SetProperty(HelloWallViewProperties.WINDOW_UI_IS_ENABLED, true);

            bool bWindowIsEnabled = this.GetProperty<bool>(HelloWallViewProperties.WINDOW_IS_ENABLED);
            if (!bWindowIsEnabled)
            {
                this.SetProperty(HelloWallViewProperties.WINDOW_SETTINGS_ARE_ENABLED, false);

                return true;
            }            

            this.SetProperty(HelloWallViewProperties.WINDOW_SETTINGS_ARE_ENABLED, true);

            bool bWindowDimesnonsUIIsEnabled = !bWallIsEnabled;
            this.SetProperty(HelloWallViewProperties.WINDOW_DIMENSIONS_UI_IS_ENABLED, bWindowDimesnonsUIIsEnabled);

            IfcView view = this.GetProperty<IfcView>(HelloWallViewProperties.VIEW);

            this.SetProperty(HelloWallViewProperties.WINDOW_EXTRUDED_POLYGON_IS_ENABLED, view == IfcView.Coordination);
            if (view == IfcView.Presentation)
            {
                this.SetProperty(HelloWallViewProperties.WINDOW_BODY_REPRESENTATION, IfcBodyRepresentation.BRep);
            }

            string strWindowName = this.View.GetProperty(HelloWallViewProperties.WINDOW_NAME).ToString();
            if (string.IsNullOrEmpty(strWindowName))
            {
                this.View.SetError(HelloWallViewProperties.WINDOW_NAME, "Window name is empty.");

                return false;
            }

            string strWindowThickness = this.View.GetProperty(HelloWallViewProperties.WINDOW_THICKNESS).ToString();
            if (!this.IsInteger(strWindowThickness))
            {
                this.View.SetError(HelloWallViewProperties.WINDOW_THICKNESS, Resources.ERR_INVALID_INTEGER);

                return false;
            }

            string strWindowYOffset = this.View.GetProperty(HelloWallViewProperties.WINDOW_Y_OFFSET).ToString();
            if (!this.IsInteger(strWindowYOffset))
            {
                this.View.SetError(HelloWallViewProperties.WINDOW_Y_OFFSET, Resources.ERR_INVALID_INTEGER);

                return false;
            }

            if (bWindowDimesnonsUIIsEnabled)
            {
                string strWindowHeight = this.View.GetProperty(HelloWallViewProperties.WINDOW_HEIGHT).ToString();
                if (!this.IsInteger(strWindowHeight))
                {
                    this.View.SetError(HelloWallViewProperties.WINDOW_HEIGHT, Resources.ERR_INVALID_INTEGER);

                    return false;
                }

                string strWindowWidth = this.View.GetProperty(HelloWallViewProperties.WINDOW_WIDTH).ToString();
                if (!this.IsInteger(strWindowWidth))
                {
                    this.View.SetError(HelloWallViewProperties.WINDOW_WIDTH, Resources.ERR_INVALID_INTEGER);

                    return false;
                }
            }

            return true;
        }

        /// <summary>
        /// Helper
        /// </summary>
        private void UpdateGeneralUI()
        {
            this.SetProperty(HelloWallViewProperties.SCHEMA_FILE, this.Settings.SchemaFile);
            this.SetProperty(HelloWallViewProperties.OUTPUT_FILE, this.Settings.OutputFile);
            this.SetProperty(HelloWallViewProperties.VIEW, this.Settings.View);
            this.SetProperty(HelloWallViewProperties.INCLUDE_QUANTITIES, this.Settings.IncludeQuantities);
            this.SetProperty(HelloWallViewProperties.USE_METERS, this.Settings.UseMeters);
        }

        /// <summary>
        /// Helper
        /// </summary>
        private void UpdateWallUI()
        {
            this.SetProperty(HelloWallViewProperties.WALL_IS_ENABLED, this.Settings.WallIsEnabled);
            this.SetProperty(HelloWallViewProperties.WALL_NAME, this.Settings.WallName);
            this.SetProperty(HelloWallViewProperties.WALL_BODY_REPRESENTATION, this.Settings.WallBodyRepresentation);
            this.SetProperty(HelloWallViewProperties.WALL_EXTRUDED_POLYGON_IS_ENABLED, this.Settings.View == IfcView.Coordination);
            this.SetProperty(HelloWallViewProperties.WALL_BOUNDING_BOX, this.Settings.WallBoundingBox);
            this.SetProperty(HelloWallViewProperties.WALL_THICKNESS, this.Settings.WallThickness.ToString());
            this.SetProperty(HelloWallViewProperties.WALL_HEIGHT, this.Settings.WallHeight.ToString());
            this.SetProperty(HelloWallViewProperties.WALL_WIDTH, this.Settings.WallWidth.ToString());
        }

        /// <summary>
        /// Helper
        /// </summary>
        private void UpdateOpeningUI()
        {
            this.SetProperty(HelloWallViewProperties.OPENING_IS_ENABLED, this.Settings.OpeningIsEnabled);
            this.SetProperty(HelloWallViewProperties.OPENING_NAME, this.Settings.OpeningName);
            this.SetProperty(HelloWallViewProperties.OPENING_BODY_REPRESENTATION, this.Settings.OpeningBodyRepresentation);
            this.SetProperty(HelloWallViewProperties.OPENING_EXTRUDED_POLYGON_IS_ENABLED, this.Settings.View == IfcView.Coordination);
            this.SetProperty(HelloWallViewProperties.OPENING_BOUNDING_BOX, this.Settings.OpeningBoundingBox);
            this.SetProperty(HelloWallViewProperties.OPENING_BOUNDING_BOX_IS_ENABLED, this.Settings.View == IfcView.Coordination);
            this.SetProperty(HelloWallViewProperties.OPENING_X_OFFSET, this.Settings.OpeningXOffset.ToString());
            this.SetProperty(HelloWallViewProperties.OPENING_Z_OFFSET, this.Settings.OpeningZOffset.ToString());
            this.SetProperty(HelloWallViewProperties.OPENING_HEIGHT, this.Settings.OpeningHeight.ToString());
            this.SetProperty(HelloWallViewProperties.OPENING_WIDTH, this.Settings.OpeningWidth.ToString());
        }

        /// <summary>
        /// Helper
        /// </summary>
        private void UpdateWindowUI()
        {
            this.SetProperty(HelloWallViewProperties.WINDOW_IS_ENABLED, this.Settings.WindowIsEnabled);
            this.SetProperty(HelloWallViewProperties.WINDOW_NAME, this.Settings.WindowName);
            this.SetProperty(HelloWallViewProperties.WINDOW_BODY_REPRESENTATION, this.Settings.WindowBodyRepresentation);
            this.SetProperty(HelloWallViewProperties.WINDOW_EXTRUDED_POLYGON_IS_ENABLED, this.Settings.View == IfcView.Coordination);
            this.SetProperty(HelloWallViewProperties.WINDOW_BOUNDING_BOX, this.Settings.WindowBoundingBox);
            this.SetProperty(HelloWallViewProperties.WINDOW_THICKNESS, this.Settings.WindowThickness.ToString());
            this.SetProperty(HelloWallViewProperties.WINDOW_Y_OFFSET, this.Settings.WindowYOffset.ToString());
            this.SetProperty(HelloWallViewProperties.WINDOW_HEIGHT, this.Settings.WindowHeight.ToString());
            this.SetProperty(HelloWallViewProperties.WINDOW_WIDTH, this.Settings.WindowWidth.ToString());
        }

        /// <summary>
        /// A property in View (MVP) has been changed
        /// </summary>
        public void OnProperyChanged()
        {
            ValidateUI();
        }

        /// <summary>
        /// The View => Presenter
        /// </summary>
        public void OnCreateIFCFile()
        {
            try
            {
                SaveSettings();

                using (HelloWallIfcFileFactory factory = new HelloWallIfcFileFactory(this.Settings))
                {
                    factory.Build();
                    factory.SaveAsIFC();
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// The View => Presenter
        /// </summary>
        public void OnCreateIFCXMLFile()
        {
            try
            {
                SaveSettings();

                using (HelloWallIfcFileFactory factory = new HelloWallIfcFileFactory(this.Settings))
                {
                    factory.Build();
                    factory.SaveAsIFCX();
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// View => Presenter => Model (MVP)
        /// </summary>
        private void SaveSettings()
        {
            #region General

            this.Settings.SchemaFile = this.GetProperty<string>(HelloWallViewProperties.SCHEMA_FILE);
            this.Settings.OutputFile = this.GetProperty<string>(HelloWallViewProperties.OUTPUT_FILE).ToString();
            this.Settings.View = this.GetProperty<IfcView>(HelloWallViewProperties.VIEW);
            this.Settings.IncludeQuantities = this.GetProperty<bool>(HelloWallViewProperties.INCLUDE_QUANTITIES);
            this.Settings.UseMeters = this.GetProperty<bool>(HelloWallViewProperties.USE_METERS);

            #endregion // General

            #region Wall & Opening

            this.Settings.WallIsEnabled = this.GetProperty<bool>(HelloWallViewProperties.WALL_IS_ENABLED);
            if (this.Settings.WallIsEnabled)
            {
                #region Wall

                this.Settings.WallName = this.GetProperty<string>(HelloWallViewProperties.WALL_NAME);
                this.Settings.WallBodyRepresentation = this.GetProperty<IfcBodyRepresentation>(HelloWallViewProperties.WALL_BODY_REPRESENTATION);
                this.Settings.WallBoundingBox = this.GetProperty<bool>(HelloWallViewProperties.WALL_BOUNDING_BOX);
                this.Settings.WallThickness = int.Parse(this.GetProperty<string>(HelloWallViewProperties.WALL_THICKNESS));
                this.Settings.WallHeight = int.Parse(this.GetProperty<string>(HelloWallViewProperties.WALL_HEIGHT));
                this.Settings.WallWidth = int.Parse(this.GetProperty<string>(HelloWallViewProperties.WALL_WIDTH));

                #endregion // Wall

                #region Opening

                this.Settings.OpeningIsEnabled = this.GetProperty<bool>(HelloWallViewProperties.OPENING_IS_ENABLED);
                if (this.Settings.OpeningIsEnabled)
                {
                    this.Settings.OpeningName = this.GetProperty<string>(HelloWallViewProperties.OPENING_NAME);
                    this.Settings.OpeningBodyRepresentation = this.GetProperty<IfcBodyRepresentation>(HelloWallViewProperties.OPENING_BODY_REPRESENTATION);
                    this.Settings.OpeningBoundingBox = this.GetProperty<bool>(HelloWallViewProperties.OPENING_BOUNDING_BOX);
                    this.Settings.OpeningXOffset = int.Parse(this.GetProperty<string>(HelloWallViewProperties.OPENING_X_OFFSET));
                    this.Settings.OpeningZOffset = int.Parse(this.GetProperty<string>(HelloWallViewProperties.OPENING_Z_OFFSET));
                    this.Settings.OpeningHeight = int.Parse(this.GetProperty<string>(HelloWallViewProperties.OPENING_HEIGHT));
                    this.Settings.OpeningWidth = int.Parse(this.GetProperty<string>(HelloWallViewProperties.OPENING_WIDTH));
                }

                #endregion // Opening & Opening
            }
            else
            {
                this.Settings.OpeningIsEnabled = false;
            }

            #endregion // Wall

            #region Window
            
            this.Settings.WindowIsEnabled = this.GetProperty<bool>(HelloWallViewProperties.WINDOW_IS_ENABLED);

            if (this.Settings.WindowIsEnabled && (!this.Settings.WallIsEnabled || (this.Settings.WallIsEnabled && this.Settings.OpeningIsEnabled)))
            {
                this.Settings.WindowName = this.GetProperty<string>(HelloWallViewProperties.WINDOW_NAME);
                this.Settings.WindowBodyRepresentation = this.GetProperty<IfcBodyRepresentation>(HelloWallViewProperties.WINDOW_BODY_REPRESENTATION);
                this.Settings.WindowBoundingBox = this.GetProperty<bool>(HelloWallViewProperties.WINDOW_BOUNDING_BOX);
                this.Settings.WindowThickness = int.Parse(this.GetProperty<string>(HelloWallViewProperties.WINDOW_THICKNESS));
                this.Settings.WindowYOffset = int.Parse(this.GetProperty<string>(HelloWallViewProperties.WINDOW_Y_OFFSET));
                this.Settings.WindowHeight = int.Parse(this.GetProperty<string>(HelloWallViewProperties.WINDOW_HEIGHT));
                this.Settings.WindowWidth = int.Parse(this.GetProperty<string>(HelloWallViewProperties.WINDOW_WIDTH));
            }           

            #endregion // Window
        }

        /// <summary>
        /// Accessor
        /// </summary>
        private HelloWallSettings Settings
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        private IHelloWallView View
        {
            get;
            set;
        }

        /// <summary>
        /// Helper
        /// </summary>
        private void SetProperty(string strProperty, object value)
        {
            try
            {
                _bSkipValidation = true;

                this.View.SetProperty(strProperty, value);
            }
            catch
            {
                throw;
            }
            finally
            {
                _bSkipValidation = false;
            }
        }

        /// <summary>
        /// Helper
        /// </summary>
        private TType GetProperty<TType>(string strProperty)
        {
            object property = this.View.GetProperty(strProperty);

            if (!(property is TType))
            {
                throw new Exception(string.Format("Invalid property type: '{0}'", strProperty));
            }

            return (TType)property;
        }

        /// <summary>
        /// Helper
        /// </summary>
        private bool IsInteger(string strValue)
        {
            int iValue;
            if (!int.TryParse(strValue, out iValue))
            {
                this.View.SetError(HelloWallViewProperties.WALL_THICKNESS, Resources.ERR_INVALID_INTEGER);

                return false;
            }

            return true;
        }
    }
}
