#include "Rendering\Texture.h"

//Create a Texture and set some default values.
Texture::Texture(GLuint width, GLuint height, unsigned char* data) : Width(0), Height(0), Internal_Format(GL_RGBA), Image_Format(GL_BGRA), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_NEAREST) {
	glGenTextures(1, &this->ID);

	this->Width = width;
	this->Height = height;
	// Create Texture
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	// Set Texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const {
	glBindTexture(GL_TEXTURE_2D, this->ID);
}