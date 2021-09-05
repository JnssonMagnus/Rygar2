#include "stdafx.h"
#include "CommandLineManager.h"

namespace CommonUtilities
{
	CommandLineManager* CommandLineManager::ourInstance = nullptr;

	CommandLineManager::CommandLineManager()
	{
		std::string commandLine = GetCommandLineA();
		for (std::string::size_type index = FindNextParameter(commandLine, 0); index < commandLine.size(); ++index)
		{
			std::string::size_type parameterEndIndex = commandLine.find(' ', index + 1);
			std::string parameter = commandLine.substr(index + 1, parameterEndIndex - index - 1);
			index = parameterEndIndex;

			while (FindNextArgument(commandLine, index) != std::string::npos)
			{
				std::string::size_type argumentIndexStart = FindNextArgument(commandLine, index);
				std::string::size_type argumentEndIndex = commandLine.find(" ", argumentIndexStart);

				std::string argument = commandLine.substr(argumentIndexStart, argumentEndIndex - argumentIndexStart);
				index = argumentEndIndex == std::string::npos ? commandLine.size() : argumentEndIndex;

				myCommandLines[parameter].insert(argument);
			}
		}
	}

	CommandLineManager::~CommandLineManager()
	{
	}

	std::string::size_type CommandLineManager::FindNextParameter(const std::string& aCommandLine, std::string::size_type aCurrentIndex) const
	{
		return aCommandLine.find("-", aCurrentIndex);
	}

	std::string::size_type CommandLineManager::FindNextArgument(const std::string& aCommandLine, std::string::size_type aCurrentIndex) const
	{
		for (std::string::size_type index = aCurrentIndex; index < aCommandLine.size(); ++index)
		{
			if (aCommandLine[index] == ' ')
			{
				if (aCommandLine[index + 1] == '-')
					break;
				return index + 1;
			}
		}

		return std::string::npos;
	}

	bool CommandLineManager::HasParameter(const char* aParameter)
	{
		return ( myCommandLines.find(aParameter) != myCommandLines.end() );
	}

	bool CommandLineManager::HasArgument(const char* aParameter, const char* aArgument)
	{
		if (HasParameter(aParameter) == true)
		{
			return myCommandLines[aParameter].find(aArgument) != myCommandLines[aParameter].end();
		}
		else
		{
			return false;
		}
	}
	CommandLineManager& CommandLineManager::GetInstance()
	{
		assert(ourInstance != nullptr && "CommandLineManager not created!");
		return *ourInstance;
	}

	void CommandLineManager::Destroy()
	{
		assert(ourInstance != nullptr && "Can't destroy CommandLineManager. Not created!");
	}

	void CommandLineManager::Create()
	{
		assert(ourInstance == nullptr && "CommandLineManager already created!");
		ourInstance = new CommandLineManager();
	}
}

namespace CU = CommonUtilities;