#pragma once

class GameObject;
class AnimationSet;

class AnimationController
{
public:
	void					Init(const GameObject& aParent, AnimationSet& aAnimationSet);
	void					Update();

private:
	const GameObject*		myParent = nullptr;
	AnimationSet*			myParentAnimationSet = nullptr;
};

