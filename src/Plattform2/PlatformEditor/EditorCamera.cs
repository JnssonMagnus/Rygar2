using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PlatformEditor
{   class EditorCamera
    {
        private Vector2 myPosition = new Vector2(0.0f, 0.0f);
        private Vector2 mySize = new Vector2(640.0f, 480.0f);
        public Vector2 Position
        {
            get
            {
                return myPosition;
            }

            set
            {
                myPosition = value;
            }
        }
        public Vector2 Size
        {
            get
            {
                return mySize;
            }

            set
            {
                mySize = value;
            }
        }

    }
}
