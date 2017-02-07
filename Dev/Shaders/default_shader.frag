#version 330 core

in vec2 Colour;

out vec4 color;

uniform vec4 colour;

void main()
{    
    color = vec4(colour);
}  