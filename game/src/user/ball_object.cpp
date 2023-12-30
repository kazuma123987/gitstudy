#include "ball_object.h"
BallObject::BallObject()
    : GameObject(), radius(25.0f), stuck(true), sticky(false), passThrough(false) {}
BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture image)
    : GameObject(pos, glm::vec2(radius * 2.0f), image, glm::vec3(1.0f), velocity), radius(radius), stuck(true), sticky(false), passThrough(false) {}
glm::vec2 BallObject::Move(float deltaTime, int window_width, int window_height)
{
    if (!stuck)
    {
        this->position += deltaTime * this->velocity;
        if (this->position.x <= 0.0f)
        {
            this->velocity.x = -this->velocity.x;
            this->position.x = 0.0f;
        }
        else if (this->position.x + this->size.x >= window_width)
        {
            this->velocity.x = -this->velocity.x;
            this->position.x = window_width - this->size.x;
        }
        if (this->position.y + this->size.y >= window_height)
        {
            this->velocity.y = -this->velocity.y;
            this->position.y = window_height - this->size.y;
        }
    }
    return this->position;
}
void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->position = position;
    this->velocity = velocity;
    this->stuck = true;
    this->sticky = false;
    this->passThrough = false;
    this->color = glm::vec3(1.0f);
}