#pragma once
#include "GameObject.h"
class Explosion : public GameObject
{
public:
				Explosion();		
	void		Collide(GameObject* aGameObject) override;
	void		Update(const float aDeltaTime) override;
private:
	float		myAge = 0.f;
};

