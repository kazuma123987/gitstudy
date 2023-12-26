#version 400 core
in vec2 texCoord;
uniform vec3 textColor;
uniform vec3 outlineColor;
uniform vec3 shadowColor=vec3(0.0f);
uniform sampler2D bitmap;
uniform float thickness;
uniform float softness;
uniform float outline_thickness;
uniform float outline_softness;
uniform float shadow_thickness=0.5f;
uniform float shadow_softness=0.1f;
out vec4 FragColor;
void main()
{
    //SDF以0.5为边界
    float alpha=texture(bitmap,texCoord).r;
    //outline宽度0.5f: <0.5f:outlineColor >0.5f:texColor
    float outline=smoothstep(outline_thickness-outline_softness,outline_thickness+outline_softness,alpha);
    float shadow=texture(bitmap,texCoord-0.1f).r;
    shadow=smoothstep(shadow_thickness-shadow_softness,shadow_thickness+shadow_softness,shadow);
    alpha=smoothstep(thickness-softness,thickness+softness,alpha);
    FragColor=vec4(mix(outlineColor,textColor,outline),alpha);
    if(alpha==0)FragColor=vec4(shadowColor,shadow);
    // //梯度渐变
    // float alpha=texture(bitmap,texCoord).r;
    // float edge=0.5f;
    // vec3 edgeColor = vec3(1.0);
    // if(alpha < 0.5)
    //     discard;
    // FragColor = vec4(mix(edgeColor,textColor,texCoord.y), 1.0);//opengl以左上角为原点
}