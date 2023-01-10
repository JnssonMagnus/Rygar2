#pragma once

class Actor;
class AnimationSet;

class AnimationController
{
public:
	virtual					~AnimationController() = default;
							AnimationController(const Actor& aParent, AnimationSet& aAnimationSet);
	virtual void			Update();

protected:
	const Actor*			myParent = nullptr;
	AnimationSet*			myParentAnimationSet = nullptr;

	bool					IsOnGround() const;
};

