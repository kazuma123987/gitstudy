#include <stdio.h>
void num()
{
    char a=-1;
    int b=-1;
    //编译器是32位所以长度均为4个字节
    printf("sizeof(unsigned int)=%d,sizeof(unsigned long)=%d\n",sizeof(unsigned int),sizeof(unsigned long));
    //%u和%lu分别输出（unsigned int）和（unsigned long）类型，在输出前会将输出前的值强行更换为unsigned长度的数字类型
    printf("alu=%u,a1u=%lu,bu=%u,blu=%lu\n", a,a,b,b);
}
int main()
{
    num();
    return 0;
}