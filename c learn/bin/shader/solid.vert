#version 400 core
layout(location=0)in vec2 aPos;
uniform mat4 proj;
uniform vec2 offset;
uniform float scale;
void main()
{
    gl_Position=proj*vec4(aPos.xy*scale+offset,0.0f,1.0f);
}