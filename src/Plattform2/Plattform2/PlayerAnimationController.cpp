#include "stdafx.h"
#include "PlayerAnimationController.h"
#include "GameObject.h"
#include "Animation.h"
#include "PhysicBody.h"

void PlayerAnimationController::Update()
{
	assert(myParent != nullptr && "AnimationController not initiated!");
	if (myParent->GetProperty<int>(PropertyKey::eLife) <= 0)
	{
		myParentAnimationSet->PushAnimation(eAnimationID::eDead);
	}
	else if (myParent->GetPhysicBody().IsEnabled())
	{
		myParentAnimationSet->FlipImage(!myParent->GetProperty<bool>(PropertyKey::eFacingRight));
		if (IsOnGround() == false)
		{
			ChoseInAirAnimation();
		}
		else
		{
			ChoseOnGroundAnimation();
		}
	}
}

void PlayerAnimationController::ChoseInAirAnimation()
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

void PlayerAnimationController::ChoseOnGroundAnimation()
{
	if (myParent->GetProperty<bool>(PropertyKey::eIsAttacking) == true)
	{
		if (myParent->GetProperty<bool>(PropertyKey::eDucking) == false)
			myParentAnimationSet->PushAnimation(eAnimationID::eAttack);
		else
			myParentAnimationSet->PushAnimation(eAnimationID::eDuckAttack);
	}
	else if (abs(myParent->GetPhysicBody().GetVelocity().myX) < 1.f)
	{
		if (myParent->GetProperty<bool>(PropertyKey::eDucking) == false)
			myParentAnimationSet->PushAnimation(eAnimationID::eIdle);
		else
			myParentAnimationSet->PushAnimation(eAnimationID::eDuckIdle);
	}
	else
	{
		myParentAnimationSet->PushAnimation(eAnimationID::eWalk);
	}

}
