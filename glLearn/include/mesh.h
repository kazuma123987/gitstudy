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
	Mesh(float array[], size_t arraySize, unsigned int type, const char *diffusePath = NULL,
		 const char *specularPath = NULL, const char *normalPath = NULL, const char *heightPath = NULL)
	{
		processArray(array, arraySize, type);
		if (diffusePath)
		{
			Texture texture;
			texture.id = TextureFromFile(diffusePath);
			texture.type = "texture_diffuse";
			texture.path = diffusePath;
			textures.emplace_back(texture);
		}
		if (specularPath)
		{
			Texture texture;
			texture.id = TextureFromFile(specularPath);
			texture.type = "texture_specular";
			texture.path = specularPath;
			textures.emplace_back(texture);
		}
		if (normalPath)
		{
			Texture texture;
			texture.id = TextureFromFile(normalPath);
			texture.type = "texture_normal";
			texture.path = normalPath;
			textures.emplace_back(texture);
		}
		if (heightPath)
		{
			Texture texture;
			texture.id = TextureFromFile(heightPath);
			texture.type = "texture_height";
			texture.path = heightPath;
			textures.emplace_back(texture);
		}
		setupMesh();
	}
	Mesh(float array[], size_t arraySize, unsigned int type, std::vector<std::string> cubePaths)
	{
		processArray(array, arraySize, type);
		Texture texture;
		stbi_set_flip_vertically_on_load(false);//天空盒按照方向向量取值时yz轴是反的
		texture.id = loadCubeTexture(cubePaths);
		stbi_set_flip_vertically_on_load(true);
		texture.type = "texture_cube";
		texture.path = cubePaths[0].substr(0, cubePaths[0].find_last_of('\\'));
		textures.emplace_back(texture);
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
	void processArray(float array[], size_t arraySize, unsigned int type);
};
#endif // !_MESH_H_
