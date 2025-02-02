#ifndef __PARTICLE_EMITTER_H
#define __PARTICLE_EMITTER_H

#include <vector>
#include <list>
#include <glm/glm.hpp>
#include "particle.h"

class ParticleEmitter
{
public:
    ParticleEmitter();
    const std::list<Particle> &getParticles() const;
    bool isAlive() const;
    void update(float deltaTime);
    void draw(Renderer &renderer);
    void setPosition(glm::vec2 pos);
    void setVelocity(glm::vec2 vec);
    void setParInitSpeed(float speed);
    void setParInitSize(float size);
    void setParInitLife(float life);
    void setParPerSecond(int count);
    void setEmitterLife(float life);

private:
    void emitParticle(); // 发射粒子
    glm::vec2 position; // 发射器位置
    glm::vec2 velocity; // 发射器速度
    float emitterLife;  // 发射器生命
    bool _isActive;      // 发射器是否存活

    float particleInitialSpeed;    // 发射时粒子的初始速度
    float particleInitialSize;     // 发射时粒子初始大小
    float particleInitialLife;     // 发射时粒子初始生命
    int particlesPerSecond;        // 每秒发射粒子数
    std::list<Particle> particles; // 所有粒子
};

#endif