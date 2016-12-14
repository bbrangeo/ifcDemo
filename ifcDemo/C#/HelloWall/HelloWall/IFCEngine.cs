using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
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
    /// IFCEngine.dll wrapper
    /// </summary>
    public class IfcEngine
    {        
        #region Constants

        public const string IFCEngineDLL = @"IFCEngine.dll";

        public const string TRUE = "T";
        public const string FALSE = "F";

        public const IfcHandle sdaiADB = 1;
        public const IfcHandle sdaiAGGR = sdaiADB + 1;
        public const IfcHandle sdaiBINARY = sdaiAGGR + 1;
        public const IfcHandle sdaiBOOLEAN = sdaiBINARY + 1;
        public const IfcHandle sdaiENUM = sdaiBOOLEAN + 1;
        public const IfcHandle sdaiINSTANCE = sdaiENUM + 1;
        public const IfcHandle sdaiINTEGER = sdaiINSTANCE + 1;
        public const IfcHandle sdaiLOGICAL = sdaiINTEGER + 1;
        public const IfcHandle sdaiREAL = sdaiLOGICAL + 1;
        public const IfcHandle sdaiSTRING = sdaiREAL + 1;
        public const IfcHandle sdaiUNICODE = sdaiSTRING + 1;
        public const IfcHandle sdaiEXPRESSSTRING = sdaiUNICODE + 1;
        public const IfcHandle engiGLOBALID = sdaiEXPRESSSTRING + 1;

        public const IfcHandle sdaiARRAY = 1;
        public const IfcHandle sdaiLIST = 2;
        public const IfcHandle sdaiSET = 3;
        public const IfcHandle sdaiBAG = 4;

        #endregion // Constants

        #region Imports

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiCreateModelBNUnicode")]
        public static extern IfcHandle sdaiCreateModelBNUnicode(IfcHandle repository, byte[] strFileName, byte[] strSchemaName);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiCloseModel")]
        public static extern void sdaiCloseModel(IfcHandle model);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiCreateInstanceBN")]
        public static extern IfcHandle sdaiCreateInstanceBN(IfcHandle model, string entityName);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiCreateInstanceBN")]
        public static extern IfcHandle sdaiCreateInstanceBN(IfcHandle model, byte[] entityName);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiPutAttrBN")]
        public static extern void sdaiPutAttrBN(IfcHandle instance, string attributeName, IfcHandle valueType, IfcHandle value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiPutAttrBN")]
        public static extern void sdaiPutAttrBN(IfcHandle instance, string attributeName, IfcHandle valueType, ref IfcHandle value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiPutAttrBN")]
        public static extern void sdaiPutAttrBN(IfcHandle instance, string attributeName, IfcHandle valueType, ref double value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiPutAttrBN")]
        public static extern void sdaiPutAttrBN(IfcHandle instance, string attributeName, IfcHandle valueType, string value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiPutAttrBN")]
        public static extern void sdaiPutAttrBN(IfcHandle instance, string attributeName, IfcHandle valueType, byte[] value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiPutAttrBN")]
        public static extern void sdaiPutAttrBN(IfcHandle instance, byte[] attributeName, IfcHandle valueType, ref IfcHandle value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiPutAttrBN")]
        public static extern void sdaiPutAttrBN(IfcHandle instance, byte[] attributeName, IfcHandle valueType, ref double value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiPutAttrBN")]
        public static extern void sdaiPutAttrBN(IfcHandle instance, byte[] attributeName, IfcHandle valueType, string value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiPutAttrBN")]
        public static extern void sdaiPutAttrBN(IfcHandle instance, byte[] attributeName, IfcHandle valueType, byte[] value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiCreateAggrBN")]
        public static extern IfcHandle sdaiCreateAggrBN(IfcHandle instance, string attributeName);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiCreateAggrBN")]
        public static extern IfcHandle sdaiCreateAggrBN(IfcHandle instance, byte[] attributeName);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiAppend")]
        public static extern void sdaiAppend(IfcHandle list, IfcHandle valueType, IfcHandle value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiAppend")]
        public static extern void sdaiAppend(IfcHandle list, IfcHandle valueType, ref IfcHandle value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiAppend")]
        public static extern void sdaiAppend(IfcHandle list, IfcHandle valueType, ref double value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiAppend")]
        public static extern void sdaiAppend(IfcHandle list, IfcHandle valueType, string value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiAppend")]
        public static extern void sdaiAppend(IfcHandle list, IfcHandle valueType, byte[] value);

        [DllImport(IFCEngineDLL, EntryPoint = "setStringUnicode")]
        public static extern IfcHandle setStringUnicode(IfcHandle unicode);

        [DllImport(IFCEngineDLL, EntryPoint = "getTimeStamp")]
        public static extern IfcHandle getTimeStamp(IfcHandle model);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiCreateADB")]
        public static extern IfcHandle sdaiCreateADB(IfcHandle valueType, ref IfcHandle value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiCreateADB")]
        public static extern IfcHandle sdaiCreateADB(IfcHandle valueType, ref double value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiCreateADB")]
        public static extern IfcHandle sdaiCreateADB(IfcHandle valueType, string value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiCreateADB")]
        public static extern IfcHandle sdaiCreateADB(IfcHandle valueType, byte[] value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiPutADBTypePath")]
        public static extern void sdaiPutADBTypePath(IfcHandle ADB, IfcHandle pathCount, string path);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiPutADBTypePath")]
        public static extern void sdaiPutADBTypePath(IfcHandle ADB, IfcHandle pathCount, byte[] path);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiSaveModelBNUnicode")]
        public static extern void sdaiSaveModelBNUnicode(IfcHandle model, byte[] fileName);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiSaveModelAsXmlBNUnicode")]
        public static extern void sdaiSaveModelAsXmlBNUnicode(IfcHandle model, byte[] fileName);

        [DllImport(IFCEngineDLL, EntryPoint = "SetSPFFHeaderItem")]
        public static extern IfcHandle SetSPFFHeaderItem(IfcHandle model, IfcHandle itemIndex, IfcHandle itemSubIndex, IfcHandle valueType, string value);

        [DllImport(IFCEngineDLL, EntryPoint = "SetSPFFHeaderItem")]
        public static extern IfcHandle SetSPFFHeaderItem(IfcHandle model, IfcHandle itemIndex, IfcHandle itemSubIndex, IfcHandle valueType, byte[] value);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiGetAttrDefinition")]
        public static extern IfcHandle sdaiGetAttrDefinition(IfcHandle entity, string attributeName);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiGetAttrDefinition")]
        public static extern IfcHandle sdaiGetAttrDefinition(IfcHandle entity, byte[] attributeName);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiGetInstanceType")]
        public static extern IfcHandle sdaiGetInstanceType(IfcHandle instance);

        [DllImport(IFCEngineDLL, EntryPoint = "sdaiCreateAggr")]
        public static extern IfcHandle sdaiCreateAggr(IfcHandle instance, IfcHandle attribute);

        #endregion // Imports
    }    
}
