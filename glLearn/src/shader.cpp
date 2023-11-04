#include "tool.h"
#include "shader.h"
Shader::Shader(const char *vpath, const char *fpath)
{
    // 文件操作
    FILE *fp1 = fopen(vpath, "rb");
    if (!fp1)
        fputs("\nfailed to open the path of vertexShader", stderr);
    FILE *fp2 = fopen(fpath, "rb");
    if (!fp1)
        fputs("\nfailed to open the path of fragmentShader", stderr);
    fseek(fp1, 0, SEEK_END);
    long size1 = ftell(fp1);
    fseek(fp2, 0, SEEK_END);
    long size2 = ftell(fp2);
    char *code1 = (char *)malloc(size1 + 1);
    char *code2 = (char *)malloc(size2 + 1);
    rewind(fp1);
    rewind(fp2);
    size_t readSize1 = fread(code1, sizeof(char), size1, fp1);
    if (readSize1 < size1)
        fputs("\nfailed to read the file", stderr);
    code1[size1] = '\0';
    size_t readSize2 = fread(code2, sizeof(char), size2, fp2);
    if (readSize2 < size2)
        fputs("\nfailed to read the file", stderr);
    code2[size2] = '\0';
    fclose(fp1);
    fclose(fp2);
    // 顶点着色器
    GLuint vsh = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsh, 1, &code1, NULL);
    glCompileShader(vsh);
    int flag_v = 1;
    char infolog[512];
    glGetShaderiv(vsh, GL_COMPILE_STATUS, &flag_v);
    if (!flag_v)
    {
        glGetShaderInfoLog(vsh, 512, NULL, infolog);
        fputs(infolog, stderr);
    }
    free(code1);
    // 片段着色器
    GLuint fsh = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fsh, 1, &code2, NULL);
    glCompileShader(fsh);
    int flag_f = 1;
    glGetShaderiv(fsh, GL_COMPILE_STATUS, &flag_f);
    if (!flag_f)
    {
        glGetShaderInfoLog(fsh, 512, NULL, infolog);
        fputs(infolog, stderr);
    }
    free(code2);
    // 着色器程序
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vsh);
    glAttachShader(shaderProgram, fsh);
    glLinkProgram(shaderProgram);
    int flag_p = 1;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &flag_p);
    if (!flag_p)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        fputs(infolog, stderr);
    }
    glDeleteShader(vsh);
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
void Shader::unfm1i(const char *str, float value) const
{
    glUniform1i(glGetUniformLocation(shaderProgram, str), value);
}
void Shader::unfm3f(const char *str, float a, float b, float c)
{
    glUniform3f(glGetUniformLocation(shaderProgram, str), a, b, c);
}
void Shader::unfmat4fv(const char *str,glm::mat4 matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram,str),1,GL_FALSE,glm::value_ptr(matrix));
}