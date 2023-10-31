#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 color;
uniform float x;
uniform float y;
out vec4 ourcolor; 
void main()
{
    gl_Position = vec4(aPos.x+x,aPos.y+y,aPos.z, 1.0);
    ourcolor=vec4(color,1);
}