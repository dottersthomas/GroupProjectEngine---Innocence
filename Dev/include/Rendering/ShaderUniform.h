#ifndef _SHADER_UNIFORM_H_
#define _SHADER_UNIFORM_H_

#include <iostream>
#include "glm\glm.hpp"

enum ShaderType {
	UNIFORM_INT,
	UNIFORM_FLOAT,
	VEC2,
	VEC3,
	VEC4,
	MAT3,
	MAT4
};

struct ShaderUniform {


	std::string M_Address;
	ShaderType M_Type;
	union 
	{
		int M_Int;
		float M_Float;
		glm::vec2 M_Vec2;
		glm::vec3 M_Vec3;
		glm::vec4 M_Vec4;
		glm::mat3 M_Mat3;
		glm::mat4 M_Mat4;
	};


	ShaderUniform() {}
	//ShaderUniform(ShaderUniform &) {}

	ShaderUniform(const ShaderUniform&) = default;

};



#endif