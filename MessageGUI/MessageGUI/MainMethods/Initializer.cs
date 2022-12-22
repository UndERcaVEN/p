using MessageGUI.UI;
using System.Runtime.InteropServices;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MessageGUI
{

    [ComVisible(true)]
    public class Initializer: IMessageGUI
    {
        public string message { get; set; }
        public string username { get; set; }
        public int userCount { get; set; }

        private bool trim = false;

        GUIForm form;
        public void Initialize()
        {
            message = null;
            new UsernameRequestForm(this).ShowDialog();
            form = new GUIForm(this);
            new Thread(() => form.ShowDialog()).Start();
            message = $"{username} вошёл в чат";
        }


        public void DisplayMessage(string message)
        {
            form.DisplayMessage(message, trim);
            trim = true;
        }

        public void ClearMessage()
        {
            message = null;
        }
    }
}
