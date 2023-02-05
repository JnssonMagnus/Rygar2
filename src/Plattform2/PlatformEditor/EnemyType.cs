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
    }
}
