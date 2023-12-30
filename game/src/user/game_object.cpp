#include "game_object.h"
GameObject::GameObject()
    : position(glm::vec2(0.0f)), size(glm::vec2(1.0f)), velocity(glm::vec2(0.0f)),
      color(glm::vec3(1.0f)), rotation(0.0f), image(), isSolid(false), destoryed(false) {}
GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture &image, glm::vec3 color, glm::vec2 velocity)
{
  this->position = pos;
  this->size=size;
  this->velocity=velocity;
  this->color=color;
  this->rotation=0.0f;
  this->image=image;
  this->isSolid=false;
  this->destoryed=false;
}
void GameObject::Draw(SpriteRender &renderer)
{
  renderer.DrawSprite(this->image, this->position, this->size, this->rotation, this->color);
}