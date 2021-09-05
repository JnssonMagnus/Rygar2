#include "stdafx.h"
#include "TimeUnit.h"

namespace Timer
{
	TimeUnit::TimeUnit(const TimeType aTimeInMicroSeconds)
	{
		UpdateTime(aTimeInMicroSeconds);
	}

	void TimeUnit::UpdateTime(const TimeType aTimeInMicroSeconds)
	{
		myTimeInMicroSeconds = aTimeInMicroSeconds;
	}

	TimeUnit::~TimeUnit(void)
	{
	}
}