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
private:
	std::string m_Tag = "";
protected:
	GameObject * m_GameObjectParent_;
public:
	virtual ~Component() = default;

	std::string m_ComponentName;

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

	// Set the tag.
	void setTag(std::string name)
	{
		m_Tag = name;
	}

	// Get the tag.
	std::string getTag() const
	{
		return m_Tag;
	}

	// Register class with lua
	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.beginClass<Component>("Component")
			.addData<GameObject*>("parent", &Component::m_GameObjectParent_)
			.addProperty<std::string>("tag", &Component::getTag, &Component::setTag)
			.endClass();
	}
};

#endif