#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
  
out vec4 color;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

uniform highp mat4 mView;


void main()
{
    vec3 ambient = light.ambient * material.ambient;
  	
	vec3 norm = normalize(Normal);
    vec3 lightDir = normalize((vec3(mView) * light.position) - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
	diffuse = clamp(diffuse, 0.0, 1.0);
   
	vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
      
	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0f);
	//color = vec4(reflectDir * vec3(0.5) + vec3(0.5), 1.0f);




//	float attenuation = 1.0;
//   //Calculate the light vector
//
//   vec3 L = normalize(light.position - FragPos);  
//   vec4 ambient = vec4(light.ambient * material.ambient, 1.0);
// 
//   vec4 Id = attenuation * vec4(material.diffuse,1.0) * vec4(light.diffuse,1.0) * max(dot(Normal,L), 0.0);
//   Id = clamp(Id, 0.0, 1.0);   
//     
//   vec4 specular;
//   specular = attenuation * vec4(light.specular, 1.0) * vec4(material.specular, 1.0) * pow(max(0.0, dot(reflect(-L, Normal), normalize(FragPos))),5.0);
//
//   color =  vec4( ambient + Id + specular);
} 