#pragma once
#include "GameObject.h"

class Player;

class Apple : public GameObject
{
public:
	bool		Use(Player& aPlayer) override;
	void		Collide(GameObject* aGameObject) override;
private:
};
