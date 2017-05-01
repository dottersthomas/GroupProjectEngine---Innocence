#pragma once

#include <lua.hpp>
#include <LuaBridge.h>

class LuaHelper
{
public:
	// Converts an std container into a lua table
	template<typename T>
	static luabridge::LuaRef ToTable(T& container)
	{
		// Get lua state
		auto L = LuaEngine::getInstance().L();

		// Create table
		auto table = luabridge::newTable(L);

		// Fill table
		for each (auto& e in container)
			table.append(e);

		// Return table
		return table;
	}

	// Registers a component or components as a global variable in lua
	template<typename T>
	static luabridge::LuaRef GetGlobalComponent(GameObject& go, bool findAll, const char* globalName)
	{
		// Get lua state
		auto L = LuaEngine::getInstance().L();

		// Register global
		if (findAll)
		{
			auto vec = go.GetComponentsByType<T>();
			luabridge::setGlobal(L, LuaHelper::ToTable(vec), globalName);
		}
		else
			luabridge::setGlobal(L, go.GetComponentByType<T>(), globalName);

		return luabridge::getGlobal(L, globalName);
	}
};
