#include "stdio.h"
int main(void)
{
    /*补充说明tips:
    1.a=*p++执行步骤:a=*p;p++
    2.*p++的优点：对应于一条汇编语句，提高程序速度
    */
    int a[2]={1,2};
    int *p=&a[0];
    printf("%d\n",&a[1]-&a[0]);//地址相减后不会直接输出，而是相减后除以sizeof(地址对应的数据类型)
    printf("%d\n",(p+1)-p);
}