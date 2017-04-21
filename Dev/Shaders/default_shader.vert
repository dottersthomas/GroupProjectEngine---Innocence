#version 330 core

layout (location = 0) in vec3 vertex; 
layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec3 FragPos;


uniform mat4 mModel;
uniform mat4 mProjection;
uniform mat4 mView;

void main()
{
	gl_Position = mProjection * mView *  mModel * vec4(vertex, 1.0f);
    FragPos = vec3(mView * mModel * vec4(vertex, 1.0f));
    Normal = mat3(transpose(inverse(mModel))) * normal; 
}