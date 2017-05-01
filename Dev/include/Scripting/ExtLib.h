#pragma once

#include <lua.hpp>
#include <LuaBridge.h>
#include <glm/glm.hpp>

/// <summary>
/// Used to register classes from external libraries with Lua.
/// </summary>
class ExtLib
{
public:	
	/// <summary>
	/// Registers classes with Lua.
	/// </summary>
	/// <param name="L">The lua_State to use.</param>
	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		// --- GLM

		// Register vectors
		getGlobalNamespace(L)
			.beginClass<glm::vec2>("Vec2")
			.addConstructor<void(*)(float, float)>()
			.addData<float>("x", &glm::vec2::x)
			.addData<float>("y", &glm::vec2::y)
			.endClass()
			.deriveClass<glm::vec3, glm::vec2>("Vec3")
			.addConstructor<void(*)(float, float, float)>()
			.addData<float>("z", &glm::vec3::z)
			.endClass()
			.deriveClass<glm::vec4, glm::vec3>("Vec4")
			.addConstructor<void(*)(float, float, float, float)>()
			.addData<float>("w", &glm::vec4::w)
			.endClass();
	}
};