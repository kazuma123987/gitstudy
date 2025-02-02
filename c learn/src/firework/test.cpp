#include <vector>
#include <list>
#include <ctime>
#include <chrono>
#include <conio.h>
#include <memory>
#include "particle_emitter.h"
#include "resource_manager.h"
#include "windows.h"

const int frameRate = 120;
int winWidth = 3840;
int winHeight = 2160;

int main()
{
    // 初始化随机数种子
    std::srand(static_cast<unsigned int>(std::time(0)));

    // 创建渲染器
    auto renderer = std::make_unique<Renderer>();
    if (!renderer->initGraph(winWidth, winHeight))
    {
        return -1;
    }

    // 初始化粒子发射器
    std::list<ParticleEmitter> emitters;
    for (size_t i = 0; i < 1; i++)
    {
        ParticleEmitter emitter;
        emitter.setPosition(glm::vec2(winWidth / 2, winHeight / 2)); // 发射器位置
        // emitter.setVelocity(glm::vec2(0.0f, 100.0f));                // 发射器速度
        emitter.setParPerSecond(100);    // 发射器生成粒子速度
        emitter.setParInitSize(20.0f);   // 粒子初始尺寸
        emitter.setParInitSpeed(200.0f); // 粒子初始速度大小
        emitter.setParInitLife(3.0f);    // 粒子生命
        emitter.setEmitterLife(200.0f);  // 发射器生命
        emitters.push_back(emitter);
    }
    renderer->clear(); // 清屏
    // 初始化时间
    auto lastTime = std::chrono::system_clock::now();
    auto frameTime = std::chrono::system_clock::now();

    // 主循环
    while (!renderer->isRun())
    {
        // 更新时间
        float deltaTime = std::chrono::duration<float>(std::chrono::system_clock::now() - lastTime).count();
        lastTime = std::chrono::system_clock::now();

        // 更新粒子发射器
        for (auto it = emitters.begin(); it != emitters.end();)
        {
            it->update(deltaTime);
            if (!it->isAlive())
            {
                it = emitters.erase(it);
            }
            else
            {
                it->draw(*renderer);
                it++;
            }
        }

        // 刷新屏幕
        if (std::chrono::duration<float>(std::chrono::system_clock::now() - frameTime).count() >= 1.0f / frameRate)
        {
            renderer->flush(); // 交换缓冲区
            renderer->clear(); // 清屏
            frameTime = std::chrono::system_clock::now();
        }

        // 处理事件
        renderer->update();
    }
    ResourceManager::Clear();
    renderer->closeGraph();
    return 0;
}