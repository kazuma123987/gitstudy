#include "test.h"
#include "fmod/fmod.h"
#include "mmsystem.h"
#include "glad/glad.h"  //glad.h必须放在glfw3.h前面，glad可以查找gl、glu、glex、wgl、glx的函数指针以方便调用其函数
#include "GLFW/glfw3.h" //轻量级跨平台工具库，提供渲染物体最低限度的API（管理窗口、读取输入、处理事件）
#pragma comment(lib, "winmm.lib")
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void exit_Input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
int playmusic(FMOD_SYSTEM **system, FMOD_SOUND **sound, FMOD_CHANNEL **channel, const char *bgm)
{
    FMOD_RESULT result = FMOD_System_Create(system, FMOD_VERSION);
    if (result != FMOD_OK)
    {
        fputs("\nfailed to create system", stderr);
        return 1;
    }
    result = FMOD_System_Init(*system, 32, FMOD_INIT_NORMAL, NULL);
    if (result != FMOD_OK)
    {
        fputs("\nfailed to init system", stderr);
        return 1;
    }
    result = FMOD_System_CreateSound(*system, bgm, FMOD_LOOP_NORMAL | FMOD_3D, NULL, sound);
    if (result != FMOD_OK)
    {
        fputs("\nfailed to create sound", stderr);
        return 1;
    }
    result = FMOD_System_PlaySound(*system, *sound, NULL, FMOD_OK, channel);
    if (result != FMOD_OK)
    {
        fputs("\nfailed to play sound", stderr);
        return 1;
    }
    return 0;
}
int playmusic_once(FMOD_SYSTEM **system, FMOD_SOUND **sound, FMOD_CHANNEL **channel, const char *bgm)
{
    FMOD_RESULT result = FMOD_System_CreateSound(*system, bgm, FMOD_LOOP_OFF | FMOD_3D, NULL, sound);
    if (result != FMOD_OK)
    {
        fputs("\nfailed to create sound", stderr);
        return 1;
    }
    result = FMOD_System_PlaySound(*system, *sound, NULL, FMOD_OK, channel);
    if (result != FMOD_OK)
    {
        fputs("\nfailed to play sound", stderr);
        return 1;
    }
    return 0;
}
void press_choose_input(GLFWwindow *window, FMOD_SYSTEM **system, FMOD_SOUND **sound, FMOD_CHANNEL **channel,clock_t *pre)
{
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        FMOD_Sound_Release(*sound);
        playmusic_once(system, sound, channel, "music/choose.wav");
        *pre=clock();
    }
}
void press_3D_input(GLFWwindow *window, bool *flag_3D, clock_t *dst)
{
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        *flag_3D = !(*flag_3D);
        *dst = clock();
    }
}
int main()
{
    FMOD_SYSTEM *system = NULL;
    FMOD_SOUND *sound1 = NULL;
    FMOD_SOUND *sound2 = NULL;
    FMOD_CHANNEL *channel1 = NULL;
    FMOD_CHANNEL *channel2 = NULL;
    glfwInit();                                                    // glfw的初始化
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // 设置主版本为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 // 设置次版本为3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 设置核心模式，只能使用OpenGL功能的一个子集（这个子集足够用了）
#ifndef WIN32
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 如果不是windows系统要设置这个
#endif
    GLFWwindow *window = glfwCreateWindow(800, 600, "game", NULL, NULL); // 创建窗口
    if (!window)
    {
        fputs("failed to create a window\n", stderr); // 创建窗口错误检查
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);                          // 通知GLFW将窗口的上下文设置为当前线程的主上下文
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // glad加载函数指针且初始化
    {
        fputs("failed to init glad\n", stderr);
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 注册窗口大小改变时触发的回调函数
    playmusic(&system, &sound1, &channel1, "music/start.mp3");
    // 参数部分
    FMOD_VECTOR pos;
    pos.x = 0;
    pos.y = 0;
    pos.z = 2;
    unsigned int msec = 0;
    clock_t cur_t = 0;
    clock_t pre_3D_t=0;
    clock_t pre_choost_t;
    while (!glfwWindowShouldClose(window)) // 渲染循环
    {
        cur_t=clock();
        /*输入与判断部分*/
        exit_Input(window); // 自定义的函数，当按下空格键时设置glfwWindowShouldClose为true
        FMOD_BOOL isplaying = FALSE;  
        if (cur_t-pre_choost_t>200)
        {
            press_choose_input(window, &system, &sound2, &channel2,&pre_choost_t);
        }
        bool flag_3D, pre;
        pre = flag_3D;
        if (cur_t - pre_3D_t > 500)
        {
            press_3D_input(window, &flag_3D, &pre_3D_t);
        }
        if (pre != flag_3D && !flag_3D)
        {
            FMOD_VECTOR pos1;
            pos1.x = 0;
            pos1.y = 0;
            pos1.z = 0;
            FMOD_Channel_Set3DAttributes(channel1, &pos1, NULL);
            FMOD_System_Update(system);
        }
        if (flag_3D)
        {
            FMOD_Channel_GetPosition(channel1, &msec, FMOD_TIMEUNIT_MS);
            double angle = 3.1415926536 * msec / 4000;
            pos.x = 2 * sin(angle);
            pos.z = 2 * cos(angle);
            FMOD_Channel_Set3DAttributes(channel1, &pos, NULL);
            FMOD_System_Update(system);
        }
        /*渲染部分*/
        glClearColor(0.1, 0.2, 0.3, 0.4); // 设置运行glclear时的颜色，这是状态参数
        glClear(GL_COLOR_BUFFER_BIT);     // 采用设置的颜色清屏
        /*输出部分*/
        glfwSwapBuffers(window); // 交换两个缓冲区的数据，以实现实时渲染
        glfwPollEvents();        // 监听事件
    }
    glfwTerminate(); // 渲染完成，释放所有资源
    FMOD_Sound_Release(sound1);
    FMOD_System_Release(system);
    return 0;
}