using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PlatformEditor
{
    static class Settings
    {
        public static string GetDataPath()
        {
            return "C:/Users/Magnus.jonsson/Dropbox/C++/RygarRemake/";
        }

        public static int TileWidth()
        {
            return 16;
        }
        public static int TileHeight()
        {
            return 16;
        }

        public static int MapWidth()
        {
            return 25;
        }

        public static int MapHeight()
        {
            return 25;
        }
    }
}
