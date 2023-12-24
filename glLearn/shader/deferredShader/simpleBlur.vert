#version 400 core
layout(location=0)in vec3 aPos;
layout(location=1)in vec2 aTexCoord;
out vec2 texCoord;
void main()
{
    texCoord=aTexCoord;
    gl_Position=vec4(aPos.xy,0.0f,1.0f);
}