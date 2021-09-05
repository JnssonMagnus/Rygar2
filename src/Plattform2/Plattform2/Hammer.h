#pragma once
#include "GameObject.h"

class Hammer : public GameObject
{
public:
	bool Use(Player& aPlayer) override;

private:
};
