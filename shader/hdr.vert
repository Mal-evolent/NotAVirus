#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexTexCoord;

out vec2 TexCoords;

void main()
{
    TexCoords = VertexTexCoord;
    gl_Position = vec4(VertexPosition, 1.0);
} 