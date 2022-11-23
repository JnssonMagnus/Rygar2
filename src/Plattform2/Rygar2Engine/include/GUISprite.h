#pragma once
#include "Sprite.h"

class GUISprite : public Sprite
{
public:
	void Draw(const Vector2f& aPosition, const Vector2<int>& aSrcPos, const Vector2<int>& aSrcSize, const float aRotation = 0.f) override;
	void Draw(const Vector2f& aPosition, const Vector2<int>& aDstSize, const Color& aColor, const unsigned char aAlpha) override;
};

