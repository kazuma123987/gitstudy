#version 400 core
layout(triangles)in;
layout(triangle_strip,max_vertices=18)out;
uniform mat4 shadowCubeMat[6];//世界坐标转裁切空间
out vec4 fragPos;
void main()
{
    for(int face=0;face<6;face++)
    {
        gl_Layer=face;
        for(int i=0;i<3;i++)
        {
            fragPos=gl_in[i].gl_Position;
            gl_Position=shadowCubeMat[face]*fragPos;
            EmitVertex();
        }
        EndPrimitive();
    }    
}