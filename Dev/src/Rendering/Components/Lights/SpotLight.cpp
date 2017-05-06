#include "Rendering\Components\Lights\SpotLight.h"



SpotLight::SpotLight(std::string pShader) {
	setShader(pShader);
	setUniformName("spotLights");
}

SpotLight::SpotLight(std::string pShader, glm::vec3 pos, glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float cutoff) : m_Position_(glm::vec3(0.0f, 0.0f, 0.0f)), m_Direction_(glm::vec3(0.0f, -1.0f, 0.0f)), m_CutOff_(12.5f) {
	setShader(pShader);
	setUniformName("spotLights");

	m_Direction_ = dir;
	m_Position_ = pos;
	m_CutOff_ = cutoff;
	m_SoftCutoff_ = cutoff + 5.0f;


	setAmbient(amb);
	setDiffuse(diff);
	setSpecular(spec);

	setDirty(true);

}



//Called every tick.
void SpotLight::Update(double dt) {

}

//Called at the end of every tick, mainly for maintenance uses.
void SpotLight::LateUpdate(double dt) {

}

//Called when the component is destroyed.
void SpotLight::Destroy() {

}

//Called when the component starts.
void SpotLight::Start() {

}

void SpotLight::UpdateLightUniforms(int pos) {

	ShaderUniform lightDirection;
	lightDirection.M_Address = getUniformName() + "[" + std::to_string(pos) + "].direction";
	lightDirection.M_Type = ShaderType::VEC3;
	lightDirection.M_Vec3 = m_Direction_;

	ShaderUniform lightCutOff;
	lightCutOff.M_Address = getUniformName() + "[" + std::to_string(pos) + "].cutoff";
	lightCutOff.M_Type = ShaderType::FLOAT;
	lightCutOff.M_Float = m_CutOff_;

	ShaderUniform lightSoftCutOff;
	lightSoftCutOff.M_Address = getUniformName() + "[" + std::to_string(pos) + "].softcutoff";
	lightSoftCutOff.M_Type = ShaderType::FLOAT;
	lightSoftCutOff.M_Float = m_SoftCutoff_;

	ShaderUniform lightPosition;
	lightPosition.M_Address = getUniformName() + "[" + std::to_string(pos) + "].position";
	lightPosition.M_Type = ShaderType::VEC3;
	lightPosition.M_Vec3 = m_Position_;

	ResourceManager::getInstance()->GetShader(getShader())->SetUniform(lightDirection);
	ResourceManager::getInstance()->GetShader(getShader())->SetUniform(lightCutOff);
	ResourceManager::getInstance()->GetShader(getShader())->SetUniform(lightSoftCutOff);
	ResourceManager::getInstance()->GetShader(getShader())->SetUniform(lightPosition);

	setDirty(false);

}