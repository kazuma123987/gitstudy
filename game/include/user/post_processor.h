#ifndef __POST__PROCESSOR__H
#define __POST__PROCESSOR__H
#include "shader.h"
#include "texture.h"
class PostProcessor
{
public:
    Shader shader;
    Texture texture; // FBO的颜色缓冲
    int width, height;
    bool chaos, confuse, shake;
    PostProcessor(Shader &shader, int width, int height);
    ~PostProcessor();
    void BindMFBO();
    void Copy_MFBO_To_FBO();
    void Draw();
private:
    GLuint MFBO, FBO;
    GLuint MRBO; // MFBO的颜色缓冲
    GLuint VAO, VBO;
    GLuint ID;
    void InitData();
};
#endif