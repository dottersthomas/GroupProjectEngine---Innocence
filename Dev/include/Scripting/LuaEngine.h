#pragma once

#include <lua.hpp>
#include <iostream>

class LuaEngine
{
public:
	static LuaEngine& getInstance()
	{
		static LuaEngine instance;
		return instance;
	}

	~LuaEngine();

	const char* m_lastCommand; // Last file/expression executed

	lua_State* L(); // Get lua state

	void executeExpression(const char* expression); // Executes Lua expression
	void executeFile(const char* file); // Executes file

	static void printError(const char* msg)
	{
		std::cerr << "[Scripting] Error: " << msg << "\n";
	}
private:
	LuaEngine();

	lua_State* m_L; // Member lua state

	void reportErrors(int state); // Handle errors
};
