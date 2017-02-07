#version 330 core

layout (location = 0) in vec3 vertex; 

out vec2 TexCoords;


uniform mat4 mModel;
uniform mat4 mProjection;
uniform mat4 mView;

void main()
{
	TexCoords = vec2(1.0 - vertex.x, vertex.y);
    gl_Position = mProjection * mView * mModel  * vec4(vertex.xyz, 1.0);
}