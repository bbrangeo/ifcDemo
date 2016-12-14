using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Reflection;

namespace HelloWall
{
    public partial class HelloWallForm 
        : Form
        , IHelloWallView
    {
        #region Members

        /// <summary>
        /// The last control where the error provider has been shown
        /// </summary>
        private Control _errorProviderControl = null;

        #endregion // Members

        /// <summary>
        /// ctor
        /// </summary>
        public HelloWallForm()
        {
            InitializeComponent();
        }

        #region IHelloWallView

        /// <summary>
        /// IHelloWallView
        /// </summary>
        public HelloWallPresenter Presenter
        {
            get;
            set;
        }

        /// <summary>
        /// IHelloWallView
        /// </summary>
        public void SetProperty(string strProperty, object property)
        {
            if (SetGeneralProperty(strProperty, property))
            {
                return;
            }

            if (SetWallProperty(strProperty, property))
            {
                return;
            }

            if (SetOpeningProperty(strProperty, property))
            {
                return;
            }

            if (SetWindowProperty(strProperty, property))
            {
                return;
            }

            throw new Exception("Unknown property.");
        }

        /// <summary>
        /// Helper
        /// </summary>
        /// <returns></returns>
        private bool SetGeneralProperty(string strProperty, object property)
        {
            switch (strProperty)
            {
                case HelloWallViewProperties.SCHEMA_FILE:
                    {
                        _tbSchemaFileName.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.OUTPUT_FILE:
                    {
                        _tbOutputFileName.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.VIEW:
                    {
                        IfcView view = HelloWallViewProperties.ConvertProperty<IfcView>(strProperty, property);

                        if (view == IfcView.Coordination)
                        {
                            _rbCoordinationView.Checked = true;
                        }
                        else
                        {
                            _rbPresentationView.Checked = true;
                        }

                        return true;
                    }

                case HelloWallViewProperties.INCLUDE_QUANTITIES:
                    {
                        _cbIncludeQuantites.Checked = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.USE_METERS:
                    {
                        _cbUseMeters.Checked = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        return true;
                    }
            } // switch (strProperty)

            return false;
        }

        /// <summary>
        /// Helper
        /// </summary>
        /// <returns></returns>
        private bool SetWallProperty(string strProperty, object property)
        {
            switch (strProperty)
            {
                case HelloWallViewProperties.WALL_IS_ENABLED:
                    {
                        _cbWall.Checked = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.WALL_SETTINGS_ARE_ENABLED:
                    {
                        bool bWallSettingsAreEnabled = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        _rbWallExtrudedPolygon.Enabled = bWallSettingsAreEnabled;
                        _rbWallBRep.Enabled = bWallSettingsAreEnabled;
                        _cbWallBoundingBox.Enabled = bWallSettingsAreEnabled;
                        _tbWallName.Enabled = bWallSettingsAreEnabled;
                        _tbWallThickness.Enabled = bWallSettingsAreEnabled;
                        _tbWallHeight.Enabled = bWallSettingsAreEnabled;
                        _tbWallWidth.Enabled = bWallSettingsAreEnabled;

                        return true;
                    }

                case HelloWallViewProperties.WALL_NAME:
                    {
                        _tbWallName.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.WALL_BODY_REPRESENTATION:
                    {
                        IfcBodyRepresentation representation = HelloWallViewProperties.ConvertProperty<IfcBodyRepresentation>(strProperty, property);
                        if (representation == IfcBodyRepresentation.ExtrudedPolygon)
                        {
                            _rbWallExtrudedPolygon.Checked = true;
                        }
                        else
                        {
                            _rbWallBRep.Checked = true;
                        }

                        return true;
                    }

                case HelloWallViewProperties.WALL_EXTRUDED_POLYGON_IS_ENABLED:
                    {
                        _rbWallExtrudedPolygon.Enabled = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.WALL_BOUNDING_BOX:
                    {
                        _cbWallBoundingBox.Checked = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.WALL_THICKNESS:
                    {
                        _tbWallThickness.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.WALL_HEIGHT:
                    {
                        _tbWallHeight.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.WALL_WIDTH:
                    {
                        _tbWallWidth.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }
            } // switch (strProperty)

            return false;
        }

        /// <summary>
        /// Helper
        /// </summary>
        /// <returns></returns>
        private bool SetOpeningProperty(string strProperty, object property)
        {
            switch (strProperty)
            {
                case HelloWallViewProperties.OPENING_UI_IS_ENABLED:
                    {
                        _gbOpening.Enabled = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.OPENING_IS_ENABLED:
                    {
                        _cbOpening.Checked = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.OPENING_SETTINGS_ARE_ENABLED:
                    {
                        bool bOpeningSettingsAreEnabled = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        _rbOpeningExtrudedPolygon.Enabled = bOpeningSettingsAreEnabled;
                        _rbOpeningBRep.Enabled = bOpeningSettingsAreEnabled;
                        _cbOpeningBoundingBox.Enabled = bOpeningSettingsAreEnabled;
                        _tbOpeningName.Enabled = bOpeningSettingsAreEnabled;
                        _tbOpeningXOffset.Enabled = bOpeningSettingsAreEnabled;
                        _tbOpeningZOffset.Enabled = bOpeningSettingsAreEnabled;
                        _tbOpeningHeight.Enabled = bOpeningSettingsAreEnabled;
                        _tbOpeningWidth.Enabled = bOpeningSettingsAreEnabled;

                        return true;
                    }

                case HelloWallViewProperties.OPENING_NAME:
                    {
                        _tbOpeningName.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.OPENING_BODY_REPRESENTATION:
                    {
                        IfcBodyRepresentation representation = HelloWallViewProperties.ConvertProperty<IfcBodyRepresentation>(strProperty, property);
                        if (representation == IfcBodyRepresentation.ExtrudedPolygon)
                        {
                            _rbOpeningExtrudedPolygon.Checked = true;
                        }
                        else
                        {
                            _rbOpeningBRep.Checked = true;
                        }

                        return true;
                    }

                case HelloWallViewProperties.OPENING_EXTRUDED_POLYGON_IS_ENABLED:
                    {
                        _rbOpeningExtrudedPolygon.Enabled = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.OPENING_BOUNDING_BOX:
                    {
                        _cbOpeningBoundingBox.Checked = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.OPENING_BOUNDING_BOX_IS_ENABLED:
                    {
                        _cbOpeningBoundingBox.Enabled = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.OPENING_X_OFFSET:
                    {
                        _tbOpeningXOffset.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.OPENING_Z_OFFSET:
                    {
                        _tbOpeningZOffset.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.OPENING_HEIGHT:
                    {
                        _tbOpeningHeight.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.OPENING_WIDTH:
                    {
                        _tbOpeningWidth.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }
            } // switch (strProperty)

            return false;
        }

        /// <summary>
        /// Helper
        /// </summary>
        /// <returns></returns>
        private bool SetWindowProperty(string strProperty, object property)
        {
            switch (strProperty)
            {
                case HelloWallViewProperties.WINDOW_UI_IS_ENABLED:
                    {
                        _gbWindow.Enabled = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.WINDOW_IS_ENABLED:
                    {
                        _cbWindow.Checked = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.WINDOW_SETTINGS_ARE_ENABLED:
                    {
                        bool bWindowSettingsAreEnabled = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        _rbWindowExtrudedPolygon.Enabled = bWindowSettingsAreEnabled;
                        _rbWindowBRep.Enabled = bWindowSettingsAreEnabled;
                        _cbWindowBoundingBox.Enabled = bWindowSettingsAreEnabled;
                        _tbWindowName.Enabled = bWindowSettingsAreEnabled;
                        _tbWindowThickness.Enabled = bWindowSettingsAreEnabled;
                        _tbWindowYOffset.Enabled = bWindowSettingsAreEnabled;
                        _tbWindowHeight.Enabled = bWindowSettingsAreEnabled;
                        _tbWindowWidth.Enabled = bWindowSettingsAreEnabled;

                        return true;
                    }

                case HelloWallViewProperties.WINDOW_NAME:
                    {
                        _tbWindowName.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.WINDOW_BODY_REPRESENTATION:
                    {
                        IfcBodyRepresentation representation = HelloWallViewProperties.ConvertProperty<IfcBodyRepresentation>(strProperty, property);
                        if (representation == IfcBodyRepresentation.ExtrudedPolygon)
                        {
                            _rbWindowExtrudedPolygon.Checked = true;
                        }
                        else
                        {
                            _rbWindowBRep.Checked = true;
                        }

                        return true;
                    }

                case HelloWallViewProperties.WINDOW_EXTRUDED_POLYGON_IS_ENABLED:
                    {
                        _rbWindowExtrudedPolygon.Enabled = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.WINDOW_BOUNDING_BOX:
                    {
                        _cbWindowBoundingBox.Checked = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.WINDOW_THICKNESS:
                    {
                        _tbWindowThickness.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.WINDOW_Y_OFFSET:
                    {
                        _tbWindowYOffset.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.WINDOW_DIMENSIONS_UI_IS_ENABLED:
                    {
                        _tbWindowHeight.Enabled = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);
                        _tbWindowWidth.Enabled = HelloWallViewProperties.ConvertProperty<bool>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.WINDOW_HEIGHT:
                    {
                        _tbWindowHeight.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }

                case HelloWallViewProperties.WINDOW_WIDTH:
                    {
                        _tbWindowWidth.Text = HelloWallViewProperties.ConvertProperty<string>(strProperty, property);

                        return true;
                    }
            } // switch (strProperty)

            return false;
        }

        /// <summary>
        /// IHelloWallView
        /// </summary>
        public object GetProperty(string strProperty)
        {
            object property = GetGeneralProperty(strProperty);
            if (property != null)
            {
                return property;
            }

            property = GetWallProperty(strProperty);
            if (property != null)
            {
                return property;
            }

            property = GetOpeningProperty(strProperty);
            if (property != null)
            {
                return property;
            }

            property = GetWindowProperty(strProperty);
            if (property != null)
            {
                return property;
            }

            throw new Exception("Unknown property.");
        }

        /// <summary>
        /// Helper
        /// </summary>
        private object GetGeneralProperty(string strProperty)
        {
            switch (strProperty)
            {
                case HelloWallViewProperties.SCHEMA_FILE:
                    {
                        return _tbSchemaFileName.Text;
                    }

                case HelloWallViewProperties.OUTPUT_FILE:
                    {
                        return _tbOutputFileName.Text;
                    }

                case HelloWallViewProperties.VIEW:
                    {
                        return _rbCoordinationView.Checked ? IfcView.Coordination : IfcView.Presentation;
                    }

                case HelloWallViewProperties.INCLUDE_QUANTITIES:
                    {
                        return _cbIncludeQuantites.Checked;
                    }

                case HelloWallViewProperties.USE_METERS:
                    {
                        return _cbUseMeters.Checked;
                    }
            } // switch (strProperty)

            return null;
        }

        /// <summary>
        /// Helper
        /// </summary>
        private object GetWallProperty(string strProperty)
        {
            switch (strProperty)
            {
                case HelloWallViewProperties.WALL_IS_ENABLED:
                    {
                        return _cbWall.Checked;
                    }

                case HelloWallViewProperties.WALL_NAME:
                    {
                        return _tbWallName.Text;
                    }

                case HelloWallViewProperties.WALL_BODY_REPRESENTATION:
                    {
                        return _rbWallExtrudedPolygon.Checked ? IfcBodyRepresentation.ExtrudedPolygon : IfcBodyRepresentation.BRep;
                    }

                case HelloWallViewProperties.WALL_BOUNDING_BOX:
                    {
                        return _cbWallBoundingBox.Checked;
                    }

                case HelloWallViewProperties.WALL_THICKNESS:
                    {
                        return _tbWallThickness.Text;
                    }

                case HelloWallViewProperties.WALL_HEIGHT:
                    {
                        return _tbWallHeight.Text;
                    }

                case HelloWallViewProperties.WALL_WIDTH:
                    {
                        return _tbWallWidth.Text;
                    }
            } // switch (strProperty)

            return null;
        }

        /// <summary>
        /// Helper
        /// </summary>
        private object GetOpeningProperty(string strProperty)
        {
            switch (strProperty)
            {
                case HelloWallViewProperties.OPENING_IS_ENABLED:
                    {
                        return _cbOpening.Checked;
                    }

                case HelloWallViewProperties.OPENING_NAME:
                    {
                        return _tbOpeningName.Text;
                    }

                case HelloWallViewProperties.OPENING_BODY_REPRESENTATION:
                    {
                        return _rbOpeningExtrudedPolygon.Checked ? IfcBodyRepresentation.ExtrudedPolygon : IfcBodyRepresentation.BRep;
                    }

                case HelloWallViewProperties.OPENING_BOUNDING_BOX:
                    {
                        return _cbOpeningBoundingBox.Checked;
                    }

                case HelloWallViewProperties.OPENING_X_OFFSET:
                    {
                        return _tbOpeningXOffset.Text;
                    }

                case HelloWallViewProperties.OPENING_Z_OFFSET:
                    {
                        return _tbOpeningZOffset.Text;
                    }

                case HelloWallViewProperties.OPENING_HEIGHT:
                    {
                        return _tbOpeningHeight.Text;
                    }

                case HelloWallViewProperties.OPENING_WIDTH:
                    {
                        return _tbOpeningWidth.Text;
                    }
            } // switch (strProperty)

            return null;
        }

        /// <summary>
        /// Helper
        /// </summary>
        private object GetWindowProperty(string strProperty)
        {
            switch (strProperty)
            {
                case HelloWallViewProperties.WINDOW_IS_ENABLED:
                    {
                        return _cbWindow.Checked;
                    }

                case HelloWallViewProperties.WINDOW_NAME:
                    {
                        return _tbWindowName.Text;
                    }

                case HelloWallViewProperties.WINDOW_BODY_REPRESENTATION:
                    {
                        return _rbWindowExtrudedPolygon.Checked ? IfcBodyRepresentation.ExtrudedPolygon : IfcBodyRepresentation.BRep;
                    }

                case HelloWallViewProperties.WINDOW_BOUNDING_BOX:
                    {
                        return _cbWindowBoundingBox.Checked;
                    }

                case HelloWallViewProperties.WINDOW_THICKNESS:
                    {
                        return _tbWindowThickness.Text;
                    }

                case HelloWallViewProperties.WINDOW_Y_OFFSET:
                    {
                        return _tbWindowYOffset.Text;
                    }

                case HelloWallViewProperties.WINDOW_HEIGHT:
                    {
                        return _tbWindowHeight.Text;
                    }

                case HelloWallViewProperties.WINDOW_WIDTH:
                    {
                        return _tbWindowWidth.Text;
                    }
            } // switch (strProperty)

            return null;
        }

        /// <summary>
        /// IHelloWallView
        /// </summary>
        public void SetError(string strProperty, string strError)
        {
            if (_errorProviderControl != null)
            {
                _errorProvider.SetError(_errorProviderControl, string.Empty);

                _errorProviderControl = null;
            }

            _errorProvider.Clear();

            _btnCreateIFC.Enabled = string.IsNullOrEmpty(strError);
            _btnCreateIFX.Enabled = string.IsNullOrEmpty(strError);
            _btnTestMode.Enabled = string.IsNullOrEmpty(strError);

            if (string.IsNullOrEmpty(strProperty) && string.IsNullOrEmpty(strError))
            {
                return;
            }

            switch (strProperty)
            {
                #region General

                case HelloWallViewProperties.SCHEMA_FILE:
                    {
                        _errorProviderControl = _btnSchemaFileName;
                    }
                    break;

                case HelloWallViewProperties.OUTPUT_FILE:
                    {
                        _errorProviderControl = _btnOutputFileName;
                    }
                    break;

                case HelloWallViewProperties.CREATE_IFC_BUTTON:
                    {
                        _errorProviderControl = _btnCreateIFC;
                    }
                    break;

                #endregion // General

                #region Wall

                case HelloWallViewProperties.WALL_NAME:
                    {
                        _errorProviderControl = _tbWallName;
                    }
                    break;

                case HelloWallViewProperties.WALL_THICKNESS:
                    {
                        _errorProviderControl = _tbWallThickness;
                    }
                    break;

                case HelloWallViewProperties.WALL_HEIGHT:
                    {
                        _errorProviderControl = _tbWallHeight;
                    }
                    break;

                case HelloWallViewProperties.WALL_WIDTH:
                    {
                        _errorProviderControl = _tbWallWidth;
                    }
                    break;

                #endregion // Wall

                #region Opening

                case HelloWallViewProperties.OPENING_NAME:
                    {
                        _errorProviderControl = _tbOpeningName;
                    }
                    break;

                case HelloWallViewProperties.OPENING_X_OFFSET:
                    {
                        _errorProviderControl = _tbOpeningXOffset;
                    }
                    break;

                case HelloWallViewProperties.OPENING_Z_OFFSET:
                    {
                        _errorProviderControl = _tbOpeningZOffset;
                    }
                    break;

                case HelloWallViewProperties.OPENING_HEIGHT:
                    {
                        _errorProviderControl = _tbOpeningHeight;
                    }
                    break;

                case HelloWallViewProperties.OPENING_WIDTH:
                    {
                        _errorProviderControl = _tbOpeningWidth;
                    }
                    break;

                #endregion // Opening

                #region Window

                case HelloWallViewProperties.WINDOW_NAME:
                    {
                        _errorProviderControl = _tbWindowName;
                    }
                    break;

                case HelloWallViewProperties.WINDOW_THICKNESS:
                    {
                        _errorProviderControl = _tbWindowThickness;
                    }
                    break;

                case HelloWallViewProperties.WINDOW_Y_OFFSET:
                    {
                        _errorProviderControl = _tbWindowYOffset;
                    }
                    break;

                case HelloWallViewProperties.WINDOW_HEIGHT:
                    {
                        _errorProviderControl = _tbWindowHeight;
                    }
                    break;

                case HelloWallViewProperties.WINDOW_WIDTH:
                    {
                        _errorProviderControl = _tbWindowWidth;
                    }
                    break;

                #endregion // Window                

                default:
                    {
                        System.Diagnostics.Debug.Assert(false);

                        throw new Exception("Unknown property.");
                    }
            } // switch (strProperty)

            if (_errorProviderControl != null)
            {
                _errorProvider.SetError(_errorProviderControl, strError);
                _errorProvider.SetIconAlignment(_errorProviderControl, ErrorIconAlignment.MiddleLeft);
            }
        }

        #endregion // IHelloWallView

        /// <summary>
        /// Handler
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void _btnCreateIFC_Click(object sender, EventArgs e)
        {
            this.Presenter.OnCreateIFCFile();
        }

        /// <summary>
        /// Handler
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void _btnCreateIFX_Click(object sender, EventArgs e)
        {
            this.Presenter.OnCreateIFCXMLFile();
        }

        /// <summary>
        /// Handler
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void HelloWallForm_Load(object sender, EventArgs e)
        {
            this.Presenter.OnLoad();
        }        

        /// <summary>
        /// Handler
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void _btnSchemaFileName_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Schema File|*.exp";

            string strDefaultFolder = Path.GetDirectoryName(Assembly.GetExecutingAssembly().CodeBase);
            openFileDialog.InitialDirectory = strDefaultFolder;

            if (openFileDialog.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            _tbSchemaFileName.Text = openFileDialog.FileName;

            this.Presenter.OnProperyChanged();
        }

        /// <summary>
        /// Handler
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void _btnOutputFileName_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "IFC File|*.ifc";

            if (saveFileDialog.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            _tbOutputFileName.Text = saveFileDialog.FileName;

            this.Presenter.OnProperyChanged();
        }

        /// <summary>
        /// Handler
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnEvent(object sender, EventArgs e)
        {
            this.Presenter.OnProperyChanged();
        }

        /// <summary>
        /// Handler
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void _btnTestMode_Click(object sender, EventArgs e)
        {
            this.Presenter.OnTestMode();
        }

        /// <summary>
        /// Handler
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void _btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
