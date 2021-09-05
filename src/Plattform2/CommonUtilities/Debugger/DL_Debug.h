#pragma once
#include <string>
#include <fstream>
#include <map>

#define DL_ASSERT(_Expression) (void)( (!!(_Expression)) || (DL_Debug::Debug::GetInstance()->AssertMessage(__FILE__,__LINE__,__FUNCTION__, #_Expression), 0) );
#define DL_PRINT(string)  DL_Debug::Debug::GetInstance()->PrintMessage(string);
#define DL_DEBUG(...)  DL_Debug::Debug::GetInstance()->DebugMessage(__LINE__,__FUNCTION__,__VA_ARGS__);

#define DL_WRITELOG(logType, ...)  DL_Debug::Debug::GetInstance()->WriteLog(logType, __VA_ARGS__);
#ifdef USE_FILTERLOG
	#define RESOURCE_LOG(...) DL_WRITELOG("Resource", __VA_ARGS__)
	#define ENGINE_LOG(...) DL_WRITELOG("Engine", __VA_ARGS__)
	#define INGAME_LOG(...) DL_WRITELOG("Ingame", __VA_ARGS__)

#else
	#define RESOURCE_LOG(...)
	#define ENGINE_LOG(...)
	#define INGAME_LOG(...)
#endif

std::string GetClock();

namespace DL_Debug

{
	class Debug
	{
	public:
		static Debug*		GetInstance();
		static void			Create (const std::string &aFilename = "DebugLogger.txt");
		static void			Destroy();
		void				Init();

		void				PrintMessage(const std::string& aString);
		void				AssertMessage(const std::string& aFile, unsigned int aLine, const std::string& aFunction,const std::string& aMessage);
		void				DebugMessage(unsigned int aLine, const std::string& aFunction, const char *aFormat, ...);

		void				WriteLog(const char* aLogType, const char* aFormat, ...);
		void				ActivateFilterLog(const char* aLogType);
		void				DeactivateFilterLog(const char* aLogType);

	private:
							Debug(void);
							~Debug(void);
		void				CreateConsole();

		void				WriteToConsole(const char* aMessage);
		void				WriteToLogfile(const char* aMessage);

		std::map<std::string, std::ofstream>
							myLogStreams;
		std::ofstream		myFileStream;
		static Debug		*ourInstance;



	};
}
