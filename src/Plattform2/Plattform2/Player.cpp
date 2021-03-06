#include "stdafx.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "GameObjectType.h"
#include "GameObjectTypes.h"
#include "Megaton.h"
#include "Map.h"
#include "Weapon.h"
#include "Sprayer.h"
#include "Shotgun.h"
#include "GrenadeLauncher.h"
#include "ParticleEmitter.h"
#include <postmaster/postmaster.h>

Player::Player()
{
	myPickedUpObject = nullptr;
	myDashStrength = 400.f;
	myJumpStrength = 10.f;
	myDashReloadTimer = 60;
	myDashTime = 0;
}

Player::~Player()
{
	myWeapons.DeleteAll();
}

void Player::Update(const float aDeltaTime)
{
	Actor::Update(aDeltaTime);
	myWeapons[myCurrentWeapon]->Update(aDeltaTime);
	myStats.UpdateStats();

	Vector2f positionByHook = myHook.Update(aDeltaTime, myPhysicBody->GetPosition(), myPhysicBody->GetVelocity());

	myHook.Shorten();

	myPhysicBody->AddForce( (positionByHook - myPhysicBody->GetPosition()) * Vector2f(60.f, 10.8f));
	myPhysicBody->SetPosition(positionByHook);

	if (myPickedUpObject != nullptr)
	{
		Vector2f newPos = myPhysicBody->GetPosition();
		newPos -= Vector2f(0, myPhysicBody->GetHalfSize().myY + myPickedUpObject->GetPhysicBody().GetHalfSize().myY);
		myPickedUpObject->GetPhysicBody().SetPosition(newPos);
	}

	Message listenerMessage(eMessageTypes::eUpdateListenerPosition);
	listenerMessage.myMatrix.SetPosition(Vector4f{ myPhysicBody->GetPosition().myX, myPhysicBody->GetPosition().myY, 0.f, 0.f });
	PostMaster::GetInstance()->SendMessage(listenerMessage);

	static bool last = true; 
	if (myPhysicBody->HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eBottom) == true && last == false)
		PostMaster::GetInstance()->SendSoundEvent("land");

	last = myPhysicBody->HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eBottom);

	if (myStats.GetStat(eStats::eHealth) <= 0.f)
		PostMaster::GetInstance()->SendDelayedMessage(Message(eMessageTypes::ePlayerDied));

	myDashTime--;

	ChangeProperty<bool>(ePropertyValues::eFacingRight) = myAim.GetPosition().myX > myPhysicBody->GetPosition().myX;
}

void Player::Draw()
{
	myAnimationSet.Draw(myPhysicBody->GetPosition());
	myHook.Draw();
	
	myStats.SetStat(eStats::eAmmo, myWeapons[myCurrentWeapon]->GetPercentageAmmoLeft() * 100.f);
	myStatsViewer.Draw({ 10, 10 });
	myAim.Draw();
}

void Player::Init(GameObjectType& aGameObjectType)
{
	Actor::Init(aGameObjectType);

	myHook.Init();

	myAim.Init();

	myAnimationSet.Init("data/gfx/player.png");

	const Vector2<int> frameSize(20, 34);
	myAnimationSet.AddAnimation(eAnimationID::eWalk, 3, frameSize, 10);
	myAnimationSet.AddAnimation(eAnimationID::eIdle, 1, frameSize, 5);
	myAnimationSet.AddAnimation(eAnimationID::eFall, 1, frameSize, 5, { 0, frameSize.myY * 3 });
	myAnimationSet.AddAnimation(eAnimationID::eJump, 1, frameSize, 5, { 0, frameSize.myY * 2 });
	myAnimationSet.PushAnimation(eAnimationID::eIdle);

	myAnimationSet.CenterPivot();

	AddWeapons();

// ------------------------------

	myPhysicBody->SetPosition({ 300, 200 });
	myPhysicBody->SetHalfSize(Vector2f(myAnimationSet.GetSize().x / 2.f,
		myAnimationSet.GetSize().y / 2.f));

	myStatsViewer.Init(myStats);
	myStats.SetStat(eStats::eHealth, 1000000.f);
	myStats.SetStat(eStats::eAmmo, 1000.f);

	myProperties.SetValue(ePropertyValues::eLife, 1000000);
}

void Player::RecieveEvent(const Input::eInputEvent aEvent, const Input::eInputState aState, const float aValue)
{
	switch (aEvent)
	{
	case Input::eInputEvent::eFireGun1:
		if (aState == Input::eInputState::ePressed)
		{
			Vector2f dir = myAim.GetPosition() - myPhysicBody->GetPosition();
			dir.Normalize();
			myWeapons[myCurrentWeapon]->Shoot(myPhysicBody->GetPosition(), dir, myAim.GetPosition());
		}
		break;

	case Input::eInputEvent::eCycleWeapons:
	{
		const int cycleValue = aValue > 0 ? 1 : -1;
		PostMaster::GetInstance()->SendSoundEvent("changeWeapon");
		CycleWeapons(cycleValue);
		break;
	}
	case Input::eInputEvent::eUseItem:
		if (myPickedUpObject != nullptr)
		{				
			if (myPickedUpObject->Use(*this) == true)
			{
				myPickedUpObject->Delete();
				myPickedUpObject = nullptr;
			}
		}

		break;

	case Input::eInputEvent::ePickUp:
		if (aState == Input::eInputState::eDown)
		{
			if (myPickedUpObject == nullptr)
			{
				GameObject* closest = GameObjectManager::GetInstance()->GetClosest(myPhysicBody->GetPosition(), this);
				if (closest != nullptr)
				{
					PickUp(closest);
				}
			}
			else
			{
				DropItem();
			}
		}
		break;

	case Input::eInputEvent::eUseHook:
	{
		Vector2f direction = myAim.GetPosition() - myPhysicBody->GetPosition();
		direction.Normalize();

		myHook.Fire(direction);
		break;
	}
	case Input::eInputEvent::eMoveRight:
		myPhysicBody->AddForce({ 90.f, 0.f });
		break;
	case Input::eInputEvent::eMoveLeft:
		myPhysicBody->AddForce({ -90.f, 0.f });
		break;
	case Input::eInputEvent::eDown:
		myHook.Extend();
		break;
	case Input::eInputEvent::eDash:
		if (myDashTime <= 0)
		{
			const int direction = myPhysicBody->GetVelocity().myX > 0 ? 1 : -1;
			myPhysicBody->SetVelocity({ myDashStrength * direction, -2.f });
			myDashTime = myDashReloadTimer;
		}
		break;
	case Input::eInputEvent::eJump:
		myHook.Shorten();
		if (aState == Input::eInputState::eDown &&
			myPhysicBody->HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eBottom) == true)
		{
			PostMaster::GetInstance()->SendSoundEvent("jump");
			myPhysicBody->SetForce({ myPhysicBody->GetForce().myX, -myJumpStrength });
			myHasDoubleJumped = false;
		}
		else if (aState == Input::eInputState::eDown)
		{
			if (myPhysicBody->HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eLeft) == true)
			{
				myPhysicBody->AddForce({ 10.f, -5.f });
			}
			else if (myPhysicBody->HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eRight) == true)
			{
				myPhysicBody->AddForce({ -10.f, -5.f });
			}
			else if (myHasDoubleJumped == false)
			{
				myPhysicBody->SetForce({ myPhysicBody->GetForce().myX, -myJumpStrength });
				myHasDoubleJumped = true;
			}
		}
		break;
	}
}

void Player::CollideWithTile(eCollisionPoint collisionPoint)
{
	if (myHook.GetState() == Hook::eState::eStuck)
	{
		if (myPhysicBody->HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eTop) == true)
			myHook.Fire(Vector2f(0.f, 0.f));
	}
}

void Player::ChangeStat(const eStats aStat, const float aChange)
{
	myStats.ChangeStat(aStat, aChange);
}

bool Player::PickUp(GameObject* aGameObject)
{
	DL_ASSERT(aGameObject != nullptr && "Tried to pick up nullptr!");
	if (myPickedUpObject != nullptr)
	{
		return false;
	}
	else
	{
		myPickedUpObject = aGameObject;
		aGameObject->GetPhysicBody().SetEnabled(false);
		aGameObject->GetPhysicBody().SetForce({ 0.f, 0.f });
		aGameObject->GetPhysicBody().SetVelocity({ 0.f, 0.f });
		aGameObject->GetPhysicBody().SetRotation(false);
	}
	return false;
}

void Player::DropItem()
{
	if (myPickedUpObject != nullptr)
	{
		Vector2f newPos = myPhysicBody->GetPosition();
		newPos -= Vector2f(0, myPhysicBody->GetHalfSize().myY + myPickedUpObject->GetPhysicBody().GetHalfSize().myY - 5.f);
		myPickedUpObject->GetPhysicBody().SetPosition(newPos);

		myPickedUpObject->GetPhysicBody().SetRotation(true);
		myPickedUpObject->GetPhysicBody().SetEnabled(true);
		myPickedUpObject->GetPhysicBody().AddForce(myPhysicBody->GetVelocity() + Vector2f(0, -10.f));
		myPickedUpObject = nullptr;
	}
}

const Vector2f Player::GetAimLocalPosition() const
{
	return myAim.GetLocalPosition();
}

const Stats& Player::GetStats() const
{
	return myStats;
}

void Player::CycleWeapons(int aCycleValue)
{
	myCurrentWeapon += aCycleValue;
	if (myCurrentWeapon >= myWeapons.Size())
	{
		myCurrentWeapon = 0;
	}
	else if (myCurrentWeapon < 0)
	{
		myCurrentWeapon = myWeapons.Size() - 1;
	}
}

void Player::AddWeapons()
{
	Weapon* sprayer = new Sprayer();
	Weapon* shotgun = new Shotgun();
	Weapon* grenadeLauncher = new GrenadeLauncher();
	myWeapons.Add(sprayer);
	myWeapons.Add(shotgun);
	myWeapons.Add(grenadeLauncher);
}

