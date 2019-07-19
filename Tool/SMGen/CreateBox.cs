using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SMGen
{
    public partial class CreateBox : Form
    {
        public CreateBox()
        {
            InitializeComponent();
        }

        private void OnLoad(object sender, EventArgs e)
        {
            mText.Focus();
        }

        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
            {
                this.DialogResult = DialogResult.Cancel;
                this.Close();
            }
            else if (e.KeyCode == Keys.Enter)
            {
                this.DialogResult = DialogResult.OK;
            }
        }

        public string GetContents()
        {
            return mText.Text;
        }
    }
}
