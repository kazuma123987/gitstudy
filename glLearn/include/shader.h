#ifndef _SHADER_H_
#define _SHADER_H_
#include <tool.h>
//定向光	struct DirectLight{glm::vec3 dir,glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular}
struct DirectLight
{
	glm::vec3 dir;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
//点光源struct DotLight{glm::vec3 pos,glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,float constant,float linear,float quadratic}
struct DotLight
{
	glm::vec3 pos;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
//聚光灯struct SpotLight	{glm::vec3 pos,glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,float constant,float linear,float quadratic,float inCutOff,float outCutOff,glm::vec3 front}
struct SpotLight
{
	glm::vec3 pos;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float inCutOff;
	float outCutOff;
	glm::vec3 front;
};
class Shader {
public:
	Shader(const char* vpath, const char* fpath);
	unsigned int shaderProgram;

	void use();
	void unfm1f(const char* str, float value) const;
	void unfm1i(const char* str, int value) const;
	void unfm3f(const char* str, float a, float b, float c) const;
	void unfvec3fv(const char* str, glm::vec3 vec3)const;
	void unfmat3fv(const char* str, glm::mat3 mat3)const;
	void unfmat4fv(const char* str, glm::mat4 trans) const;
	void unfDirLight(const char* str, DirectLight* dirLight)const;
	void unfDotLight(const char* str, DotLight* dotLight)const;
	void unfSpotLight(const char* str, SpotLight* spotLight)const;
};
#endif