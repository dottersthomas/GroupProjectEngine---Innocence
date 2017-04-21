#version 330

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 Normals;

layout (location=2) in vec2 fragTexCoord;


out vec3 Normal;
out vec3 FragPos;
out vec2 texCoord;


uniform mat4 mModel;
uniform mat4 mProjection;
uniform mat4 mView;

void main()
{
	texCoord = fragTexCoord;

	FragPos = vec3(mModel * vec4(VertexPosition, 1.0f));

    Normal = mat3(transpose(inverse(mModel))) * Normals;  

    gl_Position = mProjection * mView * mModel  *  vec4(VertexPosition,1.0);
}
