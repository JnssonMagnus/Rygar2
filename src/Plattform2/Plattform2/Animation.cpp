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
}

void AnimationSet::Draw(const Vector2f& aPosition, const float aAngle, const bool aNoZoom)
{	
	const Animation& animation = myAnimations[myCurrentAnimationID];
	int currentFrame = (static_cast<int>(myCurrentTime / (1.f / animation.myFpsCount)) % animation.myFrameCount);
	if (animation.myLoop == false && myCurrentTime > ((1.f / animation.myFpsCount) * animation.myFrameCount))
		currentFrame = animation.myFrameCount - 1;
		
	RenderCommand renderCommand;
	renderCommand.myDstSize = renderCommand.mySrcSize = animation.myRectSize;
	renderCommand.mySrcPos = { animation.myStartPosition.myX + animation.myRectSize.myX * currentFrame, animation.myStartPosition.myY };
	renderCommand.myTexture = myTexture;
	renderCommand.myDstPos = aPosition;
	renderCommand.myPivot = myPivot;
	renderCommand.myAngle = aAngle;
	renderCommand.myColor = { 255_uc, 255_uc, 255_uc };
	renderCommand.myOptions |= static_cast<unsigned char>(myFlipImage) * RenderCommand::eRenderOptions::eFlipped + 
		static_cast<unsigned char>(aNoZoom) * RenderCommand::eRenderOptions::eNoZoom;
	
	ourRenderer->AddRenderCommand(renderCommand);
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
