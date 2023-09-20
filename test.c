#include <stdio.h>
#include "stdlib.h"
#include "string.h"
/*
1.局部变量：作用域为局部，作用时间为局部
2.静态局部变量：作用域为局部，作用时间是全局
3.全局变量：作用域和作用时间都是全局
4.一个子函数定义完局部变量并结束后再开启另一个子函数，则另一个子函数定义的局部变量地址与上一个子函数相同,所以，
不要返回函数的局部变量的值给其他函数，这是不安全的，使用malloc分配的地址一般是安全的，但最安全的方法是返回传入函数的指针，
5.全局变量与静态局部变量的地址是相邻的，且它们与局部变量的地址是相差很大的
6.全局变量和静态局部变量对于多线程是不安全的，因为它们的改变会并发改变多线程的值
7.不要使用全局变量在函数之间传值
*/
int gAll=10;//全局变量
void f1();
void f2();
int main()
{
   f1();
   f2();
   f2();
   f2();
   printf("in main gAll=%d\n",gAll);
}
void f1()
{
   static int ball;
   int i=12;
   int j=0;
   printf("in f1 gAll=%d\n",gAll);
   gAll++;
   printf("%p\n",&i);
   printf("%p\n",&j);
   printf("&ball=%p\n",&ball);
   printf("&gAll=%p\n",&gAll);//全局变量与局部变量相邻
}
void f2()
{
   static int all=1;
   int k=24;//调用完f1后得到i的地址,而不是j的地址
   all++;
   printf("the all is:%d\n",all);
   printf("%p\n",&k);
}