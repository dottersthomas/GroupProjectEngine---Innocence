#pragma once

#include <lua.hpp>
#include <LuaBridge.h>
#include "LuaEngine.h"

/// <summary>
/// Provides helper functions that allow for interaction between Lua and C++.
/// </summary>
class LuaHelper
{
public:
	/// <summary>
	/// Converts an std container into a Lua table.
	/// </summary>
	/// <param name="container">The container.</param>
	/// <returns>luabridge::LuaRef</returns>
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

	/// <summary>
	/// Registers a component or components as a global variable in Lua.
	/// </summary>
	/// <param name="go">The GameObject the component is being registered to.</param>
	/// <param name="findAll">if set to <c>true</c> find all components of the type specified.</param>
	/// <param name="globalName">Name of the global variable the component should be registered to.</param>
	/// <returns>luabridge::LuaRef</returns>

	template<typename T>
	static luabridge::LuaRef GetGlobalComponent(GameObject& go, bool findAll, const char* globalName, const char* tag)
	{
		// Get lua state
		auto L = LuaEngine::getInstance().L();

		// Register global
		if (findAll)
		{
			auto vec = go.GetComponentsByType<T>();
			// Check for tag
			if (tag != "")
			{
				// Find by tag
				std::vector<T*> elements;

				for (auto& e : vec)
				{
					if (static_cast<Component*>(e)->getTag() == tag)
						elements.push_back(e);
				}

				luabridge::setGlobal(L, LuaHelper::ToTable(elements), globalName);
			}
			else
				luabridge::setGlobal(L, LuaHelper::ToTable(vec), globalName);
		}
		else
			luabridge::setGlobal(L, go.GetComponentByType<T>(), globalName);

		return luabridge::getGlobal(L, globalName);
	}
};
