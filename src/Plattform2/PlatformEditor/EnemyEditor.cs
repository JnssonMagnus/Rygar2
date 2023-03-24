using Newtonsoft.Json;
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
    public partial class EnemyEditor : Form
    {
        public EnemyEditor()
        {
            InitializeComponent();
        }

        private void Life_ValueChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].life = (int)Life.Value;
        }

        private void Staggered_ValueChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].staggeredTime = (float)Staggered.Value;
        }

        private void Weight_ValueChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.weight = (float)Weight.Value;
        }

        private void Bounciness_ValueChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.bounciness = (float)Bounciness.Value;
        }

        private void AirFrictionX_ValueChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.airFriction.x = (float)AirFrictionX.Value;
        }

        private void AirFrictionY_ValueChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.airFriction.y = (float)AirFrictionY.Value;
        }

        private void GroundFrictionX_ValueChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.groundFriction.x = (float)GroundFrictionX.Value;
        }

        private void GroundFrictionY_ValueChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.groundFriction.y = (float)GroundFrictionY.Value;
        }

        private void PhysicsCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.physicsEnabled = PhysicsCheckbox.Checked;
        }

        private void GravityCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.gravity = GravityCheckbox.Checked;
        }

        private void KineticCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.kinetic = KineticCheckbox.Checked;
        }

        private void RotationCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].rotateObject = RotationCheckbox.Checked;
        }

        private void EnemyTypeList_SelectedIndexChanged(object sender, EventArgs e)
        {
            enemyTabControl.Visible = EnemyTypeList.SelectedItem != null;
            if (EnemyTypeList.SelectedItem == null)
                return;

            Life.Value = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].life;
            Staggered.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].staggeredTime;
            RotationCheckbox.Checked = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].rotateObject;
            KineticCheckbox.Checked = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.kinetic;
            GravityCheckbox.Checked = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.gravity;
            PhysicsCheckbox.Checked = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.physicsEnabled;
            GroundFrictionX.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.groundFriction.x;
            GroundFrictionY.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.groundFriction.y;
            AirFrictionX.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.airFriction.x;
            AirFrictionY.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.airFriction.y;
            NameText.Text = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].name;
            Weight.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.weight;
            Bounciness.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.bounciness;
            IDText.Text = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].ID.ToString();

            PlayerTagCheckbox.Checked = (MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.collisionTags & 1) > 0;
            BulletTagCheckbox.Checked = (MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.collisionTags & 2) > 0;
            EnemyTagCheckbox.Checked = (MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.collisionTags & 4) > 0;
            PickableTagCheckbox.Checked = (MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.collisionTags & 8) > 0;

            // Animation
            WidthValue.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].animationSet.width;
            HeightValue.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].animationSet.height;

            if (MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].image != null)
            {
                try
                {
                    EnemyPic.Image = Image.FromFile(MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].image);
                    EnemyPic.Width = EnemyPic.Image.Width * 2;
                    EnemyPic.Height = EnemyPic.Image.Height * 2;
                }
                catch
                {
                    EnemyPic.Image = null;
                }
            }
            else
            {
                EnemyPic.Image = null;
            }
        }

        private void EnemyTagCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            UpdateCollisionTags();
        }
        private void UpdateCollisionTags()
        {
            if (EnemyTypeList.SelectedItem != null)
            {
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicBody.collisionTags =
                    (PlayerTagCheckbox.Checked ? 1 : 0) +
                    (BulletTagCheckbox.Checked ? 2 : 0) +
                    (EnemyTagCheckbox.Checked ? 4 : 0) +
                    (PickableTagCheckbox.Checked ? 8 : 0);
            }
        }

        private void PlayerTagCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            UpdateCollisionTags();
        }

        private void BulletTagCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            UpdateCollisionTags();
        }

        private void PickableTagCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            UpdateCollisionTags();
        }

        private void SaveBtn_Click(object sender, EventArgs e)
        {
            Save();
        }

        private void Save()
        {
            JsonSerializer serializer = new JsonSerializer();
                using (System.IO.StreamWriter sw = new System.IO.StreamWriter(@"data/json/Enemies.json"))
                using (JsonWriter writer = new JsonTextWriter(sw))
                {
                    writer.Formatting = Formatting.Indented;
                    serializer.Serialize(writer, MapEditor.ourEnemyTypes);
                }

            MessageBox.Show("enemy types saved!", "Saved", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void NewBtn_Click(object sender, EventArgs e)
        {
            string name = "";
            DialogResult result = Utilities.InputBox("New Enemy type", "Choose a unique enemy name", ref name);
            if (result == DialogResult.OK)
            {
                EnemyTypeList.Items.Add(name);
                EnemyType newType = new EnemyType();
                newType.ID = CreateNewID();
                newType.name = name;
                MapEditor.ourEnemyTypes.Add(newType);
                EnemyTypeList.SelectedIndex = EnemyTypeList.Items.Count - 1;
            }
        }

        private int CreateNewID()
        {
            int highestID = -1;

            foreach (EnemyType enemyType in MapEditor.ourEnemyTypes)
            {
                if (enemyType.ID > highestID)
                {
                    highestID = enemyType.ID;
                }
            }
            return highestID + 1;
        }

        private void RemoveBtn_Click(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
            {
                MapEditor.ourEnemyTypes.RemoveAt(EnemyTypeList.SelectedIndex);
                EnemyTypeList.Items.RemoveAt(EnemyTypeList.SelectedIndex);
            }
        }

        private void EnemyEditor_Load(object sender, EventArgs e)
        {
            foreach (EnemyType enemyType in MapEditor.ourEnemyTypes)
            {
                EnemyTypeList.Items.Add(enemyType.name);
            }
        }

        private void EnemyEditor_FormClosed(object sender, FormClosedEventArgs e)
        {
            MapEditor.ourInstance.LoadEnemyTypes();
            MapEditor.ourInstance.Enabled = true;
            MapEditor.ourInstance.Show();
        }

        private void SelectPicBtn_Click(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem == null)
                return;

            FileDialog loadPic = new OpenFileDialog();
            loadPic.Filter = "*.png|*.png";
            DialogResult result = loadPic.ShowDialog();
            if (result == DialogResult.OK)
            {
                EnemyPic.Image = Image.FromFile(loadPic.FileName);
                int dataIndex = loadPic.FileName.IndexOf("data");
                string relativePath = loadPic.FileName.Substring(dataIndex);
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].image = relativePath;
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].animationSet.sprite = relativePath;

                EnemyPic.Width = EnemyPic.Image.Width * 2;
                EnemyPic.Height = EnemyPic.Image.Height * 2;
            }
        }

        private void label12_Click(object sender, EventArgs e)
        {

        }

        private void WidthValue_ValueChanged(object sender, EventArgs e)
        {
            MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].animationSet.width = (int)WidthValue.Value;
            EnemyPic.Refresh();
        }

        private void HeightValue_ValueChanged(object sender, EventArgs e)
        {
            MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].animationSet.height = (int)HeightValue.Value;
            EnemyPic.Refresh();
        }

        private void FramesValue_ValueChanged(object sender, EventArgs e)
        {
            GetCurrentAnimation().frames = (int)FramesValue.Value;
        }

        private Animation GetCurrentAnimation()
        {
            return MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].animationSet.GetAnimation(SelectedAnimation.Text);
        }

        private void FPSValue_ValueChanged(object sender, EventArgs e)
        {
            GetCurrentAnimation().FPS = (int)FPSValue.Value;
        }

        private void SelectedAnimation_SelectedIndexChanged(object sender, EventArgs e)
        {
            Animation animation = GetCurrentAnimation();
            FPSValue.Value = (decimal)animation.FPS;
            FramesValue.Value = (decimal)animation.frames;
            EnemyPic.Refresh();
        }

        private void EnemyPic_Click(object sender, EventArgs e)
        {
            Animation animation = GetCurrentAnimation();
            MouseEventArgs mouseEvent = (MouseEventArgs)(e);
            int cellWidth = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].animationSet.width;
            int cellHeight = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].animationSet.height;
            int animationStartX = (mouseEvent.X / cellWidth * 2) * cellWidth * 2;
            int animationStartY = (mouseEvent.X / cellHeight * 2) * cellHeight * 2;
            animation.startX = animationStartX / 2;
            animation.startY = animationStartY / 2;
            EnemyPic.Refresh();
        }

        private void EnemyPic_Paint(object sender, PaintEventArgs e)
        {
            Animation animation = GetCurrentAnimation();
            Pen greenPen = new Pen(Color.Cyan, 2);
            int cellWidth = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].animationSet.width;
            int cellHeight = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].animationSet.height;

            e.Graphics.DrawRectangle(greenPen, animation.startX * 2, animation.startY * 2, cellWidth * 2, cellHeight * 2);

            ImageNameText.Text = System.IO.Path.GetFileName(MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].animationSet.sprite);
            ImageSizeText.Text = "Size: " + EnemyPic.Width / 2 + "x" + EnemyPic.Height / 2;
        }
    }
}
