#pragma once
#include "Message.h"

class Observer
{
public:
	virtual void		RecieveMessage(const Message& aAction) = 0;

};

