#ifndef _SHADER_H_
#define _SHADER_H_
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
};
#endif