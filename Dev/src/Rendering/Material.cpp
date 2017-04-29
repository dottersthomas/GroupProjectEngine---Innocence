#include "Rendering\Material.h"

#include "Rendering\ResourceManager.h"

Material::Material(std::string pDiffuse, std::string pSpecular, float pShine) {
	m_hasTextures_ = true;

	m_Textures_.push_back(pDiffuse);
	m_Textures_.push_back(pSpecular);

	m_Shininess_ = pShine;
}

Material::Material(glm::vec3 pDiffuse, glm::vec3 pSpecular, float pShine) {
	m_diffuseColour_ = pDiffuse;
	m_specularColour_ = pSpecular;

	m_Shininess_ = pShine;

}

Material::Material(std::vector<std::string> pTextures, float pShine) {
	m_Textures_ = pTextures;

	m_Shininess_ = pShine;
}

void Material::UpdateUniforms(std::string pShader) {


	ShaderUniform toggle;
	toggle.M_Address = "material.hasTexture";
	toggle.M_Type = INT;
	if (m_hasTextures_)
		toggle.M_Int = 1;
	else
		toggle.M_Int = 0;

	ShaderUniform shininess;
	shininess.M_Address = "material.shininess";
	shininess.M_Type = FLOAT;
	shininess.M_Float = m_Shininess_;

	ShaderUniform diffuse;
	ShaderUniform specular;


	if (m_hasTextures_) {
		/*diffuse.M_Address = "material.diffuseTexture";
		diffuse.M_Type = INT;
		diffuse.M_Int = 0;

		specular.M_Address = "material.specularTexture";
		specular.M_Type = INT;
		specular.M_Int = 1;*/
	}
	else {
		diffuse.M_Address = "material.colour_diffuse";
		diffuse.M_Type = VEC3;
		diffuse.M_Vec3 = m_diffuseColour_;

		specular.M_Address = "material.colour_specular";
		specular.M_Type = VEC3;
		specular.M_Vec3 = m_specularColour_;
	}

	ResourceManager::getInstance()->GetShader(pShader).SetUniform(toggle);
	ResourceManager::getInstance()->GetShader(pShader).SetUniform(shininess);
	ResourceManager::getInstance()->GetShader(pShader).SetUniform(diffuse);
	ResourceManager::getInstance()->GetShader(pShader).SetUniform(specular);

}


void Material::BindTextures(std::string pShader) {

	if (m_hasTextures_) {
		GLuint diffuseNr = 1;
		GLuint specularNr = 1;
		for (GLuint i = 0; i < m_Textures_.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
											  // Retrieve texture number (the N in diffuse_textureN)
			std::stringstream ss;
			std::string number;
			std::string name = ResourceManager::getInstance()->GetTexture(m_Textures_[i]).type;
			if (name == "texture_diffuse")
				ss << diffuseNr++; // Transfer GLuint to stream
			else if (name == "texture_specular")
				ss << specularNr++; // Transfer GLuint to stream
			number = ss.str();
			// Now set the sampler to the correct texture unit

			ShaderUniform uniform;
			uniform.M_Address = std::string("material.") + std::string(name + number);
			uniform.M_Type = INT;
			uniform.M_Int = i;

			ResourceManager::getInstance()->GetShader(pShader).SetUniform(uniform);
			// And finally bind the texture
			ResourceManager::getInstance()->GetTexture(m_Textures_[i]).Bind();
		}
	}
}