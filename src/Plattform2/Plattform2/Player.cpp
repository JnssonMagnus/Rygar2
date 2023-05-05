#include "stdafx.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "GameObjectType.h"
#include "GameObjectTypes.h"
#include "Megaton.h"
#include "MapChunk.h"
#include "Weapon.h"
#include "Sprayer.h"
#include "Shotgun.h"
#include "GrenadeLauncher.h"
#include "DiskArmor.h"
#include "ParticleEmitter.h"
#include "PlayerAnimationController.h"
#include <PostMaster/MessageTypes.h>
#include <postmaster/postmaster.h>


Player::Player() : myPlayerUI(*this)
{
	myPickedUpObject = nullptr;
	myDashStrength = 400.f;
	myJumpStrength = 7.f;
	myDashReloadTimer = 60;
	myDashTime = 0;	
	myWalkSpeed = 280.f;

	myProperties.SetValue(PropertyKey::eLife, 3);
	myProperties.SetValue(PropertyKey::eMaxLife, 3);
	myProperties.SetValue(PropertyKey::eDucking, false);
	myProperties.SetValue(PropertyKey::eKeepOnLevelReset, true);

	myStaggeredData.myDamageToBeStaggered = 1;
	myStaggeredData.myTimeToBeStaggared = 0.3f;
}

Player::~Player()
{
	myWeapons.DeleteAll();
}

void Player::Update(const float aDeltaTime)
{
	Actor::Update(aDeltaTime);	

	UpdateHook(aDeltaTime);
	UpdatePickedUpObject();
	UpdateWeapon(aDeltaTime);
	PlayLandOnGroundSound();
	UpdateSoundListenerPosition();

	if (IsDead())
		PostMaster::GetInstance()->SendDelayedMessage(Message(eMessageTypes::ePlayerDied));

	myDashTime--;
	myInvinsibleTime -= aDeltaTime;

	ChangeProperty<bool>(ePropertyValues::eFacingRight) = myAim.GetPosition().myX > myPhysicBody->GetPosition().myX;
}

void Player::Draw()
{
	myAnimationSet.Draw(myPhysicBody->GetPosition());
	myHook.Draw();
	
	myWeapons[myCurrentWeapon]->Draw();
	
	myPlayerUI.Draw({ 10, 10 });
	myAim.Draw();
}

void Player::Init(GameObjectType& aGameObjectType)
{
	Actor::Init<PlayerAnimationController>(aGameObjectType, *this, myAnimationSet);
	myHook.Init("data/gfx/link.png", "data/gfx/hook.png", 200.f, 5.f, 1);	

	myAim.Init();

	myAnimationSet.Init("data/gfx/player.png");

	const Vector2<int> frameSize(24, 32);
	myAnimationSet.AddAnimation(eAnimationID::eWalk, 6, frameSize, 9);
	myAnimationSet.AddAnimation(eAnimationID::eIdle, 1, frameSize, 5, { frameSize.myX * 2, frameSize.myY * 2 });
	myAnimationSet.AddAnimation(eAnimationID::eFall, 1, frameSize, 5, { 0, frameSize.myY * 3 });
	myAnimationSet.AddAnimation(eAnimationID::eJump, 1, frameSize, 5, { 0, frameSize.myY * 3 });
	myAnimationSet.AddAnimation(eAnimationID::eAttack, 1, frameSize, 5, { 0, frameSize.myY });
	myAnimationSet.AddAnimation(eAnimationID::eJumpAttack, 1, frameSize, 5, frameSize );
	myAnimationSet.AddAnimation(eAnimationID::eDuckIdle, 1, frameSize, 5, { 0, frameSize.myY * 2 });
	myAnimationSet.AddAnimation(eAnimationID::eDuckAttack, 1, frameSize, 5, { frameSize.myX * 2, frameSize.myY});
	myAnimationSet.AddAnimation(eAnimationID::eThrowHook, 1, frameSize, 5, { frameSize.myX * 1, frameSize.myY * 2 });
	myAnimationSet.AddAnimation(eAnimationID::eStagger, 1, frameSize, 1, { frameSize.myX * 3, frameSize.myY });
	myAnimationSet.PushAnimation(eAnimationID::eIdle);

	myAnimationSet.CenterPivot();

	AddWeapons();

// ------------------------------

	myPhysicBody->SetPosition({ 100, 50 });
	myPhysicBody->SetHalfSize(Vector2f(myAnimationSet.GetSize().x / 2.f,
		myAnimationSet.GetSize().y / 2.f - 2));

	myPlayerUI.Init();

	myProperties.SetValue(ePropertyValues::eLife, 3);

	myHook.SetHitWallSoundEvent("rygarHookStuck");
	myHook.SetLaunchSoundEvent("rygarHookThrow");

	SetRespawnPosition(GetPhysicBody().GetPosition());
}

void Player::RecieveEvent(const Input::eInputEvent aEvent, const Input::eInputState aState, const float aValue)
{
	if (IsStaggered()) {
		return;
	}

	switch (aEvent)
	{
	case Input::eInputEvent::eFireGun1:
	{
		if (aState == Input::eInputState::eDown)
		{
			Vector2f direction = myAim.GetPosition() - myWeapons[myCurrentWeapon]->GetPosition();
			direction.Normalize();
			myWeapons[myCurrentWeapon]->Shoot(myPhysicBody->GetPosition(), direction, myAim.GetPosition());
		}
		break;
	}
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
		if (IsHinderedFromMoving() == false)
			myPhysicBody->AddForce({ myWalkSpeed, 0.f });
		break;
	case Input::eInputEvent::eMoveLeft:
		if (IsHinderedFromMoving() == false)
			myPhysicBody->AddForce({ -myWalkSpeed, 0.f });
		break;
	case Input::eInputEvent::eDown:
		if (myHook.GetState() == Chain::eState::eUnreleased && aState == Input::eInputState::ePressed && myPhysicBody->HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eBottom) == true) {
			ChangeProperty<bool>(PropertyKey::eDucking) = true;
		}
		else if (myHook.GetState() == Chain::eState::eUnreleased && aState == Input::eInputState::eUp) {
			ChangeProperty<bool>(PropertyKey::eDucking) = false;
		}

		if (!myPhysicBody->HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eBottom)) {
			myHook.Extend();
		}
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
		if (!myPhysicBody->HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eTop)) {
			myHook.Shorten();
		}
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
			//else if (myHasDoubleJumped == false)
			//{
			//	myPhysicBody->SetForce({ myPhysicBody->GetForce().myX, -myJumpStrength });
			//	myHasDoubleJumped = true;
			//}
		}
		break;
	}
}

void Player::CollidedWithMap(const MapCollisionData& aMapCollisionData)
{
	Actor::CollidedWithMap(aMapCollisionData);
	if (myHook.GetState() == Chain::eState::eStuck)
	{
		if (myPhysicBody->HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eTop) == true)
			myHook.Fire(Vector2f(0.f, 0.f));
	}
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

bool Player::IsAboveEnemy(const GameObject* const aGameObject) const
{
	return myPhysicBody->GetMiddleBottom().myY < aGameObject->GetPhysicBody().GetMiddleTop().myY + 5;
}

void Player::Respawn()
{
	myPhysicBody->SetStartPosition(myRespawnPosition);
	myPhysicBody->SetVelocity({ 0.f, 0.f });
	myPhysicBody->SetForce({ 0.f, 0.f });
	myDashTime = 0;
	myProperties.SetValue(PropertyKey::eDucking, false);
	myStaggeredData.myDamageOverLastFiveSeconds = 0;
	myStaggeredData.myStaggeredTime = 0;

	myHook.Reset();
	myDisk.Reset();

	myInvinsibleTime = 0;
	myProperties.SetValue(ePropertyValues::eLife, 3);
	myAnimationSet.ClearColorBlinks();
	PostMaster::GetInstance()->SendDelayedMessage(Message(eMessageTypes::ePlayerDied));
}

void Player::SetRespawnPosition(const Vector2f& aWorldPosition)
{
	myRespawnPosition = aWorldPosition;
}

bool Player::IsDead() const
{
	return GetProperty<int>(ePropertyValues::eLife) < 0;
}

bool Player::IsHinderedFromMoving() const
{
	return IsAttacking() && myPhysicBody->HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eBottom) == true || GetProperty<bool>(PropertyKey::eDucking) == true;
}

bool Player::IsAttacking() const
{
	return myProperties.GetValue<bool>(ePropertyValues::eIsAttacking);
}

void Player::Collide(GameObject* aGameObject)
{
	if (aGameObject->GetPhysicBody().HasCollisionTag(eCollisionTags::eEnemy))
	{
		if (IsAboveEnemy(aGameObject) == true)
		{
			constexpr float jumpOnEnemyBounceForce = -6.f;
			myPhysicBody->SetVelocity({ myPhysicBody->GetVelocity().myX, jumpOnEnemyBounceForce });
			Actor* actor = dynamic_cast<Actor*>(aGameObject);
			actor->Stagger();
			PostMaster::GetInstance()->SendSoundEvent("rygarJumpStagger");
		}
	}
}

void Player::Damage(const int aDamage, const Vector2f& aContactPoint)
{
	if (!IsStaggered() && myInvinsibleTime <= 0.f) {
		PostMaster::GetInstance()->SendSoundEvent("rygarTakeDamage");
		Actor::Damage(aDamage, aContactPoint);
		myAnimationSet.ColorBlink(Color(130_uc, 100_uc, 100_uc), 1.7f, 0.1f);
		
		const float staggerDirection = aContactPoint.myX < myPhysicBody->GetPosition().myX ? 1.f : -1.f;
		myPhysicBody->TranslatePosition({ 0.f, -1.f });
		myPhysicBody->SetVelocity({ 0, 0 });
		myPhysicBody->AddForce({ staggerDirection * 3000.f, -300.1f });
		myInvinsibleTime = 2.f;
		myAnimationSet.PushAnimation(eAnimationID::eStagger);
	}

	if (IsDead()) 
	{
		Respawn();
	}
}

const Vector2f Player::GetAimLocalPosition() const
{
	return myAim.GetLocalPosition();
}

void Player::UpdateHook(const float aDeltaTime)
{
	Vector2f positionByHook = myHook.Update(aDeltaTime, myPhysicBody->GetPosition(), myPhysicBody->GetVelocity());

	myPhysicBody->AddForce((positionByHook - myPhysicBody->GetPosition()) * Vector2f(30.f, 5.8f));
	myPhysicBody->TranslatePosition(positionByHook - myPhysicBody->GetPosition());

}

void Player::UpdatePickedUpObject()
{
	if (myPickedUpObject != nullptr)
	{
		Vector2f newPos = myPhysicBody->GetPosition();
		newPos -= Vector2f(0, myPhysicBody->GetHalfSize().myY + myPickedUpObject->GetPhysicBody().GetHalfSize().myY);
		myPickedUpObject->GetPhysicBody().SetPosition(newPos);
	}
}

void Player::PlayLandOnGroundSound()
{
	static bool last = true;
	if (myPhysicBody->HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eBottom) == true && last == false)
		PostMaster::GetInstance()->SendSoundEvent("rygarLand");

	last = myPhysicBody->HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eBottom);
}

void Player::UpdateWeapon(const float aDeltaTime)
{
	const Vector2<int> duckingModifier = GetProperty<bool>(ePropertyValues::eDucking) ? Vector2<int>(0, 8) : Vector2<int>(0, 0);
	myWeapons[myCurrentWeapon]->Update(aDeltaTime, myPhysicBody->GetPosition() + duckingModifier, GetProperty<bool>(ePropertyValues::eFacingRight) ? 1.f : -1.f);
	myProperties.ChangeValue<bool>(ePropertyValues::eIsAttacking) = myWeapons[myCurrentWeapon]->GetWeaponStatus() == eWeaponStatus::eFireing ? true : false;
}

void Player::UpdateSoundListenerPosition()
{
	Message listenerMessage(eMessageTypes::eUpdateListenerPosition);
	listenerMessage.myMatrix.SetPosition(Vector4f{ myPhysicBody->GetPosition().myX, myPhysicBody->GetPosition().myY, 0.f, 0.f });
	PostMaster::GetInstance()->SendMessage(listenerMessage);
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
	Weapon* diskArmor = new DiskArmor();
	diskArmor->SetOffsetPosition({ 10, -7 });

	Weapon* shotgun = new Shotgun();
	Weapon* grenadeLauncher = new GrenadeLauncher();
	myWeapons.Add(diskArmor);
	myWeapons.Add(sprayer);
	myWeapons.Add(shotgun);
	myWeapons.Add(grenadeLauncher);

	for (auto& weapon : myWeapons)
		weapon->Init();
}


