#include "stdafx.h"
#include "Enemy.h"
#include "EnemyType.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "PhysicBody.h"
#include "Megaton.h"
#include "MapChunk.h"
#include "AIBehaviour.h"
#include "AnimationController.h"

Enemy::Enemy(EnemyType& enemyType) : myEnemyType(enemyType)
{
	Init(enemyType);
}

void Enemy::Update(const float aDeltaTime)
{
	Actor::Update(aDeltaTime);

	if (myStaggeredData.myStaggeredTime > 0.f)
		return;

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
}

void Enemy::Init(EnemyType& aEnemyType)
{
	Actor::Init<AnimationController>(aEnemyType, *this, myAnimationSet);

	myProperties.SetValue(ePropertyValues::eLife, aEnemyType.GetMaxLife());
	myProperties.SetValue(ePropertyValues::eAlive, true);
	myProperties.SetValue(ePropertyValues::eFacingRight, true);

	const AnimationSet2& animationSet = aEnemyType.GetAnimationSet();

	myAnimationSet.Init(animationSet.mySprite.c_str());

	const Vector2<int> frameSize = animationSet.myCellSize;
	myPhysicBody->SetHalfSize(frameSize / 2.f);

	for (const auto& [animationID, animationData] : animationSet.myAnimations) {
		myAnimationSet.AddAnimation(animationID, animationData.myFrameCount, frameSize, animationData.myFpsCount);
	}

	myAnimationSet.CenterPivot();
}

void Enemy::Collide(GameObject* aGameObject)
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