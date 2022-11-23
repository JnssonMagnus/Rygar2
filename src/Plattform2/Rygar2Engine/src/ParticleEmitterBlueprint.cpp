#include "stdafx.h"
#include "ParticleEmitterBlueprint.h"
#include "Helpers.h"
#include "ResourceManager.h"

eBlendMode StringToBlendMode(const char* aBlendString)
{
	if (strcmp(aBlendString, "none"))
	{
		return eBlendMode::eNone;
	}
	else if (strcmp(aBlendString, "normal"))
	{
		return eBlendMode::eNormal;
	}
	else if (strcmp(aBlendString, "add"))
	{
		return eBlendMode::eAdd;
	}
	else if (strcmp(aBlendString, "multiply"))
	{
		return eBlendMode::eMultiply;
	}
		
	DL_ASSERT(false && "Unknown blend mode found!");

	return eBlendMode::eNormal;
}

void ParticleEmitterBlueprint::Init(const rapidjson::GenericObject<false, rapidjson::Value>& aObject)
{
#ifdef _DEBUG
	myName = aObject.FindMember("name")->value.GetString();
#endif	
	myStartColor = Helpers::GetVector4FromJSON("startColor", aObject);
	myEndColor = Helpers::GetVector4FromJSON("endColor", aObject);

	myStartSize = Helpers::GetVector2FromJSON("startSize", aObject);
	myEndSize = Helpers::GetVector2FromJSON("endSize", aObject);
	myMaxAge = aObject.FindMember("maxAge")->value.GetFloat();
	myDrag = aObject.FindMember("drag")->value.GetFloat();
	myTexture = ResourceManager::GetInstance()->GetTexture(aObject.FindMember("image")->value.GetString());
	myParticleMaxAge = aObject.FindMember("particleMaxAge")->value.GetFloat();
	myInitVelocity = Helpers::GetVector2FromJSON("initVelocity", aObject);
	myGravity = aObject.FindMember("gravity")->value.GetBool();
	myRandomDirection = CU::DegToRad(aObject.FindMember("randomDirection")->value.GetFloat());
	myBlendMode = StringToBlendMode(aObject.FindMember("blending")->value.GetString());
}
