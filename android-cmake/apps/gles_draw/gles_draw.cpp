#include <iostream>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

// 顶点着色器
const char *vertexShaderSource = R"(
    attribute vec4 aPosition;
    void main() {
        gl_Position = aPosition;
    }
)";

// 片段着色器
const char *fragmentShaderSource = R"(
    precision mediump float;
    void main() {
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
)";

int main()
{
    const EGLint configAttribs[] = {EGL_RENDERABLE_TYPE, EGL_WINDOW_BIT,
                                    EGL_RED_SIZE, 8,
                                    EGL_GREEN_SIZE, 8,
                                    EGL_BLUE_SIZE, 8,
                                    EGL_DEPTH_SIZE, 24,
                                    EGL_NONE};

    const EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    // 初始化 EGL 环境
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    EGLBoolean ret = eglInitialize(display, nullptr, nullptr);
    if (ret != EGL_TRUE)
        std::cout << "egl创建窗口失败" << std::endl;

    // 设置 EGL 配置
    EGLConfig config;
    EGLint numConfigs;
    ret = eglChooseConfig(display, configAttribs, &config, 1, &numConfigs);
    if (ret != EGL_TRUE)
        std::cout << "egl配置失败" << std::endl;

    // 创建 EGL 上下文
    EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);

    // 创建 EGL 窗口表面
    // EGLNativeWindowType window = ANativeWindow_fromSurface(env, surface);
    EGLNativeWindowType eglwindow = nullptr; // !注意这里的window应该是JINI上层传过来的，所以接下来不会正确创建窗口
    EGLSurface surface = eglCreateWindowSurface(display, config, eglwindow, nullptr);

    // 使 EGL 上下文成为当前上下文
    eglMakeCurrent(display, surface, surface, context);

    // 编译和链接着色器程序
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glUseProgram(program);

    // 设置顶点数据
    GLfloat vertices[] = {
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f};

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLint positionAttribute = glGetAttribLocation(program, "aPosition");
    glEnableVertexAttribArray(positionAttribute);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // 绘制红色三角形
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // 显示绘制结果
    eglSwapBuffers(display, surface);

    // 等待用户输入
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();

    // 清理资源
    glDeleteProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteBuffers(1, &vbo);
    eglDestroySurface(display, surface);
    eglDestroyContext(display, context);
    eglTerminate(display);

    return 0;
}