#ifndef __GAME__H
#define __GAME__H
#include <tool.h>
#include <global.h>
#include <sound.h>
#include <shader.h>
#include <mesh.h>
#include <model.h>
#include <frameBuffer.h>
#include <fonts.h>
void utf8_to_wchar(wchar_t *dst, size_t dstlen, char *src);
glm::vec3 getPoint(GLfloat radius, GLfloat u, GLfloat v);
void createSphere(GLfloat *sphere, GLfloat radius, GLuint Longitude, GLuint Latitude);
class Game
{
public:
    // 用于四边形(quad)绘制的VAO/VBO
    GLuint quadVAO = 0;
    GLuint quadVBO;
    GLuint noiseMap;
    std::vector<glm::vec3> ssaoSamples;
    Fonts *font;
    // GUI变量
    bool drawRock = true;
    bool skyBox_ON = false;
    bool dirLight_ON = true;
    bool dotLight_ON = true;
    bool spotLight_ON = false;
    bool ssao_ON = false;
    float height_scale = 0.1f;
    int blurCount = 1;
    int kernelSize = 64;
    float kernelRadius = 0.5f;
    char textBuffer[4096] = "InputText";
    wchar_t wtestBuffer[4096] = {0};
    float textScale = 1.0f;
    float text_thickness = 0.5f;
    float text_softness = 0.0f;
    float outline_thickness = 0.5f;
    float outline_softness = 0.0f;
    glm::vec3 textColor = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 outlineColor = glm::vec3(1.0f);
    // 着色器
    Shader *cubeShader;
    Shader *modelShader;
    Shader *lightShader;
    Shader *outlineShader;
    Shader *screenShader;
    Shader *skyboxShader;
    Shader *instantShader;
    Shader *depthShader;
    Shader *depthCubeShader;
    Shader *blurShader;
    Shader *twoTexShader;
    Shader *gBufferShader;
    Shader *deferredShader;
    Shader *ssaoShader;
    Shader *simpleBlurShader;
    Shader *fontShader;
    Shader *ballShader;
    // 模型和网格
    Mesh *box;
    Mesh *wall;
    Mesh *redWall;
    Mesh *toyBox;
    Mesh *ground;
    Mesh *light;
    Mesh *skybox;
    Mesh *sphere;
    Model *human;
    Model *rock;
    const int rockNum = 100000;
    glm::mat4 boxMat[10];
    glm::mat4 humanMat = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
    glm::mat4 *rockMat;
    const float near_plane = 0.1f;
    const float far_plane = 100.0f;
    // 光源矩阵
    glm::mat4 unitMat = glm::mat4(1.0f);
    glm::vec3 lightPos = glm::vec3(0.0f, 4.0f, 3.0f);
    // dirLight
    DirectLight dirLight = {glm::vec3(2.0f, -8.0f, 1.0f), glm::vec3(0.1f), glm::vec3(0.1f), glm::vec3(0.01f)};
    glm::mat4 dirShadowSpaceMat = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane) * glm::lookAt(-dirLight.dir, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    // dotLight
    glm::vec3 dotColor = glm::vec3(1.0f);
    DotLight dotLight = {lightPos, 0.02f * dotColor, 0.5f * dotColor, dotColor, 1.0f, 0.09f, 0.032f};
    glm::mat4 dotLightMat = glm::translate(unitMat, dotLight.pos);
    glm::mat4 dotShadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
    glm::mat4 dotShadowMat[6];
    // spotLight
    glm::vec3 spotColor = glm::vec3(1.0f);
    SpotLight spotLight = {glm::vec3(0.0f), glm::vec3(0.01f), glm::vec3(0.7f), glm::vec3(1.0f), 1.0f, 0.09f, 0.032f,
                           glm::cos(glm::radians(15.0f)), glm::cos(glm::radians(17.5f)), glm::vec3(0.0f, 0.0f, -1.0f)};
    glm::mat4 spotShadowSpaceMat;
    // 帧缓冲对象（当纹理预分配空间(imageData=NULL)且绑定对象不存在时纹理的缓冲区也会随之消失
    // 例如声明全局变量FrameBuffer a,b;令FrameBuffer test(WIDTH,HEIGHT);a=test;则a拷贝过来的纹理缓冲会在test生命结束时被释放
    // 同时若a=FrameBuffer(WIDTH,HEIGHT);n=FrameBuffer(WIDTH,HEIGHT);则a和b的纹理缓冲始终是同一个
    // 因为纹理缓冲的分配规则:若当前最新纹理缓冲有数据,则不论绑定对象是否存在,都可以通过ID查找,分配新纹理时默认ID为当前最新ID+1
    // 若当前最新纹理缓冲没有数据,只要绑定对象存在,就不会主动释放内存,若绑定对象不存在,则会主动释放内存,分配的新纹理ID与对象作用域有关
    FrameBuffer *finalFBO;
    FrameBuffer *texFBO;
    FrameBuffer *twoTexFBO;
    FrameBuffer *pingpongFBO;
    FrameBuffer *shadowFBO;
    FrameBuffer *spotShadowFBO;
    FrameBuffer *gBufferFBO;
    FrameBuffer *ssaoFBO;
    FrameBuffer *ssaoBlurFBO;
    Game(){};
    ~Game()
    {
        game_free();
    };
    uint8_t init(void);
    uint8_t glfw_init(void);
    void imgui_init();
    void global_init();
    void game_free();
    void update();
    void rendGUI();
    void rendFPS(GLFWwindow *window);
    void rendShadowMap();
    void rendGBuffer();
    void deferredRend();
    void postRend();
    void drawQuad();
};
#endif