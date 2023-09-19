#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main(void) 
{
    char str1[4];
    char str2[4];
    scanf("%s",str1);
    scanf("%s",str2);
    printf("%p\n",str1);
    printf("%p\n",str2);
    printf("%p\n",&str2[1]);
    printf("%s##%s##",str1,str2);//字符串越界后若后面有要使用的地址则会输出长度为sizeof(input_str)-sizeof(str)的字符串
}