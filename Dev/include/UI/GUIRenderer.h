#ifndef _GUI_RENDERER_H_
#define _GUI_RENDERER_H_


#include <gl\glew.h>
#include <GLFW\glfw3.h>


#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "General\Scene.h"
#include "General\GameObjectVectorWrapper.h"
#include "UI\Components\CanvasComponent.h"

//Unique renderer designed to render the ui only.
class GUIRenderer {

	//Type of GUI being displayed, unused right now.
	enum GUIType {
		FULL_MENU,
		OVERLAY
	};

private:
	//The current scene to be rendering.
	Scene * m_CurrentScene_;
	//Game Objects with a canvas component.
	GameObjectVectorWrapper::t_GameObject_Vector_ m_sceneGameObjects_;
	//current window.
	GLFWwindow * m_Window_;

	//The orthographic projection used to overlay the ui.
	glm::mat4 Projection = glm::ortho(0.0f, 1280.f, 720.f, 0.0f, -1.0f, 1.0f);

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(1, 1, 1),
		glm::vec3(1, 1, 0),
		glm::vec3(0, 1, 0)
	);




public:
	GUIRenderer() {

	}
	GUIRenderer(GLFWwindow * pWindow);

	void Render();

	void setScene(Scene * pScene);
};


#endif