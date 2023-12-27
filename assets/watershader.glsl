#GLSL_vertex
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;

out vec4 vertexColor;

float speed = 0.2;
float waveFunction(vec4 position)
{
	return cos(time*speed+position.x) + sin(-time*speed+position.y);
}

float waveDiffer(vec4 position)
{
	return (-sin(time*speed+position.x) + cos(time*speed+position.z))/(2.0*sqrt(2.0)); // CALCULUS
}

void main()
{
	vec4 finalPosition = model * vec4(aPos.xyz,1.0);
	float height = waveFunction(finalPosition);
	finalPosition.y += height*1.0;
	vec3 waterColor = vec3(0.06,0.37,0.61);
	vertexColor = vec4(waterColor + (vec3(1) - waterColor) * height/20.0,0.25);
	gl_Position = projection * view * finalPosition;
}

#GLSL_fragment
#version 330 core

in vec4 vertexColor;

out vec4 FragColor;

void main()
{
	FragColor = vertexColor;
}
