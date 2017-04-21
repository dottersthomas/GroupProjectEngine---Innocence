#ifndef _RENDERING_DIRECTIONAL_LIGHT_H_
#define _RENDERING_DIRECTIONAL_LIGHT_H_

#include "Light.h"

class DirectionalLight : public Light{

private:

	glm::vec3 m_Direction_;

public:
	DirectionalLight() {}
	DirectionalLight(std::string pShader);
	DirectionalLight(std::string pShader, glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec);

	//Called every tick.
	virtual void Update(double dt);

	//Called at the end of every tick, mainly for maintenance uses.
	virtual void LateUpdate(double dt);

	//Called when the component is destroyed.
	virtual void Destroy();

	//Called when the component starts.
	virtual void Start();
};



#endif