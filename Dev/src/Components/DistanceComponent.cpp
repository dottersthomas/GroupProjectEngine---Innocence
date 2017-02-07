#include "Components\DistanceComponent.h"
#include "Components\RenderComponent.h"
#include "Rendering\ResourceManager.h"
#include "Proxy.h"

void DistanceComponent::Update(double dt) {

	if (!hasBeenToggled) {

		glm::vec3 tc1 = glm::vec3(m_GameObjectParent_->GetComponentByType<TransformComponent>()->getPosition().x, 0.0, m_GameObjectParent_->GetComponentByType<TransformComponent>()->getPosition().z);
		glm::vec3 tc2 = glm::vec3(m_Player_->getPosition().x, 0.0, m_Player_->getPosition().z);


		if (glm::distance(tc1, tc2) < m_Distance_) {
			m_GameObjectParent_->GetComponentByType<RenderComponent>()->toggleDrawing(false);

			Proxy::getInstance()->requestScoreIncrease(1);
			hasBeenToggled = true;
		}
	}


}
void DistanceComponent::LateUpdate(double dt) {




}

void DistanceComponent::Destroy() {




}
void DistanceComponent::Start() {




}