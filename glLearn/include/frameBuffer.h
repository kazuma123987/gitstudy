#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_
#include <tool.h>
#include <shader.h>
//注意在渲染循环中先绑定多重采样帧缓冲对象再进行常规渲染,再把多重采样帧缓冲对象的颜色缓冲、深度缓冲、模板缓冲还原到屏幕空间帧缓冲
//帧缓冲对象
class FrameBuffer
{
public:
    FrameBuffer(int width, int height)
    {
        this->width=width;
        this->height=height;
        // 帧缓冲对象(FrameBuffer Object)
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        // 用纹理创建颜色帧缓冲
        glGenTextures(1, &TEXTURE);
        glBindTexture(GL_TEXTURE_2D, TEXTURE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); // 生成了缓存空间但没有填充数据
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TEXTURE, 0);
        // 用渲染缓冲对象RBO(RenderBuffer Object)创建深度与模板缓冲(深度24bit,模板8bit),不同于纹理缓冲,RBO的
        // 缓冲区专门为帧缓冲设计
        glGenRenderbuffers(1, &RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // 创建缓存区存放width*height个点的depth与stencil值
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
        // 检查帧缓冲是否完整
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            fputs("The screen frameBuffer is not complete", stderr);
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // 解除帧缓冲的绑定,防止误操作

        //多重采样帧缓冲(MSAA多重采样抗锯齿)
        glGenFramebuffers(1,&MFBO);
        glBindFramebuffer(GL_FRAMEBUFFER,MFBO);
        //多重采样纹理
        glGenTextures(1,&MTEXTURE);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,MTEXTURE);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,4,GL_RGB,width,height,GL_TRUE);
        glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE,0);
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D_MULTISAMPLE,MTEXTURE,0);
        //多重采样渲染缓冲
        glGenRenderbuffers(1, &MRBO);
        glBindRenderbuffer(GL_RENDERBUFFER,MRBO);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER,4,GL_DEPTH24_STENCIL8,width,height);
        glBindRenderbuffer(GL_RENDERBUFFER,0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,MRBO);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
            fputs("The mutisampler frameBuffer is not complete", stderr);
        glBindFramebuffer(GL_FRAMEBUFFER,0);

        //用于阴影贴图的帧缓冲(不包含颜色信息)
        glGenFramebuffers(1,&SFBO);
        glBindFramebuffer(GL_FRAMEBUFFER,SFBO);
        //深度与模板纹理
        glGenTextures(1,&STEXTURE_DEPTH_STENCIL);
        glBindTexture(GL_TEXTURE_2D,STEXTURE_DEPTH_STENCIL);
        glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,width,height,0,GL_DEPTH_COMPONENT,GL_FLOAT,NULL);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };//注意设置阴影贴图的边缘颜色
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
        glBindTexture(GL_TEXTURE_2D,0);
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,STEXTURE_DEPTH_STENCIL,0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
            fputs("The shadow frameBuffer is not complete", stderr);
        glBindFramebuffer(GL_FRAMEBUFFER,0);

        float vertex[] =
            {
                -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom-left
                1.0f, -1.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
                1.0f, 1.0f, 1.0f, 1.0f, 1.0f,   // top-right
                1.0f, 1.0f, 1.0f, 1.0f, 1.0f,   // top-right
                -1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  // top-left
                -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom-left
            };
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindVertexArray(0);
    }
    ~FrameBuffer()
    {
        destoyFBO();
    }
    void bindMFBO()
    {
        glViewport(0,0,width,height);
        glBindFramebuffer(GL_FRAMEBUFFER, MFBO);
    }
    void bindFBO()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    }
    void bindSFBO()
    {
        glViewport(0,0,width,height);
        glBindFramebuffer(GL_FRAMEBUFFER, SFBO);
    }
    void unBind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void bindSTexture(Shader *shader,const char *name,int index=0)
    {
        shader->unfm1i(name,index);
        glActiveTexture(GL_TEXTURE0+index);
        glBindTexture(GL_TEXTURE_2D,STEXTURE_DEPTH_STENCIL);
    }
    void Draw(Shader *shader)
    {
        //先把多重采样帧缓冲的颜色缓冲、深度缓冲、模板缓冲(缓冲区大小是采样点个数倍)还原到一般的帧缓冲
        glBindFramebuffer(GL_READ_FRAMEBUFFER,MFBO);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER,FBO);
        glBlitFramebuffer(0,0,width,height,0,0,width,height,GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT,GL_NEAREST);
        //画屏幕空间
        shader->use();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);//注意要先绑定默认帧缓冲再清除对应的缓冲区
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, TEXTURE);//片段着色器sampler2D对应的是GL_TEXTURE_2D纹理
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    void destoyFBO()
    {
        glDeleteRenderbuffers(1, &RBO);
        glDeleteRenderbuffers(1, &MRBO);
        glDeleteFramebuffers(1, &FBO);
        glDeleteFramebuffers(1, &MFBO);
        glDeleteFramebuffers(1, &SFBO);
        glDeleteTextures(1, &TEXTURE);
        glDeleteTextures(1, &MTEXTURE);
        glDeleteTextures(1, &STEXTURE_DEPTH_STENCIL);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

private:
    int width,height;
    GLuint VAO, VBO;
    GLuint FBO, RBO, TEXTURE;
    GLuint MFBO, MRBO, MTEXTURE;
    GLuint SFBO,STEXTURE_DEPTH_STENCIL;
};
#endif