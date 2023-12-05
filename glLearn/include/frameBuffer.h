#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_
#include <tool.h>
#include <shader.h>
class FrameBuffer
{
public:
    FrameBuffer(int width, int height)
    {
        // 帧缓冲对象(FrameBuffer Object)
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        // 用纹理创建颜色帧缓冲
        glGenTextures(1, &texColorBuffer);
        glBindTexture(GL_TEXTURE_2D, texColorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); // 生成了缓存空间但没有填充数据
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
        // 用渲染缓冲对象RBO(RenderBuffer Object)创建深度与模板缓冲(深度24bit,模板8bit),不同于纹理缓冲,RBO的
        // 缓冲区专门为帧缓冲设计
        glGenRenderbuffers(1, &RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // 创建缓存区存放width*height个点的depth与stencil值
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
        // 检查帧缓冲是否完整
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            fputs("The frameBuffer is not complete", stderr);
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // 解除帧缓冲的绑定,防止误操作

        float vertex[] =
        {
        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // bottom-left
         1.0f, -1.0f,  1.0f,  1.0f, 0.0f, // bottom-right
         1.0f,  1.0f,  1.0f,  1.0f, 1.0f, // top-right
         1.0f,  1.0f,  1.0f,  1.0f, 1.0f, // top-right
        -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, // top-left
        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // bottom-left
        };
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindVertexArray(0);
    }
    ~FrameBuffer()
    {
        destoyFBO();
    }
    void bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    }
    void unBind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void Draw(Shader *shader)
    {
        unBind();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_STENCIL_TEST);
        shader->use();
        glBindTexture(GL_TEXTURE_2D, texColorBuffer);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,30);
    }
    void destoyFBO()
    {
        glDeleteRenderbuffers(1, &RBO);
        glDeleteFramebuffers(1, &FBO);
        glDeleteTextures(1, &texColorBuffer);
        glDeleteVertexArrays(1,&VAO);
        glDeleteBuffers(1,&VBO);
    }

private:
    GLuint VAO, VBO, FBO, RBO, texColorBuffer;
};
#endif