using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Xml;

namespace PlatformEditor
{
    class MapData
    {
        public string Space = "preserve";

        public int myMapWidth = 25;
        public int myMapHeight = 25;

        private List<GameObject> myGameObjects = new List<GameObject>();

        private Image myTileSetImage;
        private string myFilename;
        private char[] myTileData;

        public string myTilesetName;
        private Tileset myTileset;
        public Tileset Tileset
        {
            get
            {
                return myTileset;
            }

            set
            {
                myTileset = value;
                myTileSetImage = Image.FromFile(Settings.GetDataPath() + "data/gfx/tilesets/" + myTileset.TileImage);
                myTilesetName = myTileset.myTilesetName;
            }
        }

        public void Save()
        {
            System.IO.BinaryWriter binaryWriter = new System.IO.BinaryWriter(System.IO.File.Open(Settings.GetDataPath() + "data/testLevel.lvl", System.IO.FileMode.OpenOrCreate));
            myFilename = "testLevel1.lvl\n";

            // Map
            binaryWriter.Write(myFilename);
            binaryWriter.Write(myTileset.myTilesetName+"\n");
            binaryWriter.Write(myMapWidth);
            binaryWriter.Write(myMapHeight);
            binaryWriter.Write(myTileData, 0, myMapWidth * myMapHeight);

            // GameObjects on map
            binaryWriter.Write(myGameObjects.Count);
            foreach (GameObject gameObject in myGameObjects)
            {
                binaryWriter.Write(gameObject.myGameObjectType.ID);
                binaryWriter.Write(gameObject.myPosition.x);
                binaryWriter.Write(gameObject.myPosition.y);
            }

            binaryWriter.Close();
        }

        public List<GameObject> GetGameObjects()
        {
            return myGameObjects;
        }   

        public GameObject PlaceObject(Vector2 aPosition, GameObjectType aGameObjectType)
        {
            GameObject gameObject = new GameObject();
            gameObject.myPosition = aPosition;
            gameObject.myGameObjectType = aGameObjectType;
            myGameObjects.Add(gameObject);
            return gameObject;
        }

        public Image GetTileSetImage()
        {
            return myTileSetImage;
        }
        public void SetTile(int aX, int aY, char aTileX, char aTileY)
        {
            if (aX >= 0 && aX >= 0 && aX < myMapWidth && aY < myMapHeight)
            {
                char tilesOnRow = (char)(myTileSetImage.Width / myTileset.TileWidth);
                char tileID = (char)(aTileX + (char)(aTileY * tilesOnRow));
                myTileData[aX + aY * myMapWidth] = tileID;
            }
        }

        public int GetTile(int aX, int aY)
        {
            if (aX >= 0 && aX < myMapWidth && aY >= 0 && aY < myMapHeight)
            {
                return myTileData[aX + aY * myMapWidth];
            }
            else
            {
                return -1;
            }
        }
        public Point GetTileSource(int aX, int aY)
        {
            if (myTileset != null)
            {
                char tileID = myTileData[aX + aY * myMapWidth];
                char tilesOnRow = (char)(myTileSetImage.Width / myTileset.TileWidth);

                Point source = new Point(myTileset.TileWidth * (tileID % tilesOnRow), myTileset.TileHeight * (tileID / tilesOnRow));
                return source;
            }
            else
            {
                return new Point(0, 0);
            }
        }

        public void ResizeMap(int aWidth, int aHeight)
        {
            var newTileData = new char[aWidth * aHeight];

            for (int y = 0; y < myMapHeight; y++)
            {
                for (int x = 0; x < myMapWidth; x++)
                {
                    if (y < aHeight && x < aWidth)
                    {
                        int tileIDtoTransfer = y * myMapWidth + x;
                        int tileIDtoTransferTo = y * aWidth + x;

                        newTileData[tileIDtoTransferTo] = myTileData[tileIDtoTransfer];
                    }                    
                }
            }

            myMapWidth = aWidth;
            myMapHeight = aHeight;

            myTileData = newTileData;
        }

        public void Init()
        {
            myTileData = new char[myMapWidth * myMapHeight];
        }

        private GameObjectType GetGameObjectTypeByID(int aID)
        {
            foreach (GameObjectType gameObjectType in MapEditor.ourGameObjectTypes)
            {
                if (aID == gameObjectType.ID)
                {
                    return gameObjectType;
                }
            }

            throw null;
            return new GameObjectType();
        }

        public void LoadFromFile(string aFilename)
        {
            System.IO.BinaryReader binaryReader = new System.IO.BinaryReader(System.IO.File.Open(aFilename, System.IO.FileMode.Open));
            myFilename = binaryReader.ReadString();
            myFilename = myFilename.Remove(myFilename.Length - 1, 1); // remove endline

            myTilesetName = binaryReader.ReadString();
            myTilesetName = myTilesetName.Remove(myTilesetName.Length - 1, 1); // remove endline

            myMapWidth = binaryReader.ReadInt32();
            myMapHeight = binaryReader.ReadInt32();

            myTileData = new char[myMapWidth * myMapHeight];
            binaryReader.Read(myTileData, 0, myMapWidth * myMapHeight);

            int gameObjectCount = binaryReader.ReadInt32();
            myGameObjects = new List<GameObject>();
            for (int gameObjectIndex = 0; gameObjectIndex < gameObjectCount; gameObjectIndex++)
            {
                GameObject gameObject = new GameObject();
                int ID = binaryReader.ReadInt32();
                gameObject.myGameObjectType = GetGameObjectTypeByID(ID);
                gameObject.myPosition.x = binaryReader.ReadSingle();
                gameObject.myPosition.y = binaryReader.ReadSingle();
                myGameObjects.Add(gameObject);
            }

            binaryReader.Close();
        }
    }
}
