#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_


#include "Scene.h"
#include <iostream>
#include "Rendering\Renderer.h"
#include "UI\GUIRenderer.h"

#include "Rendering\ResourceManager.h"
#include "Physics\Components\TransformComponent.h"
#include "Rendering\Components\RenderComponent.h"
#include "Rendering\Components\FirstPersonCameraComponent.h"
#include "UI\Components\CanvasComponent.h"


#include "UI\CanvasRect.h"


#include "Rendering\MeshFactory.h"

class SceneManager {

private:

	//The current scene
	Scene * m_CurrentScene_ = nullptr;

	//The scene to be switched to
	Scene * m_Unswitched_;

	//True if a switch between scenes is necessary and the appropriate steps can be taken by the engine.
	bool m_switch_;

public:

	SceneManager();
	~SceneManager() {

	}

	//Load a scene with this path.
	bool LoadScene(std::string pPath);
	bool LoadScene(Scene * pScene);

	//A scene is ready to be switched out/
	void switchScene();

	void DeleteScene();

	//Get the current active scene.
	Scene * getCurrentScene() {
		return m_CurrentScene_;
	}

	//Update the renderers with the current scene data.
	void UpdateRenderers(Renderer * pRenderer, GUIRenderer * pGUIRenderer);

	//Check if a new scene is ready to be switched.
	bool NewSceneReady() {
		return m_switch_;
	}

};


#endif