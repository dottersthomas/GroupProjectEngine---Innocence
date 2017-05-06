#include "Rendering\SkyBox.h"


SkyBox::SkyBox(std::string pShader, std::vector<const GLchar* > paths) {
	m_ShaderName_ = pShader;
	m_Shader_ = ResourceManager::getInstance()->GetShader(pShader);
	CubeMapTexture * texture = ResourceManager::getInstance()->loadCubemap(paths, false, "texture_skybox", "texture_skybox");
	m_Material_.assignCubeMap(texture);

	GLfloat skyboxVertices[] = {
		// Positions          
		-10000.0f,  10000.0f, -10000.0f,
		-10000.0f, -10000.0f, -10000.0f,
		10000.0f, -10000.0f, -10000.0f,
		10000.0f, -10000.0f, -10000.0f,
		10000.0f,  10000.0f, -10000.0f,
		-10000.0f,  10000.0f, -10000.0f,

		-10000.0f, -10000.0f,  10000.0f,
		-10000.0f, -10000.0f, -10000.0f,
		-10000.0f,  10000.0f, -10000.0f,
		-10000.0f,  10000.0f, -10000.0f,
		-10000.0f,  10000.0f,  10000.0f,
		-10000.0f, -10000.0f,  10000.0f,

		10000.0f, -10000.0f, -10000.0f,
		10000.0f, -10000.0f,  10000.0f,
		10000.0f,  10000.0f,  10000.0f,
		10000.0f,  10000.0f,  10000.0f,
		10000.0f,  10000.0f, -10000.0f,
		10000.0f, -10000.0f, -10000.0f,

		-10000.0f, -10000.0f,  10000.0f,
		-10000.0f,  10000.0f,  10000.0f,
		10000.0f,  10000.0f,  10000.0f,
		10000.0f,  10000.0f,  10000.0f,
		10000.0f, -10000.0f,  10000.0f,
		-10000.0f, -10000.0f,  10000.0f,

		-10000.0f,  10000.0f, -10000.0f,
		10000.0f,  10000.0f, -10000.0f,
		10000.0f,  10000.0f,  10000.0f,
		10000.0f,  10000.0f,  10000.0f,
		-10000.0f,  10000.0f,  10000.0f,
		-10000.0f,  10000.0f, -10000.0f,

		-10000.0f, -10000.0f, -10000.0f,
		-10000.0f, -10000.0f,  10000.0f,
		10000.0f, -10000.0f, -10000.0f,
		10000.0f, -10000.0f, -10000.0f,
		-10000.0f, -10000.0f,  10000.0f,
		10000.0f, -10000.0f,  10000.0f
	};

	GLuint skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);
}


void SkyBox::Render(glm::mat4 pProj, glm::mat4 pView) {
	glDepthMask(GL_FALSE);

	if (ResourceManager::getInstance()->getCurrentShaderID() != m_ShaderName_) {
		ResourceManager::getInstance()->useShader(m_ShaderName_); //Error check for false shader switch.
	}
	m_Shader_->UpdateShaderUniforms();

	m_Shader_->SetMatrix4("mProjection", pProj);
	m_Shader_->SetMatrix4("mView", pView);

	glBindVertexArray(skyboxVAO);


	m_Material_.UpdateUniforms(m_ShaderName_);
	m_Material_.BindTextures(m_ShaderName_);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);

}