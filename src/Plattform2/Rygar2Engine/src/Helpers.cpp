#include "stdafx.h"
#include "Helpers.h"

namespace Helpers
{
	Vector4<float> GetVector4FromJSON(const char* aObjectName, const rapidjson::GenericObject<false, rapidjson::Value>& aObject)
	{
		const auto object = aObject.FindMember(aObjectName)->value.GetObject();
		return Vector4f(object.FindMember("x")->value.GetFloat(), 
			object.FindMember("y")->value.GetFloat(),
			object.FindMember("z")->value.GetFloat(),
			object.FindMember("w")->value.GetFloat());
	}

	Vector3<float> GetVector3FromJSON(const char* aObjectName, const rapidjson::GenericObject<false, rapidjson::Value>& aObject)
	{
		const auto object = aObject.FindMember(aObjectName)->value.GetObject();
		return Vector3f(object.FindMember("x")->value.GetFloat(),
			object.FindMember("y")->value.GetFloat(),
			object.FindMember("z")->value.GetFloat());
	}

	Vector2<float> GetVector2FromJSON(const char* aObjectName, const rapidjson::GenericObject<false, rapidjson::Value>& aObject)
	{
		const auto object = aObject.FindMember(aObjectName)->value.GetObject();
		return Vector2f(object.FindMember("x")->value.GetFloat(),
			object.FindMember("y")->value.GetFloat());
	}
}