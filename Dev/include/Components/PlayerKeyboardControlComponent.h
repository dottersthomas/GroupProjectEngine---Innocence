#ifndef _PLAYER_KEYBOARD_CONTROL_COMPONENT_H_
#define _PLAYER_KEYBOARD_CONTROL_COMPONENT_H_

#include "TransformComponent.h"
#include "InputComponent.h"
#include "GameObject.h"

//Input handling component for the player. This is unique to the player object and does not exist anywhere else.
class PlayerKeyboardControlComponent : public InputComponent {
private:
	bool m_Enabled_ = true;
	TransformComponent * m_ParentTransform_;

public:
	PlayerKeyboardControlComponent(GameObject * pParent);

	virtual void Update(double dt);
	virtual void LateUpdate(double dt);

	virtual void Destroy();
	virtual void Start();


	//Check if the component is enabled to read inputs.
	bool isEnabled() {
		return m_Enabled_;
	}

	//Toggle if the component is enabled or not.
	void toggleEnabled(bool pToggle) {
		m_Enabled_ = pToggle;
	}
};


#endif