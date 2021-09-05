#pragma once
#include <string>

namespace CommonUtilities
{
	std::wstring CharToWChar(const std::string& aString);
	std::string GetCPUName();
	float RandomF(const float aFrom, const float aTo);
	int Random(const int aMin, const int aMax);

	template<class T>
	T DegToRad(const T aDegree)
	{
		return (aDegree / 360) * PI * 2;
	}
}

inline constexpr unsigned char operator "" _uc(unsigned long long arg) noexcept
{
	return static_cast<unsigned char>(arg);
}


namespace CU = CommonUtilities;


