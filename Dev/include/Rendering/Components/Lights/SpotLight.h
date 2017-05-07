#ifndef _RENDERING_SPOT_LIGHT_H_
#define _RENDERING_SPOT_LIGHT_H_

#include "Rendering\Components\Lights\Light.h"

class SpotLight : public Light {

private:

	glm::vec3 m_Position_;
	glm::vec3 m_Direction_;
	float m_CutOff_;
	float m_SoftCutoff_;

	float m_Constant_;
	float m_Linear_;
	float m_Quadratic_;

public:
	SpotLight() {}
	SpotLight(std::string pShader);
	SpotLight(std::string pShader, glm::vec3 pos, glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float cutoff);

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

	void setPosition(glm::vec3 pPos) {
		setDirty(true);

		m_Position_ = pPos;
	}

	void setCutOff(float pCut) {
		setDirty(true);

		m_CutOff_ = glm::cos(glm::radians(pCut));
		m_SoftCutoff_ = glm::cos(glm::radians(pCut + 5.0f));

	}


	void setConstant(float pConstant) {

		setDirty(true);

		m_Constant_ = pConstant;
	}

	void setLinear(float pLinear) {
		setDirty(true);

		m_Linear_ = pLinear;
	}

	void setQuadratic(float pQuadratic) {
		setDirty(true);

		m_Quadratic_ = pQuadratic;
	}


	static void registerLua(lua_State* L)
	{
		using namespace luabridge;

		getGlobalNamespace(L)
			.deriveClass<SpotLight, Light>("SpotLight")
			.addConstructor<void(*)(std::string)>()
			.addData<glm::vec3>("direction", &SpotLight::m_Direction_)
			.addData<glm::vec3>("position", &SpotLight::m_Position_)
			.addData<float>("cutoff", &SpotLight::m_CutOff_)
			.addData<float>("constant", &SpotLight::m_Constant_)
			.addData<float>("linear", &SpotLight::m_Linear_)
			.addData<float>("quadratic", &SpotLight::m_Quadratic_)
			.endClass();
	}
};



#endif