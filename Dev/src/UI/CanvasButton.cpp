#include "UI\CanvasButton.h"
#include "Rendering\ResourceManager.h"
#include "General\Proxy.h"
#include "General\InputHandler.h"


void CanvasButton::Start()  {
	m_CurrentState_ = GuiStates::NORMAL;

}

void CanvasButton::Update(float dt)  {

	double mouseX, mouseY;

	Proxy::getInstance()->requestCursorPos(mouseX, mouseY);






	m_CurrentState_ = GuiStates::NORMAL;



	if(m_Position_.x < mouseX && (m_Position_.x + m_Scale_.x) > mouseX)
		if (m_Position_.y < mouseY && (m_Position_.y + m_Scale_.y) > mouseY) {
			m_CurrentState_ = GuiStates::HOVERED;
			
			if (InputHandler::isButtonDown(GLFW_MOUSE_BUTTON_LEFT))
				onclick();
		}






	//Update this elements children if it has any.
	UpdateChildren(dt);
}

void CanvasButton::Render() {
	//Set the colour.

	if(m_CurrentState_ == GuiStates::NORMAL)
		ResourceManager::getInstance()->GetShader(m_Shader_)->SetVector4f("elementColour", m_Colour_);
	else if (m_CurrentState_ == GuiStates::HOVERED)
		ResourceManager::getInstance()->GetShader(m_Shader_)->SetVector4f("elementColour", m_HoverColour_);


	m_Model_ = glm::mat4(1.0f);

	//Process the Model Matrix and push it to the GPU.
	m_Model_ = glm::translate(m_Model_, glm::vec3(m_Position_, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

	m_Model_ = glm::scale(m_Model_, glm::vec3(m_Scale_, 1.0f)); // Last scale

	ResourceManager::getInstance()->GetShader(m_Shader_)->SetMatrix4("model", m_Model_);


	//No texture will be used so no need to concern the render process with it.



	glBindVertexArray(*m_Mesh_.VAO);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
}

void CanvasButton::Destroy() {

}


void CanvasButton::onclick() {
	if(m_ClickHandle != nullptr)
		m_ClickHandle();
}