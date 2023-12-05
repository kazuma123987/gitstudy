#include "global.h"
char filePath[260];
FMODSOUND* s1;
FMODSOUND* s2;
FMODMUSIC music;
Camera* camera;
// 顶点数组
// 顶点数组
float arr_vertex[] =
{
	//位置(3)法向量(3)纹理(2)
    // Front face
    -0.5f, -0.5f,  0.5f, 0.0f,0.0f,1.0f, 0.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f, 0.0f,0.0f,1.0f, 1.0f, 0.0f, // bottom-right
     0.5f,  0.5f,  0.5f, 0.0f,0.0f,1.0f, 1.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f, 0.0f,0.0f,1.0f, 1.0f, 1.0f, // top-right
    -0.5f,  0.5f,  0.5f, 0.0f,0.0f,1.0f, 0.0f, 1.0f, // top-left
    -0.5f, -0.5f,  0.5f, 0.0f,0.0f,1.0f, 0.0f, 0.0f, // bottom-left
    // Back face
    -0.5f, -0.5f, -0.5f, 0.0f,0.0f,-1.0f, 0.0f, 0.0f, // Bottom-left
     0.5f,  0.5f, -0.5f, 0.0f,0.0f,-1.0f, 1.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f, 0.0f,0.0f,-1.0f, 1.0f, 0.0f, // bottom-right         
     0.5f,  0.5f, -0.5f, 0.0f,0.0f,-1.0f, 1.0f, 1.0f, // top-right
    -0.5f, -0.5f, -0.5f, 0.0f,0.0f,-1.0f, 0.0f, 0.0f, // bottom-left
    -0.5f,  0.5f, -0.5f, 0.0f,0.0f,-1.0f, 0.0f, 1.0f, // top-left
    // Left face
    -0.5f,  0.5f,  0.5f, -1.0f,0.0f,0.0f, 1.0f, 0.0f, // top-right
    -0.5f,  0.5f, -0.5f, -1.0f,0.0f,0.0f, 1.0f, 1.0f, // top-left
    -0.5f, -0.5f, -0.5f, -1.0f,0.0f,0.0f, 0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f, -0.5f, -1.0f,0.0f,0.0f, 0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f,  0.5f, -1.0f,0.0f,0.0f, 0.0f, 0.0f, // bottom-right
    -0.5f,  0.5f,  0.5f, -1.0f,0.0f,0.0f, 1.0f, 0.0f, // top-right
    // Right face
     0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f, 1.0f, 0.0f, // top-left
     0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f, 1.0f, // bottom-right
     0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f, 1.0f, 1.0f, // top-right         
     0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f, 1.0f, // bottom-right
     0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f, 1.0f, 0.0f, // top-left
     0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f, 0.0f, 0.0f, // bottom-left     
    // Bottom face
    -0.5f, -0.5f, -0.5f, 0.0f,-1.0f,0.0f, 0.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f, 0.0f,-1.0f,0.0f, 1.0f, 1.0f, // top-left
     0.5f, -0.5f,  0.5f, 0.0f,-1.0f,0.0f, 1.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f, 0.0f,-1.0f,0.0f, 1.0f, 0.0f, // bottom-left
    -0.5f, -0.5f,  0.5f, 0.0f,-1.0f,0.0f, 0.0f, 0.0f, // bottom-right
    -0.5f, -0.5f, -0.5f, 0.0f,-1.0f,0.0f, 0.0f, 1.0f, // top-right
    // Top face
    -0.5f,  0.5f, -0.5f, 0.0f,1.0f,0.0f, 0.0f, 1.0f, // top-left
     0.5f,  0.5f,  0.5f, 0.0f,1.0f,0.0f, 1.0f, 0.0f, // bottom-right
     0.5f,  0.5f, -0.5f, 0.0f,1.0f,0.0f, 1.0f, 1.0f, // top-right     
     0.5f,  0.5f,  0.5f, 0.0f,1.0f,0.0f, 1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f, -0.5f, 0.0f,1.0f,0.0f, 0.0f, 1.0f, // top-left
    -0.5f,  0.5f,  0.5f, 0.0f,1.0f,0.0f, 0.0f, 0.0f  // bottom-left
};
float arr_floor[] =
{
	//floor
	-1000.0f, -2.0f, -1000.0f, 0.0f, 1.0f, 0.0f,0.0f, 0.0f,
	1000.0f, -2.0f, -1000.0f, 0.0f, 1.0f, 0.0f,2000.0f, 0.0f,
	1000.0f, -2.0f, 1000.0f, 0.0f, 1.0f, 0.0f,2000.0f, 2000.0f,
	1000.0f, -2.0f, 1000.0f, 0.0f, 1.0f, 0.0f,2000.0f, 2000.0f,
	-1000.0f, -2.0f, 1000.0f, 0.0f, 1.0f, 0.0f,0.0f, 2000.0f,
	-1000.0f, -2.0f, -1000.0f, 0.0f, 1.0f, 0.0f,0.0f, 0.0f
};
size_t arrVertex_N = sizeof(arr_vertex);
size_t arrFloor_N = sizeof(arr_floor);
//模型位置偏移数组
glm::vec3 offsetModel[10] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f, 5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f, 3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f, 2.0f, -2.5f),
	glm::vec3(1.5f, 0.2f, -1.5f),
	glm::vec3(-1.3f, 1.0f, -1.5f)
};
std::vector<std::string> cubePaths=
{
    "res\\texture\\skybox\\px.jpg",
    "res\\texture\\skybox\\nx.jpg",
    "res\\texture\\skybox\\py.jpg",
    "res\\texture\\skybox\\ny.jpg",
    "res\\texture\\skybox\\pz.jpg",
    "res\\texture\\skybox\\nz.jpg",
};