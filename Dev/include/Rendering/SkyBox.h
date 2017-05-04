#ifndef _SKY_BOX_H_
#define _SKY_BOX_H_

#include "ResourceManager.h"
#include "Material.h"
#include "CubeMapTexture.h"

#include <vector>
#include <string>

class SkyBox {


private:

	std::string m_ShaderName_;
	Shader * m_Shader_;
	//Texture * m_CubeTexture_;

	Material m_Material_;

	GLuint skyboxVAO;

public:

	SkyBox() {}
	SkyBox(std::string pShader, std::vector<const GLchar* > paths);

	void Render(glm::mat4 pProj, glm::mat4 pView);

};


#endif // !_SKY_BOX_H_
