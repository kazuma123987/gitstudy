#include "test.h"
// N卡使用独显运行
//extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
// VAO:乘坐高铁的人们 VBO:高铁 显存：高铁的终点站
// VAO会存储顶点属性的更改和对应的缓存对象
void frame_size_callback(GLFWwindow *window, int width, int height);
void press_close_window(GLFWwindow *window);
void press_position_control(GLFWwindow *window, Shader *shader,clock_t *pre);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
FMODSOUND* InitSound();
void deleteSound(FMODSOUND *s);
//全局变量
static float xoffset = 0;
static float yoffset = 0;
static FMODMUSIC music;
FMODSOUND* s1=InitSound();
int main()
{
    // 初始化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 注意设置的glfw上下文版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef _APPLE_
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    music.init();
    music.loadMusic(s1,"music/start.mp3");
    // 创建窗口
    GLFWwindow *window = glfwCreateWindow(800, 600, "game", NULL, NULL);
    if (window == NULL)
    {
        fputs("\nfailed to create window", stderr);
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // 设置window为gl要处理的窗口环境
    glfwSetFramebufferSizeCallback(window, frame_size_callback);
    // 使用glad加载opengl库
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fputs("\nfailed to init glad", stderr);
        glfwTerminate();
        return -1;
    }

    // 创建着色器程序
    Shader shader1("shader/shader.vsh", "shader/shader.fsh");

    // 顶点数组和索引
    float arr_vertex[] =
        {
            0, 0.5, 0, 0.5, 0, 0,
            -0.5f, -0.5f, 0, 0, 0.5, 0,
            0.5f, -0.5f, 0, 0, 0, 0.5};

    // VAO
    GLuint VA_NAME;
    glGenVertexArrays(1, &VA_NAME);
    glBindVertexArray(VA_NAME);

    // VBO
    GLuint VB_NAME;
    glGenBuffers(1, &VB_NAME);
    glBindBuffer(GL_ARRAY_BUFFER, VB_NAME);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arr_vertex), arr_vertex, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // 解绑
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);//线框模式绘图
    // glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);//填充模式绘图（默认）
    clock_t cur = 0;
    clock_t pre_control = 0;
    glfwSetKeyCallback(window,keyCallback);
    music.playMusic(s1);
    while (!glfwWindowShouldClose(window))
    {
        cur = clock();
        // inputs
        press_close_window(window);
        // shader
        glClearColor(0.1, 0.2, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        shader1.use();
        float t=2*glfwGetTime();
        float r=cos(t)*0.5+0.5;
        float g=cos(t-PI*2/3)*0.5+0.5;
        float b=cos(t-PI*4/3)*0.5+0.5;
        arr_vertex[3]=arr_vertex[11]=arr_vertex[16]=r;
        arr_vertex[4]=arr_vertex[9]=arr_vertex[17]=g;
        arr_vertex[5]=arr_vertex[10]=arr_vertex[15]=b;
        glBufferData(GL_ARRAY_BUFFER, sizeof(arr_vertex), arr_vertex, GL_DYNAMIC_DRAW);
        if (cur - pre_control > 10)
            press_position_control(window, &shader1, &pre_control);
        glBindVertexArray(VA_NAME);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //sound
        music.set3DPosition(s1,sin(t),cos(t),0);
        music.updateSystem();
        // glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);//利用索引缓存对象画三角形
        // output
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VA_NAME); // 删除VAO绑定的一个VAO对象
    glDeleteBuffers(1, &VB_NAME);      // 删除VBO绑定的一个缓存对象
    glfwTerminate();                   // 不要忘记释放glfw资源
    deleteSound(s1);
    music.systemFree();
    return 0;
}
void frame_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void press_close_window(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, TRUE);
}
void press_position_control(GLFWwindow *window, Shader *shader, clock_t *pre)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        shader->unfm1f("y", (yoffset += 0.015));
        *pre=clock();
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        shader->unfm1f("y", (yoffset -= 0.015));
        *pre=clock();
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        shader->unfm1f("x", (xoffset -= 0.015));
        *pre=clock();
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        shader->unfm1f("x", (xoffset += 0.015));
        *pre=clock();
    }
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key==(GLFW_KEY_P)&&action==GLFW_PRESS)
    {
        static bool f=FALSE;
        FMOD_Channel_SetPaused(s1->channel,(f=!f));
    }
    else if(key==GLFW_KEY_N&&action==GLFW_PRESS)
    {
        FMOD_Channel_Stop(s1->channel);
    }
}
FMODSOUND* InitSound()
{
    FMODSOUND *s=(FMODSOUND*)malloc(sizeof(FMODSOUND));
    s->channel=NULL;
    s->sound=NULL;
    return s;
}
void deleteSound(FMODSOUND *s)
{
    FMOD_Sound_Release(s->sound);
    free(s);
}