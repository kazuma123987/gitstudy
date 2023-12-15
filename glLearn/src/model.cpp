#include <model.h>
void Model::loadModel(const char *path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf_s("ASSIMP::ERROR::%s", importer.GetErrorString());
		return;
	}
	std::string pathName = path;
	directory = pathName.substr(0, pathName.find_last_of('\\') + 1);
	processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode *node, const aiScene *scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene);
}
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	glm::vec3 vec3;
	glm::vec2 vec2;
	// process vertex
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vec3.x = mesh->mVertices[i].x;
		vec3.y = mesh->mVertices[i].y;
		vec3.z = mesh->mVertices[i].z;
		vertex.Position = vec3;
		if (mesh->HasNormals())
		{
			vec3.x = mesh->mNormals[i].x;
			vec3.y = mesh->mNormals[i].y;
			vec3.z = mesh->mNormals[i].z;
			vertex.Normal = vec3;
		}
		if (mesh->mTextureCoords[0])
		{
			vec2.x = mesh->mTextureCoords[0][i].x;
			vec2.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoord = vec2;
		}
		else
			vertex.TexCoord = glm::vec2(0, 0);
		if (mesh->HasTangentsAndBitangents())
		{
			vec3.x = mesh->mTangents[i].x;
			vec3.y = mesh->mTangents[i].y;
			vec3.z = mesh->mTangents[i].z;
			vertex.Tangent = vec3;
			vec3.x = mesh->mBitangents[i].x;
			vec3.y = mesh->mBitangents[i].y;
			vec3.z = mesh->mBitangents[i].z;
			vertex.Bitangent = vec3;
		}
		vertices.push_back(vertex);
	}
	// process index
	if (mesh->HasFaces())
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
	// process texture(material)
	aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
	// 漫射贴图
	std::vector<Texture> diffuseTexture = loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);
	textures.insert(textures.end(), diffuseTexture.begin(), diffuseTexture.end());
	// 镜面贴图
	std::vector<Texture> specularTexture = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular", scene);
	textures.insert(textures.end(), specularTexture.begin(), specularTexture.end());
	// 法线贴图
	std::vector<Texture> normalTexture = loadMaterialTexture(material, aiTextureType_NORMALS, "texture_normal", scene);
	textures.insert(textures.end(), normalTexture.begin(), normalTexture.end());
	// 高度贴图
	std::vector<Texture> heightTexture = loadMaterialTexture(material, aiTextureType_HEIGHT, "texture_height", scene);
	textures.insert(textures.end(), heightTexture.begin(), heightTexture.end());
	// 反射贴图
	std::vector<Texture> ambientTexture = loadMaterialTexture(material, aiTextureType_AMBIENT, "texture_ambient", scene);
	textures.insert(textures.end(), ambientTexture.begin(), ambientTexture.end());
	return Mesh(vertices, indices, textures);
}
std::vector<Texture> Model::loadMaterialTexture(aiMaterial *material, aiTextureType aiType, std::string typeName, const aiScene *scene)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < material->GetTextureCount(aiType); i++)
	{
		aiString aiStr;
		material->GetTexture(aiType, i, &aiStr);
		bool isQuit = false;
		for (unsigned int j = 0; j < texture_loaded.size(); j++)
		{
			if (strcmp(texture_loaded[j].path.c_str(), aiStr.C_Str()) == 0)
			{
				textures.push_back(texture_loaded[j]);
				isQuit = true;
				break;
			}
		}
		if (!isQuit)
		{
			Texture texture;
			const aiTexture *aiTex = scene->GetEmbeddedTexture(aiStr.C_Str());
			if (aiTex)
				texture.id = TextureFromEmbbeded(aiTex);
			else
				texture.id = TextureFromFile((directory + aiStr.C_Str()).c_str());
			texture.type = typeName;
			texture.path = aiStr.C_Str();
			textures.push_back(texture);
			texture_loaded.push_back(texture);
		}
	}
	return textures;
}
void Model::DestroyModel()
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].DestoryMesh();
}
void Model::Draw(Shader *shader, int instanceCount)
{
	if (!instanceCount)
		for (unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader);
	else
		for (unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader, instanceCount);
}