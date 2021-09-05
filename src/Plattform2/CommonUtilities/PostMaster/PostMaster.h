#pragma once
#include "MessageTypes.h"
#include "Message.h"
#include <GrowingArray.h>
#include <unordered_map>
#include <sstream>
#include <functional>

class Entity;
class Observer;
struct Message;

namespace CommonUtilities
{
	template<class T>
	class Matrix44;
}

namespace CU = CommonUtilities;

typedef std::unordered_map<eMessageTypes, CU::GrowingArray<Observer*>> ObserverType;

namespace Physics
{
	struct CollisionData;
}

#undef SendMessage

class PostMaster
{
public:
	void					operator=(const PostMaster&) = delete;
	static PostMaster*		GetInstance();
	void					Destroy();
	void					Register(Observer* aObserver, const eMessageTypes aMessageType);
	void					Unregister(Observer* aObserver, const eMessageTypes aMessageType);
	void					SendSoundEvent(const char* aSoundEvent, int aSoundObjectID=0);
	void					SendSoundEvent(const char* aSoundEvent, const CU::Matrix44<float>& aMatrix);
	void					SendSoundEvent(const char* aSoundEvent, const Vector2f& aPosition);
	void					SendMessage(const Message& aMessage);
	void					SendDelayedMessage(const Message& aMessage);
	void					SendMessage(const eMessageTypes aMessageType);
	void					AddColliderResponse(int aCollisionTag, int aCollisionTag2, std::function<void(Physics::CollisionData& aCollisionData)>& aFunction);
	void					SendDelayedMessages();

	template<typename... values>
	void					SendTextMessage(const values...);

private:
							PostMaster();
							~PostMaster();

	template<typename T, typename... values>
	void					ReadNextTemplateArg(std::stringstream& aStringStream, unsigned long &aTint, T aMessage, values... someValues);

	template<typename T>
	void					ReadNextTemplateArg(std::stringstream& aStringStream, unsigned long &aTint, T aMessage);

	void					ReadNextTemplateArg(std::stringstream& aStringStream, unsigned long &aTintToSet, unsigned long aTint);

	static PostMaster*		myInstance;
	ObserverType			myObservers;
	CU::GrowingArray<Message> myDelayedMessages;
};

template<typename T, typename... values>
void PostMaster::ReadNextTemplateArg(std::stringstream& aStringStream, unsigned long &aTint, T aMessage, values... someValues)
{
	aStringStream << aMessage;
	ReadNextTemplateArg(aStringStream, aTint, someValues...);
}

template<typename T>
void PostMaster::ReadNextTemplateArg(std::stringstream& aStringStream, unsigned long &aTint, T aMessage)
{
	aStringStream << aMessage;
}

template<typename... values>
void PostMaster::SendTextMessage(const values... someValues)
{
	Message message;
	message.myMessageType = eTextMessage;
	std::stringstream ss;
	unsigned long tint = 0xffffffff;
	ReadNextTemplateArg(ss, tint, someValues...);
	message.myText = ss.str();
	message.myULong = tint;
	SendMessage(message);
}