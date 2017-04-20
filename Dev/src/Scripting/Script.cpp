#include "Scripting/Script.h"
#include <LuaBridge.h>
#include "Scripting/LuaEngine.h"

Script::Script(std::shared_ptr<LuaEngine> engine, std::string path)
{
	m_Engine = engine;
	m_L = m_Engine->L();
	m_Path = path;
}

Script::~Script(){}

std::string Script::getPath()
{
	return m_Path;
}

void Script::Start()
{
	// Execute script
	execute();
	// Call function
	luabridge::LuaRef lua_Start = luabridge::getGlobal(m_L, "Start");
	lua_Start();
}

void Script::Update(double dt)
{
	// Execute script
	execute();
	// Call function
	luabridge::LuaRef lua_Update = luabridge::getGlobal(m_L, "Update");
	lua_Update(dt);
}

void Script::LateUpdate(double dt)
{
	// Execute script
	execute();
	// Call function
	luabridge::LuaRef lua_LateUpdate = luabridge::getGlobal(m_L, "LateUpdate");
	lua_LateUpdate(dt);
}

void Script::Destroy()
{
	// Execute script
	execute();
	// Call function
	luabridge::LuaRef lua_Destroy = luabridge::getGlobal(m_L, "Destroy");
	lua_Destroy();
}

void Script::execute()
{
	m_Engine->executeFile(m_Path.c_str());
}