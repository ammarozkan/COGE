#GLSL_vertex
#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0

out vec3 ourColor; // output a color to the fragment shader

uniform vec2 screen_size;
uniform vec2 object_size;
uniform vec2 position;

uniform mat4 transform;

void main()
{
    vec4 aPos_t = transform*vec4(aPos.xy,0.0,1.0);
    float ui_posx = 2*(object_size.x*aPos_t.x+position.x)/screen_size.x - 1.0;
    float ui_posy = 2*(object_size.y*aPos_t.y+position.y)/screen_size.y - 1.0;
    gl_Position = vec4(ui_posx, ui_posy, 0.0, 1.0);
    ourColor = vec3(1.0);
}

#GLSL_fragment
#version 330 core
out vec4 FragColor;
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}
