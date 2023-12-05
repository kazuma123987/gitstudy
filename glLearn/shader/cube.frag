#version 400 core
in vec2 texPos;
in vec3 fragPos;
in vec3 normal;//法向量(已标准化)
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
//uniform变量
uniform Material material;
uniform DirectLight dirLight;
uniform DotLight dotLight[4];
uniform SpotLight spotLight;
uniform vec3 viewerPos;
uniform samplerCube texture_cube1;
void main()
{
    vec3 result=dirColor(dirLight);
    for(int i=0;i<4;i++)
        result+=dotColor(dotLight[i]); 
    result+=spotColor(spotLight);
    result+=reflectColor();
    //输出颜色
    gl_FragColor=vec4(result,1.0f);
}
vec3 dirColor(DirectLight dirLight)
{
    //环境光
    vec3 ambient=dirLight.ambient*vec3(texture(material.texture_diffuse1,texPos));
    //漫射光
    vec3 fragToLight=normalize(-dirLight.dir);
    float diff=max(dot(fragToLight,normal),0.0f);
    vec3 diffuse=diff*dirLight.diffuse*vec3(texture(material.texture_diffuse1,texPos));
    //镜面光
    vec3 reflectLight=reflect(-fragToLight,normal);
    vec3 fragToViewer=normalize(viewerPos-fragPos);
    float spec=pow(max(dot(reflectLight,fragToViewer),0.0f),material.shininess);
    vec3 specular=spec*dirLight.specular*vec3(texture(material.texture_specular1,texPos));
    //返回值
    return(ambient+diffuse+specular);
}
vec3 dotColor(DotLight dotLight)
{
    //环境光
    vec3 ambient=dotLight.ambient*vec3(texture(material.texture_diffuse1,texPos));
    //漫射光
    vec3 fragToLight=normalize(dotLight.pos-fragPos);
    float diff=max(dot(fragToLight,normal),0.0f);
    vec3 diffuse=diff*dotLight.diffuse*vec3(texture(material.texture_diffuse1,texPos));
    //镜面光
    vec3 reflectLight=reflect(-fragToLight,normal);
    vec3 fragToViewer=normalize(viewerPos-fragPos);
    float spec=pow(max(dot(reflectLight,fragToViewer),0.0f),material.shininess);
    vec3 specular=spec*dotLight.specular*vec3(texture(material.texture_specular1,texPos));
    //衰减率
    float d=length(dotLight.pos-fragPos);
    float decay=1.0f/(dotLight.constant+dotLight.linear*d+dotLight.quadratic*d*d);
    //返回值
    return(ambient+diffuse+specular)*decay;
}
vec3 spotColor(SpotLight spotLight)
{
    //环境光
    vec3 ambient=spotLight.ambient*vec3(texture(material.texture_diffuse1,texPos));
    //漫射光
    vec3 fragToLight=normalize(spotLight.pos-fragPos);
    float diff=max(dot(fragToLight,normal),0.0f);
    vec3 diffuse=diff*spotLight.diffuse*vec3(texture(material.texture_diffuse1,texPos));
    //镜面光
    vec3 reflectLight=reflect(-fragToLight,normal);
    vec3 fragToViewer=normalize(viewerPos-fragPos);
    float spec=pow(max(dot(reflectLight,fragToViewer),0.0f),material.shininess);
    vec3 specular=spec*spotLight.specular*vec3(texture(material.texture_specular1,texPos));
    //衰减率
    float d=length(spotLight.pos-fragPos);
    float decay=1.0f/(spotLight.constant+spotLight.linear*d+spotLight.quadratic*d*d);
    //可见度
    float delta=dot(normalize(spotLight.front),-fragToLight);
    float visiable=clamp((delta-spotLight.outCutOff)/(spotLight.inCutOff-spotLight.outCutOff),0.0f,1.0f);
    //返回值
    return(ambient+diffuse+specular)*decay*visiable;
}
vec3 reflectColor()
{
    vec3 viewerTofrag=normalize(fragPos-viewerPos);
    vec3 reflectLight=reflect(viewerTofrag,normal);
    return vec3(texture(material.texture_reflect1,texPos))*vec3(texture(texture_cube1,reflectLight));
}