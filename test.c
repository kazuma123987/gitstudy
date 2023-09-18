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
    printf("sizeof(a[0][1]) = %zu\n", sizeof(a[0][1]));/*这里sizeof在32位系统输出类型为unsigned int,64位输出类型为unsigned long long
    为了防止无符号int类型或无符号long long类型越界（正整数部分超过有符号int或有符号long long），可使用size_t类型专用格式化说明符%zu*/
    printf("sizeof(&a[0][1]) = %zu\n", sizeof(&a[0][1]));
}