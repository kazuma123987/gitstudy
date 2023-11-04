#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 color_in;
layout (location=2) in vec2 texPos_in;
uniform mat4 trans;
out vec3 color;
out vec2 texPos;
void main()
{
    gl_Position = trans*vec4(aPos,1);
    color=color_in;
    texPos=texPos_in;
}