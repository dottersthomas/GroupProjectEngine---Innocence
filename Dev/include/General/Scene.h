#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>

#include "GameObject.h"
#include "GameObjectVectorWrapper.h"
#include "ComponentVectorWrapper.h"
#include "Rendering\Components\CameraComponent.h"
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
	void RemoveGameObject(GameObject * pGameObject);

	//Update the scene's contents.
	void Update(double dt);

	//Start the scene and its contents.
	void Start();

	//Destroy the scene and its contents.
	void Destroy();

	std::string getName() {
		return m_Name_;
	}

	GameObjectVectorWrapper::t_GameObject_Vector_ * getGameObjects() {
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
		if (m_CurrentCamera_ == nullptr)
			return nullptr;
		else
			return m_CurrentCamera_;
	}

	Environment * getEnvironment() {
		return m_Environment_;
	}

private:

	GameObject m_RootNode_ = GameObject("Root");
	
	GameObjectVectorWrapper::t_GameObject_Vector_ m_SceneGameObjects_;
	

	CameraComponent * m_CurrentCamera_ = nullptr;


	std::string m_Name_;

	Environment * m_Environment_;



};


#endif