#version 400 core
in vec4 fragPos;
uniform vec3 lightPos;
uniform float far_plane;
void main()
{
    gl_FragDepth=length(lightPos-fragPos.xyz)/far_plane;
}