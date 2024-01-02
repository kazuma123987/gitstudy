#ifndef __LIVES__H
#define __LIVES__H
#include "sprite_render.h"

class Lives
{
public:
    glm::vec2 boxPos,boxSize;
    glm::vec2 heartPos,heartSize;
    int lifePointMax;
    int curLifePoint;
    int distance;
    Lives(int width,int height,int lifePointMax,int distance);
    ~Lives();
    void Draw(SpriteRender &renderer);

private:
    Texture heart;
    Texture heartBox;
};
#endif