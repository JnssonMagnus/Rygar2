#include "stdafx.h"
#include "LuaManager.h"

int Apa(lua_State* aLuaState)
{
	std::cout << "apa" << std::endl;
	return 0;
}


void LuaManager::Init()
{
	myLuaState = luaL_newstate();
	DL_ASSERT(myLuaState != nullptr && "Failed to init lua!");
	DL_PRINT("Lua initiated!");
	
	RegisterFunction("test", &LuaManager::SelfCall);


	lua_getglobal(myLuaState, "test");
	lua_pcall(myLuaState, 0, 0, 0);
}

int LuaManager::SelfCall(lua_State* aLuaState)
{
	std::cout << "A winner is you!" << std::endl;
	return 0;
}
