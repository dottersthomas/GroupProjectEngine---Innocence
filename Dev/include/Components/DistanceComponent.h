#ifndef _DISTANCE_COMPONENT_H_
#define _DISTANCE_COMPONENT_H_

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include "Component.h"
#include "Rendering\Mesh.h"
#include "Components\TransformComponent.h"

//Checks the distance between this object and the players object.
class DistanceComponent : public Component {

private:

	TransformComponent * m_Player_;
	float m_Distance_;
	bool hasBeenToggled = false;

public:

	DistanceComponent(GameObject * pParent, TransformComponent * pTransform, float pDistance) {
		m_GameObjectParent_ = pParent;
		m_Player_ = pTransform;
		m_Distance_ = pDistance;
	}

	void Update(double dt);
	void LateUpdate(double dt);

	void Destroy();
	void Start();

};

#endif