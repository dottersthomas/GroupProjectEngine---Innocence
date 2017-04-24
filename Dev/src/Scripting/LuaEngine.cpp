#include "Scripting/LuaEngine.h"

#include <iostream>

// --- Constructor(s) and Destructor 

LuaEngine::LuaEngine() : m_L(luaL_newstate())
{
	luaL_openlibs(m_L); // Initialise lua state
}

LuaEngine::~LuaEngine()
{
	// Clean-up
	lua_close(m_L);
}

// --- Function(s)

lua_State* LuaEngine::L()
{
	return m_L;
}

// --- Method(s)

void LuaEngine::executeExpression(const char* expression)
{
	if (expression == nullptr)
	{
		std::cerr << "[Scripting] Error: Expression is null" << "\n";
		return;
	}

	int state = luaL_dostring(m_L, expression); // Execute expression
	reportErrors(state); // Check for errors

	 // Set last command variable
	m_lastCommand = expression;
}

void LuaEngine::executeFile(const char* file)
{
	if (file == nullptr) return;

	int state = luaL_dofile(m_L, file); // Execute file
	reportErrors(state); // Check for errors

	// Set last command variable
	m_lastCommand = file;
}

void LuaEngine::reportErrors(int state)
{
	if (state != 0)
	{
		std::cerr << "[Scripting] Error: " << lua_tostring(m_L, state) << "\n";
		lua_pop(m_L, 1); // Remove error from stack
	}
}