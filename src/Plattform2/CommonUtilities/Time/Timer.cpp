#include "stdafx.h"
#include "Timer.h"

namespace Timer
{
	Timer::Timer(double aStartTime) : myFrameTime(0)
	{
		myLifeTime = aStartTime;
		myOn = true;
	}

	Timer::~Timer(void)
	{
	}

	void Timer::AddTime(double aTime)
	{
		if (myOn == true)
		{
			myLifeTime += aTime;
			myFrameTime.UpdateTime(static_cast<TimeType>(aTime));
		}
	}
}