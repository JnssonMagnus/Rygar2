using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Xml;
using System.IO;

namespace PlatformEditor
{
    public class MapData
    {
        public string Space = "preserve";

        public int myMapWidth = 25;
        public int myMapHeight = 25;

        private List<GameObject> myGameObjects = new List<GameObject>();
        private List<Enemy> myEnemies = new List<Enemy>();

        private Image myTileSetImage;
        private string myFilename;
        private char[] myTileData;
        private int myChunkId;

        public string myTilesetName;
        private Vector2 myChunkWorldPosition;
        private Tileset myTileset;

        public Vector2 GetChunkWorldPosition()
        {
            return myChunkWorldPosition;
        }
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

        public List<GameObject> GetGameObjects()
        {
            return myGameObjects;
        }
        public List<Enemy> GetEnemies()
        {
            return myEnemies;
        }

        public GameObject PlaceObject(Vector2 aPosition, GameObjectType aGameObjectType)
        {
            GameObject gameObject = new GameObject();
            gameObject.myPosition = aPosition;
            gameObject.myGameObjectType = aGameObjectType;
            gameObject.myChunk = this;
            myGameObjects.Add(gameObject);
            return gameObject;
        }

        public GameObject PlaceObject(GameObject gameObject)
        {
            gameObject.myChunk = this;
            myGameObjects.Add(gameObject);
            return gameObject;
        }
        public Enemy PlaceEnemy(Vector2 aPosition, EnemyType aEnemyType)
        {
            Enemy enemy = new Enemy();
            enemy.myPosition = aPosition;
            enemy.myEnemyType = aEnemyType;
            enemy.myChunk = this;
            myEnemies.Add(enemy);
            return enemy;
        }

        public Image GetTileSetImage()
        {
            return myTileSetImage;
        }
        public void SetTile(int aX, int aY, char aTileX, char aTileY)
        {
            int localX = aX - (int)myChunkWorldPosition.x / Settings.TileWidth();
            int localY = aY - (int)myChunkWorldPosition.y / Settings.TileHeight();
            if (localX >= 0 && localY >= 0 && localX < myMapWidth && localY < myMapHeight)
            {
                char tilesOnRow = (char)(myTileSetImage.Width / myTileset.TileWidth);
                char tileID = (char)(aTileX + (char)(aTileY * tilesOnRow));
                myTileData[localX + localY * myMapWidth] = tileID;
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

        public void Init(int aChunkId)
        {
            myTileData = new char[myMapWidth * myMapHeight];
            myChunkId = aChunkId;
            myChunkWorldPosition = GetChunkWorldPositionFromID(aChunkId);
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

        private EnemyType GetEnemyTypeByID(int aID)
        {
            foreach (EnemyType enemyType in MapEditor.ourEnemyTypes)
            {
                if (aID == enemyType.ID)
                {
                    return enemyType;
                }
            }

            throw null;
            return new EnemyType();
        }

        public void Save()
        {
            myFilename = "chunk_" + myChunkId.ToString();
            string filePath = Settings.GetDataPath() + "data/levels/";
            System.IO.BinaryWriter binaryWriter = new System.IO.BinaryWriter(System.IO.File.Open(filePath + myFilename, System.IO.FileMode.OpenOrCreate));

            // Ver
            binaryWriter.Write(1);

            // Map
            binaryWriter.Write(myFilename + "\n");
            binaryWriter.Write(myTileset.myTilesetName + "\n");
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

            // Enemies on map
            binaryWriter.Write(myEnemies.Count);
            foreach (Enemy enemy in myEnemies)
            {
                binaryWriter.Write(enemy.myEnemyType.ID);
                binaryWriter.Write(enemy.myPosition.x);
                binaryWriter.Write(enemy.myPosition.y);
            }
            binaryWriter.Close();
        }

        public void LoadFromFile(string aFilename)
        {
            System.IO.BinaryReader binaryReader = new System.IO.BinaryReader(System.IO.File.Open(aFilename, System.IO.FileMode.Open));

            int ver = binaryReader.ReadInt32();

            myFilename = binaryReader.ReadString();
            myFilename = myFilename.Remove(myFilename.Length - 1, 1); // remove endline

            myTilesetName = binaryReader.ReadString();
            myTilesetName = myTilesetName.Remove(myTilesetName.Length - 1, 1); // remove endline

            myMapWidth = binaryReader.ReadInt32();
            myMapHeight = binaryReader.ReadInt32();

            myTileData = new char[myMapWidth * myMapHeight];
            binaryReader.Read(myTileData, 0, myMapWidth * myMapHeight);


            // GameObjects on Map
            int gameObjectCount = binaryReader.ReadInt32();
            myGameObjects = new List<GameObject>();
            for (int gameObjectIndex = 0; gameObjectIndex < gameObjectCount; gameObjectIndex++)
            {
                GameObject gameObject = new GameObject();
                int ID = binaryReader.ReadInt32();
                gameObject.myGameObjectType = GetGameObjectTypeByID(ID);
                gameObject.myPosition.x = binaryReader.ReadSingle();
                gameObject.myPosition.y = binaryReader.ReadSingle();
                gameObject.myChunk = this;
                myGameObjects.Add(gameObject);
            }

            // Enemies on map
            int enemyCount = binaryReader.ReadInt32();
            myEnemies = new List<Enemy>();
            for (int enemyIndex = 0; enemyIndex < enemyCount; enemyIndex++)
            {
                Enemy enemy = new Enemy();
                int ID = binaryReader.ReadInt32();
                enemy.myEnemyType = GetEnemyTypeByID(ID);
                enemy.myPosition.x = binaryReader.ReadSingle();
                enemy.myPosition.y = binaryReader.ReadSingle();
                enemy.myChunk = this;
                myEnemies.Add(enemy);
            }

            binaryReader.Close();

            myChunkWorldPosition = GetChunkWorldPositionFromID(myChunkId);
        }

        private Vector2 GetChunkWorldPositionFromID(int chunkId)
        {
            int HIGH_VALUE = 10000000;
            int x = (chunkId / HIGH_VALUE) * Settings.MapWidth() * Settings.TileWidth();
            int y = (chunkId - (((x / Settings.TileWidth()) / Settings.MapWidth()) * HIGH_VALUE)) * Settings.TileHeight() * Settings.MapHeight();
            return new Vector2(x, y);
        }
    }
}
