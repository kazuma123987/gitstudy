#include "renderer.h"
#include "resource_manager.h"
#include <vector>
extern int winWidth;
extern int winHeight;
const int numSegments = 100;
Renderer::Renderer()
{
    glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(winWidth), 0.0f, static_cast<float>(winHeight), -1.0f, 1.0f);
    this->solidShader = ResourceManager::getShader("solid").Use();
    this->solidShader.unfmat4("proj", proj);
    this->spriteShader = ResourceManager::getShader("sprite").Use();
    this->spriteShader.unfmat4("proj", proj);
    initRender();
}
Renderer::~Renderer()
{
    glDeleteBuffers(1, &quadVBO);
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &circleVBO);
    glDeleteVertexArrays(1, &circleVAO);
    glDeleteBuffers(1, &offsetVBO);
    glDeleteBuffers(1, &scaleVBO);
    glDeleteBuffers(1, &colorVBO);
}
/**
 * @brief 绘制精灵/纹理
 *
 * @param texture 纹理引用
 * @param position 位置以左下角计算,缩放以图片左下角为中心,旋转角度正数为逆时针
 * @param size 纹理大小
 * @param rotate 旋转角度
 * @param spriteColor 纹理颜色
 * @param darker 纹理颜色加深程度,1.0为正常颜色
 */
void Renderer::DrawSprite(Texture &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec4 spriteColor, float darker)
{
    this->spriteShader.Use();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size, 0.0f)); // 把旋转中心从position移动至position+size/2
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size, 0.0f)); // 旋转后别忘了移动回来
    model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));   // 以position点(左下角)为中心缩放
    this->spriteShader.unfmat4("model", model);
    this->spriteShader.unfvec4("spriteColor", spriteColor);
    this->spriteShader.unfm1f("darker", darker);
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

/**
 * @brief 绘制实心圆
 *
 * @param position 圆心位置
 * @param radius 圆半径
 * @param color 圆颜色
 */
void Renderer::DrawCircle(glm::vec2 position, float radius, glm::vec4 color)
{
    // 使用着色器程序
    this->solidShader.Use();

    // 设置 uniform 变量
    this->solidShader.unfvec2("offset", position);
    this->solidShader.unfm1f("scale", radius);
    this->solidShader.unfvec4("solidColor", color);

    // 绘制圆形
    glBindVertexArray(circleVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments + 2);
    glBindVertexArray(0);
}

void Renderer::DrawCircleInstance(std::vector<glm::vec2> &offsets, std::vector<float> &scales, std::vector<glm::vec4> &colors)
{
    glBindVertexArray(this->circleVAO);

    // 绑定并填充偏移缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, this->offsetVBO);
    glBufferData(GL_ARRAY_BUFFER, offsets.size() * sizeof(glm::vec2), offsets.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);

    // 绑定并填充缩放缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, this->scaleVBO);
    glBufferData(GL_ARRAY_BUFFER, scales.size() * sizeof(float), scales.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1);

    // 绑定并填充颜色缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, this->colorVBO);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4), colors.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);

    // 使用着色器并绘制实例化的圆形
    this->solidShader.Use();
    glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, numSegments + 2, offsets.size());

    // 清理
    glBindVertexArray(0);
}

void Renderer::initRender()
{
    {
        // 这里的坐标乘以正交投影矩阵后单位变为像素,需要通过scale变换放大
        float vertices[] =
            {
                0.0f, 0.0f, 0.0f, 0.0f, // 左下
                1.0f, 0.0f, 1.0f, 0.0f, // 右下
                0.0f, 1.0f, 0.0f, 1.0f, // 左上
                1.0f, 1.0f, 1.0f, 1.0f  // 右上
            };
        this->spriteShader.Use();
        glGenVertexArrays(1, &quadVAO);
        glBindVertexArray(quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
        glBindVertexArray(0);
    }

    {
        // 生成单位圆顶点数据
        static std::vector<glm::vec2> s_vertices(numSegments + 2);
        s_vertices[0] = glm::vec2(0.0f, 0.0f); // 圆心
        for (int i = 0; i <= numSegments + 1; ++i)
        {
            float angle = i * 2.0f * 3.1415926f / numSegments;
            float dx = cosf(angle);
            float dy = sinf(angle);
            s_vertices[i + 1] = glm::vec2(dx, dy);
        }
        glGenVertexArrays(1, &circleVAO);
        glGenBuffers(1, &circleVBO);
        glBindVertexArray(circleVAO);
        glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
        glBufferData(GL_ARRAY_BUFFER, s_vertices.size() * sizeof(glm::vec2), s_vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // glVertexAttribDivisor(0, 0); // 每次绘制非实例时更新属性0
        glBindVertexArray(0);

        // 生成实例化VBO
        glGenBuffers(1, &offsetVBO);
        glGenBuffers(1, &scaleVBO);
        glGenBuffers(1, &colorVBO);
    }
}