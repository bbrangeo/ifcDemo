using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
#if WIN64
using IfcHandle = System.Int64;
#else
using IfcHandle = System.Int32;
#endif

namespace HelloWall
{
    /// <summary>
    /// Model (Model-View-Presenter)
    /// </summary>
    public class HelloWallSettings
    {
        /// <summary>
        /// ctor
        /// </summary>
        public HelloWallSettings()
        {
            this.Reset();
        }

        /// <summary>
        /// Sets up default values
        /// </summary>
        public void Reset()
        {
            #region General

            this.SchemaFile = string.Empty;
            this.OutputFile = string.Empty; 
            this.View = IfcView.Coordination;
            this.IncludeQuantities = true;
            this.UseMeters = false;

            #endregion // General

            #region Wall

            this.WallIsEnabled = true;
            this.WallName = "Wall xyz";
            this.WallBodyRepresentation = IfcBodyRepresentation.BRep;
            this.WallBoundingBox = true;
            this.WallThickness = 300;
            this.WallHeight = 2300;
            this.WallWidth = 5000;

            #endregion // Wall

            #region Opening

            this.OpeningIsEnabled = true;
            this.OpeningName = "Opening Element xyz";
            this.OpeningBodyRepresentation = IfcBodyRepresentation.BRep;
            this.OpeningBoundingBox = true;
            this.OpeningXOffset = 900;
            this.OpeningZOffset = 250;
            this.OpeningHeight = 1400;
            this.OpeningWidth = 750;

            #endregion // Opening

            #region Window

            this.WindowIsEnabled = true;
            this.WindowName = "Window xyz";
            this.WindowBodyRepresentation = IfcBodyRepresentation.BRep;
            this.WindowBoundingBox = true;
            this.WindowThickness = 190;
            this.WindowYOffset = 12;
            this.WindowHeight = this.OpeningHeight;
            this.WindowWidth = this.OpeningWidth;

            #endregion // Window
        }

        #region General

        /// <summary>
        /// Accessor
        /// </summary>
        public string SchemaFile
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public string OutputFile
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcView View
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        /// <remarks>
        public bool IncludeQuantities
        {
            get;
            set;
        }        

        /// <summary>
        /// Accessor
        /// </summary>
        public bool UseMeters
        {
            get;
            set;
        }

        #endregion // General

        #region Wall

        /// <summary>
        /// Accessor
        /// </summary>
        public bool WallIsEnabled
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public string WallName
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcBodyRepresentation WallBodyRepresentation
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public bool WallBoundingBox
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcHandle WallThickness
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcHandle WallHeight
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcHandle WallWidth
        {
            get;
            set;
        }

        #endregion // Wall

        #region Opening

        /// <summary>
        /// Accessor
        /// </summary>
        public bool OpeningIsEnabled
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public string OpeningName
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcBodyRepresentation OpeningBodyRepresentation
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public bool OpeningBoundingBox
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcHandle OpeningXOffset
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcHandle OpeningZOffset
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcHandle OpeningHeight
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcHandle OpeningWidth
        {
            get;
            set;
        }

        #endregion // Opening

        #region Window

        /// <summary>
        /// Accessor
        /// </summary>
        public bool WindowIsEnabled
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public string WindowName
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcBodyRepresentation WindowBodyRepresentation
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public bool WindowBoundingBox
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcHandle WindowThickness
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcHandle WindowYOffset
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcHandle WindowHeight
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcHandle WindowWidth
        {
            get;
            set;
        }

        #endregion // Window
    }
}
