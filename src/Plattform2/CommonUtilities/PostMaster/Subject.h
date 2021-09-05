#pragma once
#include "MessageTypes.h"
#include <GrowingArray.h>
#include <map>

class Observer;

class Subject
{
public:
								Subject();
								~Subject();
	void						AttachObserver(const eMessageTypes aMessageType, Observer *aObserver);
	void						DetachObserver(const eMessageTypes aMessageType, Observer *aObserver);
	void						Notify(const eMessageTypes aMessageType, int aValue);

private:
	std::map<eMessageTypes, CU::GrowingArray<Observer*>> myObservers;
};

