#GLSL_vertex
#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 vertexPosition;
out vec4 vertexColor;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * vec4(10.0*aPos.xyz,1.0);
	//vertexColor = vec4((aPos.xyz+1.0)/2,1.0);
	vertexPosition = (vec4(aPos.xyz,1.0)).xyz;
}

#GLSL_fragment
#version 330 core

in vec4 vertexColor;
in vec3 vertexPosition;

out vec4 FragColor;

void main()
{
	vec3 sunDirection = vec3(1.0,0.5,1.0);
    vec3 drawDirection = normalize(vertexPosition);
    vec4 sunColor = vec4(255,235,200,255)/255;
    vec4 skyColor = vec4(135,206,235,255)/255;


    float maxStrongium = 2;
    float sunPointEffect = 1/length(cross(drawDirection,sunDirection));
    float sunStronsium = (dot(drawDirection,sunDirection) + 1)/2;

    vec4 effectedColor = (skyColor + sunPointEffect*sunColor)/(1+sunPointEffect);

    FragColor = effectedColor*sunStronsium + skyColor*(1-sunStronsium);
}
