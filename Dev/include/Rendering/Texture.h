#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <GL/glew.h>


class Texture {
private:

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
	
	Texture() {}
	Texture(GLuint width, GLuint height, unsigned char* data);

	void Bind() const;

};

#endif