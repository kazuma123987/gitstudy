#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 texPos_in;
layout(location = 2) in vec3 Normal_in;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat3 normalMat;//法向量矩阵(观察空间的变换矩阵)
uniform vec3 LightPos;//光源位置(世界坐标)
out vec3 normal;
out vec2 texPos;
out vec3 vertexPos;
out vec3 lightPos;
void main()
{
	gl_Position = proj*view*model * vec4(aPos, 1.0f);//输出的顶点位置(投影空间坐标)
	vertexPos=vec3(view*model*vec4(aPos,1.0f));//顶点位置(观察空间坐标)
	lightPos=vec3(view*vec4(LightPos,1.0f));//光源位置(观察空间坐标)
	normal=normalize(normalMat*Normal_in);//法向量位置(观察空间坐标)
	texPos = texPos_in;//纹理位置(世界坐标)
}