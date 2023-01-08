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
    public partial class TilesetEditor : Form
    {
        private Dictionary<string, Tileset> myTilesets;
        private Point myTilesetMarker = new Point();
        private Point myTilesetPreviewMarker = new Point();

        public TilesetEditor()
        {
            InitializeComponent();
        }

        private void SelectTilesetTexture_Click(object sender, EventArgs e)
        {
            if (TileSetIsChosen() == true)
            {
                OpenFileDialog dialog = new OpenFileDialog();
                dialog.InitialDirectory = Application.StartupPath + "\\data\\gfx\\tilesets\\";
                dialog.Filter = "(*.png)|*.png|(*.jpg)|*.jpg";
                dialog.Title = "Select texture for tilemap";
                DialogResult result = dialog.ShowDialog();

                if (result == DialogResult.OK)
                {
                    SelectTilesetImage(dialog.SafeFileName);
                }
            }
            else
            {
                MessageBox.Show("No tileset is chosen");
            }

        }

        private void SelectTilesetImage(string aFilename)
        {
            if (aFilename != null)
            {
                TilesetFilenameText.Text = aFilename;
                TilesetImage.Image = Image.FromFile(Settings.GetDataPath() + "\\data\\gfx\\tilesets\\" + TilesetFilenameText.Text);
                myTilesets[Tilesets.Text].TileImage = TilesetFilenameText.Text;
            }
            else
            {
                TilesetFilenameText.Text = "";
                TilesetImage.Image = null;
                myTilesets[Tilesets.Text].TileImage = "";
            }
        }

        private bool TileSetIsChosen()
        {
            return Tilesets.Text != "";
        }

        private void TilesetEditor_Load(object sender, EventArgs e)
        {
            myTilesets = new Dictionary<string, Tileset>();
            Tilesets.Items.Clear();
            try
            {
                System.IO.BinaryReader binaryReader = new System.IO.BinaryReader(System.IO.File.Open("data/tilesets/tilesets.dat", System.IO.FileMode.Open));

                int tilesetCount = binaryReader.ReadInt32();

                for (int tilesetIndex = 0; tilesetIndex < tilesetCount; tilesetIndex++)
                {
                    Tileset tileset = new Tileset();
                    tileset.LoadFrom(binaryReader);
                    Tilesets.Items.Add(tileset.myTilesetName);
                    myTilesets[tileset.myTilesetName] = tileset;
                }

                binaryReader.Close();
            }
            catch
            {

            }
        }

        private void AddTilesetButton_Click(object sender, EventArgs e)
        {
            string name = "";
            DialogResult result = TilesetEditor.InputBox("Tileset name", "Input name of tileset", ref name);
            if (result == DialogResult.OK)
            {
                if (Tilesets.Items.Contains(name) == false)
                {
                    Tileset tileset = new Tileset();
                    tileset.myTilesetName = name;
                    myTilesets.Add(name, tileset);
                    Tilesets.Items.Add(name);
                    Tilesets.Text = (string)Tilesets.Items[Tilesets.Items.Count - 1];
                }
                else
                {
                    MessageBox.Show("Tilset with that name already exists!", "Select other name", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }                
        }

        private void TilesetImage_Click(object sender, EventArgs e)
        {
            myTilesetMarker = myTilesetPreviewMarker;
            ObstacleCheckbox.Checked = myTilesets[Tilesets.Text].GetIsObstacle(GetTileID());
            DestructableCheckbox.Checked = myTilesets[Tilesets.Text].GetIsDestructable(GetTileID());
            FalloutCheckBox.Checked = myTilesets[Tilesets.Text].GetIsFallout(GetTileID());
        }

        private void TilesetImage_Paint(object sender, PaintEventArgs e)
        {
            DrawGrid(e);

            Pen previewMarkerPen = new Pen(Color.Yellow, 1);
            e.Graphics.DrawRectangle(previewMarkerPen,
                new Rectangle(myTilesetPreviewMarker.X, myTilesetPreviewMarker.Y, (int)TileWidth.Value, (int)TileHeight.Value));

            Pen markerPen = new Pen(Color.Red, 2);
            e.Graphics.DrawRectangle(markerPen, 
                new Rectangle(myTilesetMarker.X, myTilesetMarker.Y, (int)TileWidth.Value, (int)TileHeight.Value));
        }

        private void DrawGrid(PaintEventArgs e)
        {
            if (TilesetImage.Image != null)
            {
                int cols = TilesetImage.Image.Width / (int)TileWidth.Value;
                int rows = TilesetImage.Image.Height / (int)TileHeight.Value;

                Pen pen = new Pen(Color.Violet, 1);
                for (int x = 1; x < cols; x++)
                {
                    e.Graphics.DrawLine(pen, (float)(x * TileWidth.Value), 0, (float)(x * TileWidth.Value), TilesetImage.Height);
                }
                for (int y = 1; y < rows; y++)
                {
                    e.Graphics.DrawLine(pen, 0, (float)(y * TileHeight.Value), TilesetImage.Width, (float)(y * TileHeight.Value));
                }
            }
        }

        private void TileWidth_ValueChanged(object sender, EventArgs e)
        {
            if (TileSetIsChosen() == true)
            {
                myTilesets[Tilesets.Text].TileWidth = (int)TileWidth.Value;
                TilesetImage.Refresh();
            }
        }

        private void TileHeight_ValueChanged(object sender, EventArgs e)
        {
            if (TileSetIsChosen() == true)
            {
                myTilesets[Tilesets.Text].TileHeight = (int)TileHeight.Value;
                TilesetImage.Refresh();
            }
        }

        private void TilesetImage_MouseMove(object sender, MouseEventArgs e)
        {
            myTilesetPreviewMarker.X = (int)((int)(e.X / TileWidth.Value) * TileWidth.Value);
            myTilesetPreviewMarker.Y = (int)((int)(e.Y / TileHeight.Value) * TileHeight.Value);

            TilesetImage.Refresh();
        }

        private void ObstacleCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            if (TileSetIsChosen() == true)
            {
                myTilesets[Tilesets.Text].SetIsObstacle(GetTileID(), ObstacleCheckbox.Checked);
            }
        }
        private int GetTileID()
        {
            int columns = (int)(TilesetImage.Width / TileWidth.Value);
            int tileID = myTilesetMarker.X / (int)TileWidth.Value +
                         ((myTilesetMarker.Y / (int)TileHeight.Value) * columns);
            return tileID;
        }


    public static DialogResult InputBox(string title, string promptText, ref string value)
    {
        Form form = new Form();
        Label label = new Label();
        TextBox textBox = new TextBox();
        Button buttonOk = new Button();
        Button buttonCancel = new Button();

        form.Text = title;
        label.Text = promptText;
        textBox.Text = value;

        buttonOk.Text = "OK";
        buttonCancel.Text = "Cancel";
        buttonOk.DialogResult = DialogResult.OK;
        buttonCancel.DialogResult = DialogResult.Cancel;

        label.SetBounds(9, 20, 372, 13);
        textBox.SetBounds(12, 36, 372, 20);
        buttonOk.SetBounds(228, 72, 75, 23);
        buttonCancel.SetBounds(309, 72, 75, 23);

        label.AutoSize = true;
        textBox.Anchor = textBox.Anchor | AnchorStyles.Right;
        buttonOk.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
        buttonCancel.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;

        form.ClientSize = new Size(396, 107);
        form.Controls.AddRange(new Control[] { label, textBox, buttonOk, buttonCancel });
        form.ClientSize = new Size(Math.Max(300, label.Right + 10), form.ClientSize.Height);
        form.FormBorderStyle = FormBorderStyle.FixedDialog;
        form.StartPosition = FormStartPosition.CenterScreen;
        form.MinimizeBox = false;
        form.MaximizeBox = false;
        form.AcceptButton = buttonOk;
        form.CancelButton = buttonCancel;

        DialogResult dialogResult = form.ShowDialog();
        value = textBox.Text;
        return dialogResult;
    }

        private void Tilesets_SelectedIndexChanged(object sender, EventArgs e)
        {
            Tileset selectedTileset = myTilesets[Tilesets.Text];
            SelectTilesetImage(selectedTileset.TileImage);
            TileWidth.Value = selectedTileset.TileWidth;
            TileHeight.Value = selectedTileset.TileHeight;
        }

        private void SaveButton_Click(object sender, EventArgs e)
        {
            Save();
        }

        private void Save()
        {
            System.IO.BinaryWriter binaryWriter = new System.IO.BinaryWriter(System.IO.File.Open("data/tilesets/tilesets.dat", System.IO.FileMode.OpenOrCreate));
            binaryWriter.Write(Tilesets.Items.Count);

            foreach (PlatformEditor.Tileset tileset in myTilesets.Values)
            {
                tileset.SaveTo(binaryWriter);
            }

            binaryWriter.Close();
        }

        private void TilesetEditor_FormClosing(object sender, FormClosingEventArgs e)
        {
            DialogResult result = MessageBox.Show("Do you want to save changes?", "Save before quit?", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation);
            if (result == DialogResult.Yes)
            {
                Save();
            }
        }

        private void RemoveTilesetButton_Click(object sender, EventArgs e)
        {
            
        }

        private void DestructableCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            if (TileSetIsChosen() == true)
            {
                myTilesets[Tilesets.Text].SetIsDestructable(GetTileID(), DestructableCheckbox.Checked);
            }
        }

        private void AutoTileBtn_Click(object sender, EventArgs e)
        {
            if (Tilesets.Text == "")
            {
                MessageBox.Show("Choose tileset first!", "No tileset chosen", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return;
            }
            AutoTile autoTile = new AutoTile(myTilesets[Tilesets.Text]);
            autoTile.Show();
            autoTile.Focus();
        }

        private void FalloutCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (TileSetIsChosen() == true)
            {
                myTilesets[Tilesets.Text].SetIsFallout(GetTileID(), FalloutCheckBox.Checked);
            }
        }
    }
}

