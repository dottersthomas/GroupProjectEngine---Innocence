#pragma once

#include <lua.hpp>
#include <iostream>

/// <summary>
/// Manages the execution and error-checking of Lua scripts.
/// </summary>
class LuaEngine
{
public:	
	/// <summary>
	/// Returns the instance.
	/// </summary>
	/// <returns>LuaEngine&</returns>
	static LuaEngine& getInstance()
	{
		static LuaEngine instance;
		return instance;
	}
	
	/// <summary>
	/// Finalizes an instance of the <see cref="LuaEngine"/> class.
	/// </summary>
	~LuaEngine();
	
	/// <summary>
	/// The last file/expression executed
	/// </summary>
	const char* m_lastCommand;
	
	/// <summary>
	/// Returns the lua_State instance.
	/// </summary>
	/// <returns>lua_State*</returns>
	lua_State* L();
	
	/// <summary>
	/// Executes a Lua expression.
	/// </summary>
	/// <param name="expression">The expression.</param>
	void executeExpression(const char* expression);
		
	/// <summary>
	/// Executes a Lua file.
	/// </summary>
	/// <param name="file">The path to the Lua file.</param>
	void executeFile(const char* file);
	
	/// <summary>
	/// Prints an error to the console.
	/// </summary>
	/// <param name="msg">The MSG.</param>
	static void printError(const char* msg)
	{
		std::cerr << "[Scripting] Error: " << msg << "\n";
	}
private:	
	/// <summary>
	/// Prevents a default instance of the <see cref="LuaEngine"/> class from being created.
	/// </summary>
	LuaEngine();
	
	/// <summary>
	/// The lua_State to be used by all scripts.
	/// </summary>
	lua_State* m_L;
	
	/// <summary>
	/// Prints errors that have occured with Lua file execution.
	/// </summary>
	/// <param name="state">The state.</param>
	void reportErrors(int state);
};
