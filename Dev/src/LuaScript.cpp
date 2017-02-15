#include "LuaScript.h"

LuaScript::LuaScript(const std::string &fileName)
{
	// Create state
	luaState = luaL_newstate();
	// Load file
	if (luaL_loadfile(luaState, fileName.c_str()) || lua_pcall(luaState, 0, 0, 0))
	{
		// Error
		std::cout << "Error: Failed to load " << fileName << "." << "\n";
		luaState = nullptr; // TODO Check if this is needed
	}
}

LuaScript::~LuaScript()
{
	if (luaState)
		lua_close(luaState);
}

void LuaScript::printError(const std::string& variable, const std::string &reason)
{
	std::cout << "Error: Failed to fetch " << variable << "because " << reason << "." << "\n";
}