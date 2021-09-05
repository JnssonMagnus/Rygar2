#include "stdafx.h"
#include "ExceptionHandler.h"
#include "DL_Assert.h"
#include "../CommonUtils.h"
#include <DbgHelp.h>
#include <iostream>
#pragma comment(lib, "dbghelp.lib")

namespace DL_Debug
{
	void CreateMiniDump(EXCEPTION_POINTERS* someExceptionPointers)
	{
		MessageBoxW(nullptr, L"Program crashed! Minidump was created at logs/ErrorDump.dmp", L"Crash!", 0x00000000L);
		MINIDUMP_TYPE type = (MINIDUMP_TYPE)( // MiniDumpWithFullMemory |
			MiniDumpWithFullMemoryInfo |
			MiniDumpWithHandleData |
			MiniDumpWithThreadInfo |
			MiniDumpWithUnloadedModules);
		MINIDUMP_EXCEPTION_INFORMATION exception;
		exception.ExceptionPointers = someExceptionPointers;
		exception.ThreadId = GetCurrentThreadId();
		exception.ClientPointers = false;

		std::ofstream crashInfo;
		crashInfo.open("log/CrashInformation.txt", std::ofstream::out);
		
		MEMORYSTATUSEX status;
		status.dwLength = sizeof(status);
		GlobalMemoryStatusEx(&status);

		crashInfo << "Crashed " << __TIME__ << std::endl;
		crashInfo << "Exe created " << __DATE__ << std::endl;
		crashInfo << "File last changed " << __TIMESTAMP__ << std::endl;
		crashInfo << "Available memory: " << status.ullAvailPhys / 1000000.f << "MB of total " << status.ullTotalPhys / 1000000.f << std::endl;
		crashInfo << "CPU: " << CU::GetCPUName() << std::endl;

		crashInfo.close();			   		 

		HANDLE hFile = CreateFile(L"log/ErrorDump.dmp", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		assert(hFile != INVALID_HANDLE_VALUE && "Can't open or create logs/ErrorDump.dmp");
		bool result = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, type, &exception, nullptr, nullptr);
		(result); // remove warning on unused variable in release
		assert(result == true && "Failed to create minidump!");

		CloseHandle(hFile);
	}

	LONG WINAPI ExceptionFilterFunction(_EXCEPTION_POINTERS* aExceptionP)
	{
		CreateMiniDump(aExceptionP);
		return EXCEPTION_EXECUTE_HANDLER;
	}
}