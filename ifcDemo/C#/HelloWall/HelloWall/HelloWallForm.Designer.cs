namespace HelloWall
{
    partial class HelloWallForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this._errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this._cbWall = new System.Windows.Forms.CheckBox();
            this._gbWall = new System.Windows.Forms.GroupBox();
            this._cbWallBoundingBox = new System.Windows.Forms.CheckBox();
            this.label7 = new System.Windows.Forms.Label();
            this._tbWallWidth = new System.Windows.Forms.TextBox();
            this._tbWallName = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this._rbWallBRep = new System.Windows.Forms.RadioButton();
            this._rbWallExtrudedPolygon = new System.Windows.Forms.RadioButton();
            this.label4 = new System.Windows.Forms.Label();
            this._tbWallThickness = new System.Windows.Forms.TextBox();
            this._tbWallHeight = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this._btnCreateIFC = new System.Windows.Forms.Button();
            this._btnCreateIFX = new System.Windows.Forms.Button();
            this._tbSchemaFileName = new System.Windows.Forms.TextBox();
            this._btnSchemaFileName = new System.Windows.Forms.Button();
            this._btnOutputFileName = new System.Windows.Forms.Button();
            this._tbOutputFileName = new System.Windows.Forms.TextBox();
            this._gbGeneral = new System.Windows.Forms.GroupBox();
            this._rbPresentationView = new System.Windows.Forms.RadioButton();
            this._rbCoordinationView = new System.Windows.Forms.RadioButton();
            this._cbUseMeters = new System.Windows.Forms.CheckBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this._cbIncludeQuantites = new System.Windows.Forms.CheckBox();
            this._gbOpening = new System.Windows.Forms.GroupBox();
            this.label12 = new System.Windows.Forms.Label();
            this._tbOpeningWidth = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this._tbOpeningHeight = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this._tbOpeningZOffset = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this._cbOpeningBoundingBox = new System.Windows.Forms.CheckBox();
            this._tbOpeningXOffset = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this._tbOpeningName = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this._rbOpeningBRep = new System.Windows.Forms.RadioButton();
            this._rbOpeningExtrudedPolygon = new System.Windows.Forms.RadioButton();
            this._cbOpening = new System.Windows.Forms.CheckBox();
            this._gbWindow = new System.Windows.Forms.GroupBox();
            this.label18 = new System.Windows.Forms.Label();
            this._tbWindowWidth = new System.Windows.Forms.TextBox();
            this.label19 = new System.Windows.Forms.Label();
            this._tbWindowHeight = new System.Windows.Forms.TextBox();
            this.label17 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this._tbWindowYOffset = new System.Windows.Forms.TextBox();
            this._cbWindowBoundingBox = new System.Windows.Forms.CheckBox();
            this._tbWindowThickness = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this._tbWindowName = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this._rbWindowBRep = new System.Windows.Forms.RadioButton();
            this._rbWindowExtrudedPolygon = new System.Windows.Forms.RadioButton();
            this._cbWindow = new System.Windows.Forms.CheckBox();
            this._btnClose = new System.Windows.Forms.Button();
            this._btnTestMode = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this._errorProvider)).BeginInit();
            this._gbWall.SuspendLayout();
            this._gbGeneral.SuspendLayout();
            this._gbOpening.SuspendLayout();
            this._gbWindow.SuspendLayout();
            this.SuspendLayout();
            // 
            // _errorProvider
            // 
            this._errorProvider.ContainerControl = this;
            // 
            // _cbWall
            // 
            this._cbWall.AutoSize = true;
            this._cbWall.Location = new System.Drawing.Point(10, 19);
            this._cbWall.Name = "_cbWall";
            this._cbWall.Size = new System.Drawing.Size(59, 17);
            this._cbWall.TabIndex = 0;
            this._cbWall.Text = "Enable";
            this._cbWall.UseVisualStyleBackColor = true;
            this._cbWall.CheckedChanged += new System.EventHandler(this.OnEvent);
            // 
            // _gbWall
            // 
            this._gbWall.Controls.Add(this._cbWallBoundingBox);
            this._gbWall.Controls.Add(this.label7);
            this._gbWall.Controls.Add(this._tbWallWidth);
            this._gbWall.Controls.Add(this._tbWallName);
            this._gbWall.Controls.Add(this.label6);
            this._gbWall.Controls.Add(this.label3);
            this._gbWall.Controls.Add(this._rbWallBRep);
            this._gbWall.Controls.Add(this._rbWallExtrudedPolygon);
            this._gbWall.Controls.Add(this.label4);
            this._gbWall.Controls.Add(this._cbWall);
            this._gbWall.Controls.Add(this._tbWallThickness);
            this._gbWall.Controls.Add(this._tbWallHeight);
            this._gbWall.Controls.Add(this.label5);
            this._gbWall.Location = new System.Drawing.Point(12, 125);
            this._gbWall.Name = "_gbWall";
            this._gbWall.Size = new System.Drawing.Size(539, 123);
            this._gbWall.TabIndex = 0;
            this._gbWall.TabStop = false;
            this._gbWall.Text = "Wall";
            // 
            // _cbWallBoundingBox
            // 
            this._cbWallBoundingBox.AutoSize = true;
            this._cbWallBoundingBox.Location = new System.Drawing.Point(9, 100);
            this._cbWallBoundingBox.Name = "_cbWallBoundingBox";
            this._cbWallBoundingBox.Size = new System.Drawing.Size(92, 17);
            this._cbWallBoundingBox.TabIndex = 12;
            this._cbWallBoundingBox.Text = "Bounding Box";
            this._cbWallBoundingBox.UseVisualStyleBackColor = true;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(7, 42);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(104, 13);
            this.label7.TabIndex = 11;
            this.label7.Text = "Body representation:";
            // 
            // _tbWallWidth
            // 
            this._tbWallWidth.Location = new System.Drawing.Point(202, 92);
            this._tbWallWidth.Name = "_tbWallWidth";
            this._tbWallWidth.Size = new System.Drawing.Size(100, 20);
            this._tbWallWidth.TabIndex = 8;
            this._tbWallWidth.TextChanged += new System.EventHandler(this.OnEvent);
            // 
            // _tbWallName
            // 
            this._tbWallName.Location = new System.Drawing.Point(202, 19);
            this._tbWallName.Name = "_tbWallName";
            this._tbWallName.Size = new System.Drawing.Size(328, 20);
            this._tbWallName.TabIndex = 2;
            this._tbWallName.TextChanged += new System.EventHandler(this.OnEvent);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(140, 96);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(38, 13);
            this.label6.TabIndex = 7;
            this.label6.Text = "Width:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(140, 23);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(38, 13);
            this.label3.TabIndex = 1;
            this.label3.Text = "Name:";
            // 
            // _rbWallBRep
            // 
            this._rbWallBRep.AutoSize = true;
            this._rbWallBRep.Location = new System.Drawing.Point(15, 76);
            this._rbWallBRep.Name = "_rbWallBRep";
            this._rbWallBRep.Size = new System.Drawing.Size(55, 17);
            this._rbWallBRep.TabIndex = 10;
            this._rbWallBRep.TabStop = true;
            this._rbWallBRep.Text = "B-Rep";
            this._rbWallBRep.UseVisualStyleBackColor = true;
            // 
            // _rbWallExtrudedPolygon
            // 
            this._rbWallExtrudedPolygon.AutoSize = true;
            this._rbWallExtrudedPolygon.Location = new System.Drawing.Point(15, 58);
            this._rbWallExtrudedPolygon.Name = "_rbWallExtrudedPolygon";
            this._rbWallExtrudedPolygon.Size = new System.Drawing.Size(108, 17);
            this._rbWallExtrudedPolygon.TabIndex = 9;
            this._rbWallExtrudedPolygon.TabStop = true;
            this._rbWallExtrudedPolygon.Text = "Extruded Polygon";
            this._rbWallExtrudedPolygon.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(140, 47);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Thickness:";
            // 
            // _tbWallThickness
            // 
            this._tbWallThickness.Location = new System.Drawing.Point(202, 43);
            this._tbWallThickness.Name = "_tbWallThickness";
            this._tbWallThickness.Size = new System.Drawing.Size(100, 20);
            this._tbWallThickness.TabIndex = 4;
            this._tbWallThickness.TextChanged += new System.EventHandler(this.OnEvent);
            // 
            // _tbWallHeight
            // 
            this._tbWallHeight.Location = new System.Drawing.Point(202, 67);
            this._tbWallHeight.Name = "_tbWallHeight";
            this._tbWallHeight.Size = new System.Drawing.Size(100, 20);
            this._tbWallHeight.TabIndex = 6;
            this._tbWallHeight.TextChanged += new System.EventHandler(this.OnEvent);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(140, 71);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 13);
            this.label5.TabIndex = 5;
            this.label5.Text = "Height:";
            // 
            // _btnCreateIFC
            // 
            this._btnCreateIFC.Location = new System.Drawing.Point(58, 525);
            this._btnCreateIFC.Name = "_btnCreateIFC";
            this._btnCreateIFC.Size = new System.Drawing.Size(220, 23);
            this._btnCreateIFC.TabIndex = 1;
            this._btnCreateIFC.Text = "Create IFC File (SPFF)";
            this._btnCreateIFC.UseVisualStyleBackColor = true;
            this._btnCreateIFC.Click += new System.EventHandler(this._btnCreateIFC_Click);
            // 
            // _btnCreateIFX
            // 
            this._btnCreateIFX.Location = new System.Drawing.Point(284, 525);
            this._btnCreateIFX.Name = "_btnCreateIFX";
            this._btnCreateIFX.Size = new System.Drawing.Size(220, 23);
            this._btnCreateIFX.TabIndex = 2;
            this._btnCreateIFX.Text = "Create IFX File (ifcXML, ifc => ifcxml)";
            this._btnCreateIFX.UseVisualStyleBackColor = true;
            this._btnCreateIFX.Click += new System.EventHandler(this._btnCreateIFX_Click);
            // 
            // _tbSchemaFileName
            // 
            this._tbSchemaFileName.Location = new System.Drawing.Point(74, 17);
            this._tbSchemaFileName.Name = "_tbSchemaFileName";
            this._tbSchemaFileName.ReadOnly = true;
            this._tbSchemaFileName.Size = new System.Drawing.Size(395, 20);
            this._tbSchemaFileName.TabIndex = 3;
            // 
            // _btnSchemaFileName
            // 
            this._btnSchemaFileName.Location = new System.Drawing.Point(481, 16);
            this._btnSchemaFileName.Name = "_btnSchemaFileName";
            this._btnSchemaFileName.Size = new System.Drawing.Size(49, 23);
            this._btnSchemaFileName.TabIndex = 4;
            this._btnSchemaFileName.Text = "...";
            this._btnSchemaFileName.UseVisualStyleBackColor = true;
            this._btnSchemaFileName.Click += new System.EventHandler(this._btnSchemaFileName_Click);
            // 
            // _btnOutputFileName
            // 
            this._btnOutputFileName.Location = new System.Drawing.Point(481, 43);
            this._btnOutputFileName.Name = "_btnOutputFileName";
            this._btnOutputFileName.Size = new System.Drawing.Size(49, 23);
            this._btnOutputFileName.TabIndex = 6;
            this._btnOutputFileName.Text = "...";
            this._btnOutputFileName.UseVisualStyleBackColor = true;
            this._btnOutputFileName.Click += new System.EventHandler(this._btnOutputFileName_Click);
            // 
            // _tbOutputFileName
            // 
            this._tbOutputFileName.Location = new System.Drawing.Point(74, 44);
            this._tbOutputFileName.Name = "_tbOutputFileName";
            this._tbOutputFileName.ReadOnly = true;
            this._tbOutputFileName.Size = new System.Drawing.Size(395, 20);
            this._tbOutputFileName.TabIndex = 5;
            // 
            // _gbGeneral
            // 
            this._gbGeneral.Controls.Add(this._rbPresentationView);
            this._gbGeneral.Controls.Add(this._rbCoordinationView);
            this._gbGeneral.Controls.Add(this._cbUseMeters);
            this._gbGeneral.Controls.Add(this.label2);
            this._gbGeneral.Controls.Add(this.label1);
            this._gbGeneral.Controls.Add(this._cbIncludeQuantites);
            this._gbGeneral.Controls.Add(this._btnOutputFileName);
            this._gbGeneral.Controls.Add(this._tbSchemaFileName);
            this._gbGeneral.Controls.Add(this._tbOutputFileName);
            this._gbGeneral.Controls.Add(this._btnSchemaFileName);
            this._gbGeneral.Location = new System.Drawing.Point(12, 7);
            this._gbGeneral.Name = "_gbGeneral";
            this._gbGeneral.Size = new System.Drawing.Size(539, 113);
            this._gbGeneral.TabIndex = 1;
            this._gbGeneral.TabStop = false;
            this._gbGeneral.Text = "General";
            // 
            // _rbPresentationView
            // 
            this._rbPresentationView.AutoSize = true;
            this._rbPresentationView.Location = new System.Drawing.Point(10, 91);
            this._rbPresentationView.Name = "_rbPresentationView";
            this._rbPresentationView.Size = new System.Drawing.Size(110, 17);
            this._rbPresentationView.TabIndex = 11;
            this._rbPresentationView.TabStop = true;
            this._rbPresentationView.Text = "Presentation View";
            this._rbPresentationView.UseVisualStyleBackColor = true;
            // 
            // _rbCoordinationView
            // 
            this._rbCoordinationView.AutoSize = true;
            this._rbCoordinationView.Location = new System.Drawing.Point(10, 72);
            this._rbCoordinationView.Name = "_rbCoordinationView";
            this._rbCoordinationView.Size = new System.Drawing.Size(110, 17);
            this._rbCoordinationView.TabIndex = 10;
            this._rbCoordinationView.TabStop = true;
            this._rbCoordinationView.Text = "Coordination View";
            this._rbCoordinationView.UseVisualStyleBackColor = true;
            this._rbCoordinationView.CheckedChanged += new System.EventHandler(this.OnEvent);
            // 
            // _cbUseMeters
            // 
            this._cbUseMeters.AutoSize = true;
            this._cbUseMeters.Location = new System.Drawing.Point(202, 92);
            this._cbUseMeters.Name = "_cbUseMeters";
            this._cbUseMeters.Size = new System.Drawing.Size(206, 17);
            this._cbUseMeters.TabIndex = 9;
            this._cbUseMeters.Text = "Write results as meters (instead of mm)";
            this._cbUseMeters.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(58, 13);
            this.label2.TabIndex = 8;
            this.label2.Text = "Output file:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "Schema file:";
            // 
            // _cbIncludeQuantites
            // 
            this._cbIncludeQuantites.AutoSize = true;
            this._cbIncludeQuantites.Location = new System.Drawing.Point(202, 72);
            this._cbIncludeQuantites.Name = "_cbIncludeQuantites";
            this._cbIncludeQuantites.Size = new System.Drawing.Size(109, 17);
            this._cbIncludeQuantites.TabIndex = 0;
            this._cbIncludeQuantites.Text = "Include Quantites";
            this._cbIncludeQuantites.UseVisualStyleBackColor = true;
            // 
            // _gbOpening
            // 
            this._gbOpening.Controls.Add(this.label12);
            this._gbOpening.Controls.Add(this._tbOpeningWidth);
            this._gbOpening.Controls.Add(this.label14);
            this._gbOpening.Controls.Add(this._tbOpeningHeight);
            this._gbOpening.Controls.Add(this.label11);
            this._gbOpening.Controls.Add(this._tbOpeningZOffset);
            this._gbOpening.Controls.Add(this.label9);
            this._gbOpening.Controls.Add(this._cbOpeningBoundingBox);
            this._gbOpening.Controls.Add(this._tbOpeningXOffset);
            this._gbOpening.Controls.Add(this.label8);
            this._gbOpening.Controls.Add(this._tbOpeningName);
            this._gbOpening.Controls.Add(this.label10);
            this._gbOpening.Controls.Add(this._rbOpeningBRep);
            this._gbOpening.Controls.Add(this._rbOpeningExtrudedPolygon);
            this._gbOpening.Controls.Add(this._cbOpening);
            this._gbOpening.Location = new System.Drawing.Point(12, 254);
            this._gbOpening.Name = "_gbOpening";
            this._gbOpening.Size = new System.Drawing.Size(539, 126);
            this._gbOpening.TabIndex = 3;
            this._gbOpening.TabStop = false;
            this._gbOpening.Text = "Opening";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(385, 75);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(38, 13);
            this.label12.TabIndex = 19;
            this.label12.Text = "Width:";
            // 
            // _tbOpeningWidth
            // 
            this._tbOpeningWidth.Location = new System.Drawing.Point(430, 71);
            this._tbOpeningWidth.Name = "_tbOpeningWidth";
            this._tbOpeningWidth.Size = new System.Drawing.Size(100, 20);
            this._tbOpeningWidth.TabIndex = 20;
            this._tbOpeningWidth.TextChanged += new System.EventHandler(this.OnEvent);
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(385, 49);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(41, 13);
            this.label14.TabIndex = 17;
            this.label14.Text = "Height:";
            // 
            // _tbOpeningHeight
            // 
            this._tbOpeningHeight.Location = new System.Drawing.Point(430, 45);
            this._tbOpeningHeight.Name = "_tbOpeningHeight";
            this._tbOpeningHeight.Size = new System.Drawing.Size(100, 20);
            this._tbOpeningHeight.TabIndex = 18;
            this._tbOpeningHeight.TextChanged += new System.EventHandler(this.OnEvent);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(140, 75);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(48, 13);
            this.label11.TabIndex = 15;
            this.label11.Text = "Z Offset:";
            // 
            // _tbOpeningZOffset
            // 
            this._tbOpeningZOffset.Location = new System.Drawing.Point(202, 71);
            this._tbOpeningZOffset.Name = "_tbOpeningZOffset";
            this._tbOpeningZOffset.Size = new System.Drawing.Size(100, 20);
            this._tbOpeningZOffset.TabIndex = 16;
            this._tbOpeningZOffset.TextChanged += new System.EventHandler(this.OnEvent);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(140, 49);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(48, 13);
            this.label9.TabIndex = 13;
            this.label9.Text = "X Offset:";
            // 
            // _cbOpeningBoundingBox
            // 
            this._cbOpeningBoundingBox.AutoSize = true;
            this._cbOpeningBoundingBox.Location = new System.Drawing.Point(9, 104);
            this._cbOpeningBoundingBox.Name = "_cbOpeningBoundingBox";
            this._cbOpeningBoundingBox.Size = new System.Drawing.Size(92, 17);
            this._cbOpeningBoundingBox.TabIndex = 12;
            this._cbOpeningBoundingBox.Text = "Bounding Box";
            this._cbOpeningBoundingBox.UseVisualStyleBackColor = true;
            this._cbOpeningBoundingBox.CheckedChanged += new System.EventHandler(this.OnEvent);
            // 
            // _tbOpeningXOffset
            // 
            this._tbOpeningXOffset.Location = new System.Drawing.Point(202, 45);
            this._tbOpeningXOffset.Name = "_tbOpeningXOffset";
            this._tbOpeningXOffset.Size = new System.Drawing.Size(100, 20);
            this._tbOpeningXOffset.TabIndex = 14;
            this._tbOpeningXOffset.TextChanged += new System.EventHandler(this.OnEvent);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(7, 42);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(104, 13);
            this.label8.TabIndex = 11;
            this.label8.Text = "Body representation:";
            // 
            // _tbOpeningName
            // 
            this._tbOpeningName.Location = new System.Drawing.Point(202, 19);
            this._tbOpeningName.Name = "_tbOpeningName";
            this._tbOpeningName.Size = new System.Drawing.Size(328, 20);
            this._tbOpeningName.TabIndex = 2;
            this._tbOpeningName.TextChanged += new System.EventHandler(this.OnEvent);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(140, 23);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(38, 13);
            this.label10.TabIndex = 1;
            this.label10.Text = "Name:";
            // 
            // _rbOpeningBRep
            // 
            this._rbOpeningBRep.AutoSize = true;
            this._rbOpeningBRep.Location = new System.Drawing.Point(15, 78);
            this._rbOpeningBRep.Name = "_rbOpeningBRep";
            this._rbOpeningBRep.Size = new System.Drawing.Size(55, 17);
            this._rbOpeningBRep.TabIndex = 10;
            this._rbOpeningBRep.TabStop = true;
            this._rbOpeningBRep.Text = "B-Rep";
            this._rbOpeningBRep.UseVisualStyleBackColor = true;
            // 
            // _rbOpeningExtrudedPolygon
            // 
            this._rbOpeningExtrudedPolygon.AutoSize = true;
            this._rbOpeningExtrudedPolygon.Location = new System.Drawing.Point(15, 60);
            this._rbOpeningExtrudedPolygon.Name = "_rbOpeningExtrudedPolygon";
            this._rbOpeningExtrudedPolygon.Size = new System.Drawing.Size(108, 17);
            this._rbOpeningExtrudedPolygon.TabIndex = 9;
            this._rbOpeningExtrudedPolygon.TabStop = true;
            this._rbOpeningExtrudedPolygon.Text = "Extruded Polygon";
            this._rbOpeningExtrudedPolygon.UseVisualStyleBackColor = true;
            this._rbOpeningExtrudedPolygon.CheckedChanged += new System.EventHandler(this.OnEvent);
            // 
            // _cbOpening
            // 
            this._cbOpening.AutoSize = true;
            this._cbOpening.Location = new System.Drawing.Point(10, 19);
            this._cbOpening.Name = "_cbOpening";
            this._cbOpening.Size = new System.Drawing.Size(59, 17);
            this._cbOpening.TabIndex = 0;
            this._cbOpening.Text = "Enable";
            this._cbOpening.UseVisualStyleBackColor = true;
            this._cbOpening.CheckedChanged += new System.EventHandler(this.OnEvent);
            // 
            // _gbWindow
            // 
            this._gbWindow.Controls.Add(this.label18);
            this._gbWindow.Controls.Add(this._tbWindowWidth);
            this._gbWindow.Controls.Add(this.label19);
            this._gbWindow.Controls.Add(this._tbWindowHeight);
            this._gbWindow.Controls.Add(this.label17);
            this._gbWindow.Controls.Add(this.label16);
            this._gbWindow.Controls.Add(this._tbWindowYOffset);
            this._gbWindow.Controls.Add(this._cbWindowBoundingBox);
            this._gbWindow.Controls.Add(this._tbWindowThickness);
            this._gbWindow.Controls.Add(this.label13);
            this._gbWindow.Controls.Add(this._tbWindowName);
            this._gbWindow.Controls.Add(this.label15);
            this._gbWindow.Controls.Add(this._rbWindowBRep);
            this._gbWindow.Controls.Add(this._rbWindowExtrudedPolygon);
            this._gbWindow.Controls.Add(this._cbWindow);
            this._gbWindow.Location = new System.Drawing.Point(12, 386);
            this._gbWindow.Name = "_gbWindow";
            this._gbWindow.Size = new System.Drawing.Size(539, 126);
            this._gbWindow.TabIndex = 13;
            this._gbWindow.TabStop = false;
            this._gbWindow.Text = "Window";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(385, 79);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(38, 13);
            this.label18.TabIndex = 25;
            this.label18.Text = "Width:";
            // 
            // _tbWindowWidth
            // 
            this._tbWindowWidth.Location = new System.Drawing.Point(430, 75);
            this._tbWindowWidth.Name = "_tbWindowWidth";
            this._tbWindowWidth.Size = new System.Drawing.Size(100, 20);
            this._tbWindowWidth.TabIndex = 26;
            this._tbWindowWidth.TextChanged += new System.EventHandler(this.OnEvent);
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(385, 53);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(41, 13);
            this.label19.TabIndex = 23;
            this.label19.Text = "Height:";
            // 
            // _tbWindowHeight
            // 
            this._tbWindowHeight.Location = new System.Drawing.Point(430, 49);
            this._tbWindowHeight.Name = "_tbWindowHeight";
            this._tbWindowHeight.Size = new System.Drawing.Size(100, 20);
            this._tbWindowHeight.TabIndex = 24;
            this._tbWindowHeight.TextChanged += new System.EventHandler(this.OnEvent);
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(140, 75);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(48, 13);
            this.label17.TabIndex = 21;
            this.label17.Text = "Y Offset:";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(140, 49);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(59, 13);
            this.label16.TabIndex = 13;
            this.label16.Text = "Thickness:";
            // 
            // _tbWindowYOffset
            // 
            this._tbWindowYOffset.Location = new System.Drawing.Point(202, 71);
            this._tbWindowYOffset.Name = "_tbWindowYOffset";
            this._tbWindowYOffset.Size = new System.Drawing.Size(100, 20);
            this._tbWindowYOffset.TabIndex = 22;
            this._tbWindowYOffset.TextChanged += new System.EventHandler(this.OnEvent);
            // 
            // _cbWindowBoundingBox
            // 
            this._cbWindowBoundingBox.AutoSize = true;
            this._cbWindowBoundingBox.Location = new System.Drawing.Point(9, 104);
            this._cbWindowBoundingBox.Name = "_cbWindowBoundingBox";
            this._cbWindowBoundingBox.Size = new System.Drawing.Size(92, 17);
            this._cbWindowBoundingBox.TabIndex = 12;
            this._cbWindowBoundingBox.Text = "Bounding Box";
            this._cbWindowBoundingBox.UseVisualStyleBackColor = true;
            this._cbWindowBoundingBox.CheckedChanged += new System.EventHandler(this.OnEvent);
            // 
            // _tbWindowThickness
            // 
            this._tbWindowThickness.Location = new System.Drawing.Point(202, 45);
            this._tbWindowThickness.Name = "_tbWindowThickness";
            this._tbWindowThickness.Size = new System.Drawing.Size(100, 20);
            this._tbWindowThickness.TabIndex = 14;
            this._tbWindowThickness.TextChanged += new System.EventHandler(this.OnEvent);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(9, 41);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(104, 13);
            this.label13.TabIndex = 11;
            this.label13.Text = "Body representation:";
            // 
            // _tbWindowName
            // 
            this._tbWindowName.Location = new System.Drawing.Point(202, 19);
            this._tbWindowName.Name = "_tbWindowName";
            this._tbWindowName.Size = new System.Drawing.Size(328, 20);
            this._tbWindowName.TabIndex = 2;
            this._tbWindowName.TextChanged += new System.EventHandler(this.OnEvent);
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(140, 23);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(38, 13);
            this.label15.TabIndex = 1;
            this.label15.Text = "Name:";
            // 
            // _rbWindowBRep
            // 
            this._rbWindowBRep.AutoSize = true;
            this._rbWindowBRep.Location = new System.Drawing.Point(17, 77);
            this._rbWindowBRep.Name = "_rbWindowBRep";
            this._rbWindowBRep.Size = new System.Drawing.Size(55, 17);
            this._rbWindowBRep.TabIndex = 10;
            this._rbWindowBRep.TabStop = true;
            this._rbWindowBRep.Text = "B-Rep";
            this._rbWindowBRep.UseVisualStyleBackColor = true;
            // 
            // _rbWindowExtrudedPolygon
            // 
            this._rbWindowExtrudedPolygon.AutoSize = true;
            this._rbWindowExtrudedPolygon.Location = new System.Drawing.Point(17, 59);
            this._rbWindowExtrudedPolygon.Name = "_rbWindowExtrudedPolygon";
            this._rbWindowExtrudedPolygon.Size = new System.Drawing.Size(108, 17);
            this._rbWindowExtrudedPolygon.TabIndex = 9;
            this._rbWindowExtrudedPolygon.TabStop = true;
            this._rbWindowExtrudedPolygon.Text = "Extruded Polygon";
            this._rbWindowExtrudedPolygon.UseVisualStyleBackColor = true;
            this._rbWindowExtrudedPolygon.CheckedChanged += new System.EventHandler(this.OnEvent);
            // 
            // _cbWindow
            // 
            this._cbWindow.AutoSize = true;
            this._cbWindow.Location = new System.Drawing.Point(10, 19);
            this._cbWindow.Name = "_cbWindow";
            this._cbWindow.Size = new System.Drawing.Size(59, 17);
            this._cbWindow.TabIndex = 0;
            this._cbWindow.Text = "Enable";
            this._cbWindow.UseVisualStyleBackColor = true;
            this._cbWindow.CheckedChanged += new System.EventHandler(this.OnEvent);
            // 
            // _btnClose
            // 
            this._btnClose.Location = new System.Drawing.Point(284, 554);
            this._btnClose.Name = "_btnClose";
            this._btnClose.Size = new System.Drawing.Size(220, 23);
            this._btnClose.TabIndex = 15;
            this._btnClose.Text = "Close";
            this._btnClose.UseVisualStyleBackColor = true;
            this._btnClose.Click += new System.EventHandler(this._btnClose_Click);
            // 
            // _btnTestMode
            // 
            this._btnTestMode.Location = new System.Drawing.Point(58, 554);
            this._btnTestMode.Name = "_btnTestMode";
            this._btnTestMode.Size = new System.Drawing.Size(220, 23);
            this._btnTestMode.TabIndex = 14;
            this._btnTestMode.Text = "Test mode";
            this._btnTestMode.UseVisualStyleBackColor = true;
            this._btnTestMode.Click += new System.EventHandler(this._btnTestMode_Click);
            // 
            // HelloWallForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(563, 588);
            this.Controls.Add(this._btnClose);
            this.Controls.Add(this._btnTestMode);
            this.Controls.Add(this._gbWindow);
            this.Controls.Add(this._gbOpening);
            this.Controls.Add(this._gbGeneral);
            this.Controls.Add(this._btnCreateIFX);
            this.Controls.Add(this._btnCreateIFC);
            this.Controls.Add(this._gbWall);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "HelloWallForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "HelloWall";
            this.Load += new System.EventHandler(this.HelloWallForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this._errorProvider)).EndInit();
            this._gbWall.ResumeLayout(false);
            this._gbWall.PerformLayout();
            this._gbGeneral.ResumeLayout(false);
            this._gbGeneral.PerformLayout();
            this._gbOpening.ResumeLayout(false);
            this._gbOpening.PerformLayout();
            this._gbWindow.ResumeLayout(false);
            this._gbWindow.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ErrorProvider _errorProvider;
        private System.Windows.Forms.GroupBox _gbWall;
        private System.Windows.Forms.CheckBox _cbWall;
        private System.Windows.Forms.Button _btnCreateIFC;
        private System.Windows.Forms.Button _btnCreateIFX;
        private System.Windows.Forms.TextBox _tbSchemaFileName;
        private System.Windows.Forms.Button _btnSchemaFileName;
        private System.Windows.Forms.Button _btnOutputFileName;
        private System.Windows.Forms.TextBox _tbOutputFileName;
        private System.Windows.Forms.GroupBox _gbGeneral;
        private System.Windows.Forms.CheckBox _cbIncludeQuantites;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckBox _cbUseMeters;
        private System.Windows.Forms.RadioButton _rbCoordinationView;
        private System.Windows.Forms.RadioButton _rbPresentationView;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox _tbWallName;
        private System.Windows.Forms.TextBox _tbWallThickness;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox _tbWallHeight;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox _tbWallWidth;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.RadioButton _rbWallExtrudedPolygon;
        private System.Windows.Forms.RadioButton _rbWallBRep;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.CheckBox _cbWallBoundingBox;
        private System.Windows.Forms.GroupBox _gbOpening;
        private System.Windows.Forms.CheckBox _cbOpeningBoundingBox;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox _tbOpeningName;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.RadioButton _rbOpeningBRep;
        private System.Windows.Forms.RadioButton _rbOpeningExtrudedPolygon;
        private System.Windows.Forms.CheckBox _cbOpening;
        private System.Windows.Forms.GroupBox _gbWindow;
        private System.Windows.Forms.CheckBox _cbWindowBoundingBox;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox _tbWindowName;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.RadioButton _rbWindowBRep;
        private System.Windows.Forms.RadioButton _rbWindowExtrudedPolygon;
        private System.Windows.Forms.CheckBox _cbWindow;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox _tbOpeningXOffset;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox _tbOpeningZOffset;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox _tbOpeningWidth;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox _tbOpeningHeight;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.TextBox _tbWindowThickness;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.TextBox _tbWindowYOffset;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.TextBox _tbWindowWidth;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.TextBox _tbWindowHeight;
        private System.Windows.Forms.Button _btnClose;
        private System.Windows.Forms.Button _btnTestMode;
    }
}

