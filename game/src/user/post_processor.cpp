#include "post_processor.h"
PostProcessor::PostProcessor(Shader &shader, int width, int height)
    : shader(shader), texture(), width(width), height(height), chaos(false), confuse(false), shake(false)
{
    // FBO的生成
    glGenFramebuffers(1, &this->FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
    this->texture.Generate(width, height, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->texture.ID, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("failed to init FBO\n");
    // MFBO的生成
    glGenFramebuffers(1, &this->MFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, this->MFBO);
    glGenRenderbuffers(1, &MRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, MRBO);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_RGB, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, MRBO);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("failed to init MFBO\n");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // 初始化数据
    InitData();
}
PostProcessor::~PostProcessor()
{
    glDeleteFramebuffers(1, &this->MFBO);
    glDeleteFramebuffers(1, &this->FBO);
    glDeleteRenderbuffers(1, &this->MRBO);
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}
void PostProcessor::BindMFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->MFBO);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void PostProcessor::Copy_MFBO_To_FBO()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, this->MFBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->FBO);
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}
void PostProcessor::Draw()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader.Use();
    shader.unfm1f("time", glfwGetTime());
    shader.unfm1i("chaos", this->chaos);
    shader.unfm1i("confuse", this->confuse);
    shader.unfm1i("shake", this->shake);
    glActiveTexture(GL_TEXTURE0);
    this->texture.Bind();
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
void PostProcessor::InitData()
{
    // 生成VAO与VBO
    float vertices[] =
        {
            -1.0f, -1.0f, 0.0f, 0.0f, // 左下
            1.0f, -1.0f, 1.0f, 0.0f,  // 右下
            -1.0f, 1.0f, 0.0f, 1.0f,  // 左上
            1.0f, 1.0f, 1.0f, 1.0f    // 右上
        };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glBindVertexArray(0);
    // 为着色器初始化数据
    shader.Use().unfm1i("image", 0);
    float offset = 1.0f / 300.0f;
    float offsets[9][2] = {
        {-offset, offset},  // top-left
        {0.0f, offset},     // top-center
        {offset, offset},   // top-right
        {-offset, 0.0f},    // center-left
        {0.0f, 0.0f},       // center-center
        {offset, 0.0f},     // center - right
        {-offset, -offset}, // bottom-left
        {0.0f, -offset},    // bottom-center
        {offset, -offset}   // bottom-right
    };
    shader.unfvec2N("offsets", (float *)offsets, 9);
    int edge_kernel[9] = {
        -1, -1, -1,
        -1, 8, -1,
        -1, -1, -1};
    shader.unfm1iN("edge_kernel", edge_kernel, 9);
    float blur_kernel[9] = {
        1.0 / 16, 2.0 / 16, 1.0 / 16,
        2.0 / 16, 4.0 / 16, 2.0 / 16,
        1.0 / 16, 2.0 / 16, 1.0 / 16};
    shader.unfm1fN("blur_kernel", blur_kernel, 9);
}