#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	void	Collide(GameObject* aGameObject) override;
	void	CollidedWithMap(const MapCollisionData& aMapCollisionData) override;
};
