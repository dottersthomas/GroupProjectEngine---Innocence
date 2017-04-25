#ifndef _RENDERING_MATERIAL_H_
#define _RENDERING_MATERIAL_H_

#include "Texture.h"
#include "ShaderUniform.h"


#include <iostream>

class Material {

public:
	Material() {
		m_hasTextures_ = false;

	}

	Material(std::string pDiffuse, std::string pSpecular, float pShine);

	void UpdateUniforms(std::string pShader);
	
	void assignDiffuseTexture(std::string pDiffuse) {
		m_diffuseTexture_ = pDiffuse;
		m_hasTextures_ = true;
	}

	void assignSpecularTexture(std::string pSpecular) {
		m_specularTexture_ = pSpecular;
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

	std::string getDiffuseTexture() {
		return m_diffuseTexture_;
	}

	std::string getSpecularTexture() {
		return m_specularTexture_;
	}

private:

	bool m_hasTextures_;

	//Textures.
	std::string m_diffuseTexture_;
	std::string m_specularTexture_;

	ShaderUniform m_normalMap_;

	glm::vec3 m_diffuseColour_;
	glm::vec3 m_specularColour_;


	float m_Shininess_;


};


#endif // !_RENDERING_MATERIAL_H_

