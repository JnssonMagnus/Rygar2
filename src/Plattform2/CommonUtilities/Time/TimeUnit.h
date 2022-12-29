#pragma once

typedef long long TimeType;

namespace Timer
{
	class TimeUnit
	{
	public:
		TimeUnit(const TimeType aTimeInNanoSeconds);
		~TimeUnit(void);

		TimeType		GetHours() const;
		TimeType		GetSeconds() const;
		TimeType		GetMinutes() const;
		TimeType		GetMilliseconds() const;
		TimeType		GetMicroseconds() const;
		TimeType		GetNanoSeconds() const;
		TimeType		GetFPS() const;
		void			UpdateTime(const TimeType aTimeInNanoSeconds);

	private:
		TimeType		myTimeInNanoSeconds;

	};

	inline TimeType TimeUnit::GetHours() const
	{
		return myTimeInNanoSeconds / (6000000 * 60);
	}

	inline TimeType TimeUnit::GetMinutes() const
	{
		return myTimeInNanoSeconds / 6000000000;
	}

	inline TimeType TimeUnit::GetSeconds() const
	{
		return myTimeInNanoSeconds / 1000000000;
	}

	inline TimeType TimeUnit::GetMilliseconds() const
	{
		return myTimeInNanoSeconds / 1000000;
	}

	inline TimeType TimeUnit::GetMicroseconds() const
	{
		return myTimeInNanoSeconds / 1000;
	}

	inline TimeType TimeUnit::GetNanoSeconds() const
	{
		return myTimeInNanoSeconds;
	}

	inline TimeType TimeUnit::GetFPS() const
	{
		return 1000000 / GetMicroseconds();
	}


}
