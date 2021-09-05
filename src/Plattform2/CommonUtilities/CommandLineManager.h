#pragma once
#include <string>
#include <map>
#include <set>
#include <Windows.h>

namespace CommonUtilities
{
	class CommandLineManager
	{
	public:
		bool							HasParameter(const char* aParameter);
		bool							HasArgument(const char* aParameter, const char* aArgument);
		static CommandLineManager&		GetInstance();
		static void						Destroy();
		static void						Create();

	private:
										CommandLineManager();
										~CommandLineManager();
		std::map<std::string, std::set<std::string>> myCommandLines;
		static CommandLineManager*		ourInstance;
		std::string::size_type			FindNextParameter(const std::string& aCommandLine, std::string::size_type aCurrentIndex) const;
		std::string::size_type			FindNextArgument(const std::string& aCommandLine, std::string::size_type aCurrentIndex) const;
	};
}

namespace CU = CommonUtilities;