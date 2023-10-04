#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
#include <windows.h> //Sleep()
#include <conio.h>  //kbhit(),_getch()
/*--------------------------移位操作要对unsigned类型做，因为非unsigned右移时符号位不变--------------------------*/
int main()
{
    unsigned int a=0x12345678;
    /*分析，a左移4位后后四位填0，右移28位后左边28位为0，与0相异或就是本身，最终实现了位的左旋转操作*/
    unsigned int b=(a<<4)^(a>>(sizeof(int)*8-4));//二进制左移四位就是十六进制左移1位
    unsigned char t=0x01;//这里t可代表8位led灯
    while(!kbhit())//如果没有按键输入则一直循环
    {
        t=(t<<1)^(t>>7);//每隔1000ms把t左移一位
        for(unsigned char mask=1<<7;mask;mask>>=1)
            printf("%d",mask&t?1:0);
        printf("\n");
        Sleep(1000);
    }
    printf("%x",b);
}