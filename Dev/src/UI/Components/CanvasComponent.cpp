#include "UI\Components\CanvasComponent.h"
#include "Rendering\ResourceManager.h"

CanvasComponent::CanvasComponent(GameObject * pObject) {

}


void CanvasComponent::Update(double dt) {
	for (CanvasElementVectorWrapper::t_Canvas_Elements_Iter iter = m_Elements_.begin(); iter != m_Elements_.end(); ++iter) {

		(*iter)->Update(dt);
	}
}

void CanvasComponent::Render(glm::mat4 pProjection, glm::mat4 pView) {
	if (m_Elements_.size() > 0) {

		

		for (CanvasElementVectorWrapper::t_Canvas_Elements_Iter iter = m_Elements_.begin(); iter != m_Elements_.end(); ++iter) {
			if (ResourceManager::getInstance()->getCurrentShaderID() != (*iter)->RequestShader()) 
				ResourceManager::getInstance()->useShader((*iter)->RequestShader()); //Error check for false shader switch.
			


			ResourceManager::getInstance()->GetShader((*iter)->RequestShader())->SetMatrix4("projection", pProjection);
			ResourceManager::getInstance()->GetShader((*iter)->RequestShader())->SetMatrix4("view", pView);

			(*iter)->Render();

		}
	}
}

void CanvasComponent::LateUpdate(double dt) {

}

void CanvasComponent::Destroy() {

}
void CanvasComponent::Start() {

}