#include "General\GameObject.h"
#include "Physics\Components\TransformComponent.h"
#include "Scripting/LuaEngine.h"
#include "Rendering/Components/CameraComponent.h"
#include "Rendering/Components/FirstPersonCameraComponent.h"
#include "Rendering/Components/RenderComponent.h"
#include "Rendering/Components/ThirdPersonCameraComponent.h"


GameObject::GameObject(const char* pName) {
	m_Name_ = pName;
	m_Components_.reserve(10);
	m_Transform = new TransformComponent(this);
	registerComponent(m_Transform); //Every GameObject has a transform component, can be removed later as its easier to assume it exists.
}

GameObject::~GameObject()
{
	//delete m_Transform;
}

bool GameObject::checkComponentExists(std::string pName) const {

	for (int i = m_Components_.size(); i--;)
		if (m_Components_[i]->M_ComponentName == pName)
			return true;
	return false;

}

void GameObject::registerComponent(Component * pComponent) {
	pComponent->setParent(this);
	m_Components_.push_back(pComponent);
}

void GameObject::removeComponent(Component * pComponent) {
	//TODO add removal of components.
}

void GameObject::UpdateComponents(double dt) {
	for (ComponentVectorWrapper::t_Component_Iter iter = m_Components_.begin(); iter != m_Components_.end(); ++iter)
		(*iter)->Update(dt);
}

void GameObject::LateUpdateComponents() {
	for (ComponentVectorWrapper::t_Component_Iter iter = m_Components_.begin(); iter != m_Components_.end(); ++iter)
		(*iter)->LateUpdate(0.0);
}

luabridge::LuaRef GameObject::luaGetComponent(std::string type)
{
	const char* compName = "ScriptingEngine_currentComponent";
	lua_State* L = (&LuaEngine::getInstance())->L();

	// Find component type
	if (type == "TransformComponent")
		luabridge::setGlobal(L, GetComponentByType<TransformComponent>(), compName);
	else if (type == "CameraComponent")
		luabridge::setGlobal(L, GetComponentByType<CameraComponent>(), compName);
	else if (type == "FirstPersonCameraComponent")
		luabridge::setGlobal(L, GetComponentByType<FirstPersonCameraComponent>(), compName);
	else if (type == "RenderComponentComponent")
		luabridge::setGlobal(L, GetComponentByType<RenderComponent>(), compName);
	else if (type == "ThirdPersonCameraComponent")
		luabridge::setGlobal(L, GetComponentByType<ThirdPersonCameraComponent>(), compName);
	else if (type == "CanvasComponent")
		luabridge::setGlobal(L, GetComponentByType<CanvasComponent>(), compName);
	else
	{
		luabridge::setGlobal(L, nullptr, compName); // Prevents errors
		LuaEngine::printError("Component not found.");
	}

	// Return component
	return luabridge::getGlobal(L, compName);
}