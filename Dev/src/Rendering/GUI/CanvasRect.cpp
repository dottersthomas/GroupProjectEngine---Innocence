#include "Rendering\GUI\CanvasRect.h"
#include "Rendering\ResourceManager.h"

void CanvasRect::Start() {

}
void CanvasRect::Update(float dt) {


	//Update this elements children if it has any.
	UpdateChildren(dt);
}

void CanvasRect::Render() {

	//Set the colour.
	ResourceManager::getInstance()->GetShader(m_Shader_).SetVector4f("elementColour", m_Colour_);


	m_Model_ = glm::mat4(1.0f);

	//Process the Model Matrix and push it to the GPU.
	m_Model_ = glm::translate(m_Model_, glm::vec3(m_Position_, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

	m_Model_ = glm::scale(m_Model_, glm::vec3(m_Scale_, 1.0f)); // Last scale

	ResourceManager::getInstance()->GetShader(m_Shader_).SetMatrix4("model", m_Model_);


	//No texture will be used so no need to concern the render process with it.



	glBindVertexArray(*m_Mesh_.VAO);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
}


void CanvasRect::Destroy() {

}