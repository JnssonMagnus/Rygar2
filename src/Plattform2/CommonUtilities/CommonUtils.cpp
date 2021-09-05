#include "stdafx.h"
#include "CommonUtils.h"
#include <intrin.h>
#include <random>

namespace CommonUtilities
{
	std::wstring CharToWChar(const std::string& aString)
	{
		std::wstring wc(aString.size(), L'#');
		mbstowcs( &wc[0], aString.c_str(), aString.size());
		return wc;
	}

	float RandomF(const float aFrom, const float aTo)
	{
		static std::random_device seed;
		static std::mt19937 rndEngine(seed());
		std::uniform_real_distribution<float> dist{ aFrom, aTo };
		return dist(rndEngine);
	}


	std::string GetCPUName()
	{
		// Get extended ids.
		int CPUInfo[4] = { -1 };
		__cpuid(CPUInfo, 0x80000000);
		unsigned int nExIds = CPUInfo[0];

		// Get the information associated with each extended ID.
		char CPUBrandString[0x40] = { 0 };
		for (unsigned int i = 0x80000000; i <= nExIds; ++i)
		{
			__cpuid(CPUInfo, i);

			// Interpret CPU brand string and cache information.
			if (i == 0x80000002)
			{
				memcpy(CPUBrandString,
					CPUInfo,
					sizeof(CPUInfo));
			}
			else if (i == 0x80000003)
			{
				memcpy(CPUBrandString + 16,
					CPUInfo,
					sizeof(CPUInfo));
			}
			else if (i == 0x80000004)
			{
				memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
			}
		}

		return CPUBrandString;
	}
}

namespace CU = CommonUtilities;

int Random(const int aMin, const int aMax)
{
	static std::random_device seed;
	static std::mt19937 rndEngine(seed());
	std::uniform_int_distribution<int> dist{ aMin, aMax };

	return dist(rndEngine);
}
