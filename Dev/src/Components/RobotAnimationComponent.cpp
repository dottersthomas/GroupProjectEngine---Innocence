#include "Components\RobotAnimationComponent.h"

RobotAnimationComponent::RobotAnimationComponent(GameObject * pParent) {
	m_GameObjectParent_ = pParent;

	animate = true;

	armAngles[LEFT] = 0.0;
	armAngles[RIGHT] = 0.0;
	legAngles[LEFT] = 0.0;
	legAngles[RIGHT] = 0.0;

	armStates[LEFT] = FORWARD_STATE;
	armStates[RIGHT] = BACKWARD_STATE;

	legStates[LEFT] = FORWARD_STATE;
	legStates[RIGHT] = BACKWARD_STATE;
}

void RobotAnimationComponent::Update(double dt) {


	if (animate) {
		// if leg is moving forward, increase angle, else decrease angle
		for (char side = 0; side < 2; side++)
		{
			// arms
			if (armStates[side] == FORWARD_STATE)
				armAngles[side] += 0.0257100f * dt;
			else
				armAngles[side] -= 0.0257100f * dt;

			// change state if exceeding angles
			if (armAngles[side] >= 1.4f)
				armStates[side] = BACKWARD_STATE;
			else if (armAngles[side] <= -1.4f)
				armStates[side] = FORWARD_STATE;

			// legs
			if (legStates[side] == FORWARD_STATE)
				legAngles[side] += 0.0257100f * dt;
			else
				legAngles[side] -= 0.0257100f * dt;

			// change state if exceeding angles
			if (legAngles[side] >= 1.4f)
				legStates[side] = BACKWARD_STATE;
			else if (legAngles[side] <= -1.4f)
				legStates[side] = FORWARD_STATE;
		}

	}
	m_LeftLeg_->setRotation(glm::vec3(legAngles[LEFT], 0.0f, 0.0f));
	m_LeftArm_->setRotation(glm::vec3(armAngles[LEFT], 0.0f, 0.0f));
	m_RightArm_->setRotation(glm::vec3(armAngles[RIGHT], 0.0f, 0.0f));
	m_RightLeg_->setRotation(glm::vec3(legAngles[RIGHT], 0.0f, 0.0f));
}
void RobotAnimationComponent::LateUpdate(double dt) {

}

void RobotAnimationComponent::Destroy() {

}
void RobotAnimationComponent::Start() {

}