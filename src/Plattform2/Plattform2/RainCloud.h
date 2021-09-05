#pragma once
#include "GameObject.h"

class RainCloud : public GameObject
{
public:
				RainCloud();
	void		Update(const float aDeltaTime) override;

private:
	int			myDropsLeft;
};
