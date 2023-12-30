#ifndef __POWERUP__H
#define __POWERUP__H
#include "game_object.h"
const glm::vec2 PowerUp_Size = glm::vec2(120, 40);
const glm::vec2 PowerUp_Velocity = glm::vec2(0, -120.0f);
class PowerUp : public GameObject
{
public:
    std::string type;
    float duration;
    bool activated;
    PowerUp(){};
    PowerUp(std::string type, glm::vec3 color, float duration, glm::vec2 position, Texture &texture)
        : GameObject(position, PowerUp_Size, texture, color, PowerUp_Velocity), type(type), duration(duration), activated(false){}
};
#endif