#include "particle_generator.h"
ParticleGenerator::ParticleGenerator(Shader &shader, Texture &texture, int amount)
{
    this->shader=shader;
    this->texture=texture;
    this->amount=amount;
    this->Init();
}
ParticleGenerator::~ParticleGenerator()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}
void ParticleGenerator::Update(float deltaTime, GameObject &obj, int newParticleNum, glm::vec2 offset)
{
    for (int i = 0; i < newParticleNum; i++)
        this->newParticle(obj, offset);
    for (Particle &par : particles)
    {
        par.life -= deltaTime;
        if (par.life > 0.0f)
        {
            par.position += par.velocity * deltaTime;
            par.color.a -= deltaTime * 2.5f;
            par.scale -= deltaTime * 10.0f;
        }
    }
}
void ParticleGenerator::Draw()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    this->shader.Use();
    glActiveTexture(GL_TEXTURE0);
    this->texture.Bind();
    glBindVertexArray(this->VAO);
    for (Particle &par : particles)
    {
        if (par.life > 0.0f)
        {
            shader.unfvec2("offset", par.position);
            shader.unfvec4("parColor", par.color);
            shader.unfm1f("scale", par.scale);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
    }
    glBindVertexArray(0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void ParticleGenerator::Init()
{
    // 生成VAO和VBO
    float vertices[] =
        {
            0.0f, 0.0f, 0.0f, 0.0f, // 左下
            1.0f, 0.0f, 1.0f, 0.0f, // 右下
            0.0f, 1.0f, 0.0f, 1.0f, // 左上
            1.0f, 1.0f, 1.0f, 1.0f  // 右上
        };
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glBindVertexArray(0);
    // 添加粒子到数组中(这里粒子生命都为0)
    for (int i = 0; i < this->amount; i++)
        particles.emplace_back(Particle());
}
void ParticleGenerator::newParticle(GameObject &object, glm::vec2 offset)
{
    static int newParIndex = 0;
    Particle &par = particles[newParIndex];
    if (par.life <= 0.0f)
    {
        float random = (rand() % 100 - 50) / 10.0f;
        float rColor = 0.5f + (rand() % 100) / 100.0f;
        par.position = object.position + random + offset;
        par.velocity = object.velocity * 0.1f;
        par.color = glm::vec4(rColor, rColor, rColor, 1.0f);
        par.life = 1.0f;
        par.scale = 10;
        newParIndex = (newParIndex + 1) % amount;
    }
}