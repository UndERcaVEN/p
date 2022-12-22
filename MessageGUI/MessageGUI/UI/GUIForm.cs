using System.Linq;
using System.Windows.Forms;

namespace MessageGUI
{
    public partial class GUIForm : Form
    {
        private Initializer _init;
        public GUIForm(Initializer init)
        {
            InitializeComponent();
            _init = init;
            this.Text = _init.username;
        }

        internal void DisplayMessage(string message, bool trim)
        {
            message = message.Trim('췍');
            richTextBox1.Text += $"{message}\n";
        }

        internal void ClearTextBox()
        {
            richTextBox1.Clear();
        }

        private void SendButton_Click(object sender, System.EventArgs e)
        {
            if(string.IsNullOrWhiteSpace(richTextBox2.Text))
            {
                return;
            }

            _init.message = _init.username + ": " + richTextBox2.Text;
            richTextBox2.Clear();
        }
    }
}
