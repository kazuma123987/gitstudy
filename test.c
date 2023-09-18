#include "stdio.h"
int main(void)
{
    int a[3][4];
    printf("%p\n",a);
    printf("%p\n",&a);
    printf("%p\n",&a[0]);
    printf("%p\n",&a[0][0]);
    printf("%p\n",&a[0][1]);
    printf("%llx\n",&a[0][1]);//%x和%lx只能输出最多4个字节（8位16进制），%llx输出long long类型长度字节数8（16位16进制）
    printf("sizeof(a[0][1])=%d\n",sizeof(a[0][1]));
    printf("sizeof(&a[0][1])=%d\n",sizeof(&a[0][1]));//32位系统地址是4个字节，64位是8个字节
}