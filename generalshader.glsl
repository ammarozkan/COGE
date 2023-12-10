#GLSL_vertex
#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 xEffect;
uniform vec3 yEffect;
uniform vec3 zEffect;

uniform vec3 colorConstant;
uniform float colorConstant_effect=0;

void main()
{
	gl_Position = projection* view * model * vec4(aPos.xyz,1.0);
	//vertexColor = vec4((aPos.xyz+1.0)/2,1.0);
	vec3 c_p = xEffect*aPos.x + yEffect*aPos.y + zEffect*aPos.z;
	vec3 effected_color = (c_p+colorConstant*colorConstant_effect)/(1+colorConstant_effect);
	vertexColor = vec4((effected_color+1.0f)/2,1.0);
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
