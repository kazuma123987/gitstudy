#version 400 core
in vec2 texCoord;
uniform sampler2D textImage;
uniform vec3 textColor;
out vec4 FragColor;
void main()
{
    float alpha=texture(textImage,texCoord).r;
    float shadow=texture(textImage,texCoord+vec2(-0.1f)).r;
    alpha=smoothstep(0.5f-0.05f,0.5f+0.05f,alpha);
    FragColor=vec4(textColor,alpha);
    if(FragColor.a==0.0f)FragColor=vec4(vec3(0.0f),shadow);
}