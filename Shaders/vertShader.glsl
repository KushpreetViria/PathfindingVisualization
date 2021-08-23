#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 MVP_matrix;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    //gl_Position = MVP_matrix * vec4(aPos, 1.0);
}