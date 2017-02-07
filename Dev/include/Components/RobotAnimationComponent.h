#ifndef _ROBOT_ANIMATION_COMPONENT_H_
#define _ROBOT_ANIMATION_COMPONENT_H_

#include "Components.h"

class RobotAnimationComponent : public Component {
private:


	// constants for arm and leg movement states
	const char BACKWARD_STATE = 0;
	const char FORWARD_STATE = 1;

	// index constants for accessing arm and leg array data
	const char LEFT = 0;
	const char RIGHT = 1;

	Mesh * m_LeftLeg_;
	Mesh * m_LeftArm_;
	Mesh * m_RightLeg_;
	Mesh * m_RightArm_;


	char legStates[2];
	char armStates[2];


	float legAngles[2];
	float armAngles[2];

	bool animate;


public:
	RobotAnimationComponent(GameObject * pParent);

	void attachLeftLeg(Mesh * pMesh) {
		m_LeftLeg_ = pMesh;
	}

	void attachRightLeg(Mesh * pMesh) {
		m_RightLeg_ = pMesh;
	}

	void attachLeftArm(Mesh * pMesh) {
		m_LeftArm_ = pMesh;
	}

	void attachRightArm(Mesh * pMesh) {
		m_RightArm_ = pMesh;
	}



	void Update(double dt);
	void LateUpdate(double dt);

	void Destroy();
	void Start();
};



#endif // !_ROBOT_ANIMATION_COMPONENT_H_
