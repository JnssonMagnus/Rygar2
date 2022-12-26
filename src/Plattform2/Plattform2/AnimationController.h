#pragma once

class GameObject;
class AnimationSet;

class AnimationController
{
public:
	virtual					~AnimationController() = default;
							AnimationController(const GameObject& aParent, AnimationSet& aAnimationSet);
	virtual void			Update();

protected:
	const GameObject*		myParent = nullptr;
	AnimationSet*			myParentAnimationSet = nullptr;

	bool					IsOnGround() const;
};

