using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
#if WIN64
using IfcHandle = System.Int64;
#else
using IfcHandle = System.Int32;
#endif
using System.IO;

namespace HelloWall
{
    /// <summary>
    /// View
    /// </summary>
    public enum IfcView
    {
        Coordination = 0,
        Presentation = 1,
    }

    /// <summary>
    /// Body representation
    /// </summary>
    public enum IfcBodyRepresentation
    {
        ExtrudedPolygon = 0,
        BRep = 1,
        Tessellation = 2,
    }

    /// <summary>
    /// Schema version
    /// </summary>
    public enum IfcSchemaFileVersion
    {
        Unknown = 0,
        IFC2x3_TC1 = 1,
        IFC4 = 2,
    }

    /// <summary>
    /// Schema
    /// </summary>
    public class IfcSchemaFile
    {
        #region Constants

        /// <summary>
        /// Unknown
        /// </summary>
        public const string VERSION_UNKNOWN = "UNKNOWN";

        /// <summary>
        /// IFC2x3
        /// </summary>
        public const string VERSION_IFC2X3_TC1 = "IFC2X3_TC1";

        /// <summary>
        /// IFC4
        /// </summary>
        public const string VERSION_IFC4 = "IFC4";

        #endregion // Constants

        /// <summary>
        /// Helper
        /// </summary>
        public static IfcSchemaFileVersion GetVersion(string strSchemaFile)
        {
            if (string.IsNullOrEmpty(strSchemaFile))
            {
                System.Diagnostics.Debug.Assert(false);

                return IfcSchemaFileVersion.Unknown;
            }

            string strSchemaFileName = Path.GetFileNameWithoutExtension(strSchemaFile);
            if (strSchemaFileName.ToLower() == VERSION_IFC2X3_TC1.ToLower())
            {
                return IfcSchemaFileVersion.IFC2x3_TC1;
            }

            if (strSchemaFileName.ToLower() == VERSION_IFC4.ToLower())
            {
                return IfcSchemaFileVersion.IFC4;
            }

            return IfcSchemaFileVersion.Unknown;
        }

        /// <summary>
        /// Helper
        /// </summary>
        public static string GetVersionAsString(string strSchemaFile)
        {
            IfcSchemaFileVersion schemaFileVersion = GetVersion(strSchemaFile);

            switch (schemaFileVersion)
            {
                case IfcSchemaFileVersion.Unknown:
                    return VERSION_UNKNOWN;

                case IfcSchemaFileVersion.IFC2x3_TC1:
                    return VERSION_IFC2X3_TC1;

                case IfcSchemaFileVersion.IFC4:
                    return VERSION_IFC4;

                default:
                    System.Diagnostics.Debug.Assert(false, "Unknown version.");
                    break;
            }

            return VERSION_UNKNOWN;
        }
    }   

    /// <summary>
    /// Helper for creating of a compressed GUID
    /// </summary>
    public class CompressedGuidFactory
    {
        #region Constants

        /// <summary>
        /// Conversion table
        /// </summary>
        private const string CONVERSION_TABLE_64 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_$";

        #endregion // Constants

        /// <summary>
        /// Entry point
        /// </summary>
        /// <returns></returns>
        public static string Build()
        {
            byte[] guid = Guid.NewGuid().ToByteArray();

            uint[] arCodes = new uint[] { 0, 0, 0, 0, 0, 0 };

            // Creation of six 32 Bit integers from the components of the GUID structure
            arCodes[0] = (uint)guid[15];                                                    // 16. byte
            arCodes[1] = (uint)(guid[14] << 16) + (uint)(guid[13] << 8) + (uint)guid[12];   // 15-13. bytes
            arCodes[2] = (uint)(guid[11] << 16) + (uint)(guid[10] << 8) + (uint)guid[9];    // 12-10. bytes
            arCodes[3] = (uint)(guid[8] << 16) + (uint)(guid[7] << 8) + (uint)guid[6];      // 09-07. bytes
            arCodes[4] = (uint)(guid[5] << 16) + (uint)(guid[4] << 8) + (uint)guid[3];      // 06-04. bytes
            arCodes[5] = (uint)(guid[2] << 16) + (uint)(guid[1] << 8) + (uint)guid[0];      // 03-01. bytes

            string strBuffer = string.Empty;

            Int32 iLength = 3;
            for (Int32 i = 0; i < 6; i++)
            {
                string strCode;
                if (!Encode(arCodes[i], out strCode, 5, iLength))
                {
                    return string.Empty;
                }

                strBuffer += strCode;

                iLength = 5;
            }

            return strBuffer;
        }

        /// <summary>
        /// Helper for encoding
        /// </summary>
        /// <returns></returns>
        private static bool Encode(uint number, out string code, int numberOfElements, int len)
        {
            code = string.Empty;

            if (len > 5)
            {
                return false;
            }

            uint act = number;
            Int32 nDigits = len - 1;

            char[] result = new char[5];

            for (Int32 iDigit = 0; iDigit < nDigits; iDigit++)
            {
                result[nDigits - iDigit - 1] = CONVERSION_TABLE_64[(Int32)(act % 64)];

                act /= 64;
            }

            if (act != 0)
            {
                return false;
            }

            code = new string(result, 0, len - 1);

            return true;
        }
    }

    /// <summary>
    /// Describes a matrix
    /// </summary>
    public class MATRIX
    {
        public double _d11;
        public double _d12;
        public double _d13;
        public double _d21;
        public double _d22;
        public double _d23;
        public double _d31;
        public double _d32;
        public double _d33;
        public double _d41;
        public double _d42;
        public double _d43;

        /// <summary>
        /// Identity matrix
        /// </summary>
        /// <returns></returns>
        public static MATRIX IdentityMatrix()
        {
            MATRIX matrix = new MATRIX();

            matrix._d11 = 1;
            matrix._d12 = 0;
            matrix._d13 = 0;
            matrix._d21 = 0;
            matrix._d22 = 1;
            matrix._d23 = 0;
            matrix._d31 = 0;
            matrix._d32 = 0;
            matrix._d33 = 1;
            matrix._d41 = 0;
            matrix._d42 = 0;
            matrix._d43 = 0;

            return matrix;
        }
    }

    /// <summary>
    /// Describes a point
    /// </summary>
    public class POINT2D
    {
        /// <summary>
        /// ctor
        /// </summary>
        public POINT2D()
        {
            this.X = 0;
            this.Y = 0;
        }

        /// <summary>
        /// ctor
        /// </summary>
        public POINT2D(double dX, double dY)
        {
            this.X = dX;
            this.Y = dY;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public double X
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public double Y
        {
            get;
            set;
        }
    }

    /// <summary>
    /// Describes a polygon
    /// </summary>
    public class POLYGON2D : List<POINT2D>
    {
    }

    /// <summary>
    /// Describes a point
    /// </summary>
    public class POINT3D
    {
        /// <summary>
        /// ctor
        /// </summary>
        public POINT3D()
        {
            this.X = 0;
            this.Y = 0;
            this.Z = 0;
            this.CartesianPointInstance = 0;
        }

        /// <summary>
        /// ctor
        /// </summary>
        public POINT3D(double dX, double dY, double dZ)
            : this()
        {
            this.X = dX;
            this.Y = dY;
            this.Z = dZ;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public double X
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public double Y
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public double Z
        {
            get;
            set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IfcHandle CartesianPointInstance
        {
            get;
            set;
        }

        /// <summary>
        /// Identity point
        /// </summary>
        /// <returns></returns>
        public static POINT3D IdentityPoint()
        {
            return new POINT3D();
        }
    }

    /// <summary>
    /// Describes a vector
    /// </summary>
    public class VECTOR3D : List<POINT3D>
    {
    }

    /// <summary>
    /// Describes a polygon
    /// </summary>
    public class POLYGON3D
    {
        /// <summary>
        /// ctor
        /// </summary>
        public POLYGON3D()
        {
            this.Vectors = new List<VECTOR3D>();
            this.OpeningVectors = new List<VECTOR3D>();
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IList<VECTOR3D> Vectors
        {
            get;
            private set;
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IList<VECTOR3D> OpeningVectors
        {
            get;
            private set;
        }
    }

    /// <summary>
    /// Describes a shell
    /// </summary>
    public class SHELL
    {
        /// <summary>
        /// ctor
        /// </summary>
        public SHELL()
        {
            this.Polygons = new List<POLYGON3D>();
        }

        /// <summary>
        /// Accessor
        /// </summary>
        public IList<POLYGON3D> Polygons
        {
            get;
            private set;
        }
    }
}
