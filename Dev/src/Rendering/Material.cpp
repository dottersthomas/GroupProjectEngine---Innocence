#include "Rendering\Material.h"

Material::Material(std::string pDiffuse, std::string pSpecular, float pShine) {
	m_hasTextures_ = true;

	m_diffuseTexture_ = pDiffuse;
	m_specularTexture_ = pSpecular;

	m_Shininess_ = pShine;
}

void Material::UpdateUniforms(std::string pShader) {
	ShaderUniform toggle;
	toggle.M_Address = "material.hasTexture";
	toggle.M_Type = INT;
	toggle.M_Int = m_hasTextures_;

	ShaderUniform shininess;
	shininess.M_Address = "material.shininess";
	shininess.M_Type = FLOAT;
	shininess.M_Float = m_Shininess_;

	ShaderUniform diffuse;
	ShaderUniform specular;


	if (m_hasTextures_) {
		diffuse.M_Address = "material.diffuseTexture";
		diffuse.M_Type = INT;
		diffuse.M_Int = 0;

		specular.M_Address = "material.specularTexture";
		specular.M_Type = INT;
		specular.M_Int = 1;
	}
	else {
		diffuse.M_Address = "material.diffuseColour";
		diffuse.M_Type = VEC3;
		diffuse.M_Vec3 = m_diffuseColour_;

		specular.M_Address = "material.specularColour";
		specular.M_Type = VEC3;
		specular.M_Vec3 = m_specularColour_;
	}
}