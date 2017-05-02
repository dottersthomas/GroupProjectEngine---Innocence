#version 330

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 Normals;
layout (location=2) in vec2 fragTexCoord;
layout (location=3) in vec3 Tangent;
layout (location=4) in vec3 Bitangent;


out VS_OUT {
	flat int hasNMap;
	vec3 Normal;
    vec3 FragPos;
    vec2 TexCoords;
	mat3 TBN;
} vs_out;

uniform mat4 mModel;
uniform mat4 mProjection;
uniform mat4 mView;

uniform int hasNormalMap;

void main()
{
	vs_out.TexCoords = fragTexCoord;

	vs_out.FragPos = vec3(mModel * vec4(VertexPosition, 1.0f));

    vs_out.Normal = mat3(transpose(inverse(mModel))) * Normals;  

	vs_out.hasNMap = hasNormalMap;

	if(hasNormalMap == 1){
		mat3 normalMatrix = transpose(inverse(mat3(mModel)));
		vec3 T = normalize(normalMatrix * Tangent);
		vec3 B = normalize(normalMatrix * Bitangent);
		vec3 N = normalize(normalMatrix * Normals);    
		
		vs_out.TBN = transpose(mat3(T, B, N));  

	}
    gl_Position = mProjection * mView * mModel  *  vec4(VertexPosition,1.0);
}


//#version 330
//
//layout (location=0) in vec3 VertexPosition;
//layout (location=1) in vec3 Normals;
//
//layout (location=2) in vec2 fragTexCoord;
//
//
//out vec3 Normal;
//out vec3 FragPos;
//out vec2 texCoord;
//
//
//uniform mat4 mModel;
//uniform mat4 mProjection;
//uniform mat4 mView;
//
//void main()
//{
//	texCoord = fragTexCoord;
//
//	FragPos = vec3(mModel * vec4(VertexPosition, 1.0f));
//
//    Normal = mat3(transpose(inverse(mModel))) * Normals;  
//
//    gl_Position = mProjection * mView * mModel  *  vec4(VertexPosition,1.0);
//}