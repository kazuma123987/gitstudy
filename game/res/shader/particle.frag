#version 400 core
in vec2 texCoord;
uniform sampler2D image;
uniform vec4 parColor;
out vec4 FragColor;
void main()
{
    FragColor=parColor*texture(image,texCoord);
}