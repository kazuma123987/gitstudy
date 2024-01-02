#include "lives.h"
#include "resource_manager.h"
const glm::vec2 BOX_SIZE = glm::vec2(64, 64);
const glm::vec2 HEART_SIZE = glm::vec2(37, 37);
Lives::Lives(int width, int height, int lifePointMax, int distance)
{
    this->heart = ResourceManager::getTexture("heart_fill");
    this->heartBox = ResourceManager::getTexture("heart_box");
    this->curLifePoint=this->lifePointMax = lifePointMax;
    this->boxPos = glm::vec2(0.0f, height - BOX_SIZE.y);
    this->boxSize = BOX_SIZE;
    this->heartPos = glm::vec2(BOX_SIZE.x / 2.0f - HEART_SIZE.x / 2.0f, this->boxPos.y + BOX_SIZE.y / 2.0f - HEART_SIZE.y / 2.0f);
    this->heartSize = HEART_SIZE;
    this->distance = distance;
}
Lives::~Lives()
{
}
void Lives::Draw(SpriteRender &renderer)
{
    for (int i = 0; i < lifePointMax; i++)
        renderer.DrawSprite(heartBox, boxPos + glm::vec2(distance * i, 0.0f), boxSize);
    for (int i = 0; i < curLifePoint; i++)
        renderer.DrawSprite(heart, heartPos + glm::vec2(distance * i, 0.0f), heartSize);
}