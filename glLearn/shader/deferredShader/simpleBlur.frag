#version 400 core
in vec2 texCoord;
uniform sampler2D ssaoTexture;
out vec4 FragColor;
void main()
{
    vec2 texSize=1.0f/textureSize(ssaoTexture,0);
    float result=0.0f;
    for(int i=-2;i<=2;i++)
        for(int j=-2;j<=2;j++)
        {
            vec2 offset=vec2(float(i),float(j))*texSize;
            result+=texture(ssaoTexture,texCoord+offset).r;
        }
    result/=25.0f;
    FragColor=vec4(vec3(result),1.0f);
}