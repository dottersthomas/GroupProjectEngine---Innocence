#ifndef _RENDERING_MATERIAL_H_
#define _RENDERING_MATERIAL_H_

#include "Texture.h"
#include "ShaderUniform.h"
#include "Rendering\Colour.h"
#include "Rendering\CubeMapTexture.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class Material {

public:
	Material() {
		m_hasTextures_ = false;
		m_hasCubeMaps_ = false;
	}

	Material(Texture * pDiffuse, Texture * pSpecular, float pShine);
	Material(std::vector<Texture * > pTextures, float pShine);
	Material(glm::vec3 pDiffuse, glm::vec3 pSpecular, float pShine);
	Material(std::vector<Colour> pColours, float pShine);

	void UpdateUniforms(std::string pShader);

	void BindTextures(std::string pShader);
	
	void assignDiffuseTexture(Texture *  pDiffuse) {
		m_Textures_.push_back(pDiffuse);
		m_hasTextures_ = true;
	}

	void assignSpecularTexture(Texture *  pSpecular) {
		m_Textures_.push_back(pSpecular);
		m_hasTextures_ = true;
	}

	void assignCubeMap(CubeMapTexture * pMap) {
		m_CubeMaps_.push_back(pMap);
		m_hasCubeMaps_ = true;
	}

	void assignDiffuseColour(Colour pColour) {
		m_Colours_.push_back( pColour);
	}


	void assignSpecularColour(Colour pColour) {
		m_Colours_.push_back(pColour);
	}

	void setShininess(float pShine) {
		m_Shininess_ = pShine;
	}

	bool getTexturesAssigned() {
		return m_hasTextures_;
	}

	void setNormalMapToggle(bool pMap) {
		hasNormalMap = pMap;
	}

	bool getNormalMapAssigned() {
		return hasNormalMap;
	}

private:

	bool m_hasTextures_;
	bool m_hasCubeMaps_;
	std::vector<Texture *> m_Textures_;
	std::vector<CubeMapTexture *> m_CubeMaps_;
	std::vector<Colour> m_Colours_;

	std::vector<ShaderUniform> uniforms;

	bool hasNormalMap = false;


	float m_Shininess_;

	void CreateUniforms();


};


#endif // !_RENDERING_MATERIAL_H_

