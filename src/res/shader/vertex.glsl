#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 coordinates;

out vec2 FragCoordinates;

uniform mat4 uModel;
uniform mat4 uProj;

void main()
{
  gl_Position = uProj * uModel * vec4(position, 0.0, 1.0);
  FragCoordinates = coordinates;
}
