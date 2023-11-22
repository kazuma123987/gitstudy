#version 400 core
//材质
struct Material{
    sampler2D diffuseTexture;//材质的漫射光反射贴图
    sampler2D specularTexture;//材质的镜面光反射贴图
    float shininess;//材质的反光度
};
//定向光
struct DirectLight{
    vec3 lightToFrag;//光->片段(观察空间)
    vec3 ambient;//环境光颜色
    vec3 diffuse;//漫射光颜色
    vec3 specular;//镜面光颜色
};
//点光源
struct DotLight{
    vec3 position; 
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
//衰减率deque=1.0f/(constant+linear*d+quadratic*d*d)
    float constant;
    float linear;
    float quadratic;
};
//聚光灯
struct SpotLight{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    vec3 spotFront;//聚光灯前方
    float inCutOff;//内切光角的余弦
    float outCutOff;//外切光角的余弦
};
//输入变量
in vec2 texPos;//纹理坐标
in vec3 vertexPos;//顶点坐标(观察空间)
in vec3 normal;//法向量(观察空间)
//uniform变量
uniform Material material;//材质
uniform DirectLight dirLight;//定向光
uniform DotLight dotLight[4];//点光源
uniform SpotLight spotLight;//聚光灯
//定义的函数声明
vec3 directColor(DirectLight dirLight,vec3 fragToViewer);
vec3 dotColor(DotLight dotLight,vec3 fragToViewer);
vec3 spotColor(SpotLight spotLight,vec3 fragToViewer);
void main()
{
    vec3 fragToViewer=-normalize(vertexPos);
    vec3 result=vec3(0.0f);
    result+=directColor(dirLight,fragToViewer);
    for(int i=0;i<4;i++)
    result+=dotColor(dotLight[i],fragToViewer);
    result+=spotColor(spotLight,fragToViewer);
    //输出颜色
    gl_FragColor=vec4(result,1.0f);
}
vec3 directColor(DirectLight dirLight,vec3 fragToViewer)
{
    //环境光
    vec3 ambient=dirLight.ambient*texture(material.diffuseTexture,texPos).rgb;
    //漫射光
    vec3 fragTolight=normalize(-dirLight.lightToFrag);//片段->光
    float diff=max(dot(normal,fragTolight),0.0f);
    vec3 diffuse=diff*dirLight.diffuse*texture(material.diffuseTexture,texPos).rgb;
    //镜面光
    vec3 reflection=reflect(-fragTolight,normal);//因为入射向量和法向量均标准化，故无需标准化
    float spec=pow(max(dot(reflection,fragToViewer),0.0f),material.shininess);
    vec3 specular=spec*dirLight.specular*texture(material.specularTexture,texPos).rgb;
    return (ambient+diffuse+specular);
}
vec3 dotColor(DotLight dotLight,vec3 fragToViewer)
{
    float len=length(dotLight.position-vertexPos);
    float deque=1.0f/(dotLight.constant+dotLight.linear*len+dotLight.quadratic*len*len);
    //环境光
    vec3 ambient=dotLight.ambient*deque*texture(material.diffuseTexture,texPos).rgb;
    //漫射光
    vec3 fragTolight=normalize(dotLight.position-vertexPos);
    float diff=max(dot(normal,fragTolight),0.0f);
    vec3 diffuse=diff*dotLight.diffuse*deque*texture(material.diffuseTexture,texPos).rgb;
    //镜面光
    vec3 reflection=reflect(-fragTolight,normal);//因为入射向量和法向量均标准化，故无需标准化
    float spec=pow(max(dot(reflection,fragToViewer),0.0f),material.shininess);
    vec3 specular=spec*dotLight.specular*deque*texture(material.specularTexture,texPos).rgb;
    return (ambient+diffuse+specular);
}
vec3 spotColor(SpotLight spotLight,vec3 fragToViewer)
{
    float len=length(vertexPos);
    float deque=1.0f/(spotLight.constant+spotLight.linear*len+spotLight.quadratic*len*len);
    //环境光
    vec3 ambient=spotLight.ambient*deque*texture(material.diffuseTexture,texPos).rgb;
    //漫射光
    vec3 fragTolight=normalize(-vertexPos);
    float diff=max(dot(normal,fragTolight),0.0f);
    vec3 diffuse=diff*spotLight.diffuse*deque*texture(material.diffuseTexture,texPos).rgb;
    //镜面光
    vec3 reflection=reflect(-fragTolight,normal);//因为入射向量和法向量均标准化，故无需标准化
    float spec=pow(max(dot(reflection,fragToViewer),0.0f),material.shininess);
    vec3 specular=spec*spotLight.specular*deque*texture(material.specularTexture,texPos).rgb;
    //计算显示范围(可见系数=(片段角的余弦-外光切的余弦)/(内光切的余弦-外光切的余弦),且可见系数范围[0,1])
    float visiable=(dot(-fragTolight,normalize(spotLight.spotFront))-spotLight.outCutOff)/(spotLight.inCutOff-spotLight.outCutOff);
    visiable=clamp(visiable,0.0f,1.0f);
    return (ambient+visiable*(diffuse+specular));
}