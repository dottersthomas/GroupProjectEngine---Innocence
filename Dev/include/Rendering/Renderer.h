#ifndef RENDERER_H_
#define RENDERER_H_

#include <gl\glew.h>
#include <GLFW\glfw3.h>


#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "Scene.h"
#include "GameObjectVectorWrapper.h"


//The main game renderer for rendering all the RenderComponents within the scene.
class Renderer {

private:

	//The current scene.
	Scene * m_CurrentScene_;

	//Vector of all game objects with a render component.
	GameObjectVectorWrapper::t_GameObject_Vector_ m_sceneGameObjects_;
	GLFWwindow * m_Window_;

public:
	Renderer() {

	}
	Renderer(GLFWwindow * pWindow);
	
	void Render();
	
	void setScene(Scene * pScene);
};



#endif