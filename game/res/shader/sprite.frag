#version 400 core
in vec2 texCoord;
uniform sampler2D image;
uniform vec3 spriteColor;
out vec4 FragColor;
void main()
{
    FragColor=vec4(spriteColor,1.0f)*texture(image,texCoord);
}