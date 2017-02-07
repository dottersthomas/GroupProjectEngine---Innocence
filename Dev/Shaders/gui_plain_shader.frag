#version 330

in vec2 TexCoords;
out vec4 colour;

uniform vec4 elementColour;

void main()
{    
    colour = vec4(elementColour);
}  