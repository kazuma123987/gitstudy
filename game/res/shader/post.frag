#version 400 core
in vec2 texCoord;
uniform sampler2D image;
uniform vec2 offsets[9];
uniform int edge_kernel[9];
uniform float blur_kernel[9];
uniform bool chaos;
uniform bool confuse;
uniform bool shake;
out vec4 FragColor;
void main()
{
    //采样
    FragColor=vec4(0.0f,0.0f,0.0f,1.0f);
    vec3 sampleColor[9];
    if(chaos||shake)
    {
        for(int i=0;i<9;i++)
            sampleColor[i]=texture(image,texCoord+offsets[i]).rgb;
    }
    //处理特效
    if(chaos)
    {
        for(int i=0;i<9;i++)
            FragColor+=vec4(sampleColor[i]*edge_kernel[i],0.0f);
    }
    else if(confuse)
    {
        FragColor=vec4(1.0f-texture(image,texCoord).rgb,1.0f);
    }
    else if(shake)
    {
        for(int i=0;i<9;i++)
            FragColor+=vec4(sampleColor[i]*blur_kernel[i],0.0f);
    }
    else
        FragColor=texture(image,texCoord);
}