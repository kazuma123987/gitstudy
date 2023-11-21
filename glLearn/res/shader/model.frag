#version 400 core
struct Material{
    sampler2D diffuseTexture;//材质的漫射光反射贴图
    sampler2D specularTexture;//材质的镜面光反射贴图
    float shininess;//材质的反光度
};
struct Light{
    vec3 position;//光源位置(观察空间)
    vec3 ambient;//环境光颜色
    vec3 diffuse;//漫射光颜色
    vec3 specular;//镜面光颜色
};//光源=环境光+漫射光+镜面光,故有三部分颜色
in vec2 texPos;
in vec3 vertexPos;//未标准化(观察空间)
in vec3 normal;//已标准化的法向量坐标(观察空间)
uniform Material material;//材质属性
uniform sampler2D emission;//放射光材质
uniform float yOffset;
uniform float mixVector;
uniform Light light;//光源属性
out vec4 fragColor;
void main()
{
    //环境光
    vec3 ambient=light.ambient*texture(material.diffuseTexture,texPos).rgb;
    //漫射光
    vec3 VertexToLight=normalize(light.position-vertexPos);//顶点到光源矢量(注意不要先标准化,否则相减的矢量方向不正确)
    float diff=max(dot(normal,VertexToLight),0.0f);
    vec3 diffuse=diff*light.diffuse*texture(material.diffuseTexture,texPos).rgb;
    //镜面光
    vec3 reflection=reflect(-VertexToLight,normal);//因为入射向量和法向量均标准化，故无需标准化
    vec3 VertexToViewer=-normalize(vertexPos);
    float spec=pow(max(dot(reflection,VertexToViewer),0.0f),material.shininess);
    vec3 specular=spec*light.specular*texture(material.specularTexture,texPos).rgb;
    //放射光
    vec3 Emission=mixVector*texture(emission,texPos+vec2(0.0f,yOffset)).rgb;
    //输出颜色
    fragColor=vec4(ambient+diffuse+specular+Emission,1.0f);
}