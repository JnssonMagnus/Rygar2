#pragma once
#include "GameObject.h"
#include "Animation.h"

class Grenade : public GameObject
{
public:
					Grenade();
	void			Collide(GameObject* aGameObject) override;
	void			CollidedWithMap(const MapCollisionData& aMapCollisionDatas) override;
	void			Update(const float aDeltaTime) override;
	void			Init(GameObjectType& aGameObjectType) override;
	void			Draw() override;

private:
	float			myLivedTime = 0.f;
	float			myMaxAge = 0.f;
	AnimationSet	myAnimation;
};

