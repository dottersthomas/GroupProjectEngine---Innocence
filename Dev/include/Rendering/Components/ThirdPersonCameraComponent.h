#ifndef _THIRD_PERSON_CAMERA_COMPONENT_H_
#define _THIRD_PERSON_CAMERA_COMPONENT_H_

#include "CameraComponent.h"
#include "General\Proxy.h"

class ThirdPersonCameraComponent : public CameraComponent {
private:

	glm::vec3 m_Position_; //Current Position relative to the Parents transform.
	glm::vec3 m_TargetPosRelative_; //View Target relative to the Parents transform.
	glm::vec3 m_AbsolutePosition_; //Current Camera's Position in relative to the world origin (0,0,0).

	float m_CameraDistance_;


	bool m_bLimitVert_ = false;

	double m_dMousePosX_, m_dMousePosY_;
	int m_iWindowX_, m_iWindowY_;

	bool m_bLockToCenter_;

	// horizontal angle : toward -Z
	// vertical angle : 0, look at the horizon
	float m_fVerticalAngle_;
	// Initial Field of View
	float m_fInitialFoV_ = 45.0f;

	float m_fSpeed_ = 10.0f; // 3 units / second
	float m_fMouseSpeed_ = 0.005;

	glm::vec3 m_Up_;

	glm::mat4 m_View_;

public:

	//Third Person camera component.
	ThirdPersonCameraComponent() {}
	ThirdPersonCameraComponent(GameObject * pParent, std::string pName, float pDistance = 10.0f, glm::vec3 pTargetRelative = glm::vec3(0.0f, 0.0f, 0.0f));

	float m_fHorizontalAngle_;

	void Update(double dt);
	void LateUpdate(double dt);

	void Destroy();
	void Start();

	glm::mat4 Bind();

	// Register class with lua
	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.deriveClass<ThirdPersonCameraComponent, CameraComponent>("ThirdPersonCameraComponent")
			.addData<glm::vec3>("position", &ThirdPersonCameraComponent::m_Position_)
			.endClass();
	}
};

#endif
