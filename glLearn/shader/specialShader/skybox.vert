#version 400 core
layout(location=0)in vec3 aPos;
layout(std140)uniform Mat
{
	mat4 view;
	mat4 proj;
};
out vec3 texCoord;
void main(){
    vec4 pos=proj*mat4(mat3(view))*vec4(aPos,1.0f);
    texCoord=aPos*2.0f;
    gl_Position=pos.xyww;
}