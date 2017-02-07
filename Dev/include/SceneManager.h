#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_


#include "Scene.h"
#include <iostream>
#include "Rendering\Renderer.h"
#include "Rendering\GUI\GUIRenderer.h"

#include "Rendering\ResourceManager.h"
#include "Components\TransformComponent.h"
#include "Components\RenderComponent.h"
#include "Components\PlayerKeyboardControlComponent.h"
#include "Components\FirstPersonCameraComponent.h"
#include "Components\GUI\CanvasComponent.h"


#include "Rendering\GUI\CanvasRect.h"


#include "Rendering\MeshFactory.h"

class SceneManager {

private:

	//The current scene
	Scene * m_CurrentScene_;

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