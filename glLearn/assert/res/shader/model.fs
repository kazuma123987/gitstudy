#version 330 core
in vec2 texPos;
in vec3 Normal;
in vec3 FragPos;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float mixVector;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
void main()
{
    float ambientVector=0.05f;//环境光强度
    vec3 ambient=ambientVector*lightColor;//环境光颜色
    vec3 norm=normalize(Normal);//法向量标准化
    vec3 fragVec=normalize(lightPos-FragPos);//顶点到光源的方向向量标准化
    float diffVector=max(dot(norm,fragVec),0.0f);//两个单位矢量的乘积就是夹角的余弦(cos(θ)),同时乘积不能为负数
    vec3 diffuse=diffVector*lightColor;//漫射光颜色
    float specVector=0.5f;//镜面光强度
    vec3 refVec=reflect(-fragVec,norm);    //光的反射矢量
    vec3 viewVec=normalize(viewPos-FragPos);//观察矢量
    float spec=pow(max(dot(refVec,viewVec),0.0f),32);//对观察矢量与反射矢量夹角的余弦求32次方,32代表反光度
    vec3 specular=specVector*spec*lightColor;
    gl_FragColor=mix(texture(ourTexture2,texPos),texture(ourTexture1,texPos),mixVector)*vec4(ambient+diffuse+specular,1.0f);//漫射光与环境光与镜面光混合
}