#version 330 core
layout (location=0) in vec3 aPos;//顶点坐标
layout (location=1) in vec2 texPos_in;//纹理坐标
layout (location=2) in vec3 aNormal;//法向量
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat3 normMat;//法向量矩阵
out vec2 texPos;
out vec3 Normal;
out vec3 FragPos;
void main()
{
    gl_Position = proj*view*model*vec4(aPos,1.0f);
    FragPos=vec3(model*vec4(aPos,1.0f));
    texPos=texPos_in;
    Normal=normMat*aNormal;//法向量坐标转世界坐标(如果物体发生旋转和不对称缩放则每个面法向量方向会改变)
}