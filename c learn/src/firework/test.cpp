#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <conio.h>
#include "particle_emitter.h"
#include "resource_manager.h"
#include "windows.h"

const int frameRate = 144;
int winWidth = 1600;
int winHeight = 900;

std::list<ParticleEmitter> emitters;

int main()
{
    // 初始化随机数种子
    std::srand(static_cast<unsigned int>(std::time(0)));

    // 初始化 GLFW
    if (!glfwInit())
    {
        return -1;
    }

    // 创建窗口
    GLFWwindow *window = glfwCreateWindow(winWidth, winHeight, "Particle System", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // 设置 OpenGL 上下文
    glfwMakeContextCurrent(window);

    // 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    glViewport(0, 0, winWidth, winHeight); // 设置视口
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#if 0
    glMatrixMode(GL_PROJECTION);               // 选择投影矩阵堆栈
    glLoadIdentity();                          // 将当前矩阵堆栈的顶部矩阵重置为单位矩阵
    glOrtho(0, winWidth, winHeight, 0, -1, 1); // 设置正交投影的长、宽
    glMatrixMode(GL_MODELVIEW);                // 选择模型视图矩阵堆栈
    glLoadIdentity();                          // 将当前矩阵堆栈(模型变换)的顶部矩阵重置为单位矩阵,即清空上次的(位置、选择、缩放)变换
#endif

    // 加载着色器
    // SetCurrentDirectoryA("C:\\Users\\34181\\Desktop\\gitstudy\\c learn\\src\\firework");
    ResourceManager::loadShader("./shader/solid.vert", "./shader/solid.frag", NULL, "solid");
    ResourceManager::loadShader("./shader/sprite.vert", "./shader/sprite.frag", NULL, "sprite");

    // 创建渲染器
    Renderer *renderer = new Renderer();

    // 初始化粒子发射器
    for (size_t i = 0; i < 2; i++)
    {
        ParticleEmitter emitter;
        emitter.setPosition(glm::vec2(winWidth / 2 * i, 0)); // 发射器位置
        emitter.setVelocity(glm::vec2(0.0f, 100.0f));          // 发射器速度
        emitter.setParPerSecond(100000);                          // 发射器生成粒子速度
        emitter.setParInitSize(2.0f);                          // 粒子初始尺寸
        emitter.setParInitSpeed(10.0f);                        // 粒子初始速度大小
        emitter.setParInitLife(3.0f);                          // 粒子生命
        emitter.setEmitterLife(20.0f);                         // 发射器生命
        emitters.push_back(emitter);
    }

    auto lastTime = std::chrono::system_clock::now();
    auto frameTime = std::chrono::system_clock::now();

    // 主循环
    while (!glfwWindowShouldClose(window))
    {
        // 清除屏幕
        glClear(GL_COLOR_BUFFER_BIT);

        float deltaTime = std::chrono::duration<float>(std::chrono::system_clock::now() - lastTime).count();
        lastTime = std::chrono::system_clock::now();

        // 更新粒子发射器
        for (auto it = emitters.begin(); it != emitters.end();)
        {
            it->update(deltaTime);
            it->draw(*renderer);
            if (!it->isAlive())
            {
                it = emitters.erase(it);
            }
            else
            {
                it++;
            }
        }

        // 刷新屏幕
        if (std::chrono::duration<float>(std::chrono::system_clock::now() - frameTime).count() >= 1.0f / frameRate)
        {
            glfwSwapBuffers(window);
            frameTime = std::chrono::system_clock::now();
        }

        // 处理事件
        glfwPollEvents();
    }
    delete renderer;
    ResourceManager::Clear();
    glfwTerminate();
    return 0;
}