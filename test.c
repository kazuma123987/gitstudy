#include "stdio.h"
int main(void)
{
    int a=26;
    int const *p=&a;    //int const *q定义后的指针所指地址存放的值不能改变
    p++;                //指针所在地址可以变，但不能写做*p=2这样给所指的值赋值
    printf("%p\n",&a);
    printf("%p\n",p);
    int* const q=&a;    //int* const q定义的指针的地址不能改变
    *q=30;              //指针所值地址的值可以变，但不能写作q++给指针的地址赋值
    printf("%d",a);
}