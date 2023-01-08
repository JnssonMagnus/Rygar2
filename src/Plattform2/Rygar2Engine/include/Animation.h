#pragma once
#include "Sprite.h"
#include "RenderCommands.h"
#include <unordered_map>
#include <queue>

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
	void					ColorBlink(const Color& aBlinkColor, const float aBlinkLength, const float aBlinkFrequency);
	void					ClearColorBlinks();

private:
	void					UpdateColorBlink(const float aDeltaTime);
	const Color&			GetSpriteColor() const;

	struct Animation
	{
		Vector2<int> myStartPosition;
		Vector2<int> myRectSize;
		float myFpsCount;
		int myFrameCount;
		bool myLoop = true;
	};

	struct SColorBlink {
		float myBlinkLength = 0;
		float myBlinkFrequency = 0;
		Color myBlinkColor;

		Color GetColor() const {
			return myBlinkColor;

		}
	};

	std::queue<SColorBlink>						myColorBlinks;

	RenderCommand								myRenderCommand;
	std::unordered_map<eAnimationID, Animation> myAnimations;
	float										myCurrentTime = 0;
	eAnimationID								myCurrentAnimationID = eAnimationID::eDefault;					
	bool										myFlipImage = false;
};

inline void AnimationSet::FlipImage(const bool aFlag)
{
	myFlipImage = aFlag;
}

