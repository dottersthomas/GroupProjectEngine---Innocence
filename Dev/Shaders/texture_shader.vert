#version 330

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec2 fragTexCoord;
layout (location=2) in vec3 Normals;


out vec2 texCoord;

out vec3 vertPos; //Vertex position in eye coords
out vec3 N; //Transformed normal
out vec3 lightPos; //Light position in eye coords


uniform vec3 LightPosition; // Light position 
uniform mat3 NormalMatrix;
uniform mat4 mModel;
uniform mat4 mProjection;
uniform mat4 mView;

void main()
{
	texCoord = fragTexCoord;

	vertPos = vec3(mView * mModel * vec4(VertexPosition,1.0)); 
     
    lightPos = vec3(mView * mModel * vec4(LightPosition,1.0));  

    N = normalize( NormalMatrix * Normals);

    gl_Position = mProjection * mView * mModel  *  vec4(VertexPosition,1.0);
}
