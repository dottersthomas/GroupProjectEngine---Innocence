#include "Scripting/Script.h"
#include "Scripting/LuaEngine.h"

GameObject* Script::m_gameObject = nullptr;

Script::Script(std::string path, std::string tableName)
{
	m_Engine = &LuaEngine::getInstance();
	m_L = m_Engine->L();
	m_Path = path;
	m_TableName = tableName;
}

Script::~Script() {}

std::string Script::getPath()
{
	return m_Path;
}

void Script::Start()
{
	// Execute script
	execute();
	// Check if function exists, if so, execute
	if (m_Lua_Start)
	{
		try
		{
			(*m_Lua_Start)();
		}
		catch (luabridge::LuaException const& e)
		{
			LuaEngine::printError(e.what());
		}
	}
}

void Script::Update(double dt)
{
	// Execute script
	execute();
	// Check if function exists, if so, execute
	if (m_Lua_Update)
	{
		try
		{
			(*m_Lua_Update)(dt);
		}
		catch (luabridge::LuaException const& e)
		{
			LuaEngine::printError(e.what());
		}
	}
}

void Script::LateUpdate(double dt)
{
	// Execute script
	execute();
	// Check if function exists, if so, execute
	if (m_Lua_LateUpdate)
	{
		try
		{
			(*m_Lua_LateUpdate)(dt);
		}
		catch (luabridge::LuaException const& e)
		{
			LuaEngine::printError(e.what());
		}
	}
}

void Script::Destroy()
{
	// Execute script
	execute();
	// Check if function exists, if so, execute
	if (m_Lua_Destroy)
	{
		try
		{
			(*m_Lua_Destroy)();
		}
		catch (luabridge::LuaException const& e)
		{
			LuaEngine::printError(e.what());
		}
	}
}

void Script::execute()
{
	// Register globals
	registerGlobals();
	// Execute script
	m_Engine->executeFile(m_Path.c_str());
	// Load table
	load();
}

void Script::load()
{
	// Load values
	luabridge::LuaRef table = luabridge::getGlobal(m_L, m_TableName.c_str());

	if (table.isTable())
	{
		// Register functions
		if (table["Start"].isFunction())
			m_Lua_Start = std::make_shared<luabridge::LuaRef>(table["Start"]);

		if (table["Update"].isFunction())
			m_Lua_Update = std::make_shared<luabridge::LuaRef>(table["Update"]);

		if (table["LateUpdate"].isFunction())
			m_Lua_LateUpdate = std::make_shared<luabridge::LuaRef>(table["LateUpdate"]);

		if (table["Destroy"].isFunction())
			m_Lua_Destroy = std::make_shared<luabridge::LuaRef>(table["Destroy"]);
	}
}

void Script::registerGlobals()
{
	// Register global variables
	luabridge::setGlobal(m_L, m_GameObjectParent_, "gameObject");
}