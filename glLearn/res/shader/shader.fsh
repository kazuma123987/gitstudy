#version 330 core
in vec3 color;
in vec2 texPos;
out vec4 fragColor;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform sampler2D ourTexture;
uniform float mixVector;
uniform float mix2;
void main()
{
    fragColor=mix(mix(texture(ourTexture1,texPos),texture(ourTexture2,texPos),mixVector),texture(ourTexture,texPos),mix2);
}