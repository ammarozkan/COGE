#GLSL_vertex
#version 330 core
layout (location = 0) in vec2 aPos;
out vec4 vertexColor;

uniform vec3 color;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model * vec4(aPos.xy,0.0,1.0);
	vertexColor = vec4(vec3(1),1.0);
}

#GLSL_fragment
#version 330 core

in vec4 vertexColor;

out vec4 FragColor;

void main()
{
	FragColor = vertexColor;
}
