#version 400 core
in vec3 texCoord;
uniform samplerCube texture_cube1;
out vec4 FragColor;
void main(){
    FragColor=texture(texture_cube1,texCoord);
}