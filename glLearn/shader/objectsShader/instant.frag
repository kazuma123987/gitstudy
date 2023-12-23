#version 400 core
in vec2 texCoords;
struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_specular1;
    float shininess;
};
uniform Material material;
void main()
{
    gl_FragColor=texture(material.texture_diffuse1,texCoords)+texture(material.texture_diffuse2,texCoords);    
}