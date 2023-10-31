#ifndef _SHADER_H_
#define _SHADER_H_
class Shader{
public:
    Shader(const char *vpath, const char *fpath);
    unsigned int shaderProgram;

    void use();
    void unfm1f(const char *str, float value) const;
    void unfm1i(const char *str, float value) const;
    void unfm3f(const char *str, float a, float b, float c);
};
#endif