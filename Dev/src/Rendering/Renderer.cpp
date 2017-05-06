#include "Rendering\Renderer.h"
#include "Rendering\Components\RenderComponent.h"

#include "Physics\Components\BoxCollider.h"



Renderer::Renderer(GLFWwindow * pWindow) {
	m_Window_ = pWindow;


	glClearColor(0.9f, 0.6f, 0.4f, 1.0f);

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
				glm::vec3(40.0f, 40.0f, 40.0f),
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

			std::vector<GameObject> temp = *m_CurrentScene_->getGameObjects();
			for (std::vector<GameObject>::iterator iter = temp.begin(); iter != temp.end(); ++iter) {
				if ((*iter).CheckComponentTypeExists<RenderComponent>()) {
					m_sceneGameObjects_.push_back(*iter); //Add GameObject to the list.
				}
			}
			//No need to check again.
			m_CurrentScene_->M_bIsDirty = false;
		}

		m_CurrentScene_->getEnvironment()->Render(Projection, View);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//Render the scenes GameObjects. Possibly provide filtering to improve performance speed. Or maybe even have it within its own thread.
		for (std::vector<GameObject>::iterator iter = m_sceneGameObjects_.begin(); iter != m_sceneGameObjects_.end(); ++iter) {
			//Get the render component from the GameObject list and let it render itself.
			RenderComponent * render = (*iter).GetComponentByType<RenderComponent>();
			render->Render(Projection, View);


			//test
			if (iter->CheckComponentTypeExists<BoxCollider>())
			{
				BoxCollider * bc = (*iter).GetComponentByType<BoxCollider>();
				glLineWidth(2.5);
				glColor3f(1.0, 0.0, 0.0);
				glBegin(GL_LINES);
				glVertex3f(bc->GetBounds().GetMax().x, bc->GetBounds().GetMax().y, bc->GetBounds().GetMax().z);
				glVertex3f(bc->GetBounds().GetMin().x, bc->GetBounds().GetMax().y, bc->GetBounds().GetMax().z);
				glVertex3f(bc->GetBounds().GetMin().x, bc->GetBounds().GetMax().y, bc->GetBounds().GetMax().z);
				glVertex3f(bc->GetBounds().GetMin().x, bc->GetBounds().GetMax().y, bc->GetBounds().GetMin().z);
				glVertex3f(bc->GetBounds().GetMin().x, bc->GetBounds().GetMax().y, bc->GetBounds().GetMin().z);
				glVertex3f(bc->GetBounds().GetMax().x, bc->GetBounds().GetMax().y, bc->GetBounds().GetMin().z);
				glVertex3f(bc->GetBounds().GetMax().x, bc->GetBounds().GetMax().y, bc->GetBounds().GetMin().z);
				glVertex3f(bc->GetBounds().GetMax().x, bc->GetBounds().GetMin().y, bc->GetBounds().GetMin().z);
				glVertex3f(bc->GetBounds().GetMax().x, bc->GetBounds().GetMin().y, bc->GetBounds().GetMin().z);
				glVertex3f(bc->GetBounds().GetMax().x, bc->GetBounds().GetMin().y, bc->GetBounds().GetMax().z);
				glVertex3f(bc->GetBounds().GetMax().x, bc->GetBounds().GetMin().y, bc->GetBounds().GetMax().z);
				glVertex3f(bc->GetBounds().GetMin().x, bc->GetBounds().GetMin().y, bc->GetBounds().GetMax().z);
				glVertex3f(bc->GetBounds().GetMin().x, bc->GetBounds().GetMin().y, bc->GetBounds().GetMax().z);
				glVertex3f(bc->GetBounds().GetMin().x, bc->GetBounds().GetMin().y, bc->GetBounds().GetMin().z);
				glVertex3f(bc->GetBounds().GetMin().x, bc->GetBounds().GetMin().y, bc->GetBounds().GetMax().z);
				glVertex3f(bc->GetBounds().GetMax().x, bc->GetBounds().GetMin().y, bc->GetBounds().GetMax().z);
				glVertex3f(bc->GetBounds().GetMin().x, bc->GetBounds().GetMin().y, bc->GetBounds().GetMin().z);
				glVertex3f(bc->GetBounds().GetMin().x, bc->GetBounds().GetMax().y, bc->GetBounds().GetMin().z);
				glVertex3f(bc->GetBounds().GetMax().x, bc->GetBounds().GetMax().y, bc->GetBounds().GetMin().z);
				glVertex3f(bc->GetBounds().GetMax().x, bc->GetBounds().GetMin().y, bc->GetBounds().GetMin().z);
				glVertex3f(bc->GetBounds().GetMax().x, bc->GetBounds().GetMax().y, bc->GetBounds().GetMax().z);
				glVertex3f(bc->GetBounds().GetMax().x, bc->GetBounds().GetMax().y, bc->GetBounds().GetMin().z);
				glEnd();
			}

		}


	}




}

void Renderer::setScene(Scene * pScene) {
	m_CurrentScene_ = pScene;
}

void Renderer::update(float dt) {

	m_LightManager_.update(dt);
}

