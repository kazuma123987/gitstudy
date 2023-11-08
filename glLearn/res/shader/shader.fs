#version 330 core
in vec2 texPos;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float mixVector;
void main()
{
    gl_FragColor=mix(texture(ourTexture1,texPos),texture(ourTexture2,texPos),mixVector);
}