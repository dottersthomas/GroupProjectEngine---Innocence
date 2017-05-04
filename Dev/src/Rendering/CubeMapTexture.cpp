#include "Rendering\CubeMapTexture.h"


CubeMapTexture::CubeMapTexture(std::vector<glm::vec2> size, std::vector<unsigned char*> data)  {
	
	Internal_Format = GL_RGBA;
	Image_Format= GL_BGRA;
	Wrap_S = GL_REPEAT;
	Wrap_T = GL_REPEAT;
	Filter_Min = GL_LINEAR;
	Filter_Max = GL_NEAREST;

	glGenTextures(1, &this->ID);


	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

	for (int i = 0; i < data.size(); i++) {
		Width = size[i].x;
		Height = size[i].y;

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, size[i].x, size[i].y, 0, GL_RGB, GL_UNSIGNED_BYTE, data[i]);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

}

void CubeMapTexture::Bind() const {

	glBindTexture(GL_TEXTURE_CUBE_MAP, this->ID);

}