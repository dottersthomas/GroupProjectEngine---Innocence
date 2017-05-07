#include "Rendering\Shader.h"
#include <iostream>

Shader &Shader::Use()
{
	glUseProgram(this->ID);
	return *this;
}

void Shader::Compile(const GLchar* vertexSource, const GLchar* fragmentSource)
{
	GLuint sVertex, sFragment;
	// Vertex Shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");
	// Fragment Shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");
	// Shader Program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, sVertex);
	glAttachShader(this->ID, sFragment);

	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, "PROGRAM");
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);

}

void Shader::SetFloat(const GLchar *name, GLfloat value)
{
	glUniform1f(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetInteger(const GLchar *name, GLint value)
{
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y)
{
	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
void Shader::SetVector2f(const GLchar *name, const glm::vec2 &value)
{
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
void Shader::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
void Shader::SetVector3f(const GLchar *name, const glm::vec3 &value)
{
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}
void Shader::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
void Shader::SetVector4f(const GLchar *name, const glm::vec4 &value)
{
	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix3(const GLchar *name, const glm::mat3 &matrix)
{
	glUniformMatrix3fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::UpdateShaderUniforms() {

	for (UniformIterator = Uniforms.begin(); UniformIterator != Uniforms.end(); UniformIterator++) {
		switch (UniformIterator->second.M_Type)
		{
		case ShaderType::UNIFORM_INT:
			//SetInteger(UniformIterator->second.M_Address.c_str(), UniformIterator->second.M_Int);
			glUniform1i(glGetUniformLocation(this->ID, UniformIterator->second.M_Address.c_str()), UniformIterator->second.M_Int);
			break;
		case ShaderType::UNIFORM_FLOAT:
			//SetFloat(UniformIterator->second.M_Address.c_str(), UniformIterator->second.M_Float);
			glUniform1f(glGetUniformLocation(this->ID, UniformIterator->second.M_Address.c_str()), UniformIterator->second.M_Float);
			break;
		case ShaderType::VEC2:
			SetVector2f(UniformIterator->second.M_Address.c_str(), UniformIterator->second.M_Vec2);
			break;
		case ShaderType::VEC3:
			//SetVector3f(UniformIterator->second.M_Address.c_str(), UniformIterator->second.M_Vec3);
			glUniform3f(glGetUniformLocation(this->ID, UniformIterator->second.M_Address.c_str()), UniformIterator->second.M_Vec3.x, UniformIterator->second.M_Vec3.y, UniformIterator->second.M_Vec3.z);
			break;
		case ShaderType::VEC4:
			SetVector4f(UniformIterator->second.M_Address.c_str(), UniformIterator->second.M_Vec4);
			break;
		case ShaderType::MAT3:
			SetMatrix3(UniformIterator->second.M_Address.c_str(), UniformIterator->second.M_Mat3);
			break;
		case ShaderType::MAT4:
			break;
			SetMatrix4(UniformIterator->second.M_Address.c_str(), UniformIterator->second.M_Mat4);
		default:
			break;
		}
	}
}

void Shader::UpdatePackagedUniforms(std::vector<ShaderUniform>& uniforms) {
	std::vector<ShaderUniform>::iterator uniTerator;

	for (uniTerator = uniforms.begin(); uniTerator != uniforms.end(); uniTerator++) {
		switch (uniTerator->M_Type)
		{
		case ShaderType::UNIFORM_INT:
			//SetInteger(uniTerator->M_Address.c_str(), uniTerator->M_Int);
			glUniform1i(glGetUniformLocation(this->ID, uniTerator->M_Address.c_str()), uniTerator->M_Int);

			break;
		case ShaderType::UNIFORM_FLOAT:
			//SetFloat(uniTerator->M_Address.c_str(), uniTerator->M_Float);
			glUniform1f(glGetUniformLocation(this->ID, uniTerator->M_Address.c_str()), uniTerator->M_Float);

			break;
		case ShaderType::VEC2:
			SetVector2f(uniTerator->M_Address.c_str(), uniTerator->M_Vec2);
			break;
		case ShaderType::VEC3:
			//SetVector3f(uniTerator->M_Address.c_str(), uniTerator->M_Vec3);
			glUniform3f(glGetUniformLocation(this->ID, uniTerator->M_Address.c_str()), uniTerator->M_Vec3.x, uniTerator->M_Vec3.y, uniTerator->M_Vec3.z);

			break;
		case ShaderType::VEC4:
			SetVector4f(uniTerator->M_Address.c_str(), uniTerator->M_Vec4);
			break;
		case ShaderType::MAT3:
			SetMatrix3(uniTerator->M_Address.c_str(), uniTerator->M_Mat3);
			break;
		case ShaderType::MAT4:
			break;
			SetMatrix4(uniTerator->M_Address.c_str(), uniTerator->M_Mat4);
		default:
			break;
		}
	}

}

void Shader::UpdateSingleUniform(ShaderUniform& uniform) {
	switch (uniform.M_Type)
	{
	case ShaderType::UNIFORM_INT:
		SetInteger(uniform.M_Address.c_str(), uniform.M_Int);
		break;
	case ShaderType::UNIFORM_FLOAT:
		SetFloat(uniform.M_Address.c_str(), uniform.M_Float);
		break;
	case ShaderType::VEC2:
		SetVector2f(uniform.M_Address.c_str(), uniform.M_Vec2);
		break;
	case ShaderType::VEC3:
		SetVector3f(uniform.M_Address.c_str(), uniform.M_Vec3);
		break;
	case ShaderType::VEC4:
		SetVector4f(uniform.M_Address.c_str(), uniform.M_Vec4);
		break;
	case ShaderType::MAT3:
		SetMatrix3(uniform.M_Address.c_str(), uniform.M_Mat3);
		break;
	case ShaderType::MAT4:
		break;
		SetMatrix4(uniform.M_Address.c_str(), uniform.M_Mat4);
	default:
		break;
	}
}

void Shader::checkCompileErrors(GLuint GameObject, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(GameObject, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(GameObject, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else
	{
		glGetProgramiv(GameObject, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(GameObject, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}