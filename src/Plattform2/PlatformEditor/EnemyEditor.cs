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
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].weight = (float)Weight.Value;
        }

        private void Bounciness_ValueChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].bounciness = (float)Bounciness.Value;
        }

        private void AirFrictionX_ValueChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].airFriction.x = (float)AirFrictionX.Value;
        }

        private void AirFrictionY_ValueChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].airFriction.y = (float)AirFrictionY.Value;
        }

        private void GroundFrictionX_ValueChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].groundFriction.x = (float)GroundFrictionX.Value;
        }

        private void GroundFrictionY_ValueChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].groundFriction.y = (float)GroundFrictionY.Value;
        }

        private void PhysicsCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicsEnabled = PhysicsCheckbox.Checked;
        }

        private void GravityCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].gravity = GravityCheckbox.Checked;
        }

        private void KineticCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].kinetic = KineticCheckbox.Checked;
        }

        private void RotationCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].rotateObject = RotationCheckbox.Checked;
        }

        private void EnemyTypeList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (EnemyTypeList.SelectedItem != null)
            {
                Life.Value = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].life;
                Staggered.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].staggeredTime;
                RotationCheckbox.Checked = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].rotateObject;
                KineticCheckbox.Checked = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].kinetic;
                GravityCheckbox.Checked = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].gravity;
                PhysicsCheckbox.Checked = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].physicsEnabled;
                GroundFrictionX.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].groundFriction.x;
                GroundFrictionY.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].groundFriction.y;
                AirFrictionX.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].airFriction.x;
                AirFrictionY.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].airFriction.y;
                NameText.Text = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].name;
                Weight.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].weight;
                Bounciness.Value = (decimal)MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].bounciness;
                IDText.Text = MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].ID.ToString();

                PlayerTagCheckbox.Checked = (MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].collisionTags & 1) > 0;
                BulletTagCheckbox.Checked = (MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].collisionTags & 2) > 0;
                EnemyTagCheckbox.Checked = (MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].collisionTags & 4) > 0;
                PickableTagCheckbox.Checked = (MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].collisionTags & 8) > 0;
            }
            else
            {
                PlayerTagCheckbox.Checked = false;
                EnemyTagCheckbox.Checked = false;
                BulletTagCheckbox.Checked = false;
                PickableTagCheckbox.Checked = false;
                RotationCheckbox.Checked = false;
                KineticCheckbox.Checked = false;
                GravityCheckbox.Checked = false;
                PhysicsCheckbox.Checked = false;
                GroundFrictionX.Value = 0;
                GroundFrictionY.Value = 0;
                AirFrictionX.Value = 0;
                AirFrictionY.Value = 0;
                NameText.Text = "";
                Weight.Value = 0;
                Bounciness.Value = 0;                
                IDText.Text = "-1";
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
                MapEditor.ourEnemyTypes[EnemyTypeList.SelectedIndex].collisionTags =
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
    }
}
