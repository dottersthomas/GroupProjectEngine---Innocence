
in vec2 TexCoords;
out vec4 FragColour;

uniform sampler2D screenTexture;

uniform int ppToggle;

void main()
{ 
    //color = texture(screenTexture, TexCoords);
    //float average = (color.r + color.g + color.b) / 3.0;
    //color = vec4(average, average, average, 1.0);
	if(ppToggle == 1){
		vec4 uColor = vec4(0.0, 1.0, 0.0, 1.0);
		vec4 color = uColor * texture2D(screenTexture, TexCoords);
		float v = max(max(color.r, color.g), color.b);
		FragColour = vec4(0.0, v, 0.0, color.a);
	}else{
		FragColour = texture(screenTexture, TexCoords);
	
	}

}