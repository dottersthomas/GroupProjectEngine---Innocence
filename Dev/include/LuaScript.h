#pragma once

// Website used: https://eliasdaler.wordpress.com/2013/10/11/lua_cpp_binder/

#include <iostream>
#include <string>
#include <vector>

// Lua is written in C, inform compiler
extern "C"
{
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

class LuaScript
{
private:
	// --- Variables

	lua_State* luaState;
	std::string filename;
	int level;

	// --- Functions
	template <>
	inline bool LuaScript::lua_get<bool>(const std::string& variableName)
	{
		return (bool)lua_toboolean(luaState, -1);
	}

	template <>
	inline float LuaScript::lua_get<float>(const std::string& variableName)
	{
		if (!lua_isnumber(L, -1))
			printError(variableName, "Not a number");

		return (float)lua_tonumber(luaState, -1);
	}

	template <>
	inline int LuaScript::lua_get<int>(const std::string& variableName)
	{
		if (!lua_isnumber(L, -1))
			printError(variableName, "Not a number");

		return (int)lua_tonumber(luaState, -1);
	}

	template <>
	inline std::string LuaScript::lua_get<std::string>(const std::string& variableName)
	{
		std::string s = "null";
		lua_isstring(L, -1) ? s = std::string(lua_tostring(luaState, -1)) : printError(variableName, "is not a string");
		return s;
	}

	template<>
	inline std::string LuaScript::lua_getdefault<std::string>()
	{
		return "null";
	}
public:
	// --- Constructor

	LuaScript(const std::string &fileName);

	// --- Destructor

	~LuaScript();

	// --- Functions

	template<typename T>
	T get(const std::string& variable)
	{
		// Check state
		if (!luaState)
		{
			printError(variable, "Script failed to load");
			return lua_getdefault<T>(); // Returns null for different types within lua
		}

		// Put requested variable on top of the stack
		T result = lua_gettostack(variable) ? lua_get<T>(variable) : lua_getdefault<T>();

		// Pop all existing variables from stack
		lua_pop(luaState, level++);
		return result;
	}

	bool lua_gettostack(const std::string& variable)
	{
		// TODO Get rid of repeated code

		level = 0;
		std::string var = "";

		for (unsigned int i = 0; i < variable.size(), i++)
		{
			if (variable.at(i) == '.')
			{
				level == 0 ? lua_getglobal(luaState, var.c_str()) : lua_getfield(luaState, -1, var.c_str());

				if (lua_isnil(luaState, -1))
				{
					printError(variable, var + " is not defined");
					return false;
				}
				else
				{
					var = "";
					level++;
				}
			}
			else
				var += variable.at(i);
		}

		level == 0 ? lua_getglobal(luaState, var.c_str()) : lua_getfield(luaState, -1, var.c_str());

		if (lua_isnil(luaState, -1))
		{
			printError(variable, var + " is not defined");
			return false;
		}

		return true;
	}

	// Generic get
	template<typename T>
	T lua_get(const std::string& variable)
	{
		return nullptr;
	}

	// Generic default get
	template<typename T>
	T lua_getdefault(const std::string& variable)
	{
		return nullptr;
	}

	// --- Methods

	void printError(const std::string& variable, const std::string &reason);
};