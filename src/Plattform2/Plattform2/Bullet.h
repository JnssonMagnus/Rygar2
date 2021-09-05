#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	void	Collide(GameObject* aGameObject) override;
	void	CollideWithTile(eCollisionPoint collisionPoint) override;
};
