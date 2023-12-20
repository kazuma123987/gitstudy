#version 400 core
in vec2 texCoord;
uniform sampler2D screenTexture;
uniform bool horizontal;
out vec4 FragColor;
void main()
{
    vec2 texSize=1.0f/textureSize(screenTexture,0);
    float weight[5]=float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
    vec3 result=texture(screenTexture,texCoord).rgb*weight[0];
    if(horizontal)
    {
        for(int i=1;i<5;i++)
        {
            result+=texture(screenTexture,texCoord+vec2(texSize.x*i,0.0f)).rgb*weight[i];//正半轴
            result+=texture(screenTexture,texCoord-vec2(texSize.x*i,0.0f)).rgb*weight[i];//负半轴
        }
    }
    else
    {
        for(int i=1;i<5;i++)
        {
            result+=texture(screenTexture,texCoord+vec2(0.0f,texSize.y*i)).rgb*weight[i];//正半轴
            result+=texture(screenTexture,texCoord-vec2(0.0f,texSize.y*i)).rgb*weight[i];//负半轴
        }
    }
    FragColor=vec4(result,1.0f);
}