#version 400 core
layout(location=0)in vec3 aPos;
layout(location=1)in vec3 aNormal;
layout(location=2)in vec2 aTexCoord;
layout(location=3)in vec3 aTangent;
layout(location=4)in vec3 aBitangent;
layout(location=7)in mat4 modelMat;
layout(std140)uniform Mat
{
	mat4 view;
	mat4 proj;
};
uniform mat4 model;
uniform bool isInstance;
out VS_OUT
{
    vec3 fragPos;
    vec3 normal;
    vec2 texCoord;
    mat3 TBN;
}vs_out;
void main()
{
    mat4 modelMatrix=model;
    if(isInstance)modelMatrix=modelMat;
    vs_out.fragPos=vec3(modelMatrix*vec4(aPos,1.0f));
    mat3 normMat=transpose(inverse(mat3(modelMatrix)));
    vs_out.normal=normalize(normMat*aNormal);
    vs_out.texCoord=aTexCoord;
    vs_out.TBN=mat3(normalize(normMat*aTangent),normalize(normMat*aBitangent),vs_out.normal);
    gl_Position=proj*view*modelMatrix*vec4(aPos,1.0f);
}