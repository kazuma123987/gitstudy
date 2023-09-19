#include "stdio.h"
void fun(int* (*q))//对传递的指针地址进行改变的方式
{
    (*q)++;
}
void f(int const a[])//使用int const可以保证数组里面的元素不被改变，因为数组也是一种指针
{
    a++;
}
int main(void)
{
    int a[2]={1,2};
    f(a);
    int *p=&a[0];
    fun(&p);
    printf("%d\n",*p);
}