#ifndef _FIRST_PERSON_CAMERA_COMPONENT_H_
#define _FIRST_PERSON_CAMERA_COMPONENT_H_

#include "CameraComponent.h"
#include "Rendering\ShaderUniform.h"


class FirstPersonCameraComponent : public CameraComponent {
private:
	glm::vec3 m_Position_;


	bool m_bLimitVert_ = false;

	double m_dMousePosX_, m_dMousePosY_;
	int m_iWindowX_, m_iWindowY_;

	bool m_bLockToCenter_;

	// horizontal angle : toward -Z
	// vertical angle : 0, look at the horizon
	float m_fVerticalAngle_;
	// Initial Field of View
	float m_fInitialFoV_ = 45.0f;

	float m_fSpeed_ = 0.03f; // 3 units / second
	float m_fMouseSpeed_ = 0.05f;

	//Up Vector.
	glm::vec3 m_Up_;

	ShaderUniform camera;

	//View Matrix created by the bind function.
	glm::mat4 m_View_;
public:

	//First Person camera component.
	FirstPersonCameraComponent(GameObject * pParent, std::string pName, glm::vec3 pPosition = glm::vec3(0.0f, 0.0f, 0.0f));

	void Update(double dt);
	void LateUpdate(double dt);

	void Destroy();
	void Start();

	//The horizontal angle for the camera.
	float m_fHorizontalAngle_;

	void setPosition(glm::vec3 pPos) {
		m_Position_ = pPos;
	}

	glm::vec3 getPosition() {
		return m_Position_;
	}

	virtual glm::mat4 Bind();

	float GetSpeed() {
		return m_fSpeed_;
	}

	// Register class with lua
	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.deriveClass<FirstPersonCameraComponent, CameraComponent>("FirstPersonCameraComponent")
			.addData<glm::vec3>("position", &FirstPersonCameraComponent::m_Position_)
			.endClass();
	}
};

#endif
