#pragma once
#include "GameObject.h"
#include <Vector2.h>

class Sink : public GameObject
{
public:
					Sink();
	void			Update(const float aDeltaTime) override;

private:
	Vector2f		myExtends;
	unsigned char	mySinkPerFrame;
};
