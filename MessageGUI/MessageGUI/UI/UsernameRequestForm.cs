using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MessageGUI.UI
{
    public partial class UsernameRequestForm : Form
    {
        private Initializer _init;

        public UsernameRequestForm(Initializer init)
        {
            InitializeComponent();
            _init = init;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(textBox1.Text.Length != 0)
            {
                _init.username= textBox1.Text;
                this.DialogResult = DialogResult.OK;
            }
        }
    }
}
