#include "stdafx.h"
#include "ParticleEmitter.h"
#include "Renderer.h"

Renderer* ParticleEmitter::ourRenderer = nullptr;

void ParticleEmitter::Update(const float aDeltaTime)
{
	myAge += aDeltaTime;
	myTimeSinceLastCreatedParticle += aDeltaTime;

	while (myTimeSinceLastCreatedParticle > 0.01f && myAge < myBluePrint->myMaxAge)
	{
		myTimeSinceLastCreatedParticle -= 0.01f;
		Particle newParticle;
		newParticle.myPosition = myPosition;
		newParticle.mySize = myBluePrint->myStartSize;
		newParticle.myColor = myBluePrint->myStartColor;
		myParticles[0].Add(newParticle);

		ParticleModifiers particleModifiers;
		const float randomizedDirection = myDirection + CU::RandomF(-myBluePrint->myRandomDirection, myBluePrint->myRandomDirection);
		particleModifiers.myVelocity.myX = myBluePrint->myInitVelocity.myX * cos(randomizedDirection) + myBluePrint->myInitVelocity.myY * sin(randomizedDirection);
		particleModifiers.myVelocity.myY = myBluePrint->myInitVelocity.myY * cos(randomizedDirection) + myBluePrint->myInitVelocity.myX * sin(randomizedDirection);
		myParticleModifiers.Add(particleModifiers);
	}

	for (int particleIndex = myParticles[0].Size() - 1; particleIndex >= 0; particleIndex--)
	{
		myParticleModifiers[particleIndex].myAge += aDeltaTime;
		myParticleModifiers[particleIndex].myVelocity.myY += (GRAVITY * static_cast<int>(myBluePrint->myGravity));
		myParticleModifiers[particleIndex].myVelocity *= myBluePrint->myDrag;
		const float agePercent = myParticleModifiers[particleIndex].myAge / myBluePrint->myParticleMaxAge;
		myParticles[0][particleIndex].myPosition += myParticleModifiers[particleIndex].myVelocity;
		myParticles[0][particleIndex].myColor = myBluePrint->myStartColor * (1.f - agePercent) + myBluePrint->myEndColor * agePercent;
		myParticles[0][particleIndex].mySize = myBluePrint->myStartSize * (1.f - agePercent) + myBluePrint->myEndSize * agePercent;
	}

	for (int particleIndex = myParticles[0].Size()-1; particleIndex >= 0; particleIndex--)
	{
		if (myParticleModifiers[particleIndex].myAge >= myBluePrint->myParticleMaxAge)
		{
			myParticleModifiers.RemoveCyclicAtIndex(particleIndex);
			myParticles[0].RemoveCyclicAtIndex(particleIndex);
		}
	}
}

void ParticleEmitter::Draw()
{
	DL_ASSERT(myBluePrint != nullptr && "PS not initiated with texture!");
	ourRenderer->AddPSRenderCommand({ &myParticles[0], myBluePrint->myTexture, static_cast<int>(myBluePrint->myBlendMode) });
}

void ParticleEmitter::Init(const ParticleEmitterBlueprint& aBluePrint, const Vector2f& aPosition, const Vector2f& aDirection)
{
	myDirection = atan2f(aDirection.myY, aDirection.myX);
	myBluePrint = &aBluePrint;
	myPosition = aPosition;
	myParticleModifiers.SetSafeMode(false);
	myParticles[0].SetSafeMode(false);
	myParticles[1].SetSafeMode(false);
}

bool ParticleEmitter::IsFinished() const
{
	return (myAge >= myBluePrint->myMaxAge && myParticles.Size() == 0);
}

void ParticleEmitter::SetRenderer(Renderer* aRenderer)
{
	DL_ASSERT(aRenderer != nullptr && "Renderer can't be nullptr!");
	ourRenderer = aRenderer;
}
