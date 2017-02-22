#include "Rendering\Renderer.h"
#include "Rendering\Components\RenderComponent.h"

Renderer::Renderer(GLFWwindow * pWindow) {
	m_Window_ = pWindow;


	glClearColor(0.2, 0.2, 0.4, 1.0);

	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_CurrentScene_ = nullptr;
	
}


void Renderer::Render() {

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);     // Cull back facing polygons
	glCullFace(GL_BACK);

	glm::mat4 Projection = glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 1000.f);

	glm::mat4 View;

	if (m_CurrentScene_ != nullptr) {
		if (m_CurrentScene_->getBoundCamera() != nullptr) {
			View = m_CurrentScene_->getBoundCamera()->Bind();
		}
		else
			View = glm::lookAt(
				glm::vec3(2.0f, 1.0f, 5.0f),
				glm::vec3(0, 0, 0),
				glm::vec3(0, 1, 0)
			);
	}
	else
		View = glm::lookAt(
			glm::vec3(1.2f, 1.0f, 2.0f),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0)
		);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Check if the scene is dirty or not and needs an update.
	if (m_CurrentScene_ != nullptr) {

		//check if the scene is dirty, if so, update the vector. Do not set to be clean here, that is done in the 
		//subsequent GUIRender dirty check as they will share the same scene.
		if (m_CurrentScene_->M_bIsDirty) {

			m_sceneGameObjects_.clear(); //Currently clearing the list, but should become more dynamic in the future.

			GameObjectVectorWrapper::t_GameObject_Vector_ temp = *m_CurrentScene_->getGameObjects();
			for (GameObjectVectorWrapper::t_GameObject_Vector_Iterator_ iter = temp.begin(); iter != temp.end(); ++iter) {
				if ((*iter).CheckComponentTypeExists<RenderComponent>()) {
					m_sceneGameObjects_.push_back(*iter); //Add GameObject to the list.
				}
			}
			//No need to check again.
			//m_CurrentScene_->M_bIsDirty = false;
		}

		//Render the scenes GameObjects. Possibly provide filtering to improve performance speed. Or maybe even have it within its own thread.
		for (GameObjectVectorWrapper::t_GameObject_Vector_Iterator_ iter = m_sceneGameObjects_.begin(); iter != m_sceneGameObjects_.end(); ++iter) {
			//Get the render component from the GameObject list and let it render itself.
			RenderComponent * render = (*iter).GetComponentByType<RenderComponent>();
			render->Render(Projection, View);

		}
	}



}

void Renderer::setScene(Scene * pScene) {
	m_CurrentScene_ = pScene;
}

