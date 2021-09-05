#pragma once
#include "GameObject.h"

class Boulder : public GameObject
{
public:
	bool		Use(Player& aPlayer) override;
};
