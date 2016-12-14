﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;


namespace IFCViewer
{
    public partial class Form1 : Form
    {
        IFCViewerWrapper ifcViewerWrapper = null;
        public Form1()
        {

            this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            this.SetStyle(ControlStyles.UserPaint, true);
          

            InitializeComponent();

              
            
            // initialize ifc viewer 
            //      - set destination window where ifc object to be drawn
            ifcViewerWrapper = new IFCViewerWrapper();
            ifcViewerWrapper.InitGraphics(this.splitContainer1.Panel2,this.treeView1);

        }

        private void OnPaint(object sender, PaintEventArgs e)
        {
             
        }
 

        private void OnMouseMove(object sender, MouseEventArgs e)
        {
            ifcViewerWrapper.OnMouseMove(e);
        }

        private void OnMouseClick(object sender, MouseEventArgs e)
        {
            
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter =  "ifcviewer Files (*.ifc)|";
            dialog.Title = "Open";

            if (dialog.ShowDialog() == DialogResult.OK)
            {
                if (ifcViewerWrapper.OpenIFCFile(dialog.FileName))
                {
                    this.Text = string.Format("{0} - ifcviewer", System.IO.Path.GetFileNameWithoutExtension(dialog.FileName));
                }


               // this.Text = "Bau";
            }
             
        }

        private void OnResize(object sender, EventArgs e)
        {
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.splitContainer1.Panel2.BackColor = Color.Transparent;
        }

        private void Panel2_Paint(object sender, PaintEventArgs e)
        {
            if (null != ifcViewerWrapper)
            { 
                ifcViewerWrapper.Redraw();
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void splitContainer1_Panel2_MouseUp(object sender, MouseEventArgs e)
        {
            if (null != ifcViewerWrapper)
            {
                ifcViewerWrapper.OnMouseUp(e);
            }
        }

        private void splitContainer1_Panel2_MouseDown(object sender, MouseEventArgs e)
        {
            if (null != ifcViewerWrapper)
            {
                ifcViewerWrapper.OnMouseDown(e);
            }
        }

       
        private void resetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (null != ifcViewerWrapper)
            {
                ifcViewerWrapper.Reset();
                ifcViewerWrapper.Redraw();
            }
        }

        private void viewFacesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // -------------------------------------------------
            // 
            if (null == ifcViewerWrapper)
            {
                return;
            }

            // -------------------------------------------------
            if (viewFacesToolStripMenuItem == sender)
            {
                ifcViewerWrapper.Faces = viewFacesToolStripMenuItem.Checked;

                // -------------------------------------------------
                // apply changes to the drawn figure

                ifcViewerWrapper.Redraw();
            }      
            
        }

        private void viewWireFrameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // -------------------------------------------------
            // 
            if (null == ifcViewerWrapper)
            {
                return;
            }

            // -------------------------------------------------
            if (viewWireFrameToolStripMenuItem == sender)
            {
                ifcViewerWrapper.WireFrames = viewWireFrameToolStripMenuItem.Checked;

                // -------------------------------------------------
                // apply changes to the drawn figure

                ifcViewerWrapper.Redraw();
            }        
           
        }

        private void selectOnOverIn3DToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // -------------------------------------------------
            // 
            if (null == ifcViewerWrapper)
            {
                return;
            }

            // -------------------------------------------------
            if (selectOnOverIn3DToolStripMenuItem == sender)
            {
                selectOnOverIn3DToolStripMenuItem.Checked = !selectOnOverIn3DToolStripMenuItem.Checked;

                ifcViewerWrapper.Hover = selectOnOverIn3DToolStripMenuItem.Checked;

                // -------------------------------------------------
                // apply changes to the drawn figure

                ifcViewerWrapper.Redraw();
            }
        }

        /// <summary>
        /// Handler
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void treeView1_BeforeCheck(object sender, TreeViewCancelEventArgs e)
        {
        }        

        /// <summary>
        /// Handler
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void treeView1_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                treeView1.SelectedNode = e.Node;
                contextMenuStrip1.Show(treeView1, new Point(e.X, e.Y));
            }
            else
            {
                if (e.Button == System.Windows.Forms.MouseButtons.Left)
                {
                    ifcViewerWrapper._treeData.OnNodeMouseClick(sender, e);
                }
            }
        }

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            ifcViewerWrapper._treeData.OnAfterSelect(sender, e);  
        }

        private void contextMenuStrip1_Opened(object sender, EventArgs e)
        {
            ifcViewerWrapper._treeData.OnContextMenu_Opened(sender, e); 
        }

        private void aboutIfcviewerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutBox1 Box1 = new AboutBox1();
            Box1.ShowDialog();
            
        }
    }
}
