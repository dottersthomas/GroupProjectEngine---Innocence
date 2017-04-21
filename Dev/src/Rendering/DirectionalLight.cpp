#include "Rendering\DirectionalLight.h"



DirectionalLight::DirectionalLight(std::string pShader) {

}

DirectionalLight::DirectionalLight(std::string pShader, glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec) {

	m_Direction_ = dir;
	setAmbient(amb);
	setDiffuse(diff);
	setSpecular(spec);
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