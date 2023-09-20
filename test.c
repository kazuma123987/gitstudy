#include <stdio.h>
#include "stdlib.h"
#include "string.h"
void fun1(char **p)//注意用子函数为主函数分配空间时要用双重指针
{
   *p=(char *)malloc(100);
}
char *fun2()
{
   char *p=NULL;
   p=(char*)malloc(100);
   strcpy(p,"hello world 2");
   return p;
}
int main()
{
   char *str1=NULL,*str2=NULL;
   fun1(&str1);
   str2=fun2();//改变了指针的地址，指向了一个有足够空间的地址
   strcpy(str1,"hello world 1");
   printf("str1为:%s\nstr2为:%s\n",str1,str2);
   free(str1);
   free(str2);
}