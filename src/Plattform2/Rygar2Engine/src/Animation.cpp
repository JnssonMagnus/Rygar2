#include "stdafx.h"
#include "Animation.h"
#include "Renderer.h"

AnimationSet::AnimationSet()
{
	myCurrentTime = 0.f;
}

void AnimationSet::Update(const float aDeltaTime)
{
	myCurrentTime += aDeltaTime;
	UpdateColorBlink(aDeltaTime);
}

void AnimationSet::Draw(const Vector2f& aPosition, const float aAngle, const bool aNoZoom)
{	
	const Animation& animation = myAnimations[myCurrentAnimationID];
	int currentFrame = (static_cast<int>(myCurrentTime / (1.f / animation.myFpsCount)) % animation.myFrameCount);
	if (animation.myLoop == false && myCurrentTime > ((1.f / animation.myFpsCount) * animation.myFrameCount))
		currentFrame = animation.myFrameCount - 1;
		
	myRenderCommand.myDstSize = myRenderCommand.mySrcSize = animation.myRectSize;
	myRenderCommand.mySrcPos = { animation.myStartPosition.myX + animation.myRectSize.myX * currentFrame, animation.myStartPosition.myY };	
	myRenderCommand.myDstPos = aPosition;	
	myRenderCommand.myAngle = aAngle;
	myRenderCommand.myColor = GetSpriteColor();
	myRenderCommand.myOptions = static_cast<unsigned char>(myFlipImage) * RenderCommand::eRenderOptions::eFlipped + 
		static_cast<unsigned char>(aNoZoom) * RenderCommand::eRenderOptions::eNoZoom;
	myRenderCommand.myTexture = myTexture;
	myRenderCommand.myPivot = myPivot;

	ourRenderer->AddRenderCommand(myRenderCommand);
}

void AnimationSet::AddAnimation(const eAnimationID aAnimationID, const int aFrameCount, const Vector2<int>& aRectSize, 
	const float aFPSCount, const Vector2<int> aStartPosition, const bool aLoopAnimation)
{
	assert(myAnimations.find(aAnimationID) == myAnimations.end() && "AnimationID already added!");
	Animation newAnimation;
	newAnimation.myFpsCount = aFPSCount;
	newAnimation.myFrameCount = aFrameCount;
	newAnimation.myStartPosition = aStartPosition;
	newAnimation.myRectSize = aRectSize;
	newAnimation.myLoop = aLoopAnimation;
	myAnimations[aAnimationID] = newAnimation;
}

void AnimationSet::PushAnimation(const eAnimationID aAnimationID)
{
	if (aAnimationID != myCurrentAnimationID)
	{
		DL_ASSERT(myAnimations.find(aAnimationID) != myAnimations.end() && "Animation not found!");
		myCurrentAnimationID = aAnimationID;
		myCurrentTime = 0.f;
	}
}

const Vector2<int>& AnimationSet::GetSize() const
{
	const auto it = myAnimations.find(myCurrentAnimationID);
	DL_ASSERT(it != myAnimations.end() && "Animation not found!");
	return it->second.myRectSize;
}

void AnimationSet::ColorBlink(const Color& aBlinkColor, const float aBlinkLength, const float aBlinkFrequency)
{
	SColorBlink newBlink;
	newBlink.myBlinkLength = aBlinkLength;
	newBlink.myBlinkColor = aBlinkColor;
	newBlink.myBlinkFrequency = aBlinkFrequency;
	myColorBlinks.push(newBlink);
}

void AnimationSet::UpdateColorBlink(const float aDeltaTime)
{
	if (myColorBlinks.empty()) {
		return;
	}

	SColorBlink& frontBlink = myColorBlinks.front();
	frontBlink.myBlinkLength -= aDeltaTime;

	const float timeLeft = frontBlink.myBlinkLength;

	if (timeLeft <= 0.f) {
		myColorBlinks.pop();
		if (!myColorBlinks.empty()) {
			myColorBlinks.front().myBlinkLength += timeLeft;
		}
	}
}

const Color& AnimationSet::GetSpriteColor() const
{
	static const Color defaultColor(255_uc, 255_uc, 255_uc);
	if (myColorBlinks.empty()) {
		return defaultColor;
	}

	const SColorBlink& frontBlink = myColorBlinks.front();

	if (!frontBlink.myBlinkFrequency) {
		return frontBlink.myBlinkColor;
	}

	return fmod(frontBlink.myBlinkLength, frontBlink.myBlinkFrequency * 2.f) >= frontBlink.myBlinkFrequency ? frontBlink.myBlinkColor : defaultColor;
}
