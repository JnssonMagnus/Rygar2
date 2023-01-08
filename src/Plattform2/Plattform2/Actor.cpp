#include "stdafx.h"
#include "Actor.h"
#include "PhysicBody.h"
#include "MapChunk.h"
#include "Megaton.h"
#include "AnimationController.h"
#include "Tileset.h"

Actor::~Actor()
{
	SAFE_DELETE(myAnimationController);
}

void Actor::Update(const float aDeltaTime)
{
	myAnimationSet.Update(aDeltaTime);
	myAnimationController->Update();
	GameObject::Update(aDeltaTime);

	if (myStaggeredData.myStaggeredTime > 0.f)
	{
		myStaggeredData.myStaggeredTime -= aDeltaTime;
	}
}

void Actor::Draw()
{
	myAnimationSet.Draw(GetPhysicBody().GetPosition());
}

void Actor::Damage(const int aDamage, const Vector2f& aContactPoint)
{
	const int life = GetProperty<int>(ePropertyValues::eLife);
	if (life > 0)
	{
		//MapChunk& map = Megaton::GetInstance().GetMap();
		//for (size_t drop = 0; drop < myBloodHitAmount; drop++)
		//{
		//	Vector2f dropOffset(-rand() % 20 + rand() % 20, -rand() % 20 + rand() % 20);
		//	map.AddWaterDrop(aContactPoint + dropOffset, Vector2f(rand() % 3 - rand() % 3, -rand() % 3));
		//}
		ChangeProperty<int>(ePropertyValues::eLife) -= aDamage;

		if (myStaggeredData.myStaggeredTime <= 0.f && GetProperty<int>(ePropertyValues::eLife) > 0)
		{
			myStaggeredData.myDamageOverLastFiveSeconds += aDamage;
			if (myStaggeredData.myDamageOverLastFiveSeconds > myStaggeredData.myDamageToBeStaggered)
			{
				myStaggeredData.myStaggeredTime = myStaggeredData.myTimeToBeStaggared;
				myStaggeredData.myDamageOverLastFiveSeconds = 0.f;
				myAnimationSet.PushAnimation(eAnimationID::eStagger);
				//myPhysicBody->AddForce((myPhysicBody->GetPosition() - aContactPoint).GetNormalized() * 800.f);
				PostMaster::GetInstance()->SendSoundEvent("bigEnemy_stagger");
			}
		}

		myAnimationSet.ColorBlink(Color(255_uc, 0_uc, 0_uc), 0.3f, 0.f);

		if (GetProperty<int>(ePropertyValues::eLife) <= 0 && HasProperty(ePropertyValues::eKeepOnLevelReset) == false)
		{
			Delete();
			PostMaster::GetInstance()->SendSoundEvent("enemyDeath");
			Message particleMsg;
			particleMsg.myPosition = myPhysicBody->GetPosition();
			particleMsg.myDirection = { 0.f, -1.f };
			particleMsg.myMessageType = eMessageTypes::eCreateParticleSystem;
			particleMsg.myIntData = 2;

			PostMaster::GetInstance()->SendMessage(particleMsg);
		}
	}
}

void Actor::Stagger()
{
	myStaggeredData.myStaggeredTime = myStaggeredData.myTimeToBeStaggared;
}

void Actor::CollidedWithMap(const MapCollisionData& aMapCollisonData)
{
	for (const TileData* tileData : aMapCollisonData.myCollidedTileTypes)
	{
		if (tileData->myIsFallout)
		{
			Damage(99999, { 0,0 });
			return;
		}
	}
}

bool Actor::IsStaggered() const
{
	return myStaggeredData.myStaggeredTime > 0.f;
}
