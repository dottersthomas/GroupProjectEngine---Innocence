#include "Rendering\LightManager.h"

void LightManager::RegisterDirectionalLight(DirectionalLight * pDir) {
	m_DirectionalLights_.push_back(pDir);
}

void LightManager::RegisterPointLight(PointLight * pPoint) {
	m_PointLights_.push_back(pPoint);
}


void LightManager::update(float dt) {

	//Update all the lights individually.
	if (m_DirectionalLights_.size() > 0) {

		for (DirectionalLightWrapper::t_Light_Iter iter = m_DirectionalLights_.begin(); iter != m_DirectionalLights_.end(); ++iter){

			(*iter)->updateColourUniforms(iter - m_DirectionalLights_.begin());
			(*iter)->UpdateLightUniforms(iter - m_DirectionalLights_.begin());

		}


	}


	//Update all the lights individually.
	if (m_PointLights_.size() > 0) {

		for (PointLightWrapper::t_Light_Iter iter = m_PointLights_.begin(); iter != m_PointLights_.end(); ++iter) {

			(*iter)->updateColourUniforms(iter - m_PointLights_.begin());
			(*iter)->UpdateLightUniforms(iter - m_PointLights_.begin());

		}


	}



}