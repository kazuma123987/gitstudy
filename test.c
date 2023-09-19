#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main(void) 
{
    char *str1="Hello,World!";
    char *str2="Hello,World!";
    str1[0]='B';                //使用指针初始化字符串时不能给字符串赋值，相当于const char *str1
    //两个不同的指针指向同一个地址
    printf("%p\n",str1);
    printf("%p\n",str2);

    char str[]="Hello,World!";
    str[0]='B';                 //使用数组初始化的字符串能赋值
    printf("%p\n",str);         //数组初始化字符串的地址和指针初始化字符串地址不同，且长度不同
}