#version 400 core
layout(location=0)in vec3 aPos;
layout(location=1)in vec2 aTexCoords;
layout(location=7)in mat4 modelMat;
layout(std140)uniform Mat
{
    mat4 view;
    mat4 proj;
};
out vec2 texCoords;
void main()
{
    gl_Position=proj*view*modelMat*vec4(aPos,1.0f);
    texCoords=aTexCoords;     
}