#version 400 core
in VS_OUT
{
    vec3 fragPos;
    vec3 normal;
    vec2 texCoord;
    mat3 TBN;
}fs_in;
struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_normal1;
    sampler2D texture_height1;
    sampler2D texture_ambient1;
    float shininess;
};
uniform Material material;
uniform vec3 viewerPos;
uniform float height_scale;
uniform bool hasNormalMap;
uniform bool hasHeightMap;
layout(location=0)out vec3 gPosition;
layout(location=1)out vec3 gNormal;
layout(location=2)out vec4 gDiffuseAndSpecular;
void calculateTexCoord();
void calculateNormal();
vec2 texCoord=vec2(0.0f);
vec3 normal=vec3(0.0f);
void main()
{
    calculateTexCoord();
    calculateNormal();
    gPosition=fs_in.fragPos;
    gNormal=normalize(normal);
    gDiffuseAndSpecular.rgb=texture(material.texture_diffuse1,texCoord).rgb;
    gDiffuseAndSpecular.a=texture(material.texture_specular1,texCoord).a;
}
void calculateNormal()
{
    if(hasNormalMap)
    {
        normal=texture(material.texture_normal1,texCoord).rgb;
        normal=normal*2.0f-1.0f;
        normal=fs_in.TBN*normal;
    }
    else
        normal=fs_in.normal;
}
void calculateTexCoord()
{
    if(hasHeightMap)
    { 
        vec3 viewDir=normalize(transpose(fs_in.TBN)*(viewerPos-fs_in.fragPos));

        const float minLayers=8.0f;
        const float maxLayers=32.0f;
        float layerNum=mix(maxLayers,minLayers,abs(dot(vec3(0.0f,0.0f,1.0f),viewDir)));
        float perLayerDepth=1.0f/layerNum;
        vec2 perTexCoord=(viewDir.xy/viewDir.z*height_scale)/layerNum;

        vec2 curTexCoord=fs_in.texCoord;
        float curTexDepth=texture(material.texture_height1,curTexCoord).r;
        float curLayerDepth=0.0f;
        while(curLayerDepth<curTexDepth)
        {
            curLayerDepth+=perLayerDepth;
            curTexCoord-=perTexCoord;
            curTexDepth=texture(material.texture_height1,curTexCoord).r;
        }
        vec2 beforeTexCoord=curTexCoord+perTexCoord;
        //计算层深与高度贴图深度的差值
        float beforeDiff=texture(material.texture_height1,beforeTexCoord).r-(curLayerDepth-perLayerDepth);
        float afterDiff=curLayerDepth-curTexDepth;
        texCoord=beforeTexCoord-beforeDiff/(afterDiff+beforeDiff)*perTexCoord;
        if(texCoord.x>1.0f||texCoord.y>1.0f|| texCoord.x < 0.0f || texCoord.y < 0.0f)
            discard;
    }
    else 
        texCoord=fs_in.texCoord;
}