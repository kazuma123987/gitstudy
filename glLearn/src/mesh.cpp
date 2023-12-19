#include <mesh.h>
// private
void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoord));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Tangent));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Bitangent));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(5, MAX_BONE_INFLUENCE, GL_INT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, m_BoneIDs));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(6, MAX_BONE_INFLUENCE, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, m_Weights));
	glEnableVertexAttribArray(6);
	glBindVertexArray(0);
}
void Mesh::processArray(float array[], size_t arraySize, unsigned int type)
{
	static unsigned int vertexTypeCount[7] = {3, 3, 2, 3, 3, MAX_BONE_INFLUENCE, MAX_BONE_INFLUENCE};
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
		vertices.emplace_back(vertex);
		indices.emplace_back(i);
	}
}
// public
void Mesh::DestoryMesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	for (unsigned int i = 0; i < textures.size(); i++)
		glDeleteTextures(1, &textures[i].id);
}
void Mesh::Draw(Shader *shader, int instanceCount)
{
	int diffuseIndex = 0;
	int specularIndex = 0;
	int normalIndex = 0;
	int heightIndex = 0;
	int ambientIndex = 0;
	int cubeIndex = 0;
	int index;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		char *name = (char *)calloc(30, sizeof(char));
		if (textures[i].type == "texture_diffuse")
			index = ++diffuseIndex;
		else if (textures[i].type == "texture_specular")
			index = ++specularIndex;
		else if (textures[i].type == "texture_normal")
			index = ++normalIndex;
		else if (textures[i].type == "texture_height")
			index = ++heightIndex;
		else if (textures[i].type == "texture_ambient")
			index = ++ambientIndex;
		else
			index = ++cubeIndex;
		if (textures[i].type != "texture_cube")
		{
			sprintf_s(name, 30, "material.%s%d", textures[i].type.c_str(), index);
			shader->unfm1i(name, i);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			free(name);
		}
		else
		{
			sprintf_s(name, 30, "%s%d", textures[i].type.c_str(), cubeIndex);
			shader->unfm1i(name, i);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textures[i].id);
			free(name);
		}
	}
	glBindVertexArray(VAO);
	if (!instanceCount)
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, instanceCount);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}
unsigned int TextureFromFile(const char *path)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	int width, height, nColorChannels;
	unsigned char *imagedata = stbi_load(path, &width, &height, &nColorChannels, 0);
	if (imagedata)
	{
		GLenum format;
		switch (nColorChannels)
		{
		case 1:
			format = GL_RED;
			break;
		case 2:
			format = GL_RG;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		if (width % 4 == 0)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imagedata);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imagedata);
			glGenerateMipmap(GL_TEXTURE_2D);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}
	}
	else
		printf_s("failed to open the image file:%s", path);
	free(imagedata);
	return textureID;
}
unsigned int TextureFromEmbbeded(const aiTexture *aiTex)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	int width, height, nColorChannels;
	unsigned char *imagedata;
	if (aiTex->mHeight == 0)
		imagedata = stbi_load_from_memory((unsigned char *)aiTex->pcData, aiTex->mWidth, &width, &height, &nColorChannels, 0);
	else
		imagedata = stbi_load_from_memory((unsigned char *)aiTex->pcData, aiTex->mWidth * aiTex->mHeight, &width, &height, &nColorChannels, 0);
	if (imagedata)
	{
		GLenum format;
		switch (nColorChannels)
		{
		case 1:
			format = GL_RED;
			break;
		case 2:
			format = GL_RG;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		}
		if (width % 4 == 0)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imagedata);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imagedata);
			glGenerateMipmap(GL_TEXTURE_2D);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}
	}
	else
		printf_s("failed to load the image from memory");
	free(imagedata);
	return textureID;
}
unsigned int loadCubeTexture(std::vector<std::string> cubePaths)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	int width, height, nColorChannel;
	GLenum format;
	for (unsigned int i = 0; i < cubePaths.size(); i++)
	{
		unsigned char *imageData = stbi_load(cubePaths[i].c_str(), &width, &height, &nColorChannel, 0);
		if (imageData)
		{
			switch (nColorChannel)
			{
			case 1:
				format = GL_RED;
				break;
			case 2:
				format = GL_RG;
				break;
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
				break;
			}
			if (width % 4 == 0)
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
			else
			{
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			}
		}
		else
			fputs("failed to load the cubeImage", stderr);
		stbi_image_free(imageData);
	}
	return textureID;
}