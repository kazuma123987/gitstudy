#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <time.h>    //time(),time_t,ctime
#include <windows.h> //Sleep()
#include <conio.h>   //kbhit(),_getch()
#define LENGTH 15
HANDLE hOutput, hBuffer; // 定义输出显示缓冲区与内部显示缓冲区
COORD coord = {0, 0};    // 定义显示的坐标
DWORD bytes = 0;
char data[LENGTH][LENGTH]; // 定义写入内部缓冲区的字符数组
void show()
{
    clock_t pre=clock();
    int count=0;
    static bool flag = FALSE;
    if (flag)
        memset(data, '-', LENGTH * LENGTH);
    else
        memset(data, '*', LENGTH * LENGTH);
    flag = !flag;
    for (int i = 0; i < LENGTH; i++)
    {
        coord.Y=i;
        WriteConsoleOutputCharacterA(hBuffer, data[i],LENGTH,coord,&bytes);
    }
    //交换缓冲区指针
    HANDLE temp=hOutput;
    hOutput=hBuffer;
    hBuffer=temp;
    //system("cls");//清屏函数设置在这里能防止屏闪
    SetConsoleActiveScreenBuffer(hOutput);
    while(1)
    {
        if(count=29&&clock()-pre>=43)//clock()是以毫秒为单位
        {
            count=0;
            break;
        }
        else if(clock()-pre>=33)
        {
            count++;
            break;
        }
    }
}
int main(int argc, char *argv[])
{
    //创建显示缓冲区
    hOutput = CreateConsoleScreenBuffer(
        GENERIC_WRITE,    // 进程可以往缓冲区写数据
        FILE_SHARE_WRITE, // 缓冲区可共享写权限
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL);
    hBuffer = CreateConsoleScreenBuffer(
        GENERIC_WRITE,    // 进程可以往缓冲区写数据
        FILE_SHARE_WRITE, // 缓冲区可共享写权限
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL);
    // 隐藏显示缓冲区光标
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = 0;
    cci.dwSize = 1;
    SetConsoleCursorInfo(hOutput, &cci);
    SetConsoleCursorInfo(hBuffer, &cci);
    while (!kbhit())
    {
        show();
    }
}
