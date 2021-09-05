#pragma once
#include "Texture.h"
#include "particle.h"
#include "ParticleEmitterBlueprint.h"

struct ParticleModifiers
{
	Vector2f	myVelocity;
	float		myAge = 0.f;
};

class Renderer;

class ParticleEmitter
{
public:
	void			Update(const float aDeltaTime);
	void			Draw();
	void			Init(const ParticleEmitterBlueprint& aBluePrint, const Vector2f& aPosition, const Vector2f& aDirection);
	bool			IsFinished() const;
	static void		SetRenderer(Renderer* aRenderer);

private:	
	CU::StaticArray<CU::GrowingArray<Particle>, 2>
										myParticles;
	CU::GrowingArray<ParticleModifiers>	myParticleModifiers;
	float								myAge = 0.f;
	float								myTimeSinceLastCreatedParticle = 0.f;
	Vector2f							myPosition;
	float								myDirection = 0.f;
	const ParticleEmitterBlueprint		*myBluePrint = nullptr;
	static Renderer*					ourRenderer;
};

