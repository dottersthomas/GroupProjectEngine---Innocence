#include "Components\ThirdPersonCameraComponent.h"


ThirdPersonCameraComponent::ThirdPersonCameraComponent(GameObject * pParent, std::string pName, float pDistance, glm::vec3 pTargetRelative) {
	m_GameObjectParent_ = pParent;
	M_ComponentName = pName;

	m_CameraDistance_ = pDistance;


	int width, height;
	Proxy::getInstance()->requestWindowSize(width, height);

	m_iWindowX_ = width;
	m_iWindowY_ = height;

	m_fHorizontalAngle_ = 3.14f;
	m_fVerticalAngle_ = 0.0f;

	m_bLimitVert_ = true;

	//Update properly.
	m_dMousePosX_ = width / 2;
	m_dMousePosY_ = height / 2;

}


void ThirdPersonCameraComponent::Update(double dt) {

	if (m_Active_) {

		Proxy::getInstance()->requestCursorPos(m_dMousePosX_, m_dMousePosY_);
		m_fHorizontalAngle_ += m_fMouseSpeed_ * dt * float(m_iWindowX_ / 2 - m_dMousePosX_);
		m_fVerticalAngle_ += m_fMouseSpeed_ * dt * float(m_iWindowY_ / 2 - m_dMousePosY_);
		if (m_bLimitVert_) {
			if (m_fVerticalAngle_ > (3.142 / 2.1)) m_fVerticalAngle_ = (3.142 / 2.1);
			if (m_fVerticalAngle_ < -(3.142 / 2.1)) m_fVerticalAngle_ = -(3.142 / 2.1);
		}


		float targetX = m_TargetPosRelative_.x + m_GameObjectParent_->GetComponentByType<TransformComponent>()->getPosition().x;
		float targetY = m_TargetPosRelative_.y + m_GameObjectParent_->GetComponentByType<TransformComponent>()->getPosition().y;
		float targetZ = m_TargetPosRelative_.z + m_GameObjectParent_->GetComponentByType<TransformComponent>()->getPosition().z;


		m_AbsolutePosition_ = glm::vec3(
			m_CameraDistance_ * sin(m_fHorizontalAngle_) * sin(m_fVerticalAngle_ + (3.14f / 2.0f)) + targetX,
			m_CameraDistance_ * cos(m_fVerticalAngle_ + (3.14f / 2.0f)) + targetY,
			m_CameraDistance_ * cos(m_fHorizontalAngle_) * sin(m_fVerticalAngle_ + (3.14f / 2.0f)) + targetZ
		);


		m_GameObjectParent_->GetComponentByType<TransformComponent>()->setDirection((m_TargetPosRelative_ + m_GameObjectParent_->GetComponentByType<TransformComponent>()->getPosition()) - m_AbsolutePosition_);
		m_GameObjectParent_->GetComponentByType<TransformComponent>()->setRight(glm::vec3(
			m_GameObjectParent_->GetComponentByType<TransformComponent>()->getDirection().z,
			0.0f,
			-m_GameObjectParent_->GetComponentByType<TransformComponent>()->getDirection().x));

		m_Up_ = glm::cross(
			m_GameObjectParent_->GetComponentByType<TransformComponent>()->getDirection(),
			m_GameObjectParent_->GetComponentByType<TransformComponent>()->getRight());
	}

}
void ThirdPersonCameraComponent::LateUpdate(double dt) {
	if (m_Active_) {
		int width, height;
		Proxy::getInstance()->requestWindowSize(width, height);

		Proxy::getInstance()->requestCursorPositionChange(width / 2, height / 2);
	}
}

void ThirdPersonCameraComponent::Destroy() {

}
void ThirdPersonCameraComponent::Start() {

	int width, height;
	Proxy::getInstance()->requestWindowSize(width, height);

	Proxy::getInstance()->requestCursorPositionChange(width / 2, height / 2);
}

glm::mat4 ThirdPersonCameraComponent::Bind() {
	m_View_ = glm::lookAt( m_AbsolutePosition_,				// Camera is here
		m_TargetPosRelative_ + m_GameObjectParent_->GetComponentByType<TransformComponent>()->getPosition(), // and looks here : at the same position, plus "direction"
		m_Up_						// Head is up (set to 0,-1,0 to look upside-down)
	);
	return m_View_;
}