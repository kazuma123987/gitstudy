#version 400 core
layout(location=0)in vec3 aPos;
layout(location=1)in vec2 aTexCoord;
layout(std140)uniform Mat
{
    mat4 view;
    mat4 proj;
};
uniform mat4 model;
out vec2 texCoord;
void main()
{
    gl_Position=proj*view*model*vec4(aPos,1.0f);
    texCoord=aTexCoord;     
}