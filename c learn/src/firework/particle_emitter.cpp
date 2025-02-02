#include "particle_emitter.h"
#include <cstdlib> // for rand()
#include <chrono>

ParticleEmitter::ParticleEmitter()
{
    this->position = glm::vec2(0.0f);
    this->velocity = glm::vec2(0.0f);
    this->emitterLife = 0.0f;
    this->_isActive = true;
    this->particleInitialSpeed = 0.0f;
    this->particleInitialSize = 0.0f;
    this->particleInitialLife = 0.0f;
    this->particlesPerSecond = 0;
}

const std::list<Particle> &ParticleEmitter::getParticles() const
{
    return this->particles;
}

bool ParticleEmitter::isAlive() const
{
    return this->_isActive;
}

void ParticleEmitter::update(float deltaTime)
{
    if (this->_isActive)
    {
        this->position += deltaTime * this->velocity;
        this->emitterLife -= deltaTime;
        if (this->emitterLife <= 0.0f)
        {
            this->_isActive = false;
        }

        // 发射粒子
        static float emissionAccumulator = 0.0f;
        emissionAccumulator += this->particlesPerSecond * deltaTime;
        while (emissionAccumulator >= 1.0f)
        {
            emitParticle();
            emissionAccumulator -= 1.0f;
        }
    }

    // 更新粒子
    for (auto it = particles.begin(); it != particles.end();)
    {
        it->update(deltaTime);
        if (!it->isAlive())
        {
            it = particles.erase(it);
        }
        else
        {
            it++; // 没擦除时自增迭代器
        }
    }
}

void ParticleEmitter::draw(Renderer &renderer)
{
    // 更新粒子
#if 0
    for (auto it = particles.begin(); it != particles.end(); ++it)
    {
        if (it->isAlive())
        {
            it->draw(renderer);
        }
    }
#else
    // 提取粒子数据
    static std::vector<glm::vec2> offsets;
    static std::vector<float> scales;
    static std::vector<glm::vec4> colors;

    offsets.resize(0);
    scales.resize(0);
    colors.resize(0);

    for (const auto &particle : particles)
    {
        offsets.push_back(particle.getPosition());
        scales.push_back(particle.getSize());
        colors.push_back(particle.getColor());
    }
    renderer.DrawCircleInstance(offsets, scales, colors);
#endif
}

void ParticleEmitter::setPosition(glm::vec2 pos)
{
    this->position = pos;
}
void ParticleEmitter::setVelocity(glm::vec2 vec)
{
    this->velocity = vec;
}
void ParticleEmitter::setParInitSpeed(float speed)
{
    this->particleInitialSpeed = speed;
}
void ParticleEmitter::setParInitSize(float size)
{
    this->particleInitialSize = size;
}
void ParticleEmitter::setParInitLife(float life)
{
    this->particleInitialLife = life;
}
void ParticleEmitter::setParPerSecond(int count)
{
    this->particlesPerSecond = count;
}

void ParticleEmitter::setEmitterLife(float life)
{
    this->emitterLife = life;
}

void ParticleEmitter::emitParticle()
{
    glm::vec2 particlePosition = this->position;
    float angle = (rand() % 201) / 100.0f * PI; // [0 , 2PI]
    glm::vec2 particleVelocity = glm::vec2(cos(angle), sin(angle)) * this->particleInitialSpeed;
    float particleLife = ((rand() % 201) / 1000.0f + 0.8f) * this->particleInitialLife;
    float particleSize = ((rand() % 201) / 1000.0f + 0.8f) * this->particleInitialSize;
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    float time = (duration.count() % 4001) / 2000.0f * PI;
    glm::vec4 color = glm::vec4(glm::vec2(cosf(time), sinf(time)) * 0.5f + 0.5f, 0.5f, 1.0f);
    particles.emplace_back(particlePosition, particleVelocity, particleLife, particleSize, PARTYPE_CIRCLE, color);
}