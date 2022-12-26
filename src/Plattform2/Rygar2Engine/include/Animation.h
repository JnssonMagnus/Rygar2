#pragma once
#include "Sprite.h"
#include <unordered_map>

enum class eAnimationID
{
	eDefault,
	eIdle,
	eWalk,
	eJump,
	eAttack,
	eDuckAttack,
	eJumpAttack,
	eFall,
	eStagger,
	eDead,
	eDuckIdle,
	eThrowHook
};

class AnimationSet : public Sprite
{
public:
							AnimationSet();
	void					Update(const float aDeltaTime);
	void					Draw(const Vector2f& aPosition, const float aAngle = 0.f, const bool aNoZoom = false) override;
	void					AddAnimation(const eAnimationID aAnimationID, const int aFrameCount, const Vector2<int>& aRectSize, 
								const float aFPSCount = 15, const Vector2<int> aStartPosition = { 0, 0 }, const bool aLoopAnimation = true);
	void					PushAnimation(const eAnimationID aAnimationID);
	void					FlipImage(const bool aFlag);
	const Vector2<int>&		GetSize() const;

private:

	struct Animation
	{
		Vector2<int> myStartPosition;
		Vector2<int> myRectSize;
		float myFpsCount;
		int myFrameCount;
		bool myLoop = true;
	};


	float			myCurrentTime;
	eAnimationID	myCurrentAnimationID = eAnimationID::eDefault;
	std::unordered_map<eAnimationID, Animation>
					myAnimations;
	bool			myFlipImage = false;
};

inline void AnimationSet::FlipImage(const bool aFlag)
{
	myFlipImage = aFlag;
}

