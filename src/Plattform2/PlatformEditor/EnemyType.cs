using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace PlatformEditor
{
    public class EnemyType : GameObjectType
    {
        public int exp;
        public int life;
        public int touchDamage;
        public float staggeredTime;
        public AnimationSet animationSet = new AnimationSet();
    }
    public class Enemy
    {
        public MapData myChunk;
        public Vector2 myPosition = new Vector2(0, 0);
        public EnemyType myEnemyType = null;

        public bool IsInside(int aX, int aY)
        {
            int halfWidth = MapEditor.ourInstance.myEnemyTypeImages[myEnemyType.ID].Width / 2;
            int halfHeight = MapEditor.ourInstance.myEnemyTypeImages[myEnemyType.ID].Height / 2;
            return (aX > myPosition.x - halfWidth && aX < myPosition.x + halfWidth &&
                    aY > myPosition.y - halfHeight && aY < myPosition.y + halfHeight);
        }

        public List<Variable> variables = new List<Variable>();
    }
}
