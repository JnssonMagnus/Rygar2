using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PlatformEditor
{
    public partial class MapSettings : Form
    {
        public MapSettings(int aCurrentMapWidth, int aCurrentMapHeight)
        {
            InitializeComponent();
            WidthNumeric.Value = aCurrentMapWidth;
            HeightNumeric.Value = aCurrentMapHeight;
        }

        public int GetMapWidth()
        {
            return (int)WidthNumeric.Value;
        }

        public int GetMapHeight()
        {
            return (int)HeightNumeric.Value;
        }

        private void MapSettings_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void CancelBtn_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }
    }
}
