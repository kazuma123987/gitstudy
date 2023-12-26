#version 400 core
in vec2 texCoord;
layout(std140)uniform Mat
{
	mat4 view;
	mat4 proj;
};
uniform sampler2D gPositionDepth;
uniform sampler2D gNormal;
uniform sampler2D noiseMap;//每个像素rgb值组成的vec3向量位于垂直于正z方向的xy平面上,纹理为4*4大小
uniform vec3 samples[64];//位于切线空间,半径为0.0~1.0的正半球面
uniform int kernelSize;
uniform float radius;
vec3 fragPos=texture(gPositionDepth,texCoord).rgb;
vec3 normal=texture(gNormal,texCoord).rgb;
vec3 noiseVec=normalize(texture(noiseMap,texCoord*vec2(1600/4.0f,900/4.0f)).rgb);//这里把4*4的纹理拓展成了1600*900的纹理
out vec4 FragColor;
void main()
{
    vec3 tangent=normalize(noiseVec-dot(normal,noiseVec)*normal);//tangent向量就是noiseVec向normal向量做的垂线
    vec3 bitangent=cross(normal,tangent);
    mat3 TBN=mat3(tangent,bitangent,normal);
    float occlusion=0.0f;
    for(int i=0;i<kernelSize;i++)
    {
        vec3 samplePos=TBN*samples[i];//切线空间向量->世界空间向量
        samplePos=fragPos+samplePos*radius;//世界空间向量->世界坐标
        vec4 viewSample=view*vec4(samplePos,1.0f);
        vec4 projSample=proj*viewSample;//观察空间坐标->裁切空间坐标((x,y,z)/w∈[-1,1])
        projSample.xyz/=projSample.w;//归一化
        projSample.xyz=(projSample.xyz+1.0f)*0.5f;
        float sampleDepth=texture(gPositionDepth,projSample.xy).a;//注意采样的观察空间z坐标
        float bias=0.025f;
        //smoothstep(float a,float b,float x) t=satitude
        float rangeCheck=smoothstep(0.0f,1.0f,radius/abs(-viewSample.z-sampleDepth));
        occlusion+=(-viewSample.z-bias>sampleDepth?1.0f:0.0f)*rangeCheck;//!观察空间摄像机朝向为-z方向
    }
    occlusion=1.0f-occlusion/kernelSize;
    FragColor=vec4(vec3(occlusion),1.0f);
}