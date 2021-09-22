using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading.Tasks;

namespace PlatformEditor
{

    struct TileData
    {
        public bool myIsObstacle;
        public bool myIsDestructable;
    }
    public class Tileset
    {
        public List<int>[] myAutoTiles = null;
        private int myTileHeight = 32;
        private int myTileWidth = 32;
        private Image myImage = null;
        private Random myRandomTile = new Random();

        public Tileset()
        {
            myAutoTiles = new List<int>[16];
            for (int i = 0; i < 16; i++)
                myAutoTiles[i] = new List<int>();
        }

        public bool IsAutoTile(int aIndex)
        {
            for (int tileTypeIndex = 0; tileTypeIndex < 16; tileTypeIndex++)
            {
                for (int autoTileIndex = 0; autoTileIndex < myAutoTiles[tileTypeIndex].Count; autoTileIndex++)
                {
                    if (myAutoTiles[tileTypeIndex][autoTileIndex] == aIndex)
                        return true;
                }
            }
            return false;
        }

        public int GetAutoTile(int aAutoTileValue)
        {         
            int possibleTiles = myAutoTiles[aAutoTileValue].Count;
            if (possibleTiles == 0)
            {
                return -1;
            }
            int pick = myAutoTiles[aAutoTileValue][myRandomTile.Next(0, possibleTiles)];
            return pick;
        }
        
        public Image GetImage()
        {
            return myImage;
        }

        public int TileWidth
        {
            get
            {
                  return myTileWidth;
            }
            set
            {
                myTileWidth = value;
                UpdateTileCount();
            }
        }
        public int TileHeight
        {
            get
            {
                return myTileHeight;
            }
            set
            {
                myTileHeight = value;
                UpdateTileCount();
            }
        }

        private string myTileImage;
        public string TileImage
        {
            set
            {
                myTileImage = value;
                if (myTileImage != null && myTileImage != "")
                {
                    myImage = Image.FromFile(Settings.GetDataPath() + "\\data\\gfx\\tilesets\\" + myTileImage);
                    UpdateTileCount();
                }
            }
            get
            {
                return myTileImage;
            }
        }
        public string myTilesetName;

        TileData[] myTileData;
        public int GetTileRows()
        {
            if (myImage != null)
            {
                return myImage.Height / myTileHeight;
            }
            else
            {
                return 0;
            }
        }

        public int GetTileCols()
        {
            if (myImage != null)
            {
                return myImage.Width / myTileWidth;
            }
            else
            {
                return 0;
            }
        }

        private void UpdateTileCount()
        {
            if (myTileData == null || GetTileRows() * GetTileCols() != myTileData.Length)
            {
                myTileData = new TileData[GetTileRows() * GetTileCols()];
            }
        }

        public void SetIsObstacle(int aTileID, bool aIsObstacle)
        {
            if (myTileData != null && aTileID < myTileData.Length)
            {
                myTileData[aTileID].myIsObstacle = aIsObstacle;
            }
        }
        public void SetIsDestructable(int aTileID, bool aIsDestructable)
        {
            if (myTileData != null && aTileID < myTileData.Length)
            {
                myTileData[aTileID].myIsDestructable = aIsDestructable;
            }
        }
        public bool GetIsObstacle(int aTileID)
        {
            return myTileData[aTileID].myIsObstacle;
        }

        public bool GetIsDestructable(int aTileID)
        {
            return myTileData[aTileID].myIsDestructable;
        }

        public void SaveTo(System.IO.BinaryWriter aBinaryWriter)
        {
            aBinaryWriter.Write(myTilesetName);
            aBinaryWriter.Write(myTileImage);
            aBinaryWriter.Write(myTileWidth);
            aBinaryWriter.Write(myTileHeight);
            aBinaryWriter.Write(myTileData.Length);
            foreach (TileData tileData in myTileData)
            {
                aBinaryWriter.Write(tileData.myIsObstacle);
                aBinaryWriter.Write(tileData.myIsDestructable);
            }

            // Save autotiles
            for (int autoTileType = 0; autoTileType < 16; autoTileType++)
            {
                aBinaryWriter.Write(myAutoTiles[autoTileType].Count);
                for (int tileOption = 0; tileOption < myAutoTiles[autoTileType].Count; tileOption++)
                {
                    aBinaryWriter.Write(myAutoTiles[autoTileType][tileOption]);
                }
            }
        }

        public void LoadFrom(System.IO.BinaryReader aBinaryReader)
        {
            myTilesetName = aBinaryReader.ReadString();
            TileImage = aBinaryReader.ReadString();

            myTileWidth = aBinaryReader.ReadInt32();
            myTileHeight = aBinaryReader.ReadInt32();
            int tileCount = aBinaryReader.ReadInt32();
            myTileData = new TileData[tileCount];
            
            for (int tileIndex = 0; tileIndex < tileCount; tileIndex++)
            {
                myTileData[tileIndex].myIsObstacle = aBinaryReader.ReadBoolean();
                myTileData[tileIndex].myIsDestructable = aBinaryReader.ReadBoolean();
            }

            // Load autotiles
            myAutoTiles = new List<int>[16];
            for (int autoTileType = 0; autoTileType < 16; autoTileType++)
            {
                int numberOfTiles = aBinaryReader.ReadInt32();
                myAutoTiles[autoTileType] = new List<int>();
                for (int tileOption = 0; tileOption < numberOfTiles; tileOption++)
                {
                    int tileID = aBinaryReader.ReadInt32();
                    myAutoTiles[autoTileType].Add(tileID);
                }
            }
        }
    }
}
