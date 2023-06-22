using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;

namespace PlatformEditor
{

    public enum VariableTypes
    {
        None,
        i,
        d,
        s
    }
    public class Variable
    {
        public Variable(string aName)
        {
            name = aName;
        }

        public Variable()
        { }

        public string name;
        public double doubleValue
        { 
            get 
            {
                return mDoubleValue; 
            }
            set 
            {
                mDoubleValue = value;
                mType = VariableTypes.d;
            }
        }

        public string stringValue
        {
            get 
            {
                return mStringValue; 
            }
            set 
            {            
                mStringValue = value;
                mType = VariableTypes.s;
            }
        }

        public VariableTypes type
        {
            get { return mType; }
            set { mType = value; }
        }

        public void Save(System.IO.BinaryWriter binaryWriter)
        {
            binaryWriter.Write(name);
            binaryWriter.Write(mType.ToString());
            switch (type)
            {
                case VariableTypes.d:
                    binaryWriter.Write(doubleValue); break;
                case VariableTypes.s:
                    binaryWriter.Write(stringValue); break;
            }
        }

        public void Load(System.IO.BinaryReader binaryReader, int version)
        {
            name = binaryReader.ReadString();
            string typeStr = binaryReader.ReadString();
            Enum.TryParse(typeStr, out mType);
            switch (mType)
            {            
                case VariableTypes.d:
                    doubleValue = binaryReader.ReadDouble(); break;
                case VariableTypes.s:
                    stringValue = binaryReader.ReadString(); break;
            }
        }

        private VariableTypes mType = VariableTypes.None;
        private string mStringValue;
        private double mDoubleValue;        
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
        public List<Variable> myVariables = new List<Variable>();

        public string GetStringValue(string aKey)
        {
            foreach (Variable variable in myVariables)
            {
                if (variable.name == aKey)
                {
                    return variable.stringValue;
                }
            }

            return "error";
        }
        public double GetDoubleValue(string aKey)
        {
            foreach (Variable variable in myVariables)
            {
                if (variable.name == aKey)
                {
                    return variable.doubleValue;
                }
            }

            return 0.0;
        }
        public bool HasKeyValue(string aKey)
        {
            foreach (Variable variable in myVariables)
            {
                if (variable.name == aKey)
                {
                    return true;
                }
            }

            return false;
        }

            public bool InsertOrChangeVar(Variable aVariable)
        {
            for (int varIndex = 0; varIndex < myVariables.Count; varIndex++)
            {
                if (myVariables[varIndex].name == aVariable.name)
                {
                    if (myVariables[varIndex].type == aVariable.type)
                    {
                        myVariables[varIndex] = aVariable;
                        return true;
                    } 
                    else
                    {
                        return false;
                    }
                }
            }

            myVariables.Add(aVariable);

            return true;
        }

        public bool IsInside(int aX, int aY)
        {
            int halfWidth = MapEditor.ourInstance.myGameObjectTypeImages[myGameObjectType.ID].Width / 2;
            int halfHeight = MapEditor.ourInstance.myGameObjectTypeImages[myGameObjectType.ID].Height / 2;
            return (aX > myPosition.x - halfWidth && aX < myPosition.x + halfWidth &&
                    aY > myPosition.y - halfHeight && aY < myPosition.y + halfHeight);
        }
        public void Save(System.IO.BinaryWriter binaryWriter)
        {
            binaryWriter.Write(myGameObjectType.ID);
            binaryWriter.Write(myPosition.x);
            binaryWriter.Write(myPosition.y);
            binaryWriter.Write(myVariables.Count);
            foreach (Variable variable in myVariables)
            {
                variable.Save(binaryWriter);
            }
        }
        public void Load(System.IO.BinaryReader binaryReader, int version)
        {            
            myPosition.x = binaryReader.ReadSingle();
            myPosition.y = binaryReader.ReadSingle();

            if (version > 1)
            {
                int varibleCount = binaryReader.ReadInt32();
                for (int variableIndex = 0; variableIndex < varibleCount; variableIndex++)
                {
                    Variable newVar = new Variable();
                    newVar.Load(binaryReader, version);
                    myVariables.Add(newVar);
                }
            }
        }
    }
    public class GameObjectType
    {
        public string name = "unnamed object";
        public string image = "";
        public PhysicBody physicBody = new PhysicBody();
        public int ID = -1;
        public bool rotateObject = false;
        public List<Variable> variables = new List<Variable>();
    }
}
