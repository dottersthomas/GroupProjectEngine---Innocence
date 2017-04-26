#pragma once

#include "Component.h"
#include <lua.hpp>
#include <LuaBridge.h>

class LuaEngine;

class Script : public Component
{
public:
	Script(std::shared_ptr<LuaEngine> engine, std::string path, std::string tableName);
	~Script();

	std::string getPath();

	void Update(double dt) override;
	void LateUpdate(double dt) override;
	void Destroy() override;
	void Start() override;
private:
	std::shared_ptr<LuaEngine> m_Engine;
	lua_State* m_L;
	std::string m_Path, m_TableName;

	std::shared_ptr<luabridge::LuaRef> m_Lua_Start;
	std::shared_ptr<luabridge::LuaRef> m_Lua_Update;
	std::shared_ptr<luabridge::LuaRef> m_Lua_LateUpdate;
	std::shared_ptr<luabridge::LuaRef> m_Lua_Destroy;

	static GameObject* m_gameObject;

	void execute();
	void load();
	void registerGlobals();
	void printError(const char* e);
};