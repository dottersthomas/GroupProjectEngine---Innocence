#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <memory>
#include <iostream>
#include <functional>
#include <lua.hpp>
#include <LuaBridge.h>

class GameObject;

//Base Component Class. This class is inherited by all other components.
class Component
{
protected:
	GameObject * m_GameObjectParent_;
public:
	virtual ~Component() = default;

	std::string M_ComponentName;

	//Called every tick.
	virtual void Update(double dt) = 0;

	//Called at the end of every tick, mainly for maintenance uses.
	virtual void LateUpdate(double dt) = 0;

	//Called when the component is destroyed.
	virtual void Destroy() = 0;

	//Called when the component starts.
	virtual void Start() = 0;

	//Set the components parent.
	void setParent(GameObject * pParent)
	{
		m_GameObjectParent_ = pParent;
	}

	// Register class with lua
	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.beginClass<Component>("Component")
			.addData<GameObject*>("parent", &Component::m_GameObjectParent_)
			.endClass();
	}
};

#endif