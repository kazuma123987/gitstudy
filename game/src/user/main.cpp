#include <stdio.h>
#include <windows.h>
#include <chrono>
#include "game.h"
#include "resource_manager.h"
// N卡使用独显运行
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
const GLuint SCREEN_WIDTH = 1600;
const GLuint SCREEN_HEIGHT = 900;
void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mod);
void frameSizeCallBack(GLFWwindow *window, int width, int height);
void setFPS(GLFWwindow *window);
void cursorPosCallBack(GLFWwindow *window, double x, double y);
void mouseButtonCallBack(GLFWwindow *window, int button, int action, int mods);
Game *game = new Game(SCREEN_WIDTH, SCREEN_HEIGHT);
int main()
{
    //  初始化glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "breakOut", NULL, NULL);
    if (window == NULL)
    {
        printf("failed to create window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // 初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("ERROR::GLAD failed to load the proc\n");
        return -1;
    }
    // 注册回调函数
    glfwSetKeyCallback(window, keyCallBack);
    glfwSetFramebufferSizeCallback(window, frameSizeCallBack);
    glfwSetCursorPosCallback(window, cursorPosCallBack);
    glfwSetMouseButtonCallback(window, mouseButtonCallBack);
    // 开启混合和面剔除
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    // 游戏初始化
    game->Init();
    // 控制游戏速度
    float curTime = 0.0f;
    float lastTIme = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        curTime = glfwGetTime();
        float deltaTime = curTime - lastTIme;
        lastTIme = curTime;
        setFPS(window);
        glfwPollEvents();
        game->ProcessInput(deltaTime);
        game->Update(deltaTime);
        if (game->exit)
            glfwSetWindowShouldClose(window, true);
        game->Render();
        glfwSwapBuffers(window);
    }
    ResourceManager::Clear();
    delete game;
    glfwTerminate();
    return 0;
}
void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mod)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            game->keys[key] = true;
        else if (action == GLFW_RELEASE)
            game->keys[key] = false;
    }
}
void frameSizeCallBack(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void setFPS(GLFWwindow *window)
{
    static int fpsCount = 0;
    fpsCount++;
    static auto lastTime = std::chrono::high_resolution_clock::now();
    auto curTime = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(curTime - lastTime).count() >= 1000)
    {
        lastTime = curTime;
        glfwSetWindowTitle(window, ("breakOut   FPS:" + std::to_string(fpsCount)).c_str());
        fpsCount = 0;
    }
}
void cursorPosCallBack(GLFWwindow *window, double x, double y)
{
    game->cursorPos.x = x;
    game->cursorPos.y = game->height - y;
}
void mouseButtonCallBack(GLFWwindow *window, int button, int action, int mods)
{
    if (button >= 0 && button <= 8)
    {
        if (action == GLFW_PRESS)
            game->buttons[button] = true;
        else if (action == GLFW_RELEASE)
            game->buttons[button] = false;
    }
}