#pragma once

#include "Component.h"
#include <lua.hpp>

class LuaEngine;

class Script : public Component
{
public:
	Script(std::shared_ptr<LuaEngine> engine, std::string path);
	~Script();

	std::string getPath();

	void Update(double dt) override;
	void LateUpdate(double dt) override;
	void Destroy() override;
	void Start() override;
private:
	std::shared_ptr<LuaEngine> m_Engine;
	lua_State* m_L;
	std::string m_Path;

	void execute();
};