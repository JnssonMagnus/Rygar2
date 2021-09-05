#pragma once
#include "ParticleEmitterBlueprint.h"

class ParticleEmitter;
class Renderer;

class ParticleSystem : public Observer
{
public:
					ParticleSystem() = default;
					~ParticleSystem() = default;
					ParticleSystem(const ParticleSystem&) = delete;
	ParticleSystem& operator=(const ParticleSystem&) = delete;

	void			RecieveMessage(const Message& aMessage) override;

	void			Update(const float aDeltaTime);
	void			Draw();
	void			Init(Renderer* aRenderer);
	void			LoadParticleEmitterBlueprints(const char* aFilePath);

private:
	CU::GrowingArray<ParticleEmitter*>
					myParticleEmitters;
	CU::GrowingArray<ParticleEmitterBlueprint>
					myBlueprints;
};

