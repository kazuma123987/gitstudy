#ifndef __BALL__OBJECT__H
#define __BALL__OBJECT__H
#include "game_object.h"
class BallObject : public GameObject
{
public:
    float radius;
    bool stuck;//是否被黏住
    bool sticky;//是否有粘性(碰撞到paddle时stuck=true)
    bool passThrough;//是否会经过固体砖块(solid)
    BallObject();
    ~BallObject(){}
    BallObject(glm::vec2 pos,float radius,glm::vec2 velocity,Texture image);
    glm::vec2 Move(float deltaTime,int window_width,int window_height);
    void Reset(glm::vec2 position,glm::vec2 velocity);
};
#endif