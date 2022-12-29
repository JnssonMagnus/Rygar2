#include "stdafx.h"
#include "Actor.h"
#include "PhysicBody.h"
#include "MapChunk.h"
#include "Megaton.h"
#include "AnimationController.h"

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
		MapChunk& map = Megaton::GetInstance().GetMap();
		for (size_t drop = 0; drop < myBloodHitAmount; drop++)
		{
			Vector2f dropOffset(-rand() % 20 + rand() % 20, -rand() % 20 + rand() % 20);
			map.AddWaterDrop(aContactPoint + dropOffset, Vector2f(rand() % 3 - rand() % 3, -rand() % 3));
		}

		if (myStaggeredData.myStaggeredTime <= 0.f)
		{
			myStaggeredData.myDamageOverLastFiveSeconds += aDamage;
			if (myStaggeredData.myDamageOverLastFiveSeconds > myStaggeredData.myDamageToBeStaggered)
			{
				myStaggeredData.myStaggeredTime = myStaggeredData.myTimeToBeStaggared;
				myStaggeredData.myDamageOverLastFiveSeconds = 0.f;
				myAnimationSet.PushAnimation(eAnimationID::eDead);
				myPhysicBody->AddForce((myPhysicBody->GetPosition() - aContactPoint).GetNormalized() * 800.f);
				PostMaster::GetInstance()->SendSoundEvent("bigEnemy_stagger");
			}
		}

		ChangeProperty<int>(ePropertyValues::eLife) -= aDamage;
		myAnimationSet.DamageBlink();

		if (GetProperty<int>(ePropertyValues::eLife) <= 0)
		{
			Delete();
			PostMaster::GetInstance()->SendSoundEvent("enemyDeath");
		}
	}
}

void Actor::Stagger()
{
	myStaggeredData.myStaggeredTime = myStaggeredData.myTimeToBeStaggared;
}
