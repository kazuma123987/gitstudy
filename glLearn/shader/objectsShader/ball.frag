#version 400 core
in vec2 texCoord;
struct Material
{
    sampler2D texture_diffuse1;
    float shininess;
};
uniform Material material;
out vec4 FragColor;
void main()
{
    FragColor=texture(material.texture_diffuse1,texCoord);
}