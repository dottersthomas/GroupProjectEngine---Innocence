#include "Rendering\Components\RenderComponent.h"
#include "Rendering\ResourceManager.h"
#include "General/GameObject.h"

#include <GLFW\glfw3.h>


RenderComponent::RenderComponent(GameObject * pParent, std::string sShader, int pType) {
	m_GameObjectParent_ = pParent;
	m_Shader_ = sShader;

	transformComponent = m_GameObjectParent_->GetComponentByType<TransformComponent>();
	m_RenderType_ = pType;
	M_ComponentName = "RENDER_COMPONENT";
}

void RenderComponent::Update(double dt) {

	TransformComponent * trans = m_GameObjectParent_->GetComponentByType<TransformComponent>();
	if (m_Models_.size() > 0) {
		for (int i = 0; i < m_Models_.size(); i++) {
			m_Models_[i].Update(trans, dt);
		}
	}
}
void RenderComponent::LateUpdate(double dt) {

}

void RenderComponent::Destroy() {

}

void RenderComponent::Start() {

}

void RenderComponent::AttachMesh(Mesh * pMesh) {
	m_Meshes_.push_back(pMesh);
}


void RenderComponent::Render(glm::mat4 pProj, glm::mat4 pView) {
	//No point processing rendering if no mesh is found, altho this is unlikely as no render component would be included.
	if (shouldDraw) {

		if (ResourceManager::getInstance()->getCurrentShaderID() != m_Shader_) {
			ResourceManager::getInstance()->useShader(m_Shader_); //Error check for false shader switch.
		}
		ResourceManager::getInstance()->GetShader(m_Shader_)->UpdateShaderUniforms();


		ResourceManager::getInstance()->GetShader(m_Shader_)->SetMatrix4("mProjection", pProj);
		ResourceManager::getInstance()->GetShader(m_Shader_)->SetMatrix4("mView", pView);

		if (m_Models_.size() > 0) {
			for (int i = 0; i < m_Models_.size(); i++) {
				m_Models_[i].Render(m_Shader_, nullptr);
			}
		}


	}
}




