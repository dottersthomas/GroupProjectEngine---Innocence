#include "General\GameObject.h"
#include "Physics\Components\TransformComponent.h"
#include "Scripting/LuaEngine.h"
#include "Rendering/Components/CameraComponent.h"
#include "Rendering/Components/FirstPersonCameraComponent.h"
#include "Rendering/Components/RenderComponent.h"
#include "Rendering/Components/ThirdPersonCameraComponent.h"
#include "Scripting/LuaHelper.h"

GameObject::GameObject(const char* pName)
{
	m_Name_ = pName;
	m_Components_.reserve(10);
	m_Transform = new TransformComponent(this);
	registerComponent(m_Transform); //Every GameObject has a transform component, can be removed later as its easier to assume it exists.
}

GameObject::~GameObject()
{
	//delete m_Transform;
}

bool GameObject::checkComponentExists(std::string pName) const
{
	for (int i = m_Components_.size(); i--;)
		if (m_Components_[i]->m_ComponentName == pName)
			return true;
	return false;

}

void GameObject::registerComponent(Component * pComponent)
{
	pComponent->setParent(this);
	m_Components_.push_back(pComponent);
}

void GameObject::removeComponent(Component * pComponent)
{

	ComponentVectorWrapper::t_Component_Iter iter = std::find(m_Components_.begin(), m_Components_.end(), pComponent);
	if (iter != m_Components_.end()) {
		m_Components_.erase(iter);
	}
}

void GameObject::UpdateComponents(double dt)
{
	for (ComponentVectorWrapper::t_Component_Iter iter = m_Components_.begin(); iter != m_Components_.end(); ++iter)
		(*iter)->Update(dt);
}

void GameObject::LateUpdateComponents(double dt)
{
	for (ComponentVectorWrapper::t_Component_Iter iter = m_Components_.begin(); iter != m_Components_.end(); ++iter)
		(*iter)->LateUpdate(dt);
}

luabridge::LuaRef GameObject::luaGetComponent(std::string type)
{
	// Return component
	return luaGetComponentHelper(type, false, "");
}

luabridge::LuaRef GameObject::luaGetComponents(std::string type)
{
	// Return components
	return luaGetComponentHelper(type, true, "");
}

luabridge::LuaRef GameObject::luaGetComponentsByTag(std::string type, std::string tag)
{
	// Return components by tag
	return luaGetComponentHelper(type, true, tag.c_str());
}

luabridge::LuaRef GameObject::luaGetComponentHelper(std::string type, bool findAll, const char* tag)
{
	lua_State* L = (&LuaEngine::getInstance())->L();

	// Find component type
	if (type == "TransformComponent")
		LuaHelper::GetGlobalComponent<TransformComponent>(*this, findAll, m_CompName, tag);
	else if (type == "CameraComponent")
		LuaHelper::GetGlobalComponent<CameraComponent>(*this, findAll, m_CompName, tag);
	else if (type == "FirstPersonCameraComponent")
		LuaHelper::GetGlobalComponent<FirstPersonCameraComponent>(*this, findAll, m_CompName, tag);
	else if (type == "RenderComponentComponent")
		LuaHelper::GetGlobalComponent<RenderComponent>(*this, findAll, m_CompName, tag);
	else if (type == "ThirdPersonCameraComponent")
		LuaHelper::GetGlobalComponent<ThirdPersonCameraComponent>(*this, findAll, m_CompName, tag);
	else if (type == "CanvasComponent")
		LuaHelper::GetGlobalComponent<CanvasComponent>(*this, findAll, m_CompName, tag);
	else if (type == "RigidBody")
		LuaHelper::GetGlobalComponent<RigidBody>(*this, findAll, m_CompName, tag);
	else if (type == "BoxCollider")
		LuaHelper::GetGlobalComponent<BoxCollider>(*this, findAll, m_CompName, tag);
	else
	{
		luabridge::setGlobal(L, nullptr, m_CompName); // Prevents errors
		LuaEngine::printError("Component not found.");
	}

	// Return component
	return luabridge::getGlobal(L, m_CompName);
}
