using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;

namespace PlatformEditor
{
    public partial class GameObjectEditor : Form
    {
        public GameObjectEditor()
        {
            InitializeComponent();
            this.FormClosed += Form_Closed;
        }

        private void Form_Closed(object sender, FormClosedEventArgs e)
        {
            DialogResult result = MessageBox.Show("Do you want to save to file before exiting game object editor?", "Save?", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (result == DialogResult.Yes)
            {
                Save();
            }
            MapEditor.ourInstance.LoadGameObjectTypes();
            MapEditor.ourInstance.Enabled = true;
            MapEditor.ourInstance.Show();
        }

        private void SelectPicBtn_Click(object sender, EventArgs e)
        {
            FileDialog loadPic = new OpenFileDialog();
            loadPic.Filter = "*.png|*.png";
            DialogResult result = loadPic.ShowDialog();
            if (result == DialogResult.OK)
            {
                GameObjectPic.Image = Image.FromFile(loadPic.FileName);
                int dataIndex = loadPic.FileName.IndexOf("data");
                string relativePath = loadPic.FileName.Substring(dataIndex);
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].image = relativePath;
            }
        }

        private void GameObjectEditor_Load(object sender, EventArgs e)
        {
            foreach (GameObjectType gameObjectType in MapEditor.ourGameObjectTypes)
            {
                GameObjectTypeList.Items.Add(gameObjectType.name);
            }
        }

        private void NameText_TextChanged(object sender, EventArgs e)
        {
            if (GameObjectTypeList.SelectedItem != null)
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].name = NameText.Text.ToString();            
        }

        private void Weight_ValueChanged(object sender, EventArgs e)
        {
            if (GameObjectTypeList.SelectedItem != null)
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.weight = (float)Weight.Value;
        }

        private void Bounciness_ValueChanged(object sender, EventArgs e)
        {
            if (GameObjectTypeList.SelectedItem != null)
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.bounciness = (float)Bounciness.Value;
        }

        private void AirFrictionX_ValueChanged(object sender, EventArgs e)
        {
            if (GameObjectTypeList.SelectedItem != null)
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.airFriction.x = (float)AirFrictionX.Value;
        }

        private void AirFrictionY_ValueChanged(object sender, EventArgs e)
        {
            if (GameObjectTypeList.SelectedItem != null)
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.airFriction.y = (float)AirFrictionY.Value;
        }

        private void GroundFrictionX_ValueChanged(object sender, EventArgs e)
        {
            if (GameObjectTypeList.SelectedItem != null)
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.groundFriction.x = (float)GroundFrictionX.Value;
        }

        private void GroundFrictionY_ValueChanged(object sender, EventArgs e)
        {
            if (GameObjectTypeList.SelectedItem != null)
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.groundFriction.y = (float)GroundFrictionY.Value;
        }

        private void UpdateCollisionTags()
        {
            if (GameObjectTypeList.SelectedItem != null)
            {
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.collisionTags =
                    (PlayerTagCheckbox.Checked ? 1 : 0) +
                    (BulletTagCheckbox.Checked ? 2 : 0) +
                    (EnemyTagCheckbox.Checked ? 4 : 0) +
                    (PickableTagCheckbox.Checked ? 8 : 0);
            }
        }

        private void PhysicsCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            if (GameObjectTypeList.SelectedItem != null)
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.physicsEnabled = PhysicsCheckbox.Checked;
        }

        private void GravityCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            if (GameObjectTypeList.SelectedItem != null)
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.gravity = GravityCheckbox.Checked;
        }

        private void KineticCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            if (GameObjectTypeList.SelectedItem != null)
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.kinetic = KineticCheckbox.Checked;
        }

        private void RotationCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            if (GameObjectTypeList.SelectedItem != null)
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].rotateObject = RotationCheckbox.Checked;
        }

        private void GameObjectTypeList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (GameObjectTypeList.SelectedItem != null)
            {
                RotationCheckbox.Checked = MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].rotateObject;
                KineticCheckbox.Checked = MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.kinetic;
                GravityCheckbox.Checked = MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.gravity;
                PhysicsCheckbox.Checked = MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.physicsEnabled;
                GroundFrictionX.Value = (decimal)MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.groundFriction.x;
                GroundFrictionY.Value = (decimal)MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.groundFriction.y;
                AirFrictionX.Value = (decimal)MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.airFriction.x;
                AirFrictionY.Value = (decimal)MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.airFriction.y;
                NameText.Text = MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].name;
                Weight.Value = (decimal)MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.weight;
                Bounciness.Value = (decimal)MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.bounciness;
                IDText.Text = MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].ID.ToString();

                PlayerTagCheckbox.Checked = (MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.collisionTags & 1) > 0;
                BulletTagCheckbox.Checked = (MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.collisionTags & 2) > 0;
                EnemyTagCheckbox.Checked = (MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.collisionTags & 4) > 0;
                PickableTagCheckbox.Checked = (MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].physicBody.collisionTags & 8) > 0;


                if (MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].image != null)
                {
                    try
                    {
                        GameObjectPic.Image = Image.FromFile(MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].image);
                    }
                    catch
                    {
                        GameObjectPic.Image = null;
                    }
                }
                else
                {
                    GameObjectPic.Image = null;
                }
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
                GameObjectPic.Image = null;
                IDText.Text = "-1";
            }
        }

        private void NewBtn_Click(object sender, EventArgs e)
        {
            string name = "";
            DialogResult result = Utilities.InputBox("New Game Object type", "Chooce a unique game object name", ref name);
            if (result == DialogResult.OK)
            {                
                GameObjectTypeList.Items.Add(name);
                GameObjectType newType = new GameObjectType();
                newType.ID = CreateNewID();
                newType.name = name;
                MapEditor.ourGameObjectTypes.Add(newType);
                GameObjectTypeList.SelectedIndex = GameObjectTypeList.Items.Count - 1;
            }
        }

        private int CreateNewID()
        {
            int highestID = -1;

            foreach (GameObjectType gameObjectType in MapEditor.ourGameObjectTypes)
            {
                if (gameObjectType.ID > highestID)
                {
                    highestID = gameObjectType.ID;
                }
            }
            return highestID + 1;
        }

        private void RemoveBtn_Click(object sender, EventArgs e)
        {
            if (GameObjectTypeList.SelectedItem != null)
            {
                MapEditor.ourGameObjectTypes.RemoveAt(GameObjectTypeList.SelectedIndex);
                GameObjectTypeList.Items.RemoveAt(GameObjectTypeList.SelectedIndex);
            }
        }

        private void SaveBtn_Click(object sender, EventArgs e)
        {
            Save();
        }

        private void Save()
        {
            JsonSerializer serializer = new JsonSerializer();
            using (System.IO.StreamWriter sw = new System.IO.StreamWriter(@"data/json/GameObjects.json"))
            using (JsonWriter writer = new JsonTextWriter(sw))
            {
                writer.Formatting = Formatting.Indented;
                serializer.Serialize(writer, MapEditor.ourGameObjectTypes);
            }

            MessageBox.Show("Game object types saved!", "Saved", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void PickableTagCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            UpdateCollisionTags();
        }

        private void AddVaribleBtn_Click(object sender, EventArgs e)
        {
            string name = "";
            DialogResult result = Utilities.InputBox("New custom variable", "Choose a unique variable name", ref name);
            if (result == DialogResult.OK)
            {
                if (MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].variables.Contains(new VariableType(name)) == true)
                {
                    MessageBox.Show("Error! A variable with that name already exists!", "Error!", MessageBoxButtons.OK);
                    return;
                }

                VariableType variableType = new VariableType(name);
                variableType.defaultValue = 0.0f;
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].variables.Add(variableType);

                int index = VariableGrid.Rows.Add(variableType.name);
                VariableGrid.Rows[index].Cells["value"].Value = variableType.defaultValue;

                //VariableListBox.Items.Add(name);
                //VariableDefaultValue.Value = 0;
            }
        }

        private void RemoveVariableBtn_Click(object sender, EventArgs e)
        {
            if (VariableListBox.SelectedItem != null)
            {
                int index = VariableListBox.SelectedIndex;
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].variables.RemoveAt(index);
                VariableListBox.Items.RemoveAt(index);
            }
        }

        private void VariableListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (VariableListBox.SelectedItem != null)
            {
                VariableDefaultValue.Value = (decimal)MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].variables[VariableListBox.SelectedIndex].defaultValue;
            }
        }

        private void VariableDefaultValue_ValueChanged(object sender, EventArgs e)
        {
            if (VariableListBox.SelectedItem != null)
            {
                MapEditor.ourGameObjectTypes[GameObjectTypeList.SelectedIndex].variables[VariableListBox.SelectedIndex].defaultValue = (float)VariableDefaultValue.Value;
            }
        }

        private void GameObjectPic_Click(object sender, EventArgs e)
        {

        }
    }
}
