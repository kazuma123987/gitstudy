#version 400 core
layout(location=0)in vec4 posTex;
out vec2 texCoord;
layout(std140)uniform Mat
{
    mat4 view;
    mat4 proj;
};
uniform mat4 projection;
void main()
{
    texCoord=posTex.zw;
    gl_Position=projection*vec4(posTex.xy,0.0f,1.0f);
    //gl_Position=proj*view*vec4(posTex.xy/1600.0f,5.0f,1.0f);
}