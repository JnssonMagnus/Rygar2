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
        private EditorCamera myCamera = new EditorCamera();
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

        private World myWorld;

        private Point myOldMousePosition = new Point();

        private struct MouseStatus
        {
            public bool myLeftMousePressed;
            public bool myRightMousePressed;
            public bool myLeftMouseDown;
            public bool myRightMouseDown;
            public bool myLeftMouseUp;
            public bool myRightMouseUp;
        };

        MouseStatus myMouseStatus;


        private bool myIsDraggingObject = false;

        public MapEditor()
        {
            InitializeComponent();
            ourInstance = this;
            myWorld = new World();
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
                if (gameObjectType.image != null)
                {
                    try
                    {
                        Image image = Image.FromFile(gameObjectType.image);
                        myGameObjectTypeImages[gameObjectType.ID] = image;
                    }
                    catch
                    {
                        MessageBox.Show("Image not found" + gameObjectType.image);
                    }
                }
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

            myCamera.Size.x = (int)Map.Width * 10;
            myCamera.Size.y = (int)Map.Height * 10;

            myWorld.LoadAll(myTilesets);
            Tilesets.SelectedIndex = Tilesets.Items.IndexOf(myWorld.GetMapChunkFromTileIndex(0, 0).myTilesetName);
            Map.Refresh();
        }

        private void Tileset_MouseEnter(object sender, EventArgs e)
        {
            Tileset.Width = Tileset.Image.Width;
            Tileset.Height = Tileset.Image.Height;
        }

        private void Tileset_MouseLeave(object sender, EventArgs e)
        {
            Tileset.Width = Settings.TileWidth();
            Tileset.Height = Settings.TileHeight();
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
            Tileset.Width = Settings.TileWidth();
            Tileset.Height = Settings.TileHeight();

            int x = (int)(((MouseEventArgs)e).X / Tileset.Width) * Tileset.Width;
            int y = (int)(((MouseEventArgs)e).Y / Tileset.Height) * Tileset.Height;

            SelectTileFromTileset(x, y);
        }

        private void TilePreview_Paint(object sender, PaintEventArgs e)
        {
            if (Tilesets.Text.Length != 0)
            {
                e.Graphics.DrawImage(myTilesets[Tilesets.Text].GetImage(), new Rectangle(0, 0, Settings.TileWidth(), Settings.TileHeight()),
                    new Rectangle(myTileSourceX, myTileSourceY, Settings.TileWidth(), Settings.TileHeight()), GraphicsUnit.Pixel);
            }
        }

        private void Tileset_MouseMove(object sender, MouseEventArgs e)
        {
            myTilesetMarker.X = (int)(e.X / Settings.TileWidth()) * Settings.TileWidth();
            myTilesetMarker.Y = (int)(e.Y / Settings.TileHeight()) * Settings.TileHeight();
            Tileset.Refresh();
        }

        private void Tileset_Paint(object sender, PaintEventArgs e)
        {
            if (Tilesets.Text.Length != 0)
            {
                Pen redPen = new Pen(Color.Red, 2);
                Pen yellowPen = new Pen(Color.Yellow, 2);
                e.Graphics.DrawRectangle(redPen, myTilesetMarker.X, myTilesetMarker.Y, Settings.TileWidth(), Settings.TileHeight());
                e.Graphics.DrawRectangle(yellowPen, myOldTilesetMarker.X, myOldTilesetMarker.Y, Settings.TileWidth(), Settings.TileHeight());
            }
        }

        private void SetTile(int aTargetNodeX, int aTargetNodeY, int aTileIndex, bool aUpdateNeighbours = false)
        {
            var mapChunk = myWorld.GetMapChunkFromTileIndex(aTargetNodeX, aTargetNodeY);
            mapChunk.Tileset = myTilesets[Tilesets.Text];

            if (myTilesets[Tilesets.Text].IsAutoTile(aTileIndex) == true)
            {
                int autoTileValue = 0;
                int leftTileIndex = myWorld.GetTile(aTargetNodeX - 1, aTargetNodeY);
                int rightTileIndex = myWorld.GetTile(aTargetNodeX + 1, aTargetNodeY);
                int upperTileIndex = myWorld.GetTile(aTargetNodeX, aTargetNodeY - 1);
                int lowerTileIndex = myWorld.GetTile(aTargetNodeX, aTargetNodeY + 1);

                autoTileValue |= Convert.ToInt32(myTilesets[Tilesets.Text].IsAutoTile(upperTileIndex)) * 1;
                autoTileValue |= Convert.ToInt32(myTilesets[Tilesets.Text].IsAutoTile(lowerTileIndex)) * 4;
                autoTileValue |= Convert.ToInt32(myTilesets[Tilesets.Text].IsAutoTile(rightTileIndex)) * 2;
                autoTileValue |= Convert.ToInt32(myTilesets[Tilesets.Text].IsAutoTile(leftTileIndex)) * 8;

                int pickedTile = myTilesets[Tilesets.Text].GetAutoTile(autoTileValue);
                if (pickedTile == -1)
                    pickedTile = aTileIndex;

                char x = Convert.ToChar(pickedTile % myTilesets[Tilesets.Text].GetTileCols());
                char y = Convert.ToChar(pickedTile / myTilesets[Tilesets.Text].GetTileCols());

                SetTile(aTargetNodeX, aTargetNodeY, x, y);
            }
            else
            {
                SetTile(aTargetNodeX, aTargetNodeY, (char)(myTilesetMarker.X / Settings.TileWidth()), (char)(myTilesetMarker.Y / Settings.TileHeight()));
            }
            if (aUpdateNeighbours)
            {
                SetIfAutoTile(aTargetNodeX - 1, aTargetNodeY, myWorld.GetTile(aTargetNodeX - 1, aTargetNodeY));
                SetIfAutoTile(aTargetNodeX + 1, aTargetNodeY, myWorld.GetTile(aTargetNodeX + 1, aTargetNodeY));
                SetIfAutoTile(aTargetNodeX, aTargetNodeY - 1, myWorld.GetTile(aTargetNodeX, aTargetNodeY - 1));
                SetIfAutoTile(aTargetNodeX, aTargetNodeY + 1, myWorld.GetTile(aTargetNodeX, aTargetNodeY + 1));
            }
        }

        void SetIfAutoTile(int aTargetNodeX, int aTargetNodeY, int aTileIndex)
        {
            if (aTargetNodeX >= 0 && aTargetNodeY >= 0 && myTilesets[Tilesets.Text].IsAutoTile(aTileIndex) == true)
            {
                SetTile(aTargetNodeX, aTargetNodeY, aTileIndex, false);
            }
        }
        private void Map_Click(object sender, EventArgs e)
        {

        }

        private GameObject PickObject(MouseEventArgs aMouseEvent)
        {
            var gameObjects = myWorld.GetGameObjectsFromChunk(aMouseEvent.X + (int)myCamera.Position.x, aMouseEvent.Y + (int)myCamera.Position.y);
            foreach (GameObject gameObject in gameObjects)
            {
                if (gameObject.IsInside(aMouseEvent.X + (int)myCamera.Position.x, aMouseEvent.Y + (int)myCamera.Position.y) == true)
                {
                    if (mySelectedGameObject != gameObject)
                    {
                        return gameObject;
                    }
                }
            }

            if (mySelectedGameObject != null && mySelectedGameObject.IsInside(aMouseEvent.X + (int)myCamera.Position.x, aMouseEvent.Y + (int)myCamera.Position.y) == true)
            {
                return mySelectedGameObject;
            }

            return null;
        }

        private void SetTile(int aXNode, int aYNode, char aXnodeSource, char aYNodeSource)
        {
            myWorld.SetTile(aXNode, aYNode, aXnodeSource, aYNodeSource, myTilesets[Tilesets.Text]);
        }

        private void Map_MouseMove(object sender, MouseEventArgs e)
        {
            int offSetX = (int)myCamera.Position.x % Settings.TileWidth() - 1;
            int offSetY = (int)myCamera.Position.y % Settings.TileHeight() - 1;
            myMapMarker.X = (int)((e.X + offSetX) / Settings.TileWidth()) * Settings.TileWidth() - offSetX;
            myMapMarker.Y = (int)((e.Y + offSetY) / Settings.TileHeight()) * Settings.TileHeight() - offSetY;


            if (EditTab.SelectedTab.Text == "Tileset")
            {
                if (myMouseStatus.myLeftMousePressed)
                {
                    SetTile(e);
                }
            }
            else if (EditTab.SelectedTab.Text == "Objects")
            {
                if (myMouseStatus.myLeftMousePressed && mySelectedGameObject != null)
                {
                    mySelectedGameObject.myPosition = new Vector2(e.X + myCamera.Position.x, e.Y + myCamera.Position.y);
                }
            }

            // Drag camera
            if (myMouseStatus.myRightMousePressed == true)
            {
                myCamera.Position.x -= e.Location.X - myOldMousePosition.X;
                myCamera.Position.y -= e.Location.Y - myOldMousePosition.Y;
                myOldMousePosition.X = e.Location.X;
                myOldMousePosition.Y = e.Location.Y;
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
            var gameObjects = myWorld.GetGameObjectsFromFrustum(myCamera);
            foreach (GameObject gameObject in gameObjects)
            {
                int halfWidth = myGameObjectTypeImages[gameObject.myGameObjectType.ID].Width / 2;
                int halfHeight = myGameObjectTypeImages[gameObject.myGameObjectType.ID].Height / 2;
                Point position = new Point((int)gameObject.myPosition.x - halfWidth - (int)myCamera.Position.x, (int)gameObject.myPosition.y - halfHeight - (int)myCamera.Position.y);
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
                e.Graphics.DrawRectangle(greenPen, mySelectedGameObject.myPosition.x - halfWidth - myCamera.Position.x, mySelectedGameObject.myPosition.y - halfHeight - myCamera.Position.y, 
                    halfWidth * 2, halfHeight * 2);
            }
        }
        private void DrawTileEditGizmos(PaintEventArgs e)
        {
            var visibleChunks = myWorld.GetChunksInFrustum(myCamera);
            foreach (var chunk in visibleChunks)
            {
                if (chunk.GetTileSetImage() != null)
                {
                    Pen greenPen = new Pen(Color.Green, 2);

                    e.Graphics.DrawImage(chunk.GetTileSetImage(), new Rectangle(myMapMarker.X, myMapMarker.Y, Settings.TileWidth(), Settings.TileHeight()),
                        new Rectangle(myTileSourceX, myTileSourceY, Settings.TileWidth(), Settings.TileHeight()), GraphicsUnit.Pixel);

                    e.Graphics.DrawRectangle(greenPen, myMapMarker.X, myMapMarker.Y, Settings.TileWidth(), Settings.TileHeight());
                }
            }
        }

        private void DrawTiles(PaintEventArgs e)
        {
            var visibleMapChunks = myWorld.GetChunksInFrustum(myCamera);
            foreach (var mapChunk in visibleMapChunks)
            {
                if (mapChunk != null && mapChunk.GetTileSetImage() != null)
                {
                    Vector2 chunkWorldPosition = mapChunk.GetChunkWorldPosition();
                    for (int y = 0; y < mapChunk.myMapHeight; y++)
                    {
                        for (int x = 0; x < mapChunk.myMapWidth; x++)
                        {
                            int tileXPosition = x * mapChunk.Tileset.TileWidth + (int)chunkWorldPosition.x - (int)myCamera.Position.x;
                            int tileYPosition = y * mapChunk.Tileset.TileHeight + (int)chunkWorldPosition.y - (int)myCamera.Position.y;
                            Rectangle position = new Rectangle(tileXPosition, tileYPosition, mapChunk.Tileset.TileWidth, mapChunk.Tileset.TileHeight);
                            Point sourcePosition = mapChunk.GetTileSource(x, y);
                            Rectangle source = new Rectangle(sourcePosition, new Size(mapChunk.Tileset.TileWidth, mapChunk.Tileset.TileHeight));
                            e.Graphics.DrawImage(mapChunk.GetTileSetImage(), position, source, GraphicsUnit.Pixel);
                        }
                    }
                }
            }
        }

        private void Map_MouseUp(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Left:
                    myMouseStatus.myLeftMousePressed = false;
                    myMouseStatus.myLeftMouseDown = false;
                    myMouseStatus.myLeftMouseUp = true;
                    break;
                case MouseButtons.Right:
                    myMouseStatus.myRightMousePressed = false;
                    myMouseStatus.myRightMouseDown = false;
                    myMouseStatus.myRightMouseUp = true;
                    break;
            }

            if (EditTab.SelectedTab.Text == "Objects" && myMouseStatus.myLeftMouseUp && mySelectedGameObject != null)
            {
                mySelectedGameObject.myChunk.GetGameObjects().Remove(mySelectedGameObject);
                myWorld.PlaceObject(mySelectedGameObject);
            }
        }

        private void Map_MouseDown(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Left:
                    myMouseStatus.myLeftMousePressed = true;
                    myMouseStatus.myLeftMouseDown = true;
                    break;
                case MouseButtons.Right:
                    myMouseStatus.myRightMousePressed = true;
                    myMouseStatus.myRightMouseDown = true;
                    break;
            }

            MouseEventArgs mouseEvent = (MouseEventArgs)e;

            if (EditTab.SelectedTab.Text == "Tileset")
            {
                if (mouseEvent.Button == MouseButtons.Left)
                {
                    SetTile(mouseEvent);
                }
            }
            else if (EditTab.SelectedTab.Text == "Objects")
            {
                mySelectedGameObject = PickObject(mouseEvent);
                Map.Refresh();
            }
        }

        private void SetTile(MouseEventArgs mouseEventArgs)
        {
            int targetNodeX = (int)((mouseEventArgs.X + myCamera.Position.x) / Settings.TileWidth());
            int targetNodeY = (int)((mouseEventArgs.Y + myCamera.Position.y) / Settings.TileHeight());
            int tileIndex = (myTilesetMarker.X / Settings.TileWidth()) + (myTilesetMarker.Y / Settings.TileHeight()) * myTilesets[Tilesets.Text].GetTileCols();
            SetTile(targetNodeX, targetNodeY, tileIndex, true);
        }

        private void Map_MouseLeave(object sender, EventArgs e)
        {
            myMouseStatus.myLeftMousePressed = false;
            myMouseStatus.myRightMousePressed = false;
        }

        private void QuitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void SaveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            myWorld.SaveAll();
        }

        private void OpenToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }

        private void TilesetEditorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TilesetEditor tilesetEditor = new TilesetEditor();
            tilesetEditor.Show();
        }

        private void Tilesets_SelectedIndexChanged(object sender, EventArgs e)
        {            
            Tileset.Image = myTilesets[Tilesets.Text].GetImage();
            Map.Enabled = true;
            Tileset.Enabled = true;
            TilePreview.Width = myTilesets[Tilesets.Text].TileWidth;
            TilePreview.Height = myTilesets[Tilesets.Text].TileHeight;
            Tileset.Width = myTilesets[Tilesets.Text].TileWidth;
            Tileset.Height = myTilesets[Tilesets.Text].TileHeight;

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
                    myCamera.Position.x -= moveSpeed;
                    Map.Refresh();
                    handled = true; break;
                case Keys.Right:
                    myCamera.Position.x += moveSpeed;
                    Map.Refresh();
                    handled = true; break;
                case Keys.Up:
                    myCamera.Position.y -= moveSpeed;
                    Map.Refresh();
                    handled = true; break;
                case Keys.Down:
                    myCamera.Position.y += moveSpeed;
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
                            mySelectedGameObject.myChunk.GetGameObjects().Remove(mySelectedGameObject);
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
            myCamera.Position.y =- (int)((vMapScroll.Value / 100.0f) * Map.Height);
            Map.Refresh();
        }

        private void HMapScroll_Scroll(object sender, ScrollEventArgs e)
        {
            myCamera.Position.x = -(int)((hMapScroll.Value / 100.0f) * Map.Width);
            Map.Refresh();
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
                position.x += myCamera.Position.x;
                position.y += myCamera.Position.y;
                mySelectedGameObject = myWorld.PlaceObject(position, ourGameObjectTypes[GameObjectTypesList.SelectedIndex]);
            }
        }

        private void GameObjectTypesList_SelectedIndexChanged(object sender, MouseEventArgs e)
        {
            ObjectTypePrevPic.Image = Image.FromFile(ourGameObjectTypes[GameObjectTypesList.SelectedIndex].image);
        }

        private void mapSettingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MapSettings mapSettings = new MapSettings(Settings.MapWidth(), Settings.MapHeight());
            DialogResult result = mapSettings.ShowDialog();
            if (result == DialogResult.OK)
            {
               // myMapData.ResizeMap(mapSettings.GetMapWidth(), mapSettings.GetMapHeight());
                Map.Refresh();
            }
        }

        private void createFrameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            for (int x = 0; x < Settings.MapWidth(); x++)
            {
                SetTile(x, 0, 1, true);
                SetTile(x, Settings.MapHeight() - 1, 1, true);
            }

            for (int y = 0; y < Settings.MapHeight(); y++)
            {
                SetTile(0, y, 1, true);
                SetTile(Settings.MapWidth() - 1, y, 1, true);
            }
        }
    }
}

