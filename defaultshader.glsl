#GLSL_vertex
#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat+ projection;

void main()
{
	gl_Position = projection* view * model * vec4(aPos.xyz,1.0);
	vertexColor = vec4((aPos.xyz+1.0)/2,1.0);
}

#GLSL_fragment
#version 330 core

in vec4 vertexColor;
uniform vec4 cpuColor;

out vec4 FragColor;

void main()
{
	FragColor = vertexColor*((cpuColor+vec4(1))/2);
}
