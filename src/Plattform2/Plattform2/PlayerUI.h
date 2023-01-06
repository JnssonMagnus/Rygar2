#pragma once
#include "Text.h"
#include "GUISprite.h"
#include <GrowingArray.h>

class Player;

class PlayerUI
{
public:
								PlayerUI(const Player& aPlayer);
	void						Init();
	void						Draw(const Vector2<int>& aPosition);

private:
	void						DrawHealth();

	const Player&				myPlayer;
	GUISprite					myHealthSprite;
};
