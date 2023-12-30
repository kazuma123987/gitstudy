#ifndef __PARTICLE__GENERATOR__H
#define __PARTICLE__GENERATOR__H
#include <vector>
#include "shader.h"
#include "texture.h"
#include "game_object.h"
struct Particle
{
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec4 color;
    float scale;
    float life;
    Particle() : position(0.0f), velocity(0.0f), color(1.0f), scale(10.0f), life(0.0f) {}
};
class ParticleGenerator
{
public:
    ParticleGenerator(Shader &shader, Texture &texture, int amount);
    ~ParticleGenerator();
    void Update(float deltaTime, GameObject &obj, int newParticleNum, glm::vec2 offset = glm::vec2(0.0f));
    void Draw();

private:
    std::vector<Particle> particles;
    int amount;
    Shader shader;
    Texture texture;
    GLuint VAO, VBO;
    void Init();
    void newParticle(GameObject &object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};
#endif