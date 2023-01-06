#include "stdafx.h"
#include "PlayerUI.h"
#include "Player.h"
#include "Settings.h"

PlayerUI::PlayerUI(const Player& aPlayer) : myPlayer(aPlayer)
{	
}

void PlayerUI::Init()
{
	myHealthSprite.Init("data/gfx/UI/PlayerHealth.png");
}

void PlayerUI::Draw(const Vector2<int>& aPosition)
{
	DrawHealth();
}

void PlayerUI::DrawHealth()
{
	constexpr int x = 10;
	constexpr int y = 10;
	constexpr int space = 18;

	const int playerHealth = myPlayer.GetProperty<int>(PropertyKey::eLife);
	const int playerMaxHealth = myPlayer.GetProperty<int>(PropertyKey::eMaxLife);

	const Vector2<int> healthSpriteSize = { myHealthSprite.GetSize().myX / 2, myHealthSprite.GetSize().myY };

	for (int healthIndex = 0; healthIndex < playerMaxHealth; healthIndex++)
	{
		const Vector2f position = { static_cast<float>(x + healthIndex * healthSpriteSize.myX), y };
		const Vector2<int> src = { healthSpriteSize.myX * static_cast<int>((playerMaxHealth - healthIndex) <= playerHealth), 0 };
		myHealthSprite.Draw(position, src, healthSpriteSize, 0.f);
	}
}
