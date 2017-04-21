#ifndef _SHADER_H_
#define _SHADER_H_


#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderUniform.h"


// General purpsoe shader GameObject. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.
class Shader
{
public:
	// State
	GLuint ID;
	// Constructor
	Shader() { Uniforms.reserve(100); }
	// Sets the current shader as active
	Shader  &Use();
	// Compiles the shader from given source code
	void Compile(const GLchar *vertexSource, const GLchar *fragmentSource); 

	//Various Shader uniform assignment functions. Utility functions.
	void SetFloat(const GLchar *name, GLfloat value);

	void SetInteger(const GLchar *name, GLint value);

	void SetVector2f(const GLchar *name, GLfloat x, GLfloat y);

	void SetVector2f(const GLchar *name, const glm::vec2 &value);

	void SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z);

	void SetVector3f(const GLchar *name, const glm::vec3 &value);

	void SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	void SetVector4f(const GLchar *name, const glm::vec4 &value);

	void SetMatrix3(const GLchar *name, const glm::mat3 &matrix);

	void SetMatrix4(const GLchar *name, const glm::mat4 &matrix);

	void SetUniform(ShaderUniform& pUniform) {
		Uniforms.push_back(pUniform);
	}
	
	void UpdateShaderUniforms();

private:
	// Checks if compilation or linking failed and if so, print the error logs
	void checkCompileErrors(GLuint GameObject, std::string type);
	std::vector<ShaderUniform> Uniforms;
};


#endif