//#version 330 core

struct Material {

	int hasTexture;

	vec3 colour_diffuse;
	vec3 colour_specular;

    sampler2D texture_diffuse1;
	sampler2D texture_specular1;  
    float shininess;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


in vec3 FragPos;  
in vec3 Normal;  
in vec2 texCoord;

out vec4 FragColour;
  
uniform vec3 viewPos;
uniform Material material;
uniform DirLight directionalLights[DIRECTIONAL_LIGHTS];
uniform PointLight pointLights[POINT_LIGHTS];

uniform highp mat4 mView;



// Function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
   // Properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // == ======================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == ======================================	
    // Phase 1: Directional lighting
    vec3 result = CalcDirLight(directionalLights[0], norm, viewDir);
    // Phase 2: Point lights
    for(int i = 0; i < POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    // Phase 3: Spot light
    // result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
    vec3 diff = vec3(texture(material.texture_diffuse1, texCoord));
  //  FragColour = vec4(diff, 1.0);
    FragColour = vec4(result, 1.0);

} 

// Calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Combine results
	if(material.hasTexture == 1){
		vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, texCoord));
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, texCoord));
		vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, texCoord));
		return (ambient + diffuse + specular);
	}else{
		vec3 ambient = light.ambient * material.colour_diffuse;
		vec3 diffuse = light.diffuse * diff * material.colour_diffuse;
		vec3 specular = light.specular * spec * material.colour_specular;
		return (ambient + diffuse + specular);
	
	}
}

// Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f ;    
    // Combine results
	if(material.hasTexture == 1){
		vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, texCoord));
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, texCoord));
		vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, texCoord));
		return (ambient + diffuse + specular);

	}else{
		vec3 ambient = light.ambient * material.colour_diffuse;
		vec3 diffuse = light.diffuse * diff * material.colour_diffuse;
		vec3 specular = light.specular * spec * material.colour_specular;
		return (ambient + diffuse + specular);

	}
}