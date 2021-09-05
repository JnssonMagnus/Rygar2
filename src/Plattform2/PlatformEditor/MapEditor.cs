using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using Newtonsoft.Json;

namespace PlatformEditor
{
    public partial class MapEditor : Form
    {
        private Dictionary<string, Tileset> myTilesets;
        static public List<GameObjectType> ourGameObjectTypes = new List<GameObjectType>();
        static public MapEditor ourInstance;

        private GameObject mySelectedGameObject = null;

        public Dictionary<int, Image> myGameObjectTypeImages = new Dictionary<int, Image>();

        private int myTileSourceX = 0;
        private int myTileSourceY = 0;

        private Point myTilesetMarker = new Point();
        private Point myOldTilesetMarker = new Point();

        private Point myMapMarker = new Point();

        private MapData myMapData;

        private Point myOldMousePosition = new Point();

        private bool myLeftMousePressed = false;
        private bool myRightMousePressed = false;

        private bool myIsDraggingObject = false;

        public MapEditor()
        {
            InitializeComponent();
            ourInstance = this; 
            
        }

        private void LoadTilesets()
        {
            string path = "data/tilesets/tilesets.dat";
            myTilesets = new Dictionary<string, Tileset>();
            if (System.IO.File.Exists(path) == true)
            {
                System.IO.BinaryReader binaryReader = new System.IO.BinaryReader(System.IO.File.Open(path, System.IO.FileMode.Open));

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
        }

        public void LoadGameObjectTypes()
        {
            GameObjectTypesList.Items.Clear();
            using (StreamReader file = File.OpenText(@"data/json/gameObjects.json")) 
            {
                JsonSerializer serializer = new JsonSerializer();
                ourGameObjectTypes = (List<GameObjectType>)serializer.Deserialize(file, typeof(List<GameObjectType>));
            }

            foreach (GameObjectType gameObjectType in ourGameObjectTypes)
            {
                GameObjectTypesList.Items.Add(gameObjectType.name);
                Image image = Image.FromFile(gameObjectType.image);
                myGameObjectTypeImages[gameObjectType.ID] = image;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            LoadTilesets();
            LoadGameObjectTypes();

            Map.AllowDrop = true;
            Map.DragEnter += Map_DragEnter;
            Map.DragDrop += Map_DragDrop;
            Map.DragLeave += Map_DragLeave;
            Map.DragOver += Map_DragOver;

            myMapData = new MapData();
            myMapData.myMapWidth = 25;
            myMapData.myMapHeight = 25;
            myMapData.Init();
        }

        private void Tileset_MouseEnter(object sender, EventArgs e)
        {
            Tileset.Width = Tileset.Image.Width;
            Tileset.Height = Tileset.Image.Height;
        }

        private void Tileset_MouseLeave(object sender, EventArgs e)
        {
            Tileset.Width = myMapData.Tileset.TileWidth;
            Tileset.Height = myMapData.Tileset.TileHeight;
        }

        private void SelectTileFromTileset(int aX, int aY)
        {
            myTileSourceX = aX;
            myTileSourceY = aY;

            myOldTilesetMarker.X = myTileSourceX;
            myOldTilesetMarker.Y = myTileSourceY;

            TilePreview.Refresh();
        }

        private void Tileset_Click(object sender, EventArgs e)
        {
            Tileset.Width = myMapData.Tileset.TileWidth;
            Tileset.Height = myMapData.Tileset.TileHeight;

            int x = (int)(((MouseEventArgs)e).X / myMapData.Tileset.TileWidth) * myMapData.Tileset.TileWidth;
            int y = (int)(((MouseEventArgs)e).Y / myMapData.Tileset.TileHeight) * myMapData.Tileset.TileHeight;

            SelectTileFromTileset(x, y);
        }

        private void TilePreview_Paint(object sender, PaintEventArgs e)
        {
            if (myMapData.GetTileSetImage() != null)
            {
                e.Graphics.DrawImage(myMapData.GetTileSetImage(), new Rectangle(0, 0, myMapData.Tileset.TileWidth, myMapData.Tileset.TileHeight),
                    new Rectangle(myTileSourceX, myTileSourceY, myMapData.Tileset.TileWidth, myMapData.Tileset.TileHeight), GraphicsUnit.Pixel);
            }
        }

        private void Tileset_MouseMove(object sender, MouseEventArgs e)
        {
            myTilesetMarker.X = (int)(e.X / myMapData.Tileset.TileWidth) * myMapData.Tileset.TileWidth;
            myTilesetMarker.Y = (int)(e.Y / myMapData.Tileset.TileHeight) * myMapData.Tileset.TileHeight;
            Tileset.Refresh();
        }

        private void Tileset_Paint(object sender, PaintEventArgs e)
        {
            if (myMapData.Tileset != null)
            {
                Pen redPen = new Pen(Color.Red, 2);
                Pen yellowPen = new Pen(Color.Yellow, 2);
                e.Graphics.DrawRectangle(redPen, myTilesetMarker.X, myTilesetMarker.Y, myMapData.Tileset.TileWidth, myMapData.Tileset.TileHeight);
                e.Graphics.DrawRectangle(yellowPen, myOldTilesetMarker.X, myOldTilesetMarker.Y, myMapData.Tileset.TileWidth, myMapData.Tileset.TileHeight);
            }
        }

        private void SetTile(int aTargetNodeX, int aTargetNodeY, int aTileIndex, bool aUpdateNeighbours = false)
        {
            if (myTilesets[Tilesets.Text].IsAutoTile(aTileIndex) == true)
            {
                int autoTileValue = 0;
                int leftTileIndex = myMapData.GetTile(aTargetNodeX - 1, aTargetNodeY);
                int rightTileIndex = myMapData.GetTile(aTargetNodeX + 1, aTargetNodeY);
                int upperTileIndex = myMapData.GetTile(aTargetNodeX, aTargetNodeY - 1);
                int lowerTileIndex = myMapData.GetTile(aTargetNodeX, aTargetNodeY + 1);

                autoTileValue |= Convert.ToInt32(myTilesets[Tilesets.Text].IsAutoTile(upperTileIndex)) * 1;
                autoTileValue |= Convert.ToInt32(myTilesets[Tilesets.Text].IsAutoTile(lowerTileIndex)) * 4;
                autoTileValue |= Convert.ToInt32(myTilesets[Tilesets.Text].IsAutoTile(rightTileIndex)) * 2;
                autoTileValue |= Convert.ToInt32(myTilesets[Tilesets.Text].IsAutoTile(leftTileIndex)) * 8;

                int pickedTile = myMapData.Tileset.GetAutoTile(autoTileValue);
                if (pickedTile == -1)
                    pickedTile = aTileIndex;

                char x = Convert.ToChar(pickedTile % myMapData.Tileset.GetTileCols());
                char y = Convert.ToChar(pickedTile / myMapData.Tileset.GetTileCols());

                SetTile(aTargetNodeX, aTargetNodeY, x, y);
            }
            else
            {
                SetTile(aTargetNodeX, aTargetNodeY, (char)(myTilesetMarker.X / myMapData.Tileset.TileWidth), (char)(myTilesetMarker.Y / myMapData.Tileset.TileHeight));
            }
            if (aUpdateNeighbours)
            {
                SetIfAutoTile(aTargetNodeX - 1, aTargetNodeY, myMapData.GetTile(aTargetNodeX - 1, aTargetNodeY));
                SetIfAutoTile(aTargetNodeX + 1, aTargetNodeY, myMapData.GetTile(aTargetNodeX + 1, aTargetNodeY));
                SetIfAutoTile(aTargetNodeX, aTargetNodeY - 1, myMapData.GetTile(aTargetNodeX, aTargetNodeY - 1));
                SetIfAutoTile(aTargetNodeX, aTargetNodeY + 1, myMapData.GetTile(aTargetNodeX, aTargetNodeY + 1));
            }
        }

        void SetIfAutoTile(int aTargetNodeX, int aTargetNodeY, int aTileIndex)
        {
            if (aTargetNodeX >= 0 && aTargetNodeY >= 0 &&
                aTargetNodeX < myMapData.myMapWidth && aTargetNodeY < myMapData.myMapHeight &&
                myTilesets[Tilesets.Text].IsAutoTile(aTileIndex) == true)
            {
                SetTile(aTargetNodeX, aTargetNodeY, aTileIndex, false);
            }
        }
        private void Map_Click(object sender, EventArgs e)
        {
            MouseEventArgs mouseEvent = (MouseEventArgs)e;
            if (EditTab.SelectedTab.Text == "Tileset")
            {
                if (mouseEvent.Button == MouseButtons.Left)
                {
                    myLeftMousePressed = true;
                    int targetNodeX = (int)(mouseEvent.X / myMapData.Tileset.TileWidth);
                    int targetNodeY = (int)(mouseEvent.Y / myMapData.Tileset.TileHeight);
                    int tileIndex = (myTilesetMarker.X / myMapData.Tileset.TileWidth) + (myTilesetMarker.Y / myMapData.Tileset.TileHeight) * myTilesets[Tilesets.Text].GetTileCols();
                    SetTile(targetNodeX, targetNodeY, tileIndex, true);
                }
                else if (mouseEvent.Button == MouseButtons.Right)
                {
                    myRightMousePressed = true;
                }
            }
            else if (EditTab.SelectedTab.Text == "Objects")
            {
                mySelectedGameObject = PickObject(mouseEvent);
                Map.Refresh();
            }
        }

        private GameObject PickObject(MouseEventArgs aMouseEvent)
        {
            var gameObjects = myMapData.GetGameObjects();
            foreach (GameObject gameObject in gameObjects)
            {
                if (gameObject.IsInside(aMouseEvent.X, aMouseEvent.Y) == true)
                {
                    return gameObject;
                }
            }
            return null;
        }

        private void SetTile(int aXNode, int aYNode, char aXnodeSource, char aYNodeSource)
        {
            myMapData.SetTile(aXNode, aYNode, aXnodeSource, aYNodeSource);
        }

        private void Map_MouseMove(object sender, MouseEventArgs e)
        {
            myMapMarker.X = (int)(e.X / myMapData.Tileset.TileWidth) * myMapData.Tileset.TileWidth;
            myMapMarker.Y = (int)(e.Y / myMapData.Tileset.TileHeight) * myMapData.Tileset.TileHeight;

            if (myLeftMousePressed)
            {
                Map_Click(sender, e);
            }

            if (myRightMousePressed == true)
            {
                Map.Left += e.Location.X - myOldMousePosition.X;
                Map.Top += e.Location.Y - myOldMousePosition.Y;
            }
            else
            {
                myOldMousePosition.X = e.Location.X;
                myOldMousePosition.Y = e.Location.Y;
            }

            Map.Refresh();
        }

        private void Map_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.Clear(Color.Black);
            DrawTiles(e);
            DrawGameObjects(e);

            if (EditTab.SelectedTab.Text == "Tileset")
            {
                DrawTileEditGizmos(e);
            }
            else if (EditTab.SelectedTab.Text == "Objects")
            {
                DrawObjectEditGizmos(e);
            }
        }

        private void DrawGameObjects(PaintEventArgs e)
        {
            var gameObjects = myMapData.GetGameObjects();
            foreach (GameObject gameObject in gameObjects)
            {
                int halfWidth = myGameObjectTypeImages[gameObject.myGameObjectType.ID].Width / 2;
                int halfHeight = myGameObjectTypeImages[gameObject.myGameObjectType.ID].Height / 2;
                Point position = new Point((int)gameObject.myPosition.x - halfWidth, (int)gameObject.myPosition.y - halfHeight);
                int ID = gameObject.myGameObjectType.ID;
                e.Graphics.DrawImage(myGameObjectTypeImages[ID], new Rectangle(position, 
                    new Size(myGameObjectTypeImages[gameObject.myGameObjectType.ID].Width, myGameObjectTypeImages[gameObject.myGameObjectType.ID].Height) ));
            }
        }

        private void DrawObjectEditGizmos(PaintEventArgs e)
        {
            if (myIsDraggingObject == true)
            {
                int halfWidth = myGameObjectTypeImages[GameObjectTypesList.SelectedIndex].Width / 2;
                int halfHeight = myGameObjectTypeImages[GameObjectTypesList.SelectedIndex].Height / 2;

                Point previewPos = new Point(myOldMousePosition.X, myOldMousePosition.Y);
                previewPos.X -= halfWidth;
                previewPos.Y -= halfHeight;
                e.Graphics.DrawImage(myGameObjectTypeImages[GameObjectTypesList.SelectedIndex], previewPos);
            }

            if (mySelectedGameObject != null)
            {
                Pen greenPen = new Pen(Color.Green);
                int halfWidth = myGameObjectTypeImages[mySelectedGameObject.myGameObjectType.ID].Width / 2;
                int halfHeight = myGameObjectTypeImages[mySelectedGameObject.myGameObjectType.ID].Height / 2;
                e.Graphics.DrawRectangle(greenPen, mySelectedGameObject.myPosition.x - halfWidth, mySelectedGameObject.myPosition.y - halfHeight, 
                    halfWidth * 2, halfHeight * 2);
            }
        }
        private void DrawTileEditGizmos(PaintEventArgs e)
        {
            if (myMapData.GetTileSetImage() != null)
            {
                Pen greenPen = new Pen(Color.Green, 2);

                e.Graphics.DrawImage(myMapData.GetTileSetImage(), new Rectangle(myMapMarker.X, myMapMarker.Y, myMapData.Tileset.TileWidth, myMapData.Tileset.TileHeight),
                    new Rectangle(myTileSourceX, myTileSourceY, myMapData.Tileset.TileWidth, myMapData.Tileset.TileHeight), GraphicsUnit.Pixel);

                e.Graphics.DrawRectangle(greenPen, myMapMarker.X, myMapMarker.Y, myMapData.Tileset.TileWidth, myMapData.Tileset.TileHeight);
            }
        }

        private void DrawTiles(PaintEventArgs e)
        {
            if (myMapData.GetTileSetImage() != null)
            {
                for (int y = 0; y < myMapData.myMapHeight; y++)
                {
                    for (int x = 0; x < myMapData.myMapWidth; x++)
                    {
                        Rectangle position = new Rectangle(x * myMapData.Tileset.TileWidth, y * myMapData.Tileset.TileHeight, myMapData.Tileset.TileWidth, myMapData.Tileset.TileHeight);
                        Point sourcePosition = myMapData.GetTileSource(x, y);
                        Rectangle source = new Rectangle(sourcePosition, new Size(myMapData.Tileset.TileWidth, myMapData.Tileset.TileHeight));
                        e.Graphics.DrawImage(myMapData.GetTileSetImage(), position, source, GraphicsUnit.Pixel);
                    }
                }
            }
        }

        private void Map_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                myLeftMousePressed = false;
            }
            else if (e.Button == MouseButtons.Right)
            {
                myRightMousePressed = false;
            }
        }

        private void Map_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                myLeftMousePressed = true;
            }
            else if (e.Button == MouseButtons.Right)
            {
                myRightMousePressed = true;
            }
        }

        private void Map_MouseLeave(object sender, EventArgs e)
        {
            myLeftMousePressed = false;
            myRightMousePressed = false;
        }

        private void QuitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void SaveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            myMapData.Save();
        }

        private void OpenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            myMapData.LoadFromFile("data/testLevel.lvl");
            Tilesets.SelectedItem = myMapData.myTilesetName;
            Map.Refresh();
        }

        private void TilesetEditorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TilesetEditor tilesetEditor = new TilesetEditor();
            tilesetEditor.Show();
        }

        private void Tilesets_SelectedIndexChanged(object sender, EventArgs e)
        {
            myMapData.Tileset = myTilesets[Tilesets.Text];
            Tileset.Image = myMapData.GetTileSetImage();
            Map.Enabled = true;
            Tileset.Enabled = true;
            TilePreview.Width = myMapData.Tileset.TileWidth;
            TilePreview.Height = myMapData.Tileset.TileHeight;
            Tileset.Width = myMapData.Tileset.TileWidth;
            Tileset.Height = myMapData.Tileset.TileHeight;

            Map.Width = myMapData.myMapWidth * myMapData.Tileset.TileWidth;
            Map.Height = myMapData.myMapHeight * myMapData.Tileset.TileHeight;

            Map.Refresh();
            Tileset.Refresh();
            TilePreview.Refresh();
        }

        private bool MoveMapWithKeys(Keys keyData)
        {
            bool handled = false;
            int moveSpeed = 100;

            switch (keyData)
            {
                case Keys.Left:
                    Map.Left += moveSpeed;
                    Map.Refresh();
                    handled = true; break;
                case Keys.Right:
                    Map.Left -= moveSpeed;
                    Map.Refresh();
                    handled = true; break;
                case Keys.Up:
                    Map.Top += moveSpeed;
                    Map.Refresh();
                    handled = true; break;
                case Keys.Down:
                    Map.Top -= moveSpeed;
                    Map.Refresh();
                    handled = true; break;
            }

            return handled;
        }
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            bool handled = false;
            if (EditTab.SelectedTab.Text == "Objects")
            {
                if (mySelectedGameObject != null)
                {
                    switch (keyData)
                    {
                        case Keys.Delete:
                            myMapData.GetGameObjects().Remove(mySelectedGameObject);
                            mySelectedGameObject = null;
                            Map.Refresh();
                            handled = true; break;
                        case Keys.Left:
                            mySelectedGameObject.myPosition.x--;
                            Map.Refresh();
                            handled = true; break;
                        case Keys.Right:
                            mySelectedGameObject.myPosition.x++;
                            Map.Refresh();
                            handled = true; break;
                        case Keys.Up:
                            mySelectedGameObject.myPosition.y--;
                            Map.Refresh();
                            handled = true; break;
                        case Keys.Down:
                            mySelectedGameObject.myPosition.y++;
                            Map.Refresh();
                            handled = true; break;
                    }
                }
                else
                {
                    if (MoveMapWithKeys(keyData))
                        handled = true;
                }
            }
            else if (EditTab.SelectedTab.Text == "Tileset")
            {
                if (MoveMapWithKeys(keyData))
                    handled = true;
            }

            if (handled)
                return true;

            return base.ProcessCmdKey(ref msg, keyData);
        }

        private void VMapScroll_Scroll(object sender, ScrollEventArgs e)
        {
            Map.Top = -(int)((vMapScroll.Value / 100.0f) * Map.Height);
        }

        private void HMapScroll_Scroll(object sender, ScrollEventArgs e)
        {
            Map.Left = -(int)((hMapScroll.Value / 100.0f) * Map.Width);
        }

        private void GameObjectTypeEditorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GameObjectEditor gameObjectEditor = new GameObjectEditor();
            gameObjectEditor.Show();
            this.Enabled = false;
        }

        private void GameObjectTypesList_SelectedIndexChanged(object sender, EventArgs e)
        {
            ObjectTypePrevPic.Image = Image.FromFile(ourGameObjectTypes[GameObjectTypesList.SelectedIndex].image);
        }

        private void GameObjectTypesList_MouseDown(object sender, MouseEventArgs e)
        {
            DragDropEffects dragDropEffect = DoDragDrop(GameObjectTypesList.SelectedIndex, DragDropEffects.Copy);
            ObjectTypePrevPic.Image = Image.FromFile(ourGameObjectTypes[GameObjectTypesList.SelectedIndex].image);
        }

        private void MenuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }
        private void Map_DragEnter(object sender, DragEventArgs e)
        {
            e.Effect = DragDropEffects.Copy;
            myIsDraggingObject = true;
        }

        private void Map_DragLeave(object sender, EventArgs e)
        {
            myIsDraggingObject = false;
        }

        private void Map_DragOver(object sender, EventArgs e)
        {
            DragEventArgs drag = (DragEventArgs)e;
            Point localPos = Map.PointToClient(new Point(drag.X, drag.Y));
            myOldMousePosition.X = localPos.X;
            myOldMousePosition.Y = localPos.Y;
            Map.Refresh();
        }

        private void Map_DragDrop(object sender, DragEventArgs e)
        {
            myIsDraggingObject = false;
            if (GameObjectTypesList.SelectedItem != null)
            {
                Vector2 position = new Vector2(Map.PointToClient(Cursor.Position).X, Map.PointToClient(Cursor.Position).Y);
                mySelectedGameObject = myMapData.PlaceObject(position, ourGameObjectTypes[GameObjectTypesList.SelectedIndex]);
            }
        }

        private void GameObjectTypesList_SelectedIndexChanged(object sender, MouseEventArgs e)
        {
            ObjectTypePrevPic.Image = Image.FromFile(ourGameObjectTypes[GameObjectTypesList.SelectedIndex].image);
        }

        private void mapSettingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MapSettings mapSettings = new MapSettings(myMapData.myMapWidth, myMapData.myMapHeight);
            DialogResult result = mapSettings.ShowDialog();
            if (result == DialogResult.OK)
            {
                myMapData.ResizeMap(mapSettings.GetMapWidth(), mapSettings.GetMapHeight());
                Map.Refresh();
            }
        }

        private void createFrameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            for (int x = 0; x < myMapData.myMapWidth; x++)
            {
                SetTile(x, 0, 1, true);
                SetTile(x, myMapData.myMapHeight - 1, 1, true);
            }

            for (int y = 0; y < myMapData.myMapHeight; y++)
            {
                SetTile(0, y, 1, true);
                SetTile(myMapData.myMapWidth - 1, y, 1, true);
            }
        }
    }
}

