#ifndef _TOOL_H_
#define _TOOL_H_
/*---------------内部库----------------*/
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
/*---------------外部库----------------*/
//需要链接库的头文件
#include "glm/glm.hpp" //后面均为opengl提供的数学库,可以用于opengl之外的数学运算
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <fmod/fmod.h>
#include <glad/glad.h>  //glad.h必须放在glfw3.h前面，glad可以查找gl、glu、glex、wgl、glx的函数指针以方便调用其函数
#include <GLFW/glfw3.h> //轻量级跨平台工具库，提供渲染物体最低限度的API（管理窗口、读取输入、处理事件）
#include <stb_image.h>
#define PI 3.1415926536
#define WIDTH 700
#define HEIGHT 700
#endif