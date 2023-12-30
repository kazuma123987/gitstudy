#ifndef __GAME__OBJECT__H
#define __GAME__OBJECT__H
#include "texture.h"
#include "shader.h"
#include "sprite_render.h"
class GameObject
{
public:
    // 物体状态
    glm::vec2 position, size, velocity;
    glm::vec3 color;
    float rotation;
    bool isSolid;
    bool destoryed;
    //渲染状态
    Texture image;
    //构造函数
    GameObject();
    GameObject(glm::vec2 pos,glm::vec2 size,Texture &image,glm::vec3 color=glm::vec3(1.0f),glm::vec2 velocity=glm::vec2(0.0f));
    ~GameObject(){};
    //渲染函数
    virtual void Draw(SpriteRender &renderer);
};
#endif