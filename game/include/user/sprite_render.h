#ifndef __SPRITE__RENDER__H
#define __SPRITE__RENDER__H
#include "shader.h"
#include "texture.h"
class SpriteRender
{
public:
    SpriteRender(Shader &shader);
    ~SpriteRender();
    void DrawSprite(Texture &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), 
    float rotate = 0.0f, glm::vec3 spriteColor = glm::vec3(1.0f),float darker=1.0f);

private:
    Shader shader;
    GLuint quadVAO,quadVBO;
    void initRender();
};
#endif