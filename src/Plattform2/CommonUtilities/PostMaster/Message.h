#pragma once
#include "MessageTypes.h"
#include <string>
#include <Vector2.h>
#include <Matrix44.h>

#pragma warning( push )
#pragma warning( disable : 26495)
struct Message
{
	Message() = default;

	Message(const eMessageTypes aMessageType)
	{
		myMessageType = aMessageType;
	}

	Message(const eMessageTypes aMessageType, const int aValue)
	{
		myMessageType = aMessageType;
		myIntData = aValue;
	}

	Message(const eMessageTypes aMessageType, const std::string& aString, const Vector2f& aPosition)
	{
		myMessageType = aMessageType;
		myText = aString;
		myPosition = aPosition;
	}

	CU::Matrix44f myMatrix;
	std::string myText;
	Vector2f myPosition;
	Vector2f myDirection;
	void* myVoidPointer = nullptr;

	union 
	{
		int myIntData;
		int myFirstColliderTag;
		float myFloatData;
		unsigned long myULong;
	};

	union
	{
		int mySecondIntData;
		int mySecondColliderTag;
	};

	eMessageTypes myMessageType;
};

#pragma warning( pop )