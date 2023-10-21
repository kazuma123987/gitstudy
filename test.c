#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
#include <stdint.h>  //uint16_t,int8_t...
#include <windows.h> //Sleep()
#include <conio.h>   //kbhit(),_getch()
#include <time.h>    //time(),time_t,ctime
int main()

{
    int index = 0;
    while (!kbhit())
    {
        time_t now_time;
        time(&now_time);//给now_time赋值1970年开始经过的秒数(时间戳)
        char *p=ctime(&now_time);
        if(p[index=strcspn(p,"\n")]=='\n')p[index]='\0';//替换换行符
        printf("\r%s", p);//将光标移到行首打印字符串
        fflush(stdout);//刷新输出缓冲区
        Sleep(100);//延时100ms
    }
}