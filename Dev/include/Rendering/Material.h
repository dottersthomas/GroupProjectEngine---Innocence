#ifndef _RENDERING_MATERIAL_H_
#define _RENDERING_MATERIAL_H_

#include "Texture.h"
#include "ShaderUniform.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class Material {

public:
	Material() {
		m_hasTextures_ = false;

	}

	Material(std::string pDiffuse, std::string pSpecular, float pShine);
	Material(std::vector<std::string> pTextures, float pShine);
	Material(glm::vec3 pDiffuse, glm::vec3 pSpecular, float pShine);

	void UpdateUniforms(std::string pShader);

	void BindTextures(std::string pShader);
	
	void assignDiffuseTexture(std::string pDiffuse) {
		m_Textures_.push_back(pDiffuse);
		m_hasTextures_ = true;
	}

	void assignSpecularTexture(std::string pSpecular) {
		m_Textures_.push_back(pSpecular);
		m_hasTextures_ = true;
	}

	void assignDiffuseColour(glm::vec3 pColour) {
		m_diffuseColour_ = pColour;
	}


	void assignSpecularColour(glm::vec3 pColour) {
		m_specularColour_ = pColour;
	}

	void setShininess(float pShine) {
		m_Shininess_ = pShine;
	}

	bool getTexturesAssigned() {
		return m_hasTextures_;
	}

private:

	bool m_hasTextures_;

	std::vector<std::string> m_Textures_;

	ShaderUniform m_normalMap_;

	glm::vec3 m_diffuseColour_;
	glm::vec3 m_specularColour_;


	float m_Shininess_;


};


#endif // !_RENDERING_MATERIAL_H_

