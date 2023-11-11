#ifndef _SHADER_H_
#define _SHADER_H_
#include "tool.h"
//当类里面的函数不是声明，而是实现时，则会被隐式的当作内联(inline)函数
//内联函数必须写在头文件中,如果类的内部只进行了函数的声明,若要使其内联则一定要把实现写在头文件
class Shader{
public:
    Shader(const char *vpath, const char *fpath);
    unsigned int shaderProgram;

    void use();
    void unfm1f(const char *str, float value) const;
    void unfm1i(const char *str, float value) const;
    void unfm3f(const char *str, float a, float b, float c);
    void unfvec3f(const char *str,glm::vec3 vec);
    void unfmat3fv(const char *str,glm::mat3 matrix);
    void unfmat4fv(const char *str,glm::mat4 matrix);
};
#endif