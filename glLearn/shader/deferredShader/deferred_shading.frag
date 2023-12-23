#version 400 core
//定向光
struct DirectLight
{
    vec3 dir;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
//点光源
struct DotLight
{
    vec3 pos;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};
//聚光灯
struct SpotLight
{
    vec3 pos;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
    float inCutOff;
    float outCutOff;
    vec3 front;
};
in vec2 texCoord;
//uniform变量
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gDiffuseAndSpecular;

uniform sampler2D dirShadowMap;
uniform samplerCube dotShadowMap;
uniform sampler2D spotShadowMap;
uniform mat4 dirShadowSpaceMat;
uniform mat4 spotShadowSpaceMat;

uniform bool dirLight_ON;
uniform bool dotLight_ON;
uniform bool spotLight_ON;
uniform float near_plane;
uniform float far_plane;
uniform DirectLight dirLight;
uniform DotLight dotLight;
uniform SpotLight spotLight;

uniform vec3 viewerPos;
//声明
vec3 dirColor(DirectLight dirLight);
vec3 dotColor(DotLight dotLight);
vec3 spotColor(SpotLight spotLight);
float linearDepth(float depth);
out vec4 FragColor;
//全局变量
vec3 fragPos=texture(gPosition,texCoord).rgb;
vec3 normal=texture(gNormal,texCoord).rgb;
vec3 diffuse=texture(gDiffuseAndSpecular,texCoord).rgb;
float sp=texture(gDiffuseAndSpecular,texCoord).a;
vec3 viewDir=normalize(viewerPos-fragPos);
vec2 pixelSize=1.0f/textureSize(dirShadowMap,0);
void main()
{
    //计算光照
    vec3 result=vec3(0.0f);
    if(dirLight_ON)
        result+=dirColor(dirLight);
    if(dotLight_ON)
        result+=dotColor(dotLight);
    if(spotLight_ON)
        result+=spotColor(spotLight);
    FragColor=vec4(result,1.0f);
}
vec3 dirColor(DirectLight dirLight)
{
    //环境光
    vec3 ambient=dirLight.ambient*diffuse;
    //漫射光
    vec3 lightDir=normalize(-dirLight.dir);
    float diff=max(dot(lightDir,normal),0.0f);
    vec3 finalDiffuse=diff*dirLight.diffuse*diffuse;
    //计算阴影
    vec4 dirFragPos=dirShadowSpaceMat*vec4(fragPos,1.0f);
    vec3 projCoord=dirFragPos.rgb/dirFragPos.w;
    projCoord=(projCoord+1.0f)*0.5f;
    float currentDepth=projCoord.z;//片段的深度值
    float bias=pixelSize.x*sqrt(1-dot(lightDir,normal));//h=d/2*sin(θ)
    float shadow=0.0f;
    for(int i=-1;i<=1;i++)
        for(int j=-1;j<=1;j++)
        {
            float sampleDepth=texture(dirShadowMap,projCoord.xy+vec2(i,j)*pixelSize).r;//光源到片段所在直线上最近片段的深度值
            shadow+=currentDepth-bias>sampleDepth?1.0f:0.0f;
        }
    shadow/=9.0f;
    //返回值
    return(ambient+(1.0f-shadow)*finalDiffuse);
}
vec3 dotColor(DotLight dotLight)
{
    //环境光
    vec3 ambient=dotLight.ambient*diffuse;
    //漫射光
    vec3 lightDir=normalize(dotLight.pos-fragPos);
    float diff=max(dot(lightDir,normal),0.0f);
    vec3 finalDiffuse=diff*dotLight.diffuse*diffuse;
    //衰减率
    float d=length(dotLight.pos-fragPos);
    float decay=1.0f/(dotLight.constant+dotLight.linear*d+dotLight.quadratic*d*d);
    //计算阴影
    float currentDepth=length(dotLight.pos-fragPos)/far_plane;
    float closestDepth=texture(dotShadowMap,-lightDir).r;
    float bias=0.005f;
    float shadow=currentDepth-bias>closestDepth?1.0f:0.0f;
    //返回值
    return(ambient+(1.0f-shadow)*finalDiffuse)*decay;
}
vec3 spotColor(SpotLight spotLight)
{
    //环境光
    vec3 ambient=spotLight.ambient*diffuse;
    //漫射光
    vec3 lightDir=normalize(spotLight.pos-fragPos);
    float diff=max(dot(lightDir,normal),0.0f);
    vec3 finalDiffuse=diff*spotLight.diffuse*diffuse;
    //衰减率
    float d=length(spotLight.pos-fragPos);
    float decay=1.0f/(spotLight.constant+spotLight.linear*d+spotLight.quadratic*d*d);
    //可见范围
    float delta=dot(normalize(spotLight.front),-lightDir);
    float visiable=clamp((delta-spotLight.outCutOff)/(spotLight.inCutOff-spotLight.outCutOff),0.0f,1.0f);
    //计算阴影
    vec4 spotFragPos=spotShadowSpaceMat*vec4(fragPos,1.0f);
    vec3 projCoord=spotFragPos.rgb/spotFragPos.w;
    projCoord=(projCoord+1.0f)*0.5f;
    float currentDepth=projCoord.z;//片段的深度值
    float currentLinearDepth=linearDepth(currentDepth);
    float bias=pixelSize.x*sqrt(1-dot(lightDir,normal));
    float shadow=0.0f;
    for(int i=-1;i<=1;i++)
        for(int j=-1;j<=1;j++)
        {
            float sampleDepth=texture(spotShadowMap,projCoord.xy+vec2(i,j)*pixelSize).r;//光源到片段所在直线上最近片段的深度值
            shadow+=currentLinearDepth-bias>linearDepth(sampleDepth)?1.0f:0.0f;
        }
    shadow/=9.0f;
    //返回值
    return (ambient+(1.0f-shadow)*finalDiffuse)*decay*visiable;
}
float linearDepth(float depth)
{
    return (near_plane*far_plane/(far_plane+(near_plane-far_plane)*depth)-near_plane)/(far_plane-near_plane);
}