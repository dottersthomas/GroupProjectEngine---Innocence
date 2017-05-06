#include "Rendering\Renderer.h"
#include "Rendering\Components\RenderComponent.h"

#include "Physics\Components\BoxCollider.h"
#include "General\WindowManager.h"

bool Renderer::hasResized = false;


void Renderer::window_size_callback(GLFWwindow* window, int width, int height)
{
	hasResized = true;

}


Renderer::Renderer(GLFWwindow * pWindow) {
	m_Window_ = pWindow;


	glClearColor(0.9f, 0.6f, 0.4f, 1.0f);

	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_CurrentScene_ = nullptr;

	

	glfwGetFramebufferSize(WindowManager::getInstance().getWindow(), &screen_width, &screen_height);


	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_fbo_texture_);
	glBindTexture(GL_TEXTURE_2D, m_fbo_texture_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screen_width, screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	/* Depth buffer */
	glGenRenderbuffers(1, &m_rbo_depth_);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo_depth_);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, screen_width, screen_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	/* Framebuffer to link everything together */
	glGenFramebuffers(1, &m_FBO_);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO_);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fbo_texture_, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo_depth_);


	GLenum status;
	if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE) {
		fprintf(stderr, "glCheckFramebufferStatus: error %p", status);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLfloat quadVertices[] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
								 // Positions   // TexCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	GLuint quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glBindVertexArray(0);


	/*glDeleteRenderbuffers(1, &m_rbo_depth_);
	glDeleteTextures(1, &m_fbo_texture_);
	glDeleteFramebuffers(1, &m_FBO_);
	glDeleteBuffers(1, &vbo_fbo_vertices);*/



	::glfwSetWindowSizeCallback(WindowManager::getInstance().getWindow(), Renderer::window_size_callback);

}


void Renderer::Render() {

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);     // Cull back facing polygons
	glCullFace(GL_BACK);


	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO_);



	float ratio = screen_width / (float)screen_height;

	if (hasResized) {
		glfwGetFramebufferSize(WindowManager::getInstance().getWindow(), &screen_width, &screen_height);

	
		glBindTexture(GL_TEXTURE_2D, m_fbo_texture_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screen_width, screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo_depth_);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, screen_width, screen_height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		hasResized = false;
	}


	glm::mat4 Projection = glm::perspective(45.0f, ratio, 0.1f, 20000.f);

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

		}




		//Draw Scene to Texture.
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST); // We don't care about depth information when rendering a single quad

								  // Draw Screen
		ResourceManager::getInstance()->GetShader("post_process_fbo")->Use();

		if (m_CurrentScene_->shouldPostProcess()) {
			ResourceManager::getInstance()->GetShader("post_process_fbo")->SetInteger("ppToggle", 1);

		}
		else {
			ResourceManager::getInstance()->GetShader("post_process_fbo")->SetInteger("ppToggle", 0);

		}

		glActiveTexture(GL_TEXTURE0);


		glBindVertexArray(quadVAO);
		glBindTexture(GL_TEXTURE_2D, m_fbo_texture_);	// Use the color attachment texture as the texture of the quad plane
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);



	}
	







}

void Renderer::setScene(Scene * pScene) {
	m_CurrentScene_ = pScene;
}

void Renderer::update(float dt) {

	m_LightManager_.update(dt);
}

