#ifndef RENDERER_H_
#define RENDERER_H_

#include <gl\glew.h>
#include <GLFW\glfw3.h>


#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "General\Scene.h"
#include "General\GameObjectVectorWrapper.h"

#include "Rendering\LightManager.h"


//The main game renderer for rendering all the RenderComponents within the scene.
class Renderer {

private:

	//The current scene.
	Scene * m_CurrentScene_ = nullptr;

	//Vector of all game objects with a render component.
	GameObjectVectorWrapper::t_GameObject_Vector_ m_sceneGameObjects_;
	GLFWwindow * m_Window_;
	LightManager m_LightManager_;

public:
	Renderer() {

	}
	Renderer(GLFWwindow * pWindow);
	
	void Render();
	
	void setScene(Scene * pScene);

	void update(float dt);

	LightManager& getLightManager() {
		return m_LightManager_;
	}


};



#endif