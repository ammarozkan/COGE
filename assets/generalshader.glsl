#GLSL_vertex
#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 vertexPosition;
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
	vertexPosition = (model * vec4(aPos.xyz,1.0)).xyz;
}

#GLSL_fragment
#version 330 core

in vec4 vertexColor;
in vec3 vertexPosition;

uniform vec4 cpuColor;
uniform vec3 cameraPosition;

out vec4 FragColor;

void main()
{
	vec3 sunDirection = normalize(vec3(1.0,0.5,1.0));
    vec4 sunColor = vec4(255,235,200,255)/255;
	vec4 object_color = vertexColor*((cpuColor+vec4(1))/2);


	vec3 normal = normalize(cross(dFdx(vertexPosition), dFdy(vertexPosition)));
	vec3 look_dir = normalize(cameraPosition - vertexPosition);
	vec3 reflect_dir = normalize(reflect(sunDirection,normal));
	float luma = max(dot(normal,sunDirection),0.0);

	vec4 came_light = (sunColor*0.5 + luma*sunColor)/(1.5);
	FragColor = object_color * came_light;
}
