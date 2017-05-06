
struct Material {

	int hasTexture;

	vec3 colour_diffuse;
	vec3 colour_specular;

    sampler2D texture_diffuse1;
	sampler2D texture_specular1;  

	sampler2D texture_normal1;
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


struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutoff;
    float softcutoff;

	float constant;
    float linear;
    float quadratic;
 
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};


in VS_OUT {
	flat int hasNMap;
	vec3 Normal;
    vec3 FragPos;
    vec2 TexCoords;
	mat3 TBN;
} fs_in;


out vec4 FragColour;
  
uniform vec3 viewPos;
uniform Material material;
uniform DirLight directionalLights[DIRECTIONAL_LIGHTS];
uniform PointLight pointLights[POINT_LIGHTS];
uniform SpotLight spotLights[SPOT_LIGHTS];


uniform highp mat4 mView;



// Function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 norm;
	vec3 viewDir;

   if(fs_in.hasNMap == 1){
		vec3 normal = texture(material.texture_normal1, fs_in.TexCoords).rgb;
   
		norm = normalize(normal * 2.0 - 1.0);

		vec3 tangentViewPos = fs_in.TBN * viewPos;
		vec3 tangentFragPos = fs_in.TBN * fs_in.FragPos; 

		viewDir = normalize(tangentViewPos - tangentFragPos);
   }else{
		norm = normalize(fs_in.Normal);
		viewDir = normalize(viewPos - fs_in.FragPos);
   }


   
    vec3 result;


    for(int i = 0; i < DIRECTIONAL_LIGHTS; i++)
		result = CalcDirLight(directionalLights[i], norm, viewDir);

    for(int i = 0; i < POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, fs_in.FragPos, viewDir); 
	
   // for(int i = 0; i < SPOT_LIGHTS; i++)	   
     //  result += CalcSpotLight(spotLights[i], norm, fs_in.FragPos, viewDir);  
	   
	     
    vec3 diff = vec3(texture(material.texture_diffuse1, fs_in.TexCoords));
	
	FragColour = vec4(result, 1.0);

} 

// Calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	float diff;
	float spec;

	if(fs_in.hasNMap == 1){
		vec3 tangentFragPos = fs_in.TBN * fs_in.FragPos;

		diff = max(dot(normal, lightDir), 0.0);

		vec3 reflectDir = reflect(-lightDir, normal);

		vec3 halfwayDir = normalize(lightDir + viewDir);  

		spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
	}else{
	
		diff = max(dot(normal, lightDir), 0.0);
		    // Specular shading
		vec3 reflectDir = reflect(-lightDir, normal);

		spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	}

	if(material.hasTexture == 1){
		vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, fs_in.TexCoords));
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, fs_in.TexCoords));
		vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, fs_in.TexCoords));
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

	vec3 lightDir;
	float diff;
	float spec;
	float distance;

	if(fs_in.hasNMap == 1){
		vec3 tangentFragPos = fs_in.TBN * fs_in.FragPos;
		vec3 tangentLightPos = fs_in.TBN * light.position;

		lightDir = normalize(tangentLightPos - tangentFragPos);

		diff = max(dot(lightDir, normal), 0.0);

		vec3 reflectDir = reflect(-lightDir, normal);

		vec3 halfwayDir = normalize(lightDir + viewDir);  

		spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

		 distance = length(light.position - tangentFragPos);
		 
	}else{
		lightDir = normalize(light.position - fragPos);
		// Diffuse shading
		diff = max(dot(normal, lightDir), 0.0);
		// Specular shading
		vec3 reflectDir = reflect(-lightDir, normal);

		spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

		 distance = length(light.position - fragPos);
		
	}
	
	 float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

	if(material.hasTexture == 1){
		vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, fs_in.TexCoords));
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, fs_in.TexCoords));
		vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, fs_in.TexCoords));

		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;
		return (ambient + diffuse + specular);

	}else{
		vec3 ambient = light.ambient * material.colour_diffuse;
		vec3 diffuse = light.diffuse * diff * material.colour_diffuse;
		vec3 specular = light.specular * spec * material.colour_specular;

		
		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;
		return (ambient + diffuse + specular);

	}
}


// Calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir;
	float diff;
	float spec;
	float distance;

	if(fs_in.hasNMap == 1){
		vec3 tangentFragPos = fs_in.TBN * fs_in.FragPos;
		vec3 tangentLightPos = fs_in.TBN * light.position;

		lightDir = normalize(tangentLightPos - tangentFragPos);

		diff = max(dot(lightDir, normal), 0.0);

		vec3 reflectDir = reflect(-lightDir, normal);

		vec3 halfwayDir = normalize(lightDir + viewDir);  

		spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

		 distance = length(light.position - tangentFragPos);
		 
	}else{
		lightDir = normalize(light.position - fragPos);
		diff = max(dot(normal, lightDir), 0.0);
		vec3 reflectDir = reflect(-lightDir, normal);

		spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

		distance = length(light.position - fragPos);
		
	}


   
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // Spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutoff - light.softcutoff;
    float intensity = clamp((theta - light.softcutoff) / epsilon, 0.0, 1.0);
   
	if(material.hasTexture == 1){
		vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, fs_in.TexCoords));
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, fs_in.TexCoords));
		vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, fs_in.TexCoords));

		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;
		return (ambient + diffuse + specular);

	}else{
		vec3 ambient = light.ambient * material.colour_diffuse;
		vec3 diffuse = light.diffuse * diff * material.colour_diffuse;
		vec3 specular = light.specular * spec * material.colour_specular;

		
		ambient *= attenuation * intensity;
		diffuse *= attenuation * intensity;
		specular *= attenuation * intensity;
		return (ambient + diffuse + specular);

	}
}



//struct Material {
//
//	int hasTexture;
//
//	vec3 colour_diffuse;
//	vec3 colour_specular;
//
//    sampler2D texture_diffuse1;
//	sampler2D texture_specular1;  
//    float shininess;
//}; 
//
//struct DirLight {
//    vec3 direction;
//	
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//};
//
//struct PointLight {
//    vec3 position;
//    
//    float constant;
//    float linear;
//    float quadratic;
//	
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//};
//
//
//in vec3 FragPos;  
//in vec3 Normal;  
//in vec2 texCoord;
//
//out vec4 FragColour;
//  
//uniform vec3 viewPos;
//uniform Material material;
//uniform DirLight directionalLights[DIRECTIONAL_LIGHTS];
//uniform PointLight pointLights[POINT_LIGHTS];
//
//uniform highp mat4 mView;
//
//
//
//// Function prototypes
//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
//
//void main()
//{
//   // Properties
//    vec3 norm = normalize(Normal);
//    vec3 viewDir = normalize(viewPos - FragPos);
//    
//    // == ======================================
//    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
//    // For each phase, a calculate function is defined that calculates the corresponding color
//    // per lamp. In the main() function we take all the calculated colors and sum them up for
//    // this fragment's final color.
//    // == ======================================	
//    // Phase 1: Directional lighting
//    vec3 result = CalcDirLight(directionalLights[0], norm, viewDir);
//    // Phase 2: Point lights
//    for(int i = 0; i < POINT_LIGHTS; i++)
//        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
//    // Phase 3: Spot light
//    // result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
//    vec3 diff = vec3(texture(material.texture_diffuse1, texCoord));
//  //  FragColour = vec4(diff, 1.0);
//    FragColour = vec4(result, 1.0);
//
//} 
//
//// Calculates the color when using a directional light.
//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
//{
//    vec3 lightDir = normalize(-light.direction);
//    // Diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // Specular shading
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//    // Combine results
//	if(material.hasTexture == 1){
//		vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, texCoord));
//		vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, texCoord));
//		vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, texCoord));
//		return (ambient + diffuse + specular);
//	}else{
//		vec3 ambient = light.ambient * material.colour_diffuse;
//		vec3 diffuse = light.diffuse * diff * material.colour_diffuse;
//		vec3 specular = light.specular * spec * material.colour_specular;
//		return (ambient + diffuse + specular);
//	
//	}
//}
//
//// Calculates the color when using a point light.
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
//{
//    vec3 lightDir = normalize(light.position - fragPos);
//    // Diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // Specular shading
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//    // Attenuation
//    float distance = length(light.position - fragPos);
//    float attenuation = 1.0f ;    
//    // Combine results
//	if(material.hasTexture == 1){
//		vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, texCoord));
//		vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, texCoord));
//		vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, texCoord));
//		return (ambient + diffuse + specular);
//
//	}else{
//		vec3 ambient = light.ambient * material.colour_diffuse;
//		vec3 diffuse = light.diffuse * diff * material.colour_diffuse;
//		vec3 specular = light.specular * spec * material.colour_specular;
//		return (ambient + diffuse + specular);
//
//	}
//}