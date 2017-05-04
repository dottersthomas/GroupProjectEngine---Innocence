#ifndef _CUBE_MAP_TEXTURE_H_
#define _CUBE_MAP_TEXTURE_H_

#include "Texture.h"
#include <glm\glm.hpp>

#include <vector>

class CubeMapTexture {

public:

	// Holds the ID of the texture GameObject, used for all texture operations to reference to this particlar texture
	GLuint ID;
	// Texture image dimensions
	GLuint Width, Height; // Width and height of loaded image in pixels
						  // Texture Format
	GLuint Internal_Format; // Format of texture GameObject
	GLuint Image_Format; // Format of loaded image
						 // Texture configuration
	GLuint Wrap_S; // Wrapping mode on S axis
	GLuint Wrap_T; // Wrapping mode on T axis
	GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
	GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels

	std::string type;

	CubeMapTexture() {}
	CubeMapTexture(std::vector<glm::vec2> size, std::vector<unsigned char*> data);

	void Bind() const;

};


#endif // !_CUBE_MAP_TEXTURE_H_
