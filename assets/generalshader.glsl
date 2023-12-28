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
uniform vec3 sunDirection;

out vec4 FragColor;

vec4 getSunColor()
{
    vec3 worldPlane = normalize(vec3(sunDirection.x,0,sunDirection.z));
    float nearToWorldPlane = length(cross(worldPlane,sunDirection));
	return vec4(255,235*nearToWorldPlane,200*nearToWorldPlane,255)/255;
}

float getSunPower()
{
    return pow((dot(sunDirection,vec3(0,1,0))+1)/2,1);
}

void main()
{
    vec4 sunColor = getSunColor();
	float sunPower = 1;
	vec4 object_color = vertexColor*((cpuColor+vec4(1))/2);


	vec3 normal = normalize(cross(dFdx(vertexPosition), dFdy(vertexPosition)));
	vec3 look_dir = normalize(cameraPosition - vertexPosition);
	vec3 reflect_dir = normalize(reflect(sunDirection,normal));
	float luma = max(dot(normal,sunDirection),0.0);

	vec4 came_light = (vec4(0.1,0.1,0.2,1.0)+ 0.4*sunColor*getSunPower() + 0.6*getSunPower()*sunPower*luma*sunColor);
	FragColor = object_color * came_light;
}
