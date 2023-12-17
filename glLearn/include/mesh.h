#ifndef _MESH_H_
#define _MESH_H_
#define MAX_BONE_INFLUENCE 4
#include <tool.h>
#include <shader.h>
unsigned int TextureFromFile(const char *path);
unsigned int TextureFromEmbbeded(const aiTexture *aiTex);
unsigned int loadCubeTexture(std::vector<std::string> cubePaths);
enum VertexType
{
	POSITION = 1u,
	NORMAL = 1u << 1,
	TEXCOORD = 1u << 2,
	TANGENT = 1u << 3,
	BITANGENT = 1u << 4,
	M_BONEIDS = 1u << 5,
	M_WEIGHTS = 1u << 6
};
struct Vertex
{
	glm::vec3 Position;					 // 位置
	glm::vec3 Normal;					 // 法向量
	glm::vec2 TexCoord;					 // 纹理坐标
	glm::vec3 Tangent;					 // 切向量
	glm::vec3 Bitangent;				 // 副切向量
	int m_BoneIDs[MAX_BONE_INFLUENCE];	 // 骨骼ID
	float m_Weights[MAX_BONE_INFLUENCE]; // 骨骼权重
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
	Mesh(float array[], size_t arraySize, unsigned int type, const char *diffusePath = NULL, const char *specularPath = NULL, const char *normalPath = NULL)
	{
		unsigned int vertexTypeCount[7] = {3, 3, 2, 3, 3, MAX_BONE_INFLUENCE, MAX_BONE_INFLUENCE};
		int groupCount = 0;
		int offset = 0;
		for (unsigned int i = 0; i < 7; i++)
			groupCount += type & 1u << i ? vertexTypeCount[i] : 0;
		for (unsigned int i = 0; i < (arraySize / 4) / groupCount; i++)
		{
			Vertex vertex;
			if (type & VertexType::POSITION)
			{
				vertex.Position = glm::vec3(array[offset], array[offset + 1], array[offset + 2]);
				offset += 3;
			}
			if (type & VertexType::NORMAL)
			{
				vertex.Normal = glm::vec3(array[offset], array[offset + 1], array[offset + 2]);
				offset += 3;
			}
			if (type & VertexType::TEXCOORD)
			{
				vertex.TexCoord = glm::vec2(array[offset], array[offset + 1]);
				offset += 2;
			}
			if (type & VertexType::TANGENT)
			{
				vertex.Tangent = glm::vec3(array[offset], array[offset + 1], array[offset + 2]);
				offset += 3;
			}
			if (type & VertexType::BITANGENT)
			{
				vertex.Bitangent = glm::vec3(array[offset], array[offset + 1], array[offset + 2]);
				offset += 3;
			}
			if (type & VertexType::M_BONEIDS)
			{
				for (int j = 0; j < MAX_BONE_INFLUENCE; j++)
					vertex.m_BoneIDs[j] = array[offset + j];
				offset += MAX_BONE_INFLUENCE;
			}
			if (type & VertexType::M_WEIGHTS)
			{
				for (int j = 0; j < MAX_BONE_INFLUENCE; j++)
					vertex.m_Weights[j] = array[offset + j];
			}
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
		if (normalPath)
		{
			Texture texture;
			texture.id = TextureFromFile(normalPath);
			texture.type = "texture_normal";
			texture.path = normalPath;
			textures.push_back(texture);
		}
		setupMesh();
	}
	Mesh(float array[], size_t arraySize, std::vector<std::string> cubePaths)
	{
		for (size_t i = 0; i < arraySize / 32; i++)
		{
			Vertex vertex;
			vertex.Position = glm::vec3(array[8 * i], array[1 + 8 * i], array[2 + 8 * i]);
			vertex.Normal = glm::vec3(array[3 + 8 * i], array[4 + 8 * i], array[5 + 8 * i]);
			vertex.TexCoord = glm::vec2(array[6 + 8 * i], array[7 + 8 * i]);
			vertices.push_back(vertex);
			indices.push_back(i);
		}
		Texture texture;
		texture.id = loadCubeTexture(cubePaths);
		texture.type = "texture_cube";
		texture.path = cubePaths[0].substr(0, cubePaths[0].find_last_of('\\'));
		textures.push_back(texture);
		setupMesh();
	}
	void DestoryMesh();
	void Draw(Shader *shader, int instanceCount = 0);
	GLuint getVAO()
	{
		return VAO;
	}

private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};
#endif // !_MESH_H_
