#ifndef _LIGHT_COMPONENT_H_
#define _LIGHT_COMPONENT_H_

#include "Component.h"

#include <glm\glm.hpp>

class LightComponent : public Component{

	enum LightType {
		SOURCE,
		DIRECTIONAL,
		SPOTLIGHT,
		POINT
	};

private:
	glm::vec3 m_Position_;
	glm::vec3 m_Lightcolour_;


	
public:

	LightComponent(GameObject * pParent, glm::vec3 pPosition = glm::vec3(0.0f, 0.0f, 0.0f));

	void setupLight(LightType pType, glm::vec3 pColour, float pIntensity);


	void Update(double dt);
	void LateUpdate(double dt);
	
	void Destroy();
	void Start();
};


#endif
