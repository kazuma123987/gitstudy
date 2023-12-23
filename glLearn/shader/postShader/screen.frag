#version 400 core
in vec2 texCoord;
uniform sampler2D screenTexture;
uniform sampler2D bloomTexture;
uniform bool gammaCorrection;
uniform bool HDR_ON;
uniform float exposure;
vec3 kernelColor();
out vec4 FragColor;
void main(){
    vec3 result=vec3(0.0f);
    result+=kernelColor();
    result+=texture(bloomTexture,texCoord).rgb;
    //HDR
    if(HDR_ON)
    result=vec3(1.0f)-exp(-result*exposure);
    //伽马校正
    float gammaValue = 2.2f;
    if(gammaCorrection)result=pow(result,vec3(1.0f/gammaValue));
    FragColor=vec4(result,1.0f);
}
vec3 kernelColor()
{
    const float offset = 1.0f / 300.0f;
    vec2 offsets[9]=vec2[]
    (
        vec2(-offset,offset), //左上
        vec2(0.0f,offset),    //上
        vec2(offset,offset),  //右上
        vec2(-offset,0.0f),   //左
        vec2(0.0f,0.0f),      //中
        vec2(offset,0.0f),   //右
        vec2(-offset,-offset),//左下
        vec2(0.0f,-offset),   //下
        vec2(offset,-offset)  //右下
    );
    float kernel[9]=float[]//影响周围像素混合的权重数组,称之为核(也叫卷积矩阵,但本身是数组),其所有权重相加应等于1,小于1变暗，大于1变亮
    (
        0,0,0,
        0,1,0,
        0,0,0
    );
    vec3 sampleColor[9];//样本颜色
    for(int i=0;i<9;i++)
        sampleColor[i]=vec3(texture(screenTexture,texCoord.st+offsets[i]));//记录了当前纹理朝9个方向移动的颜色
    vec3 multiColor=vec3(0.0f);//混合颜色
    for(int i=0;i<9;i++)
        multiColor+=sampleColor[i]*kernel[i];
    return multiColor;
}