#ifndef _MESH_H_
#define _MESH_H_
#define MAX_BONE_INFLUENCE 4
#include <tool.h>
#include <shader.h>
unsigned int TextureFromFile(const char* path);
unsigned int TextureFromEmbbeded(const aiTexture* aiTex);
unsigned int loadCubeTexture(std::vector<std::string> cubePaths);
struct Vertex
{
	glm::vec3 Position;//位置
	glm::vec3 Normal;//法向量
	glm::vec2 TexCoord;//纹理坐标
	glm::vec3 Tangent;//切向量
	glm::vec3 Bitangent;//副切向量
	int m_BoneIDs[MAX_BONE_INFLUENCE];//骨骼ID
	float m_Weights[MAX_BONE_INFLUENCE];//骨骼权重
};
struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};
class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		setupMesh();
	}
	Mesh(float array[], int numberCount, const char* diffusePath, const char* specularPath)
	{
		for (int i = 0; i < numberCount / 8; i++)
		{
			Vertex vertex;
			vertex.Position = glm::vec3(array[8 * i], array[1 + 8 * i], array[2 + 8 * i]);
			vertex.Normal = glm::vec3(array[3 + 8 * i], array[4 + 8 * i], array[5 + 8 * i]);
			vertex.TexCoord = glm::vec2(array[6 + 8 * i], array[7 + 8 * i]);
			vertices.push_back(vertex);
			indices.push_back(i);
		}
		if (diffusePath)
		{
			Texture texture;
			texture.id = TextureFromFile(diffusePath);
			texture.type = "texture_diffuse";
			texture.path = diffusePath;
			textures.push_back(texture);
		}
		if (specularPath)
		{
			Texture texture;
			texture.id = TextureFromFile(specularPath);
			texture.type = "texture_specular";
			texture.path = specularPath;
			textures.push_back(texture);
		}
		setupMesh();
	}
	Mesh(float array[], int numberCount, std::vector<std::string> cubePaths)
	{
		for (int i = 0; i < numberCount / 8; i++)
		{
			Vertex vertex;
			vertex.Position = glm::vec3(array[8 * i], array[1 + 8 * i], array[2 + 8 * i]);
			vertex.Normal = glm::vec3(array[3 + 8 * i], array[4 + 8 * i], array[5 + 8 * i]);
			vertex.TexCoord = glm::vec2(array[6 + 8 * i], array[7 + 8 * i]);
			vertices.push_back(vertex);
			indices.push_back(i);
		}
		Texture texture;
		texture.id=loadCubeTexture(cubePaths);
		texture.type="texture_cube";
		texture.path=cubePaths[0].substr(0,cubePaths[0].find_last_of('\\'));
		textures.push_back(texture);
		setupMesh();
	}
	void DestoryMesh();
	void Draw(Shader* shader,int instanceCount=0);
	GLuint getVAO()
	{
		return VAO;
	}
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};
#endif // !_MESH_H_
