#include "stdafx.h"
#include "DL_Debug.h"
#include "ReleaseAssert.h"
#include "DL_StackWalker.h"
#include "ReleaseAssert.h"
#include "..\CommandLineManager.h"
#include "..\CommonUtils.h"
#include <stdarg.h>
#include <iostream>
#include <sstream>
#include <time.h>

namespace DL_Debug
{
	Debug* Debug::ourInstance = nullptr;

	Debug::Debug(void)
	{
	}

	Debug::~Debug(void)
	{
		myFileStream.close();
	}

	Debug* Debug::GetInstance()
	{
		assert(ourInstance != nullptr && "Debug not created.");
		return ourInstance;
	}

	void Debug::Create(const std::string& aFilename)
	{
		assert(ourInstance == nullptr && "Debug already created.");
		ourInstance = new Debug();
		// TODO! If path "Log" doesn't exist, create directory from code
		ourInstance->myFileStream.open(aFilename);
		if (ourInstance->myFileStream.is_open() == false)
		{
			size_t split = aFilename.find_last_of("/");
			std::string missingDir = aFilename.substr(0, split);
			std::wstring missingDirW = CommonUtilities::CharToWChar(missingDir);
			bool result = CreateDirectory(missingDirW.c_str(), nullptr);
			assert(result == true && "Debug couldn't create directory.");
			ourInstance->myFileStream.open(aFilename);
		}
		assert (ourInstance->myFileStream.is_open() == true && "Debug couldn't create file.");
#ifndef NDEBUG
		ourInstance->CreateConsole();
#endif
	}

	void Debug::Destroy()
	{
		assert(ourInstance != nullptr && "Debug not created.");
		delete ourInstance;
		ourInstance = nullptr;
	}

	void Debug::Init()
	{
		if (CU::CommandLineManager::GetInstance().HasArgument("activatelog", "engine") == true)
		{
			ActivateFilterLog("Engine");
		}
		if (CU::CommandLineManager::GetInstance().HasArgument("activatelog", "resource") == true)
		{
			ActivateFilterLog("Resource");
		}
		if (CU::CommandLineManager::GetInstance().HasArgument("activatelog", "ingame") == true)
		{
			ActivateFilterLog("Ingame");
		}
	}

	void Debug::PrintMessage(const std::string& aString)
	{
		WriteToConsole(aString.c_str());
		WriteToLogfile(aString.c_str());
	}

	void Debug::DebugMessage(unsigned int aLine, const std::string& aFunction, const char *aFormat, ...)
	{
		char buffer[1024];
		va_list args;
		va_start(args, aFormat);
		vsprintf_s(buffer, aFormat, args);
		va_end(args);

		std::stringstream message;
		message << "[DEBUG] [LINE: " << aLine << "] [FUNCTION: " << aFunction << "]  " << buffer;

		WriteToConsole(message.str().c_str());
		WriteToLogfile(message.str().c_str());
	}

	void Debug::WriteLog(const char* aLogType, const char* aFormat, ...)
	{
		auto it = myLogStreams.find(aLogType);
		if (it != myLogStreams.end())
		{
			char buffer[1024];
			va_list args;
			va_start(args, aFormat);
			vsprintf_s(buffer, aFormat, args);
			va_end(args);

			std::stringstream message;
			message << "[" << GetClock() << "][" << aLogType << "] - " << buffer << std::endl;

			std::cout << message.str();
			it->second << message.str();
			it->second.flush();
		}
	}

	void Debug::ActivateFilterLog(const char* aLogType)
	{
		auto fileStreamIterator = myLogStreams.find(aLogType);
		if (fileStreamIterator == myLogStreams.end())
		{
			std::stringstream filename;
			filename << "log/" << aLogType << "_log.txt";
			myLogStreams[aLogType].open(filename.str());
			DL_ASSERT(myLogStreams[aLogType].is_open() == true && "Debug couldn't create log filter file.");
		}
	}

	void Debug::DeactivateFilterLog(const char* aLogType)
	{
		auto fileStreamIterator = myLogStreams.find(aLogType);
		if (fileStreamIterator != myLogStreams.end())
		{
			fileStreamIterator->second.close();
			myLogStreams.erase(fileStreamIterator);
		}
	}

	void Debug::AssertMessage(const std::string& aFile, unsigned int aLine, const std::string& aFunction,const std::string& aMessage)
	{
		std::stringstream message;
		
		message << "Asserted in: " << aFile << std::endl;
		message << "Line: " << aLine << std::endl;
		message << "Function: " << aFunction << std::endl;
		message << "Assert msg: " << aMessage << std::endl << std::endl;
		message << "Call Stack:" << std::endl;

		WriteToConsole(message.str().c_str());
		WriteToLogfile(message.str().c_str());

		DL_Debug::StackWalker sw;
		sw.ShowCallstack();
		assert(false && aMessage.c_str());	
	}

#pragma warning(disable:4996)
	void Debug::CreateConsole()
	{
		AllocConsole();
		freopen("conin$", "r", stdin);
		freopen("conout$", "w", stdout);
		freopen("conout$", "w", stderr); 
		HWND console = GetConsoleWindow();
		RECT r;
		GetWindowRect(console, &r); 
		MoveWindow(console, r.left, r.top, 800, 600, TRUE);

		DL_DEBUG("Console created.");
	}

	void Debug::WriteToConsole(const char* aMessage)
	{
		(aMessage);
#ifndef NDEBUG
		std::cout << aMessage << std::endl;
#endif
	}

	void Debug::WriteToLogfile(const char* aMessage)
	{
		myFileStream << aMessage << std::endl;
		myFileStream.flush();
	}
}

std::string GetClock()
{
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	std::stringstream time;
	time << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec;

	return time.str();
}
