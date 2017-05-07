#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>

#include "GameObject.h"
#include "ComponentVectorWrapper.h"
#include "Rendering\Components\CameraComponent.h"
#include "Scripting\LuaHelper.h"
#include "Rendering\Environment.h"


//Main Scene class. This holds effectivly the entire game.
class Scene {
	

public:
	Scene();
	Scene(std::string pName);
	~Scene() {

	}

	//Add a game object to the scene.
	int AddGameObject(GameObject pGameObject);
	void RemoveGameObject(std::string pName);

	//Update the scene's contents.
	void Update(double dt);

	//Start the scene and its contents.
	void Start();

	//Destroy the scene and its contents.
	void Destroy();

	std::string getName() {
		return m_Name_;
	}

	luabridge::LuaRef luaGetGameObject(std::string name);

	luabridge::LuaRef luaGetGameObjects();

	std::vector<GameObject> * getGameObjects() {
		return &m_SceneGameObjects_;
	}
	bool M_bIsDirty = true;

	//Attach a main camera component to the scene. Only one camera can be the main and in use at any point.
	void attachMainCameraComponent(CameraComponent * pCamera) {
		if (m_CurrentCamera_ != nullptr)
			m_CurrentCamera_->SetActive(false);
		m_CurrentCamera_ = pCamera;
		m_CurrentCamera_->SetActive(true);
	}

	//Get the currently bound camera.
	CameraComponent * getBoundCamera() {
		return m_CurrentCamera_;
	}

	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.beginClass<Scene>("Scene")
			.addConstructor<void(*)(std::string name)>()
			.addData("name", &Scene::m_Name_, false)
			.addData("mainCamera", &Scene::m_CurrentCamera_, false)
			.addFunction("attachMainCamera", &Scene::attachMainCameraComponent)
			.addFunction("addGameObject", &Scene::AddGameObject)
			.addFunction("removeGameObject", &Scene::RemoveGameObject)
			.addFunction("getGameObject", &Scene::luaGetGameObject)
			.addFunction("getGameObjects", &Scene::luaGetGameObjects)
			.addFunction("togglePostProcess", &Scene::togglePostProcess)
			.addProperty("postProcessEnabled", &Scene::shouldPostProcess)
			.endClass();
	}

	Environment * getEnvironment() {
		return m_Environment_;
	}

	void togglePostProcess(int pToggle) {
		m_ShouldPostProcess_ = pToggle;
	}

	int shouldPostProcess() const {
		return m_ShouldPostProcess_;
	}

private:

	GameObject m_RootNode_ = GameObject("Root");
	
	std::vector<GameObject> m_SceneGameObjects_;

	CameraComponent * m_CurrentCamera_ = nullptr;

	std::string m_Name_;

	Environment * m_Environment_;

	int m_ShouldPostProcess_ = false;

};


#endif