#version 400 core
layout(location=0)in vec3 aPos;
uniform mat4 shadowSpaceMat;
uniform mat4 model;
void main(){
    gl_Position=shadowSpaceMat*model*vec4(aPos,1.0f);   
}