#include "Rendering\Components\Lights\DirectionalLight.h"



DirectionalLight::DirectionalLight(std::string pShader) {
	setShader(pShader);
	setUniformName("directionalLights");
	m_ComponentName = "DIRECTIONAL_LIGHT";

}

DirectionalLight::DirectionalLight(std::string pShader, glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec) : m_Direction_(glm::vec3(0.0f, -1.0f, 0.0f)) {
	setShader(pShader);
	setUniformName("directionalLights");
	m_Direction_ = dir;
	setAmbient(amb);
	setDiffuse(diff);
	setSpecular(spec);

	setDirty(true);
	m_ComponentName = "DIRECTIONAL_LIGHT";

}



//Called every tick.
void DirectionalLight::Update(double dt) {

}

//Called at the end of every tick, mainly for maintenance uses.
void DirectionalLight::LateUpdate(double dt) {

}

//Called when the component is destroyed.
void DirectionalLight::Destroy() {

}

//Called when the component starts.
void DirectionalLight::Start() {

}

void DirectionalLight::UpdateLightUniforms(int pos){

	ShaderUniform lightDirection;
	lightDirection.M_Address = getUniformName() + "[" + std::to_string(pos) + "].direction";
	lightDirection.M_Type = ShaderType::VEC3;
	lightDirection.M_Vec3 = m_Direction_;

	ResourceManager::getInstance()->GetShader(getShader())->SetUniform(lightDirection);

	setDirty(false);

}