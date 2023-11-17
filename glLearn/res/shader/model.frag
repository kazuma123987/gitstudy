#version 330 core
in vec2 texPos;
in vec3 vertexPos;//未标准化(观察空间)
in vec3 lightPos;//未标准化(观察空间)
in vec3 normal;//已标准化的法向量坐标(观察空间)
uniform sampler2D ourTexture[6];//纹理
uniform int texIndex;//纹理索引
uniform vec3 lightColor;//光源颜色
out vec4 fragColor;
void main()
{
    //环境光
    float ambientIntensity=0.1f;
    vec3 ambient=ambientIntensity*lightColor;
    //漫射光
    float diffIntensity=1.0f;
    vec3 VertexToLight=normalize(lightPos-vertexPos);//顶点到光源矢量
    float diff=max(dot(normal,VertexToLight),0.0f);
    vec3 diffuse=diff*diffIntensity*lightColor;
    //镜面光
    float specIntensity=0.5f;
    vec3 reflection=reflect(-VertexToLight,normal);//因为入射向量和法向量均标准化，故无需标准化
    vec3 VertexToViewer=-normalize(vertexPos);
    float spec=pow(max(dot(reflection,VertexToViewer),0.0f),32);
    vec3 specular=specIntensity*spec*lightColor;
    //输出颜色
    fragColor=texture(ourTexture[texIndex],texPos)*vec4(ambient+diffuse+specular,1.0f);
}