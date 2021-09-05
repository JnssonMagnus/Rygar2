#include "stdafx.h"
#include "Subject.h"
#include "observer.h"


Subject::Subject()
{
}

Subject::~Subject()
{
}

void Subject::AttachObserver(const eMessageTypes aMessageType, Observer *aObserver)
{
	myObservers[aMessageType].Add(aObserver);
}

void Subject::DetachObserver(const eMessageTypes aMessageType, Observer *aObserver)
{
	myObservers[aMessageType].RemoveCyclic(aObserver);
}

void Subject::Notify(const eMessageTypes aMessageType, int aValue)
{
	Message message(aMessageType, aValue);
	for (int i = 0; i < myObservers[aMessageType].Size(); ++i)
	{
		(myObservers[aMessageType])[i]->RecieveMessage(message);
	}
}
	  