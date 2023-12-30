#version 400 core
layout(location=0)in vec4 aPos;
uniform bool chaos;
uniform bool confuse;
uniform bool shake;
uniform float time;
out vec2 texCoord;
void main()
{
    texCoord=aPos.zw;
    gl_Position=vec4(aPos.xy,0.0f,1.0f);
    if(chaos)
        texCoord=texCoord+vec2(sin(time),cos(time))*0.3f;
    else if(confuse)
        texCoord=1.0f-texCoord;
    if(shake)
        gl_Position.xy+=vec2(cos(10*time),cos(15*time))*0.01f;
}