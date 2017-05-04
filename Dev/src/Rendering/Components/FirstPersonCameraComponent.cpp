#include "Rendering\Components\FirstPersonCameraComponent.h"
#include "General\Proxy.h"

FirstPersonCameraComponent::FirstPersonCameraComponent(GameObject * pParent, std::string pName, glm::vec3 pPosition) {

	m_GameObjectParent_ = pParent;
	m_ComponentName = pName;


	int width, height;
	Proxy::getInstance()->requestWindowSize(width, height);

	m_Position_ = pPosition;

	m_iWindowX_ = width;
	m_iWindowY_ = height;

	m_fHorizontalAngle_ = 3.14f;
	m_fVerticalAngle_ = 0.0f;

	m_bLimitVert_ = true;

	//Update properly.
	m_dMousePosX_ = width / 2;
	m_dMousePosY_ = height / 2;
}

void FirstPersonCameraComponent::Update(double dt) {
	if (m_Active_) {
		Proxy::getInstance()->requestCursorPos(m_dMousePosX_, m_dMousePosY_);
		m_fHorizontalAngle_ += m_fMouseSpeed_ * dt * float(m_iWindowX_ / 2 - m_dMousePosX_);
		m_fVerticalAngle_ += m_fMouseSpeed_ * dt * float(m_iWindowY_ / 2 - m_dMousePosY_);
		if (m_bLimitVert_) {
			if (m_fVerticalAngle_ > (3.142 / 2)) m_fVerticalAngle_ = (3.142 / 2);
			if (m_fVerticalAngle_ < -(3.142 / 2)) m_fVerticalAngle_ = -(3.142 / 2);

		}

		// Direction : Spherical coordinates to Cartesian coordinates conversion.
		m_GameObjectParent_->GetComponentByType<TransformComponent>()->setDirection(glm::normalize(glm::vec3(
			cos(m_fVerticalAngle_) * sin(m_fHorizontalAngle_),
			sin(m_fVerticalAngle_),
			cos(m_fVerticalAngle_) * cos(m_fHorizontalAngle_)
		)));

		// Right vector
		m_GameObjectParent_->GetComponentByType<TransformComponent>()->setRight(glm::normalize(glm::vec3(
			sin(m_fHorizontalAngle_ - 3.14f / 2.0f),
			0,
			cos(m_fHorizontalAngle_ - 3.14f / 2.0f)
		)));



		//Up vector
		m_Up_ = glm::normalize(glm::cross(
			m_GameObjectParent_->GetComponentByType<TransformComponent>()->getRight(),
			m_GameObjectParent_->GetComponentByType<TransformComponent>()->getDirection()));
	}
}

void FirstPersonCameraComponent::LateUpdate(double dt) {
	//After the update is complete, update the data for the next update call.
	if (m_Active_) {
		int width, height;
		Proxy::getInstance()->requestWindowSize(width, height);

		Proxy::getInstance()->requestCursorPositionChange(width / 2, height / 2);
	}
}

void FirstPersonCameraComponent::Destroy() {

}
void FirstPersonCameraComponent::Start() {
	int width, height;
	Proxy::getInstance()->requestWindowSize(width, height);

	Proxy::getInstance()->requestCursorPositionChange(width / 2, height / 2);
}

glm::mat4 FirstPersonCameraComponent::Bind() {
	m_View_ = glm::lookAt(
		(m_Position_ + m_GameObjectParent_->GetComponentByType<TransformComponent>()->getPosition()),				// Camera is here
		(m_Position_ + m_GameObjectParent_->GetComponentByType<TransformComponent>()->getPosition()) 
		+ m_GameObjectParent_->GetComponentByType<TransformComponent>()->getDirection(), // and looks here : at the same position, plus "direction"
		m_Up_						// Head is up (set to 0,-1,0 to look upside-down)
	);
	return m_View_;
}