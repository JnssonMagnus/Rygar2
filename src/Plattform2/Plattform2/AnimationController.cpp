#include "stdafx.h"
#include "AnimationController.h"
#include "PhysicBody.h"
#include "Animation.h"
#include "Actor.h"

AnimationController::AnimationController(const Actor& aParent, AnimationSet& aAnimationSet)
{
	DL_ASSERT(myParentAnimationSet == nullptr && "Character animationController already set up!");
	myParent = &aParent;
	myParentAnimationSet = &aAnimationSet;
}

void AnimationController::Update()
{
	assert(myParent != nullptr && "AnimationController not initiated!");
	if (myParent->GetProperty<int>(PropertyKey::eLife) <= 0)
	{
		myParentAnimationSet->PushAnimation(eAnimationID::eDead);
	}
	else if (myParent->GetPhysicBody().IsEnabled())
	{
		myParentAnimationSet->FlipImage(!myParent->GetProperty<bool>(PropertyKey::eFacingRight));
		if (myParent->GetPhysicBody().GetOption(ePhysicBodyOptions::eGravity) == true)
		{
			if (IsOnGround() == false)
			{
				if (myParent->GetProperty<bool>(PropertyKey::eIsAttacking) == true)
				{
					myParentAnimationSet->PushAnimation(eAnimationID::eJumpAttack);
				}
				else if (myParent->GetPhysicBody().GetVelocity().myY < 0.f)
				{
					myParentAnimationSet->PushAnimation(eAnimationID::eJump);
				}
				else
				{
					myParentAnimationSet->PushAnimation(eAnimationID::eFall);
				}
			}
			else
			{
				if (myParent->GetProperty<bool>(PropertyKey::eIsAttacking) == true)
				{
					myParentAnimationSet->PushAnimation(eAnimationID::eAttack);
				}
				else if (abs(myParent->GetPhysicBody().GetVelocity().myX) < 0.3f)
				{
					myParentAnimationSet->PushAnimation(eAnimationID::eIdle);
				}
				else
				{
					myParentAnimationSet->PushAnimation(eAnimationID::eWalk);
				}
			}
		}
	}
}

bool AnimationController::IsOnGround() const
{
	return myParent->GetPhysicBody().HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eBottom);
}
