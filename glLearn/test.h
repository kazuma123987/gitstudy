#ifndef _TEST_H_
#define _TEST_H_
#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
#include <stdint.h>  //uint16_t,int8_t..B.
#include <time.h>    //time(),time_t,ctime
#include <stdint.h>
#include <math.h>
#include <windows.h> //Sleep()
#include <conio.h>   //kbhit(),_getch()
#include <mmsystem.h>
#include "fmod/fmod.h"
#include "glad/glad.h"  //glad.h必须放在glfw3.h前面，glad可以查找gl、glu、glex、wgl、glx的函数指针以方便调用其函数
#include "GLFW/glfw3.h" //轻量级跨平台工具库，提供渲染物体最低限度的API（管理窗口、读取输入、处理事件）
#define PI 3.1415926536
static FMOD_CHANNEL *sharedChannel;
class Shader
{
public:
    unsigned int shaderProgram;
    Shader(const char *vpath, const char *fpath)
    {
        // 文件操作
        const int FileName_Size = 128;
        FILE *fp1 = fopen(vpath, "rb");
        if (!fp1)
            fputs("\nfailed to open the path of vertexShader", stderr);
        FILE *fp2 = fopen(fpath, "rb");
        if (!fp1)
            fputs("\nfailed to open the path of fragmentShader", stderr);
        fseek(fp1, 0, SEEK_END);
        long size1 = ftell(fp1);
        fseek(fp2, 0, SEEK_END);
        long size2 = ftell(fp2);
        char *code1 = (char *)malloc(size1 + 1);
        char *code2 = (char *)malloc(size2 + 1);
        rewind(fp1);
        rewind(fp2);
        size_t readSize1 = fread(code1, sizeof(char), size1, fp1);
        if (readSize1 < size1)
            fputs("\nfailed to read the file", stderr);
        code1[size1] = '\0';
        size_t readSize2 = fread(code2, sizeof(char), size2, fp2);
        if (readSize2 < size2)
            fputs("\nfailed to read the file", stderr);
        code2[size2] = '\0';
        fclose(fp1);
        fclose(fp2);
        // 顶点着色器
        GLuint vsh = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vsh, 1, &code1, NULL);
        glCompileShader(vsh);
        int flag_v = 1;
        char infolog[512];
        glGetShaderiv(vsh, GL_COMPILE_STATUS, &flag_v);
        if (!flag_v)
        {
            glGetShaderInfoLog(vsh, 512, NULL, infolog);
            fputs(infolog, stderr);
        }
        free(code1);
        // 片段着色器
        GLuint fsh = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fsh, 1, &code2, NULL);
        glCompileShader(fsh);
        int flag_f = 1;
        glGetShaderiv(fsh, GL_COMPILE_STATUS, &flag_f);
        if (!flag_f)
        {
            glGetShaderInfoLog(fsh, 512, NULL, infolog);
            fputs(infolog, stderr);
        }
        free(code2);
        // 着色器程序
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vsh);
        glAttachShader(shaderProgram, fsh);
        glLinkProgram(shaderProgram);
        int flag_p = 1;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &flag_p);
        if (!flag_p)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
            fputs(infolog, stderr);
        }
        glDeleteShader(vsh);
        glDeleteShader(fsh);
    }

    void use()
    {
        glUseProgram(shaderProgram);
    }
    void unfm1f(const char *str, float value) const
    {
        glUniform1f(glGetUniformLocation(shaderProgram, str), value);
    }
    void unfm1i(const char *str, float value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgram, str), value);
    }
    void unfm3f(const char *str, float a, float b, float c)
    {
        glUniform3f(glGetUniformLocation(shaderProgram, str), a, b, c);
    }
};
typedef struct FMODSOUND
{
    FMOD_SOUND *sound;
    FMOD_CHANNEL *channel;
} FMODSOUND;
class FMODMUSIC
{
public:
    FMOD_SYSTEM *system;
    void init()
    {
        FMOD_RESULT result = FMOD_System_Create(&system, FMOD_VERSION);
        if (result != FMOD_OK)
        {
            fputs("\nfailed to create system", stderr);
            return;
        }
        result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
        if (result != FMOD_OK)
        {
            fputs("\nfailed to init system", stderr);
            FMOD_System_Release(system);
            return;
        }
    }
    void loadMusic(FMODSOUND *s, const char *bgm)
    {
        FMOD_RESULT result = FMOD_System_CreateSound(system, bgm, FMOD_DEFAULT, NULL, &s->sound);
        if (result != FMOD_OK)
            fputs("\nfailed to load the music", stderr);
    }
    void playMusic(FMODSOUND *s,bool share_flag=false)
    {

        FMOD_RESULT result;
        static int isplaying;
        FMOD_Channel_IsPlaying(s->channel, &isplaying);
        if (!isplaying)
        {
            result = FMOD_System_PlaySound(system, s->sound, NULL, FALSE, &s->channel);
            if (result != FMOD_OK)
                fputs("\nfailed to play music", stderr);
        }
        else if(share_flag)
        {
            result = FMOD_System_PlaySound(system, s->sound, NULL, FALSE, &sharedChannel);
            if (result != FMOD_OK)
                fputs("\nfailed to play music", stderr);
        }
    }
    void setSoundMode(FMOD_MODE mode, FMODSOUND *s)
    {
        FMOD_Sound_SetMode(s->sound, mode);
    }
    void set3DPosition(FMODSOUND *s, float x, float y, float z)
    {
        if (s!=NULL)
        {
            FMOD_VECTOR pos;
            pos.x = x;
            pos.y = y;
            pos.z = z;
            FMOD_Channel_Set3DAttributes(s->channel, &pos, NULL);
        }
    }
    void updateSystem()
    {
        FMOD_System_Update(system);
    }
    void systemFree()
    {
        FMOD_System_Release(system);
    }
};
#endif