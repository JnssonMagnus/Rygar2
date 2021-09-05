#pragma once

typedef unsigned int TimeType;

namespace Timer
{
	class TimeUnit
	{
	public:
		TimeUnit(const TimeType aTimeInMicroSeconds);
		~TimeUnit(void);

		TimeType		GetHours() const;
		TimeType		GetSeconds() const;
		TimeType		GetMinutes() const;
		TimeType		GetMilliseconds() const;
		TimeType		GetMicroseconds() const;
		TimeType		GetFPS() const;
		void			UpdateTime(const TimeType aTimeInMicroSeconds);

	private:
		TimeType		myTimeInMicroSeconds;

	};

	inline TimeType TimeUnit::GetHours() const
	{
		return myTimeInMicroSeconds / (6000000 * 60);
	}

	inline TimeType TimeUnit::GetMinutes() const
	{
		return myTimeInMicroSeconds / 6000000;
	}

	inline TimeType TimeUnit::GetSeconds() const
	{
		return myTimeInMicroSeconds / 1000000;
	}

	inline TimeType TimeUnit::GetMilliseconds() const
	{
		return myTimeInMicroSeconds / 1000;
	}

	inline TimeType TimeUnit::GetMicroseconds() const
	{
		return myTimeInMicroSeconds;
	}

	inline TimeType TimeUnit::GetFPS() const
	{
		return 1000000 / myTimeInMicroSeconds;
	}


}
