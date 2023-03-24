using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PlatformEditor
{
    public class Variable
    {
        public string name;
        public float value;
    }
    public class VariableType
    {
        public string name;
        public float defaultValue = 0.0f;

        public VariableType(string aName)
        {
            name = aName;
        }

        public bool Equals(VariableType other)
        {
            return other.name == name;
        }
    }
    public class Vector2
    {
        public Vector2(float aX, float aY)
        {
            x = aX;
            y = aY;
        }
        public float x;
        public float y;
    }

    public class PhysicBody
    {
        public Vector2 airFriction = new Vector2(1, 1);
        public Vector2 groundFriction = new Vector2(1, 1);
        public float bounciness = 0.8f;
        public float weight = 1.0f;
        public bool physicsEnabled = true;
        public bool gravity = true;
        public bool kinetic = false;
        public int collisionTags = 0;
    }

    public class GameObject
    {
        public MapData myChunk;
        public Vector2 myPosition = new Vector2(0, 0);
        public GameObjectType myGameObjectType = null;

        public bool IsInside(int aX, int aY)
        {
            int halfWidth = MapEditor.ourInstance.myGameObjectTypeImages[myGameObjectType.ID].Width / 2;
            int halfHeight = MapEditor.ourInstance.myGameObjectTypeImages[myGameObjectType.ID].Height / 2;
            return (aX > myPosition.x - halfWidth && aX < myPosition.x + halfWidth &&
                    aY > myPosition.y - halfHeight && aY < myPosition.y + halfHeight);
        }

        public List<Variable> variables = new List<Variable>();
    }
    public class GameObjectType
    {
        public string name = "unnamed object";
        public string image = "";
        public PhysicBody physicBody = new PhysicBody();
        public int ID = -1;
        public bool rotateObject = false;
        public List<VariableType> variables = new List<VariableType>();
    }
}
