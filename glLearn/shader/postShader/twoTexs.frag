#version 400 core
in vec2 texCoord;
uniform sampler2D screenTexture;
layout(location=0)out vec4 FragColor;
layout(location=1)out vec4 lightColor;
void main()
{
    FragColor=texture(screenTexture,texCoord);
    float lighting=dot(FragColor.rgb,vec3(0.2126, 0.7152, 0.0722));
    if(lighting>1.0f)
        lightColor=vec4(FragColor.rgb,1.0f);    
}