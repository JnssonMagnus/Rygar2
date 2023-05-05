#include "stdafx.h"
#include "Variable.h"

void VariableContainer::LoadJSON(const rapidjson::GenericArray<false, rapidjson::Value>& aVariables)
{
	for (auto var = aVariables.Begin(); var != aVariables.End(); var++)
	{
		auto object = var->GetObject();
		const std::string varName = object.FindMember("name")->value.GetString();
		const VariableTypes varType = static_cast<VariableTypes>(object.FindMember("type")->value.GetInt());
		switch (varType)
		{
		case VariableTypes::s:
		{
			const std::string stringValue = object.FindMember("stringValue")->value.GetString();
			myVariables[varName] = stringValue;
			break;
		}
		case VariableTypes::i:
		{
			const int intValue = object.FindMember("intValue")->value.GetInt();
			myVariables[varName] = intValue;
			break;
		}
		case VariableTypes::d:
		{
			const double doubleValue = object.FindMember("doubleValue")->value.GetDouble();
			myVariables[varName] = static_cast<float>(doubleValue);
			break;
		}
		}
		
	}
}