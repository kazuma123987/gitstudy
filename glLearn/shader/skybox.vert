#version 400 core
layout(location=0)in vec3 aPos;
uniform mat4 view;//w分量为0的矩阵
uniform mat4 proj;
out vec3 texCoord;
void main(){
    vec4 pos=proj*mat4(mat3(view))*vec4(aPos,1.0f);
    texCoord=aPos*2.0f;
    gl_Position=pos.xyww;
}