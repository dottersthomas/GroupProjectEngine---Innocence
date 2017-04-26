#ifndef _GameObject_H_
#define _GameObject_H_

#include <memory>	
#include <vector>
#include "Component.h"
#include "ComponentVectorWrapper.h"
#include "Exceptions\ComponentMissingException.h"
#include <lua.hpp>
#include <LuaBridge.h>
#include "Physics/Components/TransformComponent.h"

//Game Object container class, used to hold components and manage their lifecycle.
class GameObject
{
public:
	GameObject(const char* pName);
	~GameObject();

	//Objects name.
	const char* m_Name_;

	//Register and Remove a component from the object.
	void registerComponent(Component * pComponent);
	void removeComponent(Component * pComponent);


	//Update all the components.
	void UpdateComponents(double dt);

	//Late update all components.
	void LateUpdateComponents();

	ComponentVectorWrapper::t_Components_Vector_& getComponents()
	{
		return m_Components_;
	}

	bool checkComponentExists(std::string pName) const;


	void updateParents()
	{
		/*for (int i = m_Components_.size(); i--;) {
			m_Components_[i]->setParent(this);
		}*/
	}

	//Get the Component by its type. As each component should be unique, only one of its type should exist, so filtering by type is effective to get a specific component.
	template<typename T>
	T* GetComponentByType()
	{
		try
		{
			for (ComponentVectorWrapper::t_Component_Iter iter = m_Components_.begin(); iter != m_Components_.end(); ++iter)
				if (*iter != nullptr)
					if (T* type = dynamic_cast<T*>(*iter))
						return type;
			throw ComponentMissingException();
		}
		catch (ComponentMissingException& e)
		{
			std::cout << e.what() << std::endl;
			__debugbreak();
		}
	}

	//find a Component by its type. As each component should be unique, only one of its type should exist, so filtering by type is effective to find a specific component.
	template<typename T>
	bool CheckComponentTypeExists()
	{
		if (m_Components_.size() > 0)
			for (ComponentVectorWrapper::t_Component_Iter iter = m_Components_.begin(); iter != m_Components_.end(); ++iter)
				if (*iter != nullptr)
					if (T* type = dynamic_cast<T*>(*iter))
						return true;
		return false;
	}

	// Register class with lua
	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.beginClass<GameObject>("GameObject")
			.addConstructor<void(*)(const char* name)>()
			.addData<const char*>("name", &GameObject::m_Name_, false)
			.addData<TransformComponent*>("transform", &GameObject::m_Transform)
			.addFunction("addComponent", &GameObject::registerComponent)
			.addFunction("removeComponent", &GameObject::removeComponent)
			.endClass();
	}
private:
	ComponentVectorWrapper::t_Components_Vector_ m_Components_;
	TransformComponent* m_Transform;
};

#endif