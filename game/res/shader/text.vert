#version 400 core
layout(location=0)in vec4 aPos;
uniform mat4 proj;
out vec2 texCoord;
void main()
{
    texCoord=aPos.zw;
    gl_Position=proj*vec4(aPos.xy,0.0f,1.0f);
}