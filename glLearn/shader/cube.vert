#version 400 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 normal_in;
layout(location = 2) in vec2 texPos_in;
uniform mat4 model;
layout(std140)uniform Mat
{
	uniform mat4 view;
	uniform mat4 proj;
};
uniform mat3 normMat;//法向量矩阵
out vec3 fragPos;
out vec3 normal;
out vec2 texPos;
void main()
{
	gl_Position = proj*view*model * vec4(aPos, 1.0f);
	fragPos=vec3(model*vec4(aPos,1.0f));//顶点
	normal=normalize(normMat*normal_in);//法向量
	texPos = texPos_in;//纹理
}