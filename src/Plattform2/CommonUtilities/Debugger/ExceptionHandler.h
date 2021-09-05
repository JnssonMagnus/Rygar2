#pragma once
#include <Windows.h>

namespace DL_Debug
{
#define CATCH_EXCEPTION(_x) __try{ _x }	__except (DL_Debug::ExceptionFilterFunction( GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER) {	}

	void CreateMiniDump(EXCEPTION_POINTERS* someExceptionPointers);
	LONG WINAPI ExceptionFilterFunction(_EXCEPTION_POINTERS* aExceptionP);
}