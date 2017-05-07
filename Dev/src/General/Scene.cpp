#include "General\Scene.h"
#include "Rendering\Components\RenderComponent.h"
#include "Rendering\MeshFactory.h"


#include <memory>


Scene::Scene() {
	m_CurrentCamera_ = nullptr;
	m_SceneGameObjects_.reserve(100); // Temporary reservation of space, XML file loading will handle this efficiently itself.


	m_SceneGameObjects_.push_back(m_RootNode_);
	m_SceneGameObjects_[0].removeComponent(m_SceneGameObjects_[0].GetComponentByType<TransformComponent>());

	m_Environment_ = new Environment();

}

Scene::Scene(std::string pName) {
	m_Name_ = pName;
	m_SceneGameObjects_.reserve(100); // Temporary reservation of space, XML file loading will handle this efficiently itself.

	m_SceneGameObjects_.push_back(m_RootNode_);
	m_SceneGameObjects_[0].removeComponent(m_SceneGameObjects_[0].GetComponentByType<TransformComponent>());
	m_Environment_ = new Environment();

}

int Scene::AddGameObject(GameObject pGameObject) {
	std::cout << m_SceneGameObjects_.capacity() << std::endl;
	m_SceneGameObjects_.push_back(pGameObject);
	M_bIsDirty = true;
	return m_SceneGameObjects_.size() - 1;
}

void Scene::RemoveGameObject(std::string pName) {
	
	std::vector<GameObject>::iterator iter = m_SceneGameObjects_.begin();
	while ( iter != m_SceneGameObjects_.end()) {
		if ((*iter).m_Name_ == pName) {
			iter = m_SceneGameObjects_.erase(iter);
		}
		++iter;
	}
	
	M_bIsDirty = true;
}

void Scene::Update(double dt){
	if (m_SceneGameObjects_.size() > 0) {

		//Standard Update.
		for (std::vector<GameObject>::iterator iter = m_SceneGameObjects_.begin(); iter != m_SceneGameObjects_.end(); ++iter) {
			(*iter).UpdateComponents(dt);
		}


		//Late update.
		for (std::vector<GameObject>::iterator iter = m_SceneGameObjects_.begin(); iter != m_SceneGameObjects_.end(); ++iter) {
			(*iter).LateUpdateComponents(dt);

		}
	}
}


void Scene::Start() {

	//Start the Components within the Scene.
	if(m_SceneGameObjects_.size())
		for (std::vector<GameObject>::iterator iter = m_SceneGameObjects_.begin(); iter != m_SceneGameObjects_.end(); ++iter) {
			for (ComponentVectorWrapper::t_Component_Iter iter2 = (*iter).getComponents().begin(); iter2 != (*iter).getComponents().end(); ++iter2) {
				(*iter2)->Start();
			}
		}
}


void Scene::Destroy() {
	//Destroy the components.
	if (m_SceneGameObjects_.size() > 0)

		for (std::vector<GameObject>::iterator iter = m_SceneGameObjects_.begin(); iter != m_SceneGameObjects_.end(); ++iter) {
			for (ComponentVectorWrapper::t_Component_Iter iter2 = (*iter).getComponents().begin(); iter2 != (*iter).getComponents().end(); ++iter2) {
				(*iter2)->Destroy();
			}
		}


	//Clear the GameObjects vector.
	m_SceneGameObjects_.clear();
}

<<<<<<< HEAD

luabridge::LuaRef Scene::luaGetGameObject(std::string name)
 {
		// Get GameObjects
		auto goVec = getGameObjects();
	
		lua_State* L = (&LuaEngine::getInstance())->L();
	auto globalName = "Scripting_currentGameObject";
	
			// Loop through objects to find one specified
		for (GameObject& go : *goVec)
		 {
		if (go.m_Name_ == name)
			 {
						// Set global
				luabridge::setGlobal(L, go, globalName);
						// Return global
				return luabridge::getGlobal(L, globalName);
			}
		}
	
		std::cout << "[Scripting] Error: " << "GameObject not found!" << "\n";
	return luabridge::LuaRef(L);
	}


=======
luabridge::LuaRef Scene::luaGetGameObject(std::string name)
{
	// Get GameObjects
	auto goVec = getGameObjects();

	lua_State* L = (&LuaEngine::getInstance())->L();
	auto globalName = "Scripting_currentGameObject";

	// Loop through objects to find one specified
	for (GameObject& go : *goVec)
	{
		if (go.m_Name_ == name)
		{
			// Set global
			luabridge::setGlobal(L, go, globalName);
			// Return global
			return luabridge::getGlobal(L, globalName);
		}
	}

	std::cout << "[Scripting] Error: " << "GameObject not found!" << "\n";
	return luabridge::LuaRef(L);
}
>>>>>>> 666b570b4b17c6c4998cdddb9c7086bb4fdf2947

luabridge::LuaRef Scene::luaGetGameObjects()
{
	// Get gameObjects and convert to lua table
	luabridge::LuaRef table = LuaHelper::ToTable(*getGameObjects());
	// Set lua global
	auto globalName = "Scripting_sceneGameObjects";
	lua_State* L = (&LuaEngine::getInstance())->L();
	luabridge::setGlobal(L, &table, globalName);
	// Return reference to global
	return luabridge::getGlobal(L, globalName);
}
