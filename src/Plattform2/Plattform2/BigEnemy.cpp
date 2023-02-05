#include "stdafx.h"
#include "BigEnemy.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "PhysicBody.h"
#include "Megaton.h"
#include "MapChunk.h"
#include "AnimationController.h"

void BigEnemy::Update(const float aDeltaTime)
{
	const float moveForce = 3.f;
	if (myStaggeredData.myStaggeredTime > 0)
	{
		myStaggeredData.myStaggeredTime -= aDeltaTime;
		return;
	}

	if (GetProperty<int>(ePropertyValues::eLife) > 0)
	{
		GameObject* player = GameObjectManager::GetInstance()->GetFirstWithName("player");
		assert(player != nullptr && "Player not found!");
		ChangeProperty<bool>(PropertyKey::eFacingRight) = player->GetPhysicBody().GetPosition().myX > myPhysicBody->GetPosition().myX;
		if (player->GetPhysicBody().GetPosition().myX < myPhysicBody->GetPosition().myX)
			myPhysicBody->AddForce({ -moveForce, 0.f });
		else
			myPhysicBody->AddForce({ moveForce, 0.f });

		if (player->GetPhysicBody().GetPosition().myY - myPhysicBody->GetPosition().myY < -20 
			&& myPhysicBody->HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eBottom))
		{
			constexpr float jumpForce = -500.f;
			myPhysicBody->AddForce({ 0.f, jumpForce });
		}
	}
	else
	{
		if (GetProperty<bool>(ePropertyValues::eAlive) == true)
		{
			PostMaster::GetInstance()->SendSoundEvent("bigEnemy_die");

			ChangeProperty<bool>(ePropertyValues::eAlive) = false;
			GetPhysicBody().SetIsKinetic(true);
			MapChunk& map = Megaton::GetInstance().GetMap();

			constexpr size_t dropAmounth = 250;
			for (size_t drop = 0; drop < dropAmounth; drop++)
			{
				Vector2f dropOffset(-rand() % 20 + rand() % 20, -rand() % 20 + rand() % 20);
				map.AddWaterDrop(myPhysicBody->GetPosition() + dropOffset, myPhysicBody->GetVelocity() / 5.f + Vector2f(rand() % 4, -3.f - rand() % 5));
			}
		}
		else
		{
			myHasBeenDeadTimer += 0.016f;
			if (myHasBeenDeadTimer > 50.f)
			{
				Delete();
			}

			MapChunk& map = Megaton::GetInstance().GetMap();
			constexpr size_t dropAmounth = 5;
			for (size_t drop = 0; drop < dropAmounth; drop++)
			{
				Vector2f dropOffset(-rand() % 20 + rand() % 20, -rand() % 20 + rand() % 20);
				map.AddWaterDrop(myPhysicBody->GetPosition() + dropOffset, myPhysicBody->GetVelocity() / 5.f + Vector2f(rand() % 4, -3.f - rand() % 5));
			}
		}
	}

	Actor::Update(aDeltaTime);
}

void BigEnemy::Init(GameObjectType& aGameObjectType)
{
	Actor::Init<AnimationController>(aGameObjectType, *this, myAnimationSet);
	myProperties.SetValue(ePropertyValues::eLife, 5);
	myProperties.SetValue(ePropertyValues::eAlive, true);
	myProperties.SetValue(ePropertyValues::eFacingRight, true);

	myAnimationSet.Init("data/gfx/enemies/rollerEnemy.png");

	const Vector2<int> frameSize(24, 30);
	myPhysicBody->SetHalfSize(frameSize / 2.f);
	myAnimationSet.AddAnimation(eAnimationID::eWalk, 4, frameSize, 10);
	myAnimationSet.AddAnimation(eAnimationID::eIdle, 4, frameSize, 10);
	myAnimationSet.AddAnimation(eAnimationID::eFall, 4, frameSize, 10);
	myAnimationSet.AddAnimation(eAnimationID::eJump, 4, frameSize, 10);
	myAnimationSet.AddAnimation(eAnimationID::eDead, 4, frameSize, 10);
	myAnimationSet.PushAnimation(eAnimationID::eIdle);
	myAnimationSet.CenterPivot();

}

void BigEnemy::Collide(GameObject* aGameObject)
{
	if (aGameObject->GetPhysicBody().HasCollisionTag(eCollisionTags::ePlayer))
	{
		Player* player = dynamic_cast<Player*>(aGameObject);
		DL_ASSERT(player && "Object with player tag was not player!");
		if (player && player->IsAboveEnemy(this) == false)
		{
			player->Damage(1, GetPhysicBody().GetPosition());
		}
	}
}
