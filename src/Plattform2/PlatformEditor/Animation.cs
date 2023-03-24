using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PlatformEditor
{
    public class Animation
    {
        public float FPS = 5;
        public int frames = 1;
        public float startX = 0;
        public float startY = 0;
    }
    public class AnimationSet
    {
        public string name;
        public string sprite;
        public int width = 16;
        public int height = 16;

        public Animation GetAnimation(string name)
        {
            if (myAnimations.ContainsKey(name) == false)
                myAnimations.Add(name, new Animation());

            Animation animation = myAnimations[name];
            return animation;
        }

        public Dictionary<string, Animation> myAnimations = new Dictionary<string, Animation>();
    }
}
