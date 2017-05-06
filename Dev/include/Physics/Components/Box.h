#pragma once

#include "glm\glm.hpp"
#include <lua.hpp>
#include <LuaBridge.h>

class Box
{
private:
	float maxX, minX, maxY, minY, maxZ, minZ;
	float omaxX, ominX, omaxY, ominY, omaxZ, ominZ;
	float width, height, depth;

	glm::vec3 midPoint;
public:
	Box();
	Box(glm::vec3 minPoints, glm::vec3 maxPoints);
	glm::vec3 GetMax() const;
	glm::vec3 GetMin() const;
	glm::vec3 GetOMax() const;
	glm::vec3 GetOMin() const;
	glm::vec3 getMid() const
	{
		return midPoint;
	}

	void SetMax(glm::vec3 newMax);
	void SetMin(glm::vec3 newMin);
	~Box();

	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.beginClass<Box>("Box")
				.addConstructor<void(*)()>()
				.addProperty("min", &Box::GetMin, &Box::SetMin)
				.addProperty("max", &Box::GetMax, &Box::SetMax)
				.addFunction("oMin", &Box::GetOMin)
				.addFunction("oMax", &Box::GetOMax)
				.addFunction("mid", &Box::getMid)
			.endClass();
	}
};