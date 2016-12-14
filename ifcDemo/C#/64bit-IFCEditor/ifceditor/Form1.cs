using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using IfcEngine;

namespace ifceditor
{
    public partial class Form1 : Form
    {
        private Int64 model;
        private Entity[] myEntities;
        private List<Instance> myInstances = new List<Instance>();

        public Form1()
        {
            model = 0;
            InitializeComponent();
            textBoxFileName.Text = AppDomain.CurrentDomain.BaseDirectory + "myFile.ifc";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string fileName = textBoxFileName.Text;

            if (model != 0)
            {
                IfcEngine.x64.sdaiCloseModel(model);
            }

            model = IfcEngine.x64.sdaiOpenModelBN(0, fileName, "IFC2X3_TC1.exp");
            if (model != 0)
            {
                IntPtr outputValue = IntPtr.Zero;
                IfcEngine.x64.GetSPFFHeaderItem(model, 9, 0, IfcEngine.x64.sdaiSTRING, out outputValue);
                string s = Marshal.PtrToStringAnsi(outputValue);
                if (s.Contains("IFC2") == false)
                {
                    IfcEngine.x64.sdaiCloseModel(model);
                    model = 0;
                    if (s.Contains("IFC4") == true)
                    {
                        model = IfcEngine.x64.sdaiOpenModelBN(0, fileName, "IFC4.exp");
                    }
                }
            }

            treeViewLP.Nodes.Clear();
            if (model != 0)
            {
                Int64 cnt = IfcEngine.x64.engiGetEntityCount(model),
                      i = 0;

                myEntities = new Entity[cnt];
                while (i < cnt) {
                    myEntities[i] = new Entity(IfcEngine.x64.engiGetEntityElement(model, i));
                    myEntities[i].attributeCnt = IfcEngine.x64.engiGetEntityNoArguments(myEntities[i].ifcEntity);
                    myEntities[i].instanceCnt = IfcEngine.x64.sdaiGetMemberCount(IfcEngine.x64.sdaiGetEntityExtent(model, myEntities[i].ifcEntity));
                    i++;
                }

                while (i != 0) {
                    i--;
                    Int64 ifcParentEntity = IfcEngine.x64.engiGetEntityParent(myEntities[i].ifcEntity);
                    if (ifcParentEntity != 0)
                    {
                        Int64 j = 0;
                        while (j < cnt)
                        {
                            if (ifcParentEntity == myEntities[j].ifcEntity)
                            {
                                if (myEntities[j].child != null)
                                {
                                    myEntities[i].next = myEntities[j].child;
                                }
                                myEntities[j].child = myEntities[i];
                                myEntities[i].parent = myEntities[j];
                            }
                            j++;
                        }
                    }
                }

                while (i < cnt)
                {
                    if (myEntities[i].parent == null)
                    {
                        InsertItemEntityLP(myEntities[i], null);
                    }
                    i++;
                }
            }

            InitRightPane(null);
        }


        //
        //  Left Pane
        //

        private Entity GetEntity(TreeNode node)
        {
            Int64 i = 0;
            while (i < myEntities.Count())
            {
                if (myEntities[i].node == node)
                {
                    return myEntities[i];
                }
                i++;
            }
            return null;
        }

        private Int64 NestedInstanceCnt(Entity myEntity)
        {
            Int64 instanceCnt = myEntity.instanceCnt;
            Entity child = myEntity.child;
            while (child != null) {
                instanceCnt += NestedInstanceCnt(child);
                child = child.next;
            }
            return instanceCnt;
        }

        private string CreateEntityName(Entity myEntity)
        {
            IntPtr entityNamePtr = IntPtr.Zero;
            IfcEngine.x64.engiGetEntityName(myEntity.ifcEntity, IfcEngine.x64.sdaiSTRING, out entityNamePtr);
            string entityName = Marshal.PtrToStringAnsi(entityNamePtr);

            Int64 instanceCnt = NestedInstanceCnt(myEntity);
            if (instanceCnt != 0)
            {
                entityName += "  " + myEntity.instanceCnt;
                if (myEntity.child != null)
                {
                    entityName += " / " + instanceCnt;
                }
            }
            return  entityName;
        }

        private void InsertItemAttributeLP(Entity myEntity, Int64 index)
        {
            IntPtr argumentNamePtr = IntPtr.Zero;
            IfcEngine.x64.engiGetEntityArgumentName(myEntity.ifcEntity, index, IfcEngine.x64.sdaiSTRING, out argumentNamePtr);
            string argumentName = Marshal.PtrToStringAnsi(argumentNamePtr);

            myEntity.nodeAttributes.Nodes.Add(argumentName);
        }

        private void InsertItemAttributesLP(Entity myEntity)
        {
            myEntity.nodeAttributes = new TreeNode("attributes");
            myEntity.node.Nodes.Add(myEntity.nodeAttributes);

            Int64 noArguments = IfcEngine.x64.engiGetEntityNoArguments(myEntity.ifcEntity), i = 0;
            if (myEntity.parent != null) {
                i = myEntity.parent.attributeCnt;
            }
            while  (i < noArguments) {
                InsertItemAttributeLP(myEntity, i++);
            }
        }

        private void InsertItemSubTypesLP(Entity myEntity)
        {
            Entity child = myEntity.child;
            if (child != null)
            {
                myEntity.nodeSubTypes = new TreeNode("subtypes");
                myEntity.node.Nodes.Add(myEntity.nodeSubTypes);

                while (child != null)
                {
                    InsertItemEntityLP(child, myEntity);
                    child = child.next;
                }
            }
        }

        private void InsertItemEntityLP(Entity myEntity, Entity myParent)
        {
            myEntity.node = new TreeNode(CreateEntityName(myEntity));

            if (myParent == null)
            {
                treeViewLP.Nodes.Add(myEntity.node);
            }
            else
            {
                myParent.nodeSubTypes.Nodes.Add(myEntity.node);
            }

            InsertItemSubTypesLP(myEntity);

            if (myEntity.attributeCnt != 0 && (myEntity.parent == null || myEntity.parent.attributeCnt < myEntity.attributeCnt))
            {
                InsertItemAttributesLP(myEntity);
            }
        }

        private void treeViewLP_AfterSelect(object sender, System.Windows.Forms.TreeViewEventArgs e)
        {
            if (e.Action == TreeViewAction.ByMouse)
            {
                Entity myEntity = GetEntity(e.Node);
                InitRightPane(myEntity);
            }
        }

        //
        //  Right Pane
        //

        private string CreateAttributeTextADB(ref bool children, Int64 ADB)
        {
            string buffer = "";
            switch (IfcEngine.x64.sdaiGetADBType(ADB)) {
                case IfcEngine.x64.sdaiADB:
                    Int64 ADBsub = 0;
                    IfcEngine.x64.sdaiGetADBValue(ADB, IfcEngine.x64.sdaiADB, out ADBsub);
                    if (ADBsub != 0)
                    {
                        IntPtr pathPtr = IntPtr.Zero;
                        IfcEngine.x64.sdaiGetADBTypePath(ADBsub, IfcEngine.x64.sdaiSTRING, out pathPtr);
                        buffer += Marshal.PtrToStringAnsi(pathPtr) + "(" + CreateAttributeTextADB(ref children, ADBsub) + ")";
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x64.sdaiAGGR:
                    Int64 value = 0;
                    IfcEngine.x64.sdaiGetADBValue(ADB, IfcEngine.x64.sdaiAGGR, out value);
                    if (value != 0)
                    {
                        buffer += "(";
                        Int64 cnt = IfcEngine.x64.sdaiGetMemberCount(value), i = 0;
                        while  (i < cnt)
                        {
                            if (i > 0)
                            {
                                buffer += ", ";
                            }
                            buffer += "???";
                            i++;
                        }
                        buffer += ")";
                    } else {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x64.sdaiBOOLEAN:
                case IfcEngine.x64.sdaiENUM:
                case IfcEngine.x64.sdaiLOGICAL:
                    IntPtr valuePtrEnum = IntPtr.Zero;
                    IfcEngine.x64.sdaiGetADBValue(ADB, IfcEngine.x64.sdaiSTRING, out valuePtrEnum);
                    if (valuePtrEnum != IntPtr.Zero)
                    {
                        buffer += Marshal.PtrToStringAnsi(valuePtrEnum);
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x64.sdaiINSTANCE:
                    Int64 localIfcInstance = 0;
                    IfcEngine.x64.sdaiGetADBValue(ADB, IfcEngine.x64.sdaiINSTANCE, out localIfcInstance);
                    if (localIfcInstance != 0)
                    {
                        buffer += "#" + IfcEngine.x64.internalGetP21Line(localIfcInstance).ToString();
                        children = true;
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x64.sdaiINTEGER:
                    Int64 valueInt32 = 0;
                    IfcEngine.x64.sdaiGetADBValue(ADB, IfcEngine.x64.sdaiINTEGER, out valueInt32);
                    buffer += valueInt32.ToString();
                    break;
                case IfcEngine.x64.sdaiSTRING:
                    IntPtr valuePtrString = IntPtr.Zero;
                    IfcEngine.x64.sdaiGetADBValue(ADB, IfcEngine.x64.sdaiSTRING, out valuePtrString);
                    if (valuePtrString != IntPtr.Zero)
                    {
                        buffer += "'" + Marshal.PtrToStringAnsi(valuePtrString) + "'";
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x64.sdaiREAL:
                    double valueDouble = 0;
                    IfcEngine.x64.sdaiGetADBValue(ADB, IfcEngine.x64.sdaiREAL, out valueDouble);
                    buffer += valueDouble.ToString();
                    break;
            }
            return buffer;
        }

        private string CreateAttributeTextAGGR(ref bool children, Int64 aggregate, Int64 elementIndex)
        {
            string buffer = "";
            Int64 aggregateType = 0;
            IfcEngine.x64.engiGetAggrType(aggregate, ref aggregateType);
            switch (aggregateType) {
                case IfcEngine.x64.sdaiADB:
                    Int64 ADB = 0;
                    IfcEngine.x64.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x64.sdaiADB, out ADB);
                    if (ADB != 0)
                    {
                        IntPtr pathPtr = IntPtr.Zero;
                        IfcEngine.x64.sdaiGetADBTypePath(ADB, IfcEngine.x64.sdaiSTRING, out pathPtr);
                        buffer += Marshal.PtrToStringAnsi(pathPtr) + "(" + CreateAttributeTextADB(ref children, ADB) + ")";
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x64.sdaiAGGR:
                    Int64 value = 0;
                    IfcEngine.x64.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x64.sdaiAGGR, out value);
                    if (value != 0)
                    {
                        buffer += "(";
                        Int64 cnt = IfcEngine.x64.sdaiGetMemberCount(value), i = 0;
                        while (i < cnt  &&  i < 8)
                        {
                            if (i > 0)
                            {
                                buffer += ", ";
                            }
                            buffer += CreateAttributeTextAGGR(ref children, value, i++);
                        }
                        if (i < cnt)
                        {
                            buffer += ", ...";
                        }
                        buffer += ")";
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x64.sdaiBOOLEAN:
                case IfcEngine.x64.sdaiENUM:
                case IfcEngine.x64.sdaiLOGICAL:
                    IntPtr valuePtrEnum = IntPtr.Zero;
                    IfcEngine.x64.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x64.sdaiSTRING, out valuePtrEnum);
                    if (valuePtrEnum != IntPtr.Zero)
                    {
                        buffer += Marshal.PtrToStringAnsi(valuePtrEnum);
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x64.sdaiINSTANCE:
                    Int64 localIfcInstance = 0;
                    IfcEngine.x64.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x64.sdaiINSTANCE, out localIfcInstance);
                    if (localIfcInstance != 0)
                    {
                        buffer += "#" + IfcEngine.x64.internalGetP21Line(localIfcInstance).ToString();
                        children = true;
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x64.sdaiINTEGER:
                    Int64 valueInt32 = 0;
                    IfcEngine.x64.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x64.sdaiINTEGER, out valueInt32);
                    buffer += valueInt32.ToString();
                    break;
                case IfcEngine.x64.sdaiSTRING:
                    IntPtr valueStringPtr = IntPtr.Zero;
                    IfcEngine.x64.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x64.sdaiSTRING, out valueStringPtr);
                    if (valueStringPtr != IntPtr.Zero)
                    {
                        buffer += "'" + Marshal.PtrToStringAnsi(valueStringPtr) + "'";
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x64.sdaiREAL:
                    double valueDouble = 0;
                    IfcEngine.x64.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x64.sdaiREAL, out valueDouble);
                    buffer += valueDouble.ToString();
                    break;
            }
            return buffer;
        }

        private string CreateAttributeText(ref bool children, Int64 ifcInstance, string attributeName, Int64 attributeType)
        {
            string buffer = "";
            switch  (attributeType) {
                case IfcEngine.x64.sdaiADB:
                    Int64 ADB = 0;
                    IfcEngine.x64.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x64.sdaiADB, out ADB);
                    if (ADB != 0)
                    {
                        IntPtr pathPtr = IntPtr.Zero;
                        IfcEngine.x64.sdaiGetADBTypePath(ADB, IfcEngine.x64.sdaiSTRING, out pathPtr);
                        buffer += Marshal.PtrToStringAnsi(pathPtr) + "(" + CreateAttributeTextADB(ref children, ADB) + ")";
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x64.sdaiAGGR:
                    Int64 valueInt32 = 0;
                    IfcEngine.x64.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x64.sdaiAGGR, out valueInt32);
                    if (valueInt32 != 0)
                    {
                        buffer += "(";
                        Int64 cnt = IfcEngine.x64.sdaiGetMemberCount(valueInt32), i = 0;
                        while  (i < cnt  &&  i < 8)
                        {
                            if (i > 0)
                            {
                                buffer += ", ";
                            }
                            buffer += CreateAttributeTextAGGR(ref children, valueInt32, i++);
                        }
                        if (i < cnt)
                        {
                            buffer += ", ...";
                        }
                        buffer += ")";
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x64.sdaiBOOLEAN:
                case IfcEngine.x64.sdaiENUM:
                case IfcEngine.x64.sdaiLOGICAL:
                    IntPtr valuePtrEnum = IntPtr.Zero;
                    IfcEngine.x64.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x64.sdaiSTRING, out valuePtrEnum);
                    if (valuePtrEnum != IntPtr.Zero)
                    {
                        buffer += Marshal.PtrToStringAnsi(valuePtrEnum);
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x64.sdaiINSTANCE:
                    Int64 localIfcInstance = 0;
                    IfcEngine.x64.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x64.sdaiINSTANCE, out localIfcInstance);
                    if (localIfcInstance != 0)
                    {
                        buffer += "#" + IfcEngine.x64.internalGetP21Line(localIfcInstance);
                        children = true;
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x64.sdaiINTEGER:
                    Int64 value = 0;
                    IfcEngine.x64.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x64.sdaiINTEGER, out value);
                    buffer +=  value.ToString();
                    break;
                case IfcEngine.x64.sdaiSTRING:
                    IntPtr valuePtrString = IntPtr.Zero;
                    IfcEngine.x64.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x64.sdaiSTRING, out valuePtrString);
                    if (valuePtrString != IntPtr.Zero)
                    {
                        buffer += "'" + Marshal.PtrToStringAnsi(valuePtrString) + "'";
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x64.sdaiREAL:
                    double valueDouble = 0;
                    IfcEngine.x64.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x64.sdaiREAL, out valueDouble);
                    buffer += valueDouble.ToString();
                    break;
            }
            return buffer;
        }

        private void GetAttributeReferencesADB(Int64 ADB, TreeNode parentNode)
        {
            switch (IfcEngine.x64.sdaiGetADBType(ADB)) {
                case IfcEngine.x64.sdaiADB:
                    Int64 ADBsub = 0;
                    IfcEngine.x64.sdaiGetADBValue(ADB, IfcEngine.x64.sdaiADB, out ADBsub);
                    if (ADBsub != 0) {
                        GetAttributeReferencesADB(ADBsub, parentNode);
                    }
                    break;
                case IfcEngine.x64.sdaiAGGR:
                    Int64 value = 0;
                    IfcEngine.x64.sdaiGetADBValue(ADB, IfcEngine.x64.sdaiAGGR, out value);
                    if (value != 0) {
                        Int64 cnt = IfcEngine.x64.sdaiGetMemberCount(value), i = 0;
                        while  (i < cnt) {
                            GetAttributeReferencesAGGR(value, i++, parentNode);
                        }
                    }
                    break;
                case IfcEngine.x64.sdaiBOOLEAN:
                case IfcEngine.x64.sdaiENUM:
                case IfcEngine.x64.sdaiLOGICAL:
                    break;
                case IfcEngine.x64.sdaiINSTANCE:
                    Int64 localIfcInstance = 0;
                    IfcEngine.x64.sdaiGetADBValue(ADB, IfcEngine.x64.sdaiINSTANCE, out localIfcInstance);
                    if (localIfcInstance != 0) {
                        InsertItemInstance(localIfcInstance, parentNode);
                    }
                    break;
                case IfcEngine.x64.sdaiINTEGER:
                    break;
                case IfcEngine.x64.sdaiSTRING:
                    break;
                case IfcEngine.x64.sdaiREAL:
                    break;
            }
        }

        private void GetAttributeReferencesAGGR(Int64 aggregate, Int64 elementIndex, TreeNode parentNode)
        {
            Int64 aggregateType = 0;
            IfcEngine.x64.engiGetAggrType(aggregate, ref aggregateType);
            switch (aggregateType) {
                case IfcEngine.x64.sdaiADB:
                    Int64 ADB = 0;
                    IfcEngine.x64.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x64.sdaiADB, out ADB);
                    if (ADB != 0)
                    {
                        GetAttributeReferencesADB(ADB, parentNode);
                    }
                    break;
                case IfcEngine.x64.sdaiAGGR:
                    Int64 value = 0;
                    IfcEngine.x64.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x64.sdaiAGGR, out value);
                    if (value != 0)
                    {
                        Int64 cnt = IfcEngine.x64.sdaiGetMemberCount(value), i = 0;
                        while (i < cnt)
                        {
                            GetAttributeReferencesAGGR(value, i++, parentNode);
                        }
                    }
                    break;
                case IfcEngine.x64.sdaiBOOLEAN:
                case IfcEngine.x64.sdaiENUM:
                case IfcEngine.x64.sdaiLOGICAL:
                    break;
                case IfcEngine.x64.sdaiINSTANCE:
                    Int64 localIfcInstance = 0;
                    IfcEngine.x64.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x64.sdaiINSTANCE, out localIfcInstance);
                    if (localIfcInstance != 0)
                    {
                        InsertItemInstance(localIfcInstance, parentNode);
                    }
                    break;
                case IfcEngine.x64.sdaiINTEGER:
                    break;
                case IfcEngine.x64.sdaiSTRING:
                    break;
                case IfcEngine.x64.sdaiREAL:
                    break;
            }
        }

        private void GetAttributeReferences(Int64 ifcInstance, string attributeName, Int64 attributeType, TreeNode parentNode)
        {
            switch (attributeType) {
                case IfcEngine.x64.sdaiADB:
                    Int64 ADB = 0;
                    IfcEngine.x64.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x64.sdaiADB, out ADB);
                    if (ADB != 0) {
                        GetAttributeReferencesADB(ADB, parentNode);
                    }
                    break;
                case IfcEngine.x64.sdaiAGGR:
                    Int64 value = 0;
                    IfcEngine.x64.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x64.sdaiAGGR, out value);
                    if (value != 0) {
                        Int64 cnt = IfcEngine.x64.sdaiGetMemberCount(value), i = 0;
                        while  (i < cnt) {
                            GetAttributeReferencesAGGR(value, i++, parentNode);
                        }
                    }
                    break;
                case IfcEngine.x64.sdaiBOOLEAN:
                case IfcEngine.x64.sdaiENUM:
                case IfcEngine.x64.sdaiLOGICAL:
                    break;
                case IfcEngine.x64.sdaiINSTANCE:
                    Int64 localIfcInstance = 0;
                    IfcEngine.x64.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x64.sdaiINSTANCE, out localIfcInstance);
                    if (localIfcInstance != 0) {
                        InsertItemInstance(localIfcInstance, parentNode);
                    }
                    break;
                case IfcEngine.x64.sdaiINTEGER:
                    break;
                case IfcEngine.x64.sdaiSTRING:
                    break;
                case IfcEngine.x64.sdaiREAL:
                    break;
            }
        }

        private string CreateInstanceName(Int64 ifcInstance)
        {
            string instanceName = "#" + IfcEngine.x64.internalGetP21Line(ifcInstance) + " = ";

            IntPtr entityNamePtr = IntPtr.Zero;
            IfcEngine.x64.engiGetEntityName(IfcEngine.x64.sdaiGetInstanceType(ifcInstance), IfcEngine.x64.sdaiSTRING, out entityNamePtr);
            instanceName += Marshal.PtrToStringAnsi(entityNamePtr) + "()";

            return instanceName;
        }

        public void InsertItemInstanceEntity(Int64 ifcEntity, TreeNode parent)
        {
            IntPtr entityNamePtr = IntPtr.Zero;
            IfcEngine.x64.engiGetEntityName(ifcEntity, IfcEngine.x64.sdaiSTRING, out entityNamePtr);
            string entityName = Marshal.PtrToStringAnsi(entityNamePtr);

            parent.Nodes.Add(entityName);
        }

        private void InsertItemInstance(Int64 ifcInstance, TreeNode parent)
        {
            if (ifcInstance != 0)
            {
                TreeNode node;
                string instanceName = CreateInstanceName(ifcInstance);
                if (parent == null)
                {
                    node = treeViewRP.Nodes.Add(instanceName);
                }
                else
                {
                    node = parent.Nodes.Add(instanceName);
                }
                myInstances.Add(new Instance(ifcInstance, node));

                node.Nodes.Add("??");
            }
        }

        private void InitRightPane(Entity myEntity)
        {
            myInstances.Clear();
            treeViewRP.Nodes.Clear();

            if (myEntity != null) {
                Int64 ifcObjects = IfcEngine.x64.sdaiGetEntityExtent(model, myEntity.ifcEntity),
                      ifcObjectsCnt = IfcEngine.x64.sdaiGetMemberCount(ifcObjects), i = 0;
                while (i < ifcObjectsCnt)
                {
                    Int64 ifcObject = 0;
                    IfcEngine.x64.engiGetAggrElement(ifcObjects, i++, IfcEngine.x64.sdaiINSTANCE, out ifcObject);
                    InsertItemInstance(ifcObject, null);
                }
            }
        }

        private void InsertItemInstanceEntityRP(Int64 ifcEntity, TreeNode parentNode)
        {
            IntPtr entityNamePtr = IntPtr.Zero;
            IfcEngine.x64.engiGetEntityName(ifcEntity, IfcEngine.x64.sdaiSTRING, out entityNamePtr);
            string entityName = Marshal.PtrToStringAnsi(entityNamePtr);

            parentNode.Nodes.Add(entityName);
        }

        private void InsertItemInstanceAttributeRP(Int64 ifcInstance, string attributeName, Int64 attributeType, TreeNode parentNode)
        {
            string instanceAttributeName = "  " + attributeName + " = ";

            bool children = false;
            instanceAttributeName += CreateAttributeText(ref children, ifcInstance, attributeName, attributeType);

            TreeNode myNode = parentNode.Nodes.Add(instanceAttributeName);
            if (children)
            {
                Instance myInstance = new Instance(ifcInstance, myNode);
                myInstance.attributeName = attributeName;
                myInstance.attributeType = attributeType;
                myInstances.Add(myInstance);

                myNode.Nodes.Add("??");
            }
        }

        private Int64 InsertItemAttributesRP(Int64 ifcEntity, Int64 ifcInstance, TreeNode parentNode)
        {
            if (ifcEntity != 0)
            {
                //
                //  Walk over the parents
                //
                Int64 attributeCnt = InsertItemAttributesRP(IfcEngine.x64.engiGetEntityParent(ifcEntity), ifcInstance, parentNode), attributeType;

                //
                //  Start with Entity name
                //
                InsertItemInstanceEntity(ifcEntity, parentNode);

                //
                //	Walk over attributes
                //
                while (attributeCnt < IfcEngine.x64.engiGetEntityNoArguments(ifcEntity))
                {
                    IntPtr attributeNamePtr = IntPtr.Zero;
                    attributeType = 0;
                    IfcEngine.x64.engiGetEntityArgumentName(ifcEntity, attributeCnt, IfcEngine.x64.sdaiSTRING, out attributeNamePtr);
                    IfcEngine.x64.engiGetEntityArgumentType(ifcEntity, attributeCnt, ref attributeType);

                    string attributeName = Marshal.PtrToStringAnsi(attributeNamePtr);
                    InsertItemInstanceAttributeRP(ifcInstance, attributeName, attributeType, parentNode);

                    attributeCnt++;
                }

                return attributeCnt;
            }

            return 0;
        }

        private void treeViewRP_BeforeExpand(object sender, System.Windows.Forms.TreeViewCancelEventArgs e)
        {
            Instance myInstance = null;
            Int32 i = 0;
            while  (i < myInstances.Count())
            {
                if (myInstances.ElementAt(i).node == e.Node) {
                    myInstance = myInstances.ElementAt(i);
                }
                i++;
            }

            if (myInstance != null  &&  myInstance.expanded == false)
            {
                e.Node.Nodes.Clear();
                if (myInstance.attributeName != null)
                {
                    GetAttributeReferences(myInstance.ifcInstance, myInstance.attributeName, myInstance.attributeType, myInstance.node);
                }
                else
                {
                    InsertItemAttributesRP(IfcEngine.x64.sdaiGetInstanceType(myInstance.ifcInstance), myInstance.ifcInstance, myInstance.node);
                }
                myInstance.expanded = true;
            }
        }

        public class Entity
        {
            public Int64 ifcEntity;
            public TreeNode node;
            public TreeNode nodeSubTypes;
            public TreeNode nodeAttributes;
            public Int64 attributeCnt;
            public Int64 instanceCnt;

            public Entity parent;
            public Entity child;
            public Entity next;

            public Entity(Int64 ifcEntity)
            {
                this.ifcEntity = ifcEntity;
            }
        }

        public class Instance
        {
            public Int64 ifcInstance;
            public TreeNode node;
            public string attributeName;
            public Int64 attributeType;

            public bool expanded;

            public Instance(Int64 ifcInstance, TreeNode node)
            {
                this.ifcInstance = ifcInstance;
                this.node = node;

                attributeName = null;
                attributeType = 0;

                expanded = false;
            }
        }
    }
}
