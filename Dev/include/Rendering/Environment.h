#ifndef _RENDERING_ENVIRONMENT_H_
#define _RENDERING_ENVIRONMENT_H_

#include "Rendering\SkyBox.h"

class Environment {

private:

	SkyBox * m_SkyBox_;
	bool hasSkybox = false;

public:
	Environment(){}

	void setSkyBox(SkyBox * pSkyBox) {
		m_SkyBox_ = pSkyBox;
		hasSkybox = true;
	}

	SkyBox * getSkyBox() {
		return m_SkyBox_;
	}


	void Render(glm::mat4 pProj, glm::mat4 pView);


};


#endif // !_RENDERING_ENVIRONMENT_H_
