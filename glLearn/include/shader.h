#ifndef _SHADER_H_
#define _SHADER_H_
#include <tool.h>
// 定向光	struct DirectLight{glm::vec3 dir,glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular}
struct DirectLight
{
	glm::vec3 dir;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
// 点光源struct DotLight{glm::vec3 pos,glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,float constant,float linear,float quadratic}
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
// 聚光灯struct SpotLight	{glm::vec3 pos,glm::vec3 ambient,glm::vec3 diffuse,glm::vec3 specular,float constant,float linear,float quadratic,float inCutOff,float outCutOff,glm::vec3 front}
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
class Shader
{
public:
	Shader(const char *vpath, const char *fpath, const char *gpath = NULL);
	unsigned int shaderProgram;

	void use();
	void unfm1f(const char *str, float value) const;
	void unfm1i(const char *str, int value) const;
	void unfm3f(const char *str, float a, float b, float c) const;
	void unfvec3fv(const char *str, glm::vec3 vec3,int count=1) const;
	void unfmat3fv(const char *str, glm::mat3 mat3,int count=1) const;
	void unfmat4fv(const char *str, glm::mat4 trans,int count=1) const;
	void unfDirLight(const char *str, DirectLight *dirLight) const;
	void unfDotLight(const char *str, DotLight *dotLight) const;
	void unfSpotLight(const char *str, SpotLight *spotLight) const;

private:
	//读取文件的字符串(记住要free掉)
	char *readCode(const char *path)
	{
		FILE *fp = NULL;
		fopen_s(&fp, path, "rb");
		if (!fp)
			printf_s("\nfailed to open the path : %s",path);
		fseek(fp, 0, SEEK_END);
		size_t size = ftell(fp);
		rewind(fp);
		char *code = (char *)malloc(size + 1);
		size_t readSize = fread(code, sizeof(char), size, fp);
		if (readSize < size)
			fputs("\nfailed to read the file", stderr);
		code[size] = '\0';
		fclose(fp);
		return code;
	}
	GLuint createShader(char **code,GLenum shaderType)
	{
		GLuint shader=glCreateShader(shaderType);
		glShaderSource(shader,1,code,NULL);
		glCompileShader(shader);
		int flag=1;
		char infoLog[512];
		glGetShaderiv(shader,GL_COMPILE_STATUS,&flag);
		if(!flag)
		{
			glGetShaderInfoLog(shader,512,NULL,infoLog);
			fputs(infoLog,stderr);
		}
		free(*code);
		return shader;
	}
};
#endif