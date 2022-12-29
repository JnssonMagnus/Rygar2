#include "stdafx.h"
#include "TimeUnit.h"

namespace Timer
{
	TimeUnit::TimeUnit(const TimeType aTimeInNanoSeconds)
	{
		UpdateTime(aTimeInNanoSeconds);
	}

	void TimeUnit::UpdateTime(const TimeType aTimeInNanoSeconds)
	{
		myTimeInNanoSeconds = aTimeInNanoSeconds;
	}

	TimeUnit::~TimeUnit(void)
	{
	}
}