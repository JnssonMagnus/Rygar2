using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace PlatformEditor
{
    class World
    {        
        public Dictionary<int, MapData> mMapChunks = new Dictionary<int, MapData>();
        public void SetTile(int aTileX, int aTileY, char aSourceTileX, char aSourceTileY, Tileset tileset)
        {
            var mapChunk = GetMapChunkFromTileIndex(aTileX, aTileY);            

            if (mapChunk.Tileset == null)
            {
                mapChunk.Tileset = tileset;
            }

            mapChunk.SetTile(aTileX, aTileY, aSourceTileX, aSourceTileY);
        }

        public GameObject PlaceObject(Vector2 aPosition, GameObjectType aGameObjectType)
        {
            var mapChunk = GetMapChunk((int)aPosition.x, (int)aPosition.y);
            return mapChunk.PlaceObject(aPosition, aGameObjectType);
        }

        public List<GameObject> GetGameObjectsFromChunk(int aWorldPositionX, int aWorldPositionY)
        {
            var chunk = GetMapChunk(aWorldPositionX, aWorldPositionY);
            if (chunk == null)
            {
                return new List<GameObject>();
            }
            return chunk.GetGameObjects();
        }

        public void SaveAll()
        {
            foreach (var mapData in mMapChunks)
            {
                mapData.Value.Save();
            }
        }

        public void LoadAll(Dictionary<string, Tileset> tilesets)
        {
            string filePath = Settings.GetDataPath() + "data/levels/";
            var files = Directory.GetFiles(filePath);
            foreach (string file in files)
            {
                int chunkId = GetChunkIdFromString(file);
                MapData newChunk = new MapData();
                newChunk.Init(chunkId);
                newChunk.LoadFromFile(file);
                mMapChunks[chunkId] = newChunk;
                newChunk.Tileset = tilesets[newChunk.myTilesetName];
            }
        }

        private int GetChunkIdFromString(string chunkFilePath)
        {
            int index = chunkFilePath.LastIndexOf('_');
            string chunkIdStr = chunkFilePath.Remove(0, index + 1);
            int chunkId = int.Parse(chunkIdStr);
            return chunkId;
        }

        public MapData GetMapChunk(int aWorldX, int aWorldY)
        {
            int chunkId = GetChunkIdFromWorldPosition(aWorldX, aWorldY);
            if (mMapChunks.ContainsKey(chunkId) == false)
            {
                mMapChunks[chunkId] = new MapData();
                mMapChunks[chunkId].Init(chunkId);
            }

            return mMapChunks[chunkId];
        }

        public MapData GetMapChunkFromTileIndex(int aWorldTileIndexX, int aWorldTileIndexY)
        {
            var chunk = GetMapChunk(aWorldTileIndexX * Settings.TileWidth(), aWorldTileIndexY * Settings.TileHeight());
            return chunk;
        }

        private int GetChunkIdFromWorldPosition(int aX, int aY)
        {
            int HIGH_ID = 10000000;
            int highId = ((aX / Settings.TileWidth()) / Settings.MapWidth()) * HIGH_ID;
            int lowId = (aY / Settings.TileHeight()) / Settings.MapHeight();
            return lowId + highId;
        }

        public List<GameObject> GetGameObjectsFromFrustum(EditorCamera camera)
        {
            List<GameObject> visibleObjects = new List<GameObject>();
            var visibleMapChunks = GetChunksInFrustum(camera);
            foreach (var chunk in visibleMapChunks)
            {
                var gameObjectsInChunk = chunk.GetGameObjects();
                visibleObjects.AddRange(gameObjectsInChunk);
            }                

            return visibleObjects;
        }

        public List<MapData> GetChunksInFrustum(EditorCamera camera)
        {
            List<MapData> visibleChunks = new List<MapData>();
            foreach (var chunk in mMapChunks)
            {
                visibleChunks.Add(chunk.Value);
            }
            //for (int x = (int)camera.Position.x; x < (int)(camera.Position.x + camera.Size.x); x += (int)camera.Size.x)
            //{
            //    for (int y = (int)camera.Position.y; y < (int)(camera.Position.y + camera.Size.y); y += (int)camera.Size.y)
            //    {
            //        var mapChunk = GetMapChunk(x, y);
            //        if (mapChunk != null)
            //        {
            //            visibleChunks.Add(mapChunk);
            //        }
            //    }
            //}

            return visibleChunks;
        }
    }
}
