#ifndef _RENDERING_POINT_LIGHT_H_
#define _RENDERING_POINT_LIGHT_H_

#include "Rendering\Components\Lights\Light.h"

class PointLight : public Light {

public:
	PointLight(){ }

	PointLight(std::string pShader);
	PointLight(std::string pShader, glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float constant, float linear, float quadratic);
	//Called every tick.
	virtual void Update(double dt);

	//Called at the end of every tick, mainly for maintenance uses.
	virtual void LateUpdate(double dt);

	//Called when the component is destroyed.
	virtual void Destroy();

	//Called when the component starts.
	virtual void Start();

	virtual void UpdateLightUniforms(int pos);

	void setPosition(glm::vec3 pPos) {

		setDirty(true);

		m_Position_ = pPos;
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
			.deriveClass<PointLight, Light>("PointLight")
				.addConstructor<void(*)(std::string)>()
				.addData<glm::vec3>("position", &PointLight::m_Position_)
				.addData<float>("constant", &PointLight::m_Constant_)
				.addData<float>("linear", &PointLight::m_Linear_)
				.addData<float>("quadratic", &PointLight::m_Quadratic_)
			.endClass();
	}

private:
	float m_Constant_;
	float m_Linear_;
	float m_Quadratic_;

	glm::vec3 m_Position_;

};



#endif // !_RENDERING_POINT_LIGHT_H_
