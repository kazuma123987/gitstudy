#include <shader.h>
Shader::Shader(const char *vpath, const char *fpath, const char *gpath)
{
	// 顶点着色器
	char *code1 = readCode(vpath);
	GLuint vsh = createShader(&code1, GL_VERTEX_SHADER);
	// 片段着色器
	char *code2 = readCode(fpath);
	GLuint fsh = createShader(&code2, GL_FRAGMENT_SHADER);
	// 几何着色器
	GLuint gsh;
	if (gpath)
	{
		char *code3 = readCode(gpath);
		gsh = createShader(&code3, GL_GEOMETRY_SHADER);
	}
	// 着色器程序
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vsh);
	if(gpath)
		glAttachShader(shaderProgram,gsh);
	glAttachShader(shaderProgram, fsh);
	glLinkProgram(shaderProgram);
	int flag_p = 1;
	char infolog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &flag_p);
	if (!flag_p)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		fputs(infolog, stderr);
	}
	glDeleteShader(vsh);
	if(gpath)
		glDeleteShader(gsh);
	glDeleteShader(fsh);
}

void Shader::use()
{
	glUseProgram(shaderProgram);
}
void Shader::unfm1f(const char *str, float value) const
{
	glUniform1f(glGetUniformLocation(shaderProgram, str), value);
}
void Shader::unfm1i(const char *str, int value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, str), value);
}
void Shader::unfm3f(const char *str, float a, float b, float c) const
{
	glUniform3f(glGetUniformLocation(shaderProgram, str), a, b, c);
}
void Shader::unfmat4fv(const char *str, glm::mat4 trans,int count) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, str),count, GL_FALSE, glm::value_ptr(trans));
}
void Shader::unfvec3fv(const char *str, glm::vec3 vec3,int count) const
{
	glUniform3fv(glGetUniformLocation(shaderProgram, str),count, glm::value_ptr(vec3));
}
void Shader::unfmat3fv(const char *str, glm::mat3 mat3,int count) const
{
	glUniformMatrix3fv(glGetUniformLocation(shaderProgram, str),count, GL_FALSE, glm::value_ptr(mat3));
}
void Shader::unfDirLight(const char *str, DirectLight *dirLight) const
{
	std::string name = str;
	glUniform3fv(glGetUniformLocation(shaderProgram, (name + ".dir").c_str()), 1, glm::value_ptr(dirLight->dir));
	glUniform3fv(glGetUniformLocation(shaderProgram, (name + ".ambient").c_str()), 1, glm::value_ptr(dirLight->ambient));
	glUniform3fv(glGetUniformLocation(shaderProgram, (name + ".diffuse").c_str()), 1, glm::value_ptr(dirLight->diffuse));
	glUniform3fv(glGetUniformLocation(shaderProgram, (name + ".specular").c_str()), 1, glm::value_ptr(dirLight->specular));
}
void Shader::unfDotLight(const char *str, DotLight *dotLight) const
{
	std::string name = str;
	glUniform3fv(glGetUniformLocation(shaderProgram, (name + ".pos").c_str()), 1, glm::value_ptr(dotLight->pos));
	glUniform3fv(glGetUniformLocation(shaderProgram, (name + ".ambient").c_str()), 1, glm::value_ptr(dotLight->ambient));
	glUniform3fv(glGetUniformLocation(shaderProgram, (name + ".diffuse").c_str()), 1, glm::value_ptr(dotLight->diffuse));
	glUniform3fv(glGetUniformLocation(shaderProgram, (name + ".specular").c_str()), 1, glm::value_ptr(dotLight->specular));
	glUniform1f(glGetUniformLocation(shaderProgram, (name + ".constant").c_str()), dotLight->constant);
	glUniform1f(glGetUniformLocation(shaderProgram, (name + ".linear").c_str()), dotLight->linear);
	glUniform1f(glGetUniformLocation(shaderProgram, (name + ".quadratic").c_str()), dotLight->quadratic);
}
void Shader::unfSpotLight(const char *str, SpotLight *spotLight) const
{
	std::string name = str;
	glUniform3fv(glGetUniformLocation(shaderProgram, (name + ".pos").c_str()), 1, glm::value_ptr(spotLight->pos));
	glUniform3fv(glGetUniformLocation(shaderProgram, (name + ".ambient").c_str()), 1, glm::value_ptr(spotLight->ambient));
	glUniform3fv(glGetUniformLocation(shaderProgram, (name + ".diffuse").c_str()), 1, glm::value_ptr(spotLight->diffuse));
	glUniform3fv(glGetUniformLocation(shaderProgram, (name + ".specular").c_str()), 1, glm::value_ptr(spotLight->specular));
	glUniform1f(glGetUniformLocation(shaderProgram, (name + ".constant").c_str()), spotLight->constant);
	glUniform1f(glGetUniformLocation(shaderProgram, (name + ".linear").c_str()), spotLight->linear);
	glUniform1f(glGetUniformLocation(shaderProgram, (name + ".quadratic").c_str()), spotLight->quadratic);
	glUniform1f(glGetUniformLocation(shaderProgram, (name + ".inCutOff").c_str()), spotLight->inCutOff);
	glUniform1f(glGetUniformLocation(shaderProgram, (name + ".outCutOff").c_str()), spotLight->outCutOff);
	glUniform3fv(glGetUniformLocation(shaderProgram, (name + ".front").c_str()), 1, glm::value_ptr(spotLight->front));
}