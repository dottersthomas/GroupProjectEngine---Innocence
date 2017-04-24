#pragma once

#include <lua.hpp>

class LuaEngine
{
public:
	LuaEngine();
	LuaEngine(const LuaEngine& other);  // Non-Construction Copy
	~LuaEngine();

	LuaEngine& operator=(const LuaEngine&); // Prevents copy

	const char* m_lastCommand; // Last file/expression executed

	lua_State* L(); // Get lua state

	void executeExpression(const char* expression); // Executes Lua expression
	void executeFile(const char* file); // Executes file
private:
	lua_State* m_L; // Member lua state

	void reportErrors(int state); // Handle errors
};