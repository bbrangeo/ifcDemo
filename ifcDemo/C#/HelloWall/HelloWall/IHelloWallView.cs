using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HelloWall
{
    /// <summary>
    /// View (Model-View-Presenter)
    /// </summary>
    public interface IHelloWallView
    {
        /// <summary>
        /// Accessor
        /// </summary>
        HelloWallPresenter Presenter
        {
            get;
            set;
        }

        /// <summary>
        /// Setter
        /// </summary>
        /// <param name="strProperty"></param>
        /// <param name="property"></param>
        void SetProperty(string strProperty, object property);

        /// <summary>
        /// Getter
        /// </summary>
        /// <param name="strProperty"></param>
        /// <returns></returns>
        object GetProperty(string strProperty);

        /// <summary>
        /// Error management
        /// </summary>
        /// <param name="strProperty"></param>
        /// <param name="strError"></param>
        void SetError(string strProperty, string strError);
    }
}
