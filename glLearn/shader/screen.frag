#version 400 core
in vec2 texCoord;
uniform sampler2D screenTexture;
uniform bool gammaCorrection;
uniform bool HDR_ON;
uniform float exposure;
const float offset = 1.0f / 300.0f;
out vec4 FragColor;
void main(){
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
    //HDR
    if(HDR_ON)
    multiColor=vec3(1.0f)-exp(-multiColor*exposure);
    //伽马校正
    float gammaValue = 2.2f;
    if(gammaCorrection)multiColor=pow(multiColor,vec3(1.0f/gammaValue));
    FragColor=vec4(multiColor,1.0f);
}