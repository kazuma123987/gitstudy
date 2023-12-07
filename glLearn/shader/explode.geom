#version 400 core
layout(triangles) in;
layout(triangle_strip,max_vertices=3) out;
in VS_OUT
{
vec3 fragPos;
vec3 normal;
vec2 texPos;
}gs_in[];
//declare
void drawVertex(int index,vec3 norm);
vec3 getNormal();
vec4 explode(vec4 position,vec3 normal);
//uniform
uniform float time;
out vec3 fragPos;
out vec3 normal;
out vec2 texPos;
void main()
{
    vec3 norm=getNormal();
    drawVertex(0,norm);
    drawVertex(1,norm);
    drawVertex(2,norm);
    EndPrimitive();        
}
void drawVertex(int index,vec3 norm)
{
    gl_Position=explode(gl_in[index].gl_Position,norm);
    fragPos=gs_in[index].fragPos;
    normal=gs_in[index].normal;
    texPos=gs_in[index].texPos;
    EmitVertex();
}
vec3 getNormal()
{
    vec3 a=vec3(gl_in[0].gl_Position-gl_in[1].gl_Position);
    vec3 b=vec3(gl_in[2].gl_Position-gl_in[1].gl_Position);
    return normalize(cross(a,b));
}
vec4 explode(vec4 position,vec3 normal)
{
    const float magnitude=2.0f;
    vec3 direction=magnitude*time*normal;
    return position+vec4(direction,0.0f);
}