namespace ifceditor
{
    partial class Form1
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
            this.treeViewLP = new System.Windows.Forms.TreeView();
            this.treeViewRP = new System.Windows.Forms.TreeView();
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.textBoxFileName = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // treeViewLP
            // 
            this.treeViewLP.Location = new System.Drawing.Point(12, 44);
            this.treeViewLP.Name = "treeViewLP";
            this.treeViewLP.Size = new System.Drawing.Size(441, 579);
            this.treeViewLP.TabIndex = 0;
            this.treeViewLP.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeViewLP_AfterSelect);
            // 
            // treeViewRP
            // 
            this.treeViewRP.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.treeViewRP.Location = new System.Drawing.Point(459, 44);
            this.treeViewRP.Name = "treeViewRP";
            this.treeViewRP.Size = new System.Drawing.Size(502, 579);
            this.treeViewRP.TabIndex = 1;
            this.treeViewRP.BeforeExpand += new System.Windows.Forms.TreeViewCancelEventHandler(this.treeViewRP_BeforeExpand);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(808, 10);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(153, 26);
            this.button1.TabIndex = 2;
            this.button1.Text = "Open File";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(75, 17);
            this.label1.TabIndex = 3;
            this.label1.Text = "File Name:";
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // textBoxFileName
            // 
            this.textBoxFileName.Location = new System.Drawing.Point(93, 12);
            this.textBoxFileName.Name = "textBoxFileName";
            this.textBoxFileName.Size = new System.Drawing.Size(708, 22);
            this.textBoxFileName.TabIndex = 4;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(973, 635);
            this.Controls.Add(this.textBoxFileName);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.treeViewRP);
            this.Controls.Add(this.treeViewLP);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TreeView treeViewLP;
        private System.Windows.Forms.TreeView treeViewRP;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.TextBox textBoxFileName;
    }
}

