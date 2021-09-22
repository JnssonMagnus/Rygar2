#pragma once
#include <memory>
extern "C"
{
#include "lauxlib.h"
}

struct lua_State;


class LuaManager
{
public:
	typedef int(CallFunction)(lua_State*);
	void Init();

	template<class T>
	void RegisterFunction(const char* aLuaName, T aFunction);

	int SelfCall(lua_State* aLuaState);

private:
	lua_State* myLuaState = nullptr;

};

template<class T>
inline void LuaManager::RegisterFunction(const char* aLuaName, T aFunction)
{
	//lua_pushlightuserdata(myLuaState, this);
	//lua_pushcclosure(myLuaState, &LuaManager::SelfCall, 1);
	//lua_register(myLuaState, aLuaName, aFunction);
}
