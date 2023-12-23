#version 400 core
out vec4 FragColor;
void main(){
    if(mod(gl_FragCoord.x+gl_FragCoord.y,10.0f)>5.0f)
    discard;
    FragColor=vec4(0.6f,0.6f,0.6f,1.0f);   
}