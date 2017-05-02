#ifndef _RENDERING_DIRECTIONAL_LIGHT_H_
#define _RENDERING_DIRECTIONAL_LIGHT_H_

#include "Rendering\Components\Lights\Light.h"

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

	virtual void UpdateLightUniforms(int pos);

	void setDirection(glm::vec3 pDir) {
		setDirty(true);

		m_Direction_ = pDir;
	}

	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.deriveClass<DirectionalLight, Light>("DirectionalLight")
				.addConstructor<void(*)(std::string)>()
				.addData<glm::vec3>("direction", &DirectionalLight::m_Direction_)
			.endClass();
	}
};



#endif