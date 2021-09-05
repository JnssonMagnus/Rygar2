#pragma once
#include <..\external\rapidJSON\document.h>

enum class eBlendMode
{
	eNormal = 0,
	eNone = 1,
	eAdd = 2,
	eMultiply = 4
};

struct ParticleEmitterBlueprint
{
	void Init(const rapidjson::GenericObject<false, rapidjson::Value>& aObject);

#ifdef _DEBUG
	std::string		myName;
#endif

	Vector4f		myStartColor;
	Vector4f		myEndColor;
	Vector2f		myStartSize;
	Vector2f		myEndSize;
	Vector2f		myInitVelocity;
	Texture			myTexture;
	float			myParticleMaxAge = 1.f;
	float			myMaxAge = 1.f;
	float			myDrag = 1.f;
	float			myRandomDirection = 0.f;
	bool			myGravity = false;
	eBlendMode		myBlendMode = eBlendMode::eNormal;
};

