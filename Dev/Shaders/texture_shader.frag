#version 330

uniform sampler2D tex;
in vec2 texCoord;

in vec3 vertPos;
in vec3 N;
in vec3 lightPos;

uniform vec3 La;			// Ambient light intensity
uniform vec3 Ld;            // Diffuse light intensity

out vec4 FragColour;

void main() {


 float attenuation = 1.0;



   //Calculate the light vector
   vec3 L = normalize(lightPos - vertPos);  
    

   vec4 ambient =  vec4(La, 1.0);



   //calculate Diffuse Light Intensity making sure it is not negative 
   //and is clamped 0 to 1  
   vec4 Id = attenuation  * texture(tex,texCoord) * vec4(Ld,1.0) * max(dot(N,L), 0.0);
   Id = clamp(Id, 0.0, 1.0);     


   FragColour = vec4(ambient + Id) * texture(tex,texCoord);
}
