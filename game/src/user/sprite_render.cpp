#include "sprite_render.h"
SpriteRender::SpriteRender(Shader &shader)
{
    this->shader = shader;
    initRender();
}
SpriteRender::~SpriteRender()
{
    glDeleteBuffers(1, &quadVBO);
    glDeleteVertexArrays(1, &quadVAO);
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
void SpriteRender::DrawSprite(Texture &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 spriteColor,float darker)
{
    this->shader.Use();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size, 0.0f));//把旋转中心从position移动至position+size/2
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size, 0.0f));//旋转后别忘了移动回来
    model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));//以position点(左下角)为中心缩放
    this->shader.unfmat4("model", model);
    this->shader.unfvec3("spriteColor", spriteColor);
    this->shader.unfm1f("darker",darker);
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
void SpriteRender::initRender()
{
    //这里的坐标乘以正交投影矩阵后单位变为像素,需要通过scale变换放大
    float vertices[] =
        {
            0.0f, 0.0f, 0.0f, 0.0f,//左下
            1.0f, 0.0f, 1.0f, 0.0f,//右下
            0.0f, 1.0f, 0.0f, 1.0f,//左上
            1.0f, 1.0f, 1.0f, 1.0f //右上
        };
    glGenVertexArrays(1, &quadVAO);
    glBindVertexArray(quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glBindVertexArray(0);
}