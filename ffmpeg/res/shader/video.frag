#version 400 core
in vec2 texCoord;
uniform sampler2D image_Y;
uniform sampler2D image_U;
uniform sampler2D image_V;
out vec4 FragColor;
void main()
{
    vec3 yuv;
    yuv.r=texture(image_Y,texCoord).r;
    yuv.g=texture(image_U,texCoord).r-0.5f;
    yuv.b=texture(image_V,texCoord).r-0.5f;
    vec3 rgb=mat3(vec3(1,1,1),vec3(0,-0.395,2.032),vec3(1.140,-0.581,0))*yuv;
    FragColor=vec4(rgb,1.0f);
}