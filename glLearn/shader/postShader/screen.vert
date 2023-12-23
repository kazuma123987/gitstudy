#version 400 core
layout(location=0)in vec3 aPos;
layout(location=1)in vec2 aTexCoord;
out vec2 texCoord;
void main(){
    gl_Position=vec4(aPos.xy,0.0f,1.0f);//因为我们的顶点的横纵坐标是(-0.5f,0.5f),放大两倍后刚好占满标准空间的屏幕
    texCoord=aTexCoord;   
}