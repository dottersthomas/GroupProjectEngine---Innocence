#include "UI\GUIRenderer.h"



GUIRenderer::GUIRenderer(GLFWwindow * pWindow) {

	m_Window_ = pWindow;

	m_CurrentScene_ = nullptr;
}

void GUIRenderer::Render() {

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);     // Cull back facing polygons
	glCullFace(GL_BACK);


	//The orthographic projection used to overlay the ui.
	Projection = glm::ortho(0.0f, 1280.f, 720.f, 0.0f, -1.0f, 1.0f);

	// Camera matrix
	View = glm::lookAt(
		glm::vec3(1, 1, 1),
		glm::vec3(1, 1, 0),
		glm::vec3(0, 1, 0)
	);



	if (m_CurrentScene_ != nullptr) {

		if (m_CurrentScene_->M_bIsDirty) {

			m_sceneGameObjects_.clear(); //Currently clearing the list, but should become more dynamic in the future.

			std::vector<GameObject> temp = *m_CurrentScene_->getGameObjects();
			for (std::vector<GameObject>::iterator iter = temp.begin(); iter != temp.end(); ++iter) {
				if ((*iter).CheckComponentTypeExists<CanvasComponent>()) {
					m_sceneGameObjects_.push_back(*iter); //Add GameObject to the list.
				}
			}
			//No need to check again.
			m_CurrentScene_->M_bIsDirty = false;
		}

		//Render the UI
		for (std::vector<GameObject>::iterator iter = m_sceneGameObjects_.begin(); iter != m_sceneGameObjects_.end(); ++iter) {

			CanvasComponent * canvas = (*iter).GetComponentByType<CanvasComponent>();
			canvas->Render(Projection, View);

		}
	}


}

void GUIRenderer::setScene(Scene * pScene) {


	m_CurrentScene_ = pScene;

}

