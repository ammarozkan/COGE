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
    ui_position = vec2((object_size.x*aPos.x+position.x)/screen_size.x, (object_size.y*aPos.y+position.y)/screen_size.y);
    gl_Position = transform * vec4(ui_position.xy, 0.0, 1.0);
    ourColor = vec4(1.0);
}

#GLSL_fragment
#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
  
void main()
{
    FragColor = vec4(ourColor, 1.0);
}