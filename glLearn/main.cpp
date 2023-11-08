#include "shader.h"
#include "sound.h"
#include "tool.h"
// N卡使用独显运行
// extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
// 函数声明
void error_callback(int error, const char *description);
void frame_size_callback(GLFWwindow *window, int width, int height);
void press_close_window(GLFWwindow *window);
void press_position_control(GLFWwindow *window, Shader *shader, clock_t *pre);
void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods);
void OpenName_Init(OPENFILENAMEA *ofn, char szFile[]);
int main(int argc, char *argv[])
{
    // 获取文件当前路径
    GetModuleFileNameA(NULL, filePath, PATH_MAX);
    char *c = strrchr(filePath, '\\');
    if (c != NULL)
        *(c + 1) = '\0';
    // glfw初始化
    glfwInit();
    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 注意设置的glfw上下文版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef _APPLE_
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // 创建glfw窗口
    GLFWwindow *window = glfwCreateWindow(700, 700, "game", NULL, NULL);
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
    /*-----------first box-----------*/
    // 创建着色器程序
    SetCurrentDirectoryA(filePath);
    Shader shader1("res\\shader\\shader.vs", "res\\shader\\shader.fs");

    // 顶点数组和索引
    float arr_vertex[] =
        {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
         -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

         -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
         -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
         -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
         0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
         -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};
    unsigned int arr_index[] = {
        0, 1, 3, 1, 2, 3, // front
        4, 5, 7, 5, 7, 6, // behind
        6, 7, 2, 7, 2, 3, // left
        4, 5, 0, 5, 1, 0, // right
        4, 0, 7, 0, 3, 7, // top
        1, 2, 6, 1, 5, 6  // bottom
    };

    // VAO
    GLuint VA_NAME[2];
    glGenVertexArrays(2, VA_NAME);
    glBindVertexArray(VA_NAME[0]);

    // VBO
    GLuint VB_NAME;
    glGenBuffers(1, &VB_NAME);
    glBindBuffer(GL_ARRAY_BUFFER, VB_NAME);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arr_vertex), arr_vertex,
                 GL_STATIC_DRAW);

    // EBO
    GLuint EB_NAME[2];
    glGenBuffers(2, EB_NAME);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EB_NAME[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arr_index), arr_index,
                 GL_STATIC_DRAW);

    // TEXTURE
    GLuint texture[4];
    glGenTextures(4, texture);

    glBindTexture(GL_TEXTURE_2D, texture[0]); // 绑定第一个纹理
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST_MIPMAP_LINEAR); // 只有缩小能开启多级渐远纹理
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST); // 像素清晰,图像柔和
    // 加载并发送纹理
    int width[4], height[4], nColorChannels[4];
    stbi_set_flip_vertically_on_load(TRUE);
    unsigned char *imageData = stbi_load("res/texture/metal1.jpg", &width[0],
                                         &height[0], &nColorChannels[0], 0);
    if (imageData)
    {
        // 注意如果是png需要把两个GL_RGB都换成GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width[0], height[0], 0, GL_RGB,
                     GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        fputs("\nfailed to load the image1", stderr);
    stbi_image_free(imageData); // 纹理已加载，删除纹理数组

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST_MIPMAP_LINEAR); // 像素清晰,图像整体偏像素风
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    imageData = stbi_load("res/texture/qln.jpg", &width[1], &height[1],
                          &nColorChannels[1], 0);
    if (imageData)
    {
        glPixelStorei(
            GL_UNPACK_ALIGNMENT,
            1); // 按每行单字节处理图片传输(纹理宽度乘以颜色通道数不是4的整数倍时需要使用,高度不影响)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width[1], height[1], 0, GL_RGB,
                     GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // 恢复默认状态(每行四字节传输)
    }
    else
        fputs("\nfailed to load the image2", stderr);
    stbi_image_free(imageData);
    // 指定纹理单元传入的位置(注意这里不要把第二个参数设置成GL_TEXTURE0等)
    shader1.use();
    shader1.unfm1i("ourTexture1", 0);
    shader1.unfm1i("ourTexture2", 1);

    // 顶点指针设置
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)0); // 顶点坐标
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)(3 * sizeof(float))); // 纹理坐标
    glEnableVertexAttribArray(1);
    // 开启深度测试
    glEnable(GL_DEPTH_TEST);

    // 解绑(VEO不建议解绑)
    // glBindVertexArray(0); //
    // VAO解绑,VAO只会绑定glVertexAttribPointer、glEnableVertexAttribArray、VBO、EBO信息
    // glBindBuffer(GL_ARRAY_BUFFER, 0);//VBO解绑,解绑的VBO仍会绑定VAO
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);//!!!不要解绑，否则VAO会不能用顶点索引

    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);//线框模式绘图
    // glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);//填充模式绘图（默认）
    clock_t cur = 0;
    clock_t pre_control = 0;
    glfwSetKeyCallback(window, keyCallback);
    // fmod
    s1 = InitSound();
    s2 = InitSound();
    music.init();
    music.loadMusic(s1, "res/music/start.mp3");
    FMOD_Sound_SetMode(s1->sound, FMOD_LOOP_NORMAL);
    music.loadMusic(s2, "res/music/choose.wav");
    music.playMusic(s1);
    // 坐标系统
    viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
    projMat = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f); // 透视投影矩阵
    // for (int i = 0; i < 4; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //         printf("%.3f,", projMat[i][j]);
    //     printf("\n");
    // }
    while (!glfwWindowShouldClose(window))
    {
        cur = clock();
        // inputs
        press_close_window(window);
        // shader
        glClearColor(0.1, 0.2, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader1.use();
        float t = 2 * glfwGetTime();
        if (cur - pre_control > 10)
            press_position_control(window, &shader1, &pre_control);
        float scale = (sin(t) + 1) * 0.5;
        glm::vec3 offVec[10] = {
            glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f), glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f), glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f), glm::vec3(-1.3f, 1.0f, -1.5f)};
        shader1.unfm1f("mixVector", scale);
        shader1.unfmat4fv("view", viewMat);
        shader1.unfmat4fv("proj", projMat);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        // glBindVertexArray(VA_NAME[0]);
        for (int i = 0; i < 10; i++)
        {
            glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), offVec[i]);
            if (i % 2 == 0)
                modelMat = glm::rotate(
                    modelMat, (float)glfwGetTime() * glm::radians(100.0f),
                    glm::vec3(1.0f, 0.2f, 0.5f));
            shader1.unfmat4fv("model", modelMat);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // sound
        music.set3DPosition(s1, sin(t), cos(t), 0);
        music.updateSystem();
        // output
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(2, VA_NAME); // 删除VAO绑定的一个VAO对象
    glDeleteBuffers(1, &VB_NAME);     // 删除VBO绑定的一个缓存对象
    glDeleteBuffers(2, EB_NAME);
    glDeleteTextures(4, texture);
    glfwTerminate(); // 不要忘记释放glfw资源
    deleteSound(s1);
    deleteSound(s2);
    music.systemFree();
    return 0;
}
// 回调函数
void error_callback(int error, const char *description)
{
    fputs(description, stderr);
}
void frame_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == (GLFW_KEY_P) && action == GLFW_PRESS)
    {
        static bool f = FALSE;
        music.playMusic(s2);
        FMOD_Channel_SetPaused(s1->channel, (f = !f));
    }
    else if (key == GLFW_KEY_N && action == GLFW_PRESS)
    {
        music.playMusic(s2);
        FMOD_Channel_Stop(s1->channel);
    }
}
// 普通函数
void press_close_window(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, TRUE);
}
void press_position_control(GLFWwindow *window, Shader *shader, clock_t *pre)
{
    // 位移控制
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        viewMat = glm::translate(viewMat, glm::vec3(0.0f, -0.015f, 0.0f));
        *pre = clock();
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.015f, 0.0f));
        *pre = clock();
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        viewMat = glm::translate(viewMat, glm::vec3(0.015f, 0.0f, 0.0f));
        *pre = clock();
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        viewMat = glm::translate(viewMat, glm::vec3(-0.015f, 0.0f, 0.0f));
        *pre = clock();
    }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, 0.03f));
        *pre = clock();
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -0.03f));
        *pre = clock();
    }
    // 旋转控制
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        viewMat = glm::rotate(viewMat, glm::radians(1.0f),
                              glm::vec3(0.0f, 1.0f, 0.0f));
        *pre = clock();
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        viewMat = glm::rotate(viewMat, glm::radians(-1.0f),
                              glm::vec3(0.0f, 1.0f, 0.0f));
        *pre = clock();
    }
}
void OpenName_Init(OPENFILENAMEA *ofn, char szFile[])
{
    // 初始化OPENFILENAME
    memset(ofn, 0, sizeof(OPENFILENAMEA));
    ofn->lStructSize = sizeof(OPENFILENAMEA);
    ofn->lpstrFile = szFile; // 文件路径
    // 把lpstrFile[0]赋值为'\0'这样GetOpenFileName不会用szFile的内容初始化它自己
    ofn->lpstrFile[0] = '\0';
    ofn->nMaxFile = PATH_MAX;                     // 文件路径长度
    ofn->lpstrFilter = "All\0*.*\0Text\0*.TXT\0"; // 定义了两个筛选器ALL(*.*),Text(*.TXT),索引值分别为1，2
    ofn->nFilterIndex = 1;                        // 默认筛选器索引
    ofn->lpstrFileTitle = NULL;                   // 文件名，如果需要获取文件名，ofn.Flags需要开启OFN_EXPLORER
    ofn->nMaxFileTitle = 0;                       // 文件名长度
    ofn->lpstrInitialDir = NULL;
    ofn->Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 禁止用户使用不存在的路径和文件名
}