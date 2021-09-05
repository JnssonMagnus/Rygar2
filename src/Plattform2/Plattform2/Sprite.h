#pragma once
#include <Vector2.h>
#include "Texture.h"
#include "typedefs.h"

class Renderer;

class Sprite
{
public:
	virtual						~Sprite() = default;
								Sprite();
	virtual void				Draw(const Vector2f& aPosition, const float aAngle = 0.f, const bool aNoZoom = false);
	virtual void				Draw(const Vector2f& aPosition, const Vector2<int>& aSrcPos, const Vector2<int>& aSrcSize, const float aAngle = 0.f);
	virtual void				Draw(const Vector2f& aPosition, const Vector2<int>& aDstSize, const Color& aColor = Color(255_uc, 255_uc, 255_uc), const unsigned char aAlpha = 255_uc);
	virtual void				Draw(const Vector2f& aPosition, const Vector2<int>& aDstSize, const float aAngle);
	void						Init(const char* aFilename);
	void						SetPivot(const Vector2<int>& aPivot);
	void						CenterPivot();
	virtual const Vector2<int>&	GetSize() const;

	static void					SetRenderer(Renderer* aRenderer);

protected:
	Texture						myTexture;	
	Vector2<int>				myPivot;
	static Renderer*			ourRenderer;
};
