#ifndef _RENDERING_LIGHT_MANAGER_
#define _RENDERING_LIGHT_MANAGER_


#include "Rendering\Components\Lights\Light.h"
#include "Rendering\Components\Lights\DirectionalLight.h"
#include "Rendering\Components\Lights\PointLight.h"
#include "Rendering\Components\Lights\SpotLight.h"


struct DirectionalLightWrapper {

	typedef std::vector<DirectionalLight*> t_Light_Vector_;

	typedef t_Light_Vector_::iterator t_Light_Iter;
	typedef t_Light_Vector_::const_iterator t_Light_Const_Iter;
};

struct PointLightWrapper {

	typedef std::vector<PointLight*> t_Light_Vector_;

	typedef t_Light_Vector_::iterator t_Light_Iter;
	typedef t_Light_Vector_::const_iterator t_Light_Const_Iter;
};

struct SpotLightWrapper {

	typedef std::vector<SpotLight*> t_Light_Vector_;

	typedef t_Light_Vector_::iterator t_Light_Iter;
	typedef t_Light_Vector_::const_iterator t_Light_Const_Iter;
};



class LightManager {

private:
	DirectionalLightWrapper::t_Light_Vector_ m_DirectionalLights_;
	PointLightWrapper::t_Light_Vector_ m_PointLights_;
	SpotLightWrapper::t_Light_Vector_ m_SpotLights_;


public:

	LightManager() {}

	void RegisterDirectionalLight(DirectionalLight * pDir);
	void RegisterPointLight(PointLight * pPoint);
	void RegisterSpotLight(SpotLight * pSpot);



	void update(float dt);
};



#endif