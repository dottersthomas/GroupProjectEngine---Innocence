#ifndef _RENDERING_MATERIAL_H_
#define _RENDERING_MATERIAL_H_

#include "Texture.h"
#include "ShaderUniform.h"


#include <iostream>

class Material {

public:
	Material() {}


private:
	//Textures.
	ShaderUniform m_diffuseTexture_;
	ShaderUniform m_specularTexture_;

	ShaderUniform m_normalMap_;


	float m_Shininess_;


};


#endif // !_RENDERING_MATERIAL_H_

