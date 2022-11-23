#pragma once
#include <..\external\rapidJSON\document.h>

namespace Helpers
{
	Vector4<float> GetVector4FromJSON(const char* aObjectName, const rapidjson::GenericObject<false, rapidjson::Value>& aObject);
	Vector3<float> GetVector3FromJSON(const char* aObjectName, const rapidjson::GenericObject<false, rapidjson::Value>& aObject);
	Vector2<float> GetVector2FromJSON(const char* aObjectName, const rapidjson::GenericObject<false, rapidjson::Value>& aObject);
}
