#ifndef _RENDERING_LIGHT_H_
#define _RENDERING_LIGHT_H_

#include <glm\glm.hpp>

#include "Component.h"
#include "ShaderUniform.h"
#include "ResourceManager.h"

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

	void setShader(std::string pShader) {
		m_Shader_ = pShader;
	}

	void setAmbient(glm::vec3 amb) {
		m_Ambient_ = amb;
	}

	void setDiffuse(glm::vec3 diff) {
		m_Diffuse_ = diff;
	}

	void setSpecular(glm::vec3 spec) {
		m_Specular_ = spec;
	}

	void setUniformName(std::string pName) {
		m_UniformName_ = pName;
	}

	void updateColourUniforms() {
		ShaderUniform ambient;
		ambient.M_Address = "";
	}

private:
	std::string m_Shader_;
	std::string m_UniformName_;

	glm::vec3 m_Ambient_;
	glm::vec3 m_Diffuse_;
	glm::vec3 m_Specular_;

};



#endif // !_RENDERING_LIGHT_H_

