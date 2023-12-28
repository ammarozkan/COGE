#GLSL_vertex
#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 vertexPosition;
out vec4 vertexColor;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * vec4(1.0*aPos.xyz,1.0);
	//vertexColor = vec4((aPos.xyz+1.0)/2,1.0);
	vertexPosition = (vec4(aPos.xyz,1.0)).xyz;
}

#GLSL_fragment
#version 330 core

in vec4 vertexColor;
in vec3 vertexPosition;

out vec4 FragColor;

uniform vec3 sunDirection;


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
    vec4 sunDefaultColor = vec4(255,235,200,255)/255;
    vec4 skyMatter = (vec4(135,206,235,255)/255)/sunDefaultColor;
    vec4 sunColor = getSunColor();
    vec4 skyColor = getSunPower()*vec4(135,206,235,255)/255;

    vec3 drawDirection = normalize(vertexPosition);

    float maxStrongium = 2;
    float sunInfiniteStronsium = sqrt(1/length(cross(drawDirection,sunDirection)));
    float sunStronsium = (dot(drawDirection,sunDirection) + 1)/2;

    vec4 effectedColor = (skyColor + sunInfiniteStronsium*sunColor)/(1+sunInfiniteStronsium);

    FragColor = (effectedColor*sunStronsium + skyColor*(1-sunStronsium))*sqrt(getSunPower());
}
