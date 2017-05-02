#include "Rendering\Components\Lights\PointLight.h"

PointLight::PointLight(std::string pShader) {
	setShader(pShader);
	setUniformName("pointLights");
}


PointLight::PointLight(std::string pShader, glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float constant, float linear, float quadratic) {

	setShader(pShader);
	setUniformName("pointLights");

	m_Position_ = pos;

	setAmbient(amb);
	setDiffuse(diff);
	setSpecular(spec);

	m_Constant_ = constant;
	m_Linear_ = linear;
	m_Quadratic_ = quadratic;

	setDirty(true);

}


//Called every tick.
void PointLight::Update(double dt) {

}

//Called at the end of every tick, mainly for maintenance uses.
void PointLight::LateUpdate(double dt) {

}

//Called when the component is destroyed.
void PointLight::Destroy() {

}

//Called when the component starts.
void PointLight::Start() {

}

void PointLight::UpdateLightUniforms(int pos) {

	ShaderUniform lightPosition;
	lightPosition.M_Address = getUniformName() + "[" + std::to_string(pos) + "].position";
	lightPosition.M_Type = VEC3;
	lightPosition.M_Vec3 = m_Position_;

	ShaderUniform lightConstant;
	lightConstant.M_Address = getUniformName() + "[" + std::to_string(pos) + "].constant";
	lightConstant.M_Type = FLOAT;
	lightConstant.M_Float = m_Constant_;

	ShaderUniform lightLinear;
	lightLinear.M_Address = getUniformName() + "[" + std::to_string(pos) + "].linear";
	lightLinear.M_Type = FLOAT;
	lightLinear.M_Float = m_Linear_;

	ShaderUniform lightQuadratic;
	lightQuadratic.M_Address = getUniformName() + "[" + std::to_string(pos) + "].quadratic";
	lightQuadratic.M_Type = FLOAT;
	lightQuadratic.M_Float = m_Quadratic_;

	ResourceManager::getInstance()->GetShader(getShader())->SetUniform(lightPosition);
	ResourceManager::getInstance()->GetShader(getShader())->SetUniform(lightConstant);
	ResourceManager::getInstance()->GetShader(getShader())->SetUniform(lightLinear);
	ResourceManager::getInstance()->GetShader(getShader())->SetUniform(lightQuadratic);

	setDirty(false);

}