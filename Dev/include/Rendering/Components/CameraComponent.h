#ifndef _CAMERA_COMPONENT_H_
#define _CAMERA_COMPONENT_H_

#include "Component.h"
#include <glm\glm.hpp>

class CameraComponent : public Component {

protected:

	bool m_Active_ = false; //Default False Value
public:

	//Abstract Camera Component to be inherited for the other camera types.
	CameraComponent() {}
	CameraComponent(GameObject * pParent) {
		m_GameObjectParent_ = pParent;
	}


	void SetActive(bool pActive) {
		m_Active_ = pActive;
	}

	virtual void Update(double dt) = 0;
	virtual void LateUpdate(double dt) = 0;

	virtual void Destroy() = 0;
	virtual void Start() = 0;


	//Used to bind the camera to be the current active camera. This is used by the renderer only.
	virtual glm::mat4 Bind() = 0;


};

#endif
