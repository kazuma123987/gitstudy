#version 400 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 normal_in;
layout(location = 2) in vec2 texPos_in;
layout(std140)uniform Mat
{
	mat4 view;
	mat4 proj;
};
uniform mat4 shadowSpaceMat;
uniform mat4 model;
uniform mat3 normMat;//法向量矩阵
//使用接口块效率更佳
out VS_OUT
{
vec3 fragPos;
vec4 fragPosShadowSpace;
vec3 normal;
vec2 texPos;
}vs_out;
void main()
{
	gl_Position = proj*view*model * vec4(aPos.x+gl_InstanceID,aPos.yz, 1.0f);
	vs_out.fragPos=vec3(model*vec4(aPos,1.0f));//顶点
	vs_out.fragPosShadowSpace=shadowSpaceMat*vec4(vs_out.fragPos,1.0f);
	vs_out.normal=normalize(normMat*normal_in);//法向量
	vs_out.texPos = texPos_in;//纹理
}