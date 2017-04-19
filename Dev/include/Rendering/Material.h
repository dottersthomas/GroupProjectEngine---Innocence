#ifndef _RENDERING_MATERIAL_H_
#define _RENDERING_MATERIAL_H_

#include "Texture.h"



#include <iostream>

class Material {

public:
	Material() {}


private:
	//Textures.
	std::string m_diffuseTexture_;
	std::string m_specularTexture_;

	std::string m_normalMap_;


	float m_Shininess_;


};


#endif // !_RENDERING_MATERIAL_H_

