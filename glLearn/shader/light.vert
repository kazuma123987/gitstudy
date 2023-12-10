#version 330 core
layout(location = 0) in vec3 aPos;
uniform mat4 model;
layout(std140)uniform Mat
{
	mat4 view;
	mat4 proj;
};
void main()
{
	gl_Position = proj*view*model * vec4(aPos, 1.0f);
}