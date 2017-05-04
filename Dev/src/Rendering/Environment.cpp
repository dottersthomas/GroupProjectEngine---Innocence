#include "Rendering\Environment.h"


void Environment::Render(glm::mat4 pProj, glm::mat4 pView) {

	if(hasSkybox)
		m_SkyBox_->Render(pProj, pView);



}