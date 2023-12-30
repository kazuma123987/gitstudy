#version 400 core
layout(location=0)in vec4 aPos;
out vec2 texCoord;
uniform mat4 proj;
uniform mat4 model;
void main()
{
    gl_Position=proj*model*vec4(aPos.xy,0.0f,1.0f);
    texCoord=aPos.zw;
}