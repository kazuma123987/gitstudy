#include "stdio.h"
int main(void)
{
    int a[3][4];
    a[0][0]=1;
    printf("%p\n",a);
    printf("%p\n",&a);
    printf("%p\n",&a[0]);
    printf("%p\n",&a[0][0]);
    printf("%llx\n",*(&a));           //&a是整个二维数组的地址
    printf("%llx\n",*(a));            //a是数组第一行a[0]的地址
    printf("%llx\n",*(&a[0]));        //&a[0]是数组第一行a[0]的地址（a==&a[0]）
    printf("%llx\n",*(a[0]));         //a[0]是a[0][0]子元素的地址
    printf("%llx\n",*(&a[0][0]));     //&a[0][0]是a[0][0]子元素的地址(a[0]==&a[0][0])
}