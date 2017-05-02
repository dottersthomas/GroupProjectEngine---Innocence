#ifndef _RENDERING_LIGHT_H_
#define _RENDERING_LIGHT_H_

#include <glm\glm.hpp>

#include "Component.h"
#include "Rendering\ShaderUniform.h"
#include "Rendering\ResourceManager.h"

class Light : public Component {

public:
	Light() {}
	Light(std::string pShader, std::string pUniformName) {
		setShader(pShader);
		setUniformName(pUniformName);
	}
//	Light(std::string pShader, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec) /*: m_Ambient_(glm::vec3(0.2f, 0.2f, 0.2f)), m_Diffuse_(glm::vec3(1.0f, 1.0f, 1.0f)), m_Specular_(glm::vec3(1.0f, 1.0f, 1.0f))*/;


	//Called every tick.
	virtual void Update(double dt) = 0;

	//Called at the end of every tick, mainly for maintenance uses.
	virtual void LateUpdate(double dt) = 0;

	//Called when the component is destroyed.
	virtual void Destroy() = 0;

	//Called when the component starts.
	virtual void Start() = 0;

	virtual void UpdateLightUniforms(int pos) = 0;

	void setShader(std::string pShader) {
		m_Shader_ = pShader;
	}

	void setAmbient(glm::vec3 amb) {
		setDirty(true);
		m_Ambient_ = amb;
	}

	void setDiffuse(glm::vec3 diff) {
		setDirty(true);

		m_Diffuse_ = diff;
	}

	void setSpecular(glm::vec3 spec) {
		setDirty(true);

		m_Specular_ = spec;
	}

	void setUniformName(std::string pName) {
		setDirty(true);

		m_UniformName_ = pName;
	}

	std::string getUniformName() {
		return m_UniformName_;
	}

	void updateColourUniforms(int pos) {

		ShaderUniform ambient;
		ambient.M_Address = m_UniformName_ + "[" + std::to_string(pos) + "].ambient";
		ambient.M_Type = VEC3;
		ambient.M_Vec3 = m_Ambient_;

		ShaderUniform diffuse;
		diffuse.M_Address = m_UniformName_ + "[" + std::to_string(pos) + "].diffuse";
		diffuse.M_Type = VEC3;
		diffuse.M_Vec3 = m_Diffuse_;

		ShaderUniform specular;
		specular.M_Address = m_UniformName_ + "[" + std::to_string(pos) + "].specular";
		specular.M_Type = VEC3;
		specular.M_Vec3 = m_Specular_;


		ResourceManager::getInstance()->GetShader(m_Shader_)->SetUniform(ambient);
		ResourceManager::getInstance()->GetShader(m_Shader_)->SetUniform(diffuse);
		ResourceManager::getInstance()->GetShader(m_Shader_)->SetUniform(specular);

		setDirty(false);	


	}

	std::string getShader() {
		return m_Shader_;
	}

	bool isDirty() {
		return m_IsDirty_;
	}

	void setDirty(bool dirty) {
		m_IsDirty_ = dirty;
	}

private:
	std::string m_Shader_;
	std::string m_UniformName_;

	glm::vec3 m_Ambient_;
	glm::vec3 m_Diffuse_;
	glm::vec3 m_Specular_;

	bool m_IsDirty_ = true;

};



#endif // !_RENDERING_LIGHT_H_

