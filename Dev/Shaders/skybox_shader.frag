
in vec3 TexCoords;
out vec4 color;

struct Material {
	 samplerCube texture_skybox;
};

uniform Material material;

void main()
{    
    color = texture(material.texture_skybox, TexCoords);
}