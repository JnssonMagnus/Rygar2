#pragma once
#include "Sprite.h"

class ParallaxLayer
{
public:
	void		Init(const char* aImageFilename, const Vector2f& aMovePercent);
	void		Render(const Vector2f& aCameraPosition, const float aCameraZoom = 1.f);

private:
	Sprite		mySprite;
	Vector2f	myMovePercent;
};
