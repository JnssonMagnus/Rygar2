#include "stdafx.h"
#include "PhysicBody.h"

PhysicBody::PhysicBody()
{
	myOptions = 0_uc;
	myGameObject = nullptr;
	myAirFriction.myX = myAirFriction.myY = 1.f;
	myGroundFriction.myX = myGroundFriction.myY = 1.f;
	myPosition.myX = myPosition.myY = 0.f;
	myOldPosition.myX = myOldPosition.myY = 0.f;
	myForce.myX = myForce.myY = 0.f;
	myVelocity.myX = myVelocity.myY = 0.f;
	myHalfSize.myX = myHalfSize.myY = 0.f;
	myPhysicStates = { 0, 0, 0, 0 };
	myBounciness = 0.f;
	SetOption(ePhysicBodyOptions::eEnable, true);
	SetOption(ePhysicBodyOptions::eGravity, true);

	Message addedMessage(eMessageTypes::ePhysicBodyAdded);
	addedMessage.myVoidPointer = this;
	PostMaster::GetInstance()->SendMessage(addedMessage);
}

PhysicBody::PhysicBody(const PhysicBody& aPhysicBody)
{
	SetOption(ePhysicBodyOptions::eEnable, false);
	*this = aPhysicBody;
}

PhysicBody::~PhysicBody()
{
}

PhysicBody& PhysicBody::operator=(const PhysicBody& aPhysicBody)
{
	SetOption(ePhysicBodyOptions::eEnable, aPhysicBody.GetOption(ePhysicBodyOptions::eEnable));
	memcpy(this, &aPhysicBody, sizeof(PhysicBody));
	return *this;
}

void PhysicBody::Update()
{
	myOldPosition = myPosition;
	
	myForce.myY += static_cast<int>(GetOption(ePhysicBodyOptions::eGravity)) * GRAVITY;

	myVelocity += myForce;

	if (HasPhysicState(ePhysicStates::eOnGround, eLocator::eBottom) == true)
	{
		myVelocity *= myGroundFriction;
	}
	else
	{
		myVelocity *= myAirFriction;
	}

	ResetPhysicState();
	// max physic threshold at the moment
	if (myVelocity.myX > 17.f)
		myVelocity.myX = 17.f;
	else if (myVelocity.myX < -17.f)
		myVelocity.myX = -17.f;
	if (myVelocity.myY > 17.f)
		myVelocity.myY = 17.f;
	else if (myVelocity.myY < -17.f)
		myVelocity.myY = -17.f;

	myPosition += myVelocity;
	myForce.myX = myForce.myY = 0.f;	
}

bool PhysicBody::Collides(const PhysicBody& aPhysicBody) const
{
	if (myPosition.myX - myHalfSize.myX > aPhysicBody.myPosition.myX + aPhysicBody.myHalfSize.myX ||
		myPosition.myX + myHalfSize.myX < aPhysicBody.myPosition.myX - aPhysicBody.myHalfSize.myX ||
		myPosition.myY - myHalfSize.myY > aPhysicBody.myPosition.myY + aPhysicBody.myHalfSize.myY ||
		myPosition.myY + myHalfSize.myY < aPhysicBody.myPosition.myY - aPhysicBody.myHalfSize.myY)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool PhysicBody::Collides(const Vector2f& aPoint) const
{
	return !(aPoint.myX < myPosition.myX - myHalfSize.myX ||
			aPoint.myY < myPosition.myY - myHalfSize.myY ||
			aPoint.myX > myPosition.myX + myHalfSize.myX ||
			aPoint.myY > myPosition.myY + myHalfSize.myY);

}

void PhysicBody::SetFriction(const Vector2f& aAirFriction, const Vector2f& aGroundFriction)
{
	myAirFriction = aAirFriction;
	myGroundFriction = aGroundFriction;
}

void PhysicBody::SetPosition(const Vector2f& aPosition)
{
	myPosition = aPosition;
}

void PhysicBody::SetForce(const Vector2f& aForce)
{
	myForce = aForce;
}

void PhysicBody::SetVelocity(const Vector2f& aVelocity)
{
	myVelocity = aVelocity;
}

void PhysicBody::SetHalfSize(const Vector2f& aHalfSize)
{
	myHalfSize = aHalfSize;
}

void PhysicBody::SetBounciness(const float aBounciness)
{
	myBounciness = aBounciness;
	myBounciness = RANGE(myBounciness, 0.f, 1.f);
}

void PhysicBody::SetMass(const float aWeight)
{
	myMass = aWeight;
}

void PhysicBody::SetCollisionTags(const char someCollisionTags)
{
	myTags = someCollisionTags;
}

void PhysicBody::SetRotation(const bool aRotateWithSpeed)
{
	SetOption(ePhysicBodyOptions::eRotateObject, aRotateWithSpeed);
}

void PhysicBody::Release()
{
	Message releaseMessage(eMessageTypes::ePhysicBodyRemoved);
	releaseMessage.myVoidPointer = this;
	PostMaster::GetInstance()->SendMessage(releaseMessage);
}

void PhysicBody::AddForce(const Vector2f& aForce)
{
	myForce += aForce / myMass;
}

bool PhysicBody::HasCollisionTag(const eCollisionTags aCollisionTag) const
{
	return (myTags & static_cast<char>(aCollisionTag));
}

void PhysicBody::AddPhysicState(const ePhysicStates aPhysicState, const eLocator aLocator)
{
	DL_ASSERT(static_cast<int>(aPhysicState) < 8 && "To many physic states, time to upgrade to an int :)");
	myPhysicStates[static_cast<int>(aLocator)] |= static_cast<short>(aPhysicState);
}

bool PhysicBody::HasPhysicState(const ePhysicStates aPhysicState, const eLocator aLocator) const
{
	return (myPhysicStates[static_cast<int>(aLocator)] & static_cast<short>(aPhysicState));
}

void PhysicBody::ResetPhysicState()
{
	myPhysicStates[0] = 0;
	myPhysicStates[1] = 0;
	myPhysicStates[2] = 0;
	myPhysicStates[3] = 0;
}

void PhysicBody::SetOption(const ePhysicBodyOptions aOption, const bool aValue)
{
	myOptions ^= (-static_cast<int>(aValue) ^ myOptions) & (static_cast<int>(aOption));
}

bool PhysicBody::GetOption(const ePhysicBodyOptions aOption) const
{
	return (myOptions & static_cast<char>(aOption)) > 0;
}

void PhysicBody::SetEnabled(const bool aFlag)
{
	if (GetOption(ePhysicBodyOptions::eEnable) != aFlag)
	{
		Message message;
		message.myVoidPointer = this;
		if (aFlag == true)
		{
			message.myMessageType = eMessageTypes::ePhysicBodyAdded;
			PostMaster::GetInstance()->SendMessage(message);
		}
		else
		{
			message.myMessageType = eMessageTypes::ePhysicBodyDisabled;
			PostMaster::GetInstance()->SendMessage(message);
		}
	}
	SetOption(ePhysicBodyOptions::eEnable, aFlag);	
}

void PhysicBody::SetGravity(const bool aIsEnabled)
{
	SetOption(ePhysicBodyOptions::eGravity, aIsEnabled);
}

void PhysicBody::SetIsKinetic(const bool aIsKinetic)
{
	SetOption(ePhysicBodyOptions::eKinetic, aIsKinetic);
}
