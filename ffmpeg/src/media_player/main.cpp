#include <stdio.h>
#include <chrono>
#include <thread>
#include <windows.h>
#include <atomic>
#include <mutex>
#include <locale.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "util.h"

#include "shader.h"
#include "sound_manager.h"
#include "texture.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#include "libavdevice/avdevice.h"
#include "libswresample/swresample.h"
#ifdef __cplusplus
}
#endif
// N卡使用独显运行
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
// 函数声明
static enum AVPixelFormat custom_get_format(AVCodecContext *vCodecCtx, const enum AVPixelFormat *pix_fmt);
void render(Shader &shader);
inline void frame_sleep(int duration, int duration_first, int fps);
void setFPS(void *window);
void glfw_init_window();
void sdl_init_window();
void read_audio_data(void *udata, Uint8 *stream, int len);
FMOD_RESULT F_CALLBACK fmod_read_data(FMOD_SOUND * /*sound*/, void *data, unsigned int datalen);
void au_decode(const char *path);
// 静态全局变量
static Uint8 *audio_chunk; // 指向PCM数据的头部
static Uint32 audio_len;   // PCM数据的总长度
static Uint8 *audio_pos;   // 指向PCM数据已经被读取到的位置
// 非静态全局变量
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
GLFWwindow *window = NULL;
SDL_Window *sdl_window = NULL;
SDL_Event sdlEvent = {0};
bool buttons[8] = {0};
glm::vec2 cursorPos = glm::vec2(0);
bool musicHasPaused = false;
enum AVPixelFormat hw_pix_fmt;
GLuint VAO, VBO;
Texture image_Y(GL_RED, GL_RED);
Texture image_U(GL_RED, GL_RED);
Texture image_V(GL_RED, GL_RED);
Texture image_UV(GL_RG, GL_RG);
// 多线程原子量
std::atomic<bool> start_or_quit(false);
std::mutex mutex;
// define
#ifdef main
#undef main
#endif
#define USE_SDL
int main(int argc, char *argv[])
{
    wchar_t tmpPath[FILENAME_MAX / 2] = {0};
    char customPath[FILENAME_MAX] = {0};
    char videoPath[] = "res/gura.mp4";
    // char videoPath[] = "res/360°.mp4";
    // char videoPath[] = "res/tera.mp4";
    // glfw_init_window();
    if (argc < 2)
        strcpy(customPath, videoPath);
    else
    {
#ifndef WIN32
        setlocale(LC_CTYPE, "");
        char_to_wchar(argv[1], tmpPath, sizeof(tmpPath), 0);
        setlocale(LC_CTYPE, "utf8");
        wchar_to_char(tmpPath, customPath, sizeof(customPath), 65001);
        setlocale(LC_CTYPE, "C");
#else
        char_to_wchar(argv[1], tmpPath, sizeof(tmpPath), 0);
        wchar_to_char(tmpPath, customPath, sizeof(customPath), 65001);
#endif
    }
#ifdef USE_SDL
    sdl_init_window();
#else
    glfw_init_window();
#endif
    //*---------资源加载部分---------*//
    const char *vCode = "#version 400 core\n"
                        "layout(location=0)in vec4 aPos;\n"
                        "out vec2 texCoord;\n"
                        "void main()\n"
                        "{\n"
                        "gl_Position=vec4(aPos.xy,0.0f,1.0f);\n"
                        "texCoord=aPos.zw;\n"
                        "};";
    const char *fCode = "#version 400 core\n"
                        "#define AV_PIX_FMT_YUV420P 0\n"
                        "#define AV_PIX_FMT_NV12 23\n"
                        "in vec2 texCoord;\n"
                        "uniform sampler2D image_Y;\n"
                        "uniform sampler2D image_U;\n"
                        "uniform sampler2D image_V;\n"
                        "uniform sampler2D image_UV;\n"
                        "uniform int format;\n"
                        "out vec4 FragColor;\n"
                        "void main()\n"
                        "{\n"
                        "vec3 yuv;\n"
                        "if(format==AV_PIX_FMT_YUV420P)\n"
                        "{\n"
                        "   yuv.r=texture(image_Y,texCoord).r;\n"
                        "   yuv.g=texture(image_U,texCoord).r-0.5f;\n"
                        "   yuv.b=texture(image_V,texCoord).r-0.5f;\n"
                        " }\n"
                        " else if(format==AV_PIX_FMT_NV12)\n"
                        "  {\n"
                        "    yuv.r=texture(image_Y,texCoord).r;\n"
                        "    yuv.gb=texture(image_UV,texCoord).rg-0.5f;\n"
                        " }\n"
                        "  vec3 rgb=mat3(vec3(1,1,1),vec3(0,-0.395,2.032),vec3(1.140,-0.581,0))*yuv;\n"
                        "  FragColor=vec4(rgb,1.0f);\n"
                        "};";
    Shader videoShader;
    videoShader.compile(vCode, fCode);
    videoShader.Use().unfm1i("image_Y", 0);
    videoShader.unfm1i("image_U", 1);
    videoShader.unfm1i("image_V", 2);
    videoShader.unfm1i("image_UV", 3);

    //*---------FFMPEG显示部分---------*//

    // 为format上下文分配空间
    AVFormatContext *fmtCtx = avformat_alloc_context();
    // 打开视频文件
    if (avformat_open_input(&fmtCtx, customPath, NULL, NULL))
        printf("failed to open the video:%s\n", customPath);

    // 查找流信息
    if (avformat_find_stream_info(fmtCtx, NULL) < 0)
        printf("failed to find stream info\n");

    // 查找流索引
    int vIndex = -1;
    const AVCodec *vCodec = NULL;
    vIndex = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, &vCodec, 0);
    if (vIndex == -1)
        printf("failed to find a video stream\n");

    // 根据选中的编解码器为编解码器上下文分配空间
    AVCodecContext *vCodecCtx = avcodec_alloc_context3(vCodec);
    vCodecCtx->thread_count = 8; // 线程数

    //*############################开启硬件加速############################
    AVBufferRef *hwCtx = NULL;
    bool hwDecode = true;
    // 1.查找设备
    AVHWDeviceType hwType = av_hwdevice_find_type_by_name("cuda");
    if (hwType == AV_HWDEVICE_TYPE_NONE)
    {
        printf("failed to find the cuda device\n");
        return 1;
    }
    // 2.获取硬件像素格式
    for (int i = 0;; i++)
    {
        const AVCodecHWConfig *config = avcodec_get_hw_config(vCodec, i);
        if (config == NULL)
        {
            printf("Decoder %s don't support the device type:%s\n", vCodec->name, av_hwdevice_get_type_name(hwType));
            hwDecode = false;
            break;
        }
        if ((config->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX) && config->device_type == hwType)
        {
            hw_pix_fmt = config->pix_fmt;
            break;
        }
    }
    // 3设置编解码器获取硬件像素格式的回调函数
    vCodecCtx->get_format = custom_get_format;
    // 4.创建硬件上下文
    if (av_hwdevice_ctx_create(&hwCtx, hwType, NULL, NULL, 0) < 0)
        printf("failed to create device context\n");
    vCodecCtx->hw_device_ctx = av_buffer_ref(hwCtx);
    //*##############################################################

    // 赋值编解码上下文并打开编解码器
    AVCodecParameters *vCodecPar = fmtCtx->streams[vIndex]->codecpar;
    avcodec_parameters_to_context(vCodecCtx, vCodecPar);
    avcodec_open2(vCodecCtx, vCodec, NULL);

    // 为packet及其数据区分配空间
    AVPacket *packet = av_packet_alloc();
    av_new_packet(packet, vCodecCtx->width * vCodecCtx->height);

    // 为帧分配空间
    AVFrame *yuvFrame = av_frame_alloc();
    AVFrame *hwFrame = av_frame_alloc();
    AVFrame *tmpFrame = NULL; // 临时指针,用于指向yuvFrame或者hwFrame
    // 创建音频解码线程
    std::thread decode(au_decode, customPath);

    // 生成纹理
    int width = vCodecCtx->width;
    int height = vCodecCtx->height;
    image_Y.Generate(width, height, NULL);
    image_U.Generate(width / 2, height / 2, NULL);
    image_V.Generate(width / 2, height / 2, NULL);
    image_UV.Generate(width / 2, height / 2, NULL);
    // 渲染视频
    int count = 0;
    int fps = (float)fmtCtx->streams[vIndex]->avg_frame_rate.num / fmtCtx->streams[vIndex]->avg_frame_rate.den + 0.5f;
    int duration = 1000 / fps;
    int duration_first = duration + 1000 % fps;
    while (1)
    {
        mutex.lock();
#ifdef USE_SDL
        SDL_PollEvent(&sdlEvent);
        if (sdlEvent.type == SDL_QUIT)
        {
            start_or_quit = false;
            break;
        }
        else if (sdlEvent.type == SDL_WINDOWEVENT)
        {
            if (sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                glViewport(0, 0, sdlEvent.window.data1, sdlEvent.window.data2);
        }
#else
        glfwPollEvents();
        if (glfwWindowShouldClose(window))
        {
            start_or_quit = false;
            break;
        }
#endif
        mutex.unlock();
        if (av_read_frame(fmtCtx, packet) >= 0)
        {
            if (packet->stream_index == vIndex)
            {
                count++;
                if (avcodec_send_packet(vCodecCtx, packet) == 0)
                {
                    while (avcodec_receive_frame(vCodecCtx, yuvFrame) == 0) // while循环统一线程
                    {
                        if (hwDecode)
                        {
                            if (av_hwframe_transfer_data(hwFrame, yuvFrame, 0) < 0)
                                printf("failed to transfer data from gpu to memory\n");
                            tmpFrame = hwFrame;
                            glActiveTexture(GL_TEXTURE0);
                            image_Y.Bind();
                            glTexImage2D(GL_TEXTURE_2D, 0, image_Y.internalFormat, image_Y.width, image_Y.height, 0, image_Y.imageFormat, GL_UNSIGNED_BYTE, tmpFrame->data[0]);
                            glActiveTexture(GL_TEXTURE3);
                            image_UV.Bind();
                            glTexImage2D(GL_TEXTURE_2D, 0, image_UV.internalFormat, image_UV.width, image_UV.height, 0, image_UV.imageFormat, GL_UNSIGNED_BYTE, tmpFrame->data[1]);
                        }
                        else
                        {

                            tmpFrame = yuvFrame;
                            glActiveTexture(GL_TEXTURE0);
                            image_Y.Bind();
                            glTexImage2D(GL_TEXTURE_2D, 0, image_Y.internalFormat, image_Y.width, image_Y.height, 0, image_Y.imageFormat, GL_UNSIGNED_BYTE, tmpFrame->data[0]);
                            glActiveTexture(GL_TEXTURE1);
                            image_U.Bind();
                            glTexImage2D(GL_TEXTURE_2D, 0, image_U.internalFormat, image_U.width, image_U.height, 0, image_U.imageFormat, GL_UNSIGNED_BYTE, tmpFrame->data[1]);
                            glActiveTexture(GL_TEXTURE2);
                            image_V.Bind();
                            glTexImage2D(GL_TEXTURE_2D, 0, image_V.internalFormat, image_V.width, image_V.height, 0, image_V.imageFormat, GL_UNSIGNED_BYTE, tmpFrame->data[2]);
                        }
                        videoShader.unfm1i("format", tmpFrame->format);
                        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                        glClear(GL_COLOR_BUFFER_BIT);
                        static int isFirst = 1;
                        if (!isFirst)
                            render(videoShader);
                        if (isFirst)
                        {
                            start_or_quit = true;
                            isFirst = 0;
                        }
                    }
                    frame_sleep(duration, duration_first, fps);
#ifdef USE_SDL
                    setFPS(sdl_window);
#else
                    setFPS(window);
#endif
                }
            }
            av_packet_unref(packet); // 清空数据区
        }
        else
        {
            start_or_quit = false;
            break; // 如果不能读取帧了就退出循环
        }
#ifdef USE_SDL
        SDL_GL_SwapWindow(sdl_window);
#else
        glfwSwapBuffers(window);
#endif
    }
    decode.join();
    printf("total frames:%d\n", count);
    // 释放内存
    av_packet_free(&packet);
    avcodec_free_context(&vCodecCtx);
    avformat_free_context(fmtCtx);
    av_frame_free(&yuvFrame);
    av_frame_free(&hwFrame);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
// 关闭窗口
#ifdef USE_SDL
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
#else
    glfwDestroyWindow(window);
    glfwTerminate();
#endif
    return 0;
}
// 渲染
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
// 保持帧间隔不变
inline void frame_sleep(int duration, int duration_first, int fps)
{
    static int fpsCount = 0;
    static auto lastTime = std::chrono::high_resolution_clock::now();
    auto fpsTime = std::chrono::milliseconds(fpsCount ? duration : duration_first);
    std::this_thread::sleep_for(lastTime - std::chrono::high_resolution_clock::now() + fpsTime);
    lastTime = std::chrono::high_resolution_clock::now();
    fpsCount = (fpsCount + 1) % fps;
}
// 设置帧率
void setFPS(void *window)
{
    static int fpsCount = 0;
    fpsCount++;
    static auto lastTime = std::chrono::high_resolution_clock::now();
    auto curTime = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(curTime - lastTime).count() >= 1000)
    {
        lastTime = curTime;
#ifdef USE_SDL
        SDL_SetWindowTitle((SDL_Window *)window, ("Media Player   FPS:" + std::to_string(fpsCount)).c_str());
#else
        glfwSetWindowTitle((GLFWwindow *)window, ("Media Player   FPS:" + std::to_string(fpsCount)).c_str());
#endif
        fpsCount = 0;
    }
}
// 用于编解码上下文的get_format回调函数
static enum AVPixelFormat custom_get_format(AVCodecContext *vCodecCtx, const enum AVPixelFormat *pix_fmt)
{
    const enum AVPixelFormat *ptr;
    for (ptr = pix_fmt; *ptr != -1; ptr++)
    {
        if (*ptr == hw_pix_fmt)
            return *ptr;
    }
    printf("failed to get hw_format\n");
    return AV_PIX_FMT_NONE;
}
// 初始化glfw
void glfw_init_window()
{
    //*---------GLFW初始化部分---------*//
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // glfwWindowHint(GLFW_RESIZABLE, false);
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Media Player", NULL, NULL);
    if (window == NULL)
    {
        printf("failed to create window\n");
        glfwTerminate();
        return;
    }
    // // 获取主显示器的视频模式
    // const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    // // 切换到全屏模式
    // glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("ERROR::GLAD failed to load the proc\n");
        return;
    }
}
void sdl_init_window()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
    {
        fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // 创建SDL Window
    sdl_window = SDL_CreateWindow("Media Player", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!sdl_window)
    {
        fprintf(stderr, "\nSDL: could not set video mode:%s - exiting\n", SDL_GetError());
        exit(1);
    }
    SDL_GL_CreateContext(sdl_window);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        printf("ERROR::GLAD failed to load the proc\n");
        return;
    }
    // SDL_Renderer *renderer = SDL_CreateRenderer(sdl_window, -1, 0);
}
// 音频设备需要更多数据的时候会调用该回调函数
void read_audio_data(void *udata, Uint8 *stream, int len) // udata就是spec.userdata
{
    // 首先使用SDL_memset()将stream中的数据设置为0
    SDL_memset(stream, 0, len);
    if (audio_len == 0)
        return;
    len = (len > audio_len ? audio_len : len);

    SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
    audio_pos += len;
    audio_len -= len;
}
FMOD_RESULT F_CALLBACK fmod_read_data(FMOD_SOUND * /*sound*/, void *data, unsigned int datalen)
{
    if (audio_len == 0)
        return FMOD_OK;
    datalen = (datalen > audio_len ? audio_len : datalen);
    memcpy(data, audio_pos, datalen);
    audio_pos += datalen;
    audio_len -= datalen;
    return FMOD_OK;
}
void au_decode(const char *path)
{
    // avformat
    AVFormatContext *fmtCtx = avformat_alloc_context();
    if (avformat_open_input(&fmtCtx, path, NULL, NULL))
        printf("failed to open the path:%s\n", path);
    if (avformat_find_stream_info(fmtCtx, NULL) < 0)
        printf("no stream info in path:%s\n", path);
    // find decoder
    int aIndex = -1;
    const AVCodec *aDecoder = NULL;
    aIndex = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, &aDecoder, 0);
    if (aIndex == -1)
        printf("failed to find the best stream in func:%s,line:%d", __FUNCTION__, __LINE__);
    // open decoder
    AVCodecContext *aCodecCtx = avcodec_alloc_context3(aDecoder);
    AVCodecParameters *par = fmtCtx->streams[aIndex]->codecpar;
    avcodec_parameters_to_context(aCodecCtx, par);
    if (avcodec_open2(aCodecCtx, aDecoder, NULL) < 0)
        printf("failed to open the audio decoder\n");
    // 设置转换参数
    int out_nb_samples = 1024;
    int out_nb_channels = 2;
    int out_sample_rate = 48000;
    AVChannelLayout out_ch_layout = AV_CHANNEL_LAYOUT_STEREO;
    AVSampleFormat out_sample_format = AV_SAMPLE_FMT_S16;
    AVChannelLayout in_ch_layout = {};
    av_channel_layout_default(&in_ch_layout, aCodecCtx->ch_layout.nb_channels);
    // 设置转换上下文
    SwrContext *swrCtx = NULL;
    swr_alloc_set_opts2(
        &swrCtx, &out_ch_layout, out_sample_format, out_sample_rate,
        &aCodecCtx->ch_layout, aCodecCtx->sample_fmt, aCodecCtx->sample_rate, 0, NULL);
    swr_init(swrCtx);
    // 分配容器空间
    AVFrame *aFrame = av_frame_alloc();
    AVPacket *packet = av_packet_alloc();
    int bufferSize = av_samples_get_buffer_size(NULL, out_nb_channels, out_nb_samples, out_sample_format, 1);
    unsigned char *buffer = (unsigned char *)av_malloc(bufferSize);
#ifndef USE_SDL
    // 设置FMOD参数
    FMOD_CREATESOUNDEXINFO exinfo;
    memset(&exinfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    exinfo.decodebuffersize = out_nb_samples;
    exinfo.defaultfrequency = out_sample_rate;
    exinfo.format = FMOD_SOUND_FORMAT_PCM16;
    exinfo.length = out_sample_rate * sizeof(short) * out_nb_channels * 5; // '5'代表5秒
    exinfo.numchannels = out_nb_channels;
    exinfo.pcmreadcallback = fmod_read_data;
    SoundManager *sound = new SoundManager(32);
    sound->loadSound(NULL, "bgm", FMOD_CREATESTREAM | FMOD_OPENUSER | FMOD_LOOP_NORMAL, &exinfo);
    while (!start_or_quit)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    sound->playSound("bgm", 0);
#else
    // SDL音频参数
    SDL_AudioSpec spec;
    spec.freq = out_sample_rate;
    spec.format = AUDIO_S16SYS;
    spec.channels = out_nb_channels;
    spec.silence = 0;
    spec.samples = out_nb_samples;
    spec.callback = read_audio_data;
    spec.userdata = NULL;
    // 打开SDL音频
    if (SDL_OpenAudio(&spec, NULL) < 0)
    {
        printf("can't open audio.\n");
        return;
    }
    while (!start_or_quit)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    // 设置为0表示开始播放
    SDL_PauseAudio(0);
#endif

    while (start_or_quit)
    {
#ifndef USE_SDL
        sound->pauseGroup(0, true);
#else
        SDL_PauseAudio(true);
#endif
        mutex.lock();
#ifndef USE_SDL
        sound->pauseGroup(0, false);
#else
        SDL_PauseAudio(false);
#endif
        mutex.unlock();
        if (av_read_frame(fmtCtx, packet) >= 0)
        {
            if (packet->stream_index == aIndex)
            {
                avcodec_send_packet(aCodecCtx, packet);
                while (avcodec_receive_frame(aCodecCtx, aFrame) == 0)
                {
                    swr_convert(
                        swrCtx, &buffer, out_nb_samples,
                        (const uint8_t **)aFrame->data, aFrame->nb_samples);
                }
                audio_chunk = buffer;
                audio_len = bufferSize;
                audio_pos = audio_chunk;
                while (audio_len > 0)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }
            av_packet_unref(packet);
        }
#ifndef USE_SDL
        sound->update();
#endif
    }

    // 清除空间
#ifndef USE_SDL
    delete sound;
#endif
    avformat_free_context(fmtCtx);
    avcodec_free_context(&aCodecCtx);
    av_frame_free(&aFrame);
    av_packet_free(&packet);
    av_free(buffer);
    swr_free(&swrCtx);
}