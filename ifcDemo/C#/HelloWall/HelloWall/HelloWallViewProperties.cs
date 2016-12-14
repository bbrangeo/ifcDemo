using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HelloWall
{
    /// <summary>
    /// View <=> Presenter (Model-View-Presenter) data contract
    /// </summary>
    public class HelloWallViewProperties
    {
        #region General

        public const string SCHEMA_FILE = "SCHEMA_FILE";
        public const string OUTPUT_FILE = "OUTPUT_FILE";
        public const string VIEW = "VIEW";
        public const string INCLUDE_QUANTITIES = "INCLUDE_QUANTITIES";
        public const string USE_METERS = "USE_METERS";
        public const string CREATE_IFC_BUTTON = "CREATE_IFC_BUTTON";

        #endregion // General

        #region Wall

        public const string WALL_IS_ENABLED = "WALL_IS_ENABLED";
        public const string WALL_SETTINGS_ARE_ENABLED = "WALL_SETTINGS_ARE_ENABLED";
        public const string WALL_NAME = "WALL_NAME";
        public const string WALL_BODY_REPRESENTATION = "WALL_BODY_REPRESENTATION";
        public const string WALL_EXTRUDED_POLYGON_IS_ENABLED = "WALL_EXTRUDED_POLYGON_IS_ENABLED";
        public const string WALL_BOUNDING_BOX = "WALL_BOUNDING_BOX";
        public const string WALL_THICKNESS = "WALL_THICKNESS";
        public const string WALL_HEIGHT = "WALL_HEIGHT";
        public const string WALL_WIDTH = "WALL_WIDTH";

        #endregion // Wall

        #region Opening

        public const string OPENING_UI_IS_ENABLED = "OPENING_UI_IS_ENABLED";
        public const string OPENING_IS_ENABLED = "OPENING_IS_ENABLED";
        public const string OPENING_SETTINGS_ARE_ENABLED = "OPENING_SETTINGS_ARE_ENABLED";
        public const string OPENING_NAME = "OPENING_NAME";
        public const string OPENING_BODY_REPRESENTATION = "OPENING_BODY_REPRESENTATION";
        public const string OPENING_EXTRUDED_POLYGON_IS_ENABLED = "OPENING_EXTRUDED_POLYGON_IS_ENABLED";
        public const string OPENING_BOUNDING_BOX_IS_ENABLED = "OPENING_BOUNDING_BOX_IS_ENABLED";
        public const string OPENING_BOUNDING_BOX = "OPENING_BOUNDING_BOX";
        public const string OPENING_X_OFFSET = "OPENING_X_OFFSET";
        public const string OPENING_Z_OFFSET = "OPENING_Z_OFFSET";
        public const string OPENING_HEIGHT = "OPENING_HEIGHT";
        public const string OPENING_WIDTH = "OPENING_WIDTH";

        #endregion // Opening

        #region Window

        public const string WINDOW_UI_IS_ENABLED = "WINDOW_UI_IS_ENABLED";
        public const string WINDOW_IS_ENABLED = "WINDOW_IS_ENABLED";
        public const string WINDOW_SETTINGS_ARE_ENABLED = "WINDOW_SETTINGS_ARE_ENABLED";
        public const string WINDOW_NAME = "WINDOW_NAME";
        public const string WINDOW_BODY_REPRESENTATION = "WINDOW_BODY_REPRESENTATION";
        public const string WINDOW_EXTRUDED_POLYGON_IS_ENABLED = "WINDOW_EXTRUDED_POLYGON_IS_ENABLED";
        public const string WINDOW_BOUNDING_BOX = "WINDOW_BOUNDING_BOX";
        public const string WINDOW_THICKNESS = "WINDOW_THICKNESS";
        public const string WINDOW_Y_OFFSET = "WINDOW_Y_OFFSET";
        public const string WINDOW_DIMENSIONS_UI_IS_ENABLED = "WINDOW_DIMENSIONS_UI_IS_ENABLED";
        public const string WINDOW_HEIGHT = "WINDOW_HEIGHT";
        public const string WINDOW_WIDTH = "WINDOW_WIDTH";

        #endregion // Window

        /// <summary>
        /// Helper
        /// </summary>
        public static TType ConvertProperty<TType>(string strProperty, object property)
        {
            if (!(property is TType))
            {
                throw new Exception(string.Format("Invalid property type: '{0}'", strProperty));
            }

            return (TType)property;
        }
    }
}
