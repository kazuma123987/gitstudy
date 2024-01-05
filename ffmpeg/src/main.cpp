#include <stdio.h>
#include <chrono>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.h"
#include "resource_manager.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#ifdef __cplusplus
}
#endif
// 函数声明
void frameSizeCallBack(GLFWwindow *window, int width, int height);
void render(Shader &shader);
// 全局变量
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;
GLuint VAO, VBO;
Texture image_Y(GL_RED, GL_RED);
Texture image_U(GL_RED, GL_RED);
Texture image_V(GL_RED, GL_RED);
int main(int argc, char *argv[])
{
    //*---------GLFW初始化部分---------*//
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "player", NULL, NULL);
    if (window == NULL)
    {
        printf("failed to create window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("ERROR::GLAD failed to load the proc\n");
        return -1;
    }
    // 注册回调函数
    glfwSetFramebufferSizeCallback(window, frameSizeCallBack);

    //*---------资源加载部分---------*//
    ResourceManager::loadShader("res/shader/video.vert", "res/shader/video.frag", NULL, "video");
    Shader &videoShader = ResourceManager::getShader("video");
    videoShader.Use().unfm1i("image_Y", 0);
    videoShader.unfm1i("image_U", 1);
    videoShader.unfm1i("image_V", 2);

    //*---------FFMPEG显示部分---------*//
    char videoPath[] = "res/gura.mp4";
    // 为format上下文分配空间
    AVFormatContext *fmtCtx = avformat_alloc_context();
    // 打开视频文件
    if (avformat_open_input(&fmtCtx, videoPath, NULL, NULL))
        printf("failed to open the video\n");
    // 查找流信息
    if (avformat_find_stream_info(fmtCtx, NULL) < 0)
        printf("failed to find stream info\n");
    // 查找流索引(这里是视频流)
    int streamIndex = -1;
    streamIndex = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if (streamIndex == -1)
        printf("failed to find a video stream\n");
    // 获取编解码器参数
    AVCodecParameters *codecPar = fmtCtx->streams[streamIndex]->codecpar;
    // 通过编解码参数中的id获取编解码器
    const AVCodec *codec = avcodec_find_decoder(codecPar->codec_id);
    // 根据选中的编解码器为编解码器上下文分配空间
    AVCodecContext *codecCtx = avcodec_alloc_context3(codec);
    // 根据编解码参数为编解码器上下文赋值
    avcodec_parameters_to_context(codecCtx, codecPar);
    // 打开编解码器
    avcodec_open2(codecCtx, codec, NULL);
    // 为packet分配空间
    AVPacket *packet = av_packet_alloc();
    // 为packet的数据区分配空间
    av_new_packet(packet, codecCtx->width * codecCtx->height);
    // 为视频帧分配空间
    AVFrame *yuvFrame = av_frame_alloc();
    // 生成纹理
    static int isFirst=1;
    int count = 0;
    int fps = fmtCtx->streams[streamIndex]->avg_frame_rate.num;
    int duration = 1000 / fps;
    int duration_last = duration + 1000 % fps;
    int width = codecCtx->width;
    int height = codecCtx->height;
    image_Y.Generate(width, height, NULL);
    image_U.Generate(width / 2, height / 2, NULL);
    image_V.Generate(width / 2, height / 2, NULL);
    while (!glfwWindowShouldClose(window))
    {
        if (av_read_frame(fmtCtx, packet) >= 0)
        {
            if (packet->stream_index == streamIndex)
            {
                count++;
                if (avcodec_send_packet(codecCtx, packet) == 0 && avcodec_receive_frame(codecCtx, yuvFrame) == 0)
                {
                    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                    glClear(GL_COLOR_BUFFER_BIT);
                    glActiveTexture(GL_TEXTURE0);
                    image_Y.Bind();
                    glTexImage2D(GL_TEXTURE_2D, 0, image_Y.internalFormat, image_Y.width, image_Y.height, 0, image_Y.imageFormat, GL_UNSIGNED_BYTE, yuvFrame->data[0]);
                    glActiveTexture(GL_TEXTURE1);
                    image_U.Bind();
                    glTexImage2D(GL_TEXTURE_2D, 0, image_U.internalFormat, image_U.width, image_U.height, 0, image_U.imageFormat, GL_UNSIGNED_BYTE, yuvFrame->data[1]);
                    glActiveTexture(GL_TEXTURE2);
                    image_V.Bind();
                    glTexImage2D(GL_TEXTURE_2D, 0, image_V.internalFormat, image_V.width, image_V.height, 0, image_V.imageFormat, GL_UNSIGNED_BYTE, yuvFrame->data[2]);
                    static int fpsCount = 0;
                    int fpsTime;
                    fpsTime = fpsCount ? duration : duration_last;
                    static auto lastTime = std::chrono::high_resolution_clock::now();
                    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - lastTime).count() < fpsTime)
                        ;
                    lastTime = std::chrono::high_resolution_clock::now();
                    fpsCount = (fpsCount + 1) % fps;
                    isFirst=0;
                }
            }
            av_packet_unref(packet); // 清空数据区
        }
        else
            glfwSetWindowShouldClose(window, true);
        if(!isFirst)render(videoShader);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    printf("total frames:%d\n", count);
    // 释放内存
    av_packet_free(&packet);
    avcodec_free_context(&codecCtx);
    avformat_free_context(fmtCtx);
    av_frame_free(&yuvFrame);
    // 关闭窗口
    glfwTerminate();
    return 0;
}
void frameSizeCallBack(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void render(Shader &shader)
{
    static int isFirst = 1;
    if (isFirst)
    {
        float vertices[] =
            {
                -1.0f, -1.0f, 0.0f, 1.0f, // 左下
                1.0f, -1.0f, 1.0f, 1.0f,  // 右下
                -1.0f, 1.0f, 0.0f, 0.0f,  // 左上
                1.0f, 1.0f, 1.0f, 0.0f    // 右上
            };
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
        glBindVertexArray(0);
        isFirst = 0;
    }
    shader.Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}