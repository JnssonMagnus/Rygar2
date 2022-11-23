#include "stdafx.h"
#include "ParticleSystem.h"
#include "ParticleEmitter.h"

void ParticleSystem::Init(Renderer* aRenderer)
{
	ParticleEmitter::SetRenderer(aRenderer);
	PostMaster::GetInstance()->Register(this, eMessageTypes::eCreateParticleSystem);
}

void ParticleSystem::LoadParticleEmitterBlueprints(const char* aFilePath)
{
	std::ifstream file(aFilePath);
	DL_ASSERT(file.is_open() == true && "Can't open file path to particle emitter blueprints!");
	std::string text((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	rapidjson::Document particleBlueprints;
	particleBlueprints.Parse(text.c_str());
	DL_ASSERT(particleBlueprints.HasParseError() == false && "Error while reading ParticleEmitterBlueprints.json!");

	for (auto it = particleBlueprints.Begin(); it != particleBlueprints.End(); it++)
	{
		ParticleEmitterBlueprint newType;
		newType.Init(it->GetObject());
		myBlueprints.Add(newType);
	}
}

void ParticleSystem::Update(const float aDeltaTime)
{
	for (int emitterIndex = myParticleEmitters.Size() - 1; emitterIndex >= 0; emitterIndex--)
	{
		myParticleEmitters[emitterIndex]->Update(aDeltaTime);
		if (myParticleEmitters[emitterIndex]->IsFinished())
		{
			myParticleEmitters.RemoveCyclicAtIndex(emitterIndex);
		}
	}
}

void ParticleSystem::Draw()
{
	for (int emitterIndex = 0; emitterIndex < myParticleEmitters.Size(); emitterIndex++)
	{
		myParticleEmitters[emitterIndex]->Draw();
	}
}

void ParticleSystem::RecieveMessage(const Message& aMessage)
{
	ParticleEmitter* particleEmitter = new ParticleEmitter();
	DL_ASSERT(aMessage.myIntData >= 0 && aMessage.myIntData < myBlueprints.Size() && "Particle blueprint unknown ID!");	
	particleEmitter->Init(myBlueprints[aMessage.myIntData], aMessage.myPosition, aMessage.myDirection);
	myParticleEmitters.Add(particleEmitter);
}
