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
        private Int32 model;
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
                IfcEngine.x86.sdaiCloseModel(model);
            }

            model = IfcEngine.x86.sdaiOpenModelBN(0, fileName, "IFC2X3_TC1.exp");
            if (model != 0)
            {
                IntPtr outputValue = IntPtr.Zero;
                IfcEngine.x86.GetSPFFHeaderItem(model, 9, 0, IfcEngine.x86.sdaiSTRING, out outputValue);
                string s = Marshal.PtrToStringAnsi(outputValue);
                if (s.Contains("IFC2") == false)
                {
                    IfcEngine.x86.sdaiCloseModel(model);
                    model = 0;
                    if (s.Contains("IFC4") == true)
                    {
                        model = IfcEngine.x86.sdaiOpenModelBN(0, fileName, "IFC4.exp");
                    }
                }
            }

            treeViewLP.Nodes.Clear();
            if (model != 0)
            {
                Int32 cnt = IfcEngine.x86.engiGetEntityCount(model),
                      i = 0;

                myEntities = new Entity[cnt];
                while (i < cnt) {
                    myEntities[i] = new Entity(IfcEngine.x86.engiGetEntityElement(model, i));
                    myEntities[i].attributeCnt = IfcEngine.x86.engiGetEntityNoArguments(myEntities[i].ifcEntity);
                    myEntities[i].instanceCnt = IfcEngine.x86.sdaiGetMemberCount(IfcEngine.x86.sdaiGetEntityExtent(model, myEntities[i].ifcEntity));
                    i++;
                }

                while (i != 0) {
                    i--;
                    Int32 ifcParentEntity = IfcEngine.x86.engiGetEntityParent(myEntities[i].ifcEntity);
                    if (ifcParentEntity != 0)
                    {
                        Int32 j = 0;
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
            Int32 i = 0;
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

        private Int32 NestedInstanceCnt(Entity myEntity)
        {
            Int32 instanceCnt = myEntity.instanceCnt;
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
            IfcEngine.x86.engiGetEntityName(myEntity.ifcEntity, IfcEngine.x86.sdaiSTRING, out entityNamePtr);
            string entityName = Marshal.PtrToStringAnsi(entityNamePtr);

            Int32 instanceCnt = NestedInstanceCnt(myEntity);
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

        private void InsertItemAttributeLP(Entity myEntity, Int32 index)
        {
            IntPtr argumentNamePtr = IntPtr.Zero;
            IfcEngine.x86.engiGetEntityArgumentName(myEntity.ifcEntity, index, IfcEngine.x86.sdaiSTRING, out argumentNamePtr);
            string argumentName = Marshal.PtrToStringAnsi(argumentNamePtr);

            myEntity.nodeAttributes.Nodes.Add(argumentName);
        }

        private void InsertItemAttributesLP(Entity myEntity)
        {
            myEntity.nodeAttributes = new TreeNode("attributes");
            myEntity.node.Nodes.Add(myEntity.nodeAttributes);

            Int32 noArguments = IfcEngine.x86.engiGetEntityNoArguments(myEntity.ifcEntity), i = 0;
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

        private string CreateAttributeTextADB(ref bool children, Int32 ADB)
        {
            string buffer = "";
            switch (IfcEngine.x86.sdaiGetADBType(ADB)) {
                case IfcEngine.x86.sdaiADB:
                    Int32 ADBsub = 0;
                    IfcEngine.x86.sdaiGetADBValue(ADB, IfcEngine.x86.sdaiADB, out ADBsub);
                    if (ADBsub != 0)
                    {
                        IntPtr pathPtr = IntPtr.Zero;
                        IfcEngine.x86.sdaiGetADBTypePath(ADBsub, IfcEngine.x86.sdaiSTRING, out pathPtr);
                        buffer += Marshal.PtrToStringAnsi(pathPtr) + "(" + CreateAttributeTextADB(ref children, ADBsub) + ")";
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x86.sdaiAGGR:
                    Int32 value = 0;
                    IfcEngine.x86.sdaiGetADBValue(ADB, IfcEngine.x86.sdaiAGGR, out value);
                    if (value != 0)
                    {
                        buffer += "(";
                        Int32 cnt = IfcEngine.x86.sdaiGetMemberCount(value), i = 0;
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
                case IfcEngine.x86.sdaiBOOLEAN:
                case IfcEngine.x86.sdaiENUM:
                case IfcEngine.x86.sdaiLOGICAL:
                    IntPtr valuePtrEnum = IntPtr.Zero;
                    IfcEngine.x86.sdaiGetADBValue(ADB, IfcEngine.x86.sdaiSTRING, out valuePtrEnum);
                    if (valuePtrEnum != IntPtr.Zero)
                    {
                        buffer += Marshal.PtrToStringAnsi(valuePtrEnum);
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x86.sdaiINSTANCE:
                    Int32 localIfcInstance = 0;
                    IfcEngine.x86.sdaiGetADBValue(ADB, IfcEngine.x86.sdaiINSTANCE, out localIfcInstance);
                    if (localIfcInstance != 0)
                    {
                        buffer += "#" + IfcEngine.x86.internalGetP21Line(localIfcInstance).ToString();
                        children = true;
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x86.sdaiINTEGER:
                    Int32 valueInt32 = 0;
                    IfcEngine.x86.sdaiGetADBValue(ADB, IfcEngine.x86.sdaiINTEGER, out valueInt32);
                    buffer += valueInt32.ToString();
                    break;
                case IfcEngine.x86.sdaiSTRING:
                    IntPtr valuePtrString = IntPtr.Zero;
                    IfcEngine.x86.sdaiGetADBValue(ADB, IfcEngine.x86.sdaiSTRING, out valuePtrString);
                    if (valuePtrString != IntPtr.Zero)
                    {
                        buffer += "'" + Marshal.PtrToStringAnsi(valuePtrString) + "'";
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x86.sdaiREAL:
                    double valueDouble = 0;
                    IfcEngine.x86.sdaiGetADBValue(ADB, IfcEngine.x86.sdaiREAL, out valueDouble);
                    buffer += valueDouble.ToString();
                    break;
            }
            return buffer;
        }

        private string CreateAttributeTextAGGR(ref bool children, Int32 aggregate, Int32 elementIndex)
        {
            string buffer = "";
            Int32 aggregateType = 0;
            IfcEngine.x86.engiGetAggrType(aggregate, ref aggregateType);
            switch (aggregateType) {
                case IfcEngine.x86.sdaiADB:
                    Int32 ADB = 0;
                    IfcEngine.x86.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x86.sdaiADB, out ADB);
                    if (ADB != 0)
                    {
                        IntPtr pathPtr = IntPtr.Zero;
                        IfcEngine.x86.sdaiGetADBTypePath(ADB, IfcEngine.x86.sdaiSTRING, out pathPtr);
                        buffer += Marshal.PtrToStringAnsi(pathPtr) + "(" + CreateAttributeTextADB(ref children, ADB) + ")";
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x86.sdaiAGGR:
                    Int32 value = 0;
                    IfcEngine.x86.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x86.sdaiAGGR, out value);
                    if (value != 0)
                    {
                        buffer += "(";
                        Int32 cnt = IfcEngine.x86.sdaiGetMemberCount(value), i = 0;
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
                case IfcEngine.x86.sdaiBOOLEAN:
                case IfcEngine.x86.sdaiENUM:
                case IfcEngine.x86.sdaiLOGICAL:
                    IntPtr valuePtrEnum = IntPtr.Zero;
                    IfcEngine.x86.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x86.sdaiSTRING, out valuePtrEnum);
                    if (valuePtrEnum != IntPtr.Zero)
                    {
                        buffer += Marshal.PtrToStringAnsi(valuePtrEnum);
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x86.sdaiINSTANCE:
                    Int32 localIfcInstance = 0;
                    IfcEngine.x86.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x86.sdaiINSTANCE, out localIfcInstance);
                    if (localIfcInstance != 0)
                    {
                        buffer += "#" + IfcEngine.x86.internalGetP21Line(localIfcInstance).ToString();
                        children = true;
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x86.sdaiINTEGER:
                    Int32 valueInt32 = 0;
                    IfcEngine.x86.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x86.sdaiINTEGER, out valueInt32);
                    buffer += valueInt32.ToString();
                    break;
                case IfcEngine.x86.sdaiSTRING:
                    IntPtr valueStringPtr = IntPtr.Zero;
                    IfcEngine.x86.engiGetAggrElement(aggregate, elementIndex,  IfcEngine.x86.sdaiSTRING, out valueStringPtr);
                    if (valueStringPtr != IntPtr.Zero)
                    {
                        buffer += "'" + Marshal.PtrToStringAnsi(valueStringPtr) + "'";
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case  IfcEngine.x86.sdaiREAL:
                    double valueDouble = 0;
                    IfcEngine.x86.engiGetAggrElement(aggregate, elementIndex,  IfcEngine.x86.sdaiREAL, out valueDouble);
                    buffer += valueDouble.ToString();
                    break;
            }
            return buffer;
        }

        private string CreateAttributeText(ref bool children, Int32 ifcInstance, string attributeName, Int32 attributeType)
        {
            string buffer = "";
            switch  (attributeType) {
                case IfcEngine.x86.sdaiADB:
                    Int32 ADB = 0;
                    IfcEngine.x86.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x86.sdaiADB, out ADB);
                    if (ADB != 0)
                    {
                        IntPtr pathPtr = IntPtr.Zero;
                        IfcEngine.x86.sdaiGetADBTypePath(ADB, IfcEngine.x86.sdaiSTRING, out pathPtr);
                        buffer += Marshal.PtrToStringAnsi(pathPtr) + "(" + CreateAttributeTextADB(ref children, ADB) + ")";
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x86.sdaiAGGR:
                    Int32 valueInt32 = 0;
                    IfcEngine.x86.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x86.sdaiAGGR, out valueInt32);
                    if (valueInt32 != 0)
                    {
                        buffer += "(";
                        Int32 cnt = IfcEngine.x86.sdaiGetMemberCount(valueInt32), i = 0;
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
                case IfcEngine.x86.sdaiBOOLEAN:
                case IfcEngine.x86.sdaiENUM:
                case IfcEngine.x86.sdaiLOGICAL:
                    IntPtr valuePtrEnum = IntPtr.Zero;
                    IfcEngine.x86.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x86.sdaiSTRING, out valuePtrEnum);
                    if (valuePtrEnum != IntPtr.Zero)
                    {
                        buffer += Marshal.PtrToStringAnsi(valuePtrEnum);
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x86.sdaiINSTANCE:
                    Int32 localIfcInstance = 0;
                    IfcEngine.x86.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x86.sdaiINSTANCE, out localIfcInstance);
                    if (localIfcInstance != 0)
                    {
                        buffer += "#" + IfcEngine.x86.internalGetP21Line(localIfcInstance);
                        children = true;
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x86.sdaiINTEGER:
                    Int32 value = 0;
                    IfcEngine.x86.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x86.sdaiINTEGER, out value);
                    buffer +=  value.ToString();
                    break;
                case IfcEngine.x86.sdaiSTRING:
                    IntPtr valuePtrString = IntPtr.Zero;
                    IfcEngine.x86.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x86.sdaiSTRING, out valuePtrString);
                    if (valuePtrString != IntPtr.Zero)
                    {
                        buffer += "'" + Marshal.PtrToStringAnsi(valuePtrString) + "'";
                    }
                    else
                    {
                        buffer += "Ø";
                    }
                    break;
                case IfcEngine.x86.sdaiREAL:
                    double valueDouble = 0;
                    IfcEngine.x86.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x86.sdaiREAL, out valueDouble);
                    buffer += valueDouble.ToString();
                    break;
            }
            return buffer;
        }

        private void GetAttributeReferencesADB(Int32 ADB, TreeNode parentNode)
        {
            switch (IfcEngine.x86.sdaiGetADBType(ADB)) {
                case IfcEngine.x86.sdaiADB:
                    Int32 ADBsub = 0;
                    IfcEngine.x86.sdaiGetADBValue(ADB, IfcEngine.x86.sdaiADB, out ADBsub);
                    if (ADBsub != 0) {
                        GetAttributeReferencesADB(ADBsub, parentNode);
                    }
                    break;
                case IfcEngine.x86.sdaiAGGR:
                    Int32 value = 0;
                    IfcEngine.x86.sdaiGetADBValue(ADB, IfcEngine.x86.sdaiAGGR, out value);
                    if (value != 0) {
                        Int32 cnt = IfcEngine.x86.sdaiGetMemberCount(value), i = 0;
                        while  (i < cnt) {
                            GetAttributeReferencesAGGR(value, i++, parentNode);
                        }
                    }
                    break;
                case IfcEngine.x86.sdaiBOOLEAN:
                case IfcEngine.x86.sdaiENUM:
                case IfcEngine.x86.sdaiLOGICAL:
                    break;
                case IfcEngine.x86.sdaiINSTANCE:
                    Int32 localIfcInstance = 0;
                    IfcEngine.x86.sdaiGetADBValue(ADB, IfcEngine.x86.sdaiINSTANCE, out localIfcInstance);
                    if (localIfcInstance != 0) {
                        InsertItemInstance(localIfcInstance, parentNode);
                    }
                    break;
                case IfcEngine.x86.sdaiINTEGER:
                    break;
                case IfcEngine.x86.sdaiSTRING:
                    break;
                case IfcEngine.x86.sdaiREAL:
                    break;
            }
        }

        private void GetAttributeReferencesAGGR(Int32 aggregate, Int32 elementIndex, TreeNode parentNode)
        {
            Int32 aggregateType = 0;
            IfcEngine.x86.engiGetAggrType(aggregate, ref aggregateType);
            switch (aggregateType) {
                case IfcEngine.x86.sdaiADB:
                    Int32 ADB = 0;
                    IfcEngine.x86.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x86.sdaiADB, out ADB);
                    if (ADB != 0)
                    {
                        GetAttributeReferencesADB(ADB, parentNode);
                    }
                    break;
                case IfcEngine.x86.sdaiAGGR:
                    Int32 value = 0;
                    IfcEngine.x86.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x86.sdaiAGGR, out value);
                    if (value != 0)
                    {
                        Int32 cnt = IfcEngine.x86.sdaiGetMemberCount(value), i = 0;
                        while (i < cnt)
                        {
                            GetAttributeReferencesAGGR(value, i++, parentNode);
                        }
                    }
                    break;
                case IfcEngine.x86.sdaiBOOLEAN:
                case IfcEngine.x86.sdaiENUM:
                case IfcEngine.x86.sdaiLOGICAL:
                    break;
                case IfcEngine.x86.sdaiINSTANCE:
                    Int32 localIfcInstance = 0;
                    IfcEngine.x86.engiGetAggrElement(aggregate, elementIndex, IfcEngine.x86.sdaiINSTANCE, out localIfcInstance);
                    if (localIfcInstance != 0)
                    {
                        InsertItemInstance(localIfcInstance, parentNode);
                    }
                    break;
                case IfcEngine.x86.sdaiINTEGER:
                    break;
                case IfcEngine.x86.sdaiSTRING:
                    break;
                case IfcEngine.x86.sdaiREAL:
                    break;
            }
        }

        private void GetAttributeReferences(Int32 ifcInstance, string attributeName, Int32 attributeType, TreeNode parentNode)
        {
            switch (attributeType) {
                case IfcEngine.x86.sdaiADB:
                    Int32 ADB = 0;
                    IfcEngine.x86.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x86.sdaiADB, out ADB);
                    if (ADB != 0) {
                        GetAttributeReferencesADB(ADB, parentNode);
                    }
                    break;
                case IfcEngine.x86.sdaiAGGR:
                    Int32 value = 0;
                    IfcEngine.x86.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x86.sdaiAGGR, out value);
                    if (value != 0) {
                        Int32 cnt = IfcEngine.x86.sdaiGetMemberCount(value), i = 0;
                        while  (i < cnt) {
                            GetAttributeReferencesAGGR(value, i++, parentNode);
                        }
                    }
                    break;
                case IfcEngine.x86.sdaiBOOLEAN:
                case IfcEngine.x86.sdaiENUM:
                case IfcEngine.x86.sdaiLOGICAL:
                    break;
                case IfcEngine.x86.sdaiINSTANCE:
                    Int32 localIfcInstance = 0;
                    IfcEngine.x86.sdaiGetAttrBN(ifcInstance, attributeName, IfcEngine.x86.sdaiINSTANCE, out localIfcInstance);
                    if (localIfcInstance != 0) {
                        InsertItemInstance(localIfcInstance, parentNode);
                    }
                    break;
                case IfcEngine.x86.sdaiINTEGER:
                    break;
                case IfcEngine.x86.sdaiSTRING:
                    break;
                case IfcEngine.x86.sdaiREAL:
                    break;
            }
        }

        private string CreateInstanceName(Int32 ifcInstance)
        {
            string instanceName = "#" + IfcEngine.x86.internalGetP21Line(ifcInstance) + " = ";

            IntPtr entityNamePtr = IntPtr.Zero;
            IfcEngine.x86.engiGetEntityName(IfcEngine.x86.sdaiGetInstanceType(ifcInstance), IfcEngine.x86.sdaiSTRING, out entityNamePtr);
            instanceName += Marshal.PtrToStringAnsi(entityNamePtr) + "()";

            return instanceName;
        }

        public void InsertItemInstanceEntity(Int32 ifcEntity, TreeNode parent)
        {
            IntPtr entityNamePtr = IntPtr.Zero;
            IfcEngine.x86.engiGetEntityName(ifcEntity, IfcEngine.x86.sdaiSTRING, out entityNamePtr);
            string entityName = Marshal.PtrToStringAnsi(entityNamePtr);

            parent.Nodes.Add(entityName);
        }

        private void InsertItemInstance(Int32 ifcInstance, TreeNode parent)
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
                Int32 ifcObjects = IfcEngine.x86.sdaiGetEntityExtent(model, myEntity.ifcEntity),
                      ifcObjectsCnt = IfcEngine.x86.sdaiGetMemberCount(ifcObjects), i = 0;
                while (i < ifcObjectsCnt)
                {
                    Int32 ifcObject = 0;
                    IfcEngine.x86.engiGetAggrElement(ifcObjects, i++, IfcEngine.x86.sdaiINSTANCE, out ifcObject);
                    InsertItemInstance(ifcObject, null);
                }
            }
        }

        private void InsertItemInstanceEntityRP(Int32 ifcEntity, TreeNode parentNode)
        {
            IntPtr entityNamePtr = IntPtr.Zero;
            IfcEngine.x86.engiGetEntityName(ifcEntity, IfcEngine.x86.sdaiSTRING, out entityNamePtr);
            string entityName = Marshal.PtrToStringAnsi(entityNamePtr);

            parentNode.Nodes.Add(entityName);
        }

        private void InsertItemInstanceAttributeRP(Int32 ifcInstance, string attributeName, Int32 attributeType, TreeNode parentNode)
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

        private Int32 InsertItemAttributesRP(Int32 ifcEntity, Int32 ifcInstance, TreeNode parentNode)
        {
            if (ifcEntity != 0)
            {
                //
                //  Walk over the parents
                //
                Int32 attributeCnt = InsertItemAttributesRP(IfcEngine.x86.engiGetEntityParent(ifcEntity), ifcInstance, parentNode), attributeType;

                //
                //  Start with Entity name
                //
                InsertItemInstanceEntity(ifcEntity, parentNode);

                //
                //	Walk over attributes
                //
                while (attributeCnt < IfcEngine.x86.engiGetEntityNoArguments(ifcEntity))
                {
                    IntPtr attributeNamePtr = IntPtr.Zero;
                    attributeType = 0;
                    IfcEngine.x86.engiGetEntityArgumentName(ifcEntity, attributeCnt, IfcEngine.x86.sdaiSTRING, out attributeNamePtr);
                    IfcEngine.x86.engiGetEntityArgumentType(ifcEntity, attributeCnt, ref attributeType);

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
                if  (myInstances.ElementAt(i).node == e.Node) {
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
                    InsertItemAttributesRP(IfcEngine.x86.sdaiGetInstanceType(myInstance.ifcInstance), myInstance.ifcInstance, myInstance.node);
                }
                myInstance.expanded = true;
            }
        }

        public class Entity
        {
            public Int32 ifcEntity;
            public TreeNode node;
            public TreeNode nodeSubTypes;
            public TreeNode nodeAttributes;
            public Int32 attributeCnt;
            public Int32 instanceCnt;

            public Entity parent;
            public Entity child;
            public Entity next;

            public Entity(Int32 ifcEntity)
            {
                this.ifcEntity = ifcEntity;
            }
        }

        public class Instance
        {
            public Int32 ifcInstance;
            public TreeNode node;
            public string attributeName;
            public Int32 attributeType;

            public bool expanded;

            public Instance(Int32 ifcInstance, TreeNode node)
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
