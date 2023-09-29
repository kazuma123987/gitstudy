#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "conio.h"
#define password_size 20
void input_key(char key[])
{
   char ch=0;
   unsigned int i=0;
   while((ch=_getch())!='\r')//_getch是windows API中conio.h中的函数，是getch的优化(优化后支持更多编译器)
   //相比于getchar,_getch不会在屏幕上显示stdin流的信息，称为无回显输入,注意只有windows平台上能使用
   {
      if(ch=='\b'&&i>0)
      {
         key[--i]='\0';//删除上一次输入的信息
         putchar('\b');//光标退格
         putchar(' ');//空格删除上一次输出的信息，之后光标到下一格
         putchar('\b');//光标退格
      }
      else if(ch>='0'&&ch<='9'&&i<password_size)//仅允许输入0-9或回车键，且密码长度满了后无法输入
      {
         key[i++]=ch;
         putchar('*');
      }
   }
   key[i]='\0';
}
int main()
{
   char key[password_size+1];//保证密码长度能达到20
   printf("input the key,press 'enter' to exit\npassword:");
   input_key(key);
   printf("\npassword:%s",key);
   return 0;
}