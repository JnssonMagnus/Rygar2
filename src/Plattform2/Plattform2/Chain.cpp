#include "stdafx.h"
#include "Chain.h"
#include "Megaton.h"
#include "MapChunk.h"
#include "GameObject.h"

Chain::Chain()
{
	myState = eState::eUnreleased;
	myParentPosition = { 0.f, 0.f };
	myHookInitSpeed = 20.f;
	myHookAcc = 0.0f;
	myHookSpeed = 0.f;
	myHookExtendFreq = 10.f;
	myHookExtendTime = 5.f;
}

void Chain::Init(const std::string_view aLinkSprite, const std::string_view aFireProjectileSprite, const float aMaxLength, 
	const float aInitSpeed, const int aReturnSpeed, GameObject* aEndObject, const bool aStickToGround)
{
	myHookSprite.Init(aFireProjectileSprite.data());
	myHookSprite.CenterPivot();
	myLinkSprite.Init(aLinkSprite.data());
	myLinkSprite.CenterPivot();
	myLinkSize = myLinkSprite.GetSize().myX;
	myEndObject = aEndObject;
	myHookInitSpeed = aInitSpeed;
	myHookMaxLength = aMaxLength;
	myReturnSpeed = aReturnSpeed;
	myStickToGround = aStickToGround;
}

void Chain::Fire(const Vector2f& aDirection)
{
	switch (myState)
	{
	case eState::eFired:
	case eState::eStuck:
		//myState = eState::eUnreleased;
		//myLinks.Clear();
		myHookSpeed = 0.f;
		myState = eState::eReturning;
		PostMaster::GetInstance()->SendSoundEvent("chainReverse");
		break;
	case eState::eUnreleased:
		myHookSpeed = myHookInitSpeed;
		myFireDirection = aDirection;
		myFireDirection.Normalize();
		myLinks.Add({ myParentPosition, { 0.f, 0.f }, atan2(myFireDirection.myY, myFireDirection.myX) });
		PostMaster::GetInstance()->SendSoundEvent("chainFire");
		myState = eState::eFired;
		if (myEndObject)
			myEndObject->SetPosition(myLinks[0].myPosition);
		break;
	}
}

void Chain::Draw()
{
	if (myState != eState::eUnreleased)
	{
		if (myEndObject)
			myEndObject->Draw();
		else
			myHookSprite.Draw(myLinks[0].myPosition, myLinks[0].myRotation);

		for (int linkIndex = 1; linkIndex < myLinks.Size(); linkIndex++)
		{
			myLinkSprite.Draw(myLinks[linkIndex].myPosition, myLinks[linkIndex].myRotation);
		}
	}
}

Vector2f Chain::Update(const float aDeltaTime, const Vector2f& aParentPosition, const Vector2f& aParentVelocity)
{
	myHookExtendTime += aDeltaTime;
	myParentPosition = aParentPosition;

	if (myState == eState::eFired)
	{
		if (HasReachedMaxLength())
		{			
			myState = eState::eReturning;			
		}
		else
		{
			myHookSpeed -= myHookAcc;
			Vector2f hitWallPosition;
			bool hitWall = FirstLinkHitWall(hitWallPosition);

			if (hitWall == false)
			{
				const float targetDistanceToParent = aParentPosition.DistanceTo(myLinks[0].myPosition += myFireDirection * myHookSpeed);
				if (targetDistanceToParent < myHookMaxLength)
					myLinks[0].myPosition += myFireDirection * myHookSpeed;
			}

			while (myLinks.GetLast().myPosition.SqrdDistanceTo(aParentPosition) > myLinkSize * myLinkSize)
			{
				Vector2f dir = myParentPosition - myLinks.GetLast().myPosition;
				dir.Normalize();
				Vector2f newPosition = myLinks.GetLast().myPosition + dir * static_cast<float>(myLinkSize);
				myLinks.Add({ newPosition, { 0.f, 0.f }, atan2(dir.y, dir.x) });
			}

			if (hitWall)
			{
				myLinks[0].myPosition = hitWallPosition;
				if (myStickToGround)
				{
					PostMaster::GetInstance()->SendSoundEvent("chainHit", myLinks[0].myPosition);
					myState = eState::eStuck;
				}
				else
				{
					PostMaster::GetInstance()->SendSoundEvent("chainHit", myLinks[0].myPosition);
					myState = eState::eReturning;
				}
			}
		}
	}
	else
	{
		constexpr float linkGravity = 0.35f;
		for (int linkIndex = 1; linkIndex < myLinks.Size(); linkIndex++)
		{
			myLinks[linkIndex].myVelocity.myY += linkGravity;
			myLinks[linkIndex].myPosition += myLinks[linkIndex].myVelocity;
		}
	}

	if (myState == eState::eStuck || myState == eState::eReturning)
	{
		myLinks.GetLast().myPosition = aParentPosition;

		int firstIndex = myState == eState::eReturning ? 0 : 1;

		for (int linkIndex = myLinks.Size() - 2; linkIndex >= firstIndex; linkIndex--)
		{
			Vector2f dir = myLinks[linkIndex + 1].myPosition - myLinks[linkIndex].myPosition;
			float force = (dir.Length() - myLinkSize) / myLinkSize;
			dir.Normalize();
			if (linkIndex == myLinks.Size() - 1)
				myLinks[linkIndex].myVelocity += aParentVelocity * 10.f;
			myLinks[linkIndex].myVelocity += dir * force;

			dir.Normalize();
			myLinks[linkIndex].myPosition = myLinks[linkIndex + 1].myPosition - dir * static_cast<float>(myLinkSize);
			myLinks[linkIndex].myRotation = atan2(dir.y, dir.x);
		}
	}

	if (myState == eState::eReturning)
	{
		for (int returnedLinks = 0; returnedLinks < myReturnSpeed; returnedLinks++)
		{
			if (myLinks.Size() > 0)
			{
				myLinks.RemoveCyclicAtIndex(myLinks.Size() - 1);
				if (myLinks.Size() == 0)
				{
					myState = eState::eUnreleased;
					PostMaster::GetInstance()->SendSoundEvent("stopChainReverse");
				}
			}
		}
	}
	else
	{
		for (int linkIndex = 1; linkIndex < myLinks.Size(); linkIndex++)
		{
			Vector2f dir = myLinks[linkIndex - 1].myPosition - myLinks[linkIndex].myPosition;
			float force = (dir.Length() - myLinkSize) / myLinkSize;
			dir.Normalize();
			myLinks[linkIndex].myVelocity += dir * force;
			myLinks[linkIndex].myPosition = myLinks[linkIndex - 1].myPosition - dir * static_cast<float>(myLinkSize);
			myLinks[linkIndex].myRotation = atan2(dir.y, dir.x);

			//if (myMap->Collided(myLinks[linkIndex].myPosition) == true)
			//{
			//	int tileX = static_cast<int>(myLinks[linkIndex].myPosition.myX / myMap->GetTileSize().myX);
			//	myLinks[linkIndex].myPosition.myX = tileX * myMap->GetTileSize().myX + myMap->GetTileSize().myX;

			//	for (int linkIndex2 = linkIndex-1; linkIndex2 > 0; linkIndex2--)
			//	{
			//		if (myMap->Collided(myLinks[linkIndex2].myPosition) == true)

			//		Vector2f dir = myLinks[linkIndex2 + 1].myPosition - myLinks[linkIndex2].myPosition;
			//		dir.Normalize();
			//		myLinks[linkIndex2].myPosition = myLinks[linkIndex2 + 1].myPosition - dir * myLinkSize;
			//		myLinks[linkIndex2].myRotation = atan2(dir.y, dir.x);
			//	}
			//}

		}
	}


	// Code for stuck and wrapping around tiles - messy and buggy
	//if (myState == eState::eStuck)
	//{
	//	myLinks.GetLast().myPosition = aParentPosition;

	//	for (int linkIndex = myLinks.Size() - 2; linkIndex > 0; linkIndex--)
	//	{
	//		if (myMap->Collided(myLinks[linkIndex].myPosition) == true)
	//			break;
	//		Vector2f dir = myLinks[linkIndex + 1].myPosition - myLinks[linkIndex].myPosition;
	//		dir.Normalize();
	//		myLinks[linkIndex].myPosition = myLinks[linkIndex + 1].myPosition - dir * myLinkSize;
	//		myLinks[linkIndex].myRotation = atan2(dir.y, dir.x);
	//	}
	//}
	// collisions vs map
	//for (int linkIndex = myLinks.Size() - 2; linkIndex > 0; linkIndex--)
	//{
	//	if (myMap->Collided(myLinks[linkIndex].myPosition) == true)
	//	{
	//		int tileX = static_cast<int>(myLinks[linkIndex].myPosition.myX / myMap->GetTileSize().myX);
	//		myLinks[linkIndex].myPosition.myX = tileX * myMap->GetTileSize().myX + myMap->GetTileSize().myX;

	//		for (int updateLinks = linkIndex; updateLinks < myLinks.Size(); updateLinks++)
	//		{
	//			Vector2f dir = myLinks[updateLinks - 1].myPosition - myLinks[updateLinks].myPosition;
	//			dir.Normalize();
	//			myLinks[updateLinks].myPosition = myLinks[updateLinks - 1].myPosition - dir * myLinkSize;
	//			myLinks[updateLinks].myRotation = atan2(dir.y, dir.x);
	//		}

	//	}
	//}

	if (myEndObject && myState != eState::eUnreleased)
	{		
		myEndObject->GetPhysicBody().SetVelocity(myLinks[0].myPosition - myEndObject->GetPhysicBody().GetPosition());				
		//myEndObject->GetPhysicBody().SetPosition(myLinks[0].myPosition);
	}


	if (myState == eState::eStuck)// &&  aParentPosition.DistanceTo(myLinks[0].myPosition) > (myLinkSize * (myLinks.Size()-1)))
	{
		return myLinks.GetLast().myPosition;			
	}

	return aParentPosition;
}

void Chain::Extend()
{
	if (myState == eState::eStuck && myHookExtendTime >= myHookExtendFreq)
	{
		myLinks.Add({ myParentPosition, Vector2f(0.f, 0.f), 0.f });
		myHookExtendTime = 0.f;
	}
}

void Chain::Shorten()
{
	if (myState == eState::eStuck && myLinks.Size() > 2 && myHookExtendTime >= myHookExtendFreq - myHookSpeed)
	{
		myHookSpeed += 0.04f;
		myLinks.RemoveCyclicAtIndex(myLinks.Size() - 1);
		myHookExtendTime = 0.f;
	}
}

Chain::eState Chain::GetState() const
{
	return myState;
}

bool Chain::FirstLinkHitWall(Vector2f& finalPosition) const
{
	const Vector2f targetPos = myLinks[0].myPosition + myFireDirection * myHookSpeed;

	constexpr int steps = 5;
	for (int step = 0; step < steps; step++)
	{
		const float percent = static_cast<float>(step) / static_cast<float>(steps);
		const Vector2f testPos = myLinks[0].myPosition * (1.f - percent) + targetPos * percent;
		MapChunk* mapChunk = Megaton::GetInstance().GetMapChunk(testPos);
		if (mapChunk && mapChunk->Collided(testPos) == true)
		{
			finalPosition = testPos;
			return true;
		}
	}

	finalPosition = myLinks[0].myPosition;
	return false;
}

bool Chain::HasReachedMaxLength() const
{
	return myParentPosition.DistanceTo(myLinks[0].myPosition) >= myHookMaxLength;
	return myLinks.Size() * myLinkSize >= myHookMaxLength;
}
