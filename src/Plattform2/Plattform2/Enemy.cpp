#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "PhysicBody.h"
#include "Megaton.h"
#include "Map.h"
#include "AIBehaviour.h"

void Enemy::Update(const float aDeltaTime)
{
	myAIBehaviour.Update(*myPhysicBody);
	ChangeProperty<bool>(PropertyKey::eFacingRight) = myPhysicBody->GetDirection().myX < 0.f;
	//const float moveForce = 10.f;
	//if (GetProperty<int>(ePropertyValues::eLife) > 0)
	//{
	//	GameObject* player = GameObjectManager::GetInstance()->GetClosestWithName("player");
	//	assert(player != nullptr && "Player not found!");
	//	ChangeProperty<bool>(PropertyKey::eFacingRight) = player->GetPhysicBody().GetPosition().myX > myPhysicBody->GetPosition().myX;
	//	if (player->GetPhysicBody().GetPosition().myX < myPhysicBody->GetPosition().myX)
	//		myPhysicBody->AddForce({ -moveForce, 0.f });
	//	else
	//		myPhysicBody->AddForce({ moveForce, 0.f });

	//	if (player->GetPhysicBody().GetPosition().myY - myPhysicBody->GetPosition().myY < -150
	//		&& myPhysicBody->HasPhysicState(ePhysicStates::eOnGround, PhysicBody::eLocator::eBottom))
	//	{
	//		constexpr float jumpForce = -200.f;
	//		myPhysicBody->AddForce({ 0.f, jumpForce });
	//	}
	//}
	//else
	//{
	//	if (GetProperty<bool>(ePropertyValues::eAlive) == true)
	//	{
	//		PostMaster::GetInstance()->SendSoundEvent("enemyDie");

	//		ChangeProperty<bool>(ePropertyValues::eAlive) = false;
	//		GetPhysicBody().SetIsKinetic(true);

	//		Map& map = Megaton::GetInstance().GetMap();
	//		constexpr size_t dropAmounth = 25;
	//		for (size_t drop = 0; drop < dropAmounth; drop++)
	//		{
	//			Vector2f dropOffset(-rand() %20 + rand()%20, -rand() % 20+rand() % 20);
	//			map.AddWaterDrop(myPhysicBody->GetPosition() + dropOffset, myPhysicBody->GetVelocity() / 5.f + Vector2f(rand()%4, -3.f - rand()%5));
	//		}
	//	}
	//	else
	//	{
	//		myHasBeenDeadTimer += 0.016f;
	//		if (myHasBeenDeadTimer > 5.f)
	//		{
	//			Delete();
	//		}
	//	}
	//}

	Actor::Update(aDeltaTime);
}

void Enemy::Init(GameObjectType& aGameObjectType)
{
	Actor::Init(aGameObjectType);
	myProperties.SetValue(ePropertyValues::eLife, 3);
	myProperties.SetValue(ePropertyValues::eAlive, true);
	myProperties.SetValue(ePropertyValues::eFacingRight, true);

	myAnimationSet.Init("data/gfx/enemies/turtleEnemy.png");

	const Vector2<int> frameSize(24, 15);
	myAnimationSet.AddAnimation(eAnimationID::eWalk, 1, frameSize);
	myAnimationSet.AddAnimation(eAnimationID::eIdle, 1, frameSize);
	myAnimationSet.AddAnimation(eAnimationID::eFall, 1, frameSize);
	myAnimationSet.AddAnimation(eAnimationID::eJump, 1, frameSize);
	myAnimationSet.AddAnimation(eAnimationID::eDead, 1, frameSize);
	myAnimationSet.PushAnimation(eAnimationID::eIdle);
	myAnimationSet.CenterPivot();
}

void Enemy::Collide(GameObject* aGameObject)
{
	if (aGameObject->GetPhysicBody().HasCollisionTag(eCollisionTags::ePlayer))
	{
		Player* player = dynamic_cast<Player*>(aGameObject);
	//	player->ChangeStat(eStats::eHealth, -0.3f);
	}

	Actor::Collide(aGameObject);
}
