#include "UI\Text2D.h"
#include "Rendering\ResourceManager.h"


Text2D::Text2D(std::string pShader, std::string pText) {
	m_Shader_ = pShader;
	m_Text_ = pText;

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_Scale_ = glm::vec2(1.0, 1.0);
}



void Text2D::Start() {
	
}

void Text2D::Update(float dt) {

}

void Text2D::Render() {
	if (ResourceManager::getInstance()->getCurrentShaderID() != m_Shader_) {
		ResourceManager::getInstance()->GetShader(m_Shader_).Use();
	}

	ResourceManager::getInstance()->GetShader(m_Shader_).SetVector4f("textColor", getColour());

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->quadVAO);

	std::string text;

	if (usesID) {
		text = ResourceManager::getInstance()->getText(m_Text_);
	}
	else {
		text = m_Text_;
	}
	
	
	int tempx = m_Position_.x;
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = ResourceManager::getInstance()->getCharacter(*c);
		GLfloat xPos = tempx + ch.h;
		GLfloat yPos = m_Position_.y;

		GLfloat h = ch.h * m_Scale_.y;
		GLfloat w = ch.w * m_Scale_.x;

		GLfloat vertices[6][4] = {
			{ xPos,     yPos + h,   0.0, 0.0 },
			{ xPos,     yPos,       0.0, 1.0 },
			{ xPos + w, yPos,       1.0, 1.0 },

			{ xPos,     yPos + h,   0.0, 0.0 },
			{ xPos + w, yPos,       1.0, 1.0 },
			{ xPos + w, yPos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		if (*c != ' ') {

		
			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		tempx += (h);
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableVertexAttribArray(0);
}

void Text2D::Destroy() {

}