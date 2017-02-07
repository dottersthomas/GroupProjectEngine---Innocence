#version 330
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = vec2(1.0 - vertex.x, vertex.y);
    gl_Position = projection * view * model  * vec4(vertex.xyz, 1.0);
}