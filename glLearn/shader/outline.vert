#version 400 core
layout(location=0)in vec3 aPos;
layout(location=1)in vec3 normal_in;
uniform mat4 model;
layout(std140)uniform Mat
{
	mat4 view;
	mat4 proj;
};
void main(){
    gl_Position=proj*view*model*vec4(aPos+0.1*normal_in,1.0f);
}