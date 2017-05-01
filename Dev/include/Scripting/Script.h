#pragma once

#include "Component.h"
#include <lua.hpp>
#include <LuaBridge.h>

class LuaEngine;

/// <summary>
/// Used to define and link a Script file.
/// </summary>
/// <seealso cref="Component" />
class Script : public Component
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Script"/> class.
	/// </summary>
	/// <param name="path">The path to the file.</param>
	/// <param name="tableName">The name for the table that will be used in Lua.</param>
	Script(std::string path, std::string tableName);
		
	/// <summary>
	/// Finalizes an instance of the <see cref="Script"/> class.
	/// </summary>
	~Script();
	
	/// <summary>
	/// Returns the path to the file.
	/// </summary>
	/// <returns>std::string</returns>
	std::string getPath();

	void Update(double dt) override;
	void LateUpdate(double dt) override;
	void Destroy() override;
	void Start() override;
private:	
	/// <summary>
	/// A pointer to a LuaEngine instance.
	/// </summary>
	LuaEngine* m_Engine;

	/// <summary>
	/// The lua_State to use.
	/// </summary>
	lua_State* m_L;
	
	/// <summary>
	/// The path to the file.
	/// </summary>
	std::string m_Path;
	
	/// <summary>
	/// The name of the table the object uses in Lua.
	/// </summary>
	std::string m_TableName;
	
	/// <summary>
	/// A pointer to the Start function defined within Lua.
	/// </summary>
	std::shared_ptr<luabridge::LuaRef> m_Lua_Start;
	
	/// <summary>
	/// A pointer to the Update function defined within Lua.
	/// </summary>
	std::shared_ptr<luabridge::LuaRef> m_Lua_Update;
	
	/// <summary>
	/// A pointer to the LateUpdate function defined within Lua.
	/// </summary>
	std::shared_ptr<luabridge::LuaRef> m_Lua_LateUpdate;
	
	/// <summary>
	/// A pointer to the Destroy function defined within Lua.
	/// </summary>
	std::shared_ptr<luabridge::LuaRef> m_Lua_Destroy;
		
	/// <summary>
	/// The parent gameObject the script is attached to.
	/// </summary>
	static GameObject* m_gameObject;
	
	/// <summary>
	/// Executes the file.
	/// </summary>
	void execute();
	
	/// <summary>
	/// Loads and links values from the file.
	/// </summary>
	void load();
	
	/// <summary>
	/// Registers global variables with the file.
	/// </summary>
	void registerGlobals();
};