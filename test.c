#include "stdio.h"
int main(void)
{
    /*对于二维数组a[x][y],可以认为：
    a就是&&a[0][0],
    &a就是&&&a[0][0],
    a[0]就是&a[0][0],
    &a[0]就是&&a[0][0]
    所以以上最终都可转化为为a[0][0]加上几个取地址符号&的形式*/
    int a[3][4];
    for(int i=0;i<3;i++)
    for(int j=0;j<4;j++)
    a[i][j]=(i+1)*(j+1);
    printf("%p\n", a);
    printf("%p\n", &a);
    printf("%p\n", &a[0]);
    printf("%p\n", &a[0][0]);
    printf("%llx\n", *(&a));       //&a是整个二维数组的地址
    printf("%llx\n", *a);          // a是数组第一行a[0]的地址
    printf("%llx\n", **a);         // a==&&a[0][0],那么**a==a[0][0]
    printf("%llx\n", *(&a[0]));    //&a[0]是数组第一行a[0]的地址（a==&a[0]）
    printf("%llx\n", *a[0]);       // a[0]是a[0][0]子元素的地址
    printf("%llx\n", *(&a[0][0])); //&a[0][0]是a[0][0]子元素的地址(a[0]==&a[0][0])
    printf("%llx , %llx\n",*(a[0]+1),*(&a[0][0]+1));
    printf("%llx , %llx\n",a[0],a[0]+1);  //对于地址：其加1后为其指向的元素的下一个元素的地址，相距sizeof(元素类型)的大小
}