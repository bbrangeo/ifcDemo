using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace HelloWall
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            HelloWallForm view = new HelloWallForm();
            HelloWallPresenter presenter = new HelloWallPresenter(new HelloWallSettings(), view);

            Application.Run(view);
        }
    }
}
