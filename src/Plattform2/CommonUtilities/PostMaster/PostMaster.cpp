#include "stdafx.h"
#include "PostMaster.h"
#include "Message.h"
#include "Observer.h"
#include <sstream>

PostMaster* PostMaster::myInstance = nullptr;

PostMaster::PostMaster()
{
}

PostMaster::~PostMaster()
{
}

PostMaster* PostMaster::GetInstance()
{
	if (myInstance == nullptr)
	{
		myInstance = new PostMaster();
	}

	return myInstance;
}

void PostMaster::Destroy()
{
	assert(myInstance != nullptr && "No instance of Postmaster exists!");
	delete myInstance;
	myInstance = nullptr;
}

void PostMaster::SendSoundEvent(const char* aSoundEvent, int aSoundObjectID)
{
	Message message;
	message.myMessageType = eMessageTypes::ePlaySoundEvent;
	message.myIntData = aSoundObjectID;
	message.myText = aSoundEvent;
	SendMessage(message);
}

void PostMaster::SendSoundEvent(const char* aSoundEvent, const CU::Matrix44<float>& aMatrix)
{
	Message message;
	message.myMessageType = eMessageTypes::ePlaySoundEvent;
	message.myIntData = -1;
	message.myMatrix = aMatrix;
	message.myText = aSoundEvent;
	SendMessage(message);
}

void PostMaster::SendSoundEvent(const char* aSoundEvent, const Vector2f& aPosition)
{
	CU::Matrix44f position;
	position.Translate(aPosition.myX, aPosition.myY, 0.f);
	SendSoundEvent(aSoundEvent, position);
}


void PostMaster::Register(Observer* aObserver, const eMessageTypes aMessageType)
{
	myObservers[aMessageType].Add(aObserver);
}

void PostMaster::Unregister(Observer* aObserver, const eMessageTypes aMessageType)
{
	myObservers[aMessageType].RemoveCyclic(aObserver);
}

void PostMaster::SendMessage(const Message& aMessage)
{
	CU::GrowingArray<Observer*>& observers = myObservers[aMessage.myMessageType];
	for (int i = 0; i < observers.Size(); ++i)
	{
		observers[i]->RecieveMessage(aMessage);
	}
}

void PostMaster::SendDelayedMessage(const Message& aMessage)
{
	myDelayedMessages.Add(aMessage);
}

void PostMaster::SendMessage(const eMessageTypes aMessageType)
{
	Message msg;
	msg.myMessageType = aMessageType;
	SendMessage(msg);	
}


void PostMaster::AddColliderResponse(int aCollisionTag, int aCollisionTag2, std::function<void(Physics::CollisionData& aCollisionData)>& aFunction)
{
	Message msg;
	msg.myFirstColliderTag = aCollisionTag;
	msg.mySecondColliderTag = aCollisionTag2;
	msg.myVoidPointer = &aFunction;
	msg.myMessageType = eMessageTypes::eAddCollisionResponse;
	SendMessage(msg);
}

void PostMaster::SendDelayedMessages()
{
	for (int messageIndex = 0; messageIndex < myDelayedMessages.Size(); ++messageIndex)
	{
		SendMessage(myDelayedMessages[messageIndex]);
	}

	myDelayedMessages.Clear();
}

void PostMaster::ReadNextTemplateArg(std::stringstream& aStringStream, unsigned long &aTintToSet, unsigned long aTint)
{
	(aStringStream);
	aTintToSet = aTint;
}