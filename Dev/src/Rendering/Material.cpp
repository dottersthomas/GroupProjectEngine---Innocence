#include "Rendering\Material.h"

#include "Rendering\ResourceManager.h"

Material::Material(Texture * pDiffuse, Texture * pSpecular, float pShine) {
	m_hasTextures_ = true;

	m_Textures_.push_back(pDiffuse);
	m_Textures_.push_back(pSpecular);

	m_Shininess_ = pShine;
	m_hasCubeMaps_ = false;

	CreateUniforms();

}

Material::Material(glm::vec3 pDiffuse, glm::vec3 pSpecular, float pShine) {
//	m_diffuseColour_ = pDiffuse;
//	m_specularColour_ = pSpecular;

	m_Shininess_ = pShine;
	m_hasCubeMaps_ = false;

	CreateUniforms();

}

Material::Material(std::vector<Texture * > pTextures, float pShine) {
	m_Textures_ = pTextures;
	m_hasCubeMaps_ = false;

	if (m_Textures_.size() == 0)
		m_hasTextures_ = false;
	else {
		for (int i = 0; i < m_Textures_.size(); i++) {
			if(m_Textures_[i]->type == "texture_normal")
				hasNormalMap = true;

		}
	}

	pTextures.erase(pTextures.begin(), pTextures.end());

	m_Shininess_ = pShine;

	CreateUniforms();

}

Material::Material(std::vector<Colour> pColours, float pShine) {
	m_Colours_ = pColours;

	m_hasTextures_ = false;
	m_hasCubeMaps_ = false;

	m_Shininess_ = pShine;

	CreateUniforms();
}


void Material::CreateUniforms() {

	ShaderUniform hasNormal;
	hasNormal.M_Address = "hasNormalMap";
	hasNormal.M_Type = ShaderType::UNIFORM_INT;
	hasNormal.M_Int = hasNormalMap ? 1 : 0;


	ShaderUniform toggle;
	toggle.M_Address = "material.hasTexture";
	toggle.M_Type = ShaderType::UNIFORM_INT;
	if (m_hasTextures_)
		toggle.M_Int = 1;
	else
		toggle.M_Int = 0;

	ShaderUniform shininess;
	shininess.M_Address = "material.shininess";
	shininess.M_Type = ShaderType::UNIFORM_FLOAT;
	shininess.M_Float = m_Shininess_;

	ShaderUniform diffuse;
	ShaderUniform specular;


	if (!m_hasTextures_) {
		if (m_Colours_.size() > 0)
			for (int i = 0; i < m_Colours_.size(); i++) {
				ShaderUniform uniform;
				uniform.M_Address = "material." + m_Colours_[i].M_Type;
				uniform.M_Type = ShaderType::VEC3;
				uniform.M_Vec3 = m_Colours_[i].M_Colour;

				uniforms.push_back(uniform);
			}
	}
	uniforms.push_back(hasNormal);
	uniforms.push_back(toggle);
	uniforms.push_back(shininess);
	uniforms.push_back(diffuse);
	uniforms.push_back(specular);

}


void Material::CleanUp() {
	if (m_Textures_.size() > 0) {
		for (GLuint i = 0; i < m_Textures_.size(); i++) {

			m_Textures_[i]->UnBind();

		}
	}
}

void Material::UpdateUniforms(std::string pShader) {

	ResourceManager::getInstance()->GetShader(pShader)->UpdatePackagedUniforms(uniforms);
	
}


void Material::BindTextures(std::string pShader) {
	if(m_Textures_.size() > 0)
		if (m_hasTextures_) {

			GLuint diffuseNr = 1;
			GLuint specularNr = 1;
			GLuint normalNr = 1;

			for (GLuint i = 0; i < m_Textures_.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
												  // Retrieve texture number (the N in diffuse_textureN)
					Texture* texture = m_Textures_[i];

					//std::stringstream ss;
					std::string number;
					std::string name = texture->type;
					if (name == "texture_diffuse")
						//ss << diffuseNr++; // Transfer GLuint to stream
						number = std::to_string(diffuseNr++);
					else if (name == "texture_specular")
						//ss << specularNr++; // Transfer GLuint to stream
						number = std::to_string(specularNr++);

					else if (name == "texture_normal")
						//ss << normalNr++;
						number = std::to_string(normalNr++);
					else
						number = std::to_string(0);
					//number = ss.str();
					// Now set the sampler to the correct texture unit

					ShaderUniform uniform;
					if (std::atoi(number.c_str()) > 0)
						uniform.M_Address = std::string("material.") + std::string(name + number);
					else
						uniform.M_Address = std::string("material.") + std::string(name);
					uniform.M_Type = ShaderType::UNIFORM_INT;
					uniform.M_Int = i;

					ResourceManager::getInstance()->GetShader(pShader)->UpdateSingleUniform(uniform);
					// And finally bind the texture
					texture->Bind();
				

			}
		}
		if (m_CubeMaps_.size() > 0) {
			if (m_hasCubeMaps_) {

				for (int i = 0; i < m_CubeMaps_.size(); i++) {

					CubeMapTexture* texture = m_CubeMaps_[i];

					//std::stringstream ss;
					std::string number = "0";
					std::string name = texture->type;

					ShaderUniform uniform;
					if (std::atoi(number.c_str()) > 0)
						uniform.M_Address = std::string("material.") + std::string(name + number);
					else
						uniform.M_Address = std::string("material.") + std::string(name);
					uniform.M_Type = ShaderType::UNIFORM_INT;
					uniform.M_Int = i;

					ResourceManager::getInstance()->GetShader(pShader)->UpdateSingleUniform(uniform);
					// And finally bind the texture
					texture->Bind();
				}
			}
		}

	
}