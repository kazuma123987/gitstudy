#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
int main()
{
   int *p[3];//定义了一个指针数组，可看作int *p0,*p1,*p2；定义后p[0],p[1],p[2]就是三个未分配空间的指针
   /*-------------------场景1（数字地址赋值）-------------------*/
   int a=1,b=2,c=3;
   //定义以后赋值
   p[0]=&a;
   p[1]=&b;
   p[2]=&c;
   //定义时赋值
   int *x[3]={&a,&b,&c};//*x[0]=1,*x[1]=2,*x[2]=3
   printf("*p[1]=%d,*x[1]=%d\n",*p[1],*x[1]);
   /*-------------------场景2（字符串地址赋值）-------------------*/
   char *str1="hello";
   char *str2=",";
   char *str3="world!";
   char *str[3]={str1,str2,str3};
   printf("%s%s%s\n",str[0],str[1],str[2]);
   /*-------------------场景3(动态内存分配自己赋值)-------------------*/
   for(int i=0;i<3;i++)
   {
   p[i]=malloc(sizeof(int));
   *p[i]=i+1;
   printf("%d ",*p[i]);
   }
}