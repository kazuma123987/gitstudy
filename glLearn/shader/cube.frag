#version 400 core
in VS_OUT
{
vec3 fragPos;
vec4 fragPosShadowSpace;
vec3 normal;//已标准化
vec2 texPos;
}fs_in;
//材质
struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_reflect1;
    float shininess;
};
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
//声明
vec3 dirColor(DirectLight dirLight);
vec3 dotColor(DotLight dotLight);
vec3 spotColor(SpotLight spotLight);
vec3 reflectColor();
float calculateShadow(vec4 fragPosShadowSpace,vec3 fragToLight);
//uniform变量
uniform Material material;
uniform DirectLight dirLight;
uniform DotLight dotLight[4];
uniform SpotLight spotLight;
uniform vec3 viewerPos;
uniform samplerCube texture_cube1;
uniform sampler2D shadowMap;
//全局变量
vec2 pixelSize=2.0f/textureSize(shadowMap,0);
void main()
{
    vec3 result=dirColor(dirLight);
    // for(int i=0;i<4;i++)
    //     result+=dotColor(dotLight[i]); 
    // result+=spotColor(spotLight);
    // result+=reflectColor();
    //输出颜色
    gl_FragColor=vec4(result,1.0f);
}
vec3 dirColor(DirectLight dirLight)
{
    //环境光
    vec3 ambient=dirLight.ambient*vec3(texture(material.texture_diffuse1,fs_in.texPos));
    //漫射光
    vec3 fragToLight=normalize(-dirLight.dir);
    float diff=max(dot(fragToLight,fs_in.normal),0.0f);
    vec3 diffuse=diff*dirLight.diffuse*vec3(texture(material.texture_diffuse1,fs_in.texPos));
    //镜面光
    vec3 fragToViewer=normalize(viewerPos-fs_in.fragPos);
    vec3 halfwayDir=normalize(fragToLight+fragToViewer);
    float spec=pow(max(dot(halfwayDir,fs_in.normal),0.0f),material.shininess);
    vec3 specular=spec*dirLight.specular*vec3(texture(material.texture_specular1,fs_in.texPos));
    //计算阴影
    float shadow=calculateShadow(fs_in.fragPosShadowSpace,fragToLight);
    //返回值
    return(ambient+(1-shadow)*(diffuse+specular));
}
vec3 dotColor(DotLight dotLight)
{
    //环境光
    vec3 ambient=dotLight.ambient*vec3(texture(material.texture_diffuse1,fs_in.texPos));
    //漫射光
    vec3 fragToLight=normalize(dotLight.pos-fs_in.fragPos);
    float diff=max(dot(fragToLight,fs_in.normal),0.0f);
    vec3 diffuse=diff*dotLight.diffuse*vec3(texture(material.texture_diffuse1,fs_in.texPos));
    //镜面光
    vec3 fragToViewer=normalize(viewerPos-fs_in.fragPos);
    vec3 halfwayDir=normalize(fragToLight+fragToViewer);
    float spec=pow(max(dot(halfwayDir,fs_in.normal),0.0f),material.shininess);
    vec3 specular=spec*dotLight.specular*vec3(texture(material.texture_specular1,fs_in.texPos));
    //衰减率
    float d=length(dotLight.pos-fs_in.fragPos);
    float decay=1.0f/(dotLight.constant+dotLight.linear*d+dotLight.quadratic*d*d);
    //返回值
    return(ambient+diffuse+specular)*decay;
}
vec3 spotColor(SpotLight spotLight)
{
    //环境光
    vec3 ambient=spotLight.ambient*vec3(texture(material.texture_diffuse1,fs_in.texPos));
    //漫射光
    vec3 fragToLight=normalize(spotLight.pos-fs_in.fragPos);
    float diff=max(dot(fragToLight,fs_in.normal),0.0f);
    vec3 diffuse=diff*spotLight.diffuse*vec3(texture(material.texture_diffuse1,fs_in.texPos));
    //镜面光
    vec3 fragToViewer=normalize(viewerPos-fs_in.fragPos);
    vec3 halfwayDir=normalize(fragToLight+fragToViewer);
    float spec=pow(max(dot(halfwayDir,fs_in.normal),0.0f),material.shininess);
    vec3 specular=spec*spotLight.specular*vec3(texture(material.texture_specular1,fs_in.texPos));
    //衰减率
    float d=length(spotLight.pos-fs_in.fragPos);
    float decay=1.0f/(spotLight.constant+spotLight.linear*d+spotLight.quadratic*d*d);
    //可见度
    float delta=dot(normalize(spotLight.front),-fragToLight);
    float visiable=clamp((delta-spotLight.outCutOff)/(spotLight.inCutOff-spotLight.outCutOff),0.0f,1.0f);
    //返回值
    return(ambient+diffuse+specular)*decay*visiable;
}
vec3 reflectColor()
{
    vec3 viewerTofrag=normalize(fs_in.fragPos-viewerPos);
    vec3 reflectLight=reflect(viewerTofrag,fs_in.normal);
    return vec3(texture(material.texture_reflect1,fs_in.texPos))*vec3(texture(texture_cube1,reflectLight));
}
float calculateShadow(vec4 fragPosShadowSpace,vec3 fragToLight)
{
    vec3 projCoords=fragPosShadowSpace.xyz/fragPosShadowSpace.w;//归一化为裁切空间坐标
    projCoords=(projCoords+1)*0.5f;//把坐标范围转化为[0,1],x和y变为UV坐标,z变成最近的深度值
    //float closestDepth=texture(shadowMap,projCoords.xy).r;
    float currentDepth=projCoords.z;
    float bias=max(0.005f*(1.0f-dot(fragToLight,fs_in.normal)),0.0f);//阴影的近平面与远平面距离越大,bias应越小(当法线方向与光的方向一致则无需偏移)
    float shadow=0.0f;
    for(int i=-1;i<=1;i++)
        for(int j=-1;j<=1;j++)
        {
            float sampleDepth=texture(shadowMap,projCoords.xy+vec2(i,j)*pixelSize).r;
            shadow+=currentDepth-bias>sampleDepth?1.0f:0.0f;
        }
    shadow/=9.0f;
    if(projCoords.z>1.0f)shadow=0.0f;//这里让深度贴图(阴影贴图)视光锥外的部分不产生阴影
    return shadow;
}