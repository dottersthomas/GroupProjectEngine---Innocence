#include "General\Scene.h"
#include "Rendering\Components\RenderComponent.h"
#include "Rendering\MeshFactory.h"


#include <memory>


Scene::Scene() {
	m_CurrentCamera_ = nullptr;
	m_SceneGameObjects_.reserve(100); // Temporary reservation of space, XML file loading will handle this efficiently itself.


	m_SceneGameObjects_.push_back(m_RootNode_);
	m_SceneGameObjects_[0].removeComponent(m_SceneGameObjects_[0].GetComponentByType<TransformComponent>());

}

Scene::Scene(std::string pName) {
	m_Name_ = pName;
	m_SceneGameObjects_.reserve(100); // Temporary reservation of space, XML file loading will handle this efficiently itself.

	m_SceneGameObjects_.push_back(m_RootNode_);
	m_SceneGameObjects_[0].removeComponent(m_SceneGameObjects_[0].GetComponentByType<TransformComponent>());
}

int Scene::AddGameObject(GameObject pGameObject) {
	std::cout << m_SceneGameObjects_.capacity() << std::endl;
	m_SceneGameObjects_.push_back(pGameObject);
	M_bIsDirty = true;
	return m_SceneGameObjects_.size() - 1;
}

void Scene::RemoveGameObject(GameObject * pGameObject) {
	M_bIsDirty = true;

}

void Scene::Update(double dt){
	if (m_SceneGameObjects_.size() > 0) {

		//Standard Update.
		for (GameObjectVectorWrapper::t_GameObject_Vector_Iterator_ iter = m_SceneGameObjects_.begin(); iter != m_SceneGameObjects_.end(); ++iter) {
			(*iter).UpdateComponents(dt);
		}


		//Late update.
		for (GameObjectVectorWrapper::t_GameObject_Vector_Iterator_ iter = m_SceneGameObjects_.begin(); iter != m_SceneGameObjects_.end(); ++iter) {
			(*iter).LateUpdateComponents();

		}
	}
}


void Scene::Start() {

	//Start the Components within the Scene.
	if(m_SceneGameObjects_.size())
		for (GameObjectVectorWrapper::t_GameObject_Vector_Iterator_ iter = m_SceneGameObjects_.begin(); iter != m_SceneGameObjects_.end(); ++iter) {
			for (ComponentVectorWrapper::t_Component_Iter iter2 = (*iter).getComponents().begin(); iter2 != (*iter).getComponents().end(); ++iter2) {
				(*iter2)->Start();
			}
		}
}


void Scene::Destroy() {
	//Destroy the components.
	if (m_SceneGameObjects_.size() > 0)

		for (GameObjectVectorWrapper::t_GameObject_Vector_Iterator_ iter = m_SceneGameObjects_.begin(); iter != m_SceneGameObjects_.end(); ++iter) {
			for (ComponentVectorWrapper::t_Component_Iter iter2 = (*iter).getComponents().begin(); iter2 != (*iter).getComponents().end(); ++iter2) {
				(*iter2)->Destroy();
			}
		}


	//Clear the GameObjects vector.
	m_SceneGameObjects_.clear();
}

luabridge::LuaRef Scene::luaGetGameObjects()
{
	// Get gameObjects and convert to lua table
	return LuaHelper::ToTable(static_cast<std::vector<GameObject>>(*(getGameObjects())));
}