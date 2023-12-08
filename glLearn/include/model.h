#ifndef _MODEL_H_
#define _MODEL_H_
#include <mesh.h>
class Model
{
public:
	std::vector<Mesh> meshes;
	std::vector<Texture> texture_loaded;
	bool gammaCorrection;
	std::string directory;
	Model(const char* path, bool gamma = false) :gammaCorrection(gamma)
	{
		loadModel(path);
	}
	void DestroyModel();
	void Draw(Shader* shader,int instanceCount=0);
private:
	void loadModel(const char* path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTexture(aiMaterial* material, aiTextureType aiType, std::string typeName, const aiScene* scene);
};
#endif // !_MODEL_H_
